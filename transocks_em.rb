#!/usr/bin/env ruby

require 'socket'
require 'rubygems'
require 'eventmachine'

class EM::Connection
  def orig_sockaddr
    addr = get_sock_opt(Socket::SOL_IP, 80) # Socket::SO_ORIGINAL_DST
    _, port, host = addr.unpack("nnN")

    [host, port]
  end
end

class TransocksClient < EM::P::Socks4
  attr_accessor :closed

  def initialize(proxied, host, port)
    @proxied = proxied
    super(host, port)
  end

  def receive_data(data)
    @proxied.send_data(data)
    proxy_incoming_to @proxied  unless @proxied.closed
  end

  def proxy_target_unbound
    close_connection
  end

  def unbind
    self.closed = true
    @proxied.close_connection_after_writing
  end
end

class TransocksTCPServer < EM::Connection
  attr_accessor :closed

  def initialize(ipfw_natd_style = false)
    @ipfw_natd_style = ipfw_natd_style
  end

  def post_init
    return  if @ipfw_natd_style

    orig_host, orig_port = orig_sockaddr
    orig_host = [orig_host].pack("N").unpack("CCCC")*'.'

    proxy_to orig_host, orig_port
  end

  def receive_data(data)
    @buf ||= ''
    @buf << data
    if @buf.gsub!(/\[DEST (\d+\.\d+\.\d+\.\d+) (\d+)\] *\n/m, '')
      orig_host, orig_port = $1, $2.to_i
      proxy_to orig_host, orig_port
      @proxied.send_data @buf
    end
  end

  def proxy_target_unbound
    close_connection
  end

  def unbind
    self.closed = true
    @proxied.close_connection_after_writing  if @proxied
  end

  private

  def proxy_to(orig_host, orig_port)
    puts "connecting to #{orig_host}:#{orig_port}"

    @proxied = EM.connect($connect_host, $connect_port, TransocksClient, self, orig_host, orig_port)
    proxy_incoming_to @proxied  unless @proxied.closed
  end
end

if ARGV.size < 3
  puts <<-EOF
    Usage: transsocks_em.rb <proxy_to_host> <proxy_to_port> <listen_port> [natd]
    natd - puts daemon in ipfw/natd bsd mode rather than linux iptables SO_ORIGINAL_DST mode,
           aka: get the original dest addr/port from the TCP stream rather than from getsockopt.
           current issue with natd mode is that the original addr wont be sent until the connection
           sends some initial data (this makes it incompatible with certain protocols, SSH for example)
  EOF
  exit 1
end

$connect_host, $connect_port, $listen_port = ARGV[0,3]

if (ARGV[3] == 'natd')
  natd = true
  puts "bsd ipfw/natd mode!"
end

EM.run do
  EM.error_handler { puts $!, $@ }

  EM.start_server '127.0.0.1', $listen_port, TransocksTCPServer, natd
end

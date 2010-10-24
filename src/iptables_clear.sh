#!/bin/sh
# Clear iptables rules. 
# Based on http://pikt.org/pikt/samples/iptables_reset_programs.cfg.html
#

IPTABLES=/sbin/iptables

if [ ! -x $IPTABLES ]; then
    echo "Can't execute $IPTABLES."
    exit 1
fi

$IPTABLES -P INPUT   ACCEPT
$IPTABLES -P OUTPUT  ACCEPT
$IPTABLES -P FORWARD ACCEPT
# Flush all chains
$IPTABLES -F
# Delete all chains
$IPTABLES -X

for table in filter nat mangle; do
    # Delete the table's rules
    $IPTABLES -t $table -F
    # Delete the table's chains    
    $IPTABLES -t $table -X
    # Delete the table's counters
    $IPTABLES -t $table -Z
done

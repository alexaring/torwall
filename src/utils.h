/**
 * This encapsulates all system calls
 */

/**
 * Copy a file from src to dst.
 * Return -1 on error, otherwise 0
 */
int copy(const char *src, const char *dst);

/**
 * Clear all iptables rules
 */
int clear_ipt_rules(void);

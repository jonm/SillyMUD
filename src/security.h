#ifndef _SECURITY_H
#define _SECURITY_H

#include <netinet/in.h>
#include <netdb.h>

struct ipv4_cidr {
  in_addr_t addr;
  in_addr_t netmask;
};

int wiz_security_check(int sock, char *name);
void set_mask6(size_t nbits, struct in6_addr *mask);
int ipv6_prefix_match(struct in6_addr *a1, struct in6_addr *a2,
                      struct in6_addr *mask);
void set_mask4(size_t nbits, struct in_addr *mask);
int ipv4_prefix_match(struct in_addr *a1, struct in_addr *a2,
                      struct in_addr *mask);
int matches_cidr(struct sockaddr *sa, char *s);
int matches_hostname(struct sockaddr *addr, struct hostent *hostaddrs);
int parse_cidr(int af, char *s, void *addr, void *mask);

#endif /* _SECURITY_H */

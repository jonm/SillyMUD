/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include "security.h"
#include "utility.h"
#include "utils.h"

int sec_check(char *arg, char *site) {
  char buf[255], buf2[255];
  FILE *f1;

  SPRINTF(buf, "security/%s", arg);

  if (!(f1 = fopen(buf, "rt"))) {
    log_msgf("Unable to open security file for %s.", arg);
    return (-1);
  }

  fgets(buf2, 250, f1);
  fclose(f1);

  if (!*buf2) {
    log_msgf("Security file for %s empty.", arg);
    return (-1);
  }

  if (buf2[strlen(buf2) - 1] == '\n')
    buf2[strlen(buf2) - 1] = '\0';

  if (!(strncmp(site, buf2, strlen(buf2)))) {
    return (1);
  }
  log_msgf("Site %s and %s don't match for %s. Booting.",
           site, buf2, arg);

  return (0);
}

int wiz_security_check(int sock, char *name) {
  char *filename;
  FILE *f;
  char buf[256];
  union {
    struct sockaddr_in addr;
    struct sockaddr_in6 addr6;
  } sa;
  struct hostent *he;
  socklen_t sa_len = sizeof(sa);

  log_msgf("Checking security access for %s", name);

  if (getpeername(sock, (struct sockaddr *)&sa, &sa_len) < 0) {
    log_msgf("ERROR: %s:%d: %s", __FILE__, __LINE__, strerror(errno));
    return(-1);
  }

  CREATE(filename, char, strlen(name) + strlen("security/") + 1);
  SPRINTF(filename, "security/%s", name);
  if ((f = fopen(filename, "r")) == NULL) {
    log_msgf("Unable to open security file for %s", name);
    return(-1);
  }

  while(fgets(buf, sizeof(buf), f)) {
    char *eol = strchr(buf, '\n');
    if (eol) *eol = '\0';
    
    /* first try to parse this as a CIDR block */
    if (matches_cidr((struct sockaddr *)&sa, buf)) {
      fclose(f);
      return(1);
    }

    /* next try it as a hostname */
    if ((he = gethostbyname2(buf, ((struct sockaddr *)&sa)->sa_family))) {
      if (matches_hostname((struct sockaddr *)&sa, he)) {
        fclose(f);
        return(1);
      }
    }
  }

  fclose(f);
  log_msgf("Unable to find matching security rule for %s", name);
  return(0);
}

int matches_cidr(struct sockaddr *sa, char *s) {
  union {
    struct in_addr addr4;
    struct in6_addr addr6;
  } addr;
  union {
    struct in_addr mask4;
    struct in6_addr mask6;
  } mask;
  
  if (!parse_cidr(sa->sa_family, s, &addr, &mask)) return(FALSE);
  switch(sa->sa_family) {
  case AF_INET:
    return ipv4_prefix_match(&((struct sockaddr_in *)sa)->sin_addr,
                             (struct in_addr *)&addr,
                             (struct in_addr *)&mask);
  case AF_INET6:
    return ipv6_prefix_match(&((struct sockaddr_in6 *)sa)->sin6_addr,
                             (struct in6_addr *)&addr,
                             (struct in6_addr *)&mask);
  }
  return(FALSE);
}

void set_mask6(size_t nbits, struct in6_addr *mask) {
  size_t i = 0;
  size_t remaining_bits = nbits;
  if (nbits > 8 * sizeof(struct in6_addr)) {
    log_msgf("ERROR: %s:%d: set_mask6: nbits too big (%d)",
	     __FILE__, __LINE__, nbits);
  }
  memset(mask, 0, sizeof(struct in6_addr));
  while(remaining_bits >= 8 && i < sizeof(struct in6_addr)) {
    mask->s6_addr[i] = 0xff;
    remaining_bits -= 8;
    i++;
  }
  if (i >= sizeof(struct in6_addr)) return;
  switch(remaining_bits) {
  case 7: mask->s6_addr[i] = 0xfe; break;
  case 6: mask->s6_addr[i] = 0xfb; break;
  case 5: mask->s6_addr[i] = 0xf8; break;
  case 4: mask->s6_addr[i] = 0xf0; break;
  case 3: mask->s6_addr[i] = 0xe0; break;
  case 2: mask->s6_addr[i] = 0xb0; break;
  case 1: mask->s6_addr[i] = 0x80; break;
  }
}

int ipv6_prefix_match(struct in6_addr *a1, struct in6_addr *a2,
		      struct in6_addr *mask) {
  for(size_t i=0; i < sizeof(struct in6_addr); i++) {
    if ((a1->s6_addr[i] & mask->s6_addr[i]) !=
	(a2->s6_addr[i] & mask->s6_addr[i])) {
      return(FALSE);
    }
  }
  return(TRUE);
}

void set_mask4(size_t nbits, struct in_addr *mask) {
  if ((size_t)nbits > 8 * sizeof(struct in_addr)) {
    log_msgf("ERROR: %s:%d: set_mask4: nbits too big (%d)",
	     __FILE__, __LINE__, nbits);
    mask->s_addr = 0xffffffff;
    return;
  }
  if (nbits == 0) {
    mask->s_addr = 0;
    return;
  }
  mask->s_addr = htonl(0xffffffff << ((8 * sizeof(struct in_addr)) - nbits));
}

int ipv4_prefix_match(struct in_addr *a1, struct in_addr *a2,
		      struct in_addr *mask) {
  return ((a1->s_addr & mask->s_addr) == (a2->s_addr & mask->s_addr));
}

size_t addr_size_bits(int af) {
  switch(af) {
  case AF_INET: return (8 * sizeof(struct in_addr));
  case AF_INET6: return (8 * sizeof(struct in6_addr));
  }
  return 0;
}

int parse_cidr_parts(int af, char *s, void *addr, int *nbits) {
  int out;
  char *slash = strchr(s, '/');
  if (slash != NULL) {
    *nbits = atoi(slash + 1);
    if (*nbits < 0 || (size_t)*nbits > addr_size_bits(af)) return(-1);
    *slash = '\0';
  } else {
    *nbits = addr_size_bits(af);
  }
  out = inet_pton(af, s, addr);
  if (slash != NULL) *slash = '/';
  return out;
}

int parse_cidr(int af, char *s, void *addr, void *mask) {
  int nbits;
  if (parse_cidr_parts(af, s, addr, &nbits) <= 0) return(FALSE);
  switch(af) {
  case AF_INET: set_mask4(nbits, (struct in_addr *)mask); break;
  case AF_INET6: set_mask6(nbits, (struct in6_addr *)mask); break;
  default:
    return(FALSE);
  }
  return(TRUE);
}

int matches_hostname(struct sockaddr *addr, struct hostent *hostaddrs) {
  if (addr->sa_family != hostaddrs->h_addrtype) return (FALSE);
  if (addr->sa_family == AF_INET) {
    struct sockaddr_in *v4addr = (struct sockaddr_in *)addr;
    struct in_addr **addr_list = (struct in_addr **)hostaddrs->h_addr_list;
    for(size_t i=0; addr_list[i] != NULL; i++) {
      if (!memcmp(&v4addr->sin_addr, addr_list[i], sizeof(struct in_addr))) {
        return(TRUE);
      }
    }
  } else if (addr->sa_family == AF_INET6) {
    struct sockaddr_in6 *v6addr = (struct sockaddr_in6 *)addr;
    struct in6_addr **addr_list = (struct in6_addr **)hostaddrs->h_addr_list;
    for(size_t i=0; addr_list[i] != NULL; i++) {
      if (!memcmp(&v6addr->sin6_addr, addr_list[i], sizeof(struct in6_addr))) {
        return(TRUE);
      }
    }
  }
  return(FALSE);
}

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <criterion/criterion.h>
#include "config.h"
#include "utils.h"
#include "security.h"

#ifdef HAVE_ARC4RANDOM_BUF
#define RANDOMIZE_BUF arc4random_buf
#elif HAVE_RAND
void randomize_buf(void *buf, size_t nbytes) {
  char *c = (char *)buf;
  for(size_t i=0; i<nbytes; i++) {
    c[i] = (char)(rand() & 0xff);
  }
}
#define RANDOMIZE_BUF randomize_buf
#endif

#ifdef HAVE_ARC4RANDOM
#define RANDOMINT arc4random
#elif HAVE_RAND
#define RANDOMINT() ((uint32_t)rand())
#endif

Test(security, parse_cidr_empty_string_v4) {
  char arg[255];
  struct in_addr a, mask;
  SPRINTF(arg, "");
  cr_assert_not(parse_cidr(AF_INET, arg, &a, &mask));
}

Test(security, parse_cidr_valid_v4) {
  char arg[255];
  struct in_addr a, mask;
  SPRINTF(arg, "6.7.8.9/24");
  cr_assert(parse_cidr(AF_INET, arg, &a, &mask));
  cr_assert_eq(a.s_addr, inet_addr("6.7.8.9"));
  cr_assert_eq(mask.s_addr, inet_addr("255.255.255.0"));
}

Test(security, parse_cidr_bad_addr_v4) {
  char arg[255];
  struct in_addr a, mask;
  SPRINTF(arg, "333.1.2.3/8");
  cr_assert_not(parse_cidr(AF_INET, arg, &a, &mask));
}

Test(security, parse_cidr_bad_prefix_v4) {
  char arg[255];
  struct in_addr a, mask;
  SPRINTF(arg, "6.7.8.9/55");
  cr_assert_not(parse_cidr(AF_INET, arg, &a, &mask));
}

Test(security, parse_cidr_no_prefix_v4) {
  char arg[255];
  struct in_addr a, mask;
  SPRINTF(arg, "6.7.8.9");
  cr_assert(parse_cidr(AF_INET, arg, &a, &mask));
  cr_assert_eq(a.s_addr, inet_addr("6.7.8.9"));
  cr_assert_eq(mask.s_addr, inet_addr("255.255.255.255"));
}

Test(security, parse_cidr_empty_string_v6) {
  char arg[255];
  struct in6_addr a, mask;
  SPRINTF(arg, "");
  cr_assert_not(parse_cidr(AF_INET6, arg, &a, &mask));
}

Test(security, parse_cidr_valid_v6) {
  char arg[255];
  struct in6_addr a, mask, a_out, mask_out;
  SPRINTF(arg, "1111:2222:3333:4444:5555:6666:7777:8888/24");
  cr_assert(parse_cidr(AF_INET6, arg, &a_out, &mask_out));
  inet_pton(AF_INET6, "1111:2222:3333:4444:5555:6666:7777:8888", &a);
  inet_pton(AF_INET6, "ffff:ff00:0000:0000:0000:0000:0000:0000", &mask);
  cr_assert(IN6_ARE_ADDR_EQUAL(&a, &a_out));
  cr_assert(IN6_ARE_ADDR_EQUAL(&mask, &mask_out));
}

Test(security, parse_cidr_bad_addr_v6) {
  char arg[255];
  struct in6_addr a, mask;
  SPRINTF(arg, "zoo/8");
  cr_assert_not(parse_cidr(AF_INET6, arg, &a, &mask));
}

Test(security, parse_cidr_bad_prefix_v6) {
  char arg[255];
  struct in6_addr a, mask;
  SPRINTF(arg, "1111:2222:3333:4444:5555:6666:7777:8888/200");
  cr_assert_not(parse_cidr(AF_INET6, arg, &a, &mask));
}

Test(security, parse_cidr_no_prefix_v6) {
  char arg[255];
  struct in6_addr a, mask, a_out, mask_out;
  SPRINTF(arg, "1111:2222:3333:4444:5555:6666:7777:8888");
  cr_assert(parse_cidr(AF_INET6, arg, &a_out, &mask_out));
  inet_pton(AF_INET6, "1111:2222:3333:4444:5555:6666:7777:8888", &a);
  inet_pton(AF_INET6, "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", &mask);
  cr_assert(IN6_ARE_ADDR_EQUAL(&a, &a_out));
  cr_assert(IN6_ARE_ADDR_EQUAL(&mask, &mask_out));
}

Test(security, set_mask6_zero_bits) {
  struct in6_addr mask;
  set_mask6(0, &mask);
  for(size_t i = 0; i < sizeof(struct in6_addr); i++) {
    cr_assert_eq(mask.s6_addr[i], 0);
  }
}

Test(security, set_mask6_all_bits) {
  struct in6_addr mask;
  set_mask6(128, &mask);
  for(size_t i = 0; i < sizeof(struct in6_addr); i++) {
    cr_assert_eq(mask.s6_addr[i], 0xff);
  }
}

Test(security, set_mask6_extra_bits) {
  struct in6_addr mask;
  set_mask6(129, &mask);
  for(size_t i = 0; i < sizeof(struct in6_addr); i++) {
    cr_assert_eq(mask.s6_addr[i], 0xff);
  }
}

Test(security, set_mask6_even_bytes) {
  struct in6_addr mask;
  set_mask6(24, &mask);
  for(size_t i = 0; i < 3; i++) {
    cr_assert_eq(mask.s6_addr[i], 0xff);
  }
  for(size_t i = 3; i < sizeof(struct in6_addr); i++) {
    cr_assert_eq(mask.s6_addr[i], 0);
  }
}

Test(security, set_mask6_partial_bytes) {
  struct in6_addr mask;
  set_mask6(28, &mask);
  for(size_t i = 0; i < 3; i++) {
    cr_assert_eq(mask.s6_addr[i], 0xff);
  }
  cr_assert_eq(mask.s6_addr[3], 0xf0);
  for(size_t i = 4; i < sizeof(struct in6_addr); i++) {
    cr_assert_eq(mask.s6_addr[i], 0);
  }
}

Test(security, set_mask6_vs_parsed) {
  struct in6_addr mask1;
  struct in6_addr mask2;
  set_mask6(64, &mask1);
  inet_pton(AF_INET6, "ffff:ffff:ffff:ffff:0000:0000:0000:0000", &mask2);
  cr_assert(IN6_ARE_ADDR_EQUAL(&mask1, &mask2));
}

Test(security, ipv6_prefix_match_same_address) {
  struct in6_addr a, mask;
  RANDOMIZE_BUF(a.s6_addr, sizeof(struct in6_addr));
  RANDOMIZE_BUF(mask.s6_addr, sizeof(struct in6_addr));
  cr_assert(ipv6_prefix_match(&a, &a, &mask));
}

Test(security, ipv6_prefix_match_zero_prefix) {
  struct in6_addr a1, a2, mask;
  RANDOMIZE_BUF(a1.s6_addr, sizeof(struct in6_addr));
  RANDOMIZE_BUF(a2.s6_addr, sizeof(struct in6_addr));
  memset(mask.s6_addr, 0, sizeof(struct in6_addr));
  cr_assert(ipv6_prefix_match(&a1, &a2, &mask));
}

Test(security, ipv6_prefix_nonmatch_last_bit) {
  struct in6_addr a1, a2, mask;
  RANDOMIZE_BUF(a1.s6_addr, sizeof(struct in6_addr));
  memcpy(a2.s6_addr, a1.s6_addr, sizeof(struct in6_addr));
  uint8_t b = a1.s6_addr[15];
  b = (b & 0x1) ? (b & ~0x1) : (b | 0x1);
  a2.s6_addr[15] = b;
  inet_pton(AF_INET6, "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", &mask);
  cr_assert_not(ipv6_prefix_match(&a1, &a2, &mask));
}

Test(security, ipv6_prefix_match_64_bits) {
  struct in6_addr a1, a2, mask;
  inet_pton(AF_INET6, "dead:beef:dead:beef:1111:2222:3333:4444", &a1);
  inet_pton(AF_INET6, "dead:beef:dead:beef:5555:6666:7777:8888", &a2);
  inet_pton(AF_INET6, "ffff:ffff:ffff:ffff:0000:0000:0000:0000", &mask);
  cr_assert(ipv6_prefix_match(&a1, &a2, &mask));
}

Test(security, ipv6_prefix_match_nonmatch_64_bits) {
  struct in6_addr a1, a2, mask;
  inet_pton(AF_INET6, "dead:beef:dead:beef:1111:2222:3333:4444", &a1);
  inet_pton(AF_INET6, "dead:beef:dead:beee:1111:2222:3333:4444", &a2);
  inet_pton(AF_INET6, "ffff:ffff:ffff:ffff:0000:0000:0000:0000", &mask);
  cr_assert_not(ipv6_prefix_match(&a1, &a2, &mask));
}

Test(security, set_mask4_zero_bits) {
  struct in_addr mask;
  set_mask4(0, &mask);
  cr_assert_eq(inet_addr("0.0.0.0"), mask.s_addr);
}

Test(security, set_mask4_all_bits) {
  struct in_addr mask;
  set_mask4(32, &mask);
  cr_assert_eq(inet_addr("255.255.255.255"), mask.s_addr);
}

Test(security, set_mask4_16_bits) {
  struct in_addr mask;
  set_mask4(16, &mask);
  cr_assert_eq(inet_addr("255.255.0.0"), mask.s_addr);
}

Test(security, set_mask4_odd_bits) {
  struct in_addr mask;
  set_mask4(20, &mask);
  cr_assert_eq(inet_addr("255.255.240.0"), mask.s_addr);
}

Test(security, set_mask4_extra_bits) {
  struct in_addr mask;
  set_mask4(33, &mask);
  cr_assert_eq(inet_addr("255.255.255.255"), mask.s_addr);
}

Test(security, ipv4_prefix_match_same_address) {
  struct in_addr a, mask;
  a.s_addr = RANDOMINT();
  mask.s_addr = RANDOMINT();
  cr_assert(ipv4_prefix_match(&a, &a, &mask));
}

Test(security, ipv4_prefix_match_zero_prefix) {
  struct in_addr a1, a2, mask;
  a1.s_addr = RANDOMINT();
  a2.s_addr = RANDOMINT();
  mask.s_addr = 0;
  cr_assert(ipv4_prefix_match(&a1, &a2, &mask));
}

Test(security, ipv4_prefix_nonmatch_last_bit) {
  struct in_addr a1, a2, mask;
  uint32_t t;
  a1.s_addr = RANDOMINT();
  t = ntohl(a1.s_addr);
  t = (t & 0x1) ? (t & ~0x1) : (t | 0x1);
  a2.s_addr = htonl(t);
  mask.s_addr = inet_addr("255.255.255.255");
  cr_assert_not(ipv4_prefix_match(&a1, &a2, &mask));
}

Test(security, ipv4_prefix_match_16_bits) {
  struct in_addr a1, a2, mask;
  a1.s_addr = inet_addr("6.7.8.9");
  a2.s_addr = inet_addr("6.7.3.4");
  mask.s_addr = inet_addr("255.255.0.0");
  cr_assert(ipv4_prefix_match(&a1, &a2, &mask));
}

Test(security, ipv4_prefix_match_nonmatch_16_bits) {
  struct in_addr a1, a2, mask;
  a1.s_addr = inet_addr("6.7.8.9");
  a2.s_addr = inet_addr("6.6.8.9");
  mask.s_addr = inet_addr("255.255.0.0");
  cr_assert_not(ipv4_prefix_match(&a1, &a2, &mask));
}

Test(security, matches_hostname_wrong_address_family) {
  struct sockaddr sa;
  struct hostent he;
  sa.sa_family = AF_INET;
  he.h_addrtype = AF_INET6;
  cr_assert_not(matches_hostname(&sa, &he));
}

Test(security, matches_hostname_unsupported_address_family) {
  struct sockaddr sa;
  struct hostent he;
  sa.sa_family = AF_UNIX;
  he.h_addrtype = AF_UNIX;
  cr_assert_not(matches_hostname(&sa, &he));
}

Test(security, matches_hostname_nonmatch_ipv4) {
  struct sockaddr_in sa;
  struct hostent he;
  struct in_addr *addr_list[] = { NULL };
  sa.sin_family = AF_INET;
  inet_pton(AF_INET, "6.7.8.9", &sa.sin_addr);
  he.h_addrtype = AF_INET;
  he.h_addr_list = (char **)&addr_list[0];
  cr_assert_not(matches_hostname((struct sockaddr *)&sa, &he));
}

Test(security, matches_hostname_nonmatch_ipv4_one_addr) {
  struct sockaddr_in sa;
  struct hostent he;
  struct in_addr addr;
  struct in_addr *addr_list[] = { &addr, NULL };
  sa.sin_family = AF_INET;
  inet_pton(AF_INET, "6.7.8.9", &sa.sin_addr);
  inet_pton(AF_INET, "1.2.3.4", &addr);
  he.h_addrtype = AF_INET;
  he.h_addr_list = (char **)&addr_list[0];
  cr_assert_not(matches_hostname((struct sockaddr *)&sa, &he));
}

Test(security, matches_hostname_ipv4) {
  struct sockaddr_in sa;
  struct hostent he;
  struct in_addr addr;
  struct in_addr *addr_list[] = { &addr, NULL };
  sa.sin_family = AF_INET;
  inet_pton(AF_INET, "6.7.8.9", &sa.sin_addr);
  inet_pton(AF_INET, "6.7.8.9", &addr);
  he.h_addrtype = AF_INET;
  he.h_addr_list = (char **)&addr_list[0];
  cr_assert(matches_hostname((struct sockaddr *)&sa, &he));
}

Test(security, matches_hostname_nonmatch_ipv6) {
  struct sockaddr_in6 sa;
  struct hostent he;
  struct in6_addr *addr_list[] = { NULL };
  sa.sin6_family = AF_INET6;
  inet_pton(AF_INET6, "dead:beef:dead:beef:dead:beef:dead:beef", &sa.sin6_addr);
  he.h_addrtype = AF_INET6;
  he.h_addr_list = (char **)&addr_list[0];
  cr_assert_not(matches_hostname((struct sockaddr *)&sa, &he));
}

Test(security, matches_hostname_nonmatch_ipv6_one_addr) {
  struct sockaddr_in6 sa;
  struct hostent he;
  struct in6_addr addr;
  struct in6_addr *addr_list[] = { &addr, NULL };
  sa.sin6_family = AF_INET6;
  inet_pton(AF_INET6, "dead:beef:dead:beef:dead:beef:dead:beef", &sa.sin6_addr);
  inet_pton(AF_INET6, "1111:2222:3333:4444:5555:6666:7777:8888", &addr);
  he.h_addrtype = AF_INET6;
  he.h_addr_list = (char **)&addr_list[0];
  cr_assert_not(matches_hostname((struct sockaddr *)&sa, &he));
}

Test(security, matches_hostname_ipv6) {
  struct sockaddr_in6 sa;
  struct hostent he;
  struct in6_addr addr;
  struct in6_addr *addr_list[] = { &addr, NULL };
  sa.sin6_family = AF_INET6;
  inet_pton(AF_INET6, "dead:beef:dead:beef:dead:beef:dead:beef", &sa.sin6_addr);
  inet_pton(AF_INET6, "dead:beef:dead:beef:dead:beef:dead:beef", &addr);
  he.h_addrtype = AF_INET6;
  he.h_addr_list = (char **)&addr_list[0];
  cr_assert(matches_hostname((struct sockaddr *)&sa, &he));
}

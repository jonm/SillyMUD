#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include "config.h"
#include "handler.h"

Test(handler, get_number_for_unnumbered_item) {
  char buf[256];
  int result;
  sprintf(buf,"hammer");
  result = get_number(buf);
  cr_assert_eq(result, 1);
  cr_assert_str_eq(buf, "hammer");
}

Test(handler, get_number_for_numbered_item) {
  char buf[256];
  int result;
  sprintf(buf,"2.hammer");
  result = get_number(buf);
  cr_assert_eq(result, 2);
  cr_assert_str_eq(buf, "hammer");
}

#include <stdio.h>
#include <criterion/criterion.h>

void dsearch(char *, char *);

Test(act_wizard, dsearch_simple) {
  char arg[255], dst[255];
  sprintf(arg, "Someone appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(dst, "Someone appears!");
}

Test(act_wizard, dsearch_simple_tilde) {
  char arg[255], dst[255];
  sprintf(arg, "Someone ~ appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(dst, "Someone appears!");
}

Test(act_wizard, dsearch_tilde_at_end) {
  char arg[255], dst[255];
  sprintf(arg, "Someone appears!~");
  dsearch(arg, dst);
  cr_assert_str_eq(dst, "Someone appears!");
}

Test(act_wizard, dsearch_tilde_N_simple) {
  char arg[255], dst[255];
  sprintf(arg, "Someone ~N appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(dst, "Someone $n appears!");
}

Test(act_wizard, dsearch_tilde_H_simple) {
  char arg[255], dst[255];
  sprintf(arg, "Someone ~H appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(dst, "Someone $s appears!");
}

Test(act_wizard, dsearch_double_tilde) {
  char arg[255], dst[255];
  sprintf(arg, "Someone ~~ appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(dst, "Someone  appears!");
}

Test(act_wizard, dsearch_double_substitution) {
  char arg[255], dst[255];
  sprintf(arg, "Someone ~N~N appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(dst, "Someone $n$n appears!");
}

Test(act_wizard, dsearch_simple_arg) {
  char arg[255], dst[255];
  sprintf(arg, "Someone appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(arg, "Someone appears!");
}

Test(act_wizard, dsearch_simple_tilde_arg) {
  char arg[255], dst[255];
  sprintf(arg, "Someone ~ appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(arg, "Someone appears!");
}

Test(act_wizard, dsearch_tilde_at_end_arg) {
  char arg[255], dst[255];
  sprintf(arg, "Someone appears!~");
  dsearch(arg, dst);
  cr_assert_str_eq(arg, "Someone appears!");
}

Test(act_wizard, dsearch_tilde_N_simple_arg) {
  char arg[255], dst[255];
  sprintf(arg, "Someone ~N appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(arg, "Someone $n appears!");
}

Test(act_wizard, dsearch_tilde_H_simple_arg) {
  char arg[255], dst[255];
  sprintf(arg, "Someone ~H appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(arg, "Someone $s appears!");
}

Test(act_wizard, dsearch_double_tilde_arg) {
  char arg[255], dst[255];
  sprintf(arg, "Someone ~~ appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(arg, "Someone  appears!");
}

Test(act_wizard, dsearch_double_substitution_arg) {
  char arg[255], dst[255];
  sprintf(arg, "Someone ~N~N appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(arg, "Someone $n$n appears!");
}

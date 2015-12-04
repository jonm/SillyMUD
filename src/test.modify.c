#include <stdio.h>
#include <criterion/criterion.h>
#include "structs.h"
#include "config.h"
#include "utils.h"
#include "interpreter.h"

void string_add(struct descriptor_data *d, char *str);
void string_add_static(struct descriptor_data *d, char *str);


Test(string_add, simple_line) {
  char *str = NULL;
  struct descriptor_data d = {
    .character = NULL,
    .str = &str,
    .max_str = 2048
  };

  char input_str[] = "Tell me what you want, what you really really want.";
  char expect_str[sizeof(input_str) + 3];
  strcpy(expect_str, input_str);
  strcat(expect_str, "\n\r");

  string_add(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_eq(d.output.head, NULL);
  cr_assert(d.str);
}

Test(string_add, simple_line_no_menu) {
  char *str = NULL;
  struct descriptor_data d = {
    .character = NULL,
    .str = &str,
    .max_str = 2048,
    .connected = CON_EXDSCR,
  };

  char input_str[] = "Tell me what you want, what you really really want.";
  char expect_str[sizeof(input_str) + 3];
  strcpy(expect_str, input_str);
  strcat(expect_str, "\n\r");

  string_add(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_eq(d.output.head, NULL);
  cr_assert(d.str);
}

Test(string_add, line_with_terminator) {
  char *str = NULL;

  struct descriptor_data d = {
    .character = NULL,
    .str = &str,
    .max_str = 2048,
  };

  char input_str[] = "Tell me what you want, what you really really want.@";
  char expect_str[] = "Tell me what you want, what you really really want.";

  string_add(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_eq(d.output.head, NULL);
  cr_assert(!d.str);
}


Test(string_add, menu_output) {
  char *str = NULL;

  struct descriptor_data d = {
    .character = NULL,
    .str = &str,
    .max_str = 2048,
    .connected = CON_EXDSCR,
  };
  d.output.head = NULL;

  char input_str[] = "Tell me what you want, what you really really want.@";
  char expect_str[] = "Tell me what you want, what you really really want.";

  string_add(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_str_eq(d.output.head->text, MENU);
  cr_assert(!d.str);
}


Test(string_add, line_too_long) {
  char *str = NULL;
  struct descriptor_data d = {
    .character = NULL,
    .str = &str,
    .max_str = 20
  };

  char input_str[] = "Tell me what you want, what you really really want.@";
  char expect_str[] = "Tell me what you wan";

  string_add(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_eq(d.output.head, NULL);
  cr_assert(!d.str);
}

Test(string_add, line_too_long_menu) {
  char *str = NULL;
  struct descriptor_data d = {
    .character = NULL,
    .str = &str,
    .max_str = 20,
    .connected = CON_EXDSCR,
  };

  char input_str[] = "Tell me what you want, what you really really want.@";
  char expect_str[] = "Tell me what you wan";

  string_add(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_str_eq(d.output.head->text, MENU);
  cr_assert(!d.str);
}

Test(string_add, append) {
  char *str = NULL;
  struct descriptor_data d = {
    .character = NULL,
    .str = &str,
    .max_str = 2048
  };

  str = malloc(128);
  strcpy(str, "Tell me what you want,");
  char input_str[] = " what you really really want.@";
  char expect_str[] = "Tell me what you want, what you really really want.";

  string_add(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_eq(d.output.head, NULL);
  cr_assert(!d.str);
}

Test(string_add, append_menu) {
  char *str = NULL;
  struct descriptor_data d = {
    .character = NULL,
    .str = &str,
    .max_str = 2048,
    .connected = CON_EXDSCR,
  };

  str = malloc(128);
  strcpy(str, "Tell me what you want,");
  char input_str[] = " what you really really want.@";
  char expect_str[] = "Tell me what you want, what you really really want.";

  string_add(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_str_eq(d.output.head->text, MENU);
  cr_assert(!d.str);
}


Test(string_add_static, simple_line) {
  char str[2048] = {0};
  struct descriptor_data d = {
    .character = NULL,
    .static_str = str,
    .max_str = sizeof(str)
  };

  char input_str[] = "Tell me what you want, what you really really want.";
  char expect_str[sizeof(input_str) + 3];
  strcpy(expect_str, input_str);
  strcat(expect_str, "\n\r");

  string_add_static(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_eq(d.output.head, NULL);
  cr_assert(d.static_str);
}

Test(string_add_static, simple_line_no_menu) {
  char str[2048] = {0};
  struct descriptor_data d = {
    .character = NULL,
    .static_str = str,
    .max_str = sizeof(str),
    .connected = CON_EXDSCR,
  };

  char input_str[] = "Tell me what you want, what you really really want.";
  char expect_str[sizeof(input_str) + 3];
  strcpy(expect_str, input_str);
  strcat(expect_str, "\n\r");

  string_add_static(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_eq(d.output.head, NULL);
  cr_assert(d.static_str);
}

Test(string_add_static, line_with_terminator) {
  char str[2048] = {0};
  struct descriptor_data d = {
    .character = NULL,
    .static_str = str,
    .max_str = sizeof(str),
  };

  char input_str[] = "Tell me what you want, what you really really want.@";
  char expect_str[] = "Tell me what you want, what you really really want.";

  string_add_static(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_eq(d.output.head, NULL);
  cr_assert(!d.static_str);
}


Test(string_add_static, menu_output) {
  char str[2048] = {0};
  struct descriptor_data d = {
    .character = NULL,
    .static_str = str,
    .max_str = sizeof(str),
    .connected = CON_EXDSCR,
  };
  d.output.head = NULL;

  char input_str[] = "Tell me what you want, what you really really want.@";
  char expect_str[] = "Tell me what you want, what you really really want.";

  string_add_static(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_str_eq(d.output.head->text, MENU);
  cr_assert(!d.static_str);
}


Test(string_add_static, line_too_long) {
  char str[20] = {0};
  struct descriptor_data d = {
    .character = NULL,
    .static_str = str,
    .max_str = sizeof(str),
  };

  char input_str[] = "Tell me what you want, what you really really want.@";
  char expect_str[] = "Tell me what you ";

  string_add_static(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_eq(d.output.head, NULL);
  cr_assert(!d.static_str);
}

Test(string_add_static, line_too_long_menu) {
  char str[20] = {0};
  struct descriptor_data d = {
    .character = NULL,
    .static_str = str,
    .max_str = sizeof(str),
    .connected = CON_EXDSCR,
  };

  char input_str[] = "Tell me what you want, what you really really want.@";
  char expect_str[] = "Tell me what you ";

  string_add_static(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_str_eq(d.output.head->text, MENU);
  cr_assert(!d.static_str);
}

Test(string_add_static, append) {
  char str[2048] = {0};
  struct descriptor_data d = {
    .character = NULL,
    .static_str = str,
    .max_str = sizeof(str),
  };

  strcpy(str, "Tell me what you want,");
  char input_str[] = " what you really really want.@";
  char expect_str[] = "Tell me what you want, what you really really want.";

  string_add_static(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_eq(d.output.head, NULL);
  cr_assert(!d.static_str);
}

Test(string_add_static, append_menu) {
  char str[2048] = {0};
  struct descriptor_data d = {
    .character = NULL,
    .static_str = str,
    .max_str = sizeof(str),
    .connected = CON_EXDSCR,
  };

  strcpy(str, "Tell me what you want,");
  char input_str[] = " what you really really want.@";
  char expect_str[] = "Tell me what you want, what you really really want.";

  string_add_static(&d, input_str);

  cr_assert_str_eq(str, expect_str);
  cr_assert_str_eq(d.output.head->text, MENU);
  cr_assert(!d.static_str);
}

#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include "config.h"
#include "structs.h"

extern void forget(struct char_data *ch, int spl);

Test(spell_parser, forget_known_spell) {
  struct char_data ch;
  struct char_skill_data skill0;
  ch.skills = &skill0;
  skill0.flags = 0x02;          /* SPELL_MEMORIZED */
  forget(&ch, 0);
  cr_assert_eq(skill0.flags, 0, "Did not unset memorized flag");
}

Test(spell_parser, forget_unknown_spell) {
  struct char_data ch;
  struct char_skill_data skill0;
  ch.skills = &skill0;
  skill0.flags = 0;
  forget(&ch, 0);
  cr_assert_eq(skill0.flags, 0, "Memorized flag did not stay unset");
}

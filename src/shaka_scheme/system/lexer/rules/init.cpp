#include "shaka_scheme/system/lexer/rules/init.hpp"
#include "shaka_scheme/system/lexer/rules/rule_token.hpp"

namespace shaka {
namespace lexer {
namespace rules {

void init_lexer_rules() {
  init_common_rules();
  init_rule_boolean();
  init_rule_character();
  init_rule_comment();
  init_rule_identifier();
  init_rule_number();
  init_rule_string();
  init_rule_token();
}

} // namespace shaka
} // namespace lexer
} // namespace rules


//
// Created by Herman on 3/7/2018.
//

#include "Character.hpp"
#include <string>

namespace shaka{

Character::Character(int val) {
  if(val > -1 && val < 128) {
    this->value = (char)val;
    return;
  }
  this->value = '\0';
}

bool operator==(const Character& a, const Character& b) {
  return a.value == b.value;
}

bool operator>(const Character& a, const Character& b) {
  return a.value > b.value;
}

bool operator<(const Character& a, const Character& b) {
  return a.value < b.value;
}

bool operator>=(const Character& a, const Character& b) {
  return a.value >= b.value;
}

bool operator<=(const Character& a, const Character& b) {
  return a.value <= b.value;
}

bool operator!=(const Character& a, const Character& b) {
  return a.value != b.value;
}

std::ostream& operator<<(std::ostream& out, const shaka::Character& chara) {
  std::string output = "#\\";
  switch((int)chara.value) {
  case 0:
    output += "null";
    break;
  case 7:
    output += "alarm";
    break;
  case 8:
    output += "backspace";
    break;
  case 9:
    output += "tab";
    break;
  case 10:
    output += "newline";
    break;
  case 13:
    output += "return";
    break;
  case 27:
    output += "escape";
    break;
  case 32:
    output += "space";
    break;
  case 127:
    output += "delete";
    break;
  default:
    output += chara.value;
  }
  out << output;
  return out;
}

} // namespace shaka
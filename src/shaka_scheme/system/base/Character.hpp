//
// Created by Herman on 3/7/2018.
//

#ifndef SHAKA_SCHEME_CHARACTER_HPP
#define SHAKA_SCHEME_CHARACTER_HPP

namespace shaka {

class Character {
public:
  Character(const Character& other) : value(other.value) {};
  Character(int val) : value(val) {};
  Character(char val) : value(val) {};

  friend bool operator==(const Character&, const Character&);
  friend bool operator>(const Character&, const Character&);
  friend bool operator<(const Character&, const Character&);
  friend bool operator>=(const Character&, const Character&);
  friend bool operator<=(const Character&, const Character&);
  friend bool operator!=(const Character&, const Character&);

  const char get_value() { return value; }
private:
  char value;
};

} // namespace shaka

#endif //SHAKA_SCHEME_CHARACTER_HPP

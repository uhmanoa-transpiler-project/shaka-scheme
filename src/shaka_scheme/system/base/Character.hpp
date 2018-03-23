//
// Created by Herman on 3/7/2018.
//

#ifndef SHAKA_SCHEME_CHARACTER_HPP
#define SHAKA_SCHEME_CHARACTER_HPP

#include <iostream>

namespace shaka {

class Character {
public:
  /**
   * @brief Copy constructor for character.
   * @param other Character object to be copied.
   */
  Character(const Character& other) : value(other.value) {};

  /**
   * @brief Constructor created via an integer.
   * @param val Integer to be casted to character.
   */
  Character(int val);

  /**
   * @brief Constructor created via a char.
   * @param val Character to be added.
   */
  Character(char val) : value(val) {};

  /**
   * @brief Empty constructor sets value at null character.
   */
  Character() : value('\0') {};


  friend bool operator==(const Character&, const Character&);
  friend bool operator>(const Character&, const Character&);
  friend bool operator<(const Character&, const Character&);
  friend bool operator>=(const Character&, const Character&);
  friend bool operator<=(const Character&, const Character&);
  friend bool operator!=(const Character&, const Character&);

  friend std::ostream& operator<<(std::ostream&, const shaka::Character&);

  char get_value() const { return value; }
private:
  char value;
};

} // namespace shaka

#endif //SHAKA_SCHEME_CHARACTER_HPP

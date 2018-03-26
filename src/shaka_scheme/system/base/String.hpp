#ifndef SHAKA_ASCII_STRING_H
#define SHAKA_ASCII_STRING_H

#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <algorithm>

namespace shaka {

class String {
public:
  String() {}

  // Construction from a std::string with iterators
  explicit String(std::string str) :
      str(str) {}

  // make new string with length "size"
  explicit String(std::size_t size) :
      str(size, ' ') {}

  // Create string with size "size" and initialize with character "b""
  String(std::size_t size, char b) :
      str(size, b) {}

  //Makes a copy of a string
  explicit String(const String& c) :
      str(c.str) {}

  explicit String(String&& c) :
      str(std::move(c.str)) {}

  // Copy and swap operator= assignment
  String& operator=(String rhs) {
    this->str = rhs.str;
    return *this;
  }

  // Copy assignment with substring.
  String(String& c, std::size_t index) :
      str(c.str.substr(index, std::string::npos)) {
  }

  // Makes a string out of part of another string
  String(String& c, std::size_t index, std::size_t length) :
      str(c.str.substr(index, length)) {}

  // return length of a_string
  std::size_t length() const {
    return str.size();
  }

  // takes the index, and returns the value of the index
  char ref(std::size_t index) const {
    return str.at(index);
  }

  // Set the internal string as another's shaka::String's substring
  void substring(const String& other, std::size_t start, std::size_t end) {
    this->str = other.str.substr(start, end-start);
  }

  void set(std::size_t index, char a) {
    this->str.at(index) = a;
  }

  void append(const String& other) {
    this->str += other.str;
  }

  void copy(const String& other) {
    this->str = other.str;
  }

  void copy(const String& other, std::size_t start) {
    this->str = other.str.substr(start, std::string::npos);
  }

  void copy(const String& other, std::size_t start, std::size_t end) {
    this->str = other.str.substr(start, end);
  }

  void fill(char fill) {
    for (char& c : this->str) {
      c = fill;
    }
  }

  void fill(char fill, std::size_t start) {
    for (std::size_t i = start; i < this->str.size(); ++i) {
      this->str.at(i) = fill;
    }
  }

  void fill(char fill, std::size_t start, std::size_t end) {
    for (std::size_t i = start; i < end; ++i) {
      this->str.at(i) = fill;
    }
  }

  void upcase() {
    std::for_each(str.begin(), str.end(), [](char c) {
      return static_cast<char>(std::toupper(static_cast<int>(c)));
    });
  }

  void downcase() {
    std::for_each(str.begin(), str.end(), [](char c) {
      return static_cast<char>(std::tolower(static_cast<int>(c)));
    });
  }

  friend bool operator==(const String& s1, const String& s2) {
    return s1.str.compare(s2.str) == 0;
  }

  friend bool operator!=(const String& s1, const String& s2) {
    return s1.str.compare(s2.str) != 0;
  }

  //  return !(s1 == s2);

  friend bool operator<(const String& s1, const String& s2) {
    return s1.str.compare(s2.str) < 0;
  }
  friend bool operator>(const String& s1, const String& s2) {
    return s1.str.compare(s2.str) > 0;
  }
  friend bool operator<=(const String& s1, const String& s2) {
    return s1.str.compare(s2.str) <= 0;
  }
  friend bool operator>=(const String& s1, const String& s2) {
    return s1.str.compare(s2.str) >= 0;
  }

  const std::string get_string() const {
    return this->str;
  }

  friend std::ostream& operator<<(std::ostream& lhs, const shaka::String& rhs);

private:
  std::string str;
};

} // namespace shaka
#endif // SHAKA_ASCII_STRING_H

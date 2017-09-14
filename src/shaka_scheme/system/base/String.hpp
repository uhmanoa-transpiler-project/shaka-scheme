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
  String(std::string str) :
      str(str) {}

  // make new string with length "size"
  String(int size) :
      str(' ', size) {}

  // Create string with size "size" and initialize with character "b""
  String(int size, char b) :
      str(b, size) {}

  //Makes a copy of a string
  String(const String& c) :
      str(c.str) {}

  String(String&& c) :
      str(std::move(c.str)) {}

  // Copy and swap operator= assignment
  String& operator=(String rhs) {
    this->str = rhs.str;
    return *this;
  }

  // Copy assignment with substring.
  String(String& c, int index) :
      str(c.str.substr(index, std::string::npos)) {
  }

  // Makes a string out of part of another string
  String(String& c, int index, int length) :
      str(c.str.substr(index, length)) {}

  // return length of a_string
  int length() const {
    return str.size();
  }

  // takes the index, and returns the value of the index
  char ref(int index) const {
    return str.at(index);
  }

  // Set the internal string as another's shaka::String's substring
  void substring(const String& other, int start, int end) {
    this->str = other.str.substr(start, end-start);
  }

  void set(int index, char a) {
    this->str.at(index) = a;
  }

  void append(const String& other) {
    this->str += other.str;
  }

  void copy(const String& other) {
    this->str = other.str;
  }

  void copy(const String& other, int start) {
    this->str = other.str.substr(start, std::string::npos);
  }

  void copy(const String& other, int start, int end) {
    this->str = other.str.substr(start, end);
  }

  void fill(char fill) {
    for (char& c : this->str) {
      c = fill;
    }
  }

  void fill(char fill, int start) {
    for (std::size_t i = start; i < this->str.size(); ++i) {
      this->str.at(i) = fill;
    }
  }

  void fill(char fill, int start, int end) {
    for (int i = start; i < end; ++i) {
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
    if (s1.get_string().size() != s2.get_string().size()) {
      return false;
    }
    for (int i = 0; i < static_cast<int>(s1.get_string().size()); i++) {

      if (s1.get_string()[i] != s2.get_string()[i]) {
        return false;
      }
    }
    return true;
  }

  friend bool operator!=(const String& s1, const String& s2) {
    if (s1.get_string().size() != s2.get_string().size()) {
      return true;
    }
    for (int i = 0; i < static_cast<int>(s1.get_string().size()); i++) {

      if (s1.get_string()[i] != s2.get_string()[i]) {
        return true;
      }
    }
    return false;
  }

  //  return !(s1 == s2);

  friend bool operator<(const String& s1, const String& s2) {
    if (s1.length() < s2.length())
      return true;
    return false;
    //return s1.a_string < s2.a_string;
  }
  friend bool operator>(const String& s1, const String& s2) {
    if (s1.length() > s2.length())
      return true;
    return false;
  }
  friend bool operator<=(const String& s1, const String s2) {
    if (s1.length() <= s2.length())
      return true;
    return false;
  }
  friend bool operator>=(const String& s1, const String& s2) {
    if (s1.length() >= s2.length())
      return true;
    return false;
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

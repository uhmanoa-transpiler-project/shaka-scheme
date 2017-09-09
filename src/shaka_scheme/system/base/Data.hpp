//
// Created by aytas on 8/6/2017.
//

#ifndef SHAKA_SCHEME_DATA_HPP
#define SHAKA_SCHEME_DATA_HPP

#include "shaka_scheme/system/exceptions/InvalidInputException.hpp"
#include "shaka_scheme/system/exceptions/TypeException.hpp"

#include "shaka_scheme/system/base/Symbol.hpp"
#include "shaka_scheme/system/base/String.hpp"
#include "shaka_scheme/system/base/Boolean.hpp"
#include "shaka_scheme/system/base/IEnvironment.hpp"
#include "shaka_scheme/system/base/DataPair.hpp"

#include <memory>

namespace shaka {

class Number;
class Symbol;
class String;
class Boolean;
class DataNode;
class Environment;
class DataPair;
class UserStructData;

//using Data = boost::variant<
//    NodePtr,
//    EnvPtr,
//    shaka::Symbol,
//    //shaka::Number,
//    shaka::String,
//    shaka::Boolean
////boost::recursive_wrapper<shaka::Procedure>,
////boost::recursive_wrapper<shaka::NativeProcedure>,
////boost::recursive_wrapper<shaka::PrimitiveProcedure>
//>;

class Data {
public:
  enum class Type : int {
    INVALID = -1,
    DATA_PAIR,
    ENVIRONMENT,
    SYMBOL,
    NUMBER,
    STRING,
    BOOLEAN
  };
private:
  Type type_tag;

  union {
    shaka::String string;
    shaka::DataPair data_pair;
    shaka::Symbol symbol;
    shaka::Boolean boolean = shaka::Boolean(false);
  };

public:

  Data(shaka::String other) {
    new(&string) shaka::String(other);
    this->type_tag = Type::STRING;
  }

  Data(shaka::Symbol other) {
    new(&symbol) shaka::Symbol(other);
    this->type_tag = Type::SYMBOL;
  }

  Data(shaka::Boolean other) {
    new(&boolean) shaka::Boolean(other);
    this->type_tag = Type::BOOLEAN;
  }

  Data(const Data& other);

  ~Data();

  template<typename T>
  T get() const;

  Type get_type() const {
    return this->type_tag;
  }
};

template<> shaka::String shaka::Data::get<shaka::String>() const;
template<> shaka::Symbol shaka::Data::get<shaka::Symbol>() const;
template<> shaka::Boolean shaka::Data::get<shaka::Boolean>() const;

std::ostream& operator<<(std::ostream& lhs, const shaka::Data& rhs);

} // namespace shaka

#endif //SHAKA_SCHEME_DATA_HPP

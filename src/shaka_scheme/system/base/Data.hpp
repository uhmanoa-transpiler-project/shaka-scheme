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

#include <memory>

namespace shaka {

class Number;
class Symbol;
class String;
class Boolean;
class DataNode;
class Environment;
using NodePtr   = std::shared_ptr<DataNode>;
using EnvPtr    = std::shared_ptr<Environment>;
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
    DATANODE,
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
    shaka::Symbol symbol = shaka::Symbol(std::string());
    shaka::Boolean boolean;
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

template<>
shaka::String shaka::Data::get<shaka::String>() const {
  if (type_tag != Type::STRING) {
    throw new shaka::TypeException(3, "Could not get() String from Data");
  }
  return this->string;
}

template<>
shaka::Symbol shaka::Data::get<shaka::Symbol>() const {
  if (type_tag != Type::SYMBOL) {
    throw new shaka::TypeException(4, "Could not get() Symbol from Data");
  }
  return this->symbol;
}

template<>
shaka::Boolean shaka::Data::get<shaka::Boolean>() const {
  if (type_tag != Type::BOOLEAN) {
    throw new shaka::TypeException(5, "Could not get() Boolean from Data");
  }
  return this->boolean;
}

std::ostream& operator<<(std::ostream& lhs, const shaka::Data& rhs) {
  switch (rhs.get_type()) {
  case shaka::Data::Type::SYMBOL: {
    lhs << rhs.get<shaka::Symbol>();
    break;
  }
  case shaka::Data::Type::STRING: {
    lhs << rhs.get<shaka::String>();
    break;
  }
  case shaka::Data::Type::BOOLEAN: {
    lhs << rhs.get<shaka::Boolean>();
    break;
  }
  }
}

}

#endif //SHAKA_SCHEME_DATA_HPP

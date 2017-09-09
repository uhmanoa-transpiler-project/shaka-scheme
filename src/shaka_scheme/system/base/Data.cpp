//
// Created by aytas on 8/6/2017.
//

#include "shaka_scheme/system/base/Data.hpp"


shaka::Data::Data(const shaka::Data &other) : type_tag
                                                  (shaka::Data::Type::INVALID) {
  // Initialize the internal field based on what type we have tagged.
  switch (other.type_tag) {
  case shaka::Data::Type::SYMBOL: {
    new(&symbol) shaka::Symbol(other.symbol);
    break;
  }
//  case shaka::Data::Type::NUMBER: {
//    this->number = other.number;
//    break;
//  }
  case shaka::Data::Type::STRING: {
    new(&string) shaka::String(other.string);
    break;
  }
  case shaka::Data::Type::BOOLEAN: {
    new(&boolean) shaka::Boolean(other.boolean);
    break;
  }
//  case shaka::Data::Type::DATA_NODE: {
//    new(&data_node) std::shared_ptr<shaka::DataNode>(other.data_node);
//    break;
//  }
//  case shaka::Data::Type::ENVIRONMENT: {
//    new(&environment) std::shared_ptr<shaka::IEnvironment>(other.environment);
//    break;
//  }
  default: {
    throw shaka::InvalidInputException(1, "Invalid data type in Data "
        "constructor.");
  }
  case Type::INVALID:break;
  //case Type::DATANODE:break;
  case Type::ENVIRONMENT:break;
  case Type::NUMBER:break;
  }
  this->type_tag = other.type_tag;
}
shaka::Data::~Data() {
  // Destroy the internal field based on what type we have tagged.
  switch (this->type_tag) {
  case shaka::Data::Type::SYMBOL: {
    this->symbol.~Symbol();
    break;
  }
//  case shaka::Data::Type::NUMBER: {
//    this->number = other.number;
//    break;
//  }
  case shaka::Data::Type::STRING: {
    this->string.~String();
    break;
  }
  case shaka::Data::Type::BOOLEAN: {
    this->boolean.~Boolean();
    break;
  }
//  case shaka::Data::Type::DATA_NODE: {
//    this->data_node::~data_node();
//    break;
//  }
//  case shaka::Data::Type::ENVIRONMENT: {
//    this->environment::~environment();
//    break;
//  }
  }

}

template<>
shaka::String shaka::Data::get<shaka::String>() const {
  if (this->get_type() != Type::STRING) {
    throw new shaka::TypeException(3, "Could not get() String from Data");
  }
  return this->string;
}

template<>
shaka::Symbol shaka::Data::get<shaka::Symbol>() const {
  if (this->get_type() != Type::SYMBOL) {
    throw new shaka::TypeException(4, "Could not get() Symbol from Data");
  }
  return this->symbol;
}

template<>
shaka::Boolean shaka::Data::get<shaka::Boolean>() const {
  if (this->get_type() != Type::BOOLEAN) {
    throw new shaka::TypeException(5, "Could not get() Boolean from Data");
  }
  return this->boolean;
}

namespace shaka {

std::ostream& operator<<(std::ostream& lhs, const shaka::Data& rhs) {
  switch (rhs.get_type()) {
  case shaka::Data::Type::SYMBOL: {
    const auto temp = rhs.get<shaka::Symbol>();
    lhs << temp;
    break;
  }
  case shaka::Data::Type::STRING: {
    const auto temp = rhs.get<shaka::String>();
    lhs << temp;
    break;
  }
  case shaka::Data::Type::BOOLEAN: {
    const auto temp = rhs.get<shaka::Boolean>();
    lhs << temp;
    break;
  }
  }
}

} // namespace shaka

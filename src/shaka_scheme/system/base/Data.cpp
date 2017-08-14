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
  case Type::DATANODE:break;
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


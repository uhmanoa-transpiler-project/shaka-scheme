//
// Created by aytas on 8/6/2017.
//

#include <shaka_scheme/system/exceptions/MissingImplementationException.hpp>

#include "shaka_scheme/system/base/Data.hpp"

shaka::Data::Data(const shaka::Data& other) :
    type_tag(shaka::Data::Type::UNSPECIFIED) {
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
  case shaka::Data::Type::DATA_PAIR: {
    new(&data_pair) shaka::DataPair(other.data_pair);
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
  case shaka::Data::Type::NULL_LIST: {
    break;
  }
  default: {
    throw shaka::InvalidInputException(1, "Invalid data type in Data "
        "constructor.");
  }
  case Type::UNSPECIFIED:break;
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
  case shaka::Data::Type::DATA_PAIR: {
    this->data_pair.~DataPair();
    break;
  }
//  case shaka::Data::Type::ENVIRONMENT: {
//    this->environment::~environment();
//    break;
//  }
  case shaka::Data::Type::NULL_LIST: {
    break;
  }
  default: {}
  }

}

template<>
shaka::String& shaka::Data::get<shaka::String>() {
  if (this->get_type() != Type::STRING) {
    throw new shaka::TypeException(3, "Could not get() String from Data");
  }
  return this->string;
}

template<>
shaka::Symbol& shaka::Data::get<shaka::Symbol>() {
  if (this->get_type() != Type::SYMBOL) {
    throw new shaka::TypeException(4, "Could not get() Symbol from Data");
  }
  return this->symbol;
}

template<>
shaka::Boolean& shaka::Data::get<shaka::Boolean>() {
  if (this->get_type() != Type::BOOLEAN) {
    throw new shaka::TypeException(5, "Could not get() Boolean from Data");
  }
  return this->boolean;
}

template<>
shaka::DataPair& shaka::Data::get<shaka::DataPair>() {
  if (this->get_type() != Type::DATA_PAIR) {
    throw new shaka::TypeException(6, "Could not get() DataPair from Data");
  }
  return this->data_pair;
}

namespace shaka {

std::ostream& operator<<(std::ostream& lhs, shaka::Data rhs) {
  switch (rhs.get_type()) {
  case shaka::Data::Type::SYMBOL: {
    auto& temp = rhs.get<shaka::Symbol>();
    lhs << temp;
    break;
  }
  case shaka::Data::Type::STRING: {
    auto& temp = rhs.get<shaka::String>();
    lhs << '\"' << temp << '\"';
    break;
  }
  case shaka::Data::Type::BOOLEAN: {
    auto& temp = rhs.get<shaka::Boolean>();
    lhs << temp;
    break;
  }
  case shaka::Data::Type::UNSPECIFIED: {
    lhs << "#!unspecified";
    break;
  }
  case shaka::Data::Type::DATA_PAIR: {
    DataPair& pair = rhs.get<DataPair>();
    // Print out the first item in the pair.
    lhs << "(";
    lhs << *pair.car();
    // If the cdr is a pair, then print out a space, get the next pair, iterate.
    while (pair.cdr()->get_type() == shaka::Data::Type::DATA_PAIR) {
      pair = pair.cdr()->get<DataPair>();
      lhs << ' ' << *pair.car();
    }
    // Else, print out:
    //    - a ) if the last item is a null list
    //    - a . <last item>) if the last item is not a null list
    if (pair.cdr()->get_type() != shaka::Data::Type::NULL_LIST) {
      lhs << " . " << *pair.cdr() << ')';
    } else {
      lhs << ')';
    }
    break;
    throw shaka::MissingImplementationException(1337,
                                                "DataPair printing is not supported yet "
                                                    "(implement in Data.cpp after adding more helper functions for "
                                                    "determining whether the current item is a list, dotted pair, etc.)");
  }
  case shaka::Data::Type::ENVIRONMENT: {
    throw shaka::MissingImplementationException(1337,
                                                "Environment printing is not supported "
                                                    "yet (Environment has not been implemented yet)");
    break;
  }
  case shaka::Data::Type::NUMBER: {
    throw shaka::MissingImplementationException(1337,
                                                "Number has not been implemented in "
                                                    "master yet");
    break;
  }
  case shaka::Data::Type::NULL_LIST: {
    lhs << "()";
    break;
  }
  default: {}
  }
  return lhs;
}

NodePtr create_unspecified() {
  Data data;
  data.type_tag = shaka::Data::Type::UNSPECIFIED;
  return create_node(data);
}
} // namespace shaka

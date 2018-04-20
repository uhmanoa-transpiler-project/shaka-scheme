//
// Created by aytas on 8/6/2017.
//

#ifndef SHAKA_SCHEME_DATA_HPP
#define SHAKA_SCHEME_DATA_HPP

#include "shaka_scheme/system/exceptions/InvalidInputException.hpp"
#include "shaka_scheme/system/exceptions/TypeException.hpp"
#include "shaka_scheme/system/base/Number.hpp"
#include "shaka_scheme/system/base/Symbol.hpp"
#include "shaka_scheme/system/base/String.hpp"
#include "shaka_scheme/system/base/Boolean.hpp"
#include "shaka_scheme/system/base/IEnvironment.hpp"
#include "shaka_scheme/system/base/DataPair.hpp"
#include "shaka_scheme/system/base/PrimitiveFormMarker.hpp"
#include "shaka_scheme/system/base/Vector.hpp"
#include "shaka_scheme/system/base/Bytevector.hpp"

#include "shaka_scheme/system/vm/Closure.hpp"
#include "shaka_scheme/system/vm/CallFrame.hpp"
#include "shaka_scheme/system/gc/GCNode.hpp"


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
class Closure;
class Vector;
class Bytevector;

class CallFrame;
class PrimitiveFormMarker;

class Data;

//using NodePtr = std::shared_ptr<Data>;
using NodePtr = gc::GCNode;

/**
 * @brief The basic sum type or variant type of all possible Scheme data types.
 */
class Data {
public:
  enum class Type : int {
    UNSPECIFIED = -1,
    DATA_PAIR,
    ENVIRONMENT,
    SYMBOL,
    NUMBER,
    STRING,
    BOOLEAN,
    CLOSURE,
    CALL_FRAME,
    NULL_LIST,
    PRIMITIVE_FORM,
    VECTOR,
    BYTEVECTOR
  };
private:
  Type type_tag;

  union {
    shaka::Boolean boolean = shaka::Boolean(false);
    shaka::String string;
    shaka::DataPair data_pair;
    shaka::Symbol symbol;
    shaka::Number number;
    shaka::Closure closure;
    shaka::CallFrame call_frame;
    shaka::PrimitiveFormMarker primitive_form;
    shaka::Vector vector;
    shaka::Bytevector bytevector;
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

  Data(shaka::Number other) {
    new(&number) shaka::Number(other);
    this->type_tag = Type::NUMBER;
  }

  Data(shaka::DataPair other) {
    new(&data_pair) shaka::DataPair(other);
    this->type_tag = Type::DATA_PAIR;
  }

  Data(shaka::Closure other) {
    new(&closure) shaka::Closure(other);
    this->type_tag = Type::CLOSURE;
  }

  Data(shaka::CallFrame other) {
    new(&call_frame) shaka::CallFrame(other);
    this->type_tag = Type::CALL_FRAME;
  }

  Data(shaka::PrimitiveFormMarker other) {
    new(&primitive_form) shaka::PrimitiveFormMarker(other);
    this->type_tag = Type::PRIMITIVE_FORM;
  }

  Data(shaka::Vector other) {
    new(&vector) shaka::Vector(other);
    this->type_tag = Type::VECTOR;
  }

  Data(shaka::Bytevector other) {
    new(&bytevector) shaka::Bytevector(other);
    this->type_tag = Type::BYTEVECTOR;
  }

  /**
   * @brief A default constructor that constructs to a null list.
   */
  Data() {
    this->type_tag = Type::NULL_LIST;
  }

  /**
   * @brief Copy constructor.
   * @param other The object to copy from.
   *
   * Uses copy-and-swap idiom.
   */
  Data(const Data& other);

  /**
   * @brief Destroys the internal data according to the type tag.
   */
  ~Data();

  /**
   * @brief Get the internal data, if it matches the type T.
   * @tparam T The type to get.
   * @return The object contained within this Data, if it matches the type T.
   * @throws shaka::TypeException when T does not match the internal data type
   * currently contained by data.
   */
  template<typename T>
  T& get();

  /**
   * @brief Get the type of the currently held internal data.
   * @return The type tag of the currently held item.
   */
  Type get_type() const {
    return this->type_tag;
  }

  friend NodePtr create_unspecified();
};

template<> shaka::String& shaka::Data::get<shaka::String>();
template<> shaka::Symbol& shaka::Data::get<shaka::Symbol>();
template<> shaka::Boolean& shaka::Data::get<shaka::Boolean>();
template<> shaka::DataPair& shaka::Data::get<shaka::DataPair>();
template<> shaka::Closure& shaka::Data::get<shaka::Closure>();
template<> shaka::CallFrame& shaka::Data::get<shaka::CallFrame>();
template<> shaka::PrimitiveFormMarker& shaka::Data::get<shaka::PrimitiveFormMarker>();
template<> shaka::Number& shaka::Data::get<shaka::Number>();
template<> shaka::Vector& shaka::Data::get<shaka::Vector>();
template<> shaka::Bytevector& shaka::Data::get<shaka::Bytevector>();

std::ostream& operator<<(std::ostream& lhs, shaka::Data rhs);

/**
 * @brief A method to create an unspecified value.
 * @return A new allocated node that represents an unspecified value.
 */
NodePtr create_unspecified();

} // namespace shaka

#endif //SHAKA_SCHEME_DATA_HPP

//
// Created by aytas on 9/3/2017.
//

#ifndef SHAKA_SCHEME_DATAPAIR_HPP
#define SHAKA_SCHEME_DATAPAIR_HPP

#include <memory>

namespace shaka {

class Data;

using NodePtr = std::shared_ptr<Data>;

/**
 * @brief Creates a managed NodePtr from an object of Data.
 * @param data The shaka::Data to create a managed NodePtr from.
 * @return The new managed NodePtr
 *
 * @note This function is meant to be replaced with an alternate
 * implementation depending on what type of memory management system is
 * used with Shaka Scheme. This means that whether using garbage collection
 * or reference counting, we trust that all managed objects will either be
 * managed by user-supplied logic in this function, or through
 */
NodePtr create_node(Data data);

/**
 * @brief The data representation of a Scheme pair.
 *
 * It contains managed references (NodePtr) to other shaka::Data.
 *
 * @note This class references Data, which means using this also requires
 * manually including Data.hpp.
 */
class DataPair {
  NodePtr left;
  NodePtr right;
public:
  /**
   * @brief By default, initializes the DataPair to a dotted pair of
   * '(() . ()) or just '(()).
   */
  DataPair();

  /**
   * @brief Basic Data constructor.
   * @param data The shaka::Data to construct from.
   *
   * Leaves the right node as nullptr.
   */
  DataPair(Data data);

  /**
   * @brief Constructs the pair of Data to initialize the DataPair to.
   * @param left_data The shaka::Data to construct the left node from.
   * @param right_data The shaka::Data to construct the right node from.
   */
  DataPair(Data left_data, Data right_data);

  /**
   * @brief Constructs left to node, and right to nullptr.
   * @param node The NodePtr to construct left to.
   */
  DataPair(NodePtr node);

  /**
   * @brief Copies the NodePtr for left and right.
   * @param left_node The NodePtr to copy into left.
   * @param right_node The NodePtr to copy into right.
   */
  DataPair(NodePtr left_node, NodePtr right_node);

  /**
   * @brief Copy constructor. Must copy all items by value, not reference.
   * @param other The object to copy.
   */
  DataPair(const DataPair& other);

  /**
   * @brief Move constructor.
   * @param other THe object to copy.
   *
   * Uses the copy-and-swap idiom.
   */
  DataPair(DataPair&& other);

  /**
   * @brief Overloaded swap function for DataPair.
   * @param lhs
   * @param rhs
   */
  friend void swap(shaka::DataPair& lhs, shaka::DataPair& rhs);

  /**
   * @brief Overloaded assignment operator.
   * @param other The other item to swap with.
   * @return A reference to this object.
   *
   * Uses the copy-and-swap idiom.
   */
  shaka::DataPair& operator=(shaka::DataPair other);

////////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Returns the first item of the pair.
   * @return The left NodePtr.
   */
  NodePtr car() const {
    return this->left;
  }

  /**
   * @brief Returns the second item of the pair.
   * @return The right NodePtr.
   */
  NodePtr cdr() const {
    return this->right;
  }

  /**
   * @brief Sets the first item of the pair.
   * @param node The node to set as the left node.
   */
  void set_car(NodePtr node) {
    this->left = node;
  }

  /**
   * @brief Sets the second item of the pair.
   * @param node The node to set as the right node.
   */
  void set_cdr(NodePtr node) {
    this->right = node;
  }
};

} // namespace shaka

#endif //SHAKA_SCHEME_DATAPAIR_HPP

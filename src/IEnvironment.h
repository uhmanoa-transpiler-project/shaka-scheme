#ifndef SHAKA_IENVIRONMENT_H
#define SHAKA_IENVIRONMENT_H

namespace shaka {

/// @brief The interface class for the Environment
template <typename Key, typename Value>
class IEnvironment {
    /// @brief Gets the pointer to the parent environment.
    ///
    /// Will return `nullptr` if there is no parent.
    std::shared_ptr<IEnvironment>   get_parent() = 0;

    /// @brief Returns a reference to the value refered
    ///        to by the key. Note that the key must exist,
    ///        otherwise, it throws an exception.
    Value&                          operator[](const Key& key) = 0;

    /// @brief Returns whether a key has an associated value
    ///        in the Environment.
    bool                            contains(const Key& key) = 0;

    /// @brief Returns a reference to the value refered
    ///        to by the key. Note that the key must exist,
    ///        otherwise, it throws an exception. Should be
    ///        identical to `operator[]`.
    Value&                          get_value(const Key& key) = 0;

    /// @brief Sets an element in the Environment referred to be the `key`
    ///        and then sets its value to `value`.
    void                            set_value(const Key& key, Value value) = 0;

    /// @brief Returns a list of all the keys in the Environment.
    std::vector<Key>                get_keys() = 0;
};

}

#endif // SHAKA_IENVIRONMENT_H

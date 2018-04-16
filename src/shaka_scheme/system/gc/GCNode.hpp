//
// Created by mortrax on 2/5/18.
//

#ifndef SHAKA_SCHEME_GCNODE_HPP
#define SHAKA_SCHEME_GCNODE_HPP


namespace shaka {
  class Data;

    namespace gc {
      class GCData;
/**
 * @brief Defines the type of GCNode, the object which will
 * wrap over GCData, providing a managed interface to Data
 */
        class GCNode {
        public:

            GCNode();
            GCNode(GCData *data);
            GCNode(const GCNode& other);
            ~GCNode();

            Data &operator*() const;
            Data *operator->() const;

            Data *get() const;
            operator bool() const;

            friend bool operator==(const GCNode& lhs, const GCNode& rhs);
            friend bool operator!=(const GCNode& lhs, const GCNode& rhs);

        private:
            GCData *gc_data;
        };


    } // namespace gc
} // namespace shaka

#endif //SHAKA_SCHEME_GCNODE_HPP

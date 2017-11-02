//
// Created by aytas on 10/23/2017.
//

#ifndef SHAKA_SCHEME_SYNTAXOBJECT_HPP
#define SHAKA_SCHEME_SYNTAXOBJECT_HPP

#include <shaka_scheme/system/base/Data.hpp>

#include <set>

namespace shaka {

using ScopeSet = std::set<std::size_t>;

struct SyntaxObject {
public:
  SyntaxObject(NodePtr data, ScopeSet scopes, unsigned line, unsigned col) :
    data(data),
    scopes(scopes),
    line_num(line),
    col_num(col) {}

  SyntaxObject(NodePtr data, unsigned line, unsigned col) :
      data(data),
      line_num(line),
      col_num(col) {}

  SyntaxObject(NodePtr data) :
    data(data),
    line_num(0),
    col_num(0) {}

  NodePtr data;
  ScopeSet scopes;
  unsigned line_num;
  unsigned col_num;
};

} // namespace shaka

#endif //SHAKA_SCHEME_SYNTAXOBJECT_HPP

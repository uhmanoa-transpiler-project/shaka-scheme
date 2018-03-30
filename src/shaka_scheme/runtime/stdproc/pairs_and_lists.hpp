//
// Created by Kayla Kwock on 3/18/18.
//

#ifndef SHAKA_SCHEME_STDPROC_PAIRS_AND_LISTS_HPP
#define SHAKA_SCHEME_STDPROC_PAIRS_AND_LISTS_HPP

#include "shaka_scheme/system/base/Number.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/exceptions/TypeException.hpp"
#include "shaka_scheme/system/core/lists.hpp"

#include <cmath>
#include <functional>
#include <typeinfo>
#include <deque>

namespace shaka {
namespace stdproc {

using Args = std::deque<NodePtr>;


using Callable = std::function<std::deque<NodePtr>(std::deque<NodePtr>)>;
namespace impl {

//(pair? ...)
Args is_pair(Args args);

//(cons ...)
Args cons(Args args);

//(car ...)
Args car(Args args);

//(cdr ...)
Args cdr(Args args);

//(set-car! ...)
Args set_car(Args args);

//(set-cdr! ...)
Args set_cdr(Args args);

//(null? ...)
Args is_null(Args args);

//(list? ...)
Args is_list(Args args);

//(make-list ...)
Args make_list(Args args);

//(list ...)
Args list(Args args);

//(length ...)
Args length(Args args);

//(append ...)
Args append(Args args);

//(reverse ...)
Args reverse(Args args);

//(list-tail ...)
Args list_tail(Args args);

//(list-ref ...)
Args list_ref(Args args);

//(list-set! ...)
Args list_set(Args args);

//(memq ...)
Args memq(Args args);

//(memv ...)
Args memv(Args args);

//(member ...)
Args member(Args args);

//(assq ...)
Args assq(Args args);

//(assv ...)
Args assv(Args args);

//(assoc ...)
Args assoc(Args args);

//(list-copy ...)
Args list_copy(Args args);

} // namespace impl

Callable is_pair = impl::is_pair;
Callable cons = impl::cons;
Callable car = impl::car;
Callable cdr = impl::cdr;
Callable set_car = impl::set_car;
Callable set_cdr = impl::set_cdr;
Callable is_null = impl::is_null;
Callable is_list = impl::is_list;
Callable make_list = impl::make_list;
Callable list = impl::list;
Callable length = impl::length;
Callable append = impl::append;
Callable reverse = impl::reverse;
Callable list_tail = impl::list_tail;
Callable list_ref = impl::list_ref;
Callable list_set = impl::list_set;
//Callable memq = impl::memq;
//Callable memv = impl::memv;
//Callable member = impl::member;
//Callable assq = impl::assq;
//Callable assv = impl::assv;
//Callable assoc = impl::assoc;
Callable list_copy = impl::list_copy;

} // namespace stdproc
} // namespace shaka



#endif //SHAKA_SCHEME_STDPROCS_PAIRS_AND_LISTS_HPP

#include <iostream>
#include <string>
#include <vector>

#include <boost/variant.hpp>

class times2_visitor : public boost::static_visitor<> {
public:

    void operator() (int& i) const {
        i *= 2;
    }

    void operator() (std::string& str) const {
        str += str;
    }
};

class times2_generic :
    public boost::static_visitor<> {
public:
    template <typename T>
    void operator() (T& operand) const {
        operand += operand;
    }
    
};

struct add;
struct sub;
template <typename OpTag> struct binary_op;

using expression = boost::variant<
    int,
    boost::recursive_wrapper< binary_op<add> >,
    boost::recursive_wrapper< binary_op<sub> >
>;



us

template <typename OpTag>
struct binary_op {
    expression left;
    expression right;

    binary_op(const expression& lhs, const expression& rhs) 
        : left(lhs), right(rhs) {}
};

class calculator : public boost::static_visitor<int> {
public:
    int operator()(int value) const {
        return value;
    }

    int operator()(const binary_op<add>& binary) const {
        return boost::apply_visitor(calculator(), binary.left)
               + boost::apply_visitor(calculator(), binary.right);
    }

    int operator()(const binary_op<sub>& binary) const {
        return boost::apply_visitor(calculator(), binary.left)
               - boost::apply_visitor(calculator(), binary.right);
    }
};

void f() {
    // result = ((7-3)+8) = 12
    expression result( 
        binary_op<add>(
            binary_op<sub>(7,3),
            8
        )
    );

    assert(boost::apply_visitor(calculator(), result) == 12);
}

using int_tree_t = boost::make_recursive_variant<
    int,
    std::vector< boost::recursive_variant_ >
>::type;

void g() {
    std::vector< int_tree_t > subresult;
    subresult.push_back(3);
    subresult.push_back(5);

    std::vector< int_tree_t > result;
    result.push_back(1);
    result.push_back(subresult);
    result.push_back(7);

    int_tree_t var(result);
}

class are_strict_equals :
    public boost::static_visitor<bool> {
public:
    template <typename T, typename U>
    bool operator()(const T&, const U&) const {
        return false;
    }

    template <typename T>
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs == rhs;
    }
};

void h() {
    boost::variant<int, std::string> v1("hello");
    
    boost::variant<double, std::string> v2("hello");
    assert(boost::apply_visitor(are_strict_equals(), v1, v2));

    boost::variant<int, const char*> v3("hello");
    assert(!boost::apply_visitor(are_strict_equals(), v1 , v3));
}


void f1() {
    using my_variant = boost::variant<double, std::string>; 

    std::vector<my_variant> seq1;
    seq1.push_back("pi is close to ");
    seq1.push_back(3.14);

    std::list<my_variant> seq2;
    seq2.push_back("pi is close to ");
    seq2.push_back(3.14);

    are_strict_equals visitor;
    assert(
        std::equal(
            v1.begin(),
            v1.end(),
            v2.begin(),
            boost::apply_visitor(visitor)
        )
    )

}


int main() {
    boost::variant<int, std::string> v;
    v = "hello";
    
    std::cout << v << std::endl;

    std::string& str = boost::get<std::string>(v);
    str += " world! ";

    std::cout << v << std::endl;

    boost::apply_visitor(times2_visitor(), v);

    std::cout << v << std::endl;

    boost::apply_visitor(times2_generic(), v);

    std::cout << v << std::endl;

    f();

    g();
}
#include <iostream>

struct A {
    A(int i, int j) {
        i = i;
        j = j;
    }

    int i;
    int j;
};

struct B {
    B(int i, int j, int k) {
        i = i;
        j = j;
        k = k;
    }

    int i;
    int j;
    int k;
};

struct Delegator {
    enum class Type : int {
        CLASS_A,
        CLASS_B
    };

    union {
        A a;
        B b;
    };

    template <typename... Args>
    Delegator(Delegator::Type type, Args... args) {
        type_ = type;

        if (type_ == Delegator::Type::CLASS_A) {
            construct<A, Args...>(a, args);
        } else if (type_ == Delegator::Type::CLASS_B) {
            construct<B, Args...>(b, args...);
        } else {
            throw std::invalid_argument("Delegator constructor: "
            "forwarded arguments does not match any of its member type constructors!");
        }
    }

    template <typename T, typename Arg>
    void construct(void* mem, void* arg) {
        new (mem) T(static_cast<Arg*>(arg));
    }

private:
    Delegator::Type     type_;
};

int main() {
    Delegator delegator(Delegator::Type::CLASS_A, 1, 2);
}
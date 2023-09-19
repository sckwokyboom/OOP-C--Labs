#include "student.h"

using namespace linkedhs;

student::student(const unsigned int age, std::string name)
        :age_(age), name_(std::move(name)) {
//    std::cout << "student ctor" << std::endl;
}

student::student(const element &other)
        :age_(other.age_), name_(other.name_) {
//    std::cout << "student copy ctor" << std::endl;
}

bool student::operator==(const element &other) const {
    return (name_ == other.name_ && age_ == other.age_);
}

bool student::operator!=(const element &other) const {
    return !(*this == other);
}

long long student_hasher::operator()(const element &el) const {
    long long h = 0;
    int p = 31;
    for (char c : el.name_) {
        h += (c - 'a' + 1) * p;
        p *= 31;
    }
    h = p * h + el.age_;
    return std::abs(h);
}

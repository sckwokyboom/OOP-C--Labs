#ifndef LINKED_HASH_SET_HPP_STUDENT_H
#define LINKED_HASH_SET_HPP_STUDENT_H
#include <iostream>

namespace linkedhs {
    struct student {
        student(unsigned int age, std::string name);

        student(const student &other);

        bool operator==(const student &other) const;

        bool operator!=(const student &other) const;

        unsigned age_;

        std::string name_;

    };

    typedef student element;

    class student_hasher {
    public:
        long long operator()(const element &el) const;
        friend student;
    };
}


#endif //LINKED_HASH_SET_HPP_STUDENT_H

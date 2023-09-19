#include <gtest/gtest.h>
#include "linked_hash_set.hpp"
#include "example_element_implementation/student.h"

student get_student_by_inx(size_t inx) {
    return {(unsigned int) inx, "NAME " + std::to_string(inx)};
}

TEST(AllMethodsTest, Compile) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (int i = 0; i < 50; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    bool summary_exp = false;
    hash_set.remove(get_student_by_inx(5));
    for (const student &el : hash_set) {
        summary_exp |= el == get_student_by_inx(10);
        summary_exp |= hash_set.contains(get_student_by_inx(7));
    }
    auto it = hash_set.find(get_student_by_inx(4));
    if (*it != get_student_by_inx(5)) {
        Linked_hash_set<student, student_hasher> hash_set2(hash_set);
        Linked_hash_set<student, student_hasher> hash_set3 = hash_set2;
        hash_set.swap(hash_set3);
        summary_exp &= hash_set == hash_set2;
        hash_set2.clear();
        hash_set3.clear();
    }
    summary_exp |= hash_set.empty();
    if (summary_exp) {
        hash_set.clear();
    }
}

TEST(InsertMethodTest, InsertIntoEmpty) {
    Linked_hash_set<student, student_hasher> hash_set;
    hash_set.insert(get_student_by_inx(5));
    ASSERT_EQ(hash_set.size(), 1);
}

TEST(InsertMethodTest, InsertWhenPresent) {
    Linked_hash_set<student, student_hasher> hash_set;
    hash_set.insert(get_student_by_inx(5));
    hash_set.insert(get_student_by_inx(5));
    ASSERT_EQ(hash_set.size(), 1);
}

TEST(InsertMethodTest, Rehash) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    for (int i = 0; i < 99; ++i) {
        hash_set.remove(get_student_by_inx(i));
    }
    ASSERT_EQ(hash_set.size(), 1);
    ASSERT_EQ(hash_set.contains(get_student_by_inx(99)), true);
}

TEST(InsertMethodTest, RemoveSame) {
    Linked_hash_set<student, student_hasher> hash_set;
    hash_set.insert(get_student_by_inx(50));
    hash_set.remove(get_student_by_inx(50));
    ASSERT_EQ(hash_set.remove(get_student_by_inx(50)), false);
}


TEST(InsertMethodTest, InsertSameElements) {
    Linked_hash_set<student, student_hasher> hash_set;
    student student1 = get_student_by_inx(50);
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(student1);
    }
    ASSERT_FALSE(hash_set.insert(student1));
}

TEST(InsertMethodTest, Size) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    ASSERT_EQ(hash_set.size(), 100);
}

TEST(InsertMethodTest, InsertSameElementsSize) {
    Linked_hash_set<student, student_hasher> hash_set;
    student student1((unsigned int) 50, "NAME");
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(student1);
    }
    ASSERT_EQ(hash_set.size(), 1);
}

TEST(Constructors_test, Copy_constructor) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    Linked_hash_set<student, student_hasher> hash_set2(hash_set);
    ASSERT_EQ(hash_set.size(), hash_set2.size());
}

TEST(Contains_method_test, Contains_elements) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    for (unsigned int i = 0; i < 100; ++i) {
        ASSERT_EQ(hash_set.contains(get_student_by_inx(i)), true);
    }
}

TEST(Contains_method_test, Contains_no_elements) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.remove(get_student_by_inx(i));
    }
    ASSERT_EQ(hash_set.contains(get_student_by_inx(99)), false);
}

TEST(Empty_method_test, Empty) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.remove(get_student_by_inx(i));
    }
    ASSERT_EQ(hash_set.empty(), true);
    ASSERT_EQ(hash_set.begin(), hash_set.end());
}

TEST(Comparison_operator_test, Empty_comparison) {
    Linked_hash_set<student, student_hasher> hash_set;
    Linked_hash_set<student, student_hasher> hash_set2;
    ASSERT_EQ(hash_set == hash_set2, true);
    ASSERT_EQ(hash_set != hash_set2, false);
}

TEST(Comparison_operator_test, Large_comparison) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i <= 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    Linked_hash_set<student, student_hasher> hash_set2;
    for (int i = 100; i >= 0; i--) {
        hash_set2.insert(get_student_by_inx((unsigned int) i));
    }
    ASSERT_TRUE(hash_set == hash_set2);
    ASSERT_FALSE(hash_set != hash_set2);
    hash_set.remove(get_student_by_inx(99));
    ASSERT_FALSE(hash_set == hash_set2);
    ASSERT_TRUE(hash_set != hash_set2);
}

TEST(Clear_method_test, Clear) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    hash_set.clear();
    ASSERT_EQ(hash_set.size(), 0);
    ASSERT_FALSE(hash_set.contains(get_student_by_inx(20)));
}

TEST(Assignment_operator_test, Empty_assignment) {
    Linked_hash_set<student, student_hasher> hash_set;
    Linked_hash_set<student, student_hasher> hash_set2;
    hash_set = hash_set2;
    ASSERT_TRUE(hash_set == hash_set2);
}

TEST(Assignment_operator_test, Large_assignment) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    Linked_hash_set<student, student_hasher> hash_set2;
    hash_set2 = hash_set;
    ASSERT_TRUE(hash_set == hash_set2);
}

TEST(Assignment_operator_test, Self_assignment) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    Linked_hash_set<student, student_hasher> hash_set_copy(hash_set);
    hash_set = hash_set;
    ASSERT_TRUE(hash_set == hash_set_copy);
}

TEST(SwapMethodTest, SwapWithEmpty) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 101; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    Linked_hash_set<student, student_hasher> hash_set2;
    hash_set.swap(hash_set2);
    ASSERT_EQ(hash_set.size(), 0);
    ASSERT_EQ(hash_set2.size(), 101);
    ASSERT_FALSE(hash_set.contains(get_student_by_inx(100)));
    ASSERT_TRUE(hash_set2.contains(get_student_by_inx(100)));
}

TEST(IteratorTest, BeginMatchesEndInEmptyCase) {
    Linked_hash_set<student, student_hasher> hash_set;
    ASSERT_EQ(hash_set.begin(), hash_set.end());
}

TEST(IteratorTest, LargeIteration) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (int i = 1000; i >= 0; i--) {
        hash_set.insert(get_student_by_inx((unsigned int) i));
    }
    unsigned int index = 1000;
    for (const auto &el : hash_set) {
        ASSERT_EQ(el, get_student_by_inx(index));
        index--;
    }
}

TEST(IteratorTest, FindEmpty) {
    Linked_hash_set<student, student_hasher> hash_set;
    ASSERT_EQ(hash_set.find(get_student_by_inx(50)), hash_set.begin());
}

TEST(IteratorTest, FindNonExistentElement) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (int i = 100; i >= 0; i--) {
        hash_set.insert(get_student_by_inx((unsigned int) i));
    }
    ASSERT_EQ(hash_set.find(get_student_by_inx(101)), hash_set.end());
}
TEST(IteratorTest, FindLarge) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (int i = 100; i >= 0; i--) {
        hash_set.insert(get_student_by_inx((unsigned int) i));
    }
    unsigned int i = 100;
    for (auto it = hash_set.begin(); it != hash_set.end(); it++) {
        if (*it == get_student_by_inx(i)) {
            ASSERT_EQ(hash_set.find(get_student_by_inx(i)), it);
            i--;
        }
    }
}


TEST(IteratorTest, FindRemovedElement) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (int i = 100; i >= 0; i--) {
        hash_set.insert(get_student_by_inx((unsigned int) i));
    }
    hash_set.remove(get_student_by_inx(59));
    ASSERT_TRUE(hash_set.find(get_student_by_inx(59)) == hash_set.end());
}

TEST(ConstructorTest, CopyConstructorDeepCopy) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    Linked_hash_set<student, student_hasher> hash_set_copy(hash_set);
    hash_set_copy.remove(get_student_by_inx(59));
    ASSERT_FALSE(hash_set.find(get_student_by_inx(59)) == hash_set.end());
    ASSERT_TRUE(hash_set_copy.find(get_student_by_inx(59)) == hash_set_copy.end());
}

TEST(AssignmentOperatorTest, AssignmentDeepCopy) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    Linked_hash_set<student, student_hasher> hash_set_copy;
    for (unsigned int i = 100; i < 200; ++i) {
        hash_set_copy.insert(get_student_by_inx(i));
    }
    hash_set_copy = hash_set;
    hash_set_copy.remove(get_student_by_inx(59));
    ASSERT_NE(hash_set.find(get_student_by_inx(59)), hash_set.end());
    ASSERT_EQ(hash_set_copy.find(get_student_by_inx(59)), hash_set_copy.end());
    ASSERT_EQ(hash_set_copy.find(get_student_by_inx(150)), hash_set_copy.end());
    ASSERT_EQ(hash_set.find(get_student_by_inx(150)), hash_set.end());
}


TEST(IteratorTest, CheckOrderAfterRemove) {
    Linked_hash_set<student, student_hasher> hash_set;
    for (unsigned int i = 0; i < 100; ++i) {
        hash_set.insert(get_student_by_inx(i));
    }
    Linked_hash_set<student, student_hasher> hash_set_copy(hash_set);
    hash_set_copy.remove(get_student_by_inx(59));
    auto copy_it = hash_set_copy.begin();
    for (const auto &el : hash_set) {
        if (el != get_student_by_inx(59)) {
            ASSERT_EQ(el, *copy_it);
            copy_it++;
        }
    }
}

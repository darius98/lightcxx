#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_trivially_destructible_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_trivially_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_trivially_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_trivially_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_trivially_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_destructible, EVERY_CV, int[10], int[10][10]);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_destructible, EVERY_CV, int[], int[][10],
                               int[][10][10]);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_trivially_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, is_trivially_destructible);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, is_trivially_destructible);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_trivially_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_trivially_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_trivially_destructible, EVERY_CV);
// TEST_UNARY_TRAIT_AGAINST_UNION(true, is_trivially_destructible, EVERY_CV); // Special tests
// TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_trivially_destructible, EVERY_CV); // Special tests
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_trivially_destructible);

class ClassWithDeletedDtor {
  public:
    ~ClassWithDeletedDtor() = delete;
};

class ClassWithDeletedDtorMember {
  public:
    ClassWithDeletedDtor d;
};

class ClassWithProtectedDtor {
  protected:
    ~ClassWithProtectedDtor() {}
};

class ClassWithPrivateDtor {
  private:
    ~ClassWithPrivateDtor() {}
};

class ClassWithPrivateDtorBase : public ClassWithPrivateDtor {};

class IncompleteClass;

union UnionWithDeletedDtor {
    [[maybe_unused]] int x;
    [[maybe_unused]] char c[4];

    ~UnionWithDeletedDtor() = delete;
};

union UnionWithProtectedDtor {
    [[maybe_unused]] int x;
    [[maybe_unused]] char c[4];

  protected:
    ~UnionWithProtectedDtor() {}
};

union UnionWithPrivateDtor {
    [[maybe_unused]] int x;
    [[maybe_unused]] char c[4];

  protected:
    ~UnionWithPrivateDtor() {}
};

class ClassWithDefinedDtor {
  public:
    [[maybe_unused]] int x;
    [[maybe_unused]] int y;

    ~ClassWithDefinedDtor() {}
};

union UnionWithDefinedDtor {
    [[maybe_unused]] int x;
    [[maybe_unused]] char c[4];

    ~UnionWithDefinedDtor() {}
};

class ClassWithProtectedDtorBase : public ClassWithProtectedDtor {};

class ClassWithProtectedDtorBaseAndDefinedDtor : public ClassWithProtectedDtor {
  public:
    ~ClassWithProtectedDtorBaseAndDefinedDtor() {}
};

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_destructible, EVERY_CV, ClassWithDeletedDtor,
                               ClassWithDeletedDtorMember, ClassWithProtectedDtor,
                               ClassWithPrivateDtor, ClassWithPrivateDtorBase, IncompleteClass,
                               UnionWithDeletedDtor, UnionWithProtectedDtor, UnionWithPrivateDtor,
                               ClassWithDefinedDtor, UnionWithDefinedDtor,
                               ClassWithProtectedDtorBase,
                               ClassWithProtectedDtorBaseAndDefinedDtor);

class ClassWithDefaultedDtor {
  public:
    [[maybe_unused]] int x;
    [[maybe_unused]] int y;

    ClassWithDefaultedDtor() = default;
};

union UnionWithDefaultedDtor {
    [[maybe_unused]] int x;
    [[maybe_unused]] char c[4];

    ~UnionWithDefaultedDtor() = default;
};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_destructible, EVERY_CV, ClassWithDefaultedDtor,
                               UnionWithDefaultedDtor);
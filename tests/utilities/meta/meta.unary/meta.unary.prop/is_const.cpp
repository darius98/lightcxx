#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_const_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_const, NO_CV);
TEST_UNARY_TRAIT_AGAINST_VOID(true, is_const, CONST);
TEST_UNARY_TRAIT_AGAINST_VOID(false, is_const, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_VOID(true, is_const, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_const, NO_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_const, CONST);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_const, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_const, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_const, NO_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_const, CONST);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_const, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_const, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_const, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_const, CONST);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_const, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_const, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_const, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, is_const, CONST);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_const, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, is_const, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_const, NO_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_const, CONST);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_const, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_const, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_const);

TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_const);

TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_const, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_const, CONST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_const, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_const, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_const, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_const, CONST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_const, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_const, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_const, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_const, CONST);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_const, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_const, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_UNION(false, is_const, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, is_const, CONST);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_const, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_UNION(true, is_const, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_const, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_const, CONST);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_const, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_const, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_const);
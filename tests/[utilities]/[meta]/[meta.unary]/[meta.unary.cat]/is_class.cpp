// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."

#include <type_traits>

#include "meta/test_unary_trait.h"

TEST_UNARY_TRAIT_AGAINST_VOID(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_UNION(false, std::is_class);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, std::is_class);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, std::is_class);

int main() {
    return 0;
}
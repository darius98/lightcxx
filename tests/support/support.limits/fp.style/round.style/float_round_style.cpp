#include <limits>

#include "testing.h"

TEST() {
    constexpr auto indeterminate_1 = ::std::float_round_style::round_indeterminate;
    constexpr auto indeterminate_2 = ::std::round_indeterminate;
    expect_type_and_value(indeterminate_1, const ::std::float_round_style&, -1);
    expect_type_and_value(indeterminate_2, const ::std::float_round_style&, -1);

    constexpr auto to_zero_1 = ::std::float_round_style::round_toward_zero;
    constexpr auto to_zero_2 = ::std::round_toward_zero;
    expect_type_and_value(to_zero_1, const ::std::float_round_style&, 0);
    expect_type_and_value(to_zero_2, const ::std::float_round_style&, 0);

    constexpr auto to_nearest_1 = ::std::float_round_style::round_to_nearest;
    constexpr auto to_nearest_2 = ::std::round_to_nearest;
    expect_type_and_value(to_nearest_1, const ::std::float_round_style&, 1);
    expect_type_and_value(to_nearest_2, const ::std::float_round_style&, 1);

    constexpr auto to_infinity_1 = ::std::float_round_style::round_toward_infinity;
    constexpr auto to_infinity_2 = ::std::round_toward_infinity;
    expect_type_and_value(to_infinity_1, const ::std::float_round_style&, 2);
    expect_type_and_value(to_infinity_2, const ::std::float_round_style&, 2);

    constexpr auto to_neg_infinity_1 = ::std::float_round_style::round_toward_neg_infinity;
    constexpr auto to_neg_infinity_2 = ::std::round_toward_neg_infinity;
    expect_type_and_value(to_neg_infinity_1, const ::std::float_round_style&, 3);
    expect_type_and_value(to_neg_infinity_2, const ::std::float_round_style&, 3);
}

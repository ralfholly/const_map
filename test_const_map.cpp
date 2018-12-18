#include "gmock/gmock.h"

#include "const_map.h"

#include <iostream>

namespace testing {
namespace test_const_map {

using namespace std;


TEST(TestConstMap, HelloConstMap) {
    static const const_map<int, const char*>::value_type COLORS_AS_STRINGS[] = {
        { 111, "red"   },
        { 222, "green" },
        { 333, "blue"  },
    };

    const_map<int, const char*> color_strings(COLORS_AS_STRINGS);

    // Simple lookup.
    EXPECT_EQ("green", color_strings[222]);

    // No match found -> undefined behavior!
    // const char* str = color_strings[12345]);

    // Lookup via 'find'.
    auto iter = color_strings.find(333);
    EXPECT_TRUE(iter != color_strings.end());
    EXPECT_EQ("blue", iter->second);

    // Lookup via 'find' doesn't find a match.
    iter = color_strings.find(12345);
    EXPECT_TRUE(iter == color_strings.end());
}


TEST(TestConstMap, WithSentinel) {
    static const const_map<int, const char*>::value_type COLORS_AS_STRINGS_SENT[] = {
        { 111, "red"   },
        { 222, "green" },
        { 333, "blue"  },
        { 999, nullptr },    // Sentinel.
    };

    const_map<int, const char*> color_strings(&COLORS_AS_STRINGS_SENT[0], &COLORS_AS_STRINGS_SENT[3]);

    // No match found.
    EXPECT_EQ(nullptr, color_strings[12345]);
    EXPECT_EQ(color_strings.end()->second, color_strings[12345]);
    EXPECT_EQ(nullptr, color_strings[999]);

    // Lookup via 'find'.
    auto iter = color_strings.find(12345);
    EXPECT_TRUE(iter == color_strings.end());
    iter = color_strings.find(999);
    EXPECT_TRUE(iter == color_strings.end());
}


} // namespace test_const_map
} // namespace testing


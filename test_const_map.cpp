#include "gmock/gmock.h"

#include "const_map.h"

#include <iostream>

namespace testing {
namespace test_const_map {

using namespace std;


const const_map<int, const char*>::value_type colors_as_strings[] = {
    { 111, "red" },
    { 222, "green" },
    { 333, "blue" },
    { int(), "unmapped" }
};


TEST(TestConstMap, TypicalUseCases) {
#if 0
    const const_map<int, const char*>::value_type mappings[] = {
        make_pair(111, "red"),
        make_pair(222, "green"),
        make_pair(333, "blue"),
        {}
    };
#endif

    const const_map<int, const char*> my_map(colors_as_strings);

    // Simple lookup.
    EXPECT_EQ("green", my_map[222]);

    // Lookup via 'find'.
    const_map<int, const char*>::const_iterator iter = my_map.find(333);
    EXPECT_TRUE(iter != my_map.end());
    EXPECT_EQ("blue", iter->second);

    // No match found.
    EXPECT_EQ("unmapped", my_map[12345]);
    EXPECT_EQ(my_map.end()->second, my_map[12345]);

    // Lookup via 'find' doesn't find a match.
    iter = my_map.find(12345);
    EXPECT_TRUE(iter == my_map.end());
}


} // namespace test_const_map
} // namespace testing


#include "gmock/gmock.h"

#include "const_map.h"

#include <iostream>

namespace testing {
namespace test_const_map {

using namespace std;

#define ASIZE(a) (sizeof(a) / sizeof((a)[0]))


TEST(TestConstMap, Setup) {
    EXPECT_EQ(3, 1 + 2);
}


TEST(TestConstMap, TypicalUseCases) {
    const const_map<int, const char*>::value_type mappings[] = {
        make_pair(0, "red"),
        make_pair(1, "green"),
        make_pair(2, "blue"),
    };

    //const_map<int, const char*> my_map(mappings, ASIZE(mappings), "not found");
    const_map<int, const char*> my_map(mappings, "not found");

    // Simple lookup.
    EXPECT_EQ("green", my_map[1]);

    // Lookup via 'find'.
    const_map<int, const char*>::iterator iter = my_map.find(2);
    EXPECT_TRUE(iter != my_map.end());
    EXPECT_EQ("blue", iter->second);

    // No match found.
    EXPECT_EQ(my_map.unmapped_value(), my_map[12345]);

    // Lookup via 'find' doesn't find a match.
    iter = my_map.find(12345);
    EXPECT_TRUE(iter == my_map.end());
}


} // namespace test_const_map
} // namespace testing


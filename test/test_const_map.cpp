#include "gmock/gmock.h"

#include "const_map.h"

#include <iostream>

namespace testing {
namespace test_const_map {

using namespace std;


TEST(TestConstMap, HelloConstMap) {
    static const const_map<int, const char*>::value_type COLOR_STR[] = {
        { 111, "red"   },
        { 222, "green" },
        { 333, "blue"  },
    };

    const_map<int, const char*> color_strings(COLOR_STR);

    // Simple lookup.
    EXPECT_EQ("green", color_strings[222]);

    // When op[] is used and there is no match, we get undefined behavior!
    // See 'WithSentinel' below for how sentinels can make such cases robust.
    //
    // This yields undefined behavior, just like array out-of-bounds access:
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
    #define ASIZE(array) (sizeof(array) / sizeof(array[0]))

    static const const_map<int, const char*>::value_type COLOR_STR[] = {
        { 111, "red"   },  // <-- begin()
        { 222, "green" },
        { 333, "blue"  },  // last element of mapping table
        // Sentinel
        {  -1, nullptr },  // <-- end()
    };

    const_map<int, const char*> color_strings(COLOR_STR,
        ASIZE(COLOR_STR) - 1 /* excl. sentinel */);

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


TEST(TestConstMap, SingleElement) {
    static const const_map<double, int>::value_type DOUBLE_TO_INT[] = {
        { 3.1416, 3 },
    };

    const_map<double, int> mapping(DOUBLE_TO_INT);
    EXPECT_EQ(3, mapping[3.1416]);

    auto iter = mapping.find(3.1416);
    EXPECT_EQ(3, iter->second);

    iter = mapping.find(42.1234);
    EXPECT_EQ(mapping.cend(), iter);

    static const const_map<double, int>::value_type DOUBLE_TO_INT2[] = {
        { 3.1416, 3 },
        {    0.0, 0 },  // Sentinel
    };

    const_map<double, int> mapping2(DOUBLE_TO_INT2, 1);
    EXPECT_EQ(3, mapping[3.1416]);

    iter = mapping.find(3.1416);
    EXPECT_EQ(3, iter->second);

    iter = mapping.find(42.1234);
    EXPECT_EQ(mapping.cend(), iter);

    EXPECT_EQ(mapping.cend()->second, mapping[123]);
}


TEST(TestConstMap, AssignmentAndEquality) {
    static const const_map<int, const char*>::value_type COLOR_STR[] = {
        { 111, "red"   },
        { 222, "green" },
        { 333, "blue"  },
    };

    static const const_map<int, const char*>::value_type COLOR_STR2[] = {
        { 444, "yellow"  },
        { 555, "black"  },
        { 666, "brown"  },
    };

    const_map<int, const char*> map1(COLOR_STR);
    const_map<int, const char*> map2(COLOR_STR2);
    EXPECT_NE(map1, map2);

    const_map<int, const char*> map3(map1);
    EXPECT_EQ(map3, map1);
    EXPECT_NE(map3, map2);

    map3 = map2;
    EXPECT_NE(map3, map1);
    EXPECT_EQ(map3, map2);

    EXPECT_EQ("black", map3[555]);
    EXPECT_EQ("black", map2[555]);
}


TEST(TestConstMap, DefaultCtorAndDelaySettingOfMapping) {
    const_map<int, const char*> map;

    EXPECT_EQ(0U, map.size());
    EXPECT_EQ(map.begin(), map.end());

    auto iter = map.find(555);
    EXPECT_EQ(map.end(), iter);

    static const const_map<int, const char*>::value_type COLOR_STR[] = {
        { 444, "yellow"  },
        { 555, "black"  },
        { 666, "brown"  },
    };

   map.set_mapping(COLOR_STR);
   EXPECT_EQ("black", map[555]);

   static const const_map<int, const char*>::value_type COLOR_STR2[] = {
       { 111, "red"   },
       { 222, "green" },
       { 333, "blue"  },
   };

   map.set_mapping(COLOR_STR2, ASIZE(COLOR_STR2));
   EXPECT_EQ("blue", map[333]);
}


} // namespace test_const_map
} // namespace testing

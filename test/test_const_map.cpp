#include "const_map.h"
#include "external_mapping.h"

#include "gmock/gmock.h"
#include <iostream>

namespace testing {
namespace test_const_map {

using namespace std;
using namespace approxion;


TEST(TestConstMap, HelloConstMap) {
    static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
        { 111, "red"   },
        { 222, "green" },
        { 333, "blue"  },
    };

    const_map<int, const char*> color_names(COLOR_NAMES);

    // Simple lookup.
    EXPECT_EQ("green", color_names[222]);

    // When op[] is used and there is no match, we get undefined behavior!
    // See 'WithSentinel' below for how sentinels can make such cases robust.
    //
    // This yields undefined behavior, just like array out-of-bounds access:
    // const char* str = color_names[12345]);

    // Lookup via 'find'.
    auto iter = color_names.find(333);
    EXPECT_TRUE(iter != color_names.end());
    EXPECT_EQ("blue", iter->second);

    // Lookup via 'find' doesn't find a match.
    iter = color_names.find(12345);
    EXPECT_TRUE(iter == color_names.end());
}


TEST(TestConstMap, WithSentinel) {

    static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
        { 111, "red"   },  // <-- begin()
        { 222, "green" },
        { 333, "blue"  },  // last element of mapping table
        // Sentinel
        {  -1, nullptr },  // <-- end()
    };

    const_map<int, const char*> color_names(COLOR_NAMES, const_map_sentinel::yes);

    // No match found.
    EXPECT_EQ(nullptr, color_names[12345]);
    EXPECT_EQ(color_names.end()->second, color_names[12345]);
    EXPECT_EQ(nullptr, color_names[999]);

    // Lookup via 'find'.
    auto iter = color_names.find(12345);
    EXPECT_TRUE(iter == color_names.end());
    iter = color_names.find(999);
    EXPECT_TRUE(iter == color_names.end());
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
    static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
        { 111, "red"   },
        { 222, "green" },
        { 333, "blue"  },
    };

    static const const_map<int, const char*>::value_type COLOR_NAMES2[] = {
        { 444, "yellow"  },
        { 555, "black"  },
        { 666, "brown"  },
    };

    const_map<int, const char*> map1(COLOR_NAMES);
    const_map<int, const char*> map2(COLOR_NAMES2);
    EXPECT_NE(map1, map2);

    const_map<int, const char*> map3(map1);
    EXPECT_EQ(map3, map1);
    EXPECT_NE(map3, map2);

    map3 = map2;
    EXPECT_NE(map3, map1);
    EXPECT_EQ(map3, map2);

    EXPECT_EQ("black", map3[555]);
    EXPECT_EQ("black", map2[555]);

    // Put in vector.
    vector<const_map<int, const char*> > const_maps;
    const_maps.push_back(map1);
    const_maps.push_back(map2);
    const_maps.push_back(map3);
    EXPECT_EQ(3U, const_maps.size());
}


TEST(TestConstMap, DefaultCtorAndDelaySettingOfMapping) {
    const_map<int, const char*> map;

    EXPECT_EQ(0U, map.size());
    EXPECT_EQ(map.begin(), map.end());

    auto iter = map.find(555);
    EXPECT_EQ(map.end(), iter);

    static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
        { 444, "yellow"  },
        { 555, "black"  },
        { 666, "brown"  },
    };

   map.set_mapping(COLOR_NAMES);
   EXPECT_EQ("black", map[555]);

   static const const_map<int, const char*>::value_type COLOR_NAMES2[] = {
       { 111, "red"   },
       { 222, "green" },
       { 333, "blue"  },
   };

   map.set_mapping(COLOR_NAMES2);
   EXPECT_EQ("blue", map[333]);
}


TEST(TestConstMap, NonTrivialValueType) {
    class Color {
    public:
        Color() : code_(-1) {
        }
        Color(int code) : code_(code) {
        }
        int getCode() const {
            return code_;
        }
        bool operator==(const Color& rhs) const {
            return code_ == rhs.code_;
        }

    private:
        int code_;
    };

    static const const_map<int, Color>::value_type COLORS[] = {
        { 111, Color(1) },
        { 222, Color(2) },
        { 333, Color(3) },
        {   0, Color(0) },
    };

    const_map<int, Color> colors(COLORS, const_map_sentinel::yes);

    EXPECT_EQ(2, colors[222].getCode());
    EXPECT_EQ(3, colors[333].getCode());
    EXPECT_EQ(0, colors[12345].getCode());

    // Lookup requires default ctor Colors::Colors().
    const_map<int, Color> colors2(COLORS, const_map_sentinel::yes);

    // Equality comparison requires Colors::operator==().
    EXPECT_EQ(colors, colors2);
}


TEST(TestConstMap, Lookup) {
    static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
        { 111, "red"   },
        { 222, "green" },
        { 333, "blue"  },
    };

    // 'lookup' doesn't require an instance.
    auto iter = const_map<int, const char*>::lookup(COLOR_NAMES, 333);
    EXPECT_TRUE(iter != nullptr);
    EXPECT_EQ("blue", iter->second);

    // 'lookup' doesn't find a match.
    iter = const_map<int, const char*>::lookup(COLOR_NAMES, 12345);
    EXPECT_TRUE(iter == nullptr);
}


TEST(TestConstMap, EnumKey) {
    enum Colors {
        COLOR_RED,
        COLOR_GREEN,
        COLOR_BLUE,
        COLOR_PURPLE
    };

    static const const_map<enum Colors, const char*>::value_type COLOR_NAMES[] = {
        { COLOR_RED, "red"     },
        { COLOR_GREEN, "green" },
        { COLOR_BLUE, "blue"   },
    };
    const_map<enum Colors, const char*> color_names(COLOR_NAMES);
    EXPECT_EQ("blue", color_names[COLOR_BLUE]);
}


TEST(TestConstMap, ExternalMapping) {
    const_map<double, int> round_down(ROUND_DOWN);
    EXPECT_EQ(2, round_down[2.22]);
}


TEST(TestConstMap, RangeBasedConstructor) {
    static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
        { 111, "red"   },
        { 222, "green" },
        { 333, "blue"  },
    };

    const_map<int, const char*> color_names(&COLOR_NAMES[0], &COLOR_NAMES[3]);

    // Simple lookup.
    EXPECT_EQ("green", color_names[222]);

    // Lookup via 'find'.
    auto iter = color_names.find(333);
    EXPECT_TRUE(iter != color_names.end());
    EXPECT_EQ("blue", iter->second);

    // Lookup via 'find' doesn't find a match.
    iter = color_names.find(12345);
    EXPECT_TRUE(iter == color_names.end());
}


TEST(TestConstMap, RangeBasedConstructorWithSentinel) {
    static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
        { 111, "red"   },  // <-- begin()
        { 222, "green" },
        { 333, "blue"  },  // last element of mapping table
        // Sentinel
        {  -1, nullptr },  // <-- end()
    };

    const_map<int, const char*> color_names(&COLOR_NAMES[0], &COLOR_NAMES[3]);

    // Simple lookup.
    EXPECT_EQ("green", color_names[222]);

    // Lookup via 'find'.
    auto iter = color_names.find(333);
    EXPECT_TRUE(iter != color_names.end());
    EXPECT_EQ("blue", iter->second);

    // Lookup via 'find' doesn't find a match.
    iter = color_names.find(12345);
    EXPECT_TRUE(iter == color_names.end());
}


TEST(TestConstMap, WithGapsInKeyValues) {
    static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
        { 100, "red"   },
        { 200, "green" },
        { 300, "blue"  },
    };

    const_map<int, const char*> color_names(COLOR_NAMES);

    // Simple lookup.
    EXPECT_EQ("green", color_names[200]);

    // Lookup via 'find' doesn't find a match.
    auto iter = color_names.find(150);
    EXPECT_TRUE(iter == color_names.end());
}


} // namespace test_const_map
} // namespace testing

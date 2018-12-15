#include "gmock/gmock.h"

#include "const_map.h"

#include <iostream>

namespace testing {
namespace test_const_map {

using namespace std;


TEST(TestConstMap, Setup) {
    EXPECT_EQ(3, 1 + 2);
}

TEST(TestConstMap, Simple) {
#define ASIZE(a) (sizeof(a) / sizeof((a)[0]))
    const const_map<int, double>::value_type mappings[] = {
        { 1, 1.11, },
        { 2, 2.22, },
        { 3, 3.33, },
        { 4, 4.44, },
        { 5, 5.55, }, };

    const_map<int, double> mapper(mappings, ASIZE(mappings));

    const const_map<int, double>::Mapping* m = mapper.map_unchecked(4);
    EXPECT_EQ(4.44, m->to);

    // m = mapper.map_unchecked(1);
    // cout << "1 -> " << m->to << endl;
    // 
    // if ((m = mapper.map(5)) != 0) {
    //     cout << "5 -> " << m->to << endl;
    // }

    // if ((m = mapper.map(42)) != 0) {
    //     cout << "42 -> " << m->to << endl;
    // } else {
    //     cout << "42 is not mapped" << endl;
    // }
}



} // namespace test_const_map
} // namespace testing


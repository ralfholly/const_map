
#include <iostream>
#include "ValueMapper.h"

using namespace std;

#define ASIZE(a) (sizeof(a) / sizeof((a)[0]))

// const ValueMapper<int, double>::Mapping mappingX = { 1, 1.11 };
// const ValueMapper<int, double>::Mapping mappingY = { 0, 9.99 };



int main(int argc, char* argv[]) {
    
    const ValueMapper<int, double>::Mapping mappings1[] = {
        { 1, 1.11, },
        { 2, 2.22, },
        { 3, 3.33, },
        { 4, 4.44, },
        { 5, 5.55, },
    };

    ValueMapper<int, double> mapper1(mappings1, ASIZE(mappings1));

    const ValueMapper<int, double>::Mapping* m = mapper1.map_checked(4);
    cout << "4 -> " << m->to << endl;
    
    m = mapper1.map_checked(1);
    cout << "1 -> " << m->to << endl;
    
    m = mapper1.map_checked(6);
    cout << "6 -> " << m->to << endl;
    
    m = mapper1.map_checked(0);
    cout << "0 -> " << m->to << endl;
    
    
    return 0;
}


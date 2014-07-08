#ifndef VALUEMAPPER_H
#define VALUEMAPPER_H

#include <cstddef>
#include <algorithm>


template <typename FROM, typename TO>
class ValueMapper {
public:
    struct Mapping {
        FROM from;
        TO to;
        bool operator<(int from) const {
            return this->from < from;
        }
    };

    ValueMapper(const Mapping* mappings, size_t length) : mappings_(mappings), length_(length) {
    }


    const Mapping* map_unchecked(FROM from) {
        const Mapping* end = mappings_ + length_;
        const Mapping* it = std::lower_bound(mappings_, mappings_ + length_, from);
        return it;
    }

    const Mapping* map_checked(FROM from) {
        const Mapping* end = mappings_ + length_;
        const Mapping* it = std::lower_bound(mappings_, mappings_ + length_, from);
        if ((*it).from != from) {
            return 0;
        }
        return it;
    }

private:
    const Mapping* mappings_;
    size_t length_;
    
};

// template <typename FROM, typename TO>
// bool operator<(const typename ValueMapper<FROM, TO>::Mapping& lhs, const typename ValueMapper<FROM, TO>::Mapping& rhs) {
//     return lhs.from < rhs.from;
// }

#endif 

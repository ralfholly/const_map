#ifndef CONST_MAP_H
#define CONST_MAP_H

#include <algorithm>
#include <cassert>


template <typename FROM, typename TO>
class const_map {
public:
    struct Mapping {
        FROM from;
        TO to;
        bool operator<(const FROM& from) const {
            return (*this).from < from;
        }
    };
    typedef struct Mapping value_type;
    typedef FROM key_type;
    typedef TO mapped_type;
    typedef const value_type* iterator;

    inline const_map(const value_type* mappings, size_t length);

    //inline const TO& operator[](const FROM& from) const;

    inline const value_type* map_unchecked(const mapped_type& from) const;
    inline const value_type* map(const mapped_type& from) const;

    inline iterator begin() const;
    inline iterator end() const;
    inline size_t size() const;

private:
    iterator mappings_;
    size_t length_;
};


template<typename FROM, typename TO>
typename const_map<FROM, TO>::iterator const_map<FROM, TO>::begin() const {
    return &mappings_[0];
}


template<typename FROM, typename TO>
typename const_map<FROM, TO>::iterator const_map<FROM, TO>::end() const {
    return &mappings_[length_];
}


template<typename FROM, typename TO>
size_t const_map<FROM, TO>::size() const {
    return length_;
}


template <typename FROM, typename TO>
inline const_map<FROM, TO>::const_map(const Mapping* mappings, size_t length) : mappings_(mappings), length_(length) { 
    assert(mappings != 0);
#ifndef NDEBUG
    if (length >= 1) {
        iterator prev = begin();
        iterator it = prev + 1;
        for (; it != end(); ++it, ++prev) {
            // Ensure that mapping keys are sorted and unique.
            assert((*it).from > (*prev).from);
        }
    }
#endif
}


template <typename FROM, typename TO>
const typename const_map<FROM, TO>::Mapping* const_map<FROM, TO>::map_unchecked(const mapped_type& from) const {
    iterator it = std::lower_bound(mappings_, end(), from);
    return it;
}


template <typename FROM, typename TO>
const typename const_map<FROM, TO>::Mapping* const_map<FROM, TO>::map(const mapped_type& from) const {
    iterator it = std::lower_bound(mappings_, end(), from);
    if (it == end() || (*it).from != from) {
        return end();
    }
    return it;
}

#endif

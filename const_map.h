#ifndef CONST_MAP_H
#define CONST_MAP_H

#include <algorithm>
#include <cassert>


template <typename FROM, typename TO>
class const_map {
public:
    typedef std::pair<FROM, TO> value_type;
    typedef FROM key_type;
    typedef TO mapped_type;
    typedef const value_type* iterator;

    explicit inline const_map(const value_type* mappings, size_t length, const mapped_type& unmapped_value);

    inline iterator find(const key_type& from) const;
    inline const mapped_type& operator[](const key_type& from) const;

    inline iterator begin() const;
    inline iterator end() const;
    inline size_t size() const;
    inline const mapped_type& unmapped_value() const;

private:
    iterator mappings_;
    size_t length_;
    const mapped_type& unmapped_value_;
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


template<typename FROM, typename TO>
const typename const_map<FROM, TO>::mapped_type& const_map<FROM, TO>::unmapped_value() const {
    return unmapped_value_;
}


template <typename FROM, typename TO>
inline const_map<FROM, TO>::const_map(const value_type* mappings, size_t length, const mapped_type& unmapped_value)
    : mappings_(mappings)
    , length_(length)
    , unmapped_value_(unmapped_value) {
    assert(mappings != 0);
#ifndef NDEBUG
    if (length >= 1) {
        iterator prev = begin();
        iterator it = prev + 1;
        for (; it != end(); ++it, ++prev) {
            // Ensure that mapping keys are sorted and unique.
            assert((*it).first > (*prev).first);
        }
    }
#endif
}


template <typename FROM, typename TO>
const typename const_map<FROM, TO>::value_type* const_map<FROM, TO>::find(const key_type& from) const {
    iterator it = std::lower_bound(begin(), end(), std::make_pair(from, TO()));
    if (it == end() || (*it).first != from) {
        return end();
    }
    return it;
}


template <typename FROM, typename TO>
const typename const_map<FROM, TO>::mapped_type& const_map<FROM, TO>::operator[](const key_type& from) const {
    iterator it = find(from);
    if (it == end()) {
        return unmapped_value();
    }
    return (*it).second;
}


#endif

#ifndef CONST_MAP_H
#define CONST_MAP_H

#include <algorithm>
#include <cassert>

// const_map -- a read-only, std::map-like associative array.
//
// A const_map is built around a given array of key/value pairs, sorted by key
// in ascending order. Since element lookup is done via binary search, the time
// complexity is O(log(n)).
//
// Example:
//
//     #define ASIZE(array) (sizeof(array) / sizeof(array[0]))
//
//     static const const_map<int, const char*>::value_type COLOR_STR[] = {
//         { 111, "red"   },
//         { 222, "green" },
//         { 333, "blue"  },
//         { 999, nullptr },    // Sentinel.
//     };
//
//     const_map<int, const char*> color_strings(COLOR_STR,
//         ASIZE(COLOR_STR) - 1 /* excl. sentinel */);
//
//     // Simple lookup.
//     EXPECT_EQ("green", color_strings[222]);
//
//     // No match found.
//     EXPECT_EQ(nullptr, color_strings[12345]);
//     EXPECT_EQ(color_strings.end()->second, color_strings[12345]);
//     EXPECT_EQ(nullptr, color_strings[999]);
//
//     // Lookup via 'find'.
//     auto iter = color_strings.find(12345);
//     EXPECT_TRUE(iter == color_strings.end());
//     iter = color_strings.find(999);
//     EXPECT_TRUE(iter == color_strings.end());
//

template <typename From, typename To>
class const_map {
public:
    template<typename T1, typename T2>
    struct simple_pair {
        T1 first;
        T2 second;
        bool operator<(const simple_pair& rhs) const {
            return this->first < rhs.first;
        }
    };
    typedef simple_pair<From, To> value_type;
    typedef From key_type;
    typedef To mapped_type;
    typedef const value_type* const_iterator;

    template<size_t N>
    inline const_map(const value_type (&mappings)[N]);
    inline const_map(const value_type* begin, const value_type* end);
    inline const_map(const value_type* begin, size_t nelem);

    inline bool operator==(const const_map& rhs) const;

    inline const_iterator find(const key_type& from) const;
    inline const mapped_type& operator[](const key_type& from) const;

    inline const_iterator begin() const;
    inline const_iterator end() const;
    inline const_iterator cbegin() const;
    inline const_iterator cend() const;
    inline size_t size() const;

protected:
    inline void check_preconditions();

    const_iterator const begin_;
    const_iterator const end_;
};


template <typename From, typename To>
template<size_t N>
const_map<From, To>::const_map(const value_type (&mappings)[N])
    : begin_(&mappings[0])
    , end_(&mappings[N]) {
    check_preconditions();
}


template <typename From, typename To>
const_map<From, To>::const_map(const value_type* begin, const value_type* end)
    : begin_(begin)
    , end_(end)
{
    check_preconditions();
}


template <typename From, typename To>
const_map<From, To>::const_map(const value_type* begin, size_t nelem)
    : begin_(begin)
    , end_(begin + nelem)
{
    check_preconditions();
}


template <typename From, typename To>
bool const_map<From, To>::operator==(const const_map& rhs) const {
    return (this->begin_ == rhs.begin_) and (this->end_ == rhs.end_);
}


template <typename From, typename To>
typename const_map<From, To>::const_iterator const_map<From, To>::begin() const {
    return begin_;
}


template <typename From, typename To>
typename const_map<From, To>::const_iterator const_map<From, To>::end() const {
    return end_;
}


template <typename From, typename To>
typename const_map<From, To>::const_iterator const_map<From, To>::cbegin() const {
    return begin_;
}


template <typename From, typename To>
typename const_map<From, To>::const_iterator const_map<From, To>::cend() const {
    return end_;
}


template <typename From, typename To>
size_t const_map<From, To>::size() const {
    return end_ - begin_;
}


template <typename From, typename To>
const typename const_map<From, To>::value_type* const_map<From, To>::find(const key_type& from) const {
    const simple_pair<From, To> search_value = {
        from,
        To()
    };
    const_iterator it = std::lower_bound(begin(), end(), search_value);
    return it;
}


template <typename From, typename To>
const typename const_map<From, To>::mapped_type& const_map<From, To>::operator[](const key_type& from) const {
    const_iterator it = find(from);
    return (*it).second;
}


template <typename From, typename To>
void const_map<From, To>::check_preconditions() {
#ifndef NDEBUG
    assert(begin_ != 0);
    assert(end_ != 0);
    const_iterator prev = begin();
    const_iterator it = prev + 1;
    for (; it != end(); ++it, ++prev) {
        assert((*it).first > (*prev).first); // Keys must be in sorted, in ascending order.
    }
#endif
}


#endif

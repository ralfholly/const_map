#ifndef CONST_MAP_H
#define CONST_MAP_H

#include <algorithm>
#include <functional>
#include <cassert>

namespace approxion {

// const_map -- a read-only, std::map-like associative array.
//
// A const_map is built around a given array of key/value pairs, sorted by key
// in ascending order. Since element lookup is done via binary search, the time
// complexity is O(log(n)).
//
// Example:
//
//     static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
//         { 111, "red"   },
//         { 222, "green" },
//         { 333, "blue"  },
//     };
//
//     const_map<int, const char*> color_names(COLOR_NAMES);
//
//     // Simple lookup.
//     EXPECT_EQ("green", color_names[222]);
//
//     // Lookup via 'find'.
//     auto iter = color_names.find(333);
//     EXPECT_TRUE(iter != color_names.end());
//     EXPECT_EQ("blue", iter->second);
//
//     // Lookup via 'find' failed.
//     iter = color_names.find(12345);
//     EXPECT_TRUE(iter == color_names.end());
//
//     // When op[] is used and there is no match, we get undefined behavior!
//     // See 'Sentinels' below for how sentinels can make such cases robust.
//
//     // This yields undefined behavior, just like array out-of-bounds access:
//     const char* str = color_names[12345]);
//
// Sentinels:
//
//     static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
//         { 111, "red"   },  // <-- begin()
//         { 222, "green" },
//         { 333, "blue"  },  // last element of mapping table
//         // Sentinel
//         {  -1, nullptr },  // <-- end()
//     };
//
//     const_map<int, const char*> color_names(COLOR_NAMES, const_map_sentinel::yes);
//
//     // No match found.
//     EXPECT_EQ(nullptr, color_names[12345]);
//     EXPECT_EQ(color_names.end()->second, color_names[12345]);
//     EXPECT_EQ(nullptr, color_names[999]);
//
// Static Lookup:
//
//     const_map comes with an overhead of two pointers, one to the beginning and
//     another one to the end of the mapping table. If even this is too much,
//     you can use the 'lookup' class method, which doesn't require an object:
//
//     static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
//         { 111, "red"   },
//         { 222, "green" },
//         { 333, "blue"  },
//     };
//
//     // 'lookup' doesn't require an instance.
//     auto iter = const_map<int, const char*>::lookup(COLOR_NAMES, 333);
//     EXPECT_TRUE(iter != nullptr);
//     EXPECT_EQ("blue", iter->second);
//
//     // 'lookup' doesn't find a match.
//     iter = const_map<int, const char*>::lookup(COLOR_NAMES, 12345);
//     EXPECT_TRUE(iter == nullptr);
//

struct const_map_sentinel {
    static const int no = 0;
    static const int yes = 1;
};

template <typename From, typename To, typename KeyCompare = std::less<From> >
class const_map {
public:
    typedef From key_type;
    typedef To mapped_type;
    typedef KeyCompare key_compare;
    template<typename T1, typename T2>
    struct simple_pair {
        T1 first;
        T2 second;
        bool operator<(const simple_pair& rhs) const {
            key_compare comp;
            return comp(this->first, rhs.first);
        }
        bool operator==(const simple_pair& rhs) const {
            key_compare comp;
            return (!comp(this->first, rhs.first) && !comp(rhs.first, this->first)) && (this->second == rhs.second);
            //return (this->first == rhs.first) and (this->second == rhs.second);
        }
        bool operator!=(const simple_pair& rhs) const {
            return !(*this == rhs);
        }
    };
    typedef simple_pair<From, To> value_type;
    typedef const value_type* const_iterator;

    const_map();
    template<size_t N>
    explicit  const_map(const value_type (&mappings)[N], int sentinel = const_map_sentinel::no);
    const_map(const_iterator begin, const_iterator end);

    bool operator==(const const_map& rhs) const;
    bool operator!=(const const_map& rhs) const;

    const_iterator find(const key_type& from) const;
    const mapped_type& operator[](const key_type& from) const;
    template<size_t N>
    static const_iterator lookup(const value_type(&mapping)[N], const key_type& from);

    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    size_t size() const;

    template<size_t N>
    void set_mapping(const value_type (&mappings)[N], int sentinel = const_map_sentinel::no);
    void set_mapping(const_iterator begin, const_iterator end);

private:
    void check_mappings();

    const_iterator begin_;
    const_iterator end_;
};


template <typename From, typename To, typename KeyCompare>
const_map<From, To, KeyCompare>::const_map()
    : begin_(0)
    , end_(0) {
}


template <typename From, typename To, typename KeyCompare>
template<size_t N> inline
const_map<From, To, KeyCompare>::const_map(const value_type (&mappings)[N], int sentinel)
    : begin_(&mappings[0])
    , end_(sentinel == const_map_sentinel::no ? &mappings[N] : &mappings[N - 1]) {
    check_mappings();
}


template <typename From, typename To, typename KeyCompare> inline
const_map<From, To, KeyCompare>::const_map(const_iterator begin, const_iterator end)
    : begin_(begin)
    , end_(end) {
    check_mappings();
}


template <typename From, typename To, typename KeyCompare> inline
bool
const_map<From, To, KeyCompare>::operator==(const const_map& rhs) const {
    bool equal = false;
    if (this->size() == rhs.size()) {
        equal = true;
        const_iterator it1 = this->begin();
        const_iterator it2 = rhs.begin();
        for (; it1 != this->end(); ++it1, ++it2) {
            if (*it1 != *it2) {
                equal = false;
                break;
            }
        }
    }
    return equal;
}


template <typename From, typename To, typename KeyCompare> inline
bool
const_map<From, To, KeyCompare>::operator!=(const const_map& rhs) const {
    return !(*this == rhs);
}


template <typename From, typename To, typename KeyCompare> inline
typename const_map<From, To, KeyCompare>::const_iterator
const_map<From, To, KeyCompare>::begin() const {
    return begin_;
}


template <typename From, typename To, typename KeyCompare> inline
typename const_map<From, To, KeyCompare>::const_iterator
const_map<From, To, KeyCompare>::end() const {
    return end_;
}


template <typename From, typename To, typename KeyCompare> inline
typename const_map<From, To, KeyCompare>::const_iterator
const_map<From, To, KeyCompare>::cbegin() const {
    return begin_;
}


template <typename From, typename To, typename KeyCompare> inline
typename const_map<From, To, KeyCompare>::const_iterator
const_map<From, To, KeyCompare>::cend() const {
    return end_;
}


template <typename From, typename To, typename KeyCompare> inline
size_t
const_map<From, To, KeyCompare>::size() const {
    return end_ - begin_;
}


template <typename From, typename To, typename KeyCompare> inline
typename const_map<From, To, KeyCompare>::const_iterator
const_map<From, To, KeyCompare>::find(const key_type& from) const {
    const simple_pair<From, To> search_value = {
        from,
        To()
    };
    const_iterator it = std::lower_bound(begin(), end(), search_value);
    return it;
}


template <typename From, typename To, typename KeyCompare> inline
const typename const_map<From, To, KeyCompare>::mapped_type&
const_map<From, To, KeyCompare>::operator[](const key_type& from) const {
    const_iterator it = find(from);
    return (*it).second;
}


template <typename From, typename To, typename KeyCompare>
template <size_t N> inline
typename const_map<From, To, KeyCompare>::const_iterator
const_map<From, To, KeyCompare>::lookup(const value_type(&mapping)[N], const key_type& from) {
    const simple_pair<From, To> search_value = {
        from,
        To()
    };
    const_iterator it = std::lower_bound(&mapping[0], &mapping[N], search_value);
    return (it != &mapping[N]) ? it : 0;
}


template <typename From, typename To, typename KeyCompare>
template<size_t N> inline
void
const_map<From, To, KeyCompare>::set_mapping(const value_type (&mappings)[N], int sentinel) {
    begin_ = &mappings[0];
    end_ = (sentinel == const_map_sentinel::no ? &mappings[N] : &mappings[N - 1]);
    check_mappings();
}


template <typename From, typename To, typename KeyCompare> inline
void
const_map<From, To, KeyCompare>::set_mapping(const_iterator begin, const_iterator end) {
    begin_ = begin;
    end_ = end;
    check_mappings();
}


template <typename From, typename To, typename KeyCompare> inline
void
const_map<From, To, KeyCompare>::check_mappings() {
#ifndef NDEBUG
    assert(begin_ != 0);
    assert(end_ != 0);
    assert(end_ - begin_ != 0);
    key_compare comp;
    const_iterator prev = begin();
    const_iterator it = prev + 1;
    for (; it != end(); ++it, ++prev) {
        assert(comp((*prev).first, (*it).first)); // Keys must be sorted, in ascending order.
    }
#endif
}

} // namespace approxion

#endif

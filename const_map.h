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
//     static const const_map<int, const char*>::value_type COLOR_STR[] = {
//         { 111, "red"   },
//         { 222, "green" },
//         { 333, "blue"  },
//     };
//
//     const_map<int, const char*> color_strings(COLOR_STR);
//
//     // Simple lookup.
//     EXPECT_EQ("green", color_strings[222]);
//
//     // Lookup via 'find'.
//     auto iter = color_strings.find(333);
//     EXPECT_TRUE(iter != color_strings.end());
//     EXPECT_EQ("blue", iter->second);
//
//     // Lookup via 'find' failed.
//     iter = color_strings.find(12345);
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
        bool operator==(const simple_pair& rhs) const {
            return (this->first == rhs.first) and (this->second == rhs.second);
        }
        bool operator!=(const simple_pair& rhs) const {
            return !(*this == rhs);
        }
    };
    typedef simple_pair<From, To> value_type;
    typedef From key_type;
    typedef To mapped_type;
    typedef const value_type* const_iterator;

    const_map();
    template<size_t N>
        explicit  const_map(const value_type (&mappings)[N]);
    const_map(const_iterator begin, const value_type* end);
    const_map(const_iterator begin, size_t nelem);

    bool operator==(const const_map& rhs) const;
    bool operator!=(const const_map& rhs) const;

    const_iterator find(const key_type& from) const;
    const mapped_type& operator[](const key_type& from) const;

    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    size_t size() const;

    template<size_t N>
    void set_mapping(const value_type (&mappings)[N]);
    void set_mapping(const value_type* begin, const value_type* end);
    void set_mapping(const value_type* begin, size_t nelem);

private:
     void check_mappings();

    const_iterator begin_;
    const_iterator end_;
};


template <typename From, typename To>
const_map<From, To>::const_map()
    : begin_(0)
    , end_(0)
{
    ;
}


template <typename From, typename To>
template<size_t N>
inline 
const_map<From, To>::const_map(const value_type (&mappings)[N])
    : begin_(&mappings[0])
    , end_(&mappings[N]) {
    check_mappings();
}


template <typename From, typename To>
inline
const_map<From, To>::const_map(const value_type* begin, const value_type* end)
    : begin_(begin)
    , end_(end)
{
    check_mappings();
}


template <typename From, typename To>
inline
const_map<From, To>::const_map(const value_type* begin, size_t nelem)
    : begin_(begin)
    , end_(begin + nelem)
{
    check_mappings();
}


template <typename From, typename To>
inline
bool
const_map<From, To>::operator==(const const_map& rhs) const {
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


template <typename From, typename To>
inline
bool
const_map<From, To>::operator!=(const const_map& rhs) const {
    return !(*this == rhs);
}


template <typename From, typename To>
inline
typename const_map<From, To>::const_iterator
const_map<From, To>::begin() const {
    return begin_;
}


template <typename From, typename To>
inline
typename const_map<From, To>::const_iterator
const_map<From, To>::end() const {
    return end_;
}


template <typename From, typename To>
inline
typename const_map<From, To>::const_iterator
const_map<From, To>::cbegin() const {
    return begin_;
}


template <typename From, typename To>
inline
typename const_map<From, To>::const_iterator
const_map<From, To>::cend() const {
    return end_;
}


template <typename From, typename To>
inline
size_t
const_map<From, To>::size() const {
    return end_ - begin_;
}


template <typename From, typename To>
inline
const typename const_map<From, To>::value_type*
const_map<From, To>::find(const key_type& from) const {
    const simple_pair<From, To> search_value = {
        from,
        To()
    };
    const_iterator it = std::lower_bound(begin(), end(), search_value);
    return it;
}


template <typename From, typename To>
inline
const typename const_map<From, To>::mapped_type&
const_map<From, To>::operator[](const key_type& from) const {
    const_iterator it = find(from);
    return (*it).second;
}


template <typename From, typename To>
template<size_t N>
inline
void
const_map<From, To>::set_mapping(const value_type (&mappings)[N]) {
    begin_ = &mappings[0];
    end_ = &mappings[N];
    check_mappings();
}


template <typename From, typename To>
inline
void
const_map<From, To>::set_mapping(const value_type* begin, const value_type* end) {
    begin_ = begin;
    end_ = end;
    check_mappings();
}


template <typename From, typename To>
inline
void
const_map<From, To>::set_mapping(const value_type* begin, size_t nelem) {
    begin_ = begin;
    end_ = begin + nelem;
    check_mappings();
}


template <typename From, typename To>
inline
void
const_map<From, To>::check_mappings() {
#ifndef NDEBUG
    assert(begin_ != 0);
    assert(end_ != 0);
    assert(end_ - begin_ != 0);
    const_iterator prev = begin();
    const_iterator it = prev + 1;
    for (; it != end(); ++it, ++prev) {
        assert((*it).first > (*prev).first); // Keys must be sorted, in ascending order.
    }
#endif
}


#endif

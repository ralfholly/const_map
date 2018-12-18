#ifndef CONST_MAP_H
#define CONST_MAP_H

#include <algorithm>
#include <cassert>


template <typename FROM, typename TO>
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
    typedef simple_pair<FROM, TO> value_type;
    typedef FROM key_type;
    typedef TO mapped_type;
    typedef const value_type* const_iterator;

    template<size_t N>
    inline const_map(const value_type (&mappings)[N]);
    // TODO:
    inline const_map(const value_type* mappings, size_t mappings_size);


    inline const_iterator find(const key_type& from) const;
    inline const mapped_type& operator[](const key_type& from) const;

    inline const_iterator begin() const;
    inline const_iterator end() const;
    inline const_iterator cbegin() const;
    inline const_iterator cend() const;
    inline size_t size() const;

private:
    inline void check_preconditions();

    const_iterator begin_;
    const_iterator end_;
};


template <typename FROM, typename TO>
template<size_t N>
inline const_map<FROM, TO>::const_map(const value_type (&mappings)[N])
    : begin_(&mappings[0])
    , end_(&mappings[N - 1]) {
    check_preconditions();
}


template<typename FROM, typename TO>
typename const_map<FROM, TO>::const_iterator const_map<FROM, TO>::begin() const {
    return begin_;
}


template<typename FROM, typename TO>
typename const_map<FROM, TO>::const_iterator const_map<FROM, TO>::end() const {
    return end_;
}


template<typename FROM, typename TO>
typename const_map<FROM, TO>::const_iterator const_map<FROM, TO>::cbegin() const {
    return begin_;
}


template<typename FROM, typename TO>
typename const_map<FROM, TO>::const_iterator const_map<FROM, TO>::cend() const {
    return end_;
}


template<typename FROM, typename TO>
size_t const_map<FROM, TO>::size() const {
    return end_ - begin_;
}


template <typename FROM, typename TO>
const typename const_map<FROM, TO>::value_type* const_map<FROM, TO>::find(const key_type& from) const {
    const simple_pair<FROM, TO> search_value = {
        from,
        TO()
    };
    const_iterator it = std::lower_bound(begin(), end(), search_value);
    return it;
}


template <typename FROM, typename TO>
const typename const_map<FROM, TO>::mapped_type& const_map<FROM, TO>::operator[](const key_type& from) const {
    const_iterator it = find(from);
    return (*it).second;
}


template <typename FROM, typename TO>
void const_map<FROM, TO>::check_preconditions() {
#ifndef NDEBUG
    assert(begin_ != 0);
    assert(end_ != 0);
    const_iterator prev = begin();
    const_iterator it = prev + 1;
    for (; it != end(); ++it, ++prev) {
        assert((*it).first > (*prev).first); // Keys must be in sorted, in ascending order.
    }
    // Sentinel check.
    const FROM defval = FROM();
    assert(!((*it).first < defval) && !(defval < (*it).first)); // Last key must be key's default value.
#endif
}


#endif

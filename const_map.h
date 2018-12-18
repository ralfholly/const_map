#ifndef CONST_MAP_H
#define CONST_MAP_H

#include <algorithm>
#include <cassert>


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

    const_iterator begin_;
    const_iterator end_;
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

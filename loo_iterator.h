/*
*   Created by loora1N on 2023/9/25 
*/

#ifndef LOOSTL_LOO_ITERATOR_H
#define LOOSTL_LOO_ITERATOR_H

#include "loo_config.h"
#include "loo_iterator_base.h"

__STL_BEGIN_NAMESPACE

template<class _Container>
class back_insert_iterator {
    protected:
        _Container *container;
    public:
        typedef _Container          container_type;
        typedef output_iterator_tag iterator_category;
        typedef void                value_type;
        typedef void                difference_type;
        typedef void                pointer;
        typedef void                reference;

        explicit back_insert_iterator(_Container &__x) : container(&__x) {}

        back_insert_iterator<_Container> &operator=(const typename _Container::value_type &__value) {
            container->push_back(__value);
            return *this;
        }

        back_insert_iterator<_Container> &operator*() { return *this; }

        back_insert_iterator<_Container> &operator++() { return *this; }

        back_insert_iterator<_Container> &operator++(int) { return *this; }

};

template<class _Container>
inline back_insert_iterator<_Container> back_inserter(_Container &__x) {
    return back_insert_iterator<_Container>(__x);
}

template <class _Container>
class front_insert_iterator {
    protected:
        _Container* container;
    public:
        typedef _Container          container_type;
        typedef output_iterator_tag iterator_category;
        typedef void                value_type;
        typedef void                difference_type;
        typedef void                pointer;
        typedef void                reference;

        explicit front_insert_iterator(_Container& __x) : container(&__x){}
        front_insert_iterator<_Container>&
        operator=(const typename _Container::value_type& __value) {
            container->push_front(__value);
            return *this;
        }
        front_insert_iterator<_Container>& operator*() { return *this; }
        front_insert_iterator<_Container>& operator++() { return *this; }      
        front_insert_iterator<_Container>& operator++(int) { return *this; }
};

template<class _Container>
inline front_insert_iterator<_Container> front_insert(_Container &__x) {
    return front_insert_iterator<_Container>(__x);
}

template<class _Container>
class insert_iterator
{
protected:
    _Container *container;
    typename _Container::iterator iter;
public:
    typedef _Container          container_type;
    typedef output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;

    insert_iterator(_Container *__x, typename _Container::iterator __i) : container(&__x), iter(__i) {}

    insert_iterator<_Container> &operator=(const typename _Container::value_type &__value) {
        iter = container->insert(iter, __value);    //插入位置魏iter之前的位置
        ++iter; //iter复位
        return *this;
    }

    insert_iterator<_Container> &operator*() { return *this; }

    insert_iterator<_Container> &operator++() { return *this; }

    insert_iterator<_Container> &operator++(int) { return *this; }
};

template<class _Container, class _Iterator>
inline insert_iterator<_Container> inserter(_Container &__x, _Iterator __i) {
    typedef typename _Container::iterator __iter;
    return insert_iterator<_Container>(__x, iter(__i));
}

/*TODO: 2023/9/25 */
template<class _Iterator>
class reverse_iterator {

};


__STL_END_NAMESPACE


#endif /* LOOSTL_LOO_ITERATOR_H */
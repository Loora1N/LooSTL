/*
*   Crearted by Loora1N 2023/8/31
*/

#ifndef LOOSTL_LOO_ITERRATOR_BASE_H
#define LOOSTL_LOO_ITERRATOR_BASE_H

#include <stddef.h>
#include "loo_config.h"

__STL_BEGIN_NAMESPACE
    
/*
*   Five iterator categories
*/  

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forword_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forword_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/* 输入迭代器 */
template <class _Tp, class _Distance> 
struct input_iterator
{
    typedef input_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
};

/* 输出迭代器 */
struct output_iterator {
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;
};

/* 向前迭代器 */
template <class _Tp, class _Distance> 
struct forword_iterator {
    typedef forword_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
};

/* 双向迭代器 */
template <class _Tp, class _Distance> 
struct bidirectional_iterator {
    typedef bidirectional_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
};

/* 随机访问迭代器 */
template <class _Tp, class _Distance> 
struct random_access_iterator {
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
};

/*
*   Iterator
*/
template<class _Category, class _Tp, class _Distance = ptrdiff_t, class _Pointer = _Tp*, class _Reference = _Tp &>
struct iterator {
    typedef _Category iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Pointer pointer;
    typedef _Reference reference;
};


template<class _Iterator>
struct iterator_traits {
    typedef typename _Iterator::iterator_category iterator_category;
    typedef typename _Iterator::value_type value_type;
    typedef typename _Iterator::difference_type difference_type;
    typedef typename _Iterator::pointer pointer;
    typedef typename _Iterator::reference reference;
};

/*
*   Templete partial specializtion for native pointer 
*/
template<class _Tp>
struct iterator_traits<_Tp*> {
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef ptrdiff_t difference_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
};

template<class _Tp>
struct iterator_traits<const _Tp*> {
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef ptrdiff_t difference_type;
    typedef const _Tp* pointer;
    typedef const _Tp& reference;
};

/*
*   确定迭代器的category并封装函数
*/
template<class _Iter>
inline typename iterator_traits<_Iter>::iterator_category __iterator_category(const _Iter&) {
    typedef typename iterator_traits<_Iter>::iterator_category __Category;
    return __Category();
}

template<class _Iter>
inline typename iterator_traits<_Iter>::iterator_category iterator_category(const _Iter& __i) {
    return __iterator_category(__i);
}

/*
*   确定迭代器的difference type类型
*/
template<class _Iter>
inline typename iterator_traits<_Iter>::difference_type* __distance_type(const _Iter&) {
    return static_cast<typename iterator_traits<_Iter>::difference_type *>(0);
}

template<class _Iter>
inline typename iterator_traits<_Iter>::difference_type* distance_type(const _Iter& __i) {
    return __distance_type(__i);
}

/*
*   确定迭代器的value type 类型
*/
template<class _Iter>
inline typename iterator_traits<_Iter>::value_type* __value_type(const _Iter&) {
    return static_cast<typename iterator_traits<_Iter>::value_type*>(0);
}

template<class _Iter>
inline typename iterator_traits<_Iter>::difference_type* value_type(const _Iter& __i) {
    return __value_type(__i);
}

#define __ITERATOR_CATEGORY(__i) __iterator_category(__i)
#define __DISTANCE_TYPE(__i)     __distance_type(__i)
#define __VALUE_TYPE(__i)        __value_type(__i)

/*
*   distance函数，距离计算
*/
template <class _InputIterator, class _Distance>
inline void __distance(_InputIterator __first, _InputIterator __last, _Distance& __n, input_iterator_tag) {
    while (__first != __last) {
        ++__first;
        ++__n;
    }
}

template <class _RandomAccessIterator, class _Distance>
inline void __distance(_RandomAccessIterator __first, _RandomAccessIterator __last, _Distance& __n, random_access_iterator_tag) {
    __n += __last - __first;
}

//封装底层两中distance函数
template<class _InputIterator, class _Distance>
inline void distance(_InputIterator __first, _InputIterator __last, _Distance& __n) {
    __distance(__first, __last, __n, iterator_category(__first));
}

#ifdef __STL_CLASS_PATIAL_SPECIALIZATION

    template<class _InputIterator>
    inline typename iterator_traits<_InputIterator>::diffenence_type
    __distance(_InputIterator __first, _InputIterator __last, input_iterator_tag) {
        typename iterator_traits<_InputIterator>::differen_type __n = 0;
        while (__first != __last) {
            ++__first;
            ++__n;
        }
        return __n;
    }

    template<class _RandomAccessIterator>
    inline typename iterator_traits<RandomAccessIterator>::difference_type
    __distance(_RandomAccessIterator __first, _RandomAccessIterator __last, random_access_iterator_tag) {
        return __last - __first;
    }

    template<class _InputIterator, class _Distance>
    inline typename iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, __InputIterator __last) {
        typedef typename iterator_traits<_InputIterator>::iterator_category _Category;
        __distance(__first, __last, Category());
    }

#endif /* __STL_CLASS_PATIAL_SPECIALIZATION */


    template<class _InputIterator, class _Distance>
    inline void __advance(_InputIterator &__i, _Distance __n, input_iterator_tag) {
        while(__n--) {
            ++__i;
        }
    }

    template<class _BidrectionalIterator, class _Distance>
    inline void __advance(_BidrectionalIterator &__i, _Distance __n, bidirectional_iterator_tag) {
        if (__n > 0) {
            while (__n--) {
                ++__i;
            }
        } else {
            while (__n++) {
                --__i;
            }
        }
    }

    template<class _RandomAccessIterator, class _Distance>
    inline void advance(_RandomAccessIterator &__i, _Distance __n) {
        __advance(__i, __n, __iterator_category(__i));
    }

__STL_END_NAMESPACE

#endif /* LOOSTL_STL_ITERRATOR_BASE_H */
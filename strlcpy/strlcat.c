/*
 * strlcat.c: Naive implementation of 'strlcat'.
 *
 * Copyright 2012-2014 Masashi Fujita
 *
 * License: Ms-Pl (http://www.opensource.org/licenses/ms-pl.html)
 */
#include <sys/types.h>
#include <string.h>

#include "../include/config.h"

#if defined (HAS_STRLCAT) && (HAS_STRLCAT != 0)
#   define EXPORT_(X_) X_##_test
#else
#   define EXPORT_(X_) X_
#endif

#if defined (HAS_STRNLEN) && (HAS_STRNLEN != 0)
#   define strlen_limited(S_, M_) (strnlen ((S_), (M_)))
#elif defined (HAS_STRLEN_S) && (HAS_STRLEN_S != 0)
#   define strlen_limited(S_, M_) (strlen_s ((S_), (M_)))
#else
#   error "No length limited strlen"
#endif

size_t  EXPORT_(strlcat) (char * dst, const char * src, size_t dstsize) {
    size_t src_len ;
    size_t dst_len ;
    size_t dstlimit ;

    if (dst == 0) {
        if (src == 0) {
            return 0 ;
        }
        return strlen (src) ;
    }
    /* At this point, DST != nullptr */
    if (src == 0) {
        return strlen_limited (dst, dstsize) ;
    }
    /* At this poinit, DST != nullptr && SRC != nullptr */
    src_len = strlen (src) ;
    dst_len = strlen_limited (dst, dstsize) ;
    dstlimit = dstsize - 1 ;

    if (dstlimit < dst_len) {
        /* Already overflowed */
        return dst_len + src_len ;
    }
    else {
        size_t len = src_len ;
        /* dstlen <= dstlimit */
        if (dstlimit < (dst_len + src_len)) {
            len = dstlimit - dst_len ;
        }
        memcpy (dst + dst_len, src, len) ;
        dst [dst_len + len] = 0 ;
        return dst_len + src_len ;
    }
}

/*
 * [END OF FILE]
 */


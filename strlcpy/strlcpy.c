/*
 * strlcpy.c: Naive implementation of 'strlcpy'.
 *
 * Copyright 2012-2014 Masashi Fujita
 *
 * License: Ms-Pl (http://www.opensource.org/licenses/ms-pl.html)
 */
#include <sys/types.h>
#include <string.h>
#include "../include/config.h"

#if defined (HAS_STRLCPY) && (HAS_STRLCPY != 0)
#   define EXPORT_(X_) X_##_test
#else
#   define EXPORT_(X_) X_
#endif

size_t  EXPORT_(strlcpy) (char * dst, const char * src, size_t dstsize) {
    size_t src_len ;
    size_t len ;
    size_t dstlimit ;

    if (src == 0) {
        if (dst != 0 && 0 < dstsize) {
            dst [0] = 0 ;
        }
        return 0 ;
    }

    src_len = strlen (src) ;
    len = src_len ;

    if (dst == 0 || dstsize == 0) {
        return src_len ;
    }
    dstlimit = dstsize - 1 ;

    if (dstlimit < len) {
        len = dstlimit ;
    }
    memcpy (dst, src, len) ;
    dst [len] = 0 ;

    return src_len ;
}

/*
 * [END OF FILE]
 */

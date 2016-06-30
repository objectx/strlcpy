/*
 * strlcpy.c: Naive implementation of 'strlcpy'.
 *
 * Copyright 2012-2014 Masashi Fujita
 *
 * License: Ms-Pl (http://www.opensource.org/licenses/ms-pl.html)
 */
#include <sys/types.h>
#include <string.h>

#ifdef HAVE_CONFIG_H
#   include "config.h"
#endif

#ifdef HAVE_STRLCPY
#   define export_strlcpy   strlcpy_test
#else
#   define export_strlcpy   strlcpy
#endif

#ifdef __cplusplus
extern "C" {
#endif

size_t  export_strlcpy (char * dst, const char * src, size_t dstsize) {
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

#ifdef __cplusplus
}
#endif
/*
 * [END OF FILE]
 */

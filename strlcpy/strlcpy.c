/*
 * strlcpy.c: Naive implementation of 'strlcpy'.
 *
 * Copyright 2012 Masashi Fujita
 *
 * License: Ms-Pl (http://www.opensource.org/licenses/ms-pl.html)
 */
#include <sys/types.h>
#include <string.h>
#include "../include/config.h"

#if defined (TEST_ONLY)
#   define EXPORT_(X_) X_##test
#else
#   define EXPORT_(X_) X_
#endif

size_t	EXPORT_(strlcpy) (char * dst, const char * src, size_t dstsize) {
    if (dst == 0 || dstsize == 0) {
	return 0;
    }
    if (src == 0) {
	dst [0] = 0;
	return 0;
    }
    else {
        size_t	src_len = strlen (src);
        size_t	dstlimit = dstsize - 1;

        if (dstlimit < src_len) {
	    src_len = dstlimit;
        }
        memcpy (dst, src, src_len);
        dst [src_len] = 0;
        return src_len;
    }
}

/*
 * [END OF FILE]
 */


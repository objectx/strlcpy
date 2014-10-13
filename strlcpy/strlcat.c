/*
 * strlcat.c: Naive implementation of 'strlcat'.
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

size_t	EXPORT_(strlcat) (char * dst, const char * src, size_t dstsize) {
    if (dst == 0 || dstsize == 0) {
	return 0;
    }
    else {
	size_t	dst_len = strlen (dst);

	if (src == 0) {
	    return dst_len;
	}
	else {
	    size_t	dstlimit = dstsize - 1;
	    size_t	src_len = strlen (src);

	    if (dstlimit < dst_len) {
		/* Already overflowed.  */
		return dst_len;
	    }
	    /* dst_len <= dstlimit */
	    if (dstlimit < (dst_len + src_len)) {
		src_len = dstlimit - dst_len;
		/* 0 <= src_len */
	    }
	    memcpy (dst + dst_len, src, src_len);
	    dst [dst_len + src_len] = 0;
	    return (dst_len + src_len);
	}
    }
}

/*
 * [END OF FILE]
 */


/*
 * strlcpy.c:
 *
 * Author(s): objectx
 */

#include <sys/types.h>
#include <string.h>

size_t	strlcpy (char * dst, const char * src, size_t dstsize) {
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


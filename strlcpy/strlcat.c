/*
 * strlcat.c:
 *
 * Author(s): objectx
 */

#include <sys/types.h>
#include <string.h>

size_t	strlcat (char * dst, const char * src, size_t dstsize) {
    size_t	src_len = strlen (src);
    size_t	dst_len = strlen (dst);
    size_t	dstlimit = dstsize - 1;

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

/*
 * [END OF FILE]
 */


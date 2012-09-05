/*
 * strlcpy.c:
 *
 * Author(s): objectx
 */

#include <sys/types.h>
#include <string.h>

size_t	strlcpy (char * dst, const char * src, size_t dstsize) {
    size_t	src_len = strlen (src);

    if ((dstsize - 1) < src_len) {
	src_len = dstsize - 1;
    }
    (void)memcpy (dst, src, src_len);
    dst [src_len] = 0;
    return src_len;
}

/*
 * [END OF FILE]
 */


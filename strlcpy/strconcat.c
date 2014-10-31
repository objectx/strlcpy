/*
 * strlcat.c: Concatenate supplied strings.
 *
 * Copyright 2012 Masashi Fujita
 *
 * License: Ms-Pl (http://www.opensource.org/licenses/ms-pl.html)
 */

#include <sys/types.h>
#include <string.h>
#include <stdarg.h>


size_t	vstrconcat (char *dst, size_t dstsize, size_t cntArgs, va_list ap) {
    size_t dstlimit = dstsize - 1 ;
    size_t total = 0 ;
    size_t i ;

    if (dst == 0 || dstsize == 0) {
       return 0 ;
    }
    for (i = 0; i < cntArgs; ++i) {
        const char *s = va_arg (ap, const char *) ;

        if (s != 0) {
            size_t len = strlen (s) ;

            if (dstlimit <= (total + len)) {
                len = dstlimit - total ;
                memcpy (dst + total, s, len) ;
                total = dstlimit ;
                break ;
            }
            else {
                memcpy (dst + total, s, len) ;
                total += len ;
            }
        }
    }
    dst [total] = 0 ;
    return total ;
}


size_t	strconcat (char *dst, size_t dstsize, size_t cntArgs, ...) {
    size_t	len ;
    va_list	ap ;

    va_start (ap, cntArgs) ;
    {
	len = vstrconcat (dst, dstsize, cntArgs, ap) ;
    }
    va_end (ap) ;

    return len ;
}
/*
 * [END OF FILE]
 */

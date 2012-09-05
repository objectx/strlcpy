/*
 * common.h:
 *
 * Author(s): objectx
 */
#ifndef	common_h__5D80A5054F1D2E78D6D9FAB4123D1AE7
#define	common_h__5D80A5054F1D2E78D6D9FAB4123D1AE7	1

#if defined (_MSC_VER) && (1300 <= _MSC_VER)
#pragma once
#endif

#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <assert.h>

#if defined (__cplusplus)
extern "C" {
#endif

extern size_t	strlcpy (char * dst, const char * src, size_t dstsize);
extern size_t	strlcat (char * dst, const char * src, size_t dstsize);

#if defined (__cplusplus)
}	/* end of [extern "C"] */
#endif

#endif	/* common_h__5D80A5054F1D2E78D6D9FAB4123D1AE7 */

/*
 * [END OF FILE]
 */


/*
 * common.h: Common include files (for utilize pre-compiled header).
 *
 * Copyright 2012 Masashi Fujita
 *
 * License: Ms-Pl (http://www.opensource.org/licenses/ms-pl.html)
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
#include <stdarg.h>

#if defined (__cplusplus)
extern "C" {
#endif

#if defined (TEST_ONLY)
extern size_t	strlcpy_test (char * dst, const char * src, size_t dstsize);
extern size_t	strlcat_test (char * dst, const char * src, size_t dstsize);
#endif
extern size_t	strconcat (char * dst, size_t dstsize, size_t cntArgs, ...);
extern size_t	vstrconcat (char * dst, size_t dstsize, size_t cntArgs, va_list ap);

#if defined (__cplusplus)
}	/* end of [extern "C"] */
#endif

#endif	/* common_h__5D80A5054F1D2E78D6D9FAB4123D1AE7 */

/*
 * [END OF FILE]
 */


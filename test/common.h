/*
 * common.h: Common include files (for utilize pre-compiled header).
 *
 * Copyright 2012-2014 Masashi Fujita
 *
 * License: Ms-Pl (http://www.opensource.org/licenses/ms-pl.html)
 */
#pragma once
#ifndef	common_h__5D80A5054F1D2E78D6D9FAB4123D1AE7
#define	common_h__5D80A5054F1D2E78D6D9FAB4123D1AE7	1

#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <stdarg.h>
#include <array>
#include <strconcat.hpp>

#include "config.h"
#if defined (__cplusplus)
extern "C" {
#endif

#ifdef HAVE_STRLCPY
extern size_t strlcpy_test (char *dst, const char *src, size_t dstsize);
#else
extern size_t strlcpy (char *dst, const char *src, size_t distsize) ;
#endif

#ifdef HAVE_STRLCAT
extern size_t strlcat_test (char *dst, const char *src, size_t dstsize);
#else
extern size_t strlcat (char *dst, const char *src, size_t dstsize);
#endif


#if defined (__cplusplus)
}	/* end of [extern "C"] */
#endif

#endif	/* common_h__5D80A5054F1D2E78D6D9FAB4123D1AE7 */

/*
 * [END OF FILE]
 */


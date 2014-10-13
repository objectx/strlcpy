/*
 * strlcpy.cpp:
 *
 * Copyright 2014 Masashi Fujita
 *
 * License: Ms-PL (http://www.opensource.org/licenses/ms-pl.html)
 */
#include "common.h"
#include "catch.hpp"

SCENARIO ("strlcpy", "[strlcpy]") {
    char    dst [256];
    const char  alphabets [] = "abcdefghijklmnopqrstuvwxyz";
    size_t  alpha_len = strlen (alphabets);
    size_t  result;
    size_t  (*p_strlcpy) (char *dst, const char *src, size_t dstsize) ;

#if defined (HAS_STRLCPY) && (HAS_STRLCPY != 0)
    p_strlcpy = strlcpy_test ;
#else
    p_strlcpy = strlcpy ;
#endif

    GIVEN ("0xFF filled buffer") {
        memset (dst, 0xFF, sizeof(dst));

        WHEN ("copy to 0 byte destination") {
            result = p_strlcpy (dst, alphabets, 0);
        THEN ("strlcpy should return source string length (== 26)") {
            REQUIRE (result == alpha_len) ;
        AND_THEN ("Destination should not be modified") {
            REQUIRE (dst [0] == '\xFF');
        }}}

#if defined (HAS_STRLCPY) && (HAS_STRLCPY != 0)
        INFO ("Darwin's strlcpy does not allow nullptr for destination.") ;
        WHEN ("copy to null buffer") {
            result = p_strlcpy (0, alphabets, sizeof (dst)) ;
        THEN ("strlcpy should return source string length (== 26)") {
            REQUIRE (result == alpha_len) ;
        }}

        INFO ("Darwin's strlcpy does not allow nullptr for source.")
        WHEN ("copy from null") {
            result = p_strlcpy (dst, 0, sizeof (dst)) ;
        THEN ("strlcpy should return source string length (== 0)") {
            REQUIRE (result == 0) ;
        AND_THEN ("dst [0] should be \\0") {
            REQUIRE (dst [0] == 0) ;
        }}}
#endif

        WHEN ("copying first 4 characters") {
            result = p_strlcpy (dst, alphabets, 4) ;
        THEN ("strlcpy should returns 26") {
            REQUIRE (result == 26) ;
        AND_THEN ("dst [3] should be \\0") {
            REQUIRE (dst [3] == 0) ;
        AND_THEN ("dst [4] should be unchanged") {
            REQUIRE (dst [4] == '\xFF') ;
        AND_THEN ("dst [0..3] should be \"abc\"") {
            REQUIRE (memcmp (dst, alphabets, 3) == 0) ;
        }}}}}

        WHEN ("copying all of source characters") {
            result = p_strlcpy (dst, alphabets, sizeof (dst)) ;
        THEN ("strlcpy should return 26") {
            REQUIRE (result == 26) ;
        AND_THEN ("dst [26] should be \\0") {
            REQUIRE (dst [alpha_len] == 0) ;
        AND_THEN ("dst [27] should be \xFF") {
            REQUIRE (dst [alpha_len + 1] == '\xFF') ;
        AND_THEN ("dst [0..25] should be \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (memcmp (dst, alphabets, alpha_len) == 0) ;
        }}}}}
    }
}


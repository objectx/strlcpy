/*
 * strlcat.cpp:
 *
 * Copyright 2014 Masashi Fujita
 *
 * License: Ms-PL (http://www.opensource.org/licenses/ms-pl.html)
 */
#include "common.h"
#include "catch.hpp"

SCENARIO ("strlcat", "[strlcat]") {
    char dst [256] ;
    const char  alphabets [] = "abcdefghijklmnopqrstuvwxyz";
    size_t  alpha_len = strlen (alphabets);
    size_t  result;

    size_t (*p_strlcat) (char *dst, const char *src, size_t dstsize) ;

#if defined (HAS_STRLCAT) && (HAS_STRLCAT != 0)
    p_strlcat = strlcat_test ;
#else
    p_strlcat = strlcat ;
#endif

    GIVEN ("0xFF filled buffer") {
        memset (dst, 0xFF, sizeof (dst)) ;

#if defined (HAS_STRLCAT) && (HAS_STRLCAT != 0)
        INFO ("Passing nullptr to destination is undefined") ;
        WHEN ("strlcat to null") {
            result = p_strlcat (0, alphabets, sizeof (dst)) ;
        THEN ("strlcat should return 26") {
            REQUIRE (result == 26) ;
        }}
        INFO ("Passing nullptr to source is undefined") ;
        WHEN ("strlcat from null") {
            result = p_strlcat (dst, 0, sizeof (dst)) ;
        THEN ("strlcat should return 0") {
            REQUIRE (result == 256) ;
        }}
        WHEN ("strlcat from empty string") {
            result = p_strlcat (dst, "", sizeof (dst)) ;
        THEN ("strlcat should return 0") {
            REQUIRE (result == 256) ;
        }}
#endif
        WHEN ("strlcpy to dst") {
            result = strlcpy (dst, alphabets, sizeof (dst)) ;
            REQUIRE (result == 26) ;
        AND_WHEN ("strlcat with empty string") {
            result = p_strlcat (dst, "", sizeof (dst)) ;
        THEN ("strlcat should return 26") {
            REQUIRE (result == alpha_len) ;
        AND_THEN ("dst [26] == '\0'") {
            REQUIRE (dst [alpha_len + 0] == 0) ;
        AND_THEN ("dst [27] == '\xFF'") {
            REQUIRE (dst [alpha_len + 1] == '\xFF') ;
        AND_THEN ("dst should match alphabets") {
            REQUIRE (memcmp (dst, alphabets, alpha_len) == 0) ;
        }}}}}}

        WHEN ("Append to \"ABCD\"") {
            dst [0] = 'A';
            dst [1] = 'B';
            dst [2] = 'C';
            dst [3] = 'D';
            dst [4] = 0;
        AND_WHEN ("append alphabets") {
            result = p_strlcat (dst, alphabets, 3) ;
        THEN ("strlcat should return 29") {
            REQUIRE (result == 29) ;
        AND_THEN ("dst [4] == 0") {
            REQUIRE (dst [4] == 0) ;
        AND_THEN ("dst [5] == '\xFF'") {
            REQUIRE (dst [5] == '\xFF') ;
        AND_THEN ("dst should be \"ABCD\"") {
            REQUIRE (memcmp (dst, "ABCD", 4) == 0) ;
        }}}}}}

        WHEN ("Append to \"ABCD\"") {
            dst [0] = 'A';
            dst [1] = 'B';
            dst [2] = 'C';
            dst [3] = 'D';
            dst [4] = 0;
        AND_WHEN ("append alphabets") {
            result = p_strlcat (dst, alphabets, sizeof (dst)) ;
        THEN ("strlcat should return 30") {
            REQUIRE (result == 30) ;
        AND_THEN ("dst [4 + 26 + 0] == 0") {
            REQUIRE (dst [4 + alpha_len + 0] == 0) ;
        AND_THEN ("dst [4 + 26 + 1] == '\xFF'") {
            REQUIRE (dst [4 + alpha_len + 1] == '\xFF') ;
        AND_THEN ("Start with \"ABCD\"") {
            REQUIRE (memcmp (dst, "ABCD", 4) == 0) ;
        AND_THEN ("And follows alphabets") {
            REQUIRE (memcmp (dst + 4, alphabets, alpha_len) == 0) ;
        }}}}}}}
    }
}

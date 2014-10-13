/*
 * main.c: Tests for strlcpy & strlcat.
 *
 * Copyright 2012-2014 Masashi Fujita
 *
 * License: Ms-Pl (http://www.opensource.org/licenses/ms-pl.html)
 */
#include "common.h"
#define CATCH_CONFIG_MAIN 1
#include "catch.hpp"

SCENARIO ("strlcpy", "[strlcpy]") {
    char    dst [256];
    const char  alphabets [] = "abcdefghijklmnopqrstuvwxyz";
    size_t  alpha_len = strlen (alphabets);
    size_t  result;
    size_t  (*p_strlcpy) (char *dst, const char *src, size_t dstsize) ;

#ifdef TEST_ONLY
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

#ifdef TEST_ONLY
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


void	test_strlcat () {
    char	dst [256];
    const char	alphabets [] = "abcdefghijklmnopqrstuvwxyz";
    size_t	alpha_len = strlen (alphabets);
    size_t	result;

    result = strlcat (0, alphabets, sizeof(dst));
    assert (result == 0);
    result = strlcat (dst, alphabets, 0);
    assert (result == 0);

    memset (dst, 0xFF, sizeof(dst));
    strlcpy (dst, alphabets, sizeof(dst));
    result = strlcat (dst, 0, sizeof(dst));
    assert (result == alpha_len);
    assert (dst [alpha_len + 0] == 0);
    assert (dst [alpha_len + 1] == '\xFF');
    assert (memcmp (dst, alphabets, alpha_len) == 0);

    memset (dst, 0xFF, sizeof(dst));
    dst [0] = 'A';
    dst [1] = 'B';
    dst [2] = 'C';
    dst [3] = 'D';
    dst [4] = 0;
    result = strlcat (dst, alphabets, 3);
    assert (result == 4);
    assert (dst [4] == 0);
    assert (dst [5] == '\xFF');
    assert (memcmp (dst, "ABCD", 4) == 0);

    memset (dst, 0xFF, sizeof(dst));
    dst [0] = 'A';
    dst [1] = 'B';
    dst [2] = 'C';
    dst [3] = 'D';
    dst [4] = 0;
    result = strlcat (dst, alphabets, 5);
    assert (result == 4);
    assert (dst [4] == 0);
    assert (dst [5] == '\xFF');
    assert (memcmp (dst, "ABCD", 4) == 0);

    memset (dst, 0xFF, sizeof(dst));
    dst [0] = 'A';
    dst [1] = 'B';
    dst [2] = 'C';
    dst [3] = 'D';
    dst [4] = 0;
    result = strlcat (dst, alphabets, alpha_len + 1);
    assert (result == alpha_len);
    assert (dst [alpha_len + 0] == 0);
    assert (dst [alpha_len + 1] == '\xFF');
    assert (memcmp (dst, "ABCD", 4) == 0);
    assert (memcmp (dst + 4, alphabets, alpha_len - 4) == 0);

    memset (dst, 0xFF, sizeof(dst));
    dst [0] = 'A';
    dst [1] = 'B';
    dst [2] = 'C';
    dst [3] = 'D';
    dst [4] = 0;
    result = strlcat (dst, alphabets, sizeof (dst));
    assert (result == alpha_len + 4);
    assert (dst [4 + alpha_len + 0] == 0);
    assert (dst [4 + alpha_len + 1] == '\xFF');
    assert (memcmp (dst, "ABCD", 4) == 0);
    assert (memcmp (dst + 4, alphabets, alpha_len) == 0);

}

void	test_strconcat () {
    char	dst [256];
    const char	alphabets [] = "abcdefghijklmnopqrstuvwxyz";
    size_t	alpha_len = strlen (alphabets);
    size_t	result;

    result = strconcat (0, sizeof(dst), 0);
    assert (result == 0);
    result = strconcat (dst, 0, 0);
    assert (result == 0);

    memset (dst, 0xFF, sizeof (dst));
    result = strconcat (dst, sizeof (dst), 1, "");
    assert (result == 0);
    assert (dst [0] == 0);
    assert (dst [1] == '\xFF');

    memset (dst, 0xFF, sizeof (dst));
    result = strconcat (dst, sizeof (dst), 2, ".", alphabets);
    assert (result == 1 + alpha_len);
    assert (dst [1 + alpha_len + 0] == 0);
    assert (dst [1 + alpha_len + 1] == '\xFF');
    assert (dst [0] == '.') ;
    assert (memcmp (dst + 1, alphabets, alpha_len) == 0);

    memset (dst, 0xFF, sizeof (dst));
    result = strconcat (dst, sizeof (dst), 2, "", alphabets);
    assert (result == alpha_len);
    assert (dst [alpha_len + 0] == 0);
    assert (dst [alpha_len + 1] == '\xFF');
    assert (memcmp (dst, alphabets, alpha_len) == 0);

    memset (dst, 0xFF, sizeof(dst));
    result = strconcat (dst, sizeof(dst), 1, alphabets);
    assert (result == alpha_len);
    assert (dst [alpha_len + 0] == 0);
    assert (dst [alpha_len + 1] == '\xFF');
    assert (memcmp (dst, alphabets, alpha_len) == 0);

    memset (dst, 0xFF, sizeof(dst));
    result = strconcat (dst, alpha_len, 1, alphabets);
    assert (result = alpha_len - 1);
    assert (dst [alpha_len - 1] == 0);
    assert (dst [alpha_len - 0] == '\xFF');
    assert (memcmp (dst, alphabets, alpha_len - 1) == 0);

    memset (dst, 0xFF, sizeof(dst));
    result = strconcat (dst, 2 * alpha_len, 2, alphabets, alphabets);
    assert (result = 2 * alpha_len - 1);
    assert (dst [2 * alpha_len - 1] == 0);
    assert (dst [2 * alpha_len - 0] == '\xFF');
    assert (memcmp (dst, alphabets, alpha_len) == 0);
    assert (memcmp (dst + alpha_len, alphabets, alpha_len - 1) == 0);

    memset (dst, 0xFF, sizeof(dst));
    result = strconcat (dst, alpha_len + 1, 1, alphabets);
    assert (result = alpha_len);
    assert (dst [alpha_len + 0] == 0);
    assert (dst [alpha_len + 1] == '\xFF');
    assert (memcmp (dst, alphabets, alpha_len) == 0);

    memset (dst, 0xFF, sizeof(dst));
    result = strconcat (dst, 2 * alpha_len + 1, 2, alphabets, alphabets);
    assert (result = 2 * alpha_len);
    assert (dst [2 * alpha_len + 0] == 0);
    assert (dst [2 * alpha_len + 1] == '\xFF');
    assert (memcmp (dst, alphabets, alpha_len) == 0);
    assert (memcmp (dst + alpha_len, alphabets, alpha_len) == 0);
}

/*
 * [END OF FILE]
 */

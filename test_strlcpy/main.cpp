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

/*
 * main.c: Tests for strlcpy & strlcat.
 *
 * Copyright 2012 Masashi Fujita
 *
 * License: Ms-Pl (http://www.opensource.org/licenses/ms-pl.html)
 */
#include "common.h"

static void	test_strlcpy () {
    char	dst [256];
    const char	alphabets [] = "abcdefghijklmnopqrstuvwxyz";
    size_t	alpha_len = strlen (alphabets);
    size_t	result;

    memset (dst, 0xFF, sizeof(dst));
    result = strlcpy (dst, alphabets, 0);
    assert (result == 0);
    assert (dst [0] == '\xFF');

    memset (dst, 0xFF, sizeof(dst));
    result = strlcpy (0, alphabets, sizeof(dst));
    assert (result == 0);

    memset (dst, 0xFF, sizeof(dst));
    result = strlcpy (dst, 0, sizeof(dst));
    assert (result == 0);
    assert (dst [0] == 0);

    memset (dst, 0xFF, sizeof(dst));

    result = strlcpy (dst, alphabets, 4);
    assert (result == 3);
    assert (dst [3] == 0);
    assert (dst [4] == '\xFF');
    assert (memcmp (dst, alphabets, 3) == 0);

    memset (dst, 0xFF, sizeof(dst));

    result = strlcpy (dst, alphabets, sizeof(dst));
    assert (result == alpha_len);
    assert (dst [alpha_len + 0] == 0);
    assert (dst [alpha_len + 1] = '\xFF');
    assert (memcmp (dst, alphabets, alpha_len) == 0);
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

int	main (int argc, char ** argv) {
    printf ("Testing strlcpy.");
    test_strlcpy ();
    printf ("Testing strlcat");
    test_strlcat ();
    printf ("Testing strconcat");
    test_strconcat ();
    printf ("All tests are passed.") ;
    return 0;
}

/*
 * [END OF FILE]
 */

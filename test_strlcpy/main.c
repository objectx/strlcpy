/*
 * main.c:
 *
 * Author(s): objectx
 */

#include "common.h"

static void	test_strlcpy () {
    char	dst [256];
    const char	alphabets [] = "abcdefghijklmnopqrstuvwxyz";
    size_t	alpha_len = strlen (alphabets);
    size_t	result;

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

int	main (int argc, char ** argv) {
    printf ("Testing strlcpy.") ;
    test_strlcpy ();
    printf ("All tests are passed.") ;
    return 0;
}

/*
 * [END OF FILE]
 */

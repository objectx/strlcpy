/*
 * main.cxx:
 *
 * Author(s): objectx
 */

#include "common.h"
#include "FixedSizeStringBuilder.h"

static void	test () {
    {
	char	buf [256];
	memset (buf, 0xFF, sizeof (buf));
	FixedSizeStringBuilder	sb (buf, sizeof (buf));

	sb.Append ('a');
	assert (sb.GetLength () == 1);
	assert (buf [0] == 'a');
	assert (buf [1] == 0);
    }
    {
	char	buf [256];
	const char *	str = "abc";
	size_t	str_len = strlen (str);
	memset (buf, 0xFF, sizeof (buf));
	FixedSizeStringBuilder	sb (buf, sizeof (buf));

	sb.Append (str);
	assert (sb.GetLength () == str_len);
	assert (buf [str_len] == 0);
	assert (memcmp (buf, str, str_len) == 0);
    }
    {
	char	buf [16];
	const char *	str = "abcdefghijklmnopqrstuvwxyz";
	size_t	str_len = strlen (str);

	memset (buf, 0xFF, sizeof (buf));
	FixedSizeStringBuilder	sb (buf, sizeof (buf));

	sb.Append (str);
	assert (sb.GetLength () == (sizeof (buf) - 1));
	assert (buf [sizeof (buf) - 1] == 0);
	assert (memcmp (buf, str, sizeof (buf) - 1) == 0);
    }
    {
	char	buf [10];
	const char *	str = "abcde";
	size_t	str_len = strlen (str);

	memset (buf, 0xFF, sizeof (buf));
	FixedSizeStringBuilder	sb (buf, sizeof (buf));

	sb.Append (str).Append (str);
	assert (sb.GetLength () == (sizeof (buf) - 1));
	assert (buf [sizeof (buf) - 1] == 0);
	assert (memcmp (buf, "abcdeabcde", sizeof (buf) - 1) == 0);
    }
    {
	char	buf [10];
	const char *	str = "abcde";
	size_t	str_len = strlen (str);

	memset (buf, 0xFF, sizeof (buf));
	FixedSizeStringBuilder	sb (buf, sizeof (buf));

	sb.Append (str).Append (str);
	assert (sb.GetLength () == (sizeof (buf) - 1));
	assert (buf [sizeof (buf) - 1] == 0);
	assert (memcmp (buf, "abcdeabcde", sizeof (buf) - 1) == 0);
    }
    {
	char	buf [11];
	memset (buf, 0xFF, sizeof (buf));
	FixedSizeStringBuilder	sb (buf, sizeof (buf));

	const char *	str = "abcdefghij";
	sb.AppendWithFormat ("%s", str);
	assert (sb.GetLength () == (sizeof (buf) - 1));
	assert (buf [sizeof (buf) - 1] == 0);
	assert (memcmp (buf, str, sizeof (buf) - 1) == 0);
    }
    {
	char	buf [10];
	memset (buf, 0xFF, sizeof (buf));
	FixedSizeStringBuilder	sb (buf, sizeof (buf));

	const char *	str = "abcdefghij";
	sb.AppendWithFormat ("%s", str);
	assert (sb.GetLength () == (sizeof (buf) - 1));
	assert (buf [sizeof (buf) - 1] == 0);
	assert (memcmp (buf, str, sizeof (buf) - 1) == 0);
    }
}

int	main (int argc, char **argv) {
    std::cout << "Testing FixedSizeStringBuilder." << std::endl ;
    test ();
    return 0 ;
}

/*
 * [END OF FILE]
 */


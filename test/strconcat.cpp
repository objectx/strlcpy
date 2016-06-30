
#include "common.h"
#include "catch/catch.hpp"

SCENARIO ("strconcat", "[strconcat]") {
    REQUIRE (strconcat (nullptr, 0) == -E2BIG) ;

    std::array<char, 256>   dst ;
    const char alphabets [] = "abcdefghijklmnopqrstuvwxyz" ;
    size_t alpha_len = strlen (alphabets) ;

    GIVEN ("\xFF filled buffer") {
        dst.fill (0xFF) ;
        WHEN ("Call with empty string") {
            auto result = strconcat (dst.data (), dst.size (), "") ;
        THEN ("Should return empty string") {
            REQUIRE (result == 0) ;
            REQUIRE (dst [0] == 0) ;
            REQUIRE (dst [1] == '\xFF') ;
        }}
        WHEN ("Call with \"\" and alphabets") {
            auto result = strconcat (dst.data (), dst.size (), "", alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == alpha_len) ;
            REQUIRE (dst [26 + 0] == 0) ;
            REQUIRE (dst [26 + 1] == '\xFF') ;
            REQUIRE (memcmp (dst.data (), alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with \"\" and alphabets (use `std::string`)") {
            auto result = strconcat (dst.data (), dst.size (), "", std::string { alphabets }) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == alpha_len) ;
            REQUIRE (dst [26 + 0] == 0) ;
            REQUIRE (dst [26 + 1] == '\xFF') ;
            REQUIRE (memcmp (dst.data (), alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with \"abc\" \"def\" \"ghi\"") {
            auto result = strconcat (dst.data (), dst.size (), "abc", std::string { "def" }, "ghi") ;
            THEN ("Should return \"abcdefghi\"") {
                REQUIRE (result == 9) ;
                REQUIRE (dst [9 + 0] == 0) ;
                REQUIRE (dst [9 + 1] == '\xFF') ;
                REQUIRE (memcmp (dst.data (), "abcdefghi", 9) == 0) ;
            }
        }
    }
}

#ifdef notdef
SCENARIO ("strconcat", "[strconcat]") {
    char dst [256] ;
    const char  alphabets [] = "abcdefghijklmnopqrstuvwxyz";
    size_t  alpha_len = strlen (alphabets);
    size_t  result;

    GIVEN ("\xFF filled buffer") {
        memset (dst, 0xFF, sizeof (dst)) ;

        WHEN ("Call with null destination") {
            result = strconcat (0, sizeof (dst), 0) ;
        THEN ("Should return with 0") {
            REQUIRE (result == 0) ;
        }}
        WHEN ("Destination size is 0") {
            result = strconcat (dst, 0, 0) ;
        THEN ("Should return with 0") {
            REQUIRE (result == 0) ;
        }}
        WHEN ("Call with empty string") {
            result = strconcat (dst, sizeof (dst), 1, "") ;
        THEN ("Should return empty string") {
            REQUIRE (result == 0) ;
            REQUIRE (dst [0] == 0) ;
            REQUIRE (dst [1] == '\xFF') ;
        }}
        WHEN ("Call with \"\" and alphabets") {
            result = strconcat (dst, sizeof (dst), 2, "", alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == alpha_len) ;
            REQUIRE (dst [26 + 0] == 0) ;
            REQUIRE (dst [26 + 1] == '\xFF') ;
            REQUIRE (memcmp (dst, alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with \".\" and alphabets") {
            result = strconcat (dst, sizeof (dst), 2, ".", alphabets) ;
        THEN ("Should return \".abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == (1 + alpha_len)) ;
            REQUIRE (dst [1 + 26 + 0] == 0) ;
            REQUIRE (dst [1 + 26 + 1] == '\xFF') ;
            REQUIRE (dst [0] == '.') ;
            REQUIRE (memcmp (dst + 1, alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with alphabets") {
            result = strconcat (dst, sizeof (dst), 1, alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == alpha_len) ;
            REQUIRE (dst [alpha_len + 0] == 0) ;
            REQUIRE (dst [alpha_len + 1] == '\xFF') ;
            REQUIRE (memcmp (dst, alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with alphabets (destination size == 27)") {
            result = strconcat (dst, alpha_len + 1, 1, alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == alpha_len) ;
            REQUIRE (dst [alpha_len + 0] == 0) ;
            REQUIRE (dst [alpha_len + 1] == '\xFF') ;
            REQUIRE (memcmp (dst, alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with 2 alphabets (destination size == 53)") {
            result = strconcat (dst, 2 * alpha_len + 1, 2, alphabets, alphabets) ;
        THEN ("Should return abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz") {
            REQUIRE (result == (2 * alpha_len)) ;
            REQUIRE (dst [2 * alpha_len + 0] == 0) ;
            REQUIRE (dst [2 * alpha_len + 1] == '\xFF') ;
            REQUIRE (memcmp (dst, alphabets, alpha_len) == 0) ;
            REQUIRE (memcmp (dst + alpha_len, alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with alphabets (destination size == 26)") {
            result = strconcat (dst, alpha_len, 1, alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxy\"") {
            REQUIRE (result == alpha_len - 1) ;
            REQUIRE (dst [alpha_len - 1] == 0) ;
            REQUIRE (dst [alpha_len - 0] == '\xFF') ;
            REQUIRE (memcmp (dst, alphabets, alpha_len - 1) == 0) ;
        }}
        WHEN ("Call with 2 alphabets (destination size == 52)") {
            result = strconcat (dst, 2 * alpha_len, 2, alphabets, alphabets) ;
        THEN ("Should return abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxy") {
            REQUIRE (result == (2 * alpha_len - 1)) ;
            REQUIRE (dst [2 * alpha_len - 1] == 0) ;
            REQUIRE (dst [2 * alpha_len - 0] == '\xFF') ;
            REQUIRE (memcmp (dst, alphabets, alpha_len) == 0) ;
            REQUIRE (memcmp (dst + alpha_len, alphabets, alpha_len - 1) == 0) ;
        }}
    }
}
#endif


#include "common.h"
#include "catch/catch.hpp"

SCENARIO ("Pass `const char *`", "[strconcat]") {
    REQUIRE (strconcat (nullptr, 0) == -E2BIG) ;

    char fill_char = '@' ;
    std::array<char, 256>   dst ;

    const char alphabets [] = "abcdefghijklmnopqrstuvwxyz" ;
    size_t alpha_len = strlen (alphabets) ;

    GIVEN ("'@' filled buffer") {

        dst.fill (fill_char) ;

        WHEN ("Call with empty string") {
            auto result = strconcat (dst, "") ;
        THEN ("Should return empty string") {
            REQUIRE (result == 0) ;
            REQUIRE (dst [0] == 0) ;
            REQUIRE (dst [1] == fill_char) ;
        }}
        WHEN ("Call with \"\" and alphabets") {
            auto result = strconcat (dst, "", alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == alpha_len) ;
            REQUIRE (dst [26 + 0] == 0) ;
            REQUIRE (dst [26 + 1] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with \".\" and alphabets") {
            auto result = strconcat (dst, ".", alphabets) ;
        THEN ("Should return \".abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == (1 + alpha_len)) ;
            REQUIRE (dst [1 + 26 + 0] == 0) ;
            REQUIRE (dst [1 + 26 + 1] == fill_char) ;
            REQUIRE (dst [0] == '.') ;
            REQUIRE (memcmp (dst.data () + 1, alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with alphabets") {
            auto result = strconcat (dst, alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == alpha_len) ;
            REQUIRE (dst [alpha_len + 0] == 0) ;
            REQUIRE (dst [alpha_len + 1] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with alphabets (destination size == 27)") {
            auto result = strconcat (dst.data (), alpha_len + 1, alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == alpha_len) ;
            REQUIRE (dst [alpha_len + 0] == 0) ;
            REQUIRE (dst [alpha_len + 1] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with 2 alphabets (destination size == 53)") {
            auto result = strconcat (dst, alphabets, alphabets) ;
        THEN ("Should return abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz") {
            REQUIRE (result == (2 * alpha_len)) ;
            REQUIRE (dst [2 * alpha_len + 0] == 0) ;
            REQUIRE (dst [2 * alpha_len + 1] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alphabets, alpha_len) == 0) ;
            REQUIRE (memcmp (dst.data () + alpha_len, alphabets, alpha_len) == 0) ;
        }}
        WHEN ("Call with alphabets (destination size == 26)") {
            auto result = strconcat (dst.data (), alpha_len, alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxy\"") {
            REQUIRE (result == -E2BIG) ;
            REQUIRE (dst [alpha_len - 1] == 0) ;
            REQUIRE (dst [alpha_len - 0] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alphabets, alpha_len - 1) == 0) ;
        }}
        WHEN ("Call with 2 alphabets (destination size == 52)") {
            auto result = strconcat (dst.data (), 2 * alpha_len, alphabets, alphabets) ;
        THEN ("Should return abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxy") {
            REQUIRE (result == -E2BIG) ;
            REQUIRE (dst [2 * alpha_len - 1] == 0) ;
            REQUIRE (dst [2 * alpha_len - 0] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alphabets, alpha_len) == 0) ;
            REQUIRE (memcmp (dst.data () + alpha_len, alphabets, alpha_len - 1) == 0) ;
        }}
    }
}

SCENARIO ("Pass `std::string`", "[strconcat]") {
    char fill_char = '@' ;
    std::array<char, 256>   dst ;

    const std::string alphabets { "abcdefghijklmnopqrstuvwxyz" };
    const auto        alpha_size = alphabets.size ();
    const auto        alpha_str  = alphabets.c_str ();

    const std::string emptystr ;

    GIVEN ("'@' filled buffer") {

        dst.fill (fill_char) ;

        WHEN ("Call with empty string") {
            auto result = strconcat (dst, emptystr) ;
            THEN ("Should return empty string") {
            REQUIRE (result == 0) ;
            REQUIRE (dst [0] == 0) ;
            REQUIRE (dst [1] == fill_char) ;
        }}
        WHEN ("Call with \"\" and alphabets") {
            auto result = strconcat (dst, emptystr, alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == alpha_size) ;
            REQUIRE (dst [alpha_size + 0] == 0) ;
            REQUIRE (dst [alpha_size + 1] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alpha_str, alpha_size) == 0) ;
        }}
        WHEN ("Call with \".\" and alphabets") {
            auto result = strconcat (dst, ".", alphabets) ;
        THEN ("Should return \".abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == (1 + alpha_size)) ;
            REQUIRE (dst [1 + alpha_size + 0] == 0) ;
            REQUIRE (dst [1 + alpha_size + 1] == fill_char) ;
            REQUIRE (dst [0] == '.') ;
            REQUIRE (memcmp (dst.data () + 1, alpha_str, alpha_size) == 0) ;
        }}
        WHEN ("Call with alphabets") {
            auto result = strconcat (dst, alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == alpha_size) ;
            REQUIRE (dst [alpha_size + 0] == 0) ;
            REQUIRE (dst [alpha_size + 1] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alpha_str, alpha_size) == 0) ;
        }}
        WHEN ("Call with alphabets (destination size == 27)") {
            auto result = strconcat (dst.data (), alpha_size + 1, alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxyz\"") {
            REQUIRE (result == alpha_size) ;
            REQUIRE (dst [alpha_size + 0] == 0) ;
            REQUIRE (dst [alpha_size + 1] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alpha_str, alpha_size) == 0) ;
        }}
        WHEN ("Call with 2 alphabets (destination size == 53)") {
            auto result = strconcat (dst, alphabets, alphabets) ;
        THEN ("Should return abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz") {
            REQUIRE (result == (2 * alpha_size)) ;
            REQUIRE (dst [2 * alpha_size + 0] == 0) ;
            REQUIRE (dst [2 * alpha_size + 1] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alpha_str, alpha_size) == 0) ;
            REQUIRE (memcmp (dst.data () + alpha_size, alpha_str, alpha_size) == 0) ;
        }}
        WHEN ("Call with alphabets (destination size == 26)") {
            auto result = strconcat (dst.data (), alpha_size, alphabets) ;
        THEN ("Should return \"abcdefghijklmnopqrstuvwxy\"") {
            REQUIRE (result == -E2BIG) ;
            REQUIRE (dst [alpha_size - 1] == 0) ;
            REQUIRE (dst [alpha_size - 0] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alpha_str, alpha_size - 1) == 0) ;
        }}
        WHEN ("Call with 2 alphabets (destination size == 52)") {
            auto result = strconcat (dst.data (), 2 * alpha_size, alphabets, alphabets) ;
        THEN ("Should return abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxy") {
            REQUIRE (result == -E2BIG) ;
            REQUIRE (dst [2 * alpha_size - 1] == 0) ;
            REQUIRE (dst [2 * alpha_size - 0] == fill_char) ;
            REQUIRE (memcmp (dst.data (), alpha_str, alpha_size) == 0) ;
            REQUIRE (memcmp (dst.data () + alpha_size, alpha_str, alpha_size - 1) == 0) ;
        }}
    }
}

SCENARIO ("Mix `std::string` and `const char *`", "[strconcat]") {
    char fill_char = '@' ;
    std::array<char, 256>   dst ;

    GIVEN ("'@' filled buffer") {
        dst.fill (fill_char) ;
        WHEN ("Call with \"abc\" \"def\" \"ghi\"") {
            auto result = strconcat (dst.data (), dst.size (), "abc", std::string { "def" }, "ghi") ;
        THEN ("Should return \"abcdefghi\"") {
            REQUIRE (result == 9) ;
            REQUIRE (dst [9 + 0] == 0) ;
            REQUIRE (dst [9 + 1] == fill_char) ;
            REQUIRE (memcmp (dst.data (), "abcdefghi", 9) == 0) ;
        }}
    }
}

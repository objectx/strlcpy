
#include "common.h"
#include "catch.hpp"

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
        THEN ("Should return with 0") {
            REQUIRE (result == 0) ;
        AND_THEN ("dst [0] == 0") {
            REQUIRE (dst [0] == 0) ;
        AND_THEN ("dst [1] == '\\xFF'") {
            REQUIRE (dst [1] == '\xFF') ;
        }}}}
        WHEN ("Call with \".\" and alphabets") {
            result = strconcat (dst, sizeof (dst), 2, ".", alphabets) ;
        THEN ("Should return with 27") {
            REQUIRE (result == (1 + alpha_len)) ;
        AND_THEN ("dst [1 + 26 + 0] == 0") {
            REQUIRE (dst [1 + 26 + 0] == 0) ;
        AND_THEN ("dst [1 + 26 + 1] == '\\xFF'") {
            REQUIRE (dst [1 + 26 + 1] == '\xFF') ;
        AND_THEN ("dst [0] == '.'") {
            REQUIRE (dst [0] == '.') ;
        AND_THEN ("dst [1..27] should equal to alphabets") {
            REQUIRE (memcmp (dst + 1, alphabets, alpha_len) == 0) ;
        }}}}}}
    }
}

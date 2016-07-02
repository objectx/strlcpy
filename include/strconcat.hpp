/*
 * strconcat.hpp: Concatenate strings.
 *
 * Copyright (c) 2016 Masahi Fujita
 */
#pragma once
#ifndef strconcat_hpp__4029f4e5d9284f11a3787353984d4253
#define strconcat_hpp__4029f4e5d9284f11a3787353984d4253 1

#include <sys/types.h>
#include <stdint.h>
#include <cassert>
#include <string>
#include <cerrno>
#include <array>

namespace strconcat_internal {
    /**
     * Holds currently constructing string.
     */
    class buffer final {
    public:
        using size_type = int64_t ;
    private:
        char *  buf_ = nullptr ;
        char *  p_   = nullptr ;
        char *  end_ = nullptr ;
    public:
        buffer (char *buf, size_t sz)
                : buf_ { buf }
                , p_ { buf }
                , end_ { buf + sz - 1 } {
            /* NO-OP */
        }

        size_t remain () const {
            return static_cast<size_t> (end_ - p_) ;
        }

        size_type concat () {
            *p_ = 0 ;
            return static_cast<size_type> (p_ - buf_) ;
        }

        bool append (const char *s, size_t sz) {
            auto room = remain () ;
            if (room < sz) {
                // Truncation occur!
                memcpy (p_, s, room) ;
                p_ += room ;
                *p_ = 0 ;
                return false ;
            }
            memcpy (p_, s, sz) ;
            p_ += sz ;
            return true ;
        }

        template <typename ...ARGS_>
            size_type concat_helper (size_t l, const char *s, ARGS_ ...args) {
                if (! append (s, l)) {
                    return static_cast<size_type> (-E2BIG) ;
                }
                return concat (args...) ;
            }

        template <typename ...ARGS_>
            size_type concat (const char *s, ARGS_ ...args) {
                size_t l = strlen (s) ;
                return concat_helper (l, s, args...) ;
            }

        template <typename Alloc_, typename ...ARGS_>
            size_type concat (const std::basic_string<char, std::char_traits<char>, Alloc_> &s, ARGS_ ...args) {
                return concat_helper (static_cast<size_t> (s.size ()), s.data (), args...) ;
            }
    } ;
}

/**
 * Concatenates supplied strings.
 *
 * Both `std::string` and `const char *` was allowed as sources.
 * '\0' termination was guarranteed.
 *
 * @param [out] buf Result string constructed here
 * @param bufsize Maximum string length to build
 * @param args Source strings
 * @return Length of the constructed string if success, otherwise return `-E2BIG`
 */
template <typename ...ARGS_>
    int_fast64_t strconcat (char *buf, size_t bufsize, ARGS_ ...args) {
        if (buf == nullptr || bufsize == 0) {
            return static_cast<int64_t> (-E2BIG) ;
        }
        return strconcat_internal::buffer { buf, bufsize }.concat (args...) ;
    }

/**
 * Concatenates supplied strings
 *
 * @param [out] dst Result string constructed here
 * @param args Source strings
 * @return Length of the constructed string if success, otherwise return `-E2BIG`
 */
template <size_t N_, typename ...ARGS_>
    int_fast64_t strconcat (std::array<char, N_> &dst, ARGS_ ...args) {
        return strconcat_internal::buffer { dst.data (), dst.size () }.concat (args...) ;
    }

#endif /* strconcat_hpp__4029f4e5d9284f11a3787353984d4253 */

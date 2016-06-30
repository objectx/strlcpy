//
// Copyright (c) 2016 Polyphony Digital Inc. All rights reserved.
//
#pragma once
#ifndef strconcat_hpp__4029f4e5d9284f11a3787353984d4253
#define strconcat_hpp__4029f4e5d9284f11a3787353984d4253 1

#include <sys/types.h>
#include <stdint.h>
#include <cassert>
#include <string>
#include <cerrno>

namespace strconcat_internal {
    /**
     * Holds currently constructing string.
     */
    struct buffer {
        char *  buf_ = nullptr ;
        char *  p_   = nullptr ;
        char *  end_ = nullptr ;

        buffer (char *buf, size_t sz)
                : buf_ { buf }
                , p_ { buf }
                , end_ { buf + sz - 1 } {
            /* NO-OP */
        }

        size_t remain () const {
            return static_cast<size_t> (end_ - p_) ;
        }

        ssize_t concat () {
            assert (p_ <= end_) ;
            *p_ = 0 ;
            return static_cast<ssize_t> (p_ - buf_) ;
        }

        // template <typename ...ARGS_> ssize_t concat (const char *s, ARGS_...args) ;
        // template <typename ...ARGS_> ssize_t concat (const std::string &s, ARGS_...args) ;

        template <typename ...ARGS_>
            ssize_t concat_helper (size_t l, const char *s, ARGS_...args) {
                auto room = remain () ;
                if (room < l) {
                    // Truncation occur
                    memcpy (p_, s, room) ;
                    p_ += room ;
                    *p_ = 0 ;
                    assert (p_ <= end_) ;
                    return static_cast<ssize_t> (-E2BIG) ;
                }
                memcpy (p_, s, l) ;
                p_ += l ;
                assert (p_ <= end_) ;
                return concat (args...) ;
            }

        template <typename ...ARGS_>
            ssize_t concat (const char *s, ARGS_...args) {
                size_t l = strlen (s) ;
                return concat_helper (l, s, args...) ;
            }

        template <typename ...ARGS_>
            ssize_t concat (const std::string &s, ARGS_...args) {
                return concat_helper (static_cast<size_t> (s.size ()), s.c_str (), args...) ;
            }
    } ;

}

/**
 * Concatenate supplied strings.
 *
 * Both `std::string` and `const char *` was allowed as sources.
 * '\0' termination was guarranteed.
 *
 * @param [out] buf Result string constructed here
 * @param bufsize Maximum string length to build
 * @param args Source strings
 * @return Length of constructed string
 */
template <typename ...ARGS_>
    ssize_t strconcat (char *buf, size_t bufsize, ARGS_ ...args) {
        if (buf == nullptr || bufsize == 0) {
            return static_cast<ssize_t> (-E2BIG) ;
        }
        return strconcat_internal::buffer { buf, bufsize }.concat (args...) ;
    }
#endif /* strconcat_hpp__4029f4e5d9284f11a3787353984d4253 */

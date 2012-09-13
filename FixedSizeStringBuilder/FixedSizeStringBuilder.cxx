/*
 * FixedSizeStringBuilder.cxx:
 *
 * Author(s): objectx
 */

#include <algorithm>
#include "FixedSizeStringBuilder.h"

FixedSizeStringBuilder &	FixedSizeStringBuilder::Append (char ch) {
    if ((length_ + 1) <= limit_) {
	buffer_ [length_ + 0] = static_cast<int8_t> (ch);
	buffer_ [length_ + 1] = 0;
	++length_;
    }
    return *this ;
}

FixedSizeStringBuilder &	FixedSizeStringBuilder::Append (const char * s) {
    if (s != 0) {
	int_fast32_t	len = std::min (static_cast<int_fast32_t> (strlen (s)),
					static_cast<int_fast32_t> (limit_ - length_)) ;
	memcpy (buffer_ + length_, s, len);
	length_ += len ;
	buffer_ [length_] = 0;
    }
    return *this ;
}

FixedSizeStringBuilder &	FixedSizeStringBuilder::Append (const void * s, size_t length) {
    if (s != 0 && 0 < length) {
	int_fast32_t	len = std::min (static_cast<int_fast32_t> (length),
					static_cast<int_fast32_t> (limit_ - length_));
	memcpy (buffer_ + length_, s, len);
	length_ += len;
	buffer_ [length_] = 0;
    }
    return *this ;
}

FixedSizeStringBuilder &	FixedSizeStringBuilder::AppendWithFormatV (const char * format, va_list ap) {
    size_t	room = limit_ + 1 - length_ ;
    size_t	len = vsnprintf (reinterpret_cast<char *> (buffer_ + length_), room, format, ap);
    if (len < 0 || room < (len + 1)) {
	// Truncation occured.
	length_ = limit_ ;
    }
    else {
	length_ += len ;
    }
    buffer_ [length_] = 0 ;
    return *this ;
}


FixedSizeStringBuilder &	FixedSizeStringBuilder::AppendWithFormat (const char *format, ...) {
    va_list	ap ;
    va_start (ap, format);
    AppendWithFormatV (format, ap);
    va_end (ap);
    return *this ;
}

/*
 * [END OF FILE]
 */


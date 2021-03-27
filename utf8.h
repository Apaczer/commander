#ifndef UTF8_H_
#define UTF8_H_

namespace utf8 {

inline size_t codePointLen(const char *src)
{
    return "\1\1\1\1\1\1\1\1\1\1\1\1\2\2\3\4"[static_cast<unsigned char>(*src)
        >> 4];
}

inline bool isTrailByte(char x) { return static_cast<signed char>(x) < -0x40; }

} // namespace utf8

#endif // UTF8_H_

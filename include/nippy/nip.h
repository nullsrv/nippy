// The MIT License
// ===============
//
// Copyright (c) 2026 nullsrv
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// SPDX-License-Identifier: MIT


/**
 * @file nip.h
 * Ini parser
 */
#ifndef NIP_H
#define NIP_H

#include <stdbool.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @defgroup version Version information.
 * @{
 */
#define NIP_VERSION_MAJOR       1                       ///< Major version constant.
#define NIP_VERSION_MINOR       0                       ///< Minor version constant.
#define NIP_VERSION_REVISON     0                       ///< Revision version constant.
#define NIP_VERSION             0x0100                  ///< Version number constant MNrr.
#define NIP_VERSION_STRING      "1.0.0"                 ///< Version string.
/** @} */

/**
 * @brief   Api linkage specifier.
 * @details If you want to use this library as DLL, define **NIP_DLL** before
 *          including nip.h
 */
#if defined(NIP_DLL) || defined(NIP_USE_DLL)
    #if defined(NIP_EXPORTS)
        #define NIP_API extern __declspec(dllexport)
    #else
        #define NIP_API extern __declspec(dllimport)
    #endif // NIP_EXPORTS
#else
    #define NIP_API extern
#endif // NIP_DLL

/**
 * @defgroup error Error checking macros.
 * @{
 */
#define NIP_SUCCEEDED(_err)     (_err >= 0)             ///< Check if result succeeded.
#define NIP_FAILED(_err)        (_err < 0)              ///< Check if result failed.
/** @} */

/**
 * @defgroup macros Helper macros for values.
 * @{
 */
#define NIP_VALUE_INT8(_ptr)                {{.i8  = _ptr}, NIP_VALUE_TYPE_INT8}
#define NIP_VALUE_INT16(_ptr)               {{.i16 = _ptr}, NIP_VALUE_TYPE_INT16}
#define NIP_VALUE_INT32(_ptr)               {{.i32 = _ptr}, NIP_VALUE_TYPE_INT32}
#define NIP_VALUE_INT64(_ptr)               {{.i64 = _ptr}, NIP_VALUE_TYPE_INT64}
#define NIP_VALUE_UINT8(_ptr)               {{.u8  = _ptr}, NIP_VALUE_TYPE_UINT8}
#define NIP_VALUE_UINT16(_ptr)              {{.u16 = _ptr}, NIP_VALUE_TYPE_UINT16}
#define NIP_VALUE_UINT32(_ptr)              {{.u32 = _ptr}, NIP_VALUE_TYPE_UINT32}
#define NIP_VALUE_UINT64(_ptr)              {{.u64 = _ptr}, NIP_VALUE_TYPE_UINT64}
#define NIP_VALUE_BOOL8(_ptr)               {{.i8  = _ptr}, NIP_VALUE_TYPE_BOOL8}
#define NIP_VALUE_BOOL16(_ptr)              {{.i16 = _ptr}, NIP_VALUE_TYPE_BOOL16}
#define NIP_VALUE_BOOL32(_ptr)              {{.i32 = _ptr}, NIP_VALUE_TYPE_BOOL32}
#define NIP_VALUE_BOOL64(_ptr)              {{.i64 = _ptr}, NIP_VALUE_TYPE_BOOL64}
#define NIP_VALUE_FLOAT32(_ptr)             {{.f32 = _ptr}, NIP_VALUE_TYPE_FLOAT32}
#define NIP_VALUE_FLOAT64(_ptr)             {{.f64 = _ptr}, NIP_VALUE_TYPE_FLOAT64}
#define NIP_VALUE_BOOL(_ptr)                {{.b   = _ptr}, NIP_VALUE_TYPE_BOOL}
#define NIP_VALUE_STRING(_ptr)              {{.str = _ptr}, NIP_VALUE_TYPE_STRING}
#define NIP_VALUE_CHAR_BUFFER(_ptr, _size)  {{.cb  = _ptr}, NIP_VALUE_TYPE_CHAR_BUFFER, {.buf_size = _size}}
#define NIP_VALUE_CUSTOM(_ptr)              {{.raw = _ptr}, NIP_VALUE_TYPE_CUSTOM}
/** @} */

/**
 * @defgroup macros Helper macros for default values.
 * @{
 */
#define NIP_DEF_VALUE_INT8(_val)            {{.i8  = _val}, NIP_VALUE_TYPE_INT8}
#define NIP_DEF_VALUE_INT16(_val)           {{.i16 = _val}, NIP_VALUE_TYPE_INT16}
#define NIP_DEF_VALUE_INT32(_val)           {{.i32 = _val}, NIP_VALUE_TYPE_INT32}
#define NIP_DEF_VALUE_INT64(_val)           {{.i64 = _val}, NIP_VALUE_TYPE_INT64}
#define NIP_DEF_VALUE_UINT8(_val)           {{.u8  = _val}, NIP_VALUE_TYPE_UINT8}
#define NIP_DEF_VALUE_UINT16(_val)          {{.u16 = _val}, NIP_VALUE_TYPE_UINT16}
#define NIP_DEF_VALUE_UINT32(_val)          {{.u32 = _val}, NIP_VALUE_TYPE_UINT32}
#define NIP_DEF_VALUE_UINT64(_val)          {{.u64 = _val}, NIP_VALUE_TYPE_UINT64}
#define NIP_DEF_VALUE_BOOL8(_val)           {{.i8  = _val}, NIP_VALUE_TYPE_BOOL8}
#define NIP_DEF_VALUE_BOOL16(_val)          {{.i16 = _val}, NIP_VALUE_TYPE_BOOL16}
#define NIP_DEF_VALUE_BOOL32(_val)          {{.i32 = _val}, NIP_VALUE_TYPE_BOOL32}
#define NIP_DEF_VALUE_BOOL64(_val)          {{.i64 = _val}, NIP_VALUE_TYPE_BOOL64}
#define NIP_DEF_VALUE_FLOAT32(_val)         {{.f32 = _val}, NIP_VALUE_TYPE_FLOAT32}
#define NIP_DEF_VALUE_FLOAT64(_val)         {{.f64 = _val}, NIP_VALUE_TYPE_FLOAT64}
#define NIP_DEF_VALUE_BOOL(_val)            {{.b   = _val}, NIP_VALUE_TYPE_BOOL}
#define NIP_DEF_VALUE_STRING(_val)          {{.str = _val}, NIP_VALUE_TYPE_STRING}
#define NIP_DEF_VALUE_CHAR_BUFFER(_val)     {{.str = _val}, NIP_VALUE_TYPE_STRING}
#define NIP_DEF_VALUE_CUSTOM(_val, _cp_fn)  {{.raw = _val}, NIP_VALUE_TYPE_CUSTOM, _cp_fn}
/** @} */

/**
 * @defgroup macros Helper macros for ranges.
 * @{
 */
#define NIP_RANGE_INT8(_min, _max)          {{.i8  = _min}, {.i8  = _max}, NIP_VALUE_TYPE_INT8}
#define NIP_RANGE_INT16(_min, _max)         {{.i16 = _min}, {.i16 = _max}, NIP_VALUE_TYPE_INT16}
#define NIP_RANGE_INT32(_min, _max)         {{.i32 = _min}, {.i32 = _max}, NIP_VALUE_TYPE_INT32}
#define NIP_RANGE_INT64(_min, _max)         {{.i64 = _min}, {.i64 = _max}, NIP_VALUE_TYPE_INT64}
#define NIP_RANGE_UINT8(_min, _max)         {{.u8  = _min}, {.u8  = _max}, NIP_VALUE_TYPE_UINT8}
#define NIP_RANGE_UINT16(_min, _max)        {{.u16 = _min}, {.u16 = _max}, NIP_VALUE_TYPE_UINT16}
#define NIP_RANGE_UINT32(_min, _max)        {{.u32 = _min}, {.u32 = _max}, NIP_VALUE_TYPE_UINT32}
#define NIP_RANGE_UINT64(_min, _max)        {{.u64 = _min}, {.u64 = _max}, NIP_VALUE_TYPE_UINT64}
#define NIP_RANGE_FLOAT32(_min, _max)       {{.f32 = _min}, {.f32 = _max}, NIP_VALUE_TYPE_FLOAT32}
#define NIP_RANGE_FLOAT64(_min, _max)       {{.f64 = _min}, {.f64 = _max}, NIP_VALUE_TYPE_FLOAT64}
/** @} */

/**
 * @enum NipError
 * @brief List of error codes.
 */
typedef enum NipError {
    NIP_OK                                  = 0,

    NIP_ERROR_INVALID_ARGUMENT              = -1,
    NIP_ERROR_OUT_OF_MEMORY                 = -2,
    NIP_ERROR_INVALID_CHARACTER             = -3,
    NIP_ERROR_INVALID_SECTION_NAME          = -4,
    NIP_ERROR_MISSING_SECTION_NAME          = -5,
    NIP_ERROR_INVALID_KEY_NAME              = -6,
    NIP_ERROR_EXPECTED_EQUAL_SIGN           = -7,
    NIP_ERROR_OUT_OF_RANGE                  = -8,
    NIP_ERROR_INSUFFICEINT_BUFFER           = -9,
    NIP_ERROR_MISSING_SECTION_BEFORE_KEY    = -10,
    NIP_ERROR_STRING_NOT_CLOSED             = -11,
    NIP_ERROR_INVALID_NUMBER                = -12,
    NIP_ERROR_DECODER_FAILURE               = -13,
    NIP_ERROR_UNSUPPORTED                   = -14,
    NIP_ERROR_INVALID_VALUE_DESCRIPTION     = -15,
    NIP_ERROR_FAILED_TO_COPY_DEFAULT_VALUE  = -16,
    NIP_ERROR_MISSING_KEY_VALUE             = -17,
    NIP_ERROR_DUPLICATED_SECTION_NAME       = -18,
    NIP_ERROR_DUPLICATED_KEY_NAME           = -19,
    NIP_ERROR_DUMP_OPTION_NOT_SET           = -20,
    NIP_ERROR_SECTION_NAME_TOO_LONG         = -21,
    NIP_ERROR_KEY_NAME_TOO_LONG             = -22,
    NIP_ERROR_EXPECTED_VALUE                = -23,
    NIP_ERROR_EXPECTED_SECTION_NAME         = -24,
    NIP_ERROR_EXPECTED_RBRACKET             = -25,
    NIP_ERROR_EXPECTED_SECTION_OR_KEY       = -26,
    NIP_ERROR_WRITE_FAILED                  = -27,
    NIP_ERROR_PANIC                         = -128,

} NipError;

/**
 * @enum NipValueType
 * @brief Enum for value types.
 */
typedef uint8_t NipValueType;
enum {
    NIP_VALUE_TYPE_INT8         = 1,
    NIP_VALUE_TYPE_INT16        = 2,
    NIP_VALUE_TYPE_INT32        = 3,
    NIP_VALUE_TYPE_INT64        = 4,
    NIP_VALUE_TYPE_UINT8        = 5,
    NIP_VALUE_TYPE_UINT16       = 6,
    NIP_VALUE_TYPE_UINT32       = 7,
    NIP_VALUE_TYPE_UINT64       = 8,
    NIP_VALUE_TYPE_BOOL8        = 9,
    NIP_VALUE_TYPE_BOOL16       = 10,
    NIP_VALUE_TYPE_BOOL32       = 11,
    NIP_VALUE_TYPE_BOOL64       = 12,
    NIP_VALUE_TYPE_FLOAT32      = 13,
    NIP_VALUE_TYPE_FLOAT64      = 14,
    NIP_VALUE_TYPE_BOOL         = 15,
    NIP_VALUE_TYPE_STRING       = 16,
    NIP_VALUE_TYPE_CHAR_BUFFER  = 17,
    NIP_VALUE_TYPE_CUSTOM       = 18,
};

typedef size_t(*NipWriteFn)(void *fp, const char *buffer, size_t size);

typedef int(*NipDecoder)(const char *str, size_t len, void *value_ptr);
typedef int(*NipCopyFn)(void *value_ptr, void *def_value);
typedef size_t(*NipWriter)(void *value_ptr, void *fp, NipWriteFn write_fn);

/**
 * @enum NipKvFlags
 * @brief Enum for key-value flags.
 */
typedef uint8_t NipKvFlags;
enum {
    NIP_KV_FLAGS_DEFAULT_ON_ERROR   = 1 << 4,
    NIP_KV_FLAGS_CLAMP_ON_ERROR     = 1 << 5,   // for integers and floats
    NIP_KV_FLAGS_WRITE_AS_HEX       = 1 << 6,   // for integers and floats
};

/**
 * @enum NipKvDesc
 * @brief Key-value description.
 */
typedef struct NipKvDesc {
    const char          *key;

    struct {
        union {
            int8_t      *i8;
            int16_t     *i16;
            int32_t     *i32;
            int64_t     *i64;
            uint8_t     *u8;
            uint16_t    *u16;
            uint32_t    *u32;
            uint64_t    *u64;
            float       *f32;
            double      *f64;
            bool        *b;
            char        **str;
            char        *cb;
            void        *raw;
        } ptr;

        NipValueType    type;

        union {
            uint32_t    buf_size;
        } extra_info;
    } value;

    NipDecoder          decoder;
    NipWriter           writer;
    
    struct {
        union {
            int8_t      i8;
            int16_t     i16;
            int32_t     i32;
            int64_t     i64;
            uint8_t     u8;
            uint16_t    u16;
            uint32_t    u32;
            uint64_t    u64;
            float       f32;
            double      f64;
            bool        b;
            char        *str;
            void        *ptr;
        } data;

        NipValueType    type;
        NipCopyFn       copy_fn;
    } def_value;

    struct {
        union {
            int8_t      i8;
            int16_t     i16;
            int32_t     i32;
            int64_t     i64;
            uint8_t     u8;
            uint16_t    u16;
            uint32_t    u32;
            uint64_t    u64;
            float       f32;
            double      f64;
            void        *ptr;
        } min;

        union {
            int8_t      i8;
            int16_t     i16;
            int32_t     i32;
            int64_t     i64;
            uint8_t     u8;
            uint16_t    u16;
            uint32_t    u32;
            uint64_t    u64;
            float       f32;
            double      f64;
            void        *ptr;
        } max;

        NipValueType    type;
    } range;

    const char          *comment;
    NipKvFlags          flags;
} NipKvDesc;

typedef struct NipKV NipKV;
typedef struct NipSection NipSection;

typedef enum NipOptions {
    NIP_OPTIONS_DEFAULT                     = 0,
    NIP_OPTIONS_VALIDATE_ON_RELEASE         = 1 << 1,
    NIP_OPTIONS_ALWAYS_DEFAULT_ON_ERROR     = 1 << 2,
    NIP_OPTIONS_ALWAYS_CLAMP_ON_ERROR       = 1 << 3,
    NIP_OPTIONS_STRICT                      = 1 << 4,
    NIP_OPTIONS_DUMP                        = 1 << 5,
} NipOptions;

typedef struct Nip1 {
    struct {
        NipSection      *ptr;
        uint32_t        len;
        uint32_t        cap;
    } sections;

    NipSection          *current_section;
    NipKV               *current_kv;

    struct {
        size_t          line;
        size_t          column;
        size_t          start;
        NipError        code;
    } error;

    struct {
        const char      *ptr;
        size_t          len;
    } buffer;

    NipOptions          options;
    int                 decoder_error;

    size_t              pos;
    size_t              line;
    size_t              line_start_pos;
} Nip1;

/**
 * @brief       Initialize Nip1 structure.
 * @param       nip             pointer to Nip1 struct
 * @param       options         parser options
 * @param       num_sections    number of sections to pre-allocate
 * @return      status code, see #NipError
 */
NIP_API NipError nip_init(Nip1 *nip, NipOptions options, uint32_t num_sections);

/**
 * @brief       De-initialize Nip1 object, free all the memory.
 * @param       nip             pointer to Nip1 struct
 * @return      status code, see #NipError
 */
NIP_API NipError nip_deinit(Nip1 *nip);

/**
 * @brief       Parse ini buffer.
 * @details     After the parsing it will automatically assign default values
 *              (if those were specified for key-value).
 * @param       nip             pointer to Nip1 struct
 * @param       buffer          buffer containing ini string
 * @param       len             length of the buffer
 * @return      status code, see #NipError
 */
NIP_API NipError nip_parse(Nip1 *nip, const char *buffer, size_t len);

/**
 * @brief       Parse single lien of ini buffer.
 * @param       nip             pointer to Nip1 struct
 * @param       buffer          buffer containing line
 * @param       len             length of the buffer
 * @return      status code, see #NipError
 */
NIP_API NipError nip_parse_line(Nip1 *nip, const char *buffer, size_t len);

/**
 * @brief       Indicate that parsing finished.
 * @details     Call this function only if you parse ini by line.
 * @param       nip             pointer to Nip1 struct
 * @return      status code, see #NipError
 */
NIP_API NipError nip_parse_finish(Nip1 *nip);

/**
 * @brief       Start new section.
 * @param       nip             pointer to Nip1 struct
 * @param       name            section name
 * @param       optional        is this section optional
 * @param       num_kv          number of key-value pairs to pre-allocate
 * @return      status code, see #NipError
 */
NIP_API NipError nip_begin_section(Nip1 *nip, const char *name, bool optional, uint32_t num_kv);

/**
 * @brief       End the section.
 * @param       nip             pointer to Nip1 struct
 * @return      status code, see #NipError
 */
NIP_API NipError nip_end_section(Nip1 *nip);

/**
 * @brief       End the section.
 * @param       nip             pointer to Nip1 struct
 * @param       desc            key-value description
 * @return      status code, see #NipError
 */
NIP_API NipError nip_push(Nip1 *nip, const NipKvDesc desc);

/**
 * @brief       Dump ini using write_fn.
 * @param       nip             pointer to Nip1 struct
 * @param       write_fn        function that receive buffer to write
 * @param       fp              pointer to user descriptor, passed as first argument to write_fn
 * @return      status code, see #NipError
 */
NIP_API NipError nip_dump(const Nip1 *nip, NipWriteFn write_fn, void *fp);

#if defined(__cplusplus)
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef NIP_IMPLEMENTATION

#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef min
#undef max

#pragma region "Constants"

// ========================================================================== //

#define NIP_MAX_SECTION_NAME_LENGTH     64
#define NIP_MAX_KEY_NAME_LENGTH         128
#define NIP_MAX_DEFAULT_STRING_LENGTH   102400

// ========================================================================== //

#pragma endregion

#pragma region "Macros"

// ========================================================================== //

#if defined(_DEBUG)
#include <assert.h>
#define NIP_ASSERT(_expr, _msg) assert((_expr) && (_msg))
#define NIP_PANIC(_msg)         assert((0) && (_msg))
#else
#define NIP_ASSERT(_expr, _msg) do{}while(0)
#define NIP_PANIC(_msg)         abort()
#endif // _DEBUG

#define NIP_UNREFERENCED_PARAMETER(x) (void)(x)

// ========================================================================== //

#pragma endregion

#pragma region "Data Types"

// ========================================================================== //

// NipChar
#ifdef NIP_USE_WIDE_CHAR
#define NIP_CHAR_T wchar_t
typedef wchar_t NipChar;
#define NIP_CH(c) L##c
#else
#define NIP_CHAR_T char
typedef char NipChar;
#define NIP_CH(c) c
#endif

// ========================================================================== //

// Internal NipKvFlags
enum {
    NIP_KV_FLAGS_ALREADY_USED       = 1 << 0,
    NIP_KV_FLAGS_HAS_DEFAULT        = 1 << 1,
    NIP_KV_FLAGS_HAS_RANGE          = 1 << 2,
};

// ========================================================================== //

// NipKV
struct NipKV {
    const NipChar   *key;
    void            *value_ptr;

    uint8_t         value_type;
    uint8_t         key_len;
    uint8_t         flags;

    union {
        uint32_t    buf_size;
    } extra_info;

    const NipChar   *comment;
    NipDecoder      decoder;
    NipWriter       writer;
    NipCopyFn       copy_fn;

    union {
        int8_t      i8;
        int16_t     i16;
        int32_t     i32;
        int64_t     i64;
        uint8_t     u8;
        uint16_t    u16;
        uint32_t    u32;
        uint64_t    u64;
        float       f32;
        double      f64;
        bool        b;
        NipChar     *str;
        void        *ptr;
    } def_value;

    union {
        int8_t      i8;
        int16_t     i16;
        int32_t     i32;
        int64_t     i64;
        uint8_t     u8;
        uint16_t    u16;
        uint32_t    u32;
        uint64_t    u64;
        float       f32;
        double      f64;
    } min_value;

    union {
        int8_t      i8;
        int16_t     i16;
        int32_t     i32;
        int64_t     i64;
        uint8_t     u8;
        uint16_t    u16;
        uint32_t    u32;
        uint64_t    u64;
        float       f32;
        double      f64;
        size_t      def_str_len;
    } max_value;
};

// ========================================================================== //

// NipSection
struct NipSection {
    struct {
        const char      *ptr;
        size_t          len;
    } name;

    struct {
        NipKV           *ptr;
        uint32_t        len;
        uint32_t        cap;
    } kv;

    bool                used;
    bool                optional;
    const char          *comment;
};

// ========================================================================== //

// NipTokenType
typedef enum NipTokenType {
    NIP_TOKEN_INVALID   = 0,
    NIP_TOKEN_EOL,
    NIP_TOKEN_LBRACKET,
    NIP_TOKEN_RBRACKET,
    NIP_TOKEN_EQUAL,
    NIP_TOKEN_IDENDIFIER,
    NIP_TOKEN_NUMBER,
    NIP_TOKEN_STRING,

    // All negative values are error codes.
    //NIP_TOKEN_ERROR     = -1,
} NipTokenType;

// ========================================================================== //

// NipToken
typedef struct NipToken {
    const NipChar   *str;
    uint32_t        len;
    NipTokenType    type;
} NipToken;

// ========================================================================== //

#pragma endregion

#pragma region "Helper Functions"

// ========================================================================== //

static int _nip_is_digit(NipChar c) {
    return c >= NIP_CH('0') && c <= NIP_CH('9');
}

// ========================================================================== //

static int _nip_is_xdigit(NipChar c) {
    return (c >= NIP_CH('0') && c <= NIP_CH('9'))
        || (c >= NIP_CH('a') && c <= NIP_CH('f'))
        || (c >= NIP_CH('A') && c <= NIP_CH('F'));
}

// ========================================================================== //

static int _nip_is_alpha(NipChar c) {
    return (c >= NIP_CH('a') && c <= NIP_CH('z')) || (c >= NIP_CH('A') && c <= NIP_CH('Z'));
}

// ========================================================================== //

static int _nip_is_alpha_num(NipChar c) {
    return _nip_is_alpha(c) || _nip_is_digit(c);
}

// ========================================================================== //

static int _nip_is_print(NipChar c) {
#ifdef NIP_USE_WIDE_CHAR
    return iswprint(c);
#else
    return isprint(c);
#endif
}

// ========================================================================== //

static int _nip_tolower(const NipChar c) {
#ifdef NIP_USE_WIDE_CHAR
    return towlower(c);
#else
    return tolower(c);
#endif
}

// ========================================================================== //

static size_t _nip_strlen(const NipChar *str) {
#ifdef NIP_USE_WIDE_CHAR
    return wcslen(str);
#else
    return strlen(str);
#endif
}

// ========================================================================== //

static size_t _nip_strnlen(const NipChar *str, size_t limit) {
#ifdef NIP_USE_WIDE_CHAR
    return wcsnlen(str, limit);
#else
    return strnlen(str, limit);
#endif
}

// ========================================================================== //

static int _nip_strncmp(const NipChar *str1, const NipChar *str2, size_t limit) {
#ifdef NIP_USE_WIDE_CHAR
    return wcsncmp(str1, str2, limit);
#else
    return strncmp(str1, str2, limit);
#endif
}

// ========================================================================== //

static uint64_t _nip_strtoull(const NipChar *str, NipChar **end, int radix) {
#ifdef NIP_USE_WIDE_CHAR
    return wcstoull(str, end, radix);
#else
    return strtoull(str, end, radix);
#endif
}

// ========================================================================== //

static float _nip_strtof(const NipChar *str, NipChar **end) {
#ifdef NIP_USE_WIDE_CHAR
    return wcstof(str, end);
#else
    return strtof(str, end);
#endif
}

// ========================================================================== //

static double _nip_strtod(const NipChar *str, NipChar **end) {
#ifdef NIP_USE_WIDE_CHAR
    return wcstod(str, end);
#else
    return strtod(str, end);
#endif
}

// ========================================================================== //

#pragma endregion

#pragma region "Tokenization"

// ========================================================================== //

static NipToken _nip_token(Nip1 *nip, NipTokenType type, size_t start, size_t end) {
    NIP_ASSERT(end >= start, "start > end");
    return (NipToken){&nip->buffer.ptr[start], end - start, type};
}

// ========================================================================== //

static NipToken _nip_token_error(Nip1 *nip, NipError err, size_t start, size_t end) {
    nip->error.start  = start;
    nip->error.line   = nip->line;
    nip->error.column = nip->pos - nip->line_start_pos;
    nip->error.code   = err;

    return (NipToken){&nip->buffer.ptr[start], end - start, (NipTokenType)err};
}

// ========================================================================== //

static NipToken _nip_get_next_token(Nip1 *nip) {
    enum State {
        STATE_START,
        STATE_IDENTIFIER,
        STATE_NUMBER,
        STATE_STRING,
        STATE_COMMENT,
        STATE_END,
    } state = STATE_START;

    size_t start_pos = nip->pos;
    NipChar prev = NIP_CH('\0');
    NipToken token = {NULL, 0, NIP_TOKEN_INVALID};
    for (;;) {
        size_t pos = nip->pos;
        bool advance = true;

        NipChar c;
        if (pos < nip->buffer.len) {
            c = nip->buffer.ptr[pos];
        } else {
            // End of input.
            switch (state) {
            case STATE_START:
                token = _nip_token(nip, NIP_TOKEN_EOL, pos, pos + 1);
                break;
            case STATE_IDENTIFIER:
                token = _nip_token(nip, NIP_TOKEN_IDENDIFIER, start_pos, pos);
                break;
            case STATE_NUMBER:
                token = _nip_token(nip, NIP_TOKEN_NUMBER, start_pos, pos);
                break;
            case STATE_STRING:
                token = _nip_token_error(nip, NIP_ERROR_STRING_NOT_CLOSED, start_pos, pos);
                break;
            case STATE_COMMENT:
                token = _nip_token(nip, NIP_TOKEN_EOL, pos, pos + 1);
                break;
            }

            // Break from loop.
            break;
        }

        switch (state) {
        case STATE_START:
            start_pos = pos;

            if (c == NIP_CH(' ') || c == NIP_CH('\t') || c == NIP_CH('\r')) {
                // pass
            } else if (c == NIP_CH('\n')) {
                token = _nip_token(nip, NIP_TOKEN_EOL, pos, pos + 1);
            } else if (c == NIP_CH('[')) {
                token = _nip_token(nip, NIP_TOKEN_LBRACKET, pos, pos + 1);
            } else if (c == NIP_CH(']')) {
                token = _nip_token(nip, NIP_TOKEN_RBRACKET, pos, pos + 1);
            } else if (c == NIP_CH('=')) {
                token = _nip_token(nip, NIP_TOKEN_EQUAL, pos, pos + 1);
            } else if (_nip_is_alpha(c) || c == NIP_CH('_') || c == NIP_CH('.')) {
                state = STATE_IDENTIFIER;
            } else if (_nip_is_digit(c) || c == NIP_CH('-') || c == NIP_CH('+')) {
                state = STATE_NUMBER;
            } else if (c == NIP_CH('"')) {
                state = STATE_STRING;
            } else if (c == NIP_CH(';')) {
                state = STATE_COMMENT;
            } else {
                token = _nip_token_error(nip, NIP_ERROR_INVALID_CHARACTER, start_pos, pos);
            }
            break;
        case STATE_IDENTIFIER:
            if (_nip_is_alpha_num(c) || c == NIP_CH('_') || c == NIP_CH('.')) {
                // pass
            } else {
                token = _nip_token(nip, NIP_TOKEN_IDENDIFIER, start_pos, pos);
                advance = false;
            }
            break;
        case STATE_NUMBER:
            if (_nip_is_alpha_num(c) || c == NIP_CH('-') || c == NIP_CH('+') || c == NIP_CH('.')) {
                // pass
            } else {
                token = _nip_token(nip, NIP_TOKEN_NUMBER, start_pos, pos);
                advance = false;
            }
            break;
        case STATE_STRING:
            if (c == NIP_CH('\0')) {
                token = _nip_token_error(nip, NIP_ERROR_INVALID_CHARACTER, start_pos, pos);
            } else if (c == NIP_CH('\n')) {
                token = _nip_token_error(nip, NIP_ERROR_STRING_NOT_CLOSED, start_pos, pos);
            } else if (c == NIP_CH('"') && prev != NIP_CH('\\')) {
                token = _nip_token(nip,  NIP_TOKEN_STRING, start_pos + 1, pos);
            }
            break;
        case STATE_COMMENT:
            if (c == NIP_CH('\0')) {
                token = _nip_token_error(nip, NIP_ERROR_INVALID_CHARACTER, start_pos, pos);
            } else if (c == NIP_CH('\n')) {
                token = _nip_token(nip, NIP_TOKEN_EOL, pos, pos + 1);
            }
            break;
        }

        if (advance && token.type >= 0) {
            nip->pos += 1;
            prev = c;
        }

        if (token.type != NIP_TOKEN_INVALID) {
            // Break from loop.
            break;
        }
    }

    return token;
}

// ========================================================================== //

#pragma endregion

#pragma region "Find Functions"

// ========================================================================== //

static NipSection *_nip_find_section(const Nip1 *nip, const NipChar *name, size_t len) {
    for (uint32_t i = 0; i < nip->sections.len; i += 1) {
        NipSection *section = &nip->sections.ptr[i];
        if (section->name.len == len) { 
            if (_nip_strncmp(section->name.ptr, name, len) == 0) {
                return section;
            }
        }
    }

    return NULL;
}

// ========================================================================== //

static NipKV *_nip_find_kv(const NipSection *section, const NipChar *key, size_t len) {
    for (uint32_t i = 0; i < section->kv.len; i += 1) {
        NipKV *kv = &section->kv.ptr[i];
        if (kv->key_len == len) { 
            if (_nip_strncmp(kv->key, key, len) == 0) {
                return kv;
            }
        }
    }

    return NULL;
}

// ========================================================================== //

#pragma endregion

#pragma region "Validation"

// ========================================================================== //

static NipError _nip_is_valid_section_name(const Nip1 *nip, const NipChar *name) {
    NIP_ASSERT(nip, "invalid argument");

    if (name == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    size_t len = _nip_strnlen(name, NIP_MAX_SECTION_NAME_LENGTH);
    if (len == NIP_MAX_SECTION_NAME_LENGTH) {
        return NIP_ERROR_SECTION_NAME_TOO_LONG;
    }

    if (!_nip_is_alpha_num(name[0]) && name[0] != NIP_CH('_') && name[0] != NIP_CH('.')) {
        return NIP_ERROR_INVALID_CHARACTER;
    }

    for (size_t i = 0; i < len; i += 1) {
        if (!_nip_is_alpha_num(name[i]) && name[i] != NIP_CH('_') && name[i] != NIP_CH('.')) {
            return NIP_ERROR_INVALID_CHARACTER;
        }
    }

    NipSection *section = _nip_find_section(nip, name, len);
    if (section != NULL) {
        return NIP_ERROR_DUPLICATED_SECTION_NAME;
    }

    return NIP_OK;
}

static NipError _nip_is_valid_key_name(const Nip1 *nip, const NipSection *section, const NipChar *key) {
    NIP_UNREFERENCED_PARAMETER(nip);

    NIP_ASSERT(nip, "invalid argument");
    NIP_ASSERT(section, "invalid argument");

    if (key == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    size_t len = _nip_strnlen(key, NIP_MAX_KEY_NAME_LENGTH);
    if (len == NIP_MAX_KEY_NAME_LENGTH) {        
        return NIP_ERROR_KEY_NAME_TOO_LONG;
    }

    if (!_nip_is_alpha_num(key[0]) && key[0] != NIP_CH('_') && key[0] != NIP_CH('.')) {
        return NIP_ERROR_INVALID_CHARACTER;
    }

    for (size_t i = 0; i < len; i += 1) {
        if (!_nip_is_alpha_num(key[i]) && key[i] != NIP_CH('_') && key[i] != NIP_CH('.')) {
            return NIP_ERROR_INVALID_CHARACTER;
        }
    }

    NipKV *kv = _nip_find_kv(section, key, len);
    if (kv != NULL) {
        return NIP_ERROR_DUPLICATED_KEY_NAME;
    }

    return NIP_OK;
}

static bool _nip_validate_desc(const Nip1 *nip, const NipKvDesc *desc, NipKvFlags flags) {
    NIP_UNREFERENCED_PARAMETER(nip);

    NIP_ASSERT(nip, "invalid argument");
    NIP_ASSERT(desc, "invalid argument");

    #ifdef _DEBUG
        #define VERR(msg) NIP_PANIC(msg); return false
    #else
        #define VERR(msg) return false
    #endif // _DEBUG

    if (desc->value.type == NIP_VALUE_TYPE_CUSTOM && desc->decoder == NULL) {
        VERR("custom value type require decoder");
    }

    if (desc->def_value.type != 0) {
        if (desc->value.type == NIP_VALUE_TYPE_STRING || desc->value.type == NIP_VALUE_TYPE_CHAR_BUFFER) {
            size_t len = _nip_strnlen(desc->def_value.data.str, NIP_MAX_DEFAULT_STRING_LENGTH);
            if (len == NIP_MAX_DEFAULT_STRING_LENGTH) {
                VERR("invalid default value");
            }
        } else {
            if (desc->def_value.type != desc->value.type) {
                VERR("type mismatch, def_value.type != value.type");
            }
        }

        if (desc->def_value.type == NIP_VALUE_TYPE_CUSTOM && desc->def_value.copy_fn == NULL) {
            VERR("missing copy function for custom type");
        }
    }

    if ((flags & NIP_KV_FLAGS_DEFAULT_ON_ERROR) != 0 && desc->def_value.type == 0) {
        VERR("missing default value to assign on error");
    }

    if ((flags & NIP_KV_FLAGS_CLAMP_ON_ERROR) != 0 && desc->range.type == 0) {
        VERR("missing range to clamp on error");
    }

    if (desc->range.type != 0) {
        if (desc->range.type != desc->value.type) {
            VERR("type mismatch, range.type != value.type");
        }

        if (desc->value.type == NIP_VALUE_TYPE_INT8) {
            if (desc->range.min.i8 > desc->range.max.i8) {
                VERR("range.min > range.max");
            }
        } else if (desc->value.type == NIP_VALUE_TYPE_INT16) {
            if (desc->range.min.i16 > desc->range.max.i16) {
                VERR("range.min > range.max");
            }
        } else if (desc->value.type == NIP_VALUE_TYPE_INT32) {
            if (desc->range.min.i32 > desc->range.max.i32) {
                VERR("range.min > range.max");
            }
        } else if (desc->value.type == NIP_VALUE_TYPE_INT64) {
            if (desc->range.min.i64 > desc->range.max.i64) {
                VERR("range.min > range.max");
            }
        } else if (desc->value.type == NIP_VALUE_TYPE_UINT8) {
            if (desc->range.min.u8 > desc->range.max.u8) {
                VERR("range.min > range.max");
            }
        } else if (desc->value.type == NIP_VALUE_TYPE_UINT16) {
            if (desc->range.min.u16 > desc->range.max.u16) {
                VERR("range.min > range.max");
            }
        } else if (desc->value.type == NIP_VALUE_TYPE_UINT32) {
            if (desc->range.min.u32 > desc->range.max.u32) {
                VERR("range.min > range.max");
            }
        } else if (desc->value.type == NIP_VALUE_TYPE_UINT64) {
            if (desc->range.min.u64 > desc->range.max.u64) {
                VERR("range.min > range.max");
            }
        } else if (desc->value.type == NIP_VALUE_TYPE_FLOAT32) {
            if (isnan(desc->range.min.f32)) {
                VERR("invalid value, range.min.f32 is nan");
            }

            if (isinf(desc->range.min.f32)) {
                VERR("invalid value, range.min.f32 is inf");
            }

            if (isnan(desc->range.max.f32)) {
                VERR("invalid value, range.max.f32 is nan");
            }

            if (isinf(desc->range.max.f32)) {
                VERR("invalid value, range.max.f32 is inf");
            }

            if (desc->range.min.f32 > desc->range.max.f32) {
                VERR("range.min > range.max");
            }
        } else if (desc->value.type == NIP_VALUE_TYPE_FLOAT64) {
            if (isnan(desc->range.min.f64)) {
                VERR("invalid value, range.min.f64 is nan");
            }

            if (isinf(desc->range.min.f64)) {
                VERR("invalid value, range.min.f64 is inf");
            }

            if (isnan(desc->range.max.f64)) {
                VERR("invalid value, range.max.f64 is nan");
            }

            if (isinf(desc->range.max.f64)) {
                VERR("invalid value, range.max.f64 is inf");
            }

            if (desc->range.min.f64 > desc->range.max.f64) {
                VERR("range.min > range.max");
            }
        } else {
            VERR("range specified for unsupported type");
        }
    }

    if ((nip->options & NIP_OPTIONS_DUMP) != 0) {
        if (desc->writer == NULL) {
            VERR("missing writer needed for dumping");
        }
    }

    #undef VERR

    return true;
}

// ========================================================================== //

#pragma endregion

#pragma region "Write Helpers"

// ========================================================================== //

static bool _nip_write_comment(
    const NipChar   *comment,
    bool            is_section,
    NipWriteFn      write_fn,
    void            *fp
) {
    if (comment) {        
        size_t i = 0;
        size_t start = 0;
        bool write_semicolon = true;
        while (true) {
            NipChar c =  comment[i];
            if (c == NIP_CH('\0') || c == NIP_CH('\n')) {
                if (write_semicolon && write_fn(fp, "; ", 2) != 2) {
                    return false;
                }

                size_t l = i - start;
                if (write_fn(fp, &comment[start], l) != l) {
                    return false;
                }
                start = i + 1;

                if (is_section) {
                    if (write_fn(fp, "\n", 1) != 1) {
                        return false;
                    }
                } else {
                    if (c == NIP_CH('\n') && write_fn(fp, " ", 1) != 1) {
                        return false;
                    }

                    write_semicolon = false;
                }

                if (c == NIP_CH('\0')) {
                    break;
                }
            }

            i += 1;
        }
    }

    return true;
}

// ========================================================================== //

static bool _nip_write_bool_kv(const Nip1 *nip, const NipKV *kv, NipWriteFn write_fn, void *fp) {
    NIP_UNREFERENCED_PARAMETER(nip);

    bool bvalue = false;

    switch (kv->value_type) {
    case NIP_VALUE_TYPE_BOOL8:  bvalue = *(int8_t *) kv->value_ptr != 0;  break;
    case NIP_VALUE_TYPE_BOOL16: bvalue = *(int16_t *)kv->value_ptr != 0;  break;
    case NIP_VALUE_TYPE_BOOL32: bvalue = *(int32_t *)kv->value_ptr != 0;  break;
    case NIP_VALUE_TYPE_BOOL64: bvalue = *(int64_t *)kv->value_ptr != 0;  break;
    case NIP_VALUE_TYPE_BOOL:   bvalue = *(bool *)   kv->value_ptr != 0;  break;
    }

    const NipChar *buffer;
    size_t len = 0;
    if (bvalue) {
        buffer = "true";
        len = 4;
    } else {
        buffer = "false";
        len = 5;
    }

    return write_fn(fp, buffer, len) == len;
}

// ========================================================================== //

static bool _nip_write_integer_kv(const Nip1 *nip, const NipKV *kv, NipWriteFn write_fn, void *fp) {
    NIP_UNREFERENCED_PARAMETER(nip);

    const NipChar *prefix = NULL;
    const NipChar *fmt = NULL;

    if ((kv->flags & NIP_KV_FLAGS_WRITE_AS_HEX) != 0) {
        prefix = "0x";

        switch (kv->value_type) {
        case NIP_VALUE_TYPE_INT8:   fmt = "%02X";       break;
        case NIP_VALUE_TYPE_INT16:  fmt = "%04X";       break;
        case NIP_VALUE_TYPE_INT32:  fmt = "%08X";       break;
        case NIP_VALUE_TYPE_INT64:  fmt = "%016llX";    break;
        case NIP_VALUE_TYPE_UINT8:  fmt = "%02X";       break;
        case NIP_VALUE_TYPE_UINT16: fmt = "%04X";       break;
        case NIP_VALUE_TYPE_UINT32: fmt = "%08X";       break;
        case NIP_VALUE_TYPE_UINT64: fmt = "%016llX";    break;
        }
    } else {
        prefix = NULL;

        switch (kv->value_type) {
        case NIP_VALUE_TYPE_INT8:
        case NIP_VALUE_TYPE_INT16:
        case NIP_VALUE_TYPE_INT32:  fmt = "%d";         break;
        case NIP_VALUE_TYPE_INT64:  fmt = "%lld";       break;
        case NIP_VALUE_TYPE_UINT8:
        case NIP_VALUE_TYPE_UINT16:
        case NIP_VALUE_TYPE_UINT32: fmt = "%u";         break;
        case NIP_VALUE_TYPE_UINT64: fmt = "%llu";       break;
        }
    }

    NIP_ASSERT(fmt, "format was not set");

    #define TEMP_BUFFER_SIZE 128
    NipChar buffer[TEMP_BUFFER_SIZE];
    int len = 0;

    switch (kv->value_type) {
    case NIP_VALUE_TYPE_INT8:
        len = snprintf(buffer, TEMP_BUFFER_SIZE, fmt, *(int8_t *)kv->value_ptr);
        break;
    case NIP_VALUE_TYPE_INT16:
        len = snprintf(buffer, TEMP_BUFFER_SIZE, fmt, *(int16_t *)kv->value_ptr);
        break;
    case NIP_VALUE_TYPE_INT32:
        len = snprintf(buffer, TEMP_BUFFER_SIZE, fmt, *(int32_t *)kv->value_ptr);
        break;
    case NIP_VALUE_TYPE_INT64:
        len = snprintf(buffer, TEMP_BUFFER_SIZE, fmt, *(int64_t *)kv->value_ptr);
        break;
    case NIP_VALUE_TYPE_UINT8:
        len = snprintf(buffer, TEMP_BUFFER_SIZE, fmt, *(uint8_t *)kv->value_ptr);
        break;
    case NIP_VALUE_TYPE_UINT16:
        len = snprintf(buffer, TEMP_BUFFER_SIZE, fmt, *(uint16_t *)kv->value_ptr);
        break;
    case NIP_VALUE_TYPE_UINT32:
        len = snprintf(buffer, TEMP_BUFFER_SIZE, fmt, *(uint32_t *)kv->value_ptr);
        break;
    case NIP_VALUE_TYPE_UINT64:
        len = snprintf(buffer, TEMP_BUFFER_SIZE, fmt, *(uint64_t *)kv->value_ptr);
        break;
    }

    if (len <= 0) {
        return false;
    }

    #undef TEMP_BUFFER_SIZE

    if (prefix) {
        if (write_fn(fp, prefix, 2) != 2) {
            return false;
        }
    }

    return write_fn(fp, buffer, (size_t)len) == (size_t)len;
}

// ========================================================================== //

static bool _nip_write_float_kv(const Nip1 *nip, const NipKV *kv, NipWriteFn write_fn, void *fp) {
    NIP_UNREFERENCED_PARAMETER(nip);

    const NipChar *fmt = NULL;

    if ((kv->flags & NIP_KV_FLAGS_WRITE_AS_HEX) != 0) {
        fmt = "%a";
    } else {
        fmt = "%f";
    }

    #define TEMP_BUFFER_SIZE 128
    NipChar buffer[TEMP_BUFFER_SIZE];
    int len = 0;

    switch (kv->value_type) {
    case NIP_VALUE_TYPE_FLOAT32:
        len = snprintf(buffer, TEMP_BUFFER_SIZE, fmt, *(float *)kv->value_ptr);
        break;
    case NIP_VALUE_TYPE_FLOAT64:
        len = snprintf(buffer, TEMP_BUFFER_SIZE, fmt, *(double *)kv->value_ptr);
        break;
    }

    if (len <= 0) {
        return false;
    }

    #undef TEMP_BUFFER_SIZE

    return write_fn(fp, buffer, (size_t)len) == (size_t)len;
}

// ========================================================================== //

static bool _nip_write_string_kv(const Nip1 *nip, const NipKV *kv, NipWriteFn write_fn, void *fp) {
    NIP_UNREFERENCED_PARAMETER(nip);

    const NipChar *str = NULL;
    size_t len = 0;

    switch (kv->value_type) {
    case NIP_VALUE_TYPE_STRING:
        str = *(const NipChar **)kv->value_ptr;
        if (str != NULL) {
            len = _nip_strlen(str);
        }
        break;

    case NIP_VALUE_TYPE_CHAR_BUFFER:
        str = (const NipChar *)kv->value_ptr;
        if (str != NULL) {
            len = _nip_strnlen(str, kv->extra_info.buf_size);
        }
        break;
    }

    size_t count = 0;
    count += write_fn(fp, "\"", 1);
    if (len > 0) {
        count += write_fn(fp, str, len);
    }
    count += write_fn(fp, "\"", 1);

    return count == (len + 2);
}

// ========================================================================== //

static bool _nip_write_custom_kv(const Nip1 *nip, const NipKV *kv, NipWriteFn write_fn, void *fp) {
    NIP_UNREFERENCED_PARAMETER(nip);

    if (kv->writer == NULL) {
        NIP_PANIC("specified custom type without writer");
    }

    return kv->writer(kv->value_ptr, fp, write_fn) != 0;
}

// ========================================================================== //

static bool _nip_write_kv(const Nip1 *nip, const NipKV *kv, NipWriteFn write_fn, void *fp) {
    if (write_fn(fp, kv->key, kv->key_len) != kv->key_len) {
        return false;
    }

    if (write_fn(fp, "=", 1) != 1) {
        return false;
    }

    switch (kv->value_type) {
    case NIP_VALUE_TYPE_BOOL8:
    case NIP_VALUE_TYPE_BOOL16:
    case NIP_VALUE_TYPE_BOOL32:
    case NIP_VALUE_TYPE_BOOL64:
    case NIP_VALUE_TYPE_BOOL:
        if (!_nip_write_bool_kv(nip, kv, write_fn, fp)) {
            return false;
        }
        break;

    case NIP_VALUE_TYPE_INT8:
    case NIP_VALUE_TYPE_INT16:
    case NIP_VALUE_TYPE_INT32:
    case NIP_VALUE_TYPE_INT64:
    case NIP_VALUE_TYPE_UINT8:
    case NIP_VALUE_TYPE_UINT16:
    case NIP_VALUE_TYPE_UINT32:
    case NIP_VALUE_TYPE_UINT64:
        if (!_nip_write_integer_kv(nip, kv, write_fn, fp)) {
            return false;
        }
        break;

    case NIP_VALUE_TYPE_FLOAT32:
    case NIP_VALUE_TYPE_FLOAT64:
        if (!_nip_write_float_kv(nip, kv, write_fn, fp)) {
            return false;
        }
        break;

    case NIP_VALUE_TYPE_STRING:
    case NIP_VALUE_TYPE_CHAR_BUFFER:
        if (!_nip_write_string_kv(nip, kv, write_fn, fp)) {
            return false;
        }
        break;

    case NIP_VALUE_TYPE_CUSTOM:
        if (!_nip_write_custom_kv(nip, kv, write_fn, fp)) {
            return false;
        }
        break;

    default:
        NIP_PANIC("unsupported type");
        break;
    }

    if (!_nip_write_comment(kv->comment, false, write_fn, fp)) {
        return false;
    }

    if (write_fn(fp, "\n", 1) != 1) {
        return false;
    }

    return true;
}

// ========================================================================== //

static bool _nip_write_section(
    const Nip1          *nip,
    const NipSection    *section,
    NipWriteFn          write_fn,
    void                *fp
) {
    NIP_UNREFERENCED_PARAMETER(nip);

    if (!_nip_write_comment(section->comment, true, write_fn, fp)) {
        return false;
    }

    if (write_fn(fp, "[", 1) != 1) { return false; }
    if (write_fn(fp, section->name.ptr, section->name.len) != section->name.len) {
        return false;
    }
    if (write_fn(fp, "]\n", 2) != 2) { return false; }

    return true;
}

// ========================================================================== //

#pragma endregion

#pragma region "Parsing Helpers"

// ========================================================================== //

static NipError _nip_parse_integer(
    const NipChar   *str,
    size_t          len,
    uint64_t        sign_mask,
    uint64_t        *result,
    bool            *is_negative
) {
    NIP_ASSERT(str, "invalid argument");
    NIP_ASSERT(result, "invalid argument");
    NIP_ASSERT(is_negative, "invalid argument");

    size_t i = 0;

    // Check sign.
    bool sign = (str[i] == NIP_CH('-') ? true : false);
    *is_negative = sign;

    if (sign || str[i] == NIP_CH('+')) {
        i += 1;

        if (i == len) {
            return NIP_ERROR_INVALID_NUMBER;
        }

        if (!_nip_is_digit(str[i])) {
            return NIP_ERROR_INVALID_CHARACTER;
        }
    }

    // Check prefix.
    int base = 10;
    if (str[i] == NIP_CH('0')) {
        if (i + 1 < len) {
            NipChar c = str[i + 1];
            if (c == NIP_CH('x') || c == NIP_CH('X')) {
                base = 16;
            } else if (c == NIP_CH('o') || c == NIP_CH('O')) {
                base = 8;
            } else if (c == NIP_CH('b') || c == NIP_CH('B')) {
                base = 2;
            } else {
                return NIP_ERROR_INVALID_NUMBER;
            }

            i += 2;

            if (i == len) {
                return NIP_ERROR_INVALID_NUMBER;
            }
        }
    }

    // Convert.
    errno = 0;
    const NipChar *end = NULL;
    uint64_t temp = _nip_strtoull(&str[i], &end, base);

    // The whole string must be included in conversion.
    if ((uintptr_t)(end - str) != len) {
        return NIP_ERROR_INVALID_CHARACTER;
    }

    if (errno == ERANGE) {
        errno = 0;
        return NIP_ERROR_OUT_OF_RANGE;
    }

    // For base != 10, check most significant bit to determine sign.
    // This only matters for signed integers, for unsigned mask should be 0.
    if (base != 10 && sign_mask != 0) {
        bool s = (temp & sign_mask) != 0;
        *is_negative = s ^ sign;
    }

    *result = temp;

    return NIP_OK;
}

// ========================================================================== //

static NipError _nip_parse_float32(const NipChar *str, size_t len, float *result, bool *is_negative) {
    NIP_ASSERT(str, "invalid argument");
    NIP_ASSERT(result, "invalid argument");

    // Check sign.
    bool sign = (str[0] == NIP_CH('-') ? true : false);
    *is_negative = sign;

    errno = 0;
    const NipChar *end = NULL;
    float temp = _nip_strtof(str, &end);

    // The whole string must be included in conversion.
    if ((uintptr_t)(end - str) != len) {
        return NIP_ERROR_INVALID_CHARACTER;
    }

    if (errno == ERANGE) {
        errno = 0;
        return NIP_ERROR_OUT_OF_RANGE;
    }

    *result = temp;

    return NIP_OK;
}

// ========================================================================== //

static NipError _nip_parse_float64(const NipChar *str, size_t len, double *result, bool *is_negative) {
    NIP_ASSERT(str, "invalid argument");
    NIP_ASSERT(result, "invalid argument");

    bool sign = (str[0] == NIP_CH('-') ? true : false);
    *is_negative = sign;

    errno = 0;
    const NipChar *end = NULL;
    double temp = _nip_strtod(str, &end);

    // The whole string must be included in conversion.
    if ((uintptr_t)(end - str) != len) {
        return NIP_ERROR_INVALID_CHARACTER;
    }

    if (errno == ERANGE) {
        errno = 0;
        return NIP_ERROR_OUT_OF_RANGE;
    }

    *result = temp;

    return NIP_OK;
}

// ========================================================================== //

#pragma endregion

#pragma region "Parsing"

// ========================================================================== //

static NipError _nip_parse_bool_kv(Nip1 *nip, NipKV *kv, const NipChar *str, size_t len) {
    NIP_ASSERT(nip, "invalid argument");
    NIP_ASSERT(kv, "invalid argument");

    bool strict = (nip->options & NIP_OPTIONS_STRICT) != 0;
    bool result = false;

    if (strict) {
        if (len == 1) {
            if (str[0] == NIP_CH('0')) {
                result = false;
            } else if (str[0] == NIP_CH('1')) {
                result = true;
            } else {
                return NIP_ERROR_INVALID_CHARACTER;
            }
        } else if (len == 4) {
            if (_nip_tolower(str[0]) == NIP_CH('t') &&
                _nip_tolower(str[1]) == NIP_CH('r') &&
                _nip_tolower(str[2]) == NIP_CH('u') && 
                _nip_tolower(str[3]) == NIP_CH('e'))
            {
                result = true;
            }
        } else if (len == 5) {
            if (_nip_tolower(str[0]) == NIP_CH('f') &&
                _nip_tolower(str[1]) == NIP_CH('a') &&
                _nip_tolower(str[2]) == NIP_CH('l') &&
                _nip_tolower(str[3]) == NIP_CH('s') &&
                _nip_tolower(str[4]) == NIP_CH('e'))
            {
                result = false;
            }
        } else {
            return NIP_ERROR_INVALID_CHARACTER;
        }
    } else {
        if (len == 1) {
            result = str[0] != NIP_CH('0');
        } else if (len == 5) {
            if (_nip_tolower(str[0]) == NIP_CH('f') &&
                _nip_tolower(str[1]) == NIP_CH('a') &&
                _nip_tolower(str[2]) == NIP_CH('l') &&
                _nip_tolower(str[3]) == NIP_CH('s') &&
                _nip_tolower(str[4]) == NIP_CH('e'))
            {
                result = false;
            } else {
                result = true;
            }
        } else {
            result = true;
        }
    }

    switch (kv->value_type) {
    case NIP_VALUE_TYPE_BOOL8:
        *(int8_t *)kv->value_ptr = result;
        break;
    case NIP_VALUE_TYPE_BOOL16:
        *(int16_t *)kv->value_ptr = result;
        break;
    case NIP_VALUE_TYPE_BOOL32:
        *(int32_t *)kv->value_ptr = result;
        break;
    case NIP_VALUE_TYPE_BOOL64:
        *(int64_t *)kv->value_ptr = result;
        break;
    case NIP_VALUE_TYPE_BOOL:
        *(bool *)kv->value_ptr = result;
        break;
    }

    return NIP_OK;
}

// ========================================================================== //

static NipError _nip_parse_integer_kv(Nip1 *nip, NipKV *kv, const NipChar *str, size_t len) {
    NIP_UNREFERENCED_PARAMETER(nip);

    NIP_ASSERT(nip, "invalid argument");
    NIP_ASSERT(kv, "invalid argument");

    // This is used for numbers in bases other that 10,
    // as most significant bit is the sign.
    // Only for signed integers.
    uint64_t sign_mask = 0;
    switch (kv->value_type) {
    case NIP_VALUE_TYPE_INT8:
        sign_mask = (uint64_t)1 << 7;
        break;
    case NIP_VALUE_TYPE_INT16:
        sign_mask = (uint64_t)1 << 15;
        break;
    case NIP_VALUE_TYPE_INT32:
        sign_mask = (uint64_t)1 << 31;
        break;
    case NIP_VALUE_TYPE_INT64:
        sign_mask = (uint64_t)1 << 63;
        break;
    }

    bool has_range = (kv->flags & NIP_KV_FLAGS_HAS_RANGE) != 0;
    bool clamp_on_err = (kv->flags & NIP_KV_FLAGS_CLAMP_ON_ERROR) != 0;

    uint64_t result = 0;
    bool is_negative = false;
    NipError err = _nip_parse_integer(str, len, sign_mask, &result, &is_negative);
    if (NIP_FAILED(err)) {
        if (err == NIP_ERROR_OUT_OF_RANGE && clamp_on_err) {
            // This will make the value to be range checked in switch below.
            result = UINT64_MAX;
        } else {
            return err;
        }
    }

    #define CHECK_INT_RANGE_AND_ASSIGN(TValue, maxT, m) do { \
        TValue value; \
        if (is_negative) { \
            if (result > (uint64_t)maxT + 1) { \
                if (!clamp_on_err) { \
                    return NIP_ERROR_OUT_OF_RANGE; \
                } else { \
                    value = -maxT - 1; \
                } \
            } else { \
                value = -((TValue)result); \
            } \
        } else { \
            if (result > (uint64_t)maxT) { \
                if (!clamp_on_err) { \
                    return NIP_ERROR_OUT_OF_RANGE; \
                } else { \
                    value = maxT; \
                } \
            } else { \
                value = (TValue)result; \
            } \
        } \
        if (has_range) { \
            TValue v_min = kv->min_value.m; \
            TValue v_max = kv->max_value.m; \
            if (value < v_min) { \
                if (!clamp_on_err) { \
                    return NIP_ERROR_OUT_OF_RANGE; \
                } \
                value = v_min; \
            } else if (value > v_max) { \
                if (!clamp_on_err) { \
                    return NIP_ERROR_OUT_OF_RANGE; \
                } \
                value = v_max; \
            } \
        } \
        *(TValue *)kv->value_ptr = value; \
    } while (0)

    #define CHECK_UINT_RANGE_AND_ASSIGN(TValue, maxT, m) do { \
        TValue value; \
        if (is_negative) { \
            if (!clamp_on_err) { \
                return NIP_ERROR_OUT_OF_RANGE; \
            } else { \
                value = 0; \
            } \
        } else { \
            if (result > (uint64_t)maxT) { \
                if (!clamp_on_err) { \
                    return NIP_ERROR_OUT_OF_RANGE; \
                } else { \
                    value = maxT; \
                } \
            } else { \
                value = (TValue)result; \
            } \
        } \
        if (has_range) { \
            TValue v_min = kv->min_value.m; \
            TValue v_max = kv->max_value.m; \
            if (value < v_min) { \
                if (!clamp_on_err) { \
                    return NIP_ERROR_OUT_OF_RANGE; \
                } \
                value = v_min; \
            } else if (value > v_max) { \
                if (!clamp_on_err) { \
                    return NIP_ERROR_OUT_OF_RANGE; \
                } \
                value = v_max; \
            } \
        } \
        *(TValue *)kv->value_ptr = value; \
    } while (0)

    switch (kv->value_type) {
    case NIP_VALUE_TYPE_INT8:
        CHECK_INT_RANGE_AND_ASSIGN(int8_t, INT8_MAX, i8);
        break;
    case NIP_VALUE_TYPE_INT16:
        CHECK_INT_RANGE_AND_ASSIGN(int16_t, INT16_MAX, i16);
        break;
    case NIP_VALUE_TYPE_INT32:
        CHECK_INT_RANGE_AND_ASSIGN(int32_t, INT32_MAX, i32);
        break;
    case NIP_VALUE_TYPE_INT64:
        CHECK_INT_RANGE_AND_ASSIGN(int64_t, INT64_MAX, i64);
        break;
    case NIP_VALUE_TYPE_UINT8:
        CHECK_UINT_RANGE_AND_ASSIGN(uint8_t, UINT8_MAX, u8);
        break;
    case NIP_VALUE_TYPE_UINT16:
        CHECK_UINT_RANGE_AND_ASSIGN(uint16_t, UINT16_MAX, u16);
        break;
    case NIP_VALUE_TYPE_UINT32:
        CHECK_UINT_RANGE_AND_ASSIGN(uint32_t, UINT32_MAX, u32);
        break;
    case NIP_VALUE_TYPE_UINT64:
        CHECK_UINT_RANGE_AND_ASSIGN(uint64_t, UINT64_MAX, u64);
        break;
    }

    #undef CHECK_INT_RANGE_AND_ASSIGN
    #undef CHECK_UINT_RANGE_AND_ASSIGN

    return NIP_OK;
}

// ========================================================================== //

static NipError _nip_parse_float_kv(Nip1 *nip, NipKV *kv, const NipChar *str, size_t len) {
    NIP_UNREFERENCED_PARAMETER(nip);

    NIP_ASSERT(nip, "invalid argument");
    NIP_ASSERT(kv, "invalid argument");

    bool has_range = (kv->flags & NIP_KV_FLAGS_HAS_RANGE) != 0;
    bool clamp_on_err = (kv->flags & NIP_KV_FLAGS_CLAMP_ON_ERROR) != 0;

    if (kv->value_type == NIP_VALUE_TYPE_FLOAT32) {
        float result;
        bool is_negative;
        NipError err = _nip_parse_float32(str, len, &result, &is_negative);
        if (NIP_FAILED(err)) {
            if (err == NIP_ERROR_OUT_OF_RANGE && clamp_on_err) {
                result = is_negative ? -FLT_MAX : FLT_MAX;                
            } else {
                return err;
            }
        }

        if (!isnan(result) && !isinf(result)) {
            if (has_range) {
                float v_min = kv->min_value.f32;
                float v_max = kv->max_value.f32;
                if (result < v_min) {
                    if (!clamp_on_err) {
                        return NIP_ERROR_OUT_OF_RANGE;
                    }
                    result = v_min;
                } else if (result > v_max) {
                    if (!clamp_on_err) {
                        return NIP_ERROR_OUT_OF_RANGE;
                    }
                    result = v_max;
                }
            }
        }

        *(float *)kv->value_ptr = result;
    } else {
        double result;
        bool is_negative;
        NipError err = _nip_parse_float64(str, len, &result, &is_negative);
        if (NIP_FAILED(err)) {
            if (err == NIP_ERROR_OUT_OF_RANGE && clamp_on_err) {
                result = is_negative ? -DBL_MAX : DBL_MAX;                
            } else {
                return err;
            }
        }

        if (!isnan(result) && !isinf(result)) {
            if (has_range) {
                double v_min = kv->min_value.f64;
                double v_max = kv->max_value.f64;
                if (result < v_min) {
                    if (!clamp_on_err) {
                        return NIP_ERROR_OUT_OF_RANGE;
                    }
                    result = v_min;
                } else if (result > v_max) {
                    if (!clamp_on_err) {
                        return NIP_ERROR_OUT_OF_RANGE;
                    }
                    result = v_max;
                }
            }
        }

        *(double *)kv->value_ptr = result;
    }

    return NIP_OK;
}

// ========================================================================== //

static NipError _nip_parse_string_kv(Nip1 *nip, NipKV *kv, const NipChar *str, size_t len) {
    NIP_UNREFERENCED_PARAMETER(nip);

    NIP_ASSERT(nip, "invalid argument");
    NIP_ASSERT(kv, "invalid argument");

    NipChar *data;
    if (kv->value_type == NIP_VALUE_TYPE_STRING) {
        data = malloc(sizeof(NipChar) * (len + 1));
        if (data == NULL) {
            return NIP_ERROR_OUT_OF_MEMORY;
        }

        *(NipChar **)kv->value_ptr = data;
    } else {
        if (len + 1 > kv->extra_info.buf_size) {
            return NIP_ERROR_INSUFFICEINT_BUFFER;
        }

        data = (NipChar *)kv->value_ptr;
    }

    memcpy(data, str, len);
    data[len] = NIP_CH('\0');

    return NIP_OK;
}

// ========================================================================== //

static NipError _nip_assign_def_value(Nip1 *nip, NipKV *kv) {
    NIP_ASSERT(nip, "invalid argument");
    NIP_ASSERT(kv, "invalid argument");

    NIP_ASSERT((kv->flags & NIP_KV_FLAGS_HAS_DEFAULT) != 0, "kv doesn't have default value set");

    #define ASSIGN_DEFAULT(TValue, m) *(TValue *)kv->value_ptr = kv->def_value.m

    switch (kv->value_type) {
    case NIP_VALUE_TYPE_BOOL8:   ASSIGN_DEFAULT(int8_t,     i8);    break;
    case NIP_VALUE_TYPE_BOOL16:  ASSIGN_DEFAULT(int16_t,    i16);   break;
    case NIP_VALUE_TYPE_BOOL32:  ASSIGN_DEFAULT(int32_t,    i32);   break;
    case NIP_VALUE_TYPE_BOOL64:  ASSIGN_DEFAULT(int64_t,    i64);   break;
    case NIP_VALUE_TYPE_INT8:    ASSIGN_DEFAULT(int8_t,     i8);    break;
    case NIP_VALUE_TYPE_INT16:   ASSIGN_DEFAULT(int16_t,    i16);   break;
    case NIP_VALUE_TYPE_INT32:   ASSIGN_DEFAULT(int32_t,    i32);   break;
    case NIP_VALUE_TYPE_INT64:   ASSIGN_DEFAULT(int64_t,    i64);   break;
    case NIP_VALUE_TYPE_UINT8:   ASSIGN_DEFAULT(uint8_t,    u8);    break;
    case NIP_VALUE_TYPE_UINT16:  ASSIGN_DEFAULT(uint16_t,   u16);   break;
    case NIP_VALUE_TYPE_UINT32:  ASSIGN_DEFAULT(uint32_t,   u32);   break;
    case NIP_VALUE_TYPE_UINT64:  ASSIGN_DEFAULT(uint64_t,   u64);   break;
    case NIP_VALUE_TYPE_FLOAT32: ASSIGN_DEFAULT(float,      f32);   break;
    case NIP_VALUE_TYPE_FLOAT64: ASSIGN_DEFAULT(double,     f64);   break;
    case NIP_VALUE_TYPE_BOOL:    ASSIGN_DEFAULT(bool,       b);     break;

    case NIP_VALUE_TYPE_STRING:
    case NIP_VALUE_TYPE_CHAR_BUFFER:
        // We can use _nip_parse_string_kv here.
        return _nip_parse_string_kv(nip, kv, kv->def_value.str, kv->max_value.def_str_len);

    case NIP_VALUE_TYPE_CUSTOM:
        if (kv->copy_fn) {
            int cerr = kv->copy_fn(kv->value_ptr, kv->def_value.str);
            if (cerr < 0) {
                return NIP_ERROR_FAILED_TO_COPY_DEFAULT_VALUE;
            }
        } else {
            NIP_PANIC("specified custom def_value without copy_fn");
        }
        break;

    default:
        NIP_PANIC("unsupported type");
        break;
    }

    #undef ASSIGN_DEFAULT

    return NIP_OK;
}

// ========================================================================== //

static NipError _nip_parse_value(Nip1 *nip, NipKV *kv, NipToken token) {
    NIP_ASSERT(nip, "invalid argument");
    NIP_ASSERT(kv, "invalid argument");

    const NipChar *str = token.str;
    size_t len = token.len;

    if (kv->decoder) {
        int derr = kv->decoder(str, len, kv->value_ptr);
        if (derr != 0) {
            nip->decoder_error = derr;
            return NIP_ERROR_DECODER_FAILURE;
        } else {
            return NIP_OK;
        }
    }

    NipError err;
    switch (kv->value_type) {
    case NIP_VALUE_TYPE_BOOL:
    case NIP_VALUE_TYPE_BOOL8:
    case NIP_VALUE_TYPE_BOOL16:
    case NIP_VALUE_TYPE_BOOL32:
    case NIP_VALUE_TYPE_BOOL64:
        err = _nip_parse_bool_kv(nip, kv, str, len);
        break;

    case NIP_VALUE_TYPE_INT8:
    case NIP_VALUE_TYPE_INT16:
    case NIP_VALUE_TYPE_INT32:
    case NIP_VALUE_TYPE_INT64:
    case NIP_VALUE_TYPE_UINT8:
    case NIP_VALUE_TYPE_UINT16:
    case NIP_VALUE_TYPE_UINT32:
    case NIP_VALUE_TYPE_UINT64:
        err = _nip_parse_integer_kv(nip, kv, str, len);
        break;

    case NIP_VALUE_TYPE_FLOAT32:
    case NIP_VALUE_TYPE_FLOAT64:
        err = _nip_parse_float_kv(nip, kv, str, len);
        break;

    case NIP_VALUE_TYPE_STRING:
    case NIP_VALUE_TYPE_CHAR_BUFFER:
        err = _nip_parse_string_kv(nip, kv, str, len);
        break;

    default:
        NIP_PANIC("invalid type");
        break;
    }

    // Assign default on error.
    if (NIP_FAILED(err)) {
        bool has_default = (kv->flags & NIP_KV_FLAGS_HAS_DEFAULT) != 0;
        bool def_on_err = (kv->flags & NIP_KV_FLAGS_DEFAULT_ON_ERROR) != 0;
        if (has_default && def_on_err) {
            err = _nip_assign_def_value(nip, kv);
        }
    }

    return err;
}

// ========================================================================== //

static NipError _nip_error(Nip1 *nip, const NipToken token, NipError err_code) {
    if (token.type > 0) {
        nip->error.line   = nip->line;
        nip->error.column = nip->pos - nip->line_start_pos;
        nip->error.start  = (uintptr_t)(token.str - nip->buffer.ptr);
        nip->error.code   = err_code;
    }

    return err_code;
}

// ========================================================================== //

static NipError _nip_parse_kv(Nip1 *nip, const NipToken key_tok) {
    if (nip->current_section == NULL) {
        return _nip_error(nip, key_tok, NIP_ERROR_MISSING_SECTION_BEFORE_KEY);
    }

    NipKV *kv = _nip_find_kv(nip->current_section, key_tok.str, key_tok.len);
    if (kv == NULL) {
        return _nip_error(nip, key_tok, NIP_ERROR_INVALID_KEY_NAME);
    }

    nip->current_kv = kv;

    if ((kv->flags & NIP_KV_FLAGS_ALREADY_USED) != 0) {
        return _nip_error(nip, key_tok, NIP_ERROR_DUPLICATED_KEY_NAME);
    }

    NipToken eq_tok = _nip_get_next_token(nip);
    if (eq_tok.type != NIP_TOKEN_EQUAL) {
        return _nip_error(nip, eq_tok, NIP_ERROR_EXPECTED_EQUAL_SIGN);
    }

    NipToken token = _nip_get_next_token(nip);
    if (token.type != NIP_TOKEN_IDENDIFIER &&
        token.type != NIP_TOKEN_NUMBER &&
        token.type != NIP_TOKEN_STRING)
    {
        return _nip_error(nip, token, NIP_ERROR_EXPECTED_VALUE);
    }

    NipError err = _nip_parse_value(nip, kv, token);
    if (NIP_FAILED(err)) {
        return err;
    }

    kv->flags |= NIP_KV_FLAGS_ALREADY_USED;

    return NIP_OK;
}

// ========================================================================== //

static NipError _nip_parse_section(Nip1 *nip) {
    // Read section name.
    NipToken name_tok = _nip_get_next_token(nip);
    if (name_tok.type != NIP_TOKEN_IDENDIFIER) {
        return _nip_error(nip, name_tok, NIP_ERROR_EXPECTED_SECTION_NAME);
    }

    NipSection *section = _nip_find_section(nip, name_tok.str, name_tok.len);
    if (section == NULL) {
        return _nip_error(nip, name_tok, NIP_ERROR_INVALID_SECTION_NAME);
    }

    // Check if section was already processed.
    if (section->used) {
        return _nip_error(nip, name_tok, NIP_ERROR_DUPLICATED_SECTION_NAME);
    }

    NipToken r_bracket = _nip_get_next_token(nip);
    if (r_bracket.type != NIP_TOKEN_RBRACKET) {
        return _nip_error(nip, r_bracket, NIP_ERROR_EXPECTED_RBRACKET);
    }

    // Mark section as used.
    if (nip->current_section) {
        nip->current_section->used = true;
    }

    nip->current_section = section;

    return NIP_OK;
}

// ========================================================================== //

static NipError _nip_parse_line_internal(Nip1 *nip) {
    NIP_ASSERT(nip, "invalid argument");

    nip->line_start_pos = nip->pos;

    NipToken token = _nip_get_next_token(nip);

    // Skip line with no section/kv.
    if (token.type == NIP_TOKEN_EOL) {
        return NIP_OK;
    } 

    if (token.type == NIP_TOKEN_LBRACKET) {
        NipError err = _nip_parse_section(nip);
        if (NIP_FAILED(err)) {
            return err;
        }
    } else if (token.type == NIP_TOKEN_IDENDIFIER) {
        NipError err = _nip_parse_kv(nip, token);
        if (NIP_FAILED(err)) {
            return err;
        }
    } else {
        return _nip_error(nip, token, NIP_ERROR_EXPECTED_SECTION_OR_KEY);
    }

    // Skip rest of the line
    NipToken eol_tok = _nip_get_next_token(nip);
    if (eol_tok.type != NIP_TOKEN_EOL) {
        return _nip_error(nip, eol_tok, NIP_ERROR_INVALID_CHARACTER);
    }

    nip->line += 1;

    return NIP_OK;
}

// ========================================================================== //

#pragma endregion

#pragma region "Internal Functions"

// ========================================================================== //

static NipSection *_nip_alloc_section(Nip1 *nip) {
    NIP_ASSERT(nip, "invalid argument");

    if (nip->sections.len + 1 > nip->sections.cap) {
        uint32_t new_capacity = nip->sections.cap + 16;

        NipSection *new_sections_ptr = realloc(nip->sections.ptr, sizeof(NipSection) * new_capacity);
        if (new_sections_ptr == NULL) {
            return NULL;
        }

        nip->sections.ptr = new_sections_ptr;
        nip->sections.cap = new_capacity;
    }

    uint32_t index = nip->sections.len;
    nip->sections.len += 1;

    return &nip->sections.ptr[index];
}

// ========================================================================== //

static NipKV *_nip_alloc_kv(NipSection *section) {
    NIP_ASSERT(section, "invalid argument");

    if (section->kv.len + 1 > section->kv.cap) {
        uint32_t new_capacity = section->kv.cap + 32;

        NipKV *new_kv_ptr = realloc(section->kv.ptr, sizeof(NipKV) * new_capacity);
        if (new_kv_ptr == NULL) {
            return NULL;
        }

        section->kv.ptr = new_kv_ptr;
        section->kv.cap = new_capacity;
    }

    uint32_t index = section->kv.len;
    section->kv.len += 1;

    return &section->kv.ptr[index];
}

// ========================================================================== //

uint8_t _nip_generate_flags(const Nip1* nip, const NipKvDesc *desc) {
    uint8_t flags = 0;

    if (desc->def_value.type != 0) {
        flags |= NIP_KV_FLAGS_HAS_DEFAULT;
    }

    bool always_def_on_err = (nip->options & NIP_OPTIONS_ALWAYS_DEFAULT_ON_ERROR) != 0;
    if (always_def_on_err || (desc->flags & NIP_KV_FLAGS_DEFAULT_ON_ERROR) != 0) {
        flags |= NIP_KV_FLAGS_DEFAULT_ON_ERROR;
    }

    if (desc->range.type != 0) {
        flags |= NIP_KV_FLAGS_HAS_RANGE;
    }

    bool always_clamp_on_err = (nip->options & NIP_OPTIONS_ALWAYS_CLAMP_ON_ERROR) != 0;
    if (always_clamp_on_err || (desc->flags & NIP_KV_FLAGS_CLAMP_ON_ERROR) != 0) {
        flags |= NIP_KV_FLAGS_CLAMP_ON_ERROR;
    }

    if ((desc->flags & NIP_KV_FLAGS_WRITE_AS_HEX) != 0) {
        flags |= NIP_KV_FLAGS_WRITE_AS_HEX;
    }

    return flags;
}

// ========================================================================== //

#pragma endregion

#pragma region "Public API"

// ========================================================================== //

NipError nip_init(Nip1 *nip, NipOptions options, uint32_t num_sections) {
    NIP_ASSERT(nip, "invalid argument");
    if (nip == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    nip->sections.ptr       = NULL;
    nip->sections.len       = 0;
    nip->sections.cap       = 0;
    nip->current_section    = NULL;
    nip->decoder_error      = 0;
    nip->options            = options;
    nip->buffer.ptr         = NULL;
    nip->buffer.len         = 0;
    nip->line               = 1;
    nip->line_start_pos     = 0;

    if (num_sections > 0) {
        NipSection *new_sections_ptr = realloc(nip->sections.ptr, sizeof(NipSection) * num_sections);
        if (new_sections_ptr == NULL) {
            return NIP_ERROR_OUT_OF_MEMORY;
        }

        nip->sections.ptr = new_sections_ptr;
        nip->sections.cap = num_sections;
    }

    return NIP_OK;
}

// ========================================================================== //

NipError nip_deinit(Nip1 *nip) {
    NIP_ASSERT(nip, "invalid argument");
    if (nip == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    if (nip->sections.ptr != NULL) {
        for (uint32_t i = 0; i < nip->sections.len; i += 1) {
            NipSection *section = &nip->sections.ptr[i];
            free(section->kv.ptr);
        }

        free(nip->sections.ptr);
        nip->sections.ptr = NULL;
    }

    nip->sections.len = 0;
    nip->sections.cap = 0;

    return NIP_OK;
}

// ========================================================================== //

NipError nip_parse(Nip1 *nip, const char *buffer, size_t len) {
    NIP_ASSERT(nip, "invalid argument");
    if (nip == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    if (buffer == NULL) {
        return NIP_OK;
    }

    NIP_ASSERT(nip->current_section == NULL, "didn't end section, call nip_end_section()");

    nip->buffer.ptr = buffer;
    nip->buffer.len = len;
    nip->pos        = 0;

    while (nip->pos < nip->buffer.len) {
        NipError err = _nip_parse_line_internal(nip);
        if (NIP_FAILED(err)) {
            return err;
        }
    }

    NipError err = nip_parse_finish(nip);
    if (NIP_FAILED(err)) {
        return err;
    }

    return NIP_OK;
}

// ========================================================================== //

NipError nip_parse_line(Nip1 *nip, const char *buffer, size_t len) {
    NIP_ASSERT(nip, "invalid argument");
    NIP_ASSERT(buffer, "invalid argument");
    if (nip == NULL || buffer == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    nip->buffer.ptr = buffer;
    nip->buffer.len = len;
    nip->pos        = 0;

    NipError err = _nip_parse_line_internal(nip);
    if (NIP_FAILED(err)) {
        return err;
    }

    return NIP_OK;
}

// ========================================================================== //

NipError nip_parse_finish(Nip1 *nip) {
    NIP_ASSERT(nip, "invalid argument");
    if (nip == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    for (uint32_t i = 0; i < nip->sections.len; i += 1) {
        NipSection *section = &nip->sections.ptr[i];
        if (!section->used && !section->optional) {
            for (uint32_t j = 0; j < section->kv.len; j += 1) {
                NipKV *kv = &section->kv.ptr[j];
                if ((kv->flags & NIP_KV_FLAGS_ALREADY_USED) == 0) {
                    if ((kv->flags & NIP_KV_FLAGS_HAS_DEFAULT) == 0) {
                        return NIP_ERROR_MISSING_KEY_VALUE;
                    } else {
                        NipError err = _nip_assign_def_value(nip, kv);
                        if (NIP_FAILED(err)) {
                            return err;
                        }
                    }
                }
            }
        }
    }

    return NIP_OK;
}

// ========================================================================== //

NipError nip_begin_section(Nip1 *nip, const char *name, bool optional, uint32_t num_kv) {
    NIP_ASSERT(nip, "invalid argument");
    if (nip == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    NIP_ASSERT(name, "invalid argument");
    NIP_ASSERT(nip->current_section == NULL, "section not closed, call nip_end_section() first");

#ifdef _DEBUG
    bool validate = true;
#else
    bool validate = (nip->options & NIP_OPTIONS_VALIDATE_ON_RELEASE) != 0;
#endif

    if (validate) {
        NipError err = _nip_is_valid_section_name(nip, name);
        if (NIP_FAILED(err)) {
            return err;
        }
    }

    NIP_ASSERT(name != NULL, "name is null");

    NipSection *section = _nip_alloc_section(nip);
    if (section == NULL) {
        return NIP_ERROR_OUT_OF_MEMORY;
    }

    section->name.ptr   = name;
    section->name.len   = _nip_strnlen(name, NIP_MAX_SECTION_NAME_LENGTH);
    section->kv.ptr     = NULL;
    section->kv.len     = 0;
    section->kv.cap     = 0;
    section->used       = false;
    section->optional   = optional;
    section->comment    = NULL;

    nip->current_section = section;

    if (num_kv > 0) {
        NipKV *new_kv_ptr = realloc(section->kv.ptr, sizeof(NipKV) * num_kv);
        if (new_kv_ptr == NULL) {
            return NIP_ERROR_OUT_OF_MEMORY;
        }

        section->kv.ptr = new_kv_ptr;
        section->kv.cap = num_kv;
    }

    return NIP_OK;
}

// ========================================================================== //

NipError nip_end_section(Nip1 *nip) {
    NIP_ASSERT(nip, "invalid argument");
    if (nip == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    NIP_ASSERT(nip->current_section, "unknown section, call nip_begin_section() first");
    NIP_ASSERT(nip->current_section->kv.len != 0, "empty section");

    nip->current_section = NULL;

    return NIP_OK;
}

// ========================================================================== //

NipError nip_push(Nip1 *nip, const NipKvDesc desc) {
    NIP_ASSERT(nip, "invalid argument");
    if (nip == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    NIP_ASSERT(nip->current_section, "unknown section, call nip_begin_section() first");
    if (nip->current_section == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    uint8_t flags = _nip_generate_flags(nip, &desc);

#ifdef _DEBUG
    bool validate = true;
#else
    bool validate = (nip->options & NIP_OPTIONS_VALIDATE_ON_RELEASE) != 0;
#endif

    if (validate) {
        NipError err = _nip_is_valid_key_name(nip, nip->current_section, desc.key);
        if (NIP_FAILED(err)) {
            return err;
        }

        if (!_nip_validate_desc(nip, &desc, flags)) {
            return NIP_ERROR_INVALID_VALUE_DESCRIPTION;
        }
    }

    NIP_ASSERT(desc.key != NULL, "key is null");
    NIP_ASSERT(desc.value.ptr.raw != NULL, "value ptr is null");

    NipKV *kv = _nip_alloc_kv(nip->current_section);
    if (kv == NULL) {
        return NIP_ERROR_OUT_OF_MEMORY;
    }

    kv->key         = desc.key;
    kv->value_ptr   = desc.value.ptr.raw;
    kv->comment     = desc.comment;
    kv->decoder     = desc.decoder;
    kv->copy_fn     = desc.def_value.copy_fn;    
    kv->value_type  = desc.value.type;
    kv->key_len     = (uint8_t)_nip_strnlen(desc.key, NIP_MAX_KEY_NAME_LENGTH);
    kv->flags       = flags;

    memcpy(&kv->def_value, &desc.def_value.data, sizeof(desc.def_value.data));
    memcpy(&kv->extra_info, &desc.value.extra_info, sizeof(desc.value.extra_info));

    memcpy(&kv->min_value, &desc.range.min, sizeof(desc.range.min));
    if (desc.value.type == NIP_VALUE_TYPE_STRING || desc.value.type == NIP_VALUE_TYPE_CHAR_BUFFER) {
        if (desc.def_value.type == desc.value.type) {
            size_t len = _nip_strnlen(desc.def_value.data.str, NIP_MAX_DEFAULT_STRING_LENGTH);
            kv->max_value.def_str_len = len;
        }
    } else {
        memcpy(&kv->max_value, &desc.range.max, sizeof(desc.range.max));
    }

    return NIP_OK;
}

// ========================================================================== //

NipError nip_dump(const Nip1 *nip, NipWriteFn write_fn, void *fp) {
    NIP_ASSERT(nip, "invalid argument");
    if (nip == NULL) {
        return NIP_ERROR_INVALID_ARGUMENT;
    }

    if ((nip->options & NIP_OPTIONS_DUMP) == 0) {
        return NIP_ERROR_DUMP_OPTION_NOT_SET;
    }

    for (uint32_t i = 0; i < nip->sections.len; i += 1) {
        NipSection *section = &nip->sections.ptr[i];
        if (!_nip_write_section(nip, section, write_fn, fp)) {
            return NIP_ERROR_WRITE_FAILED;
        }

        for (uint32_t j = 0; j < section->kv.len; j += 1) {
            NipKV *kv = &section->kv.ptr[j];
            if (!_nip_write_kv(nip, kv, write_fn, fp)) {
                return NIP_ERROR_WRITE_FAILED;
            }
        }
    }

    return NIP_OK;
}

// ========================================================================== //

#pragma endregion

#endif // NIP_IMPLEMENTATION

////////////////////////////////////////////////////////////////////////////////

#endif // NIP_H

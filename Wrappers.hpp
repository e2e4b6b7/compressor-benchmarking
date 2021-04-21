#pragma once

#include <cassert>

#include "lz4.h"
#include "zstd.h"

namespace wrappers {

size_t lz4_bound_wrapper(size_t src_len) {
    assert(src_len <= std::numeric_limits<int>::max());
    return static_cast<size_t>(LZ4_compressBound(static_cast<int>(src_len)));
}

size_t lz4_compress_wrapper(const char *src, size_t src_len, char *dst, size_t dst_len) {
    assert(src_len <= std::numeric_limits<int>::max());
    assert(dst_len <= std::numeric_limits<int>::max());
    return static_cast<size_t>(LZ4_compress_default(src, dst, static_cast<int>(src_len), static_cast<int>(dst_len)));
}

size_t lz4_decompress_wrapper(const char *src, size_t src_len, char *dst, size_t dst_len) {
    assert(src_len <= std::numeric_limits<int>::max());
    assert(dst_len <= std::numeric_limits<int>::max());
    return static_cast<size_t>(LZ4_decompress_safe(src, dst, static_cast<int>(src_len), static_cast<int>(dst_len)));
}

size_t (*const zstd_bound_wrapper)(size_t src_len) = ZSTD_compressBound;

size_t zstd_1_compress_wrapper(const char *src, size_t src_len, char *dst, size_t dst_len) {
    return ZSTD_compress(dst, dst_len, src, src_len, 1);
}

size_t zstd_7_compress_wrapper(const char *src, size_t src_len, char *dst, size_t dst_len) {
    return ZSTD_compress(dst, dst_len, src, src_len, 7);
}

size_t zstd_decompress_wrapper(const char *src, size_t src_len, char *dst, size_t dst_len) {
    return ZSTD_decompress(dst, dst_len, src, src_len);
}

} // namespace wrappers

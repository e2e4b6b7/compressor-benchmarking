#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>

namespace benchmark {

struct result {
    const uint64_t tic_count_compress;
    const uint64_t tic_count_decompress;
    const double compress_rate;
};

struct compressor {
    size_t (*const get_upper_bound)(size_t src_len);

    size_t (*const compress)(const char *src, size_t src_len, char *dst, size_t dst_len);

    size_t (*const decompress)(const char *src, size_t src_len, char *dst, size_t dst_len);
};

result benchmark_on_data(const char *src, size_t src_len, compressor compressor);

std::vector<result> benchmark_on_data(const char *src, size_t src_len, const std::vector<compressor> &compressors);

std::vector<result> benchmark_on_file(const std::string &filename, const std::vector<compressor> &compressors);

std::vector<std::vector<result>> benchmark_on_files(const std::vector<std::string> &filenames,
                                                    const std::vector<compressor> &compressors);

} // namespace benchmark

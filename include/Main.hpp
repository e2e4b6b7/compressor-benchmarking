#pragma once

#include <vector>
#include <string>

#include "Benchmark.hpp"
#include "Wrappers.hpp"

std::vector<std::pair<std::string, benchmark::compressor>> init_compressors() {
    using namespace wrappers;
    return {
            {"lz4",    {lz4_bound_wrapper,  lz4_compress_wrapper,    lz4_decompress_wrapper}},
            {"zstd_1", {zstd_bound_wrapper, zstd_1_compress_wrapper, zstd_decompress_wrapper}},
            {"zstd_7", {zstd_bound_wrapper, zstd_7_compress_wrapper, zstd_decompress_wrapper}}
    };
}

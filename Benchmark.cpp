#include <cstddef>
#include <cstdint>
#include <fstream>
#include <vector>
#include <cassert>
#include <iterator>

#include "Benchmark.hpp"

namespace benchmark {

inline __attribute__((always_inline))
uint64_t time_stamp() {
    unsigned int a, d;
    __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
    return static_cast<uint64_t>(a) | (static_cast<uint64_t>(d) << 32);
}

result benchmark_on_data(const char *src, size_t src_len, compressor compressor) {
    size_t upper_bound = compressor.get_upper_bound(src_len);

    char *dst = new char[upper_bound];
    char *src_copy = new char[src_len];

    uint64_t begin = time_stamp();
    size_t result_len = compressor.compress(src, src_len, dst, upper_bound);
    uint64_t end_compress = time_stamp();
    size_t decompress_size = compressor.decompress(dst, result_len, src_copy, src_len);
    uint64_t end_decompress = time_stamp();

    assert(decompress_size == src_len);

    delete[] dst;
    delete[] src_copy;

    return {
            end_compress - begin,
            end_decompress - end_compress,
            static_cast<double>(src_len) / static_cast<double>(result_len)
    };
}

std::vector<result> benchmark_on_data(const char *src, size_t src_len, const std::vector<compressor> &compressors) {
    std::vector<result> results;
    results.reserve(compressors.size());

    for (auto compressor : compressors) {
        results.emplace_back(benchmark_on_data(src, src_len, compressor));
    }

    return results;
}

std::vector<result> benchmark_on_file(const std::string &filename, const std::vector<compressor> &compressors) {
    std::ifstream file_stream(filename, std::ios_base::in | std::ios_base::binary);
    std::vector<char> file_content((std::istream_iterator<char>(file_stream)), std::istream_iterator<char>());

    const char *src = file_content.data();
    size_t src_len = file_content.size();

    return benchmark_on_data(src, src_len, compressors);
}

std::vector<std::vector<result>> benchmark_on_files(const std::vector<std::string> &filenames,
                                                    const std::vector<compressor> &compressors) {
    std::vector<std::vector<result>> results;
    results.reserve(filenames.size());
    for (const std::string &filename : filenames) {
        results.emplace_back(benchmark_on_file(filename, compressors));
    }
    return results;
}

} // namespace benchmark

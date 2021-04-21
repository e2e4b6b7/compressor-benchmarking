#include <iterator>
#include <fstream>

#include "Main.hpp"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(compression_decompression, simple) {
    std::vector<std::pair<std::string, benchmark::compressor>> compressors = init_compressors();
    std::ifstream file_stream("CMakeLists.txt", std::ios_base::in | std::ios_base::binary);
    std::vector<char> file_content((std::istream_iterator<char>(file_stream)), std::istream_iterator<char>());

    const char *src = file_content.data();
    size_t src_len = file_content.size();

    for (auto &[name, compressor] : compressors) {
        size_t upper_bound = compressor.get_upper_bound(src_len);

        char *dst = new char[upper_bound];
        char *src_copy = new char[src_len];

        size_t result_len = compressor.compress(src, src_len, dst, upper_bound);
        size_t decompress_size = compressor.decompress(dst, result_len, src_copy, src_len);

        ASSERT_EQ(decompress_size, src_len);

        for (size_t i = 0; i < decompress_size; ++i) {
            ASSERT_EQ(src[i], src_copy[i]);
        }

        delete[] dst;
        delete[] src_copy;
    }
}
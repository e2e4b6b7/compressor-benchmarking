#include <iostream>
#include <fstream>
#include <vector>

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

std::vector<std::string> init_files(int argc, char **argv) {
    std::vector<std::string> files;
    files.reserve(argc);
    for (int i = 0; i < argc; ++i) {
        files.emplace_back(argv[i]);
    }
    return files;
}

void write_to_file(const std::vector<std::vector<benchmark::result>> &results,
                   const std::vector<std::string> &files,
                   const std::vector<std::string> &compressors) {
    std::ofstream out("speed.csv");
    out << "filename";
    for (const std::string &compressor : compressors) {
        out << ',' << compressor;
    }
    out << '\n';
    assert(files.size() == results.size());
    for (size_t i = 0; i < files.size(); ++i) {
        out << files[i];
        for (const benchmark::result &result : results[i]) {
            out << ',' << result.tic_count_compress;
        }
        out << '\n';
    }
    out.close();

    out.open("compression.csv");
    out << "filename";
    for (const std::string &compressor : compressors) {
        out << ',' << compressor;
    }
    out << '\n';
    assert(files.size() == results.size());
    for (size_t i = 0; i < files.size(); ++i) {
        out << files[i];
        for (const benchmark::result &result : results[i]) {
            out << ',' << result.compress_rate;
        }
        out << '\n';
    }
    out.close();

    out.open("speed_decompression.csv");
    out << "filename";
    for (const std::string &compressor : compressors) {
        out << ',' << compressor;
    }
    out << '\n';
    assert(files.size() == results.size());
    for (size_t i = 0; i < files.size(); ++i) {
        out << files[i];
        for (const benchmark::result &result : results[i]) {
            out << ',' << result.tic_count_decompress;
        }
        out << '\n';
    }
}

int main(int argc, char **argv) {
    std::vector<std::pair<std::string, benchmark::compressor>> compressors = init_compressors();
    std::vector<std::string> files = init_files(argc - 1, argv + 1);

    std::vector<benchmark::compressor> compressors_unnamed;
    compressors_unnamed.reserve(compressors.size());
    for (auto &compressor : compressors) {
        compressors_unnamed.emplace_back(compressor.second);
    }

    std::vector<std::string> compressors_names;
    compressors_names.reserve(compressors.size());
    for (auto &compressor : compressors) {
        compressors_names.emplace_back(compressor.first);
    }

    std::vector<std::vector<benchmark::result>> results =
            benchmark::benchmark_on_files(files, compressors_unnamed);

    write_to_file(results, files, compressors_names);
}

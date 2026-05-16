#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <zlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/sysinfo.h>
#endif

namespace fs = std::filesystem;

int run(const std::string& cmd) {
    std::cout << "Executing: " << cmd << std::endl;
    return std::system(cmd.c_str());
}

int detect_ram_gb() {
#ifdef _WIN32
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return static_cast<int>(status.ullTotalPhys / (1024ULL * 1024ULL * 1024ULL));
#else
    struct sysinfo info;
    sysinfo(&info);
    return static_cast<int>(info.totalram / (1024ULL * 1024ULL * 1024ULL));
#endif
}

bool compress_with_ratio(const std::string& input, const std::string& output, int ratio) {
    std::ifstream in(input, std::ios::binary);
    if (!in) return false;

    std::vector<char> data((std::istreambuf_iterator<char>(in)), {});
    uLong srcLen = data.size();
    uLong destLen = srcLen / ratio + 64;

    std::vector<Bytef> compressed(destLen);
    if (compress(compressed.data(), &destLen,
                 reinterpret_cast<const Bytef*>(data.data()), srcLen) != Z_OK) {
        return false;
    }

    std::ofstream out(output, std::ios::binary);
    out.write(reinterpret_cast<char*>(compressed.data()), destLen);
    return true;
}

bool install_and_compress(const std::string& pkg_cmd, const std::string& pkg_file, int ratio) {
    if (run(pkg_cmd) != 0) {
        std::cerr << "Package installation failed." << std::endl;
        return false;
    }
    std::cout << "Installed package: " << pkg_file << std::endl;

    std::string compressed = pkg_file + ".zip";
    if (!compress_with_ratio(pkg_file, compressed, ratio)) {
        std::cerr << "Package compression failed." << std::endl;
        return false;
    }
    std::cout << "Compressed package ready: " << compressed << std::endl;
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: recipypes_cook <source.cpp | package.whl>" << std::endl;
        return 1;
    }

    std::string target = argv[1];
    int ram_gb = detect_ram_gb();
    int ratio = 3;
    if (ram_gb >= 16) ratio = 10;
    if (ram_gb >= 64) ratio = 50;

    if (fs::path(target).extension() == ".cpp") {
        std::string binary = "dish.out";
        std::string compile_cmd = "g++ -O2 -o " + binary + " " + target;
        if (run(compile_cmd) != 0) return 1;

        std::cout << "Applying " << ratio << ":1 compression..." << std::endl;
        compress_with_ratio(binary, binary + ".zip", ratio);
    } else {
        std::string install_cmd = "pip install " + target;
        install_and_compress(install_cmd, target, ratio);
    }

    return 0;
}

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// Simple OS detection
#if defined(_WIN32) || defined(_WIN64)
#define IS_WINDOWS
#include <windows.h>
#include <pdh.h>
#pragma comment(lib, "pdh.lib")
#elif defined(__linux__)
#define IS_LINUX
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/statvfs.h>
#elif defined(__APPLE__) || defined(__MACH__)
#define IS_MACOS
#include <sys/sysctl.h>
#include <sys/statvfs.h>
#include <mach/mach.h>
#endif

std::string getRAM() {
    #if defined(_WIN32) || defined(_WIN64)
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return std::to_string(status.ullTotalPhys / (1024 * 1024)) + " MB";
    #elif defined(__linux__)
    struct sysinfo info;
    sysinfo(&info);
    return std::to_string(info.totalram / (1024 * 1024)) + " MB";
    #elif defined(__APPLE__) || defined(__MACH__)
    uint64_t mem;
    size_t len = sizeof(mem);
    sysctlbyname("hw.memsize", &mem, &len, NULL, 0);
    return std::to_string(mem / (1024 * 1024)) + " MB";
    #else
    return "Unknown";
    #endif
}

std::string getKernelVersion() {
    #if defined(_WIN32) || defined(_WIN64)
    return "Windows Kernel";
    #elif defined(__linux__)
    std::ifstream versionFile("/proc/version");
    std::string version;
    std::getline(versionFile, version);
    return version;
    #elif defined(__APPLE__) || defined(__MACH__)
    return "Darwin Kernel";
    #else
    return "Unknown";
    #endif
}

std::string getGPU() {
    #if defined(_WIN32) || defined(_WIN64)
    return "Windows GPU";
    #elif defined(__linux__)
    std::ifstream gpuFile("/proc/driver/nvidia/version");
    std::string gpu;
    if (gpuFile.is_open()) {
        std::getline(gpuFile, gpu);
    }
    return gpu.empty() ? "Unknown GPU" : gpu;
    #elif defined(__APPLE__) || defined(__MACH__)
    return "Apple GPU";
    #else
    return "Unknown";
    #endif
}

std::string getDiskUsage() {
    #if defined(_WIN32) || defined(_WIN64)
    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;
    if (GetDiskFreeSpaceEx("C:\\", &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
        return std::to_string((totalNumberOfBytes.QuadPart - totalNumberOfFreeBytes.QuadPart) / (1024 * 1024)) + " MB used";
    } else {
        return "Unknown";
    }
    #elif defined(__linux__)
    struct statvfs stat;
    if (statvfs("/", &stat) != 0) {
        return "Unknown";
    }
    return std::to_string((stat.f_blocks - stat.f_bfree) * stat.f_frsize / (1024 * 1024)) + " MB used";
    #elif defined(__APPLE__) || defined(__MACH__)
    struct statvfs stat;
    if (statvfs("/", &stat) != 0) {
        return "Unknown";
    }
    return std::to_string((stat.f_blocks - stat.f_bfree) * stat.f_frsize / (1024 * 1024)) + " MB used";
    #else
    return "Unknown";
    #endif
}

std::string getNetworkInfo() {
    #if defined(_WIN32) || defined(_WIN64)
    return "Windows Network";
    #elif defined(__linux__)
    std::ifstream netFile("/proc/net/dev");
    std::string line, networkInfo;
    if (netFile.is_open()) {
        while (std::getline(netFile, line)) {
            networkInfo += line + "\n";
        }
    }
    return networkInfo.empty() ? "Unknown Network" : networkInfo;
    #elif defined(__APPLE__) || defined(__MACH__)
    return "Apple Network";
    #else
    return "Unknown";
    #endif
}

int main() {
    std::string kernelVersion = getKernelVersion();
    std::string ram = getRAM();
    std::string gpu = getGPU();
    std::string diskUsage = getDiskUsage();
    std::string networkInfo = getNetworkInfo();

    std::cout << "Kernel: " << kernelVersion << std::endl;
    std::cout << "RAM: " << ram << std::endl;
    std::cout << "GPU: " << gpu << std::endl;
    std::cout << "Disk Usage: " << diskUsage << std::endl;
    std::cout << "Network Info: " << networkInfo << std::endl;

    #if defined(IS_WINDOWS)
        std::cout << "Windows detected" << std::endl;
        std::cout << "       ___" << std::endl;
        std::cout << "     /     \\" << std::endl;
        std::cout << "    /  ___  \\" << std::endl;
        std::cout << "   /  /   \\  \\" << std::endl;
        std::cout << "  /  /     \\  \\" << std::endl;
        std::cout << " /  /       \\  \\" << std::endl;
        std::cout << "/__/         \\__\\" << std::endl;
    #elif defined(IS_LINUX)
        std::cout << "Linux detected" << std::endl;
        std::cout << "                    -`" << std::endl;
        std::cout << "                   .o+" << std::endl;
        std::cout << "                  `ooo/" << std::endl;
        std::cout << "                 `+oooo:" << std::endl;
        std::cout << "                `+oooooo:" << std::endl;
        std::cout << "                -+oooooo+:" << std::endl;
        std::cout << "              `/:-:++oooo+:" << std::endl;
        std::cout << "             `/++++/+++++++:" << std::endl;
        std::cout << "            `/++++++++++++++:" << std::endl;
        std::cout << "           `/+++ooooooooooooo/`" << std::endl;
        std::cout << "          ./ooosssso++osssssso+`" << std::endl;
        std::cout << "         .oossssso-````/ossssss+`" << std::endl;
        std::cout << "        -osssssso.      :ssssssso." << std::endl;
        std::cout << "       :osssssss/        osssso+++." << std::endl;
        std::cout << "      /ossssssss/        +ssssooo/-" << std::endl;
        std::cout << "    `/ossssso+/:-        -:/+osssso+-" << std::endl;
        std::cout << "   `+sso+:-`                 `.-/+oso:" << std::endl;
        std::cout << "  `++:.                           `-/+/" << std::endl;
        std::cout << "  .`                                 `/" << std::endl;
    #elif defined(IS_MACOS)
        std::cout << "Mac OS detected" << std::endl;
        std::cout << "                .:'              " << std::endl;
        std::cout << "            __ :'__              " << std::endl;
        std::cout << "         .'`__`-'__``.           " << std::endl;
        std::cout << "        :__________.-'           " << std::endl;
        std::cout << "        :_________:              " << std::endl;
        std::cout << "         :_________`-;           " << std::endl;
        std::cout << "          `.__.-.__.'            " << std::endl;
    #else
        std::cout << "Unknown OS detected" << std::endl;
        std::cout << "   .--.                          " << std::endl;
        std::cout << "  |o_o |                         " << std::endl;
        std::cout << "  |:_/ |                         " << std::endl;
        std::cout << " //   \\ \\                        " << std::endl;
        std::cout << "(|     | )                       " << std::endl;
        std::cout << "/'\\_   _/`\\                      " << std::endl;
        std::cout << "\\___)=(___/                      " << std::endl;
    #endif

    return 0;
}
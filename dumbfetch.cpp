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
        std::cout << "\033[1;34mWindows detected\033[0m" << std::endl;
        std::cout << "\033[1;34m       ___\033[0m" << std::endl;
        std::cout << "\033[1;34m     /     \\\033[0m" << std::endl;
        std::cout << "\033[1;34m    /  ___  \\\033[0m" << std::endl;
        std::cout << "\033[1;34m   /  /   \\  \\\033[0m" << std::endl;
        std::cout << "\033[1;34m  /  /     \\  \\\033[0m" << std::endl;
        std::cout << "\033[1;34m /  /       \\  \\\033[0m" << std::endl;
        std::cout << "\033[1;34m/__/         \\__\\\033[0m" << std::endl;
    #elif defined(IS_LINUX)
        std::cout << "\033[1;32mLinux detected\033[0m" << std::endl;
        std::cout << "\033[1;32m                    -`\033[0m" << std::endl;
        std::cout << "\033[1;32m                   .o+\033[0m" << std::endl;
        std::cout << "\033[1;32m                  `ooo/\033[0m" << std::endl;
        std::cout << "\033[1;32m                 `+oooo:\033[0m" << std::endl;
        std::cout << "\033[1;32m                `+oooooo:\033[0m" << std::endl;
        std::cout << "\033[1;32m                -+oooooo+:\033[0m" << std::endl;
        std::cout << "\033[1;32m              `/:-:++oooo+:\033[0m" << std::endl;
        std::cout << "\033[1;32m             `/++++/+++++++:\033[0m" << std::endl;
        std::cout << "\033[1;32m            `/++++++++++++++:\033[0m" << std::endl;
        std::cout << "\033[1;32m           `/+++ooooooooooooo/`\033[0m" << std::endl;
        std::cout << "\033[1;32m          ./ooosssso++osssssso+`\033[0m" << std::endl;
        std::cout << "\033[1;32m         .oossssso-````/ossssss+`\033[0m" << std::endl;
        std::cout << "\033[1;32m        -osssssso.      :ssssssso.\033[0m" << std::endl;
        std::cout << "\033[1;32m       :osssssss/        osssso+++.\033[0m" << std::endl;
        std::cout << "\033[1;32m      /ossssssss/        +ssssooo/-\033[0m" << std::endl;
        std::cout << "\033[1;32m    `/ossssso+/:-        -:/+osssso+-\033[0m" << std::endl;
        std::cout << "\033[1;32m   `+sso+:-`                 `.-/+oso:\033[0m" << std::endl;
        std::cout << "\033[1;32m  `++:.                           `-/+/\033[0m" << std::endl;
        std::cout << "\033[1;32m  .`                                 `/\033[0m" << std::endl;
    #elif defined(IS_MACOS)
        std::cout << "\033[1;35mMac OS detected\033[0m" << std::endl;
        std::cout << "\033[1;35m                .:'              \033[0m" << std::endl;
        std::cout << "\033[1;35m            __ :'__              \033[0m" << std::endl;
        std::cout << "\033[1;35m         .'`__`-'__``.           \033[0m" << std::endl;
        std::cout << "\033[1;35m        :__________.-'           \033[0m" << std::endl;
        std::cout << "\033[1;35m        :_________:              \033[0m" << std::endl;
        std::cout << "\033[1;35m         :_________`-;           \033[0m" << std::endl;
        std::cout << "\033[1;35m          `.__.-.__.'            \033[0m" << std::endl;
    #else
        std::cout << "\033[1;31mUnknown OS detected\033[0m" << std::endl;
        std::cout << "\033[1;31m   .--.                          \033[0m" << std::endl;
        std::cout << "\033[1;31m  |o_o |                         \033[0m" << std::endl;
        std::cout << "\033[1;31m  |:_/ |                         \033[0m" << std::endl;
        std::cout << "\033[1;31m //   \\ \\                        \033[0m" << std::endl;
        std::cout << "\033[1;31m(|     | )                       \033[0m" << std::endl;
        std::cout << "\033[1;31m/'\\_   _/`\\                      \033[0m" << std::endl;
        std::cout << "\033[1;31m\\___)=(___/                      \033[0m" << std::endl;
    #endif

    return 0;
}
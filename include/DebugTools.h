#ifndef DEBUG_TOOLS_H
#define DEBUG_TOOLS_H

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

namespace Debug {

    // Log Date/Time
    inline std::string GetCurrentDateTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        std::tm now_tm = *std::localtime(&now_time);

        std::stringstream ss;
        ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    // Matrix Log
    inline void LogMatrix(const float* m) {
    std::cout << "-> [" << GetCurrentDateTime() << "] [DEBUG] [LogMatrix] "<< std::endl;
        for (int i = 0; i < 9; ++i) {
            std::cout << m[i] << " ";
            if ((i + 1) % 3 == 0) {
                std::cout << std::endl;
            }
        }
    }


}

#endif // DEBUG_TOOLS_H
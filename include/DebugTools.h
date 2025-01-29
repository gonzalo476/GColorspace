#ifndef DEBUG_TOOLS_H
#define DEBUG_TOOLS_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace Debug
{

  // Log Date/Time
  inline std::string GetCurrentDateTime()
  {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    std::tm now_tm = *std::localtime(&now_time);

    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
  }

  // Matrix Log
  inline void LogMatrix(const float* m)
  {
    std::cout << "\n";
    std::cout << "[" << GetCurrentDateTime()
              << "] [DEBUG] [LogMatrix]: " << std::endl;
    for(int i = 0; i < 9; ++i) {
      std::cout << m[i] << " ";
      if((i + 1) % 3 == 0) {
        std::cout << std::endl;
      }
    }
  }

  // Print Generic value
  template <typename T>
  inline void LogValue(const T& value)
  {
    std::cout << "\n";
    std::cout << "[" << GetCurrentDateTime()
              << "] [DEBUG] [LogValue]: " << value << std::endl;
  };

}  // namespace Debug

#endif  // DEBUG_TOOLS_H
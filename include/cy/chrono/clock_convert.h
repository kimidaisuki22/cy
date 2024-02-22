#pragma once
#include <chrono>
namespace cy::chrono {
template <typename Target_clock = std::chrono::system_clock, typename T> auto convert_to_clock(T time_point) {
  return std::chrono::clock_cast<Target_clock>(time_point);
}
} // namespace cy::chrono
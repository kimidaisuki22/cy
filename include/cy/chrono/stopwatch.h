#pragma once
#include <chrono>
namespace cy::chrono {
class Stopwatch {
  using Clock = std::chrono::steady_clock;

public:
  Stopwatch() : base{Clock::now()} {}
  template <typename Unit = std::chrono::seconds, typename Format = double>
  auto get_elapsed_time() const {
    auto elapsed = Clock::now() - base;
    using Target_unit = std::chrono::duration<Format, typename Unit::period>;
    return std::chrono::duration_cast<Target_unit>(elapsed).count();
  }

private:
  Clock::time_point base;
};
} // namespace cy::chrono

#pragma once
#include <chrono>
namespace cy::chrono {
template <typename Time, typename Clock = typename Time::clock>
concept has_to_utc_clock = requires(Time t) { Clock::to_utc(t); };
template <typename Time, typename Clock = typename Time::clock>
concept has_to_sys_clock = requires(Time t) { Clock::to_sys(t); };

template <has_to_utc_clock T>
inline std::chrono::system_clock::time_point to_system_time_point(T file_time) {
  std::chrono::system_clock::time_point system_time;
  using Clock = typename T::clock;
  static_assert(has_to_utc_clock<T>, "should has to_utc");
  auto utc = Clock::to_utc(file_time);
  system_time = decltype(utc)::clock::to_sys(utc);

  return system_time;
}

template <has_to_sys_clock T> inline auto to_system_time_point(T file_time) {
  using Clock = typename T::clock;
  static_assert(has_to_sys_clock<T>, "should has to_sys");
  return Clock::to_sys(file_time);
}
} // namespace cy::chrono
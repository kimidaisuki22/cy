#include <ctime>
#include <cy/chrono/convert.h>
#include <cy/text/time.h>
#include <string>

namespace {
std::string format_time_with_format_string(const char *fmt,
                                           size_t buffer_size) {
  auto time_stamp = time(nullptr);

  bool ok{};
  tm time_tm = cy::chrono::time_t_to_local_time(time_stamp, &ok);
  if (!ok) {
    return "local time r failed";
  }

  return cy::text::format_tm_with_format_string(time_tm, fmt, buffer_size);
}
} // namespace
std::string cy::text::local_date_str() {
  return format_time_with_format_string("%Y-%m-%d", 32);
}
std::string cy::text::local_hour_minute_seconds_str() {
  return format_time_with_format_string("%H:%M:%S", 12);
}
std::string cy::text::format_tm_with_format_string(struct tm tm,
                                                   const char *fmt,
                                                   size_t buffer_size) {
  std::string str_buffer;
  str_buffer.resize(buffer_size);

  auto size = std::strftime(str_buffer.data(), str_buffer.size(), fmt, &tm);
  if (!size) {
    return "strftime failed";
  }
  str_buffer.resize(size);
  return str_buffer;
}

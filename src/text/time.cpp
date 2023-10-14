#include <ctime>
#include <cy/text/time.h>
#include <string>
namespace {
std::string format_time_with_format_string(const char *fmt,
                                           size_t buffer_size) {
  auto time_stamp = time(nullptr);
  tm time_tm{};
  auto result = localtime_r(&time_stamp, &time_tm);
  if (!result) {
    return "local time r failed";
  }
  std::string str_buffer;
  str_buffer.resize(buffer_size);

  auto size =
      std::strftime(str_buffer.data(), str_buffer.size(), fmt, &time_tm);
  if (!size) {
    return "strftime failed";
  }
  str_buffer.resize(size);
  return str_buffer;
}
} // namespace
std::string cy::text::local_date_str() {
    return format_time_with_format_string("%Y-%m-%e", 32);
}
std::string cy::text::local_hour_minute_seconds_str() {
    return format_time_with_format_string("%H:%M:%S", 12);
}

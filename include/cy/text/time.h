#pragma once
#include <string>
#include <ctime>
namespace cy::text {
std::string local_date_str();
std::string local_hour_minute_seconds_str();
std::string format_tm_with_format_string(struct tm tm, const char *fmt,
                                         size_t output_buffer_size);
} // namespace cy::text
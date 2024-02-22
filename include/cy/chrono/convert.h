#pragma once

#include <ctime>
namespace cy::chrono {
tm time_t_to_local_time(time_t time, bool *ok_out = nullptr);
tm time_t_to_gmt_time(time_t time, bool *ok_out = nullptr);
} // namespace cy::chrono
#include <cy/chrono/convert.h>
#include <cy/tpl/safe_set.h>

namespace cy::chrono {

tm time_t_to_local_time(time_t time, bool *ok_out) {
  tm time_tm{};
  bool ok{};
#ifdef _MSVC_LANG
  ok = localtime_s(&time_tm, &time) == 0;
#else
  ok = localtime_r(&time, &time_tm) != nullptr;
#endif
  cy::tpl::safe_set(ok_out, ok);
  return time_tm;
}
tm time_t_to_gmt_time(time_t time, bool *ok_out) {
  tm time_tm{};
  bool ok{};
#ifdef _MSVC_LANG
  ok = localtime_s(&time_tm, &time) == 0;
#else
  ok = localtime_r(&time, &time_tm) != nullptr;
#endif
  cy::tpl::safe_set(ok_out, ok);
  return time_tm;
}
} // namespace cy::chrono
#include <cy/proc/executable.h>
#include <cy/proc/work_dir.h>

namespace cy::proc {
void change_work_dir_to_binary_location() {
  auto target = cy::proc::get_executable_path().parent_path();
  // auto from = std::filesystem::current_path();
  std::filesystem::current_path(target);
  // LOG_INFO("Change work dir from {} to {}", from.string(), target.string());
}
} // namespace cy::proc

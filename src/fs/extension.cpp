#include <cy/fs/extension.h>
std::filesystem::path cy::fs::change_extension(std::filesystem::path file_name,
                                               std::filesystem::path ext_name) {
  auto ext = std::filesystem::path(ext_name).extension();
  return file_name.replace_extension(ext_name);
}

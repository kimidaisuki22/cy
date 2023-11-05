#include <cy/io/easy/file_read_write.h>
#include <fstream>

std::optional<std::string>
cy::io::easy::read_file_to_buffer(std::filesystem::path filename) {
  std::ifstream file{filename, std::ios::binary};
  if (!file.is_open()) {
    return {};
  }
  return std::string{std::istreambuf_iterator{file}, {}};
}
bool cy::io::easy::write_buffer_to_file(std::span<char> buffer,
                                        std::filesystem::path filename) {
  std::ofstream file{filename, std::ios::binary};
  file.write(buffer.data(), buffer.size());
  return file.good();
}

#pragma once
#include <string>

namespace cy::experiment {

class Mmap_file {
public:
  Mmap_file(const std::string &file_name);
  ~Mmap_file();

  void *get_data() const;
  size_t get_size() const;

private:
#ifdef _WIN32
  using HANDLE = void *;
  HANDLE file_handle_;
  HANDLE map_handle_;
#elif __APPLE__ || __linux__
  int file_descriptor_;
#endif
  void *data_;
  size_t size_;
};
} // namespace cy::experiment

#include <cy/experiment/mmap.h>

#ifdef _WIN32
#include <windows.h>
#include <iostream>
#elif __APPLE__
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#elif __linux__
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace cy::experiment {
Mmap_file::Mmap_file(const std::string &file_name) : data_(nullptr), size_(0) {
#ifdef _WIN32
  file_handle_ = CreateFileA(file_name.c_str(), GENERIC_READ, FILE_SHARE_READ,
                             NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  if (file_handle_ == INVALID_HANDLE_VALUE) {
    std::cerr << "Error opening file: " << GetLastError() << std::endl;
    return;
  }

  DWORD file_size = GetFileSize(file_handle_, NULL);
  map_handle_ =
      CreateFileMappingA(file_handle_, NULL, PAGE_READONLY, 0, file_size, NULL);

  if (map_handle_ == NULL) {
    std::cerr << "Error creating file mapping: " << GetLastError() << std::endl;
    CloseHandle(file_handle_);
    return;
  }

  data_ = MapViewOfFile(map_handle_, FILE_MAP_READ, 0, 0, file_size);
  size_ = static_cast<size_t>(file_size);
#elif __APPLE__ || __linux__
  file_descriptor_ = open(file_name.c_str(), O_RDONLY);
  if (file_descriptor_ == -1) {
    std::perror("Error opening file");
    return;
  }

  struct stat file_info;
  if (fstat(file_descriptor_, &file_info) == -1) {
    std::perror("Error getting file size");
    close(file_descriptor_);
    return;
  }

  data_ =
      mmap(NULL, file_info.st_size, PROT_READ, MAP_SHARED, file_descriptor_, 0);
  if (data_ == MAP_FAILED) {
    std::perror("Error mapping file");
    close(file_descriptor_);
    return;
  }
  size_ = file_info.st_size;
#endif
}

Mmap_file::~Mmap_file() {
#ifdef _WIN32
  if (data_) {
    UnmapViewOfFile(data_);
  }
  if (map_handle_) {
    CloseHandle(map_handle_);
  }
  if (file_handle_ != INVALID_HANDLE_VALUE) {
    CloseHandle(file_handle_);
  }
#elif __APPLE__ || __linux__
  if (data_) {
    munmap(data_, size_);
  }
  if (file_descriptor_ != -1) {
    close(file_descriptor_);
  }
#endif
}

void *Mmap_file::get_data() const { return data_; }

size_t Mmap_file::get_size() const { return size_; }

} // namespace cy::experiment
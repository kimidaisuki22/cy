#include <cy/experiment/mmap.h>
#include <iostream>
int main() {
  // Replace "test.txt" with the path to your file
  using namespace cy::experiment;
  Mmap_file mmapped_file(__FILE__);

  void *data = mmapped_file.get_data();
  size_t size = mmapped_file.get_size();

  // Access the memory-mapped data as needed
  // e.g., print the content assuming it's a text file
  if (data && size > 0) {
    std::cout.write(static_cast<char *>(data), size);
    std::cout << std::endl;
  }

  return 0;
}
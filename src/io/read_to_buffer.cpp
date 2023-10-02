#include <cy/io/read_to_buffer.h>
#include <iterator>
#include <vector>
std::vector<char> cy::io::read_to_buffer(std::istream &input_stream) {
  std::istreambuf_iterator<char> begin{input_stream}, end;
  return std::vector<char>{begin, end};
}

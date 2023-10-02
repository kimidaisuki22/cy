#pragma once

#include <istream>
#include <vector>
namespace cy::io {
std::vector<char> read_to_buffer(std::istream &input_stream);
}
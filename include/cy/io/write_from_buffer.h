#pragma once

#include <ostream>
#include <span>
namespace cy::io {
bool write_from_buffer(std::span<const uint8_t> buffer,
                       std::ostream &out_stream);
bool write_from_buffer(std::span<const char> buffer, std::ostream &out_stream);
} // namespace cy::io
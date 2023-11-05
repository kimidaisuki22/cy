#pragma once
#include <optional>
#include <string_view>
namespace cy::text {
    struct Separator_cut_result{
        std::string_view front_;
        std::optional<std::string_view> back_;
    };
    Separator_cut_result separator_cut(std::string_view src,
                                       std::string_view separator);
}
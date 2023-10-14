#include <ctime>
#include <cy/text/time.h>
std::string cy::text::local_date_str() {
    auto time_stamp = time(nullptr);
    tm time_tm{};
    auto result = localtime_r(&time_stamp,&time_tm);
    if(!result){
        return "local time r failed";
    }
    std::string str_buffer;
    str_buffer.resize(32);

    auto size = std::strftime(str_buffer.data(),str_buffer.size(),"%Y-%m-%e",&time_tm);
    if(!size){
        return "strftime failed";
    }
    str_buffer.resize(size);
    return str_buffer;
}

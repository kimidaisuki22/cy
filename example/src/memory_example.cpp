#include<iostream>
#include <cy/proc.h>
int main(){
    std::cout << cy::proc::get_current_process_memory_usage() <<"\n";
}
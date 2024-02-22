#pragma once
namespace cy::tpl{
    template<typename T>
    // set ptr to value if ptr is not nullptr.
    void safe_set(T* ptr, T value){
        if(ptr){
            *ptr = value;
        }
    }
}
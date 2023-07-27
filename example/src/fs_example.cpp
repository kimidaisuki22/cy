#include <cy/fs.h>
#include <iostream>
int main(){
    std::cout << cy::fs::change_extension("example.txt", "cpp") << std::endl;
}
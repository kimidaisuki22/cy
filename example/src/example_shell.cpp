#include <cstdlib>
#include <cy/shell/shell.h>
#include <string>

int main(int argc, char **argv) {
  http://185.107.94.68/om/133803873/e81aa580ef7ae018d603c2ceb44637e7fe9e676c-4306938-2433-3319-jpg/x/0/suo7jwtreoebob15nm7/hathdl
  for(int i=0;i< 40;i++){
    auto str = std::string("http://185.107.94.68/om/133803873/e81aa580ef7ae018d603c2ceb44637e7fe9e676c-4306938-2433-3319-jpg/x/0/suo7jwtreoebob15nm" + std::to_string(i) + "/hathdl");
    system((std::string("curl -O ") + str).c_str());
  }
}
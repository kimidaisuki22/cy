#include "cy/shell/shell.h"
#include <cstdlib>
#include <string>
#include "inner-include/os.h"
#ifndef _WIN32
#ifdef __linux__
#define  OPEN_CMD "xdg-open"
#else
#define  OPEN_CMD "open"
#endif
#if CY_TARGET_IOS
#warning "open and show is not supported on iOS"
void cy::shell::open(const std::filesystem::path &path) {
}
void cy::shell::show(const std::filesystem::path &path) {
}
#else
void cy::shell::open(const std::filesystem::path &path) {
  std::string cmd;
  auto p = path;
  cmd = OPEN_CMD " \"" + p.make_preferred().string() + "\"";
  system(cmd.c_str());
}
void cy::shell::show(const std::filesystem::path &path) {
  std::string cmd;
  auto p = path;
  cmd = OPEN_CMD " \"" + p.make_preferred().parent_path().string() + "\"";
  system(cmd.c_str());
}
#endif

#else
#include <windows.h>
void cy::shell::open(const std::filesystem::path &path) {
  std::string cmd;
  auto p = path;
  cmd = "powershell -command start '" + p.make_preferred().string() + "'";

  ShellExecuteA(nullptr, "open", path.string().c_str(), nullptr, nullptr,
                SW_NORMAL);
}
void cy::shell::show(const std::filesystem::path &path) {
  std::string cmd;
  auto p = path;
  cmd = "explorer.exe /select,\"" + p.make_preferred().string() + "\"";
  system(cmd.c_str());
}

#endif

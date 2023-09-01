#include "cy/shell/shell.h"
#include <cstdlib>
#include <string>
#ifndef _WIN32
void cy::shell::open(const std::filesystem::path &path) {
  std::string cmd;
  auto p = path;
  cmd = "open \"" + p.make_preferred().string() + "\"";
  system(cmd.c_str());
}
void cy::shell::show(const std::filesystem::path &path) {
  std::string cmd;
  auto p = path;
  cmd = "open \"" + p.make_preferred().parent_path().string() + "\"";
  system(cmd.c_str());
}

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

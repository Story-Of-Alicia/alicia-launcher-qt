#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <cstdint>
#include <filesystem>
#include <functional>
#include <string>

#include <windows.h>

namespace launcher
{

struct Profile
{
  std::string_view username;
  std::string_view secret;

  unsigned level;
};

Profile authenticate(std::string_view username, std::string_view password);

bool check_files();

bool launch(Profile &profile);
}

#endif // LAUNCHER_HPP
#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <filesystem>
#include <vector>

namespace launcher
{

struct Profile
{
  std::string_view username;
  std::string_view character_name;
  std::string_view guild;

  uint64_t level;
  uint64_t last_login;
};

Profile authenticate(std::string_view const & username, std::string_view const & password);

// checks file sums
std::vector<std::string> fileCheck() noexcept;

// updates files
bool fileUpdate(std::vector<std::string> const &files);

bool launch(Profile const &profile);
}

#endif // LAUNCHER_HPP
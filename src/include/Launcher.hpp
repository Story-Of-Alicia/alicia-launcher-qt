#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <filesystem>
#include <vector>

#include <QPromise>

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

//TODO: docs
Profile authenticate(std::string_view const & username, std::string_view const & password);

//TODO: docs
std::vector<std::string> fileCheck() noexcept;

//TODO: docs
bool fileUpdate(std::vector<std::string> const &files, const std::function<void(int)>&);

//TODO: docs
bool launch(Profile const &profile);
}

#endif // LAUNCHER_HPP
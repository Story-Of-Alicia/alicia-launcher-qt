#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <filesystem>
#include <vector>

namespace launcher
{

struct Profile
{

};

Profile authenticate(std::string_view const & username, std::string_view const & password);

// checks file sums
std::vector<std::string> fileCheck();

// updates files
bool fileUpdate(std::vector<std::string> const &files);

bool launch(Profile const &profile);
}

#endif // LAUNCHER_HPP
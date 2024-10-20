#include "launcher.hpp"

#include <format>
#include <thread>

namespace launcher {

Profile authenticate(std::string_view username, std::string_view password)
{
  throw std::exception();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return Profile {};
}

bool launch(Profile &profile)
{

}
}

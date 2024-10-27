#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <filesystem>
#include <queue>

#include <QPromise>

namespace launcher
{

enum class State
{
  PAUSE, RESUME, STOP
};

struct Profile
{
  std::string_view username;
  std::string_view character_name;
  std::string_view guild;

  uint64_t level;
  uint64_t last_login;
};


class Launcher
{
public:
  Launcher();

  [[nodiscard]] State state() const;
  [[nodiscard]] Profile profile() const;
  [[nodiscard]] int toPatch() const;
  [[nodiscard]] bool authenticated() const;

  void setState(State const & ctrl);
  void registerProgressCallback(std::function<void(int)> const * callback);

  bool authenticate(std::string const & username, std::string const & password);
  void logout();

  bool checkFiles();
  bool updateNextFile();
private:
  State _state;
  bool _authenticated;
  Profile _profile;

  std::queue<std::string> _toPatch;
  std::function<void(int)> const * _progressCallback = nullptr;
};
}

#endif // LAUNCHER_HPP
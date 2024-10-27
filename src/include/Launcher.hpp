#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <condition_variable>
#include <filesystem>
#include <queue>

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

class Launcher
{
public:
  Launcher();

  [[nodiscard]] Profile profile() const;
  [[nodiscard]] int toPatch() const;
  [[nodiscard]] bool authenticated() const;
  [[nodiscard]] bool updatePaused() const;

  /*
   * Sets _updatePaused to v.
   * This will stop or resume any workers (file check, file update).
   */
  void setUpdatePaused(bool v);

  /*
   * Sets _shouldStop to true
   * This will stop any workers (file check, file update).
   */
  void stopUpdate();

  /*
   * Authenticates specified user credentials.
   * Returns true on success, false otherwise
   */
  bool authenticate(std::string const & username, std::string const & password) noexcept;

  /*
   * Logs out user.
   */
  void logout() noexcept;

  /*
   * Makes sure game files have correct checksums.
   * Populates _toPatch queue.
   * Can be interrupted with stopUpdate().
   * In this case the function returns false.
   * Returns true on success, false if an error occurred.
   */
  bool checkFiles() noexcept;

  /*
   * Iterates _toPatch and updates a single file.
   * Can be interrupted with stopUpdate().
   * In this case the function returns false.
   * Returns true on success, false if an error occurred.
   */
  bool updateNextFile() noexcept;
private:
  std::mutex _mutex;

  // requires _mutex lock
  Profile _profile;
  // requires _mutex lock
  std::queue<std::string> _toPatch;

  std::atomic_bool _authenticated = false;
  std::atomic_bool _shouldStop    = false;
  std::atomic_bool _paused        = false;
};
}

#endif // LAUNCHER_HPP
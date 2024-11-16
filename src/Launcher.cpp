#include "Launcher.hpp"

#include <format>
#include <fstream>
#include <map>
#include <openssl/evp.h>
#include <thread>
#include <vector>
#include <sstream>

#include <QString>

namespace launcher
{

std::map<std::string, std::string> obtainFileInfo()
{
  return {
    {"file1", "ecdc5536f73bdae8816f0ea40726ef5e9b810d914493075903bb90623d97b1d8"},
    {"file2", "67ee5478eaadb034ba59944eb977797b49ca6aa8d3574587f36ebcbeeb65f70e"},
    {"file3", "94f6e58bd04a4513b8301e75f40527cf7610c66d1960b26f6ac2e743e108bdac"},
  };
}

std::string sha256_checksum(const std::string& path)
{
  // https://docs.openssl.org/master/man3/EVP_DigestInit#examples
  std::ifstream input(path, std::ios_base::binary);

  if (!input.is_open())
    throw std::logic_error("failed to open file");

  EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
  if (!mdctx)
    throw std::logic_error("message digest creation failed");

  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned md_len;

  const EVP_MD* md = EVP_sha256();
  EVP_DigestInit_ex2(mdctx, md, nullptr);

  do
  {
    unsigned char buffer[1024];
    input.read(reinterpret_cast<char*>(buffer), sizeof(buffer));
    if (input.bad())
    {
      input.close();
      throw std::logic_error("failed to read file");
    }
    if (EVP_DigestUpdate(mdctx, buffer, input.gcount()))
    {
      input.close();
      throw std::logic_error("failed to update digest");
    }

  } while (!input.eof());

  input.close();

  EVP_DigestFinal_ex(mdctx, md_value, &md_len);
  EVP_MD_CTX_free(mdctx);

  std::ostringstream ss{};

  for (int i = 0; i < md_len; i++)
  {
    char buffer[3] = {};
    snprintf(buffer, sizeof(buffer), "%02x", md_value[i]);
    ss << buffer;
  }

  return ss.str();
}

Launcher::Launcher()
    : _state(State::NONE)
{
  _profile = Profile{
    .username = "%USERNAME%",
    .character_name = "%CHARACTER%",
    .guild = "%GUILD%",
    .level = 69,
    .last_login = 0,
  };
}

State Launcher::state() const
{
  return _state;
}

int Launcher::progress() const
{
  return _progress;
}
int Launcher::progressTotal() const
{
  return _progressTotal;
}

bool Launcher::authenticate(std::string const& username, std::string const& password) noexcept
{
  std::lock_guard lock(_mutex);
  if(username == "test")
  {
    return _isAuthenticated = false;
  }

  return _isAuthenticated = true;
}

void Launcher::logout() noexcept { _isAuthenticated = false; }

Profile Launcher::profile() const { return _profile; }

int Launcher::countToDownload() const { return static_cast<int>(_toDownload.size()); }

int Launcher::countToPatch() const { return static_cast<int>(_toPatch.size()); }

bool Launcher::isAuthenticated() const { return _isAuthenticated; }

bool Launcher::isUpdateStopped() const { return _shouldStop; }

void Launcher::stopUpdate() { _shouldStop = true; }

bool Launcher::isUpdatePaused() const { return _shouldPause; }

void Launcher::setUpdatePaused(bool const v)
{
  _shouldPause = v;
  _shouldPause.notify_all();
}

bool Launcher::checkFiles() noexcept
{
  std::lock_guard lock(_mutex);

  std::queue<std::string> toDownload;
  _toDownload.swap(toDownload);

  std::queue<std::string> toPatch;
  _toPatch.swap(toPatch);

  if (!_toDownload.empty())
  {
    std::queue<std::string> empty;
    std::swap(_toDownload, empty);
  }

  for (const auto& [path, expected_sum] : obtainFileInfo())
  {
    try
    {
      if (auto sum = sha256_checksum(path); sum != expected_sum)
      {
        _toDownload.push(path);
      }
    }
    catch (std::logic_error const& e)
    {
      _toDownload.push(path);
    }
  }
  return _toDownload.empty();
}

void Launcher::update() noexcept
{
  std::lock_guard lock(_mutex);
  if(_toDownload.empty())
    return;

  _shouldPause = false;
  _shouldStop = false;

  _progress = 0;
  _progressTotal = 0;

  int counter = 0;
  size_t total = _toDownload.size() * 2;

  do
  {
    if (_shouldStop)
    {
      _state = State::NONE;
      return;
    }
    _state = State::DOWNLOADING;

    _shouldPause.wait(true);
    auto file = _toDownload.front();
    // heavy task simulation
    for (int i = 0; i < 5; i++)
    {
      if (_shouldStop)
      {
        _state = State::NONE;
        return;
      }
      _shouldPause.wait(true);

      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      _progress = static_cast<int>((static_cast<float>(i+1) / 5.0f) * 100);
    }

    _toDownload.pop();
    _toPatch.push(file);
    counter++;

    _progressTotal = static_cast<int>((static_cast<float>(counter) / static_cast<float>(total) ) * 100);
  } while(!_toDownload.empty());


  if(_toPatch.empty())
  {
    _state = State::NONE;
    return;
  }

  do
  {
    if (_shouldStop)
    {
      _state = State::NONE;
      return;
    }

    _state = State::PATCHING;

    _shouldPause.wait(true);
    auto file = _toPatch.front();
    // heavy task simulation
    for (int i = 0; i < 5; i++)
    {
      if (_shouldStop)
      {
        _state = State::NONE;
        return;
      }

      _shouldPause.wait(true);

      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      _progress = static_cast<int>((static_cast<float>(i+1) / 5.0f) * 100);
    }

    _toPatch.pop();
    counter++;

    _progressTotal = static_cast<int>((static_cast<float>(counter) / static_cast<float>(total) ) * 100);
  } while(!_toPatch.empty());

  _state = State::NONE;
}

} // namespace launcher

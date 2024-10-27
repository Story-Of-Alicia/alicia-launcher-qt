#include "Launcher.hpp"

#include <format>
#include <fstream>
#include <map>
#include <openssl/evp.h>
#include <thread>
#include <vector>

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
    : _state()
    , _authenticated(false)
{
  _profile = Profile{
    .username = "%USERNAME%",
    .character_name = "%CHARACTER%",
    .guild = "%GUILD%",
    .level = 69,
    .last_login = 0,
  };
}

bool Launcher::authenticate(std::string const& username, std::string const& password)
{
  _authenticated = true;
  return true;
}

void Launcher::logout()
{
  _authenticated = false;
}

Profile Launcher::profile() const
{
  return _profile;
}

State Launcher::state() const {
  return _state;
}

[[nodiscard]] int Launcher::toPatch() const
{
  return static_cast<int>(_toPatch.size());
}

[[nodiscard]] bool Launcher::authenticated() const
{
  return _authenticated;
}

void Launcher::setState(State const& ctrl)
{
  _state = ctrl;
}

void Launcher::registerProgressCallback(std::function<void(int)> const * callback)
{
  _progressCallback = callback;
}

bool Launcher::checkFiles()
{
  if(!_toPatch.empty())
  {
    std::queue<std::string> empty;
    std::swap(_toPatch, empty);
  }

  for (const auto& [path, expected_sum] : obtainFileInfo())
  {
    try
    {
      if (auto sum = sha256_checksum(path); sum != expected_sum)
      {
        _toPatch.push(path);
      }
    }
    catch (std::logic_error const& e)
    {
      _toPatch.push(path);
    }
  }
  return _toPatch.empty();
}

bool Launcher::updateNextFile()
{
  if(_toPatch.empty())
    return false;

  _toPatch.pop();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return _toPatch.empty();
}

} // namespace launcher

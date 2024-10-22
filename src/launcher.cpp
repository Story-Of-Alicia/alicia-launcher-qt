#include "launcher.hpp"

#include <map>
#include <format>
#include <thread>
#include <openssl/evp.h>
#include <fstream>

namespace launcher {
struct file_info
{
  std::map<std::string, std::string> files;
};

std::string sha256_checksum(const std::string& path)
{
  // https://docs.openssl.org/master/man3/EVP_DigestInit#examples
  std::ifstream input(path, std::ios_base::binary);

  if(!input.is_open())
    throw std::logic_error("failed to open file");

  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  if (!mdctx)
    throw std::logic_error("message digest creation failed");

  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned md_len;

  const EVP_MD *md = EVP_sha256();
  EVP_DigestInit_ex2(mdctx, md, nullptr);

  do
  {
    unsigned char buffer[1024];
    input.read(reinterpret_cast<char*>(buffer), sizeof(buffer));
    if(input.bad())
    {
      input.close();
      throw std::logic_error("failed to read file");
    }
    if (EVP_DigestUpdate(mdctx, buffer, input.gcount()))
    {
      input.close();
      throw std::logic_error("failed to update digest");
    }

  } while(!input.eof());

  input.close();

  EVP_DigestFinal_ex(mdctx, md_value, &md_len);
  EVP_MD_CTX_free(mdctx);

  std::ostringstream ss {};

  for(int i = 0; i < md_len; i++)
  {
    char buffer[3] = {};
    snprintf(buffer,sizeof(buffer),"%02x", md_value[i]);
    ss << buffer;
  }

  return ss.str();
}

Profile authenticate(std::string_view username, std::string_view password)
{
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return Profile {};
}

//todo maybe Qt progress stuff here
bool check_files()
{
  return false;
}

bool launch(Profile &profile)
{
  return false;
}

}

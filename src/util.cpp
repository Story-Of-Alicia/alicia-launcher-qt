#include "util.hpp"

#include <vector>
#include <windows.h>
#include <commdlg.h>
#include <cstdint>

namespace util
{
  std::wstring win32_widen(const std::string_view& narrow_str)
  {
    if (narrow_str.empty())
      return L"";

    std::wstring wide_str;
    wide_str.resize(narrow_str.size());
    MultiByteToWideChar(
        CP_UTF8,
        0,
        narrow_str.data(),
        static_cast<int32_t>(narrow_str.size()),
        wide_str.data(),
        static_cast<int32_t>(wide_str.size()));
    return wide_str;
  }

  std::string win32_narrow(const std::wstring_view& wide_str)
  {
    if (wide_str.empty())
      return "";

    // Determine the required size of the narrow UTF8 string.
    const auto size = WideCharToMultiByte(
        CP_UTF8,
        0,
        wide_str.data(),
        static_cast<int32_t>(wide_str.size()),
        nullptr,
        0,
        nullptr,
        nullptr);

    // Convert the unicode string to UTF8 string.
    std::string narrow_str;
    narrow_str.resize(size);
    WideCharToMultiByte(
        CP_UTF8,
        0,
        wide_str.data(),
        static_cast<int32_t>(wide_str.size()),
        narrow_str.data(),
        size,
        nullptr,
        nullptr);

    return narrow_str;
  }

  std::string win32_narrow(const std::u16string_view& wide_str)
  {
    if (wide_str.empty())
      return "";

    // Determine the required size of the narrow UTF8 string.
    const auto size = WideCharToMultiByte(
        CP_UTF8,
        0,
        reinterpret_cast<const wchar_t*>(wide_str.data()),
        static_cast<int32_t>(wide_str.size()),
        nullptr,
        0,
        nullptr,
        nullptr);

    // Convert the unicode string to UTF8 string.
    std::string narrow_str;
    narrow_str.resize(size);
    WideCharToMultiByte(
        CP_UTF8,
        0,
        reinterpret_cast<const wchar_t*>(wide_str.data()),
        static_cast<int32_t>(wide_str.size()),
        narrow_str.data(),
        size,
        nullptr,
        nullptr);

    return narrow_str;
  }
} // namespace util
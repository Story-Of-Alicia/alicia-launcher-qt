#ifndef LAUNCHER_UTIL_HPP
#define LAUNCHER_UTIL_HPP

#include <string>

namespace util
{

  //! Widens a narrow UTF8 string.
  //!
  //! @param narrow_str UTF8 string.
  //! @returns Wide unicode string.
  std::wstring win32_widen(const std::string_view& narrow_str);

  //! Narrows a UTF16 Unicode string.
  //!
  //! @param wide_str UTF16 string.
  //! @returns Narrow UTF8 string.
  std::string win32_narrow(const std::wstring_view& wide_str);

  //! Narrows a UTF16 Unicode string.
  //!
  //! @param wide_str UTF16 string.
  //! @returns Narrow UTF8 string.
  std::string win32_narrow(const std::u16string_view& wide_str);
} // namespace util

#endif // LAUNCHER_UTIL_HPP
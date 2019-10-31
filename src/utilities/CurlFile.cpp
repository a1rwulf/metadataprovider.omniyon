/*
 *      Copyright (C) 2005-2019 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "CurlFile.h"

#include <omniplayer/AddonBase.h>
#include <omniplayer/Filesystem.h>

#include <cstdarg>

using namespace omniyon::utilities;

bool CurlFile::Get(const std::string& strURL, std::string& strResult)
{
  kodi::vfs::CFile myFile;
  bool ret = myFile.CURLCreate(strURL.c_str());
  ret = myFile.CURLOpen(0);
  if (ret)
  {
    char buffer[1024];
    while (true)
    {
      memset(buffer, 0, sizeof(buffer));
      if (myFile.Read(buffer, 1024) > 0)
        strResult.append(buffer);
      else
        break;
    }

    return true;
  }
  return false;
}

//! @todo - a1rwulf Implement when needed
/*
bool CurlFile::Post(const std::string& strURL, std::string& strResult)
{
  void* fileHandle = curl_create(strURL.c_str());

  if (!fileHandle)
  {
    kodi::Log(ADDON_LOG_ERROR, "%s Unable to create curl handle for %s", __FUNCTION__, strURL.c_str());
    return false;
  }

  XBMC->CURLAddOption(fileHandle, XFILE::CURL_OPTION_PROTOCOL, "postdata", "POST");

  if (!XBMC->CURLOpen(fileHandle, XFILE::READ_NO_CACHE))
  {
    kodi::Log(ADDON_LOG_ERROR, "%s Unable to open url: %s", __FUNCTION__, strURL.c_str());
    XBMC->CloseFile(fileHandle);
    return false;
  }

  char buffer[1024];
  while (XBMC->ReadFileString(fileHandle, buffer, 1024))
    strResult.append(buffer);
  XBMC->CloseFile(fileHandle);

  if (!strResult.empty())
    return true;

  return false;
}

bool CurlFile::Check(const std::string& strURL)
{
  void* fileHandle = XBMC->CURLCreate(strURL.c_str());

  if (!fileHandle)
  {
    kodi::Log(ADDON_LOG_ERROR, "%s Unable to create curl handle for %s", __FUNCTION__, strURL.c_str());
    return false;
  }

  XBMC->CURLAddOption(fileHandle, XFILE::CURL_OPTION_PROTOCOL, "connection-timeout",
                      std::to_string(Settings::GetInstance().GetConnectioncCheckTimeoutSecs()).c_str());

  if (!XBMC->CURLOpen(fileHandle, XFILE::READ_NO_CACHE))
  {
    kodi::Log(ADDON_LOG_DEBUG, "%s Unable to open url: %s", __FUNCTION__, strURL.c_str());
    XBMC->CloseFile(fileHandle);
    return false;
  }

  XBMC->CloseFile(fileHandle);

  return true;
}
*/

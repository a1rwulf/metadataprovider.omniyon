/*
 *  Copyright (C) 2019 Wolfgang Haupt
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "client.h"
#include "utilities/CurlFile.h"
#include "utilities/StringUtils.h"

#include "rapidjson/document.h"
#include <omniplayer/addon-instance/MetadataProvider.h>

#include <memory>
#include <vector>

using namespace kodi;
using namespace addon;

class ATTRIBUTE_HIDDEN CMetadataProviderOmniyon : public kodi::addon::CAddonBase,
                                                  public kodi::addon::CInstanceMetadataProvider
{
public:
  CMetadataProviderOmniyon();

  virtual bool GetPlaylists(const std::string& strBaseDir,
                            std::vector<vfs::CDirEntry>& items,
                            const AddonSortDescription& sortDescription,
                            bool countOnly) override;

  virtual bool GetSongs(const std::string& strBaseDir,
                        std::vector<vfs::CDirEntry>& items,
                        int idGenre,
                        int idArtist,
                        int idAlbum,
                        int idPlaylist,
                        const AddonSortDescription& sortDescription) override;

private:
  std::string GetRequestUrl(const std::string& url) const;

  std::string m_baseUrl;
};

CMetadataProviderOmniyon::CMetadataProviderOmniyon()
{
  m_baseUrl = kodi::GetSettingString("baseurl");
}

bool CMetadataProviderOmniyon::GetPlaylists(const std::string& strBaseDir,
                                            std::vector<vfs::CDirEntry>& items,
                                            const AddonSortDescription& sortDescription,
                                            bool countOnly)
{
  kodi::Log(ADDON_LOG_NOTICE, "CApiMetadataProvider::%s start", __FUNCTION__);
  try
  {
    int total = 0;
    std::string requestUrl = GetRequestUrl(strBaseDir);

    omniyon::utilities::CurlFile webrequest;
    std::string response;
    webrequest.Get(m_baseUrl + requestUrl, response);

    rapidjson::Document doc;
    doc.Parse(response.c_str());

    if (response.empty())
      return false;

    for (auto& playlist : doc["data"]["items"].GetArray())
    {
      kodi::Log(ADDON_LOG_NOTICE, "CApiMetadataProvider::%s - %s", __FUNCTION__, playlist["label"].GetString());
      std::unique_ptr<kodi::vfs::CDirEntry> item(new kodi::vfs::CDirEntry());

      std::string uuid;
      long id = 0;

      if (playlist["id"].IsString())
        uuid = playlist["id"].GetString();
      else if (playlist["id"].IsInt())
        id = playlist["id"].GetInt();

      item->SetFolder(true);
      item->SetLabel(playlist["label"].GetString());
      item->SetPath("oam://playlists/" + !uuid.empty() ? uuid : std::to_string(id) + "/");

      //items.emplace_back(*item.get());
      total++;

      // item->m_dwSize = doc["data"]["items"].GetArray().Size();
      // std::string iconPath = playlist["thumbnail"].IsString() ? playlist["thumbnail"].GetString()
      //                                                         : "DefaultMusicPlaylists.png";

      // item->SetArt("thumb", iconPath);
      // item->SetIconImage(iconPath);

      // item->SetProvider(playlist["provider"].GetString());
      // //item->SetProperty("provider", playlist["provider"].GetString());
    }

    return true;
  }
  catch (std::exception& e)
  {
    kodi::Log(ADDON_LOG_ERROR, "%s exception - %s", __FUNCTION__, e.what());
  }
  catch (...)
  {
    kodi::Log(ADDON_LOG_ERROR, "%s failed", __FUNCTION__);
  }

  return false;
}

bool CMetadataProviderOmniyon::GetSongs(const std::string& strBaseDir,
                                        std::vector<vfs::CDirEntry>& items,
                                        int idGenre,
                                        int idArtist,
                                        int idAlbum,
                                        int idPlaylist,
                                        const AddonSortDescription& sortDescription)
{
  return true;
}

std::string CMetadataProviderOmniyon::GetRequestUrl(const std::string& url) const
{
  if (StringUtils::StartsWith(url, "oam") || StringUtils::StartsWith(url, "musicdb"))
  {
    if (url.find_first_of("playlist") != std::string::npos)
    {
      if (!StringUtils::EndsWith(url, "playlists/"))
      {
        std::string uri = "/view/1/playlist?id=" /*+ url.GetFileNameWithoutPath()*/;
        //URIUtils::RemoveSlashAtEnd(uri);
        return uri;
      }
      else
      {
        std::string uri = "/view/1/playlists";
        //URIUtils::RemoveSlashAtEnd(uri);
        return uri;
      }
    }
    else if (url.find_first_of("song") != std::string::npos)
    {
      if (!StringUtils::EndsWith(url, "songs/"))
      {
        std::string uri = "/api/v2/music/track/" /*+ url.GetFileNameWithoutPath()*/;
        //URIUtils::RemoveSlashAtEnd(uri);
        return uri;
      }
      else
      {
        std::string uri = "/api/v2/music/track";
        //URIUtils::RemoveSlashAtEnd(uri);
        return uri;
      }
    }
  }

  return "/error";
}

ADDONCREATOR(CMetadataProviderOmniyon) // Don't touch this!

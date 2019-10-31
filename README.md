# Omniyon metadata provider
Addon to supply OmniPlayer with metadata information about
music from [Omniyon] and other streaming services

## Build instructions

### Linux

1. `git clone https://git.yachtcloud.eu/yachtcloud/kodi`
2. `git clone https://git.yachtcloud.eu/yachtcloud/metadataprovider.omniyon`
3. `cd metadataprovider.omniyon && mkdir build && cd build`
4. `cmake -DADDONS_TO_BUILD=metadataprovider.omniyon -DADDON_SRC_PREFIX=../.. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../xbmc/addons -DPACKAGE_ZIP=1 ../../cmake/addons`
5. `make`
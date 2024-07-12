#ifndef PLATFORMDATA_H
#define PLATFORMDATA_H

#include "version.h"

#define AP_NAME_START "dtuGateway"

#ifndef baseDataStruct
struct baseDataStruct
{
  #if defined(ESP8266)
  uint64_t chipID = ESP.getChipId();
  #elif defined(ESP32)
  uint64_t chipID = ESP.getEfuseMac();
  #endif
  String espUniqueName = String(AP_NAME_START) + "_" + chipID;

  const char *fwVersion = VERSION;
  const char *fwBuildDate = BUILDTIME;
  
  int wifiNetworkCount = 0;
  String wifiFoundNetworks = "[{\"name\":\"empty\",\"wifi\":0,\"chan\":0}]";
  IPAddress dtuGatewayIP  = IPAddress(192, 168, 0, 1);

  unsigned long dtuGWstarttime = 0;
  unsigned long currentNTPtime = 0;
  String currentNTPtimeFormatted = "not set";

  unsigned long dtuNextUpdateCounterSeconds = 1704063600;
};
#endif

extern baseDataStruct platformData;

#define UPDATE_STATE_IDLE 0
#define UPDATE_STATE_START 1
#define UPDATE_STATE_INSTALLING 2
#define UPDATE_STATE_DONE 3
#define UPDATE_STATE_RESTART 4
#define UPDATE_STATE_FAILED 5


#ifndef baseUpdateInfoStruct
struct baseUpdateInfoStruct
{
    char updateInfoWebPath[128] = "https://github.com/ohAnd/dtuGateway/releases/download/snapshot/version.json";
    char updateInfoWebPathRelease[128] = "https://github.com/ohAnd/dtuGateway/releases/latest/download/version.json";

    char versionServer[32] = "checking";
    char versiondateServer[32] = "...";
    char updateURL[196] = ""; // will be read by getting -> updateInfoWebPath
    char versionServerRelease[32] = "checking";
    char versiondateServerRelease[32] = "...";
    char updateURLRelease[196] = ""; // will be read by getting -> updateInfoWebPath
    boolean updateAvailable = false;
    boolean updateInfoRequested = false;
    char updateStateText[16] = "waiting";

    boolean updateRunning = false;
    float updateProgress = 0;
    uint8_t updateState = UPDATE_STATE_IDLE;
};
#endif

extern baseUpdateInfoStruct updateInfo;

#endif // PLATFORMDATA_H
#ifndef ETH_MANAGER_H
#define ETH_MANAGER_H

#include <ETH.h>
#include <IPAddress.h>

class EthManager
{
public:
    EthManager(byte macAddress[], IPAddress localIp, IPAddress gateway, IPAddress subnet);

    void initialize();
    bool isConnected();

private:
    byte *mac;
    IPAddress ip;
    IPAddress gateway;
    IPAddress subnet;
};

#endif // ETHERNET_MANAGER_H

#include <ETH.h>
#include <IPAddress.h>

class EthernetManager
{
public:
    EthernetManager(byte macAddress[], IPAddress localIp, IPAddress gateway, IPAddress subnet)
        : mac(macAddress), ip(localIp), gateway(gateway), subnet(subnet) {}

    void initialize()
    {
        Serial.println("Connecting to Ethernet...");
        ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
        ETH.macAddress(mac);
        ETH.config(ip, gateway, subnet);

        // Wait for Ethernet connection
        while (!ETH.linkUp())
        {
            delay(100);
            Serial.println("Waiting for Ethernet connection...");
        }

        Serial.print("Connected! IP address: ");
        Serial.println(ETH.localIP());
    }

    bool isConnected()
    {
        return ETH.linkUp();
    }

private:
    byte *mac;
    IPAddress ip;
    IPAddress gateway;
    IPAddress subnet;
};

#include "EthManager.h"

EthManager::EthManager(byte macAddress[], IPAddress localIp, IPAddress gateway, IPAddress subnet)
    : mac(macAddress), ip(localIp), gateway(gateway), subnet(subnet) {}

void EthManager::initialize()
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

bool EthManager::isConnected()
{
    return ETH.linkUp();
}

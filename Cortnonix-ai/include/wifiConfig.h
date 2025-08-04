#ifndef WIFICONFIG_H

class SetupWifi {
public:
    SetupWifi();

    bool connectToWifi(const char* ssid, const char* password);
};



#endif
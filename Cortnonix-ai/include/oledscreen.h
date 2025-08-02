#ifndef OLEDSCREEN_H
#define OLEDSCREEN_H

class OledScreen {
public:
    OledScreen();

    void readLightIntensity();
    bool isItDark();

private:
    int LIGHT_INTENSITY;
};

#endif
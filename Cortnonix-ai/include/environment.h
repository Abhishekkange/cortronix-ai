#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment {
public:
    Environment();

    void readLightIntensity();
    bool isItDark();

private:
    int LIGHT_INTENSITY;
};

#endif
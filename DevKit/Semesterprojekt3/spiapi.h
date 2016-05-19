#ifndef SPIAPI_H
#define SPIAPI_H

#include <cstdio> //Used by sprint
#include <fcntl.h> //Used by fp
#include <unistd.h> //Used by fp

#define MAXLEN 5

class SPIapi
{
public:
    SPIapi();

    int setPacket(unsigned char* cmd, unsigned char* value) const;
    int getPacket(unsigned char* cmd, unsigned int* value);

private:
    int sendPacket(unsigned char* cmd, unsigned char* data) const;
    int receivePacket(unsigned char* cmd, unsigned int* data);
};

#endif // SPIAPI_H

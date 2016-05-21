#include "spiapi.h"

SPIapi::SPIapi()
{

}

int SPIapi::setPacket(unsigned char* cmd, unsigned char* value) const
{
    int err;

    err = sendPacket(cmd, value);
    if(err < 0) {return -*cmd;}

    return 0;
}

int SPIapi::getPacket(unsigned char* cmd, unsigned int* value)
{
    int err;

    err = receivePacket(cmd, value);
    if(err < 0) {return -*cmd;}

    return 0;
}

int SPIapi::sendPacket(unsigned char* cmd, unsigned char* data) const
{
    int err, fp, txLen;
    unsigned int txPacket;
    char txBuffer[MAXLEN];

    txPacket = (*cmd << 8) | (*data & 0x00ff);
    txLen = sprintf(txBuffer, "%d", txPacket);

    fp = open("/dev/spi_dev", O_RDWR);
    if (fp < 0)
    {
        printf("FP_OPEN ERROR: %d\n", -*cmd);
        close(fp);
        return -*cmd;
    }

    err = write(fp, &txBuffer, txLen);
    if (err <0)
    {
        printf("FP_WRITE ERROR: %d\n", -*cmd);
        close(fp);
        return -*cmd;
    }

    close(fp);

    return 0;
}

int SPIapi::receivePacket(unsigned char* cmd, unsigned int* data)
{
    int err, fp, txLen;
    unsigned int txPacket = 0;
    char txBuffer[MAXLEN];
    char rxBuffer[MAXLEN];
    unsigned int rxValue;

    txPacket = ((*cmd) << 8);
    txLen = sprintf(txBuffer, "%i", txPacket);

    fp = open("/dev/spi_dev", O_RDWR);
    if (fp < 0)
    {
        printf("FP_OPEN ERROR: %d\n", -*cmd);
        close(fp);
        return -*cmd;
    }

    err = write(fp, &txBuffer, txLen);
    if (err < 0)
    {
        printf("FP_WRITE ERROR: %d\n", -*cmd);
        close(fp);
        return -*cmd;
    }

    err = read(fp, &rxBuffer, MAXLEN);
    if(err < 0){
        printf("READ ERROR: %d\n", -*cmd);
        close(fp);
        return -*cmd;
    }

    sscanf(rxBuffer,"%i", &rxValue);

    *data = rxValue;

    close(fp);

    return 0;
}

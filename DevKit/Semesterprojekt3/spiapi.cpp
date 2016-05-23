/*!
 * @file        spiapi.cpp
 * @brief       Handles spi communication
 * @author      Victor Busk (201409557@post.au.dk)
 */

#include "spiapi.h"

/*!
 *  @brief      Initializes spiapi constructor
 *  @author     Victor Busk (201409557@post.au.dk)
 */

SPIapi::SPIapi()
{}

/*!
 *  @brief      Return the negative of the command if sending error occurs
 *  @param[in]  cmd   Command to be handled.
 *  @param[in]  val   Value to pass along with the command.
 *  @author     Victor Busk (201409557@post.au.dk)
 */

int SPIapi::setPacket(const unsigned char* cmd, unsigned char* value) const
{
    int err;

    err = sendPacket(cmd, value);
    if(err < 0) {return -*cmd;}

    return 0;
}

/*!
 *  @brief      Return the negative of the command if receiving error occurs
 *  @param[in]  cmd   Command to be handled.
 *  @param[in]  val   Value to pass along with the command.
 *  @author     Victor Busk (201409557@post.au.dk)
 */

int SPIapi::getPacket(unsigned char* cmd, unsigned int* value)
{
    int err;

    err = receivePacket(cmd, value);
    if(err < 0) {return -*cmd;}

    return 0;
}

/*!
 *  @brief      Sending value to the holder of the chosen command
 *  @param[in]  cmd   Command to be handled.
 *  @param[in]  val   Value to pass along with the command.
 *  @author     Victor Busk (201409557@post.au.dk)
 */

int SPIapi::sendPacket(const unsigned char* cmd, unsigned char* data) const
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

/*!
 *  @brief      Receiving value to the holder of the chosen command
 *  @param[in]  cmd   Command to be handled.
 *  @param[in]  val   Value to pass along with the command.
 *  @author     Victor Busk (201409557@post.au.dk)
 */

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

/* [] END OF FILE */

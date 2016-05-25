/*!
 * @file        spiapi.h
 * @brief       Handles communication
 * @class       SPIapi
 * @author      Victor Busk (201409557@post.au.dk)
 */

#ifndef SPIAPI_H
#define SPIAPI_H

#include <cstdio> //Used by sprint
#include <fcntl.h> //Used by fp
#include <unistd.h> //Used by fp

/*!
 *  @defgroup MAXLEN Length constant
 */

/*! \addtogroup MAXLEN
 *  @{
 */

/* Length set */
#define MAXLEN 5         /*!< Set length of buffer */
/*! @} */

class SPIapi
{
public:
    SPIapi();

    int setPacket(const unsigned char* cmd, unsigned char* value) const;
    int getPacket(unsigned char* cmd, unsigned int* value);

private:
    int sendPacket(const unsigned char* cmd, unsigned char* data) const;
    int receivePacket(unsigned char* cmd, unsigned int* data);
};

#endif // SPIAPI_H

/* [] END OF FILE */

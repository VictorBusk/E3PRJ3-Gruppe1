/*
 * CircularMean.c
 *
 *  Author: Simon
 */

#include "CircularMean.h"

/*
    Queue is circular and can contain BUF_SIZE elements
        start points to the next element to overwrite
        num is the number of items inserted - it grows to BUF_SIZE and then stays there
*/

// Initialize a CircularMean struct
void initCircularMean(struct CircularMean *buf)
{
    int i;
	for (i = 0; i < BUF_SIZE; ++i) {
		buf->queue[i] = -1;
	}
	buf->start = 0;
	buf->num = 0;
}

// Insert char in the end of the queue
void insertValue(struct CircularMean *buf, int val)
{
    buf->queue[buf->start] = val;
    buf->start = (buf->start +1) % BUF_SIZE;
    ++(buf->num);
    if (buf->num > BUF_SIZE) {
        buf->num = BUF_SIZE;
    }
}

// Get the mean value of all the ints in the queue
int getMeanValue(struct CircularMean *buf)
{
    if (buf->num == 0)
        return 0;

    int i, temp = 0;
    for (i = 0; i < buf->num; ++i) {
        temp += buf->queue[i];
    }

    return temp / buf->num;
}

/* [] END OF FILE */

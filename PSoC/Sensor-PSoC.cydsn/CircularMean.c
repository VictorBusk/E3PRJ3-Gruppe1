/*!
 *  @file        CircularMean.h
 *  @brief       Circular buffer used for calculating the average of a series of values.
 *  Queue is circular and can contain BUF_SIZE elements.
 *      start points to the next element to overwrite.
 *      num is the number of items inserted - it grows to BUF_SIZE and then stays there.
 *
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */

#include "CircularMean.h"

/*!
 *  @brief      Initialize a CircularMean struct
 *  @param[in]  buf Pointer to the CircularMean to initialize
 *  @public
 *  @author     Simon Nejmann (19981127@uni.au.dk)
 */
void initCircularMean(struct CircularMean *buf)
{
    int i;
	for (i = 0; i < BUF_SIZE; ++i) {
		buf->queue[i] = -1;
	}
	buf->start = 0;
	buf->num = 0;
}

/*!
 *  @brief      Insert value, possibly overwriting oldest entry
 *  @param[in]  buf Pointer to the CircularMean to insert into
 *  @param[in]  val Value to insert
 *  @public
 *  @author     Simon Nejmann (19981127@uni.au.dk)
 */
void insertValue(struct CircularMean *buf, int val)
{
    buf->queue[buf->start] = val;
    buf->start = (buf->start +1) % BUF_SIZE;
    ++(buf->num);
    if (buf->num > BUF_SIZE) {
        buf->num = BUF_SIZE;
    }
}

/*!
 *  @brief      Get the average value of all the ints in the buffer
 *  @param[in]  buf Pointer to the CircularMean
 *  @return The average value calculated
 *  @public
 *  @author     Simon Nejmann (19981127@uni.au.dk)
 */
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

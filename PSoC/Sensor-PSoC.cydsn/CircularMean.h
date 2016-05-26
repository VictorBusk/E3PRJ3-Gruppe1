/*!
 *  @file        CircularMean.h
 *  @class       CircularMean
 *  @brief       Circular buffer used for calculating the average of a series of values.
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */

#ifndef CIRCULARMEAN_H_
#define CIRCULARMEAN_H_

/*! The size of the buffer. Max 255 */
#define BUF_SIZE 30

/*!
 * @brief       Struct for the buffer
 */
struct CircularMean {
	int queue[BUF_SIZE];    /*!< Array holding the inserted values */
	unsigned char start;    /*!< Points to the next array-cell to write in */
	unsigned char num;    /*!< Number of values current in the array */
};

/*!
 *  @brief      Initialize a CircularMean struct
 *  @param[in]  buf Pointer to the CircularMean to initialize
 *  @public
 *  @author     Simon Nejmann (19981127@uni.au.dk)
 */
void initCircularMean(struct CircularMean *buf);

/*!
 *  @brief      Insert value, possibly overwriting oldest entry
 *  @param[in]  buf Pointer to the CircularMean to insert into
 *  @param[in]  val Value to insert
 *  @public
 *  @author     Simon Nejmann (19981127@uni.au.dk)
 */
void insertValue(struct CircularMean *buf, int val);

/*!
 *  @brief      Get the average value of all the ints in the buffer
 *  @param[in]  buf Pointer to the CircularMean
 *  @return     The average value calculated
 *  @public
 *  @author     Simon Nejmann (19981127@uni.au.dk)
 */
int getMeanValue(struct CircularMean *buf);

#endif /* CIRCULARMEAN_H_ */
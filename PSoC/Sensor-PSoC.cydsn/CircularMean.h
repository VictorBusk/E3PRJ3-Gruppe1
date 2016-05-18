/*
 * CircularMean.h
 *
 *  Author: Simon
 */ 

#ifndef CIRCULARMEAN_H_
#define CIRCULARMEAN_H_

// Max size 255
#define BUF_SIZE 30

// Struct for the buffer
struct CircularMean {
	int queue[BUF_SIZE];
	unsigned char start;
	unsigned char num;
};

// Initialize a CircularMean struct
void initCircularMean(struct CircularMean *buf);

// Insert char in the end of the queue
void insertValue(struct CircularMean *buf, int val);

// Get the mean value of all the ints in the queue
int getMeanValue(struct CircularMean *buf);

#endif /* CIRCULARMEAN_H_ */
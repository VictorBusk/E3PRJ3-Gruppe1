/*!
 * @file        queue.h
 * @brief       A queue for incoming commands
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#ifndef QUEUE_H
#define QUEUE_H
    
#include <project.h>

/*!
 *  @class Queue
 */
   
/***************************************
*       Public data types
***************************************/

/*!
 *  @brief      Struct to contain a command and value
 *  @public
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
struct Data
{
  int cmd_;         /**< Command stored in queue */
  int val_;         /**< Value stored in queue */
};

/***************************************
*       Public methods            
***************************************/

extern void queue_init(uint8 queueSize);
extern void pushQueue(const struct Data data);
extern void popQueue(void);
extern struct Data frontQueue(void);
extern int isEmptyQueue(void);
extern uint8 queueCount_;


#endif  // ifndef QUEUE_H
/* [] END OF FILE */
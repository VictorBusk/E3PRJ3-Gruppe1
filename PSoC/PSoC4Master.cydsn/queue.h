/*!
 *  @file       queue.h
 *  @brief      Queue modul
 *  @details    En FIFO kø der er opbygget af en single linket liste.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <project.h>

/***************************************
 *       Class
 ***************************************/
    
/*!
 *  @class      Queue queue.h
 *  @brief      Queue class
 *  @details    En FIFO kø der er opbygget af en single linket liste.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
    
 
/***************************************
 *       Public data types
 ***************************************/

/*!
 *  @brief      Action struct
 *  @details    Structen kan indeholde en kommando og tilhørende værdi, som kan indsættes i FIFO køen.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
struct Action
{
  int cmd;         /**< Kommando */
  int val;         /**< Værdi */
};


/***************************************
 *       Public methods
 ***************************************/

extern void queue_init(uint8 queueMaxSize);
extern void pushQueue(const struct Action data);
extern void popQueue(void);
extern struct Action frontQueue(void);
extern uint8 isEmptyQueue(void);

#endif  // ifndef QUEUE_H
/* [] END OF FILE */

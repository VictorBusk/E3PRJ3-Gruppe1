/*!
 *  @file       queue.h
 *  @brief      Queue modul
 *  @details    En FIFO kø der er opbygget af en single linket liste.
 *  @ingroup    PSoC-Master
 *  @class      Queue queue.h
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <project.h>

/***************************************
 *       Public data types
 ***************************************/

/*!
 *  @brief      En struct til at lager data der skal indsættes i køen
 *  @details    Structen kan indeholde en kommando og tilhørende værdi, som kan indsættes i FIFO køen.
 *  @ingroup    PSoC-Master
 *  @public
 *  @memberof   Queue
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
extern struct Data frontQueue(void);
extern uint8 isEmptyQueue(void);

#endif  // ifndef QUEUE_H
/* [] END OF FILE */
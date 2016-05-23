/*!
 * @file        queue.c
 * @brief       A queue for incoming commands
 * @class       Queue
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/***************************************
*       Private data types
***************************************/

/*!
 *  @brief      Struct to contain a element in the queue
 *  @private
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
struct Node
{
  struct Data data_;    /**< Data stored in queue */
  struct Node* next_;   /**< Next node in queue */
};

/***************************************
*       Private attributes
***************************************/

/*!
 *  @brief      Pointer to front element in queue
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
static struct Node* frontOfQueuePtr_;

/*!
 *  @brief      Pointer to back element in queue
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
static struct Node* backOfQueuePtr_;

/*!
 *  @brief      Conuter for elements in the queue
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
uint8 queueCount_;

/*!
 *  @brief      Maximum elements in queue
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
static uint8 queueMax_;

/***************************************
*       Private methods            
***************************************/

static void headInsert(struct Node** headPtr, const struct Data data);
static void headRemove(struct Node** headPtr);
static void backInsert(struct Node** backPtr, const struct Data data);


/***************************************
 *       Public methods
 ***************************************/

/**
 *  @brief      Initialize queue.
 *  @param[in]  queueSize   Size of queue.
 *  @public
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void queue_init(uint8 queueSize)
{
  frontOfQueuePtr_ = NULL;
  frontOfQueuePtr_->next_ = NULL;
  backOfQueuePtr_ = NULL;
  backOfQueuePtr_->next_ = NULL;
  queueMax_ = queueSize;
  queueCount_ = 0;
}

/**
 *  @brief      Insert element in FIFO ordre in queue 
 *  @param[in]  data    Struct of data to be placed in the queue
 *  @public
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void pushQueue(const struct Data data)
{
  if(queueCount_<queueMax_)
  {
    if(isEmptyQueue() != 1)
    {
      backInsert(&backOfQueuePtr_, data);
      backOfQueuePtr_ = backOfQueuePtr_->next_;
      queueCount_++;
    }
    else
    {
      headInsert(&frontOfQueuePtr_, data);
      backOfQueuePtr_ = frontOfQueuePtr_;
      queueCount_++;
    }
    DEBUG_PutString("Q+: count: ");
    DEBUG_PutHexByte(queueCount_);
    DEBUG_PutString(" cmd: ");
    DEBUG_PutHexByte(data.cmd_);
    DEBUG_PutString(" val: ");
    DEBUG_PutHexByte(data.val_);
    DEBUG_PutCRLF();
    DEBUG_PutCRLF();
  }
  else
  {
    DEBUG_PutString("Q~: ERROR! Queue FULL!!! count: ");
    DEBUG_PutHexByte(queueCount_);
    DEBUG_PutCRLF();
    DEBUG_PutCRLF();
  }
  
}

/**
 *  @brief      Remove front element of the queue  
 *  @public
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void popQueue()
{
  headRemove(&frontOfQueuePtr_);
  queueCount_--;
  if(isEmptyQueue() == 1)
  {
    backOfQueuePtr_ = NULL;
  }
  DEBUG_PutString("-Q: count: ");
  DEBUG_PutHexByte(queueCount_);
  DEBUG_PutCRLF();
  DEBUG_PutCRLF();
}

/*!
 *  @brief      Return data from the front element in the queue 
 *  @return     Data
 *  @public
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
struct Data frontQueue()
{
  DEBUG_PutString("Q=: count: ");
  DEBUG_PutHexByte(queueCount_);
  DEBUG_PutCRLF();
  return frontOfQueuePtr_->data_;
}

/*!
 *  @brief      Return 1 (true) if queue is empty or 0 (false) if not 
 *  @return     int
 *  @public
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
int isEmptyQueue()
{
  if(frontOfQueuePtr_ == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*!
 *  @brief      Insert element in the front of the queue
 *  @param[in]  headPtr     Pointer to front of queue
 *  @param[in]  data        Struct of data to be placed in the queue
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void headInsert(struct Node** headPtr, const struct Data data)
{
  struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
  if(temp == NULL)
  {
    return;
  }

  temp->data_ = data;
  temp->next_ = NULL;

  *headPtr = temp;
}

/*!
 *  @brief      Remove element in front af queue
 *  @param[in]  headPtr     Pointer to front of queue
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void headRemove(struct Node** headPtr)
{
  if(headPtr != NULL)
  {
struct Node* condemned;
    condemned = *headPtr;
    *headPtr = (*headPtr)->next_;
    free(condemned);
  }
}

/*!
 *  @brief      Insert element in the back of the queue
 *  @param[in]  backPtr     Pointer to back of queue
 *  @param[in]  data        Struct of data to be placed in the queue
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void backInsert(struct Node** backPtr, const struct Data data)
{
  if(*backPtr == NULL)
  {
    return;
  }

  struct Node* next = (*backPtr)->next_;
  struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
  temp->data_ = data;
  temp->next_ = next;
  (*backPtr)->next_ = temp;
}

/* [] END OF FILE */
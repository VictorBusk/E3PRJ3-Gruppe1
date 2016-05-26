/*!
 *  @file       queue.c
 *  @brief      Queue modul
 *  @details    En FIFO kø der er opbygget af en single linket liste.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>


/***************************************
 *       Private data types
 ***************************************/

/*!
 *  @brief      Node struct
 *  @details    En struct til at oprette et element der kan indsættes i køen.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
struct Node
{
  struct Action data_;  /**< Data til køen */
  struct Node* next_;   /**< Pointer til næste node i køen */
};


/***************************************
 *       Private attributes
 ***************************************/

/*!
 *  @brief      Pointer til foreste element i køen
 *  @details    En Node pointer der indeholder adressen på det foreste elementet i køen.
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
static struct Node* frontOfQueuePtr_;

/*!
 *  @brief      Pointer til bagerste element i køen
 *  @details    En Node pointer der indeholder adressen på det bagerste elementet i køen.
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
static struct Node* backOfQueuePtr_;

/*!
 *  @brief      Køens max
 *  @details    Laver ved initialisering der ønsket antal for max elementer i køen
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
static uint8 queueMax_;

/*!
 *  @brief      Kø element tæller
 *  @details    Bruges til at tælle hvor mange elementer der er i køen.
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
static uint8 queueCount_;


/***************************************
 *       Private methods
 ***************************************/

static void headInsert(struct Node** headPtr, const struct Action data);
static void headRemove(struct Node** headPtr);
static void backInsert(struct Node** backPtr, const struct Action data);


/***************************************
 *       Public methods
 ***************************************/

/*!
 *  @brief      Initialiser Queue modulet.
 *  @details    Initailiser køen med den ønsket max størelse.
 *  @public
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
void queue_init(uint8 queueMaxSize)
{
  frontOfQueuePtr_ = NULL;
  frontOfQueuePtr_->next_ = NULL;
  backOfQueuePtr_ = NULL;
  backOfQueuePtr_->next_ = NULL;
  queueMax_ = queueMaxSize;
  queueCount_ = 0;
}

/**
 *  @brief      Indsætter et element i køen
 *  @details    Indsætter det angivet element bagerst i FIFO køen.
 *  @param[in]  data    Data der skal indsættes i køen.
 *  @public
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
void pushQueue(const struct Action data)
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
    DEBUG_PutHexByte(data.cmd);
    DEBUG_PutString(" val: ");
    DEBUG_PutHexByte(data.val);
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
 *  @brief      Fjerner et element i køen
 *  @details    Fjerner det foreste element i FIFO køen.
 *  @public
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
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

/**
 *  @brief      Viser et element fra køen
 *  @details    Viser det foreste element i FIFO køen.
 *  @public
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
struct Action frontQueue()
{
  DEBUG_PutString("Q=: count: ");
  DEBUG_PutHexByte(queueCount_);
  DEBUG_PutCRLF();
  return frontOfQueuePtr_->data_;
}

/**
 *  @brief      Retuner status af køen
 *  @details    Kontrollere om køen er tom.
 *  @public
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
uint8 isEmptyQueue()
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

/**
 *  @brief      Indsætter forreste i listen
 *  @details    Indsætter det angivet element forreste i den underlægende linked liste.
 *  @param[in]  headPtr Pointer til det foreste element i listen.
 *  @param[in]  data    Data der skal indsættes i listen.
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
void headInsert(struct Node** headPtr, const struct Action data)
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

/**
 *  @brief      Fjerner fra listen
 *  @details    Fjerner det forreste element i den underlæggende linked liste
 *  @param[in]  headPtr Pointer til det forreste element i listen.
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
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

/**
 *  @brief      Indsætter bagerst i listen
 *  @details    Indsætter det angivet element bagerst i den underlægende linked liste.
 *  @param[in]  backPtr Pointer til det bagerste element i listen.
 *  @param[in]  data    Data der skal indsættes i listen.
 *  @private
 *  @memberof   Queue
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
void backInsert(struct Node** backPtr, const struct Action data)
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
/* ========================================
 *
 * File: queue.c
 * Description:
 *
 * University: AARHUS UNIVERSITY SCHOOL OF ENGINEERING
 * Project: F16 - E3PRJ3-02 Semesterprojekt 3 [240501U178]
 * Group: 1
 *
 * Author: Jeppe Stærk
 * Matriculation number: 201271201
 *
 * Version: 1.0
 * Date: 13-05-2016
 *
 * ========================================
 */

#include "queue.h"

struct Node* frontOfQueuePtr;
struct Node* backOfQueuePtr;

void queue_init()
{
  frontOfQueuePtr = NULL;
  frontOfQueuePtr->next_ = NULL;
  backOfQueuePtr = NULL;
  backOfQueuePtr->next_ = NULL;
}

void pushQueue(const struct Data data)
{
  if(isEmptyQueue() != 1)
  {
    backInsert(&backOfQueuePtr, data);
    backOfQueuePtr = backOfQueuePtr->next_;
  }
  else
  {
    headInsert(&frontOfQueuePtr, data);
    backOfQueuePtr = frontOfQueuePtr;
  }
}

void popQueue()
{
  headRemove(&frontOfQueuePtr);
  if(isEmptyQueue() == 1)
  {
    backOfQueuePtr = NULL;
  }
}

struct Data frontQueue()
{
  return frontOfQueuePtr->data_;
}

int isEmptyQueue()
{
  if(frontOfQueuePtr == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

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

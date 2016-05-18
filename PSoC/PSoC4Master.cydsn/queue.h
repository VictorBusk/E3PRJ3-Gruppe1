/* ========================================
 *
 * File: queue.h
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

#ifndef QUEUE_H
#define QUEUE_H

#include <project.h>
#include <stdio.h>
#include <stdlib.h>

struct Data
{
  int cmd_;
  int val_;
};

struct Node
{
  struct Data data_;
  struct Node* next_;
};

struct Node* frontOfQueuePtr;
struct Node* backOfQueuePtr;

extern void queue_init(void);
extern void pushQueue(const struct Data data);
extern void popQueue(void);
extern struct Data frontQueue(void);
extern int isEmptyQueue(void);

void headInsert(struct Node** headPtr, const struct Data data);
void headRemove(struct Node** headPtr);
void backInsert(struct Node** backPtr, const struct Data data);

#endif  // ifndef QUEUE_H
/* [] END OF FILE */

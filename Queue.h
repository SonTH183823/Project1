#include <stdio.h>
#include <stdlib.h>

typedef struct NodeQueue
{
  int value;
  struct NodeQueue *next;
} NodeQueue;

void pushNodeQueue(int);
int popNodeQueue();

NodeQueue *initNodeQueue(int value)
{
  NodeQueue *p = (NodeQueue *)malloc(sizeof(NodeQueue));
  p->value = value;
  p->next = NULL;
  return p;
}
NodeQueue *firstNodeQueue;
NodeQueue *lastNodeQueue;
void pushNodeQueue(int value)
{
  if (firstNodeQueue == NULL)
  {
    NodeQueue *p = initNodeQueue(value);
    firstNodeQueue = p;
    lastNodeQueue = p;
  }
  else
  {
    NodeQueue *p = initNodeQueue(value);
    lastNodeQueue->next = p;
    lastNodeQueue = p;
  }
}

int popNodeQueue()
{
  int first = firstNodeQueue->value;
  NodeQueue *p = firstNodeQueue;
  firstNodeQueue = firstNodeQueue->next;
  free(p);
  return first;
}
void pushfirstNodeQueue(int value)
{
  if (firstNodeQueue == NULL)
  {
    NodeQueue *p = initNodeQueue(value);
    firstNodeQueue = p;
    lastNodeQueue = p;
  }
  else
  {
    NodeQueue *p = initNodeQueue(value);
    p->next = firstNodeQueue;
    firstNodeQueue = p;
  }
}
void freeQueue()
{
  NodeQueue *p;
  while (firstNodeQueue != NULL)
  {
    p = firstNodeQueue->next;
    free(firstNodeQueue);
    firstNodeQueue = p;
  }
}
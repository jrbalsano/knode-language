#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include "dict.h"

typedef struct node *Node;

struct node {
  Dict dictlist;
};

void initNode();


#endif

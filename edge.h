#ifndef __EDGE_H__
#define __EDGE_H__

#include <stdio.h>
#include <stdlib.h>
#include "./libs/uthash.h"

typedef struct edge *Edge;

#include "node.h"
#include "smartpointers.h"

struct edge {
  SmartNode a;
  SmartNode b;
  enum {atob, btoa, both} edge_dir;
  int aindex;
  int bindex;
  char *edge_name;
};

/* *
 * Initialize an edge with two nodes
 */
Edge initEdge(SmartNode sa, SmartNode sb, int edge_dir);

/* *
 * Set the name of the edge
 */
void setSmartEdgeName(SmartEdge se, char *name);

/* *
 * Free the edge itself, and nothing more
 */
void freeEdge(Edge e);

#endif

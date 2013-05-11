#ifndef __EDGE_H__
#define __EDGE_H__

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

typedef struct edge *Edge;

struct edge {
  Node a;
  Node b;
  enum {atob, btoa, both} edge_type;
  char *type;
};

/* *
 * Initialize an edge with two node
 */
Edge initEdge(Node n1, Node n2, int edge_type);

/* *
 * Free the edge itself, and nothing more
 */
void freeEdge(Edge e);

#endif

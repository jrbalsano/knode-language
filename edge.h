#ifndef __EDGE_H__
#define __EDGE_H__

#include <stdio.h>
#include <stdlib.h>
#include "./libs/uthash.h"

typedef struct edge *Edge;

#include "node.h"

struct edge {
  Node a;
  Node b;
  enum {atob, btoa, both} edge_dir;
  int aindex;
  int bindex;
  char edge_name[42];
};

/* *
 * Initialize an edge with two nodes
 */
Edge initEdge(Node a, Node b, int edge_dir);

/* *
 * Set the name of the edge
 */
void setEdgeName(Edge e, char *name);

/* *
 * Free the edge itself, and nothing more
 */
void freeEdge(Edge e);

#endif

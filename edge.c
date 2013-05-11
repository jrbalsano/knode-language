#include "edge.h"

Edge initEdge(Node n1, Node n2, int edge_type) {
  Edge e = (Edge)malloc(sizeof(struct edge));
  e->a = n1;
  e->b = n2;
  return e;
}

void freeEdge(Edge e) {
  free(e);
}

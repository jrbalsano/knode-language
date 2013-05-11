#include "edge.h"

Edge initEdge(Node a, Node b, int edge_dir) {
  Edge e = (Edge)malloc(sizeof(struct edge));
  e->a = a;
  e->b = b;
  e->edge_dir = edge_dir;
  //add edge to a and b's edgelist
  addEdge(a, b, e);
  return e;
}

void setEdgeName(Edge e, char *name) {
  strncpy(e->edge_name, name, sizeof(e->edge_name));
}

void freeEdge(Edge e) {
  free(e);
}

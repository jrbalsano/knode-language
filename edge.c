#include "edge.h"

Edge initEdge(Node n1, Node n2, int edge_dir) {
  Edge e = (Edge)malloc(sizeof(struct edge));
  e->a = n1;
  e->b = n2;
  e->edge_dir = edge_dir;
  //add edge to n1's edgelist
  addEdge(n1, e);
  //add edge to n2's edgelist
  addEdge(n2, e);
  return e;
}

void setEdgeName(Edge e, char *name) {
  strncpy(e->edge_name, name, sizeof(e->edge_name));
}

void freeEdge(Edge e) {
  free(e);
}

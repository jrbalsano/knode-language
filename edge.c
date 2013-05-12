#include "edge.h"

Edge initEdge(SmartNode a, SmartNode b, int edge_dir) {
  Edge e = (Edge)malloc(sizeof(struct edge));
  e->a = a;
  e->b = b;
  e->edge_dir = edge_dir;
  return e;
}

void setSmartEdgeName(SmartEdge se, char *name) {
  strncpy(getEdge(se)->edge_name, name, sizeof(getEdge(se)->edge_name));
  freeSmartEdge(se);
}

void freeEdge(Edge e) {
  free(e);
}

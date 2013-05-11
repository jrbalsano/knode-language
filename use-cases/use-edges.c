#include <stdio.h>
#include <string.h>
#include "../edge.h"
#include "../node.h"

int main(int argc, char *argv[]) {
  //Initialize some nodes
  Node a = initNode();
  Node b = initNode();

  //Make the nodes a little bit more interesting
  addIntToNode(a, "a's first int", 55);
  addIntToNode(b, "b's first int", 88);

  //Initialize an edge
  Edge e = initEdge(a, b, atob);
  setEdgeName(e, "merpderp");
  Edge f = initEdge(a, b, atob);
  setEdgeName(f, "herpderp");

  //Follow the edge
  printf("Edge e found this on node a: %d\n", getIntFromNode(e->a, "a's first int"));
  printf("Edge e found this on node b: %d\n", getIntFromNode(e->b, "b's first int"));
  switch(e->edge_dir) {
    case atob:
      printf("atob\n");
      break;
    case btoa:
      printf("btoa\n");
      break;
    case both:
      printf("both\n");
      break;
  }

  printf("Testing out addedge: %d\n", a->edgelist[e->aindex]->aindex);
  printf("Testing out edgename: %s\n", a->edgelist[e->aindex]->edge_name);

  printf("Testing out addedge: %d\n", a->edgelist[f->aindex]->aindex);
  printf("Testing out edgename: %s\n", a->edgelist[f->aindex]->edge_name);

  //remove edge e from the edgelist of both a and b
  removeEdge(a, e);

  //free the edge, then the nodes
  //freeEdge(e);
  //freeEdge(f);

  freeNode(a);
  freeNode(b);

  return 0;
}

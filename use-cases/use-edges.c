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

  printf("Edge e's aindex is: %d\n", a->edgelist[e->aindex]->aindex);
  printf("Edge e's edgename is: %s\n", a->edgelist[e->aindex]->edge_name);

  printf("Edge f's aindex is: %d\n", a->edgelist[f->aindex]->aindex);
  printf("Edge f's edgename is: %s\n", a->edgelist[f->aindex]->edge_name);

  //remove edge e from the edgelist of both a and b, test that our removeEdge
  //function works as expected
  printf("Right now Edge f's aindex is: %d\n", f->aindex);
  removeEdge(a, e);
  printf("After removing Edge e from a, Edge f's aindex is: %d\n", f->aindex);

  //free the nodes, which will consequently iterate through each node's
  //edgelist and free those edges as well
  freeNode(a);
  freeNode(b);

  return 0;
}

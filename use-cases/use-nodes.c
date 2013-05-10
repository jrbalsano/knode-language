#include <stdio.h>
#include <string.h>
#include "../node.h"

int main(int argc, char *argv[]) {
  //Initialize the node
  Node n = initNode();

  //add string to the node's dictionary
  addToDict(n->dictlist, echar, "hello", "world");

  //add int to node's dictionary
  int tmp = 42;
  int *tmpp = &tmp;
  addToDict(n->dictlist, eint, "hello again", tmpp);

  //add double to node's dictionary
  double tmpa = 42.13;
  double *tmppa = &tmpa;
  addToDict(n->dictlist, edouble, "hello yet again", tmppa);

  //or use node's convenience methods
  addIntToNode(n, "sup dude", 69);
  addDubToNode(n, "sup dudette", 101.5);
  addStrToNode(n, "sup dude and dudette", "not much, you?");

  //print out the entry in the dictionary of the node
  printf("Node's dictionary says: %s\n", access(n->dictlist, "hello")->value.str);
  printf("Node's dictionary says: %d\n", access(n->dictlist, "hello again")->value.num);
  printf("Node's dictionary says: %f\n", access(n->dictlist, "hello yet again")->value.dub);
  
  //print out the entry in the dictionary of the node
  printf("Node's dictionary says: %d\n", access(n->dictlist, "sup dude")->value.num);
  printf("Node's dictionary says: %f\n", access(n->dictlist, "sup dudette")->value.dub);
  printf("Node's dictionary says: %s\n", access(n->dictlist, "sup dude and dudette")->value.str);


  //Free the node
  freeNode(n);
  return 0;
}

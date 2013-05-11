#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include "dict.h"

typedef struct node *Node;

#include "edge.h"

struct node {
  Dict dictlist;
  int edgecount;
  Edge edgelist[];
};

/* *
 * Initialize the node and its corresponding dictionary list. Return the
 * pointer to the malloced node
 */
Node initNode();

/* *
 * Free the node, the dictionary of the node, and the entries in the dictionary
 * of the node
 */
void freeNode(Node n);

/* *
 * add an edge to the node's edgelist
 */
void addEdge(Node n, Edge e);

/* *
 * Add an int to the dictionary of the node
 */
void addIntToNode(Node n, char *key, int value);

/* *
 * Add a double to the dictionary of the node
 */
void addDubToNode(Node n, char *key, double value);

/* *
 * Add a string to the dictionary of the node
 */
void addStrToNode(Node n, char *key, char *value);

/* *
 * return an integer from the node's dictionary. use when we _know_ we expect
 * an integer
 */
int getIntFromNode(Node n, char *key);

/* *
 * return a double from the node's dictionary. use when we _know_ we expect a
 * double
 */
double getDubFromNode(Node n, char *key);

/* *
 * return a string from the node's dictionary. use when we _know_ we expect a
 * string
 */
char *getStrFromNode(Node n, char *key);

#endif

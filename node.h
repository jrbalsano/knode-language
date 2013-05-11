#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include "dict.h"

typedef struct node *Node;

#include "edge.h"
#include "smartpointers.h"

struct node {
  Dict dictlist;
  int edgecount;
  SmartEdge edgelist[50];
};

/* *
 * Initialize the node and its corresponding dictionary list. Return the
 * pointer to the malloced node
 */
Node initNode();

/* *
 * Free the node, the dictionary of the node, the entries in the dictionary of
 * the node, and the edges in the edgelist of the node
 */
void freeNode(Node n);

/* *
 * add an edge to the node's edgelist
 */
void addSmartEdge(SmartNode sa, SmartNode sb, SmartEdge se);

/* *
 * remove an edge from the edgelists of both nodes, then free the edge
 */
void removeSmartEdge(SmartEdge se);

/* *
 * Add an int to the dictionary of the node
 */
void addIntToSmartNode(SmartNode sn, char *key, int value);

/* *
 * Add a double to the dictionary of the node
 */
void addDubToSmartNode(SmartNode sn, char *key, double value);

/* *
 * Add a string to the dictionary of the node
 */
void addStrToSmartNode(SmartNode sn, char *key, char *value);

/* *
 * return an integer from the node's dictionary. use when we _know_ we expect
 * an integer
 */
int getIntFromSmartNode(SmartNode sn, char *key);

/* *
 * return a double from the node's dictionary. use when we _know_ we expect a
 * double
 */
double getDubFromSmartNode(SmartNode sn, char *key);

/* *
 * return a string from the node's dictionary. use when we _know_ we expect a
 * string
 */
char *getStrFromSmartNode(SmartNode sn, char *key);

#endif

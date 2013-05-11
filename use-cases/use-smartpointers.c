#include "smartpointers.h"
#include <stdio.h>

SmartDict randomDictMethod() {
  //If a dict is initialized in a method
  //create a newSmartDict instead.
  SmartDict d = newSmartDict();
  //If the value of the dict is to returned
  //you'll want to create a temporary return
  //SmartDict so it can be passed back.
  SmartDict retd = copySmartDict(d);
  //Before returning from a function, always free
  //the smartDict you initially created.
  freeSmartDict(d);
  //Return the copy.
  return retd;
}

SmartNode randomNodeMethod() {
  SmartNode n = newSmartNode();
  addIntToNode(getNode(n), "NodeInt", 3);
  SmartNode retn = newSmartNode();
  freeSmartNode(n);
  return retn;
}

void cleanUp(SmartNode n, SmartDict d) {
  //this method does nothing, so the default should just be
  //to free the smartpointer parameters before exiting.
  freeSmartNode(n);
  freeSmartNode(d);
}

int main(int argc, char *argv) {
  //When using dicts, strings, nodes, and edges, only deal with smartpointers.
  SmartDict d = randomDictMethod();
  SmartNode n = randomNodeMethod();
  cleanUp(n, d);
}


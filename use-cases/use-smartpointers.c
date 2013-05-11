#include <stdio.h>
#include "../smartpointers.h"
 
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

  //ALWAYS pass a copy of the smartpointer, not the smartpointer itself.
  addIntToSmartNode(copySmartNode(n), "NodeInt", 3);

  //We make a copy of the smartpointer we want to return
  SmartNode retn = copySmartNode(n);
  //ALWAYS free the smartpointers that were passed as parameters
  freeSmartNode(n);
  return retn;
}

void cleanUp(SmartNode n, SmartDict d) {
  //this method does nothing, so the default should just be
  //to free the smartpointer parameters before exiting.
  freeSmartNode(n);
  freeSmartDict(d);
}

int main(int argc, char **argv) {
  //When using dicts, strings, nodes, and edges, only deal with smartpointers.
  SmartDict d = randomDictMethod();
  SmartNode n = randomNodeMethod();

  //If you're going to reassign something that's represented by a smartpointer
  //you're going to have to destruct and reassign.
  freeSmartNode(n);
  n = newSmartNode();

  //Always pass copies of smart pointers, not the actual smartpointer.
  cleanUp(copySmartNode(n), copySmartDict(d));

  //Add a string to the node's dictionary
  addStrToSmartNode(copySmartNode(n), "hello", "world");

  int tmp = 42;
  addIntToSmartNode(copySmartNode(n), "hihi", tmp);

  //add string to the node's dictionary in a less convenient way.
  addToDict(getNode(n)->dictlist, echar, "hello2", "world2");

  //When you're done you should free all the smart pointers you initialized except
  //for the one you are going to return.
  freeSmartNode(n);
  freeSmartDict(d);
  return 0;
}




/*
 * 	Simple main (Driver file). You will compile this using:
 * g++ -Wall main.cpp func.cpp
 *
 * The output file will be a.out or a.exe (depending on platform).
 */

#include "mytreap.h"

#include <iostream>

using namespace std;

int main() {

  tnode *a = new tnode();
  a->key=5;
  int r = a->key;
  //test_func(r);// calls the function defined in func.cpp,and declared in mytreap.h
  tnode *root,*temp;
  root=insert_key(NULL,100);
  temp=insert_key(root,53);
  temp=insert_key(root,125);
  temp=insert_key(root,1000);

  return 0;
}


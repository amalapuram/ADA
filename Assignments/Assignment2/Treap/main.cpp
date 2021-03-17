

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
  tnode *root=NULL,*temp=NULL,*root1=NULL,*root2=NULL,*pred,*succ,*findnext,*root3;

  root=insert_key(root,100);
  //cout<<root->key;
  temp=insert_key(root,53);
  //cout<<temp->key;
  //cout<<root->key;
  temp=insert_key(root,125);
 temp=insert_key(root,1000);
  temp=insert_key(root,110);
 temp=insert_key(root,121);
  temp=insert_key(root,10);
temp=insert_key(root,2110);

 temp=insert_key(root1,195);
  temp=insert_key(root1,146);
  temp=insert_key(root1,999);
  temp=insert_key(root1,6666);
  temp=insert_key(root2,44);
  temp=insert_key(root2,66);
  temp=insert_key(root2,-1);
  temp=insert_key(root2,-859.25);

  inorder_print(root);

  cout<<"-------------------------root1----------------------------"<<endl;
  inorder_print(root1);
  cout<<"-------------------------root2----------------------------"<<endl;
  inorder_print(root2);
  cout<<"after deleting node 125-----------------------------"<<endl;
  root=delete_node(root,search_key(root,125));
 inorder_print(root);
 cout<<"after deleting node 53-----------------------------"<<endl;
  root=delete_node(root,search_key(root,53));
  inorder_print(root);

  cout<<"after deleting node 100-----------------------------"<<endl;
  root=delete_node(root,search_key(root,100));
  inorder_print(root);
  temp=join_treaps(root2,root1);
  cout<<"-------------------------------------------after joining treaps------------------------------------------------------------------"<<endl;
  inorder_print(temp);


  cout<<"new root is "<<temp->key<<endl;

  pred=predecessor(search_key(temp,-859.25));
  if(pred!=NULL)
  cout<<"predecessor for 999 "<<pred->key<<endl;
  succ=successor(search_key(temp,6666));
  if(succ!=NULL)
  cout<<"successor for 999 "<<succ->key<<endl;

  findnext=find_next(temp,66666);
  if(findnext!=NULL)
  cout<<"next element after 990 \t"<<findnext->key<<endl;

  cout<<"elements less than -859.25 \t "<<num_less_than(temp,-859.25);

  root3=split_treap(temp,0);

  cout<<"-------------------------------------------after splitting treaps------------------------------------------------------------------"<<endl;
  inorder_print(root3);

  cout<<"------------------root2---------------------------------------------------------------------------"<<endl;
  inorder_print(temp);



  //predecessor check


  return 0;
}


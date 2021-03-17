/*
 * Sample function implementation file. Gives the function definition of test_func, which was declared in mytreap.h
 *
 */

#include "mytreap.h"
#include<cstdlib>
#include<iostream>
using namespace std;



/* this file implements test_func from mytreap.h */
tnode* test_func(int k)
{

    cout<<"k's value is "<<k<<", and I will return a null pointer"<<endl;
    return NULL;
}

tnode* _validateHeapProperty(tnode* root);

//Generates random priority for the key
int _getnodePriority()
{

   return rand();

}

//Finds the root of the treap
tnode* _findRootNode(tnode* p_root)
{

    if(p_root!=NULL && p_root->parent!=NULL)
    {
        tnode *temp=p_root;
        while(temp->parent!=NULL)
        {
            //cout<<"current root->"<<temp->key<<"\t size"<<temp->size<<endl;
            temp=temp->parent;
        }

       // cout<<"current root->"<<temp->key<<"\t size"<<temp->size<<endl;
            return temp;
    }
    else
        return p_root;
}

//calculates current node size
void _calculateNodeSize(tnode* root)
{
    if(root!=NULL)
    {
       //right child exists
    if(root->left==NULL && root->right!=NULL)
        root->size=(root->right->size)+1;
        //left child exists
    else if(root->right==NULL && root->left!=NULL)
        root->size=(root->left->size)+1;
        //both child exist
    else if(root->left!=NULL && root->right!=NULL)
        root->size=root->left->size+root->right->size+1;
    else
            root->size=1;
    }

}


//Adjusts node size from current node to root of the treap
void _adjustAncestorNodeSize(tnode* p_node)
{
  if(p_node)
  {
      //Adjusting current node size
      _calculateNodeSize(p_node);
      //adjusts current node's parent size
      if(p_node->parent)
      _adjustAncestorNodeSize(p_node->parent);

  }
}

tnode* _getTreapMaxValue(tnode* p_node)
{
    //finds the max value in a treap
    tnode* temp = p_node;
    while (temp->right != NULL)
        temp = temp->right;

    return temp;
}


tnode* _getTreapMinValue(tnode* p_node)
{
    //finds the min value in a treap
    tnode* temp = p_node;
    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}




//Left Rotation for Insertion
tnode* _leftRotateforInsert(tnode* p_root)
{

    tnode *rightchild,*root,*rootparent;
    root=p_root;
    rootparent=root->parent;
    //getting right child of root
    rightchild=root->right;
    if(root->left)
    root->size=root->left->size;
    else
        root->size=1;

    //Assigning left subtree of root's right child as right child of current node
    root->right=rightchild->left;
    //sets root's parent to its right child
    root->parent=rightchild;
    //Modifying the size of root's right child
    if(rightchild->left!=NULL)
    {
        if(rightchild->right)
        rightchild->size=rightchild->right->size;
        else rightchild->size=1;
        root->size=root->size+rightchild->left->size;
        //sets root's right child's left subtree parent to root
        rightchild->left->parent=root;
    }

    rightchild->parent=rootparent;
    if(rootparent!=NULL && rootparent->left!=NULL && rootparent->left==root)
        {
            rootparent->left=rightchild;


        }
        else if(rootparent!=NULL && rootparent->right!=NULL && rootparent->right==root)
        {
            rootparent->right=rightchild;

        }

        //Assigning current root as left child of current root's right child
    rightchild->left=root;


    root->parent=rightchild;


    //making current root as old root's right child
    //root=rightchild;
    _adjustAncestorNodeSize(root);
    //root=_validateHeapProperty(rightchild->parent);

    return _validateHeapProperty(rightchild->parent);


}

//Implementation of Right Rotation for Insertion
tnode* _RightRotateforInsert(tnode* p_root)
{

    tnode *leftchild,*root,*rootparent;
    root=p_root;
    //Storing the initial root's parent address
    rootparent=root->parent;
    //getting left child of root
    leftchild=root->left;
    if(root->right)
    root->size=root->right->size;
    else
        root->size=1;

    //Assigning right subtree of root's left child as left child of current node
    root->left=leftchild->right;

    //sets current root's parent to its left child
    root->parent=leftchild;
    //Modifying the size of root's right child
    if(leftchild->right!=NULL)
    {
        if(leftchild->left)
        leftchild->size=leftchild->left->size;
        else leftchild->size=1;

        root->size=root->size+leftchild->right->size;
        //sets root's left child's right subtree parent to root
        leftchild->right->parent=root;
    }

    leftchild->parent=rootparent;
    if(rootparent!=NULL && rootparent->left!=NULL && rootparent->left==root)
        {
            rootparent->left=leftchild;


        }
        else if(rootparent!=NULL && rootparent->right!=NULL && rootparent->right==root)
        {
            rootparent->right=leftchild;

        }

    //Assigning current root as right child of current root's right child
    leftchild->right=root;

    root->parent=leftchild;

    _adjustAncestorNodeSize(root);
   // root=_validateHeapProperty(leftchild->parent);

    return _validateHeapProperty(leftchild->parent);


}


//Implementation of Left Rotation
tnode* _leftRotateforDelete(tnode* p_root)
{

    tnode *rightchild,*root,*rootparent;
    root=p_root;
    rootparent=root->parent;
    //getting right child of root
    rightchild=root->right;
    if(root->left)
    root->size=root->left->size;
    else
        root->size=1;

    //Assigning left subtree of root's right child as right child of current node
    root->right=rightchild->left;
    //sets root's parent to its right child
    root->parent=rightchild;
    //Modifying the size of root's right child
    if(rightchild->left!=NULL)
    {
        if(rightchild->right)
        rightchild->size=rightchild->right->size;
        else rightchild->size=1;
        root->size=root->size+rightchild->left->size;
        //sets root's right child's left subtree parent to root
        rightchild->left->parent=root;
    }

    rightchild->parent=rootparent;
    if(rootparent!=NULL && rootparent->left!=NULL && rootparent->left==root)
        {
            rootparent->left=rightchild;


        }
        else if(rootparent!=NULL && rootparent->right!=NULL && rootparent->right==root)
        {
            rootparent->right=rightchild;

        }

        //Assigning current root as left child of current root's right child
    rightchild->left=root;


    root->parent=rightchild;


    //making current root as old root's right child
    //root=rightchild;
    _adjustAncestorNodeSize(rightchild);

    return rightchild;


}

//Implementation of Right Rotation
tnode* _RightRotateforDelete(tnode* p_root)
{

     tnode *leftchild,*root,*rootparent;
    root=p_root;
    //Storing the initial root's parent address
    rootparent=root->parent;
    //getting left child of root
    leftchild=root->left;
    if(root->right)
    root->size=root->right->size;
    else
        root->size=1;

    //Assigning right subtree of root's left child as left child of current node
    root->left=leftchild->right;

    //sets current root's parent to its left child
    root->parent=leftchild;
    //Modifying the size of root's right child
    if(leftchild->right!=NULL)
    {
        if(leftchild->left)
        leftchild->size=leftchild->left->size;
        else leftchild->size=1;

        root->size=root->size+leftchild->right->size;
        //sets root's left child's right subtree parent to root
        leftchild->right->parent=root;
    }

    leftchild->parent=rootparent;
    if(rootparent!=NULL && rootparent->left!=NULL && rootparent->left==root)
        {
            rootparent->left=leftchild;


        }
        else if(rootparent!=NULL && rootparent->right!=NULL && rootparent->right==root)
        {
            rootparent->right=leftchild;

        }

    //Assigning current root as right child of current root's right child
    leftchild->right=root;

    root->parent=leftchild;

    _adjustAncestorNodeSize(leftchild);
    //root=_validateHeapProperty(root);

    return leftchild;


}

//Helper method for checking min-heap property
tnode* _validateHeapProperty(tnode* p_root)
{

    tnode* root=p_root;
    if(p_root!=NULL)
    {
    /*cout<<"root->"<<root->key<<"\t root priority"<<p_root->priority<<endl;
    if(p_root->left!=NULL)
        cout<<"left child ->"<<p_root->left->key<<"\t child prioroty"<<p_root->left->priority<<endl;
    if(p_root->right!=NULL)
        cout<<"right child->"<<p_root->right->key<<"\t child prioroty"<<p_root->right->priority<<endl;*/
    //checks if left child has hight priority
    if(root->left!=NULL && root->left->priority < root->priority)
        return _RightRotateforInsert(root);
    //checks if right child has high priority
    else if(root->right!=NULL && root->right->priority < root->priority)
        return _leftRotateforInsert(root);
    //Returns root if all are equal priority
    return p_root;
    }
    else
        return root;
}







tnode* search_key(tnode *root,float key )
{
    //Return NULL is root is NULL
     if(root==NULL)
        return NULL;
        //Return current root id its the key
     else if(abs(root->key-key)==0){
           // cout<<"key was "<<root->key;
        return root;
     }
        //searching the right subtree
    else if((root->key-key)<0){
           // cout<<"key was "<<root->key;
        return search_key(root->right,key);
    }
        //searching the left subtree
    else {
            //cout<<"key was "<<root->key;
            return search_key(root->left,key);
    }

}

//proxy method for inorder traversal
void inorder_printProxy(tnode *root)
{
    if(root!=NULL)
    {
        if(root->left)
        inorder_printProxy(root->left);
        //cout<<endl<<root->key<<"\t priority:"<<root->priority<<"\t size:"<<root->size<<endl;
        cout<<root->key<<" ";
        if(root->right)
        inorder_printProxy(root->right);

    }
    //cout<<endl;

}

void inorder_print(tnode* root)
{
    //if root is non NULL , calls proxy method for inorder traversal print
    if(root!=NULL)
    {
        inorder_printProxy(_findRootNode(root));
        cout<<endl;
    }
}




tnode* _createNode(float p_key)
{

    tnode* newnode = new tnode();
    newnode->left = newnode->right = newnode->parent=NULL;
    newnode->key = p_key;
    //Assigning random priority
    newnode->priority = _getnodePriority();
    newnode->size=1;
   // cout<<"inserting"<< "key: "<<p_key <<"\t"<<"priority: "<<newnode->priority<<endl;
    return newnode;
}



tnode* insert_keyProxy(tnode *root, float k)
{
    tnode *temp;
//creating the new node if root is null
    if(root==NULL)
        return _createNode(k);
    //k is smaller than root insertion will go in left child
    if ((root->key-k)>=0){
        temp= insert_keyProxy(root->left, k);
        temp->parent=root;
        //cout<<"parent node: "<<root->key;
        root->left=temp;

    }

    else{
//k is larger than root insertion will go in right child
        temp=insert_keyProxy(root->right, k);
        temp->parent=root;
        //cout<<"parent node: "<<root->key;
        root->right = temp;
          }

return root;

}

tnode* insert_key(tnode *&root, float k)
{
    tnode *temp,*temp2;
    //Handling first insertion on empty treap
    if(root==NULL)
    {
        *&root=insert_keyProxy(root,k);
        return root;
    }
    //Adjusting root node prior to insertion
    temp=insert_keyProxy(root,k);
    //Finds Root Node
    temp2=_findRootNode(temp);
    //Finds k's position in treap
    temp=search_key(temp2,k);
    //Adjusting k's parent node size
    _calculateNodeSize(temp->parent);
    //Adjusting k's ancestor's size
    _adjustAncestorNodeSize(temp->parent);
    //validates heap property on treap
    temp2=_validateHeapProperty(temp->parent);
    //Reassigning the root
    *&root=_findRootNode(temp);

    return temp;
}


tnode* _delete_nodeproxy(tnode *x)
{
    tnode *rchild,*lchild,*temp,*temp2;

    //handling deletion node is a leaf node
    if(x!=NULL && x->left==NULL && x->right==NULL && x->parent!=NULL)
    {
        temp2=x->parent;
        if(x->parent->left && x->parent->left==x)
        {
            //if leaf node is an left child
            temp=x;
            x->parent->left=NULL;
            _adjustAncestorNodeSize(x->parent);
            x->parent=NULL;
            delete(temp);



        }
        else{
            //if leaf node is an right child
            temp=x;
            x->parent->right=NULL;
            _adjustAncestorNodeSize(x->parent);
            x->parent=NULL;
            delete(temp);


        }
        return temp2;
    }
        //if deletion node is internal node and had only right subtree
    else if(x!=NULL && x->left==NULL && x->right!=NULL)
    {
        //Replacing the node to be deleted with its right child
        rchild=x->right;
        rchild->parent=x->parent;
        temp=x;
     //cout<<"key"<<x->key<<"right child"<<x->right->key;
        if(x->parent!=NULL && x->parent->left!=NULL && x->parent->left==x)
        {
            x->parent->left=rchild;


        }
        else if(x->parent!=NULL && x->parent->right!=NULL && x->parent->right==x)
        {
            x->parent->right=rchild;

        }
        x->right=NULL;
        x->parent=NULL;
        delete(temp);
        //Assigning the Right child to current node
        temp2=rchild;
        //Adjusting the node size
        _adjustAncestorNodeSize(temp2->parent);

        return rchild;

    }
    ////if deletion node is internal node and had only right subtree
    else if(x!=NULL && x->right==NULL && x->left!=NULL)
    {
        //Replacing the node to be deleted with its left child
        lchild=x->left;
        lchild->parent=x->parent;
        temp=x;
        //cout<<"key"<<x->key<<"left child"<<x->left->key;
        if(x->parent!=NULL && x->parent->left!=NULL && x->parent->left==x)
        {
            x->parent->left=lchild;


        }
        else if(x->parent!=NULL && x->parent->right!=NULL && x->parent->right==x)
        {
            x->parent->right=lchild;

        }
        x->left=NULL;
        x->parent=NULL;
        delete(temp);
        //Assigning left child as current node
        temp2=lchild;
        //Adjusting the node size
        _adjustAncestorNodeSize(temp2->parent);

        return lchild;
    }
    //if both child present for deletion node,check for least priority child
    else if(x->left!=NULL && x->right!=NULL){
            if (x->left->priority >= x->right->priority){
             //Rotating left , left child is least priority
             x = _leftRotateforDelete(x);
            // cout<<"Node to be deleted"<<x->key<<" its left child"<<x->left->key;
             x->left = _delete_nodeproxy(x->left);
            // cout<<"key returning"<<x->key;
             return x;
             }
            else
                {
                //Rotates Right, right child is least priority
                x = _RightRotateforDelete(x);
                x->right = _delete_nodeproxy(x->right);
                //cout<<"key returning"<<x->key;
                return x;
                }
     }
    else{
            x=NULL;
            //return root;
        }

    return NULL;
}

tnode* delete_node(tnode *root, tnode *x)
{
    tnode *temp=NULL;
    if(root!=NULL){
    //invoking helper delete node proxy function
    temp=_delete_nodeproxy(x);
    //Returns root node of resultant tree after deletion
     return _findRootNode(temp);
     }
else
    return root;
}


tnode* join_treaps(tnode *root1, tnode *root2)
{
    //checking for NULL root node
    if(root1==NULL)
        return root2;
    else if(root2==NULL)
        return root1;
    else
    {
        tnode *temp,*left,*right;
        float tempvalue;
        //finds maximum value node in the treap rooted with root1
        left=_getTreapMaxValue(root1);
        //finds minimum value node in the treap rooted with root2
        right=_getTreapMinValue(root2);
        //calculates average value
        tempvalue=(left->key+right->key)/2;
        //creating dummy node
        temp=_createNode(tempvalue);
        temp->left=root1;
        temp->right=root2;
        //removing the dummy node
        return delete_node(temp,temp);


    }
}



tnode* successor(tnode *x)
{
    if(x!=NULL)
    {
        tnode *temp;
        //checks for min values in right subtree if it exists
        if(x->right!=NULL)
            return _getTreapMinValue(x->right);

        //Traversing to ancestor until current node is an left child
        temp=x->parent;
        while(temp!=NULL && x==temp->right)
        {
            x=temp;
            temp=temp->parent;
        }
        return temp;

    }
    return NULL;
}


tnode* predecessor(tnode *x)
{
    if(x!=NULL)
    {
        //checks for maximum element in the left subtree if it exists
        tnode *temp;
        if(x->left!=NULL)
            return _getTreapMaxValue(x->left);

        //Traversing to ancestor until current node is an right child
        temp=x->parent;
        while(temp!=NULL && x==temp->left)
        {
            x=temp;
            temp=temp->parent;
        }
        return temp;

    }
    return NULL;
}

tnode* find_next(tnode* root, float k)
{
    //checks for leaf node
    if(root->right==NULL && root->left==NULL && (root->key-k)<0)
        return NULL;
    //checks for NULL left subtree / left subtree with smaller element
    if (((root->key-k) >= 0 && root->left == NULL)|| (root->key-k >= 0 && root->left->key-k < 0))

        return root;

    //if k is larger than current root, we find it in the right sub tree
    if ((root->key-k)<= 0)
        return find_next(root->right, k);
    //otherwise finds in the left subtree
      else
        return find_next(root->left, k);

}


tnode* find_previous(tnode *root, float key)
{
    // check for NULL root
    if (root == NULL)
        return NULL;
    if (abs(root->key-key)== 0)
        return root;
  //checking right subtree
    else if ((root->key-key)< 0) {
        tnode *temp = find_previous(root->right, key);
        if (temp == NULL)
            return root;
        else
            return temp;
    }

    //checking left subtree
    else if ((root->key-key) > 0)
        return find_previous(root->left, key);
}


int num_less_than(tnode *root,float k)
{
    
   //base case NULL check
    if(root==NULL)
        return 0;
    //check left subtree if key k smaller than current node
    if((root->key-k)>=0)
        return num_less_than(root->left,k);
    else{
        //check right subtree
        if(root->left!=NULL)
            return 1+root->left->size+num_less_than(root->right,k);
        else
            return 1+num_less_than(root->right,k);
    }

}


//root is root node of the original treap, node is contains the key which is basis for splitting
tnode* _split_treapProxy(tnode *&root,tnode *node)
{
    //check for non-null target node
    if(node!=NULL)
    {
        tnode *leftchild,*rightchild,*targetNode;
        //holding left and right subtree's of Node
        leftchild=node->left;
        rightchild=node->right;

        targetNode=node;
        //iteratively splitting the treap  from target node to root node
        while(node->parent!=NULL)
        {
            if(node->parent->left==node)
            {
                node=node->parent;
                node->left=rightchild;
                if(rightchild!=NULL)
                    rightchild->parent=node;
                rightchild=node;
                //calculate right child subtree size
                _calculateNodeSize(rightchild);
                //adjusts ancestors node sizes
                _adjustAncestorNodeSize(rightchild);


            }
            else
            {
                node=node->parent;
                node->right=leftchild;
                if(leftchild!=NULL)
                    leftchild->parent=node;
                leftchild=node;
                //calculate left child subtree size
                _calculateNodeSize(leftchild);
                //adjusts ancestors node sizes
                _adjustAncestorNodeSize(leftchild);

            }
        }
        //sets new created treaps parent node to NULL
        if(leftchild!=NULL)
        leftchild->parent=NULL;
        if(rightchild!=NULL)
        rightchild->parent=NULL;

        /*if(keynotfound)
        {
            temp=insert_key(rightchild,targetNode->key);
            _calculateNodeSize(temp);
            _adjustAncestorNodeSize(temp);
            rightchild=_findRootNode(temp);
        }*/

        //deleting the splitter node from tree
        targetNode->left=NULL;
        targetNode->right=NULL;
        delete(targetNode);


        //calculating root's sizes
        _calculateNodeSize(leftchild);
        _calculateNodeSize(rightchild);


        *&root=leftchild;

        return rightchild;


    }
    else
        return NULL;
}

tnode* split_treap(tnode *&root, float k)
{
    tnode *targetNode,*temp;
    
    //searching for the node with key k
    targetNode=search_key(root,k);
    //if key k not found
    if(targetNode==NULL){
        //inserting key k with random priority
        targetNode=insert_key(root,k);
        //changing the priority to -1
        targetNode->priority=-1;
        cout<<"root is"<<root->key;
        //Restructuring the treap to make target node as root of treap
        temp=_validateHeapProperty(targetNode->parent);
        //sets the new root
        *&root=_findRootNode(targetNode);
        cout<<"new root is"<<root->key;

            }

    return _split_treapProxy(root,targetNode);

}









/* Main should only be in the main-driver file */
//~ int main() {
//~ tnode* nodepointer = test_func(10);
//~ if (nodepointer==NULL) cout<<"Returned NULL pointer!"<<endl;
//~ }

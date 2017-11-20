#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()



int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()



bool InternalNode::isNotFull(){

  return this->getCount() < internalSize;

}



BTreeNode* InternalNode::internalnode_insert_left(BTreeNode* ptr)
{

      BTreeNode* temp = this->children[0];
      ((InternalNode*)this->getLeftSibling())->insert(temp);
      children[0] = ptr;
      this->sort();
      this->changeKeyVals();

      return NULL;
}



BTreeNode* InternalNode::internalnode_insert_right(BTreeNode* ptr)
{

        ((InternalNode*)this->getRightSibling())->insert(ptr);
	this->sort();
       return NULL;



}





InternalNode* InternalNode::insert(int value)
{
  int i = 0;
  BTreeNode* ptr;

  int x = 1;
  for(i = count-1; i >= 0; i--) {
    if(keys[i] < value) {
    ptr = children[i]->insert(value);
    changeKeyVals();
    x = 0;
    break;
    }
  }
  


  if(x == 1) {
    ptr = children[0]->insert(value);
    changeKeyVals();
  }


    if (ptr == NULL)
    {
      return NULL;
    }

  





    if (this->getCount() < internalSize)
    {
      this->insert(ptr);

      changeKeyVals();

      return NULL;
    }



    





    if(this->getLeftSibling() != NULL && this->getLeftSibling()->getCount() < internalSize)
    {
      return ((InternalNode*)internalnode_insert_left(ptr));

    }
  





    if(this->getRightSibling() != NULL && this->getRightSibling()->getCount() < internalSize)
    {

   
	   if( ptr->getMinimum() > this->children[count-1]->getMinimum()  )
	   {
	    return ((InternalNode*)internalnode_insert_right(ptr));
	   }

	   else
	   {
	     ((InternalNode*)internalnode_insert_right(this->children[count-1]));
 	     this->count--;	 
	     this->insert(ptr);
	     return NULL;
	   }
    
    }
  
    else
    {

      return split_function(ptr);
   
    }

this->sort();
    return NULL;

}// InternalNode::insert()


void InternalNode::changeKeyVals()
{

    for (int i = 0; i < this->getCount(); i++)
    {
     keys[i] = children[i]->getMinimum();
    }
}




void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ 
  children[0] = oldRoot;
  count++;
  children[1] = node2;
  count++;
  oldRoot->setParent(this);
  node2->setParent(this);
  
  this->changeKeyVals();

  this->sort();

} // InternalNode::insert()




InternalNode* InternalNode::split_function(BTreeNode* newNode)
{

  InternalNode* ptr = new InternalNode(internalSize, leafSize,  NULL, this, this->getRightSibling());


  if (this->getRightSibling() != NULL)
  {
    this->getRightSibling()->setLeftSibling(ptr);
  }

  for (int i = this->getCount() - (this->getCount()/2); i < internalSize; i++)
  {
    ptr->insert(children[i]);
    this->count--;
  }

  if (ptr->getMinimum() > newNode->getMinimum())
  {
    this->insert(newNode);
    ptr->insert(this->children[count - 1]);
    this->count--;
  }
  else
  {
    ptr->insert(newNode);
  }

  this->changeKeyVals();

  this->setRightSibling(ptr);

  this->sort();

return ptr;

}


void InternalNode::sort() {

  for( int i = 0; i < getCount(); i++ )
  {
 
		BTreeNode* lowest = children[i];
 
	 for (int j = i+1; j < getCount(); j++ )
	 {
   
		  if( children[j]->getMinimum() < lowest->getMinimum() )
		  {
   
			 lowest = children[j];
  
			 BTreeNode* temp = children[i];
   
			 children[i] = children[j];
      children[j] = temp;
   
		  }
 
	 }
 
  }
  this->changeKeyVals();
}





void InternalNode::insert(BTreeNode *newNode)
{
  
  newNode->setParent(this);
  this->children[count] = newNode;
  this->count++;
  this->sort();
  this->changeKeyVals();

} // InternalNode::insert()



void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()

#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"


using namespace std;

/*GIVEN BY SEAN DAVIS*/

LeafNode::LeafNode(int LSize, InternalNode *p,

  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)

{

  values = new int[LSize];

}  // LeafNode()



/*GIVEN BY SEAN DAVIS*/
int LeafNode::getMinimum()const

{

  if(count > 0) 

    return values[0];

  else

    return 0;



} // LeafNode::getMinimum()



bool LeafNode::isNotFull() {

  return this->getCount() < leafSize;

}


void LeafNode::left_insert(int value) 

{
      int temp1 = this->getMinimum();
      this->values[0] = value;
      this->sort();
      ((LeafNode*)this->getLeftSibling())->insert(temp1);
}



void LeafNode::right_insert(int value) 

{

    if(values[count-1] < value)
    {
      ((LeafNode*)this->getRightSibling())->insert(value);
    } 

    else
     {

      int temp2 = this->values[count-1];

      this->values[count- 1] = value; 
      this->sort();


      ((LeafNode*)this->getRightSibling())->insert(temp2);
	      if(this->parent != NULL) 
      {
        this->parent->changeKeyVals();
      }
     }



}




LeafNode* LeafNode::insert(int value)

{
  if(this->isNotFull()) 
  {
    this->values[count] = value;
    this->count++;
    this->sort();
    if(this->parent != NULL) 
      {
        this->parent->changeKeyVals();
      }

    return NULL;

  } 


  if(this->getLeftSibling() != NULL && ((LeafNode*)this->getLeftSibling())->isNotFull()) 
  {
  
    this->left_insert(value);
    return NULL;

  } 


  if(this->getRightSibling() != NULL && ((LeafNode*)this->getRightSibling())->isNotFull()) 
  {
    this->right_insert(value);
    return NULL;

  } 

  else
  {

  return this->split(value);

  }

  return NULL;

}





/*GIVEN BY SEAN DAVIS*/
void LeafNode::print(Queue <BTreeNode*> &queue)

{

  cout << "Leaf: ";

  for (int i = 0; i < count; i++)

    cout << values[i] << ' ';

  cout << endl;

} // LeafNode::print()




void LeafNode::sort()

{

  for( int i = 0; i < count; i++ ) 
  {

    int min, temp;

    min = values[i];

    for (int j = i+1; j < count; j++ ) 
      {

      if( values[j] < min ) {

        min = values[j];

        temp = values[i];

        values[i] = values[j];

        values[j] = temp;

      }

    }

    }

}

LeafNode* LeafNode::split(int value) 

{
  LeafNode* new_leaf_node = new LeafNode(leafSize, this->parent, this, this->getRightSibling());
  
 if(this->getRightSibling() != NULL) 
 {
  this->getRightSibling()->setLeftSibling(new_leaf_node);
  }
  
  
  
  for(int i = this->getCount() - (this->getCount()/2); i < leafSize; i++) 
  {
  
    new_leaf_node->insert(this->values[i]);
    this->count--;
  
  }
  
  if(value < new_leaf_node->getMinimum()) 
  {
    this->insert(value);
  
    new_leaf_node->insert(this->values[count-1]);
  
    this->count--;
  } 

  else
  {
    new_leaf_node->insert(value);
  }
 
  this->setRightSibling(new_leaf_node);

  return new_leaf_node;
}

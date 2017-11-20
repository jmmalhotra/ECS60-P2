#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
  int *values;
public:
  LeafNode(int LSize, InternalNode *p, BTreeNode *left,
    BTreeNode *right);
  int getMinimum() const;
  LeafNode* insert(int value);
  void left_insert(int value);
  void right_insert(int value);
  void print(Queue <BTreeNode*> &queue);
  void sort();
  LeafNode* split(int value);
  bool isNotFull();
}; //LeafNode class

#endif

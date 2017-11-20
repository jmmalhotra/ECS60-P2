#ifndef InternalNodeH
  #define InternalNodeH

#include "BTreeNode.h"

class InternalNode:public BTreeNode
{
  int internalSize;
  BTreeNode **children;
  int *keys;
public:
  InternalNode(int ISize, int LSize, InternalNode *p,
    BTreeNode *left, BTreeNode *right);
  int getMinimum()const;
  InternalNode* insert(int value); // returns pointer to new InternalNode
    // if it splits else NULL
  void insert(BTreeNode *oldRoot, BTreeNode *node2); // if root splits use this
  void insert(BTreeNode *newNode); // from a sibling
  void print(Queue <BTreeNode*> &queue);
  bool isNotFull();
  void sort();
  InternalNode* split_function(BTreeNode* newNode);
  void changeKeyVals();
  BTreeNode* internalnode_insert_left(BTreeNode* ptr);
  BTreeNode* internalnode_insert_right(BTreeNode* ptr);
}; // InternalNode class

#endif



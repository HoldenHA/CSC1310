#if !defined (NULL)
#define NULL 0
#endif

#if !defined (AVLTREE_H)
#define AVLTREE_H

#include "Drawable.h"
#include "AVLTreeIterator.h"
#include "Line.h"

#include <iostream>
using namespace std;

template < class T >
class AVLTree : public Drawable
{

   private:
      AVLTreeNode<T>* root;

      bool avlFlag;
      int sz;

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);

      //Pre: tNode is node root is to be set to
      //Post: root node is set to tNode
      void setRootNode(AVLTreeNode<T>* tNode);

      //Pre: n/a
      //Post: root node is returned
      AVLTreeNode<T>* getRootNode();

      //Pre: height of tNode is desired
      //Post: height of tNode is returned, calculated through recursion
      int getHeight(AVLTreeNode<T>* tNode);

      //Pre: balance of tNode is desired
      //Post: balance of tNode is returned calculated using heigth(tNode->left) and heigth(tNode->right)
      int isBalanced(AVLTreeNode<T>* tNode);

      //Pre: balance factors of tNode need to be checked
      //Post: true if tNode is LEFT/RIGHT_HEAVY or BALANCED false if tNode is LEFT/RIGHT_UNBALANCED
      bool checkBalanceFactors(AVLTreeNode<T>* tNode);

      //Pre: tNode needs to be destroyed
      //Post: tNode and it's children are deleted
      void destroyItem(AVLTreeNode<T>* tNode);

      //Pre: entire AVLTree is to be destroyed
      //Post: entire AVLTree is deleted by deleting root node
      void destroy();

      //Pre: item needs to be inserted into tNode
      //Post: item is inserted into tNode at the proper location, and tNode then balances itself
      AVLTreeNode<T>* insertItem(AVLTreeNode<T>* tNode, T* item);

      //Pre: tNode needs to be rotated left
      //Post: tNode is rotated left and all of it's subtrees are placed correctly
      AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* tNode);

      //Pre: tNode needs to be rotated right to balance
      //Post: tNode is rotated right and all of it's subtrees are placed correctly
      AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* tNode);

      //Pre: tNode needs to be rotated left then right to balance
      //Post: tNode is rotated left and then right: all of it's subtrees are placed correctly; balance factors are updated
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode);

      //Pre: tNode needs to be roated right then left to balance
      //Post:tNode is rotated right and then left: all of it's subtrees are placed correctly; balance factors are updated
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode);

      //Pre: tNode need to be rotated once to the left
      //Post: tNode is rotated to the left once using rotateLeft and it's balanced factors are updated
      AVLTreeNode<T>* SL(AVLTreeNode<T>* tNode);

      //Pre: tNode need to be rotated once to the right
      //Post: tNode is rotated to the right once using rotateRight and it's balance factors are updated
      AVLTreeNode<T>* SR(AVLTreeNode<T>* tNode);

      //Pre: tNode has had a node added to it's left subtree and needs to rebalance
      //Post: tNode is rebalanced using rotations; balance factors are updated
      AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode);

      //Pre: tNode has had a node added to it's right subtree and needs to rebalance
      //Post: tNode is rebalanced using rotations; balance factors are updated
      AVLTreeNode<T>* avlFixAddRight(AVLTreeNode<T>* tNode);

      virtual void drawRec(AVLTreeNode<T>* tNode, wxDC&  dc, Line* line, int x_parent, int x_curr, int y_curr);

   public:
     //Pre: n/a
     //Post: AVLTree object is created
      AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));

      //Pre: n/a
      //Post: AVLTree object is deleted
      ~AVLTree();

      //Pre: n/a
      //Post: size of AVLTree is returned
      int size();

      //Pre: item is to be inserted into AVLTree
      //Post: item is inserted into AVLTree and balances itself
      void insert(T* item);

      //Pre: sk is the key for an item in AVLTree
      //Post: item with key sk is returned
      T* retrieve(String* sk);

      //Pre: n/a
      //Post: true if sz = 0; else false
      bool isEmpty();

      //Pre: n/a
      //Post: item at root node is returned
      T* getRootItem();

      //Pre: n/a
      //Post: AVLTreeIterator object created using AVLTree is returned
      AVLTreeIterator<T>* iterator();

      //Pre: n/a
      //Post: height of AVLTree is returned
      int getHeight();

      //Pre: n/a
      //Post: true if root->left->height = root->right->height; else false
      bool isBalanced();

      //Pre: n/a
      //Post: true if root->balanceFactor = RIGHT/LEFT_HEAVY || = BALANCED; else false
      bool checkBalanceFactors();

      void draw(wxDC&  dc, int width, int height);
      void mouseClicked(int x, int y);

};

template < class T >
AVLTree<T>::AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
  root = NULL;
  sz = 0;
  avlFlag = false;

  compare_items = comp_items;
  compare_keys = comp_keys;
}

template < class T >
AVLTree<T>::~AVLTree()
{
  destroy();
}

template < class T >
int AVLTree<T>::size()
{
  return sz;
}

template < class T >
void AVLTree<T>::insert(T* item)
{
  root = insertItem(root, item);
}

template < class T >
T* AVLTree<T>::retrieve(String* sk)
{
  AVLTreeNode<T>* tNode = getRootNode();

  while (tNode != NULL)
  {
    T* item = tNode->getItem();
    int comp = (*compare_keys) (sk, item);

    if(comp == 0)
    {
      return item;
    }
    else if(comp < 0)
    {
      tNode = tNode->getLeft();
    }
    else
    {
      tNode = tNode->getRight();
    }
  }

  return NULL;
}

template < class T >
bool AVLTree<T>::isEmpty()
{
  sz == 0;
}

template < class T >
T* AVLTree<T>::getRootItem()
{
  T* item = root->getItem();
  return item;
}

template < class T >
AVLTreeIterator<T>* AVLTree<T>::iterator()
{
  return new AVLTreeIterator<T>(root);
}

template < class T >
int AVLTree<T>::getHeight()
{
  return getHeight(root);
}

template < class T >
bool AVLTree<T>::isBalanced()
{
   int bal = isBalanced(getRootNode());
   if (bal == -1)
   {
      return false;
   }
   return true;
}

template < class T >
bool AVLTree<T>::checkBalanceFactors()
{
  return checkBalanceFactors(root);
}

template < class T >
void AVLTree<T>::setRootNode(AVLTreeNode<T>* tNode)
{
  root = tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::getRootNode()
{
  return root;
}

template < class T >
int AVLTree<T>::getHeight(AVLTreeNode<T>* tNode)
{
  if(tNode == NULL)
  {
    return 0;
  }

  int leftHeight = getHeight(tNode->getLeft());
  int rightHeight = getHeight(tNode->getRight());

  if(leftHeight >= rightHeight)
  {
    return leftHeight + 1;
  }
  else
  {
    return rightHeight + 1;
  }
}

template < class T >
int AVLTree<T>::isBalanced(AVLTreeNode<T>* tNode)
{
  if(tNode == NULL)
  {
    return true;
  }

  int balance = -1;
  AVLTreeNode<T>* left = tNode->getLeft();
  AVLTreeNode<T>* right = tNode->getRight();

  if (left_height != -1  &&  right_height != -1)
  {
      int bal = left_height - right_height;
      if (bal < 0) bal = bal * -1;
      if (bal <= 1)
      {
          if (left_height >= right_height)
          {
              balance = left_height + 1;
          }
          else
          {
              balance = right_height + 1;
          }
      }
   }
   return balance;
}

template < class T >
bool AVLTree<T>::checkBalanceFactors(AVLTreeNode<T>* tNode)
{
  AVL bal= tNode->getBalanceFactor();

  if (bal == BALANCED || bal == LEFT_HEAVY || bal == RIGHT_HEAVY)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template < class T >
void AVLTree<T>::destroyItem(AVLTreeNode<T>* tNode)
{
  if(tNode != NULL)
  {
    destroyItem(tNode->getLeft());
    destroyItem(tNode->getRight());
    delete tNode;
  }
}

template < class T >
void AVLTree<T>::destroy()
{
  destroyItem(root);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::insertItem(AVLTreeNode<T>* tNode, T* item)
{
  if(tNode == NULL)
  {
    sz++;
    avlFlag = true;
    return new AVLTreeNode<T>(item);
  }

  T* comp_item = tNode->getItem();
  int comp = (*compare_items) (item, comp_item);

  if(comp == 0)
  {
    return tNode;
  }
  else if(comp < 0)
  {
    tNode->setLeft(insertItem(tNode->getLeft(), item));
    return avlFixAddLeft(tNode);
  }
  else
  {
    tNode->setRight(insertItem(tNode->getRight(), item));
    return avlFixAddRight(tNode);
  }
}


template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* right = tNode->getRight();
   AVLTreeNode<T>* rightLeft = right->getLeft();
   right->setLeft(tNode);
   tNode->setRight(rightLeft);

   return right;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* left = tNode->getLeft();
   AVLTreeNode<T>* leftRight = left->getRight();
   left->setRight(tNode);
   tNode->setLeft(leftRight);

   return left;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* left = tNode->getLeft();
   AVLTreeNode<T>* leftRight = left->getRight();
   AVL leftRight_bal= leftRight->getBalanceFactor();

   if (leftRight_bal == BALANCED)
   {
      left->setBalanceFactor(BALANCED);
      leftRight->setBalanceFactor(BALANCED);
      tNode->setBalanceFactor(BALANCED);

      tNode->setLeft(rotateLeft(left));

      return rotateRight(tNode);
   }
   else if (leftRight_bal == LEFT_HEAVY)
   {
      left->setBalanceFactor(BALANCED);
      leftRight->setBalanceFactor(BALANCED);
      tNode->setBalanceFactor(RIGHT_HEAVY);

      tNode->setLeft(rotateLeft(left));

      return rotateRight(tNode);
   }
   else
   {
      left->setBalanceFactor(LEFT_HEAVY);
      leftRight->setBalanceFactor(BALANCED);
      tNode->setBalanceFactor(BALANCED);

      tNode->setLeft(rotateLeft(left));

      return rotateRight(tNode);
   }
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* right = tNode->getRight();
   AVLTreeNode<T>* rightLeft = right->getLeft();
   AVL rightLeft_bal = rightLeft->getBalanceFactor();

   if (rightLeft_bal == BALANCED)
   {
      right->setBalanceFactor(BALANCED);
      rightLeft->setBalanceFactor(BALANCED);
      tNode->setBalanceFactor(BALANCED);

      tNode->setRight(rotateRight(right));

      return rotateLeft(tNode);
   }
   else if (rightLeft_bal == RIGHT_HEAVY)
   {
      right->setBalanceFactor(BALANCED);
      rightLeft->setBalanceFactor(BALANCED);
      tNode->setBalanceFactor(LEFT_HEAVY);

      tNode->setRight(rotateRight(right));

      return rotateLeft(tNode);
   }
   else
   {
      right->setBalanceFactor(RIGHT_HEAVY);
      rightLeft->setBalanceFactor(BALANCED);
      tNode->setBalanceFactor(BALANCED);

      tNode->setRight(rotateRight(right));

      return rotateLeft(tNode);
   }
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::SL(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* right = tNode->getRight();
   right->setBalanceFactor(BALANCED);
   tNode->setBalanceFactor(BALANCED);

   return rotateLeft(tNode);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::SR(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* left = tNode->getLeft();
   left->setBalanceFactor(BALANCED);
   tNode->setBalanceFactor(BALANCED);

   return rotateRight(tNode);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddLeft(AVLTreeNode<T>* tNode)
{
   if (avlFlag)
   {
      tNode->insertLeft();
      AVL bal = tNode->getBalanceFactor();

      if (bal == BALANCED)
      {
         avlFlag = false;
      }
      else if (bal == LEFT_UNBALANCED)
      {
         AVLTreeNode<T>* left= tNode->getLeft();
         AVL left_bal = left->getBalanceFactor();

         if (left_bal == LEFT_HEAVY)
         {
            avlFlag = false;
            return SR(tNode);
         }
         else
         {
            avlFlag = false;
            return DLR(tNode);
         }
      }
   }

   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
   if (avlFlag)
   {
      tNode->insertRight();
      AVL bal = tNode->getBalanceFactor();

      if (bal == BALANCED)
      {
         avlFlag = false;
      }
      else if (bal == RIGHT_UNBALANCED)
      {
         AVLTreeNode<T>* right = tNode->getRight();
         AVL right_bal = right->getBalanceFactor();

         if (right_bal == RIGHT_HEAVY)
         {
            avlFlag = false;
            return SL(tNode);
         }
         else
         {
            avlFlag = false;
            return DRL(tNode);
         }
      }
   }

   return tNode;
}


//the below methods have been completed for you

template < class T >
void AVLTree<T>::draw(wxDC&  dc, int width, int height)
{
	Line line(new Color(0, 0, 0), 5.0);
	drawRec(getRootNode(), dc, &line, width, width/2, 20);
}

template < class T >
void AVLTree<T>::drawRec(AVLTreeNode<T>* tNode, wxDC& dc, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(dc, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), dc, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), dc, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(dc, x_curr, y_curr);
   }
}

template < class T >
void AVLTree<T>::mouseClicked(int x, int y) {}

#endif

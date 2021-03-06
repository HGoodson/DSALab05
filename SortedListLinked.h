#if !defined (SORTEDLISTLINKED_H)
#define SORTEDLISTLINKED_H

#include "NextNode.h"
#include "ListLinkedIterator.h"

#include <iostream>
using namespace std;

template < class T >
class SortedListLinked
{

   private:
      NextNode<T>* head;
      int sze;

      NextNode<T>** find(T* item);

      //this is how to declare a function pointer using templates
      int (*compare_items) (T* item_1, T* item_2);

   public:
      //this is how to accept a function pointer as a parameter
      SortedListLinked(int (*comp_items) (T* item_1, T* item_2));
      ~SortedListLinked();
      bool isEmpty();
      int size(); 
      void add(T* item);
      void remove(T* item);  //normally, we would use void remove(String* search_key) here
      T* get(int index);     //normally, we would use T* get(String* search_key)
      ListLinkedIterator<T>* iterator();

};

template < class T >
SortedListLinked<T>::SortedListLinked(int (*comp_items) (T* item_1, T* item_2))
{
   head = NULL;
   sze = 0;

   //store the function pointer
   compare_items = comp_items;
}

//the destructor is complex for this class
template < class T >
SortedListLinked<T>::~SortedListLinked()
{
   if (head != NULL)
   {
      NextNode<T>* curr = head;
      NextNode<T>* next = head->getNext();

      while (next != NULL)
      {
         delete curr;
         curr = next;
         next = curr->getNext();
      }

      head = NULL;
      delete curr; 
   }
}

template < class T >
bool SortedListLinked<T>::isEmpty()
{
   return sze == 0;
}

template < class T >
int SortedListLinked<T>::size()
{
   return sze;
}

template < class T >
T* SortedListLinked<T>::get(int index)
{
   if (index < 1 || index > sze)
   {
      return NULL;
   }

   int loc = 1;
   NextNode<T>* curr = head;

   while (loc < index)
   {
      curr = curr->getNext();
      loc++;
   }

   return curr->getItem();
}

template < class T >
NextNode<T>** SortedListLinked<T>::find(T* item)
{
   NextNode<T>* prev = NULL;
   NextNode<T>* curr = head;

   //DO THIS
   //loop to find the correct location to insert/remove item

   T* item_2 = (curr->getItem());

  cout << "item_2 made" << endl;

   while(curr != NULL)
   {
    //cout << "before compare" << endl;

    int compare = (*compare_items) (item, item_2);    

   //cout << "compare computed" << endl;

    if(compare > 0)
    {
   //cout << "inside if loop" << endl;
     prev = curr;
    //if(curr == NULL) cout << "curr = NULL" << endl; 
    //cout << "curr != NULL" << endl;  
     curr = curr->getNext();
   if(curr==NULL) break; 
   //cout << "curr->getNext() == NULL" << endl;
     item_2 = curr->getItem();
  //cout << "after item_2" << endl;
      }

     else break;

   //cout << "compare function done" << endl;

     }


   //could simply return prev and compute curr, but prev might be null
   //this way results in somewhat simpler code in add and remove
   NextNode<T>** nodes = new NextNode<T>*[2];
   nodes[0] = prev;
   nodes[1] = curr;

   return nodes;
}

template < class T >
void SortedListLinked<T>::add(T* item)
{
   NextNode<T>* node = new NextNode<T>(item);
 cout << "Node created" << endl;

   //special case: adding to an empty list
   if (sze == 0)
   {
      head = node;
      sze++;
      return;
   }

   NextNode<T>** nodes = find(item);
   NextNode<T>* prev = nodes[0];
   NextNode<T>* curr = nodes[1];
   delete[] nodes;

   //cout << "nodes created" << endl;

   //DO THIS
   //adding to the top of the list (check prev)
   if (prev == NULL)
   { cout << "6" << endl;
     head = node;
     node->setNext(curr);
    item->displayCD();
   }
   else    //general add
   {
    cout << "general add" << endl;
    item->displayCD();
     prev->setNext(node);
     node->setNext(curr);

   }
   cout << "post add" << endl;
   sze++;
}

template < class T >
void SortedListLinked<T>::remove(T* item)
{
   //special case: removing from an empty list
   if (sze == 0)
   {
      return;  //nothing to delete
   }

   NextNode<T>** nodes = find(item);
   NextNode<T>* prev = nodes[0];
   NextNode<T>* curr = nodes[1];
   delete[] nodes;

   //make sure that the item to be removed is actually in the list
   //if curr has run off of the end of the list, item is not there
   //if item and curr's item aren't equal, item is not there

   if (curr == NULL)
   {
      return;  //item not present
   }

   //this is how to use the function pointer
   int compare = (*compare_items) (item, curr->getItem());

   //determine whether the item to be removed is present
   if (compare != 0)
   {
      return;  //item not present
   }

   //DO THIS
   //removing the top item (check prev)
   if (prev == NULL)
   {
     //curr = head;      
     head = curr->getNext();

   }
   else  //general remove
   {
     //next = curr->getNext();
     //if(curr->getNext() == NULL) break;

     prev->setNext(curr->getNext());

   }

   delete curr;
   sze--;
}

template < class T >
ListLinkedIterator<T>* SortedListLinked<T>::iterator()
{
   return new ListLinkedIterator<T>(head);
}

#endif

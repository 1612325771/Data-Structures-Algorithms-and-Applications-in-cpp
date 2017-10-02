
// circular linked list with head node
// Reverse added

#ifndef HCircular_
#define HCircular_

#include <iostream.h>
#include "cnode.h"
#include "xcept.h"

template<class T>
class HCircular {
   public:
      HCircular() {head = new ChainNode<T>;
                  head->link = head;}
      ~HCircular();
      bool IsEmpty() const {return head->link == head;}
      int Length() const; 
      bool Find(int k, T& x) const; 
      int Search(const T& x) const; 
      HCircular<T>& Delete(int k, T& x); 
      HCircular<T>& Insert(int k, const T& x);
      void Output(ostream& out) const;
      HCircular<T>& Reverse();
   private:
      ChainNode<T> *head;  // pointer to head node
};

template<class T>
HCircular<T>::~HCircular()
{// HCircular destructor. Delete all nodes.
   // delete all nodes
   ChainNode<T> *current = head->link,
                           // current node
                *next;     // next node
   while (current != head) {
      next = current->link;
      delete current;
      current = next;
      }
   delete head;
}

template<class T>
int HCircular<T>::Length() const
{// Return the number of elements in the list.

   // count nodes
   ChainNode<T> *current = head->link;
   int len = 0;
   while (current != head) {
     len++;
     current = current->link;
     }
   return len;
}

template<class T>
bool HCircular<T>::Find(int k, T& x) const
{// Set x to the k'th element in the list.
 // Return false if no k'th; return true otherwise.
   if (k < 1 || head->link == head) return false;

   ChainNode<T> *current = head->link;
   int index = 1;  // index of current
   while (index < k && current != head) {
      // move to next node
      current = current->link;
      index++;
      }
   if (index == k) {x = current->data;
                    return true;}
   return false; // no k'th element
}

template<class T>
int HCircular<T>::Search(const T& x) const
{// Locate x.  Return position of x if found.
 // Return 0 if x not in the chain.

   // put x in head node to terminate search
   head->data = x;

   // examine nodes
   ChainNode<T> *current = head->link;
   int index = 1;  // index of current
   while (current->data != x) {
      // move to next node
      current = current->link;
      index++;
      }
   if (current == head) return 0;
   return index;
}

template<class T>
HCircular<T>& HCircular<T>::Delete(int k, T& x)
{// Set x to the k'th element and delete it.
 // Throw OutOfBounds exception if no k'th element.
   if (k < 1 || head->link == head)
      throw OutOfBounds(); // no k'th
   
   // q will eventually point to k-1'st node
   ChainNode<T> *q = head;
   int index = 0;  // index of q

   // move q to k-1'st node
   for (; index < k - 1
          && q->link != head; index++)
      q = q->link;
   if (index != k - 1 || q->link == head)
      throw OutOfBounds(); // no k'th

   ChainNode<T> *p = q->link; // k'th
   q->link = p->link; // remove

   // save k'th element and free node p
   x = p->data;
   delete p;

   return *this;
}

template<class T>
HCircular<T>& HCircular<T>::Insert(int k, const T& x)
{// Insert x after the k'th element.
 // Throw OutOfBounds exception if no k'th element.
 // Pass NoMem exception if inadequate space.
   if (k < 0) throw OutOfBounds();

   // p will eventually point to k'th node
   ChainNode<T> *p = head;
   int index = 0;
   for (; index < k && p->link != head;
          index++)  // move p to k'th
      p = p->link;
   if (index != k) throw OutOfBounds(); // no k'th

   // insert
   ChainNode<T> *y = new ChainNode<T>;
   y->data = x;
   // insert after p
   y->link = p->link;
   p->link = y;

   return *this;
}

template<class T>
void HCircular<T>::Output(ostream& out) const
{// Insert the chain elements into the stream out.
   ChainNode<T> *current;
   for (current = head->link; current != head;
                         current = current->link)
      out << current->data << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const HCircular<T>& x)
   {x.Output(out); return out;}

template<class T>
HCircular<T>& HCircular<T>::Reverse()
{// In-pace reversal of the circular list.
   ChainNode<T> *prev = head,  // previous node
                *current = head->link,
                               // current node
                *next;         // next node      
   while (current != head) {
      // change pointer direction
      next = current->link;
      current->link = prev;

      // move to next node
      prev = current;
      current = next;
      }

   // reverse pointer in head node
   head->link = prev;

   return *this;
}

#endif

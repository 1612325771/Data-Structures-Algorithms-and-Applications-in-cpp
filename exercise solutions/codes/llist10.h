

// formula-based linear list
// formla used is
// location(i) = (location(1) + i -1) % MaxSize
// linear list with merge function added

#ifndef LinearList_
#define LinearList_
#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"

template<class T>
class LinearList {
   public:
      LinearList(int MaxListSize = 10); // constructor
      ~LinearList() {delete [] element;} // destructor
      bool IsEmpty() const {return first == -1;}
      int Length() const
          {if (first == -1) return 0;
           else return (MaxSize+last-first) % MaxSize + 1;}
      bool Find(int k, T& x) const;
         // return the k'th element of list in x
      int Search(const T& x) const;
         // return position of x
      LinearList<T>& Delete(int k, T& x);
         // delete k'th element and return in x
      LinearList<T>& Insert(int k, const T& x);
         // insert x just after k'th element
      LinearList<T>& Merge(const LinearList<T>& A, 
                     const LinearList<T>& B);
      void Output(ostream& out) const;
   private:
      int first;  // location of first element
      int last;   // location of last element
      int MaxSize;
      T *element; // dynamic 1D array
};

template<class T>
LinearList<T>::LinearList(int MaxListSize)
{// Constructor for formula-based linear list.
   MaxSize = MaxListSize;
   element = new T[MaxSize];
   first = -1;  // empty list
}

template<class T>
bool LinearList<T>::Find(int k, T& x) const
{// Set x to the k'th element of the list.
 // Return false if no k'th; true otherwise.
   if (k < 1 || k > Length()) return false; // no k'th
   x = element[(first+k-1) % MaxSize];
   return true;
}

template<class T>
int LinearList<T>::Search(const T& x) const
{// Locate x.  Return position of x if found.
 // Return 0 if x not in list.
   int len = Length();
   for (int i = 1; i <= len; i++)
      if (element[(first+i-1) % MaxSize] == x) return i;
   return 0;
 }

template<class T>
LinearList<T>& LinearList<T>::Delete(int k, T& x)
{// Set x to the k'th element and delete it.
 // Throw OutOfBounds exception if no k'th element.
   if (Find(k, x)) {
      int len = Length();
      // is list empty after the deletion?
      if (len == 1) {// list becomes empty
                     first = -1;
                     return *this;}

      // determine which side has fewer elements
      // and shift the smaller number of elements
      if (k <= (len+1)/2) {// shift elements k-1 ... 1
         for (int i = k-1; i >= 1; i--)
             element[(first+i) % MaxSize]
                = element[(first+i-1) % MaxSize];
         first = (first+1) % MaxSize;
         }
      else {// shift elements k+1 ... len
         for (int i = k+1; i <= len; i++)
             element[(first+i-2) % MaxSize]
                = element[(first+i-1) % MaxSize];
         last = (MaxSize+last-1) % MaxSize;
         }
      return *this;
      }
   else throw OutOfBounds();
}

template<class T>
LinearList<T>& LinearList<T>::Insert(int k, const T& x)
{// Insert x after the k'th element.
 // Throw OutOfBounds exception if no k'th element.
 // Throw NoMem exception if list is already full.
   int len = Length();
   if (k < 0 || k > len) throw OutOfBounds();
   if (len == MaxSize) throw NoMem();

   // is the list empty?
   if (len == 0) {// insert into empty list
                  first = last = 0;
                  element[0] = x;
                  return *this;}

   // insert into a nonempty list
   // create space for new element
   if (k <= len/2) {// shift elements 1 through k
         for (int i = 1; i <= k; i++)
             element[(first+i-2) % MaxSize]
                = element[(first+i-1) % MaxSize];
         first = (MaxSize+first-1) % MaxSize;
         }
    else {// shift elements len ... k+1
          for (int i = len; i >= k+1; i--)
              element[(first+i) % MaxSize]
                 = element[(first+i-1) % MaxSize];
          last = (last+1) % MaxSize;
          }
          
   // insert as k+1'st element
   element[(first+k) % MaxSize] = x;

   return *this;
}

template<class T>
void LinearList<T>::Output(ostream& out) const
{// Put the list into the stream out.
   int len = Length();
   for (int i = 1; i <= len; i++)
      out << element[(first+i-1) % MaxSize] << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const LinearList<T>& x)
   {x.Output(out); return out;}

template <class T>
LinearList<T>& LinearList<T>::
    Merge(const LinearList<T>& A, const LinearList<T>& B)
{// Merge the two sorted lists A and B
   int al = A.Length();
   int bl = B.Length();
   if (al + bl > MaxSize) throw NoMem();
               // inadequate space for result

   int ca = A.first; // cursor for A
   int cb = B.first; // cursor for B
   int ct = 0;       // cursor for *this

   // we shall create result in element[0:al + bl - 1]
   first = 0;
   last = al + bl - 1;

   // merge from A and B to *this until
   // either A or B is exhausted
   int na = 0;  // number merged from A
   int nb = 0;  // number merged from B
   while ((na <= al) && (nb <= bl))
      if (A.element[ca] <= B.element[cb]) {
         element[ct++] = A.element[ca];
         ca = (ca + 1) % A.MaxSize;
         na++;
         }
      else {element[ct++] = B.element[cb];
            cb = (cb + 1) % B.MaxSize;
            nb++;
            }

   // take care of left overs
   if (na > al)  // A is finished
      for (int q = nb + 1; q <= bl; q++) {
         element[ct++] = B.element[cb];
         cb = (cb + 1) % B.MaxSize;
         }
   else for (int q = na + 1; q <= al; q++) {
           element[ct++] = A.element[q];
           ca = (ca + 1) % B.MaxSize;
           }

   return *this;
}

#endif

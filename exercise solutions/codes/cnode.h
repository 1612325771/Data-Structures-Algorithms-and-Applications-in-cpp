// file cnode.h

#ifndef ChainNode_
#define ChainNode_

template <class T> class Chain;
template <class T> class ChainIterator;
template <class T> class KeyedChain;
template <class T> class LinkedStack;
template <class T> class Circular;
template <class T> class CircularIterator;
template <class T> class HCircular;
template <class T> class HCircularIterator;

template <class T>
class ChainNode {
   friend Chain<T>;
   friend ChainIterator<T>;
   friend KeyedChain<T>;
   friend LinkedStack<T>;
   friend Circular<T>;
   friend CircularIterator<T>;
   friend HCircular<T>;
   friend HCircularIterator<T>;
   private:
      T data;
      ChainNode<T> *link;
};

#endif

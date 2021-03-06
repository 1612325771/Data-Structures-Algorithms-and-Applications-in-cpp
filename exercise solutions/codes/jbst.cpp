
#include <iostream.h>
#include "jbst.h"
class DataType {
   friend void main(void);
   friend IndexedBSTree<DataType,int>;
   friend ostream& operator<<(ostream& out, DataType x);
   public:
      operator int() const {return key;}
   private:
      int LeftSize;
      int key;
      char ID;
};

ostream& operator<<(ostream& out, DataType x)
{out << x.key << ' ' << x.ID << ' '
     << x.LeftSize << ' ';
 return out;}


void main(void)
{
   IndexedBSTree<DataType,int> y;
   DataType q;
   q.key = 5; q.ID = 'a';
   y.Insert(q);
   q.key = 6; q.ID = 'b';
   y.Insert(q);
   q.key = 4; q.ID = 'c';
   y.Insert(q);
   q.key = 8; q.ID = 'd';
   y.Insert(q);
   q.key = 7; q.ID = 'e';
   y.Insert(q);
   q.key = 2; q.ID = 'f';
   y.Insert(q);
   q.key = 3; q.ID = 'g';
   y.Insert(q);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();

   int n = 7; // size of tree
   for (int i = 1; i <= n; i++) {
      y.IndexedSearch(i,q);
      cout << "element " << i << " is " << q.key << ' ' << q.ID << endl;
      }

   DataType s;
   y.Delete(4,s);
   cout << "Deleted  " << s.key << ' ' << s.ID << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   y.IndexedDelete(4,s);
   cout << "Delete of fourth element suceeds ";
   cout << ' ' << s.key << ' ' << s.ID << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   y.IndexedDelete(4,s);
   cout << "Delete of fourth element succeeds ";
   cout << ' ' << s.key << ' ' << s.ID << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   y.IndexedDelete(3,s);
   cout << "Delete of third element succeeds ";
   cout << ' ' << s.key << ' ' << s.ID << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
}

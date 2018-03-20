#pragma once
template<class T>
struct Node
{
  T         Data;
  Node<T>  *pre;
  Node<T>  *next;
};

template<class T>
class List
{
private:
  int       len;
  Node<T>  *t;
  Node<T>  *pHead;
  Node<T>  *MakeNode();
  void      Free(Node<T> *pNode);
public:
            List();
           ~List();
  bool      Add(T Data);
  bool      Insert(T Data, int Index);
  bool      Delete(int Index);
  int       Search(T Data);
  void      OutPut();
};
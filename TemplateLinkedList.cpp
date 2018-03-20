// TemplateLinkedList.cpp : 定义控制台应用程序的入口点。
//
//模板类 template<class T>
// 析构函数
// 书写规范

#include "stdafx.h"
#include "User.h"
#include <iostream>
using namespace std;

template<class T>
List<T>::List()
{
  t = MakeNode(); 
  pHead = t; 
  len = 0; 
}

template<class T>
List<T>::~List()
{
  pHead = pHead->next;
  while(pHead != NULL)                                        // 遍历链表节点，
  {
    Node<T> *h = pHead;                                       // h指向第一个节点
    pHead = pHead->next;                                      
    Free(h); 
    len--; 
  }
}

template<class T>
Node<T>* List<T>::MakeNode()
{
  Node<T> *t = (Node<T> *)malloc(sizeof(Node<T>)); 
  return t; 
}

template<class T>
void List<T>::Free(Node<T> *pNode)
{
  if(pNode == NULL)
  {
    cout << "该指针已释放！" << endl; 
    return; 
  }
  free(pNode); 
  pNode = NULL; 
  if(pNode != NULL)
  {
    cout << "指针释放失败！" << endl; 
    return; 
  }
}

template<class T>
bool List<T>::Add(T Data)                                     // 新加链表
{
  Node<T> *pNode = MakeNode(); 
  if(pNode == NULL) 
    return false;                                             // 内存分配失败
  Node<T> *pFirst = pHead; 
  pNode->Data = Data; 
  if (len == 0)
  {
    pFirst->next = pNode; 
    pNode->pre = pFirst; 
    pNode->next = NULL; 
  }
  else
  {
    while(pFirst->next != NULL) 
      pFirst = pFirst->next; 
    pFirst->next = pNode; 
    pNode->pre = pFirst; 
    pNode->next = NULL; 
  }
  len++; 
  return true; 
}

template<class T>
bool List<T>::Insert(T Data, int Index)                       // 在指定位置插入节点
{
  Node<T> *pNode = MakeNode(); 
  pNode->Data = Data; 
  Node<T> *pFirst = pHead; 
  if(Index > len + 1 || Index < 0) 
    return false;                                             // 索引值不正确，结束
  if(Index == 1)                                              // 插入位置为链表头节点
  {
    pNode->next = pFirst->next; 
    pNode->pre = pFirst; 
    pFirst->next = pNode; 
  }
  else if(Index == (len + 1))                                 // 插入位置为链表末尾
  {
    for(int i = 1; i < Index; i++) 
      pFirst = pFirst->next; 
    pFirst->next = pNode; 
    pNode->pre = pFirst; 
    pNode->next = NULL; 
  }
  else                                                        // 插入位置为链表中间
  {
    for(int i = 0; i < Index; i++) 
      pFirst = pFirst->next; 
    pNode->pre = pFirst->pre; 
    pFirst->pre->next = pNode; 
    pNode->next = pFirst; 
    pFirst->pre = pNode; 
  }
  len++; 
  return true; 
}

template<class T>
bool List<T>::Delete(int Index)                               // 通过索引值删除指定节点
{
  if(Index > len || Index <= 0) 
    return false;                                             // 索引值不正确，删除失败返回
  Node<T> *pFirst = pHead; 
  for(int i = 0; i < Index; i++) 
    pFirst = pFirst->next;
  if(Index == len)                                            // 要删除的节点为最后一个
    pFirst->pre->next = NULL;                                 
  else
  {
    pFirst->pre->next = pFirst->next; 
    pFirst->next->pre = pFirst->pre; 
  }
  len--; 
  Free(pFirst); 
  return true; 
}

template<class T>
int List<T>::Search(T Data)                                   // 查找指定节点，并返回其位置
{
  int Flag = 1, flag = 0, i = 0;  
  Node<T>* pFirst = pHead->next; 
  for(; pFirst != NULL; pFirst = pFirst->next) 
  {
    if(pFirst->Data == Data) 
      return Flag; 
    flag++;
    Flag++;                                                   // Flag为位置，flag只用于判断是否查找到了
  }
  if(flag == len) 
    return 0;                                                 // 没有查找到，返回0
}

template<class T>
void List<T>::OutPut()
{
  Node<T> *pFirst = pHead; 
  while(pFirst->next != NULL)
  {
    pFirst = pFirst->next; 
    cout << pFirst->Data ; 
  }
  cout << endl; 
}

int main()
{
  int  Index; 
  char Data; 
  bool bResult = false; 
  List<char> *list = new List<char>; 
  cout << "请输入你需要添加的值：";                           // 添加测试
  do
  {
    cin >> Data; 
    bResult = list->Add(Data); 
  } while(cin.peek() != '\n');                                // 输入的字符不为换行
  list->OutPut(); 

  cout << "输入要删除的索引值:";                              // 删除测试
  cin >> Index; 
  bResult = list->Delete(Index); 
  list->OutPut(); 

  cout << "输入要插入的值:";                                  // 插入测试
  cin >> Data; 

  cout << "输入要插入值的索引:"; 
  cin >> Index; 
  bResult = list->Insert(Data, Index); 
  list->OutPut(); 

  cout << "输入要查找的值:";                                  // 查找测试
  cin >> Data; 
  cout << "查找到的值如下："; 
  int index = list->Search(Data);
  if(index == 0) 
    cout << endl << "没有找到该值！"; 
  else
    cout<<index;
  cout << endl; 
  delete list;
  return 0; 
}

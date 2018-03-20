// TemplateLinkedList.cpp : �������̨Ӧ�ó������ڵ㡣
//
//ģ���� template<class T>
// ��������
// ��д�淶

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
  while(pHead != NULL)                                        // ��������ڵ㣬
  {
    Node<T> *h = pHead;                                       // hָ���һ���ڵ�
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
    cout << "��ָ�����ͷţ�" << endl; 
    return; 
  }
  free(pNode); 
  pNode = NULL; 
  if(pNode != NULL)
  {
    cout << "ָ���ͷ�ʧ�ܣ�" << endl; 
    return; 
  }
}

template<class T>
bool List<T>::Add(T Data)                                     // �¼�����
{
  Node<T> *pNode = MakeNode(); 
  if(pNode == NULL) 
    return false;                                             // �ڴ����ʧ��
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
bool List<T>::Insert(T Data, int Index)                       // ��ָ��λ�ò���ڵ�
{
  Node<T> *pNode = MakeNode(); 
  pNode->Data = Data; 
  Node<T> *pFirst = pHead; 
  if(Index > len + 1 || Index < 0) 
    return false;                                             // ����ֵ����ȷ������
  if(Index == 1)                                              // ����λ��Ϊ����ͷ�ڵ�
  {
    pNode->next = pFirst->next; 
    pNode->pre = pFirst; 
    pFirst->next = pNode; 
  }
  else if(Index == (len + 1))                                 // ����λ��Ϊ����ĩβ
  {
    for(int i = 1; i < Index; i++) 
      pFirst = pFirst->next; 
    pFirst->next = pNode; 
    pNode->pre = pFirst; 
    pNode->next = NULL; 
  }
  else                                                        // ����λ��Ϊ�����м�
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
bool List<T>::Delete(int Index)                               // ͨ������ֵɾ��ָ���ڵ�
{
  if(Index > len || Index <= 0) 
    return false;                                             // ����ֵ����ȷ��ɾ��ʧ�ܷ���
  Node<T> *pFirst = pHead; 
  for(int i = 0; i < Index; i++) 
    pFirst = pFirst->next;
  if(Index == len)                                            // Ҫɾ���Ľڵ�Ϊ���һ��
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
int List<T>::Search(T Data)                                   // ����ָ���ڵ㣬��������λ��
{
  int Flag = 1, flag = 0, i = 0;  
  Node<T>* pFirst = pHead->next; 
  for(; pFirst != NULL; pFirst = pFirst->next) 
  {
    if(pFirst->Data == Data) 
      return Flag; 
    flag++;
    Flag++;                                                   // FlagΪλ�ã�flagֻ�����ж��Ƿ���ҵ���
  }
  if(flag == len) 
    return 0;                                                 // û�в��ҵ�������0
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
  cout << "����������Ҫ��ӵ�ֵ��";                           // ��Ӳ���
  do
  {
    cin >> Data; 
    bResult = list->Add(Data); 
  } while(cin.peek() != '\n');                                // ������ַ���Ϊ����
  list->OutPut(); 

  cout << "����Ҫɾ��������ֵ:";                              // ɾ������
  cin >> Index; 
  bResult = list->Delete(Index); 
  list->OutPut(); 

  cout << "����Ҫ�����ֵ:";                                  // �������
  cin >> Data; 

  cout << "����Ҫ����ֵ������:"; 
  cin >> Index; 
  bResult = list->Insert(Data, Index); 
  list->OutPut(); 

  cout << "����Ҫ���ҵ�ֵ:";                                  // ���Ҳ���
  cin >> Data; 
  cout << "���ҵ���ֵ���£�"; 
  int index = list->Search(Data);
  if(index == 0) 
    cout << endl << "û���ҵ���ֵ��"; 
  else
    cout<<index;
  cout << endl; 
  delete list;
  return 0; 
}

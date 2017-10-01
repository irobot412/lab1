

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "set.h"

symset uniteset(symset s1, symset s2)
{
	symset s;
	snode* p;
	
	s1 = s1->next;
	s2 = s2->next;
	
	s = p = (snode*) malloc(sizeof(snode));
	/*
		合并s1和s2两个链表中的元素到p中，从小到大
	*/
	while (s1 && s2)
	//当s1和s2中都有元素时
	{
		p->next = (snode*) malloc(sizeof(snode));
		p = p->next;
		if (s1->elem < s2->elem)
		{
			p->elem = s1->elem;
			s1 = s1->next;
		}
		else
		{
			p->elem = s2->elem;
			s2 = s2->next;
		}
	}

	while (s1)
	//当s1还有元素而s2的元素已经复制完了时
	{
		p->next = (snode*) malloc(sizeof(snode));
		p = p->next;
		p->elem = s1->elem;
		s1 = s1->next;
		
	}

	while (s2)
	//当s2还有元素而s1的元素已经复制完了时
	{
		p->next = (snode*) malloc(sizeof(snode));
		p = p->next;
		p->elem = s2->elem;
		s2 = s2->next;
	}

	p->next = NULL;

	return s;
} // uniteset

void setinsert(symset s, int elem)
//链表s已经从小到大排列好，将elem按大小顺序插入链表s中
{
	snode* p = s;
	snode* q;

	while (p->next && p->next->elem < elem)
	//如果s链表中还有元素并且小于特征值elem
	{
		p = p->next;
	}
	
	q = (snode*) malloc(sizeof(snode));
	q->elem = elem;
	q->next = p->next;
	p->next = q;
} // setinsert

symset createset(int elem, .../* SYM_NULL */)
//创建列表，依次插入elem和可变长参数列表里面的参数。其中，该列表的头元素将为空。即是从第二个结点开始插入元素。
{
	va_list list;
	symset s;

	s = (snode*) malloc(sizeof(snode));
	s->next = NULL;

	va_start(list, elem);//初始化list，list将指向elem之后的地址（即可变长参数列表在堆栈中的首地址）。
	while (elem)
	{
		setinsert(s, elem);
		elem = va_arg(list, int);
	}
	va_end(list);
	return s;
} // createset

void destroyset(symset s)
//销毁列表
{
	snode* p;

	while (s)
	{
		p = s;
		p->elem = -1000000;
		s = s->next;
		free(p);
	}
} // destroyset

int inset(int elem, symset s)
//查找元素elem是否已经在s中。
{
	s = s->next;
	while (s && s->elem < elem)
		s = s->next;

	if (s && s->elem == elem)
		return 1;
	else
		return 0;
} // inset

// EOF set.c

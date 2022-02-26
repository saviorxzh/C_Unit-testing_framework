/*************************************************************************
	> File Name: linklist.h
	> Author: xuzheheng
	> Mail: 
	> Created Time: 2021年08月24日 星期二 22时25分32秒
 ************************************************************************/

#ifndef _LINKLIST_H
#define _LINKLIST_H

#define offset(T, name) (long long)(&(((T *)(NULL))->name))
#define Head(p, T, name) (T *)((char *)(p) - offset(T, name))

struct LinkNode {
    struct LinkNode *next;
};

#endif

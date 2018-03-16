//
//  Node.h
//  HW2_MemoryManagement
//
//  Copyright © 2017년 2학기 System Programming. All rights reserved.
//
//  이름 : 구수연
//  학번 : 2014037756
//  학과 : 컴퓨터공학과
//

#ifndef _Node_h_
#define _Node_h_

typedef struct Node {
    Block item;
    struct Node *prev;
    struct Node *next;
} Node;

#endif 

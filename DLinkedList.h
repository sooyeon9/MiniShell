//
//  DLinkedList.h
//  HW2_MemoryManagement
//
//  Copyright © 2017년 2학기 System Programming. All rights reserved.
//
//  이름 : 구수연
//  학번 : 2014037756
//  학과 : 컴퓨터공학과
//

#ifndef _DLinkedList_H_
#define _DLinkedList_H_

#include <stdio.h>
#include <stdbool.h>
#include "Block.h"
#include "Node.h"

typedef struct DLinkedList {
    int size;
    struct Node *header;
    struct Node *trailer;
} DLinkedList;

void setHeaderInfo(DLinkedList *dl, Block info);
void setTrailerInfo(DLinkedList *dl, Block info);
bool isEmpty(DLinkedList *dl);
Node *getFirst(DLinkedList *dl);
Node *getLast(DLinkedList *dl);
void addFirst(DLinkedList *dl, Node *newNode);
void addLast(DLinkedList *dl, Node *newNode);
void removeLast(DLinkedList *dl);
void removeFirst(DLinkedList *dl);
void addAfter(DLinkedList *dl, Node *node, Node *newNode);
void addBefore(Node *node, Node *newNode);
void removeNode(DLinkedList *dl, Node *node);

/*
 * set header information of dl
 */
void setHeaderInfo(DLinkedList *dl, Block info) {
    dl->header->item = info;
}

/*
 * set trailer information of dl
 */
void setTrailerInfo(DLinkedList *dl, Block info) {
    dl->trailer->item = info;
}

/*
 * if empty, return true;
 * if not empty, return false;
 * bool is from <stdbool.h>
 */
bool isEmpty(DLinkedList *dl) {
    /// write your code..
    if (dl->size==0 || dl->header==NULL)
		return true;
	else
		return false;
}

/*
 * return dl's size
 */
int getSize(DLinkedList *dl) {
    return dl->size;
}

/*
 * return dl's first Node
 */
Node *getFirst(DLinkedList *dl) {
    /// write your code..
    Node *node = (Node*)malloc(sizeof(Node));
    node = dl->header;
    return node;
}

/*
 * return dl's last Node
 */
Node *getLast(DLinkedList *dl) {
    /// write your code..
    Node *node = (Node*)malloc(sizeof(Node));
    node = dl->trailer;
    return node;
}

/*
 * add newNode to dl's first position
 */
void addFirst(DLinkedList *dl, Node *newNode) {
    /// write your code..
    if(isEmpty(dl)){
		dl->trailer = newNode;
		dl->header = newNode;
	} else {
		dl->header->prev = newNode;
		newNode->next = dl->header;
		dl->header = newNode;
	}
	dl->size++;
}

/*
 * add newNode to dl's last position
 */
void addLast(DLinkedList *dl, Node *newNode) {
    /// write your code..
    if(isEmpty(dl)){
		dl->trailer = newNode;
		dl->header = newNode;
	} else {
		dl->trailer->next = newNode;
		newNode->prev = dl->trailer;
		dl->trailer = newNode;
	}
	dl->size++;
}

/*
 * remove dl's first node
 */
void removeFirst(DLinkedList *dl) {
    /// write your code..

    if(isEmpty(dl)){
		printf("error --- list is empty!\n");
		return ;
	} else if(dl->size == 1) {
		free(dl->header);
	} else {
		Node *temp = (Node*)malloc(sizeof(Node));
		temp = dl->header;
		dl->header = dl->header->next;
		dl->header->prev = NULL;
		free(temp);
	}
	
	dl->size--;
}

/*
 * remove dl's last node
 */
void removeLast(DLinkedList *dl) {
    /// write your code..
   
    if(isEmpty(dl)){
		printf("error --- list is empty!\n");
		return ;
	} else if(dl->size == 1) {
		free(dl->header);
	} else {
		Node *temp = (Node*)malloc(sizeof(Node));
		temp = dl->trailer;
		dl->trailer = dl->trailer->prev;
		dl->trailer->next = NULL;
		free(temp);
	}
	
	dl->size--;
}

/*
 * add newNode after the node
 */
void addAfter(DLinkedList *dl, Node *node, Node *newNode) {
    /// write your code..
    Node *New;
    Node *right;
    
    New = (Node*)malloc(sizeof(Node));
    *New = *newNode;
    right = node->next;
    
    New->next = right;
	New->prev = node;
	node->next = New;
	if(right)
		right->prev = New;
	
	dl->size++;
}

/*
 * add newNode before the node
 */
void addBefore(Node *node, Node *newNode) {
    /// write your code..
    Node *New;
    Node *left;
    
    New = (Node*)malloc(sizeof(Node));
    *New = *newNode;
    left = node->prev;
    
    New->prev = left;
	New->next = node;
	node->prev = New;
	left->next = New;
}

/*
 * remove the node
 */
void removeNode(DLinkedList *dl, Node *node) {
    /// write your code..
    Node *left, *right;
    
    if(dl->header == node)
		removeFirst(dl);
	else if(dl->trailer == node)
		removeLast(dl);
    else {
		left = node->prev;
		right = node->next;
    
		if(left!=NULL){
			left->next = right;
			if(right!=NULL)
				right->prev = left;
			free(node);
			node = NULL;
		}
		dl->size--;
    }
}


Node *findVaildNode(DLinkedList *dl){
	Node *compare = (Node*)malloc(sizeof(Node));
	Node *node = (Node*)malloc(sizeof(Node));
	compare = dl->header;
	int i, max=-1;;
	for(i=0; i<(dl->size); i++){
		if((compare->item.size)>=max){
			max = (compare->item.size);
			node = compare;
			compare = compare->next;
		} else {
			compare = compare->next;
		}
	}

	return node;
}


#endif

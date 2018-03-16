//
//  MemoryManager.c
//  HW2_MemoryManagement
//
//  Copyright © 2017년 2학기 System Programming. All rights reserved.
//
//  이름 : 구수연
//  학번 : 2014037756
//  학과 : 컴퓨터공학과
//

#ifndef _MemoryManager_H_
#define _MemoryManager_H_

#include <stdio.h>
#include "DLinkedList.h"

Block *m_alloc(int size);
void m_free(Block block);
void getHeap(DLinkedList *heap);
void merge();

DLinkedList *g_heap;

Block *m_alloc(int size) {
    // write your code..
    Node *vaildNode = (Node*)malloc(sizeof(Node));
    Block *newBlock = (Block*)malloc(sizeof(Block));
    newBlock->size = size;
    
    if(size<=0 || size>=(g_heap->trailer->item.end)){
		return NULL;
    } else if(g_heap->size==1) { 
		newBlock->start = g_heap->trailer->item.start;
		g_heap->trailer->item.size = g_heap->trailer->item.size - size;
		g_heap->trailer->item.start = g_heap->trailer->item.start + size;
		newBlock->end = newBlock->start+size -1;
	} else { 
		vaildNode = findVaildNode(g_heap);
		newBlock->start = vaildNode->item.start;
		vaildNode->item.size = vaildNode->item.size - size;
		vaildNode->item.start = vaildNode->item.start + size;
		newBlock->end = newBlock->start + size-1;
	}
	
    return newBlock;
}

void m_free(Block block) {
    // write your code..
    int i;
    Node *newNode = (Node*)malloc(sizeof(Node));
    Node *compare = (Node*)malloc(sizeof(Node));
    newNode->item = block;
    newNode->next = NULL;
    newNode->prev = NULL;
    compare = g_heap->header;

	for(i=0; i<g_heap->size; i++){
		if(i==0){
			if(compare->item.start>block.end){
				addFirst(g_heap,newNode);
				block.size=0;
				break;
			}
		}
		if(compare->item.end<block.start && block.end<compare->next->item.start){
			addAfter(g_heap,compare,newNode);
			block.size=0;
			break;
		}
		compare = compare->next;
	}
	
	merge();
}

void merge(){
	Node *compare = (Node*)malloc(sizeof(Node));
	compare = g_heap->header;
	
	while(compare->next != NULL){
		if(compare->item.end+1 == compare->next->item.start){
			compare->item.size += compare->next->item.size;
			compare->item.end = compare->next->item.end;
			removeNode(g_heap,compare->next);
		}
		else 
			compare = compare->next;
	}
}



void getHeap(DLinkedList *heap) {
    Node *tmpNode = heap->header;
    printf("size: %d\n", heap->trailer->item.end+1);
    printf("Header] <-> ");
    
    while(tmpNode != NULL) {
        printf("[%d<-(%d)->%d] <-> ",
        tmpNode->item.start, tmpNode->item.size, tmpNode->item.end);
        tmpNode = tmpNode->next;
    }
    
    printf("[Trailer\n");
}

#endif

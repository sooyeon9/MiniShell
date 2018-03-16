//
//  main.c
//  HW2_MemoryManagement
//
//  Copyright © 2017년 2학기 System Programming. All rights reserved.
//
//  이름 : 구수연
//  학번 : 2014037756
//  학과 : 컴퓨터공학과
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "MemoryManager.h"

void initManager();

int main(int argc, const char * argv[]) {
	int a;
	Block b;
	
    int which = 0;
    int mallocSize;
    int heapSize;
    int freeIndex;
    Block *block;
    
    Block allocatedBlocks[100];
    int lastBlockIndex = -1;
    
    printf("====Memory Manager====\n");
    printf("Set heap size: ");
    scanf("%d", &heapSize);
    
    initManager(heapSize);
    
    do {
        printf("\n====================\n");
        getHeap(g_heap);
        printf("Choose a number to operate\n");
        printf("1. malloc\n");
        printf("2. free\n");
        printf("3. print allocated blocks\n");
        printf("or, exit\n");
        scanf("%d", &which);
        
        switch(which)
        {
            case 1:
                printf("Put size for allocating: ");
                scanf("%d", &mallocSize);
                
                if ((block = m_alloc(mallocSize)) != NULL) { // success allocating
                    allocatedBlocks[++lastBlockIndex] = *block;
                    printf("success allocating\n");
                } else { // fail allocating
                    printf("fail allocating\n");
                }
                break;
            case 2:
                printf("Which block will be free (index 0~99) : ");
                scanf("%d", &freeIndex);
                if (freeIndex <= lastBlockIndex) {
                    m_free(allocatedBlocks[freeIndex]);
                    allocatedBlocks[freeIndex].size = 0;
    
					memmove(allocatedBlocks+freeIndex,allocatedBlocks+freeIndex+1,sizeof(Block)*(lastBlockIndex-freeIndex));
					lastBlockIndex--;

				}
                break;
                
            case 3:
				for(a=0; a<=lastBlockIndex; a++){
					b = allocatedBlocks[a];
					printf("%d / ( %d ) / %d \n",b.start,b.size,b.end);
				}
				break;
        }
    } while(which == 1 || which == 2 || which ==3);
    
    printf("====exit====\n");
    
    return 0;
}

/*
 * init Manager like constructor
 */
void initManager(int heapSize) {
    Block heapMemoryBlock;
    
    g_heap = ((DLinkedList*) malloc(sizeof(DLinkedList)));
    
    Node *heapMemory = (Node*) malloc(sizeof(Node));
    heapMemoryBlock.start = 0;
    heapMemoryBlock.size = heapSize;
    heapMemoryBlock.end = heapSize-1;
    heapMemory->item = heapMemoryBlock;
    
    g_heap->size = 1;
    g_heap->header = heapMemory;
    g_heap->trailer = heapMemory;
    
    heapMemory->next = NULL;
    heapMemory->prev = NULL;

}




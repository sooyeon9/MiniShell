##
##  Makefile
##  HW2_MemoryManagement
##
##  Copyright © 2017년 2학기 System Programming. All rights reserved.
##
##  이름 : 구수연
##  학번 : 2014037756
##  학과 : 컴퓨터공학과
##


main: main.o
	gcc -o main main.o

main.o: DLinkedList.h MemoryManager.h Block.h Node.h main.c
	gcc -c main.c
	
clean:
	rm -f main main.o




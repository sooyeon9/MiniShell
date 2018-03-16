#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	struct Node *next;
	int value;
}Node;

typedef struct LinkedList
{
	int count;
	struct Node *head;
	struct Node *tail;
	struct Node *current;
}LinkedList;

void insert(LinkedList* list, int value);
void insertAt(LinkedList* list, int value, int position);
void delete(LinkedList* list, int position);
int search(LinkedList* list, int value);
void update(LinkedList* list, int value, int position);
void print_list(LinkedList* list);

void main()
{
	
	LinkedList *list1 = (LinkedList*)malloc(sizeof(LinkedList));
	list1->head = NULL;
	list1->tail = NULL;
	list1->current = NULL;
	list1->count = 0;

	printf("[insert] test\n");
	insert(list1,1);
	insert(list1,2);
	insert(list1,3);
	insert(list1,4);
	insert(list1,5);
	print_list(list1);
	printf("\n");

	printf("[insertAt] test - 10 at 100, 10 at 3, 0 at 1\n");
	insertAt(list1,10,100);
	insertAt(list1,10,3);
	insertAt(list1,0,1);
	print_list(list1);
	printf("\n");

	printf("[delete] test - position 4, 99\n");
	delete(list1,4);
	delete(list1,99);
	print_list(list1);
	printf("\n");

	printf("[search] test\n");
	printf("2 is %d-Node's value\n",search(list1,2));
	printf("10 is %d-Node's value\n",search(list1,10));	
	printf("3 is %d-Node's value\n",search(list1,3));
	printf("\n");

	printf("[update] test position 3 to 88\n");
	update(list1,88,3);
	print_list(list1);
	printf("\n");

	return 0;
}

/*
void print_head_tail(LinkedList *list)
{
	Node *node = (Node*)malloc(sizeof(Node));
	node = list->head;
	printf("%d is head node\n",node->value);
	node = list->tail;
	printf("%d is tail node\n",node->value);
} 
*/

void insert(LinkedList* list, int value)
{
	Node *newnode = (Node*)malloc(sizeof(Node));
	newnode->value = value;
	newnode->next = NULL;

	if(list->head == NULL)
		list->head = newnode;
	else
		list->tail->next = newnode;
	list->tail = newnode;
	(list->count)++;
}

void insertAt(LinkedList* list, int value, int position)
{
	if(position > list->count+1 || position<=0){
		printf("error! please check position again\n");
		return NULL;
	}
	Node *newnode = (Node*)malloc(sizeof(Node));
	newnode->value = value;
	newnode->next = NULL;

	if(position==1){
		if(list->head == NULL)
			list->tail = newnode;
		else
			newnode->next = list->head;
		list->head = newnode;
	} else {
		list->current = list->head;
		int i;
		for(i=1; i<position-1; i++)
			list->current = list->current->next;
		newnode->next = list->current->next;
		list->current->next = newnode;
	}

	(list->count)++;
}

void delete(LinkedList* list, int position)
{
	if(position>list->count || position<=0 || list->count==0){
		printf("error! please check position or number of list's node\n");
		return NULL;
	} else { 
		Node *deleting = (Node*)malloc(sizeof(Node));
		Node *deletingArm = (Node*)malloc(sizeof(Node));

		if(position == 1){	
			deleting = list->head;
			deletingArm = list->head->next;
			free(deleting);
			list->head = deletingArm;
			
		} else {
			list->current = list->head;
			int i;
			for(i=1; i<position-1; i++)
				list->current = list->current->next;
			deleting = list->current->next;
			deletingArm = list->current;

			if(position==list->count){
				list->tail = deletingArm;
				list->tail->next = NULL;
			} else
				list->current->next = deleting->next;	

			free(deleting);
		}
		(list->count)--;
	}
}

int search(LinkedList* list, int value)
{
	int searching=1;
	Node *node = (Node*)malloc(sizeof(Node));
	list->current = list->head;
	node = list->current;
	while(node->value!=value){
		if(list->current->next==NULL){
			searching=0;
			break;
		}
		list->current = list->current->next;
		node = list->current;
		searching++;
	}
	return searching;
}

void update(LinkedList* list, int value, int position)
{
	if(position>list->count || position<=0 || list->count==0){
		printf("error! please check position or number of list's node\n");
		return NULL;
	} else {
		int i;
		Node *node = (Node*)malloc(sizeof(Node));
		list->current = list->head;
		for(i=1; i<position; i++)
			list->current = list->current->next;
		node = list->current;
		node->value = value;
	}
}

void print_list(LinkedList* list)
{
	list->current = list->head;
	printf("---list---\n");
	while(list->current != NULL){
		printf("%d\n",(list->current->value));
		list->current = list->current->next;
	}
	printf("----------\n");
}
	 

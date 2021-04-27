/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	char data[4];
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
        
		printf("성명: 신태양\n");
		printf("학번: 2017038096\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	listNode* p = h->rlink;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->llink;
		free(prev);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
    listNode* node;
	listNode* temp;
    node = (listNode*)malloc(sizeof(listNode));
	node -> llink = NULL;
	if(h -> rlink == NULL){
	h -> rlink = node;
	}
    temp = h -> rlink;
	while(temp -> llink != NULL)
	temp = temp -> llink;
	temp -> llink = node;
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
    listNode* prevNode;
    listNode* delNode;
	if(h -> rlink == NULL) return 0;
	if(h -> rlink -> llink == NULL) {
		free(h -> rlink);
		h -> rlink = NULL;
	}
	 else {                //리스트에 노드가 2개 이상인 경우
        prevNode = h -> rlink;
        delNode = h -> rlink -> llink;
        while(delNode -> llink != NULL) {
            prevNode = delNode;
            delNode = delNode -> llink;
        }
		free(delNode);
        prevNode -> llink = NULL;
    }

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->llink = h->rlink;
	h->rlink = node;
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
    free(h);

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
    listNode* p;
	listNode* q;
	listNode* r;

	p = h -> rlink;
	q = NULL;
	r = NULL;

	while (p !=NULL){
		r = q;
		q = p;
		p = p -> llink;
		q -> llink = r;
	}
	h -> rlink = q;

	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {
    listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	if(h -> rlink == NULL){
		newNode -> rlink = NULL;
		newNode -> llink = NULL;
		h -> rlink = newNode;
	}
	else{
		newNode -> rlink;
		newNode -> llink;
        if(newNode -> rlink != NULL)
		newNode -> rlink -> llink = newNode;
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode* pre;
    if(h -> rlink == NULL)
	if(h -> rlink -> llink == NULL){
		free(h -> rlink);
		h -> rlink = NULL;
	}
	else {
		pre = h -> rlink;
		pre = pre -> llink;
	}
	pre -> llink;
	h -> rlink;
	return 0;
}



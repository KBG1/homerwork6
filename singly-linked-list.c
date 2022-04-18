#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key; 
	struct Node* link; // Node구조체의 포인터 link 선언
} listNode;  

typedef struct Head {
	struct Node* first; //Node구조체의 포인터 first 선언
}headNode;


headNode* initialize(headNode* h); 
int freeList(headNode* h); //headNode 구조체의 포인터 h를 변수로 하는 freeList 함수 선언

int insertFirst(headNode* h, int key); //headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 정수형 함수 insertFirst 함수 선언
int insertNode(headNode* h, int key); //headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 정수형 함수 insertNode 함수 선언
int insertLast(headNode* h, int key); //headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 정수형 함수 insertLast 함수 선언

int deleteFirst(headNode* h); //headNode 구조체의 포인터 h를 변수로 하는 deleteFirst 정수형 함수 선언
int deleteNode(headNode* h, int key); //headNode 구조체의 포인터 h, 정수형 변수 key를 변수로 하는 insertFirst 정수형 함수 선언
int deleteLast(headNode* h); //headNode 구조체의 포인터 h를 변수로 하는 deleteLast 정수형 함수 선언
int invertList(headNode* h);//headNode 구조체의 포인터 h를 변수로 하는 invertList 정수형 함수 선언

void printList(headNode* h); //headNode 구조체의 포인터 h를 변수로 하는 printList 함수 선언

int main()
{
	char command;
	int key;
	headNode* headnode=NULL; //headNode구조체의 포인터 headnode 초기화

	do{
        printf("-----------Kim Beom Gyu----------------------2019062022---------\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	if(h != NULL) //h가 빈값이 아닐 때만 실행
		freeList(h); 

	headNode* temp = (headNode*)malloc(sizeof(headNode)); //headeNode의 크기만큼의 동적 메모리 할당
	temp->first = NULL; //temp의 first에 NULL 대입
	return temp; //temp값 반환
}

int freeList(headNode* h){

	listNode* p = h->first;  //listNode* 구조체 p에 h의 first값 참조하여 대입

	listNode* prev = NULL; // prev을 NULL로 설정
	while(p != NULL) { //p가 NULL이 아니라면 무한 반복
		prev = p; //prev에 p값 대입
		p = p->link; //p의 link값을 p에 대입
		free(prev); //prev 메모리 반환
	}
	free(h); //h 메모리 반환
	return 0;
}


int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode 크기만큼의 동적메모리를 listNode 구조체 node에 대입
	node->key = key; // key값을 node의 key에 대입
	node->link = NULL; //NULL을 node의 link에 대입

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		h->first = node; //h의 first에 node값 대입
		return 0;
	}

	listNode* n = h->first; //h의 first값을 listNode 구조체 n에 대입
	listNode* trail = h->first; // h의 first값을 listNode 구조체 trail에 대입

	
	while(n != NULL) { //n이 NULL이 아니라면 반복
		if(n->key >= key) { 
			
			if(n == h->first) { // h의 first가 n과 같다면

				h->first = node; //node값을 h의 first에 대입
				node->link = n; //n값을 node의 link에 대입

			} else { 

				node->link = n; //n값을 node의 link에 대입
				trail->link = node; //node값을 trail의 link에 대입

			}
			return 0;
		}

		trail = n; //trail에 n 대입
		n = n->link; // n의 link에 n 대입
	}

	
	trail->link = node; //node값을 trail의 link에 대입
	return 0;
}


int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node에 listNode구조체 크기만큼의 동적메모리 할당
	node->key = key; //key값을 node의 key값에 대입
	node->link = NULL; //NULL값을 node의 link에 대입

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		h->first = node; //node값 h의 first에 대입
		return 0;
	}

	listNode* n = h->first; // h의 first의 값을 listNode 구조체 n에 대입
	while(n->link != NULL) {
		n = n->link; //n의 link값을 n에 대입
	}
	n->link = node; //node값을 n의 link에 대입
	return 0;
}


int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode구조체 node에 listNode크기만큼의 동적 메모리 할당
	node->key = key; //key값을 node의 key값에 대입

	node->link = h->first; //h의 first 값을 node의 link에 대입
	h->first = node; //node값을 h의 first에 대입

	return 0;
}


int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		printf("nothing to delete.\n"); //삭제할게 없다
		return 0;
	}

	listNode* n = h->first; //h의 first값을 listNode구조체 n에 대입
	listNode* trail = NULL; //NULL의 값을 trail에 대입

	
	while(n != NULL) { //n이 NULL이 아닌이상 무한 반복
		if(n->key == key) { //key값이 n의 key값과 같다면
			
			if(n == h->first) { //h의 first가 n과 같다면
				h->first = n->link; //n의 link값을 h의 first에 대입
			} else { 
				trail->link = n->link; //아니라면 n의 link를 trail의 link에 대입
			}
			free(n); //n의 메모리 반환
			return 0;
		}

		trail = n; //n값을 trail로
		n = n->link; //n의 link를 n으로 대입
	}

	
	printf("cannot find the node for key = %d\n", key); // 해당 key번호를 찾을 수 없다고 출력,
	return 0;

}

int deleteLast(headNode* h) {

	if (h->first == NULL) //h의 first가 NULL이라면
	{
 		printf("nothing to delete.\n"); //삭제할게 없다
		return 0;
	}

	listNode* n = h->first; //h의 first값을 n에 대입
	listNode* trail = NULL; //trail에 NULL 대입

	
	if(n->link == NULL) { //n의 link가 NULL이라면
		h->first = NULL; //h의 first값 초기화
		free(n); //n 메모리 반환
		return 0;
	}

	
	while(n->link != NULL) { //n의 link가 NULL이 아니면
		trail = n; //n값을 trail로 대입
		n = n->link; //n의 link를 n에 대입
	}

	
	trail->link = NULL; //trail의 link 초기화
	free(n); //n 메모리 반환

	return 0;
}

int deleteFirst(headNode* h) {

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		printf("nothing to delete.\n"); //삭제 x
		return 0;
	}
	listNode* n = h->first; //listNode 구조체 n에 h의 first 대입

	h->first = n->link; //n의 link를 h의 first에 대입
	free(n); //메모리 반환

	return 0;
}


int invertList(headNode* h) {


	if(h->first == NULL) { //h의 first에 값이 없다면
		printf("nothing to invert...\n"); //삽입할게 없다
		return 0;
	}
	listNode *n = h->first; //h의 first를 listNode의 포인터 변수 n에 대입
	listNode *trail = NULL; //포인터 변수 trail 초기화
	listNode *middle = NULL; //포인터 변수 middle 초기화

	while(n != NULL){ //n 이 NULL이 아니면
		trail = middle; //middle값을 trail로
		middle = n; //n을 middle로
		n = n->link; // n의 link를 n으로
		middle->link = trail; //trail을 middle의 link로
	}

	h->first = middle; //middle값을 h의 first로

	return 0;
}


void printList(headNode* h) {
	int i = 0; 
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //h가 NULL이면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //h의 first값을 p에 대입

	while(p != NULL) { //p가 NULL이 아닐때 반복
		printf("[ [%d]=%d ] ", i, p->key); //각각 0~k번째에 있는 key 값을 순서대로 출력
		p = p->link; //p의 link값을 p에 대입
		i++; //i 증가
	}

	printf("  items = %d\n", i); //들어가있는 원소 갯수 출력
}

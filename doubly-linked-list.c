#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //listNode구조체 선언
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head { //headNode 구조체 선언
	struct Node* first;
}headNode;

int initialize(headNode** h); /*h를 초기화 하는 함수(저번과제와 달리 이중포인터 매개변수 h로 쓴 이유는 함수의 return형이
headNode구조체 포인터에서 int형으로 바뀌어서 *h를 초기화 하기위해서 **h를 사용한다)*/
int freeList(headNode* h); //h의 메모리를 해제하는 함수

int insertNode(headNode* h, int key);//노드를 삽입하는 함수
int insertLast(headNode* h, int key); //노드를 마지막에 삽입하는 함수
int insertFirst(headNode* h, int key); //노드를 처음에 삽입하는 함수
int deleteNode(headNode* h, int key); //노드를 삭제하는 함수
int deleteLast(headNode* h); //마지막 노드를 삭제하는 함수
int deleteFirst(headNode* h); //첫번째 노드를 삭제하는 함수
int invertList(headNode* h); //노드를 역순으로 재배치하는 함수

void printList(headNode* h); //노드를 출력하는 함수


int main()
{
	printf("[----- [박에스더]  [2022041054] -----]\n"); 
	char command; //사용자에게 메뉴를 입력받을 변수 선언
	int key; //사용자에게 숫자를 입력받을 변수 선언
	headNode* headnode=NULL; //헤드노드 선언 후 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자에게 메뉴를 입력받는다

		switch(command) { //commad의 값에 따라 실행
		case 'z': case 'Z': //command가 z or Z일때
			initialize(&headnode); //initialize함수를 호출하여 headnode 초기화
			break;
		case 'p': case 'P': //command가 p or P일때
			printList(headnode); //printList함수를 호출하여 headnode 출력
			break;
		case 'i': case 'I': //command가 i or I일때
			printf("Your Key = "); 
			scanf("%d", &key); //사용자에게 key를 입력받는다
			insertNode(headnode, key); //insertNode를 호출하여 headnode에 key삽입
			break;
		case 'd': case 'D': //command가 d or D일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key를 입력받는다
			deleteNode(headnode, key); //deleteNode를 호출하여 headnode에서 key를 삭제
			break;
		case 'n': case 'N': //command가 n or N일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key를 입력받는다
			insertLast(headnode, key); //insertLast를 호출하여 headnode 마지막노드에 key 삽입
			break;
		case 'e': case 'E': //command가 e or E일때
			deleteLast(headnode); //deleteLast를 호출하여 headnode의 마지막 노드를 삭제
			break;
		case 'f': case 'F': //command가 f or F일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key를 입력받는다
			insertFirst(headnode, key); //inserFirst를 호출하여 headnode 첫번째노드에 key 삽입
			break;
		case 't': case 'T': //command가 t or T일때
			deleteFirst(headnode); //deleteFirst를 호출하여 headnode의 첫번째 노드를 삭제
			break;
		case 'r': case 'R': //command가 r or R일때
			invertList(headnode); //headnode를 역순으로 재배치
			break;
		case 'q': case 'Q': //command가 q or Q일때
			freeList(headnode); //headnode의 메모리 해제
			break;
		default: //command가 위의 값들과 다를때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q or Q일때 반복문 종료

	return 1; //함수 종료
}


int initialize(headNode** h) {

	//headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
	if(*h != NULL)
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode)); //헤드노드를 동적 메모리 할당
	(*h)->first = NULL; //첫번째 노드를 NULL로 초기화
	return 1; //함수 종료
}

int freeList(headNode* h){ 

	listNode* p = h->first; //listNode 구조체 *p를 선언 후 첫번째 노드 저장

	listNode* prev = NULL; //listNode 구조체 *prev를 선언후 NULL로 초기화
	while(p != NULL) { //p가 NULL일때
		prev = p;//prev에 p저장
		p = p->rlink; //p에 p의 다음 노드의링크 저장
		free(prev); //prev 메모리 해제
	}
	free(h); //h 메모리 해제
	return 0; //함수 종료
}

void printList(headNode* h) { 
	int i = 0; //변수 i 선언 후 0으로 초기화
	listNode* p; //listNode 구조체 *p선언

	printf("\n---PRINT\n");

	if(h == NULL) { //h가 NULL일때
		printf("Nothing to print....\n"); //프린트 할 값이 없다
		return;//함수 종료
	}

	p = h->first;//p에 h의 첫번째 노드 저장

	while(p != NULL) { //p가 NULL일때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //노드 출력
		p = p->rlink;//p에 다음 노드의 링크 저장
		i++; //i값 1증가
	}

	printf("  items = %d\n", i); //i를 출력
}

int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode구조체 *node 선언 후 동적 메모리 할당
	node->key = key; //node의 멤버변수 key에 메개변수 key저장
	node->rlink = NULL; //node의 멤버 구조체rlink에 NULL저장
	node->llink = NULL; //node의 멤버 구조체llink에 NULL저장

	if (h->first == NULL) //h의 첫번째 노드가 NULL일때
	{
		h->first = node;//h의 첫번째 노드에 node 저장
		return 0; //함수 종료
	}

	listNode* n = h->first; //listNode 구조체 *n를 선언 후 첫번째 노드 저장
	while(n->rlink != NULL) { //n의 다음 노드가 NULL일때 까지 반복
		n = n->rlink;//n에 n의 다음 노드 저장
	}
	n->rlink = node;//n의 다음 노드에 node 저장
	node->llink = n;//node의 llink에 n저장
	return 0; //함수 종료
}

int deleteLast(headNode* h) {

	if (h->first == NULL) //h의 첫번째 노드가 NULL일때
	{
		printf("nothing to delete.\n"); //삭제할 노드가 없다
		return 0; //함수 종료
	}

	listNode* n = h->first; //listNode 구조체 *n를 선언 후 첫번째 노드 저장
	listNode* trail = NULL; //listNode 구조체 *trail를 선언 후 NULL 저장

	if(n->rlink == NULL) { //노드가 하나일때
		h->first = NULL; //첫번째 노드에 NULL저장
		free(n); //n의 메모리 해제
		return 0;//함수종료
	}

	while(n->rlink != NULL) { //n의 rlink가 NULL일때 까지 반복
		trail = n; //trail에 n저장
		n = n->rlink; //n에 n의 rlink저장
	}

	trail->rlink = NULL; //trail의 rlink에 NULL저장
	free(n); //n의 메모리 해제

	return 0; //함수종료
}

int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode구조체 *node 선언 후 동적 메모리 할당
	node->key = key; //node의 멤버변수 key에 메개변수 key저장
	node->rlink = node->llink = NULL; //node의 rlink와 link에 NULL저장

	if(h->first == NULL) //h의 첫번째 노드가 NULL일때
	{
		h->first = node; //첫번째 노드에 node 저장
		return 1; //함수 종료
	}

	node->rlink = h->first; //node의 rlink에 첫번째 노드 저장
	node->llink = NULL;//node의 link에 NULL 저장

	listNode *p = h->first; //listNode 구조체 *p를 선언 후 첫번째 노드 저장
	p->llink = node; //p의 llink에 node 저장
	h->first = node; //h의 첫번째 노드에 node 저장

	return 0; //함수 종료
}

int deleteFirst(headNode* h) { 

	if (h->first == NULL) //h의 첫번째 노드가 NULL일때
	{
		printf("nothing to delete.\n"); //삭제할 것이 없다
		return 0; //함수 종료
	}
	listNode* n = h->first; //listNode 구조체 *n을 선언 후 첫번째 노드 저장
	h->first = n->rlink; //h의 첫번째 노드에 n의 rlink 저장

	free(n); //n 메모리 해제

	return 0;
}

int invertList(headNode* h) {


	if(h->first == NULL) { //h의 첫번째 노드가 NULL일때 
		printf("nothing to invert...\n"); //재배치할 것이 없다
		return 0;//함수 종료
	}
	listNode *n = h->first; //listNode 구조체 *n을 선언 후 첫번째 노드 저장
	listNode *trail = NULL; //listNode 구조체 *trail을 선언 후 첫번째 노드 저장
	listNode *middle = NULL; //listNode 구조체 *middle을 선언 후 첫번째 노드 저장

	while(n != NULL){ //n이 NULL일때 까지 반복
		trail = middle; //trail에 middle저장
		middle = n; //middle에 n저장
		n = n->rlink; //n에 n의 rlink 저장
		middle->rlink = trail; //middle의 rlink에 trail저장
		middle->llink = n; //middle의 llink에 n저장
	}

	h->first = middle; //h의 첫번재 노드에 middle저장

	return 0; //함수종료
}


int insertNode(headNode* h, int key) { 

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode구조체 *node 선언 후 동적 메모리 할당
	node->key = key; //node의 멤버변수 key에 메개변수 key저장
	node->llink = node->rlink = NULL; //node의 rlink와 link에 NULL저장

	if (h->first == NULL) //h의 첫번째 노드가 NULL일때
	{
		h->first = node; //h의 첫번째 노드에 node저장
		return 0; //함수 종료
	}

	listNode* n = h->first; //listNode구조체 *n 선언 후 h의 첫번째 노드 저장

	while(n != NULL) { //n이 NULL일때까지 반복
		if(n->key >= key) { //n의 멤버변수 key가 매개변수 key보다 크거나 같을때
			if(n == h->first) { //n이 h의 첫번째 노드와 같을때
				insertFirst(h, key); //insertFirst함수 호출
			} else { //n이 h의 첫번째 노드와 다를때
				node->rlink = n; //node의 rlink에 n저장
				node->llink = n->llink; //node의 llink에 n의 llink저장
				n->llink->rlink = node; //n의 llink의 rlink에 노드 저장
			}
			return 0; //함수종료
		}

		n = n->rlink; //n에 n의 rlink저장
	}

	//마지막 노드까지 찾지 못한 경우, 마지막에 삽입
	insertLast(h, key); //insrtLast함수 호출
	return 0; //함수 종료
}

int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //h의 첫번째 노드가 NULL일때
	{
		printf("nothing to delete.\n"); //삭제할 노드가 없다
		return 1; //함수 종료
	}

	listNode* n = h->first; //listNode구조체 *n 선언 후 h의 첫번째 노드 저장

	while(n != NULL) {
		if(n->key == key) { //n의 멤버변수 key가 매개변수 key보다 같을때
			if(n == h->first) { //n이 h의 첫번째 노드와 같을때
				deleteFirst(h); //deleteFirst함수 호출
			} else if (n->rlink == NULL){ //n의 rlink가 NULL일때
				deleteLast(h); //deleteLast함수 호출
			} else { // 중간인 경우 
				n->llink->rlink = n->rlink; //n의 llink의 rlink에 n의 rlink저장
				n->rlink->llink = n->llink; //n의 rlink의 llink에 n의 llink 저장
				free(n); //n의 메모리 해제
			}
			return 1; //함수 종료
		}

		n = n->rlink; //n에 n의 rlink저장
	}

	// 찾지 못 한경우
	printf("cannot find the node for key = %d\n", key); //key에 대한 노드가 없다
	return 1; //함수 종료
}
#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //listNode����ü ����
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head { //headNode ����ü ����
	struct Node* first;
}headNode;

int initialize(headNode** h); /*h�� �ʱ�ȭ �ϴ� �Լ�(���������� �޸� ���������� �Ű����� h�� �� ������ �Լ��� return����
headNode����ü �����Ϳ��� int������ �ٲ� *h�� �ʱ�ȭ �ϱ����ؼ� **h�� ����Ѵ�)*/
int freeList(headNode* h); //h�� �޸𸮸� �����ϴ� �Լ�

int insertNode(headNode* h, int key);//��带 �����ϴ� �Լ�
int insertLast(headNode* h, int key); //��带 �������� �����ϴ� �Լ�
int insertFirst(headNode* h, int key); //��带 ó���� �����ϴ� �Լ�
int deleteNode(headNode* h, int key); //��带 �����ϴ� �Լ�
int deleteLast(headNode* h); //������ ��带 �����ϴ� �Լ�
int deleteFirst(headNode* h); //ù��° ��带 �����ϴ� �Լ�
int invertList(headNode* h); //��带 �������� ���ġ�ϴ� �Լ�

void printList(headNode* h); //��带 ����ϴ� �Լ�


int main()
{
	printf("[----- [�ڿ�����]  [2022041054] -----]\n"); 
	char command; //����ڿ��� �޴��� �Է¹��� ���� ����
	int key; //����ڿ��� ���ڸ� �Է¹��� ���� ����
	headNode* headnode=NULL; //����� ���� �� �ʱ�ȭ

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
		scanf(" %c", &command); //����ڿ��� �޴��� �Է¹޴´�

		switch(command) { //commad�� ���� ���� ����
		case 'z': case 'Z': //command�� z or Z�϶�
			initialize(&headnode); //initialize�Լ��� ȣ���Ͽ� headnode �ʱ�ȭ
			break;
		case 'p': case 'P': //command�� p or P�϶�
			printList(headnode); //printList�Լ��� ȣ���Ͽ� headnode ���
			break;
		case 'i': case 'I': //command�� i or I�϶�
			printf("Your Key = "); 
			scanf("%d", &key); //����ڿ��� key�� �Է¹޴´�
			insertNode(headnode, key); //insertNode�� ȣ���Ͽ� headnode�� key����
			break;
		case 'd': case 'D': //command�� d or D�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key�� �Է¹޴´�
			deleteNode(headnode, key); //deleteNode�� ȣ���Ͽ� headnode���� key�� ����
			break;
		case 'n': case 'N': //command�� n or N�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key�� �Է¹޴´�
			insertLast(headnode, key); //insertLast�� ȣ���Ͽ� headnode ��������忡 key ����
			break;
		case 'e': case 'E': //command�� e or E�϶�
			deleteLast(headnode); //deleteLast�� ȣ���Ͽ� headnode�� ������ ��带 ����
			break;
		case 'f': case 'F': //command�� f or F�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key�� �Է¹޴´�
			insertFirst(headnode, key); //inserFirst�� ȣ���Ͽ� headnode ù��°��忡 key ����
			break;
		case 't': case 'T': //command�� t or T�϶�
			deleteFirst(headnode); //deleteFirst�� ȣ���Ͽ� headnode�� ù��° ��带 ����
			break;
		case 'r': case 'R': //command�� r or R�϶�
			invertList(headnode); //headnode�� �������� ���ġ
			break;
		case 'q': case 'Q': //command�� q or Q�϶�
			freeList(headnode); //headnode�� �޸� ����
			break;
		default: //command�� ���� ����� �ٸ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command�� q or Q�϶� �ݺ��� ����

	return 1; //�Լ� ����
}


int initialize(headNode** h) {

	//headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ����
	if(*h != NULL)
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode)); //����带 ���� �޸� �Ҵ�
	(*h)->first = NULL; //ù��° ��带 NULL�� �ʱ�ȭ
	return 1; //�Լ� ����
}

int freeList(headNode* h){ 

	listNode* p = h->first; //listNode ����ü *p�� ���� �� ù��° ��� ����

	listNode* prev = NULL; //listNode ����ü *prev�� ������ NULL�� �ʱ�ȭ
	while(p != NULL) { //p�� NULL�϶�
		prev = p;//prev�� p����
		p = p->rlink; //p�� p�� ���� ����Ǹ�ũ ����
		free(prev); //prev �޸� ����
	}
	free(h); //h �޸� ����
	return 0; //�Լ� ����
}

void printList(headNode* h) { 
	int i = 0; //���� i ���� �� 0���� �ʱ�ȭ
	listNode* p; //listNode ����ü *p����

	printf("\n---PRINT\n");

	if(h == NULL) { //h�� NULL�϶�
		printf("Nothing to print....\n"); //����Ʈ �� ���� ����
		return;//�Լ� ����
	}

	p = h->first;//p�� h�� ù��° ��� ����

	while(p != NULL) { //p�� NULL�϶����� �ݺ�
		printf("[ [%d]=%d ] ", i, p->key); //��� ���
		p = p->rlink;//p�� ���� ����� ��ũ ����
		i++; //i�� 1����
	}

	printf("  items = %d\n", i); //i�� ���
}

int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode����ü *node ���� �� ���� �޸� �Ҵ�
	node->key = key; //node�� ������� key�� �ް����� key����
	node->rlink = NULL; //node�� ��� ����ürlink�� NULL����
	node->llink = NULL; //node�� ��� ����üllink�� NULL����

	if (h->first == NULL) //h�� ù��° ��尡 NULL�϶�
	{
		h->first = node;//h�� ù��° ��忡 node ����
		return 0; //�Լ� ����
	}

	listNode* n = h->first; //listNode ����ü *n�� ���� �� ù��° ��� ����
	while(n->rlink != NULL) { //n�� ���� ��尡 NULL�϶� ���� �ݺ�
		n = n->rlink;//n�� n�� ���� ��� ����
	}
	n->rlink = node;//n�� ���� ��忡 node ����
	node->llink = n;//node�� llink�� n����
	return 0; //�Լ� ����
}

int deleteLast(headNode* h) {

	if (h->first == NULL) //h�� ù��° ��尡 NULL�϶�
	{
		printf("nothing to delete.\n"); //������ ��尡 ����
		return 0; //�Լ� ����
	}

	listNode* n = h->first; //listNode ����ü *n�� ���� �� ù��° ��� ����
	listNode* trail = NULL; //listNode ����ü *trail�� ���� �� NULL ����

	if(n->rlink == NULL) { //��尡 �ϳ��϶�
		h->first = NULL; //ù��° ��忡 NULL����
		free(n); //n�� �޸� ����
		return 0;//�Լ�����
	}

	while(n->rlink != NULL) { //n�� rlink�� NULL�϶� ���� �ݺ�
		trail = n; //trail�� n����
		n = n->rlink; //n�� n�� rlink����
	}

	trail->rlink = NULL; //trail�� rlink�� NULL����
	free(n); //n�� �޸� ����

	return 0; //�Լ�����
}

int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode����ü *node ���� �� ���� �޸� �Ҵ�
	node->key = key; //node�� ������� key�� �ް����� key����
	node->rlink = node->llink = NULL; //node�� rlink�� link�� NULL����

	if(h->first == NULL) //h�� ù��° ��尡 NULL�϶�
	{
		h->first = node; //ù��° ��忡 node ����
		return 1; //�Լ� ����
	}

	node->rlink = h->first; //node�� rlink�� ù��° ��� ����
	node->llink = NULL;//node�� link�� NULL ����

	listNode *p = h->first; //listNode ����ü *p�� ���� �� ù��° ��� ����
	p->llink = node; //p�� llink�� node ����
	h->first = node; //h�� ù��° ��忡 node ����

	return 0; //�Լ� ����
}

int deleteFirst(headNode* h) { 

	if (h->first == NULL) //h�� ù��° ��尡 NULL�϶�
	{
		printf("nothing to delete.\n"); //������ ���� ����
		return 0; //�Լ� ����
	}
	listNode* n = h->first; //listNode ����ü *n�� ���� �� ù��° ��� ����
	h->first = n->rlink; //h�� ù��° ��忡 n�� rlink ����

	free(n); //n �޸� ����

	return 0;
}

int invertList(headNode* h) {


	if(h->first == NULL) { //h�� ù��° ��尡 NULL�϶� 
		printf("nothing to invert...\n"); //���ġ�� ���� ����
		return 0;//�Լ� ����
	}
	listNode *n = h->first; //listNode ����ü *n�� ���� �� ù��° ��� ����
	listNode *trail = NULL; //listNode ����ü *trail�� ���� �� ù��° ��� ����
	listNode *middle = NULL; //listNode ����ü *middle�� ���� �� ù��° ��� ����

	while(n != NULL){ //n�� NULL�϶� ���� �ݺ�
		trail = middle; //trail�� middle����
		middle = n; //middle�� n����
		n = n->rlink; //n�� n�� rlink ����
		middle->rlink = trail; //middle�� rlink�� trail����
		middle->llink = n; //middle�� llink�� n����
	}

	h->first = middle; //h�� ù���� ��忡 middle����

	return 0; //�Լ�����
}


int insertNode(headNode* h, int key) { 

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode����ü *node ���� �� ���� �޸� �Ҵ�
	node->key = key; //node�� ������� key�� �ް����� key����
	node->llink = node->rlink = NULL; //node�� rlink�� link�� NULL����

	if (h->first == NULL) //h�� ù��° ��尡 NULL�϶�
	{
		h->first = node; //h�� ù��° ��忡 node����
		return 0; //�Լ� ����
	}

	listNode* n = h->first; //listNode����ü *n ���� �� h�� ù��° ��� ����

	while(n != NULL) { //n�� NULL�϶����� �ݺ�
		if(n->key >= key) { //n�� ������� key�� �Ű����� key���� ũ�ų� ������
			if(n == h->first) { //n�� h�� ù��° ���� ������
				insertFirst(h, key); //insertFirst�Լ� ȣ��
			} else { //n�� h�� ù��° ���� �ٸ���
				node->rlink = n; //node�� rlink�� n����
				node->llink = n->llink; //node�� llink�� n�� llink����
				n->llink->rlink = node; //n�� llink�� rlink�� ��� ����
			}
			return 0; //�Լ�����
		}

		n = n->rlink; //n�� n�� rlink����
	}

	//������ ������ ã�� ���� ���, �������� ����
	insertLast(h, key); //insrtLast�Լ� ȣ��
	return 0; //�Լ� ����
}

int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //h�� ù��° ��尡 NULL�϶�
	{
		printf("nothing to delete.\n"); //������ ��尡 ����
		return 1; //�Լ� ����
	}

	listNode* n = h->first; //listNode����ü *n ���� �� h�� ù��° ��� ����

	while(n != NULL) {
		if(n->key == key) { //n�� ������� key�� �Ű����� key���� ������
			if(n == h->first) { //n�� h�� ù��° ���� ������
				deleteFirst(h); //deleteFirst�Լ� ȣ��
			} else if (n->rlink == NULL){ //n�� rlink�� NULL�϶�
				deleteLast(h); //deleteLast�Լ� ȣ��
			} else { // �߰��� ��� 
				n->llink->rlink = n->rlink; //n�� llink�� rlink�� n�� rlink����
				n->rlink->llink = n->llink; //n�� rlink�� llink�� n�� llink ����
				free(n); //n�� �޸� ����
			}
			return 1; //�Լ� ����
		}

		n = n->rlink; //n�� n�� rlink����
	}

	// ã�� �� �Ѱ��
	printf("cannot find the node for key = %d\n", key); //key�� ���� ��尡 ����
	return 1; //�Լ� ����
}
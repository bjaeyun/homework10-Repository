/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node { //구조체 node선언
	int key;
	struct node *left; //node포인터 left 선언
	struct node *right; //node포인터 right 선언
} Node;

/* for stack */
#define MAX_STACK_SIZE	20 //stack size 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE	20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */
/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);
/* you may add your own defined functions if necessary */
void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL; //Node포인더 head NULL로 초기화

	do{
		printf("\n\n");
		printf("-----------------[Byeun jaeyun] [2022041046]--------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': //z, Z일때
			initializeBST(&head); //initializeBST함수 호출
			break;
		case 'q': case 'Q': //q, Q일때
			freeBST(head); //freeBST함수 호출
			break;
		case 'i': case 'I': //i, I일때
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); //insert함수 호출
			break;
		case 'd': case 'D': //d, D일때
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key); //deleteNode함수 호출
			break;

		case 'r': case 'R': //r, R일때
			recursiveInorder(head->left); //recursiveInorder함수 호출
			break;
		case 't': case 'T': //t, T일때
			iterativeInorder(head->left); //iterativeInorder함수 호출
			break;

		case 'l': case 'L': //l, L일때
			levelOrder(head->left); //levelOrder함수 호출
			break;

		case 'p': case 'P': //p, P일때
			printStack(); //printStack함수 호출
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1; //1반환
}

int initializeBST(Node** h) { //BST를 초기화 하는 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //만약 BST가 비어있다면
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //h동적할당
	(*h)->left = NULL;	/* root */ //h의 left-child를 NULL로 초기화
	(*h)->right = *h; //h의 right-child에 h를 저장
	(*h)->key = -9999; //h의 key에 -9999저장

	top = -1; //top을 -1로 초기화

	front = rear = -1; //front와 rear를 -1로 초기화

	return 1; //1반환
}

void recursiveInorder(Node* ptr)//재귀적방법으로 중위순회하는 함수
{
	if(ptr) { //ptr이 NULL이 아니라면
		recursiveInorder(ptr->left); //ptr의 left-child를 중위순회
		printf(" [%d] ", ptr->key); //ptr의 key값 출력
		recursiveInorder(ptr->right); //ptr의 right-child를 중위순회
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //반복적방법으로 중위순회하는 함수
{
	for(;;) //무한 루프하는 for문
	{
		for(; node; node = node->left) //node가 NULL일때까지 반복하는 for문
			push(node); //node push
		node = pop(); //node pop
		if(!node) break; //node가 NULL이라면 break
		printf(" [%d] ", node->key); //node의 key값을 출력
		node = node->right; //node를 noed의 right-child로 이동
	}
}
/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //level 순으로 순회하는 함수
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */ //ptr이 NULL일때 return

	enQueue(ptr); //ptr을 enQueue

	for(;;)	//무한 루프하는 for문
	{
		ptr = deQueue(); //ptr을 deQueue
		if(ptr) { //ptr이 NULL이라면
			printf(" [%d] ", ptr->key); //ptr의 key값 출력
			if(ptr->left) //ptr의 left-child가 NULL이 아니라면
				enQueue(ptr->left);	//ptr의 left-child를 enQueue
			if(ptr->right) //ptr의 right-child가 NULL이 아니라면
				enQueue(ptr->right); //ptr의 right-child를 enQueue
		}
		else //ptr이 NULL이라면
			break; //break

	}

}


int insert(Node* head, int key) //BST에 node를 삽입하는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //Node 포인터변수 newNode를 선언 후 동적 할당
	newNode->key = key; //newNode의 key를 사용자로부터 입력받은 key로 설정
	newNode->left = NULL;
	newNode->right = NULL;
    //newNode의 left-child와 right-child를 NULL로 초기화
	if (head->left == NULL) { //head의 left-child가 NULL일때
		head->left = newNode; //head의 left-child에 newNode 저장
		return 1;	//1 반환
	}
	/* head->left is the root */
	Node* ptr = head->left; //Node 포인터 변수 ptr에 head의 left-child 저장
	Node* parentNode = NULL; //Node 포인터 변수 parentNode를 NULL로 초기화
	while(ptr != NULL) { //ptr이 NULL이 아닐때 반복
		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //ptr의 key가 key라면 1반환
		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //parentNode에 ptr 저장
		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr의 key가 key보다 작다면
			ptr = ptr->right; //ptr에 ptr의 right값 저장
		else //아니라면
			ptr = ptr->left; //ptr에 ptr의 left값 저장
	}
	/* linking the new node to the parent */
	if(parentNode->key > key) //parentNode의 key값이 key보다 크다면
		parentNode->left = newNode; //parentNode의 left에 newNode 저장
	else //아니라면
		parentNode->right = newNode; //parentNode의 rightdp newNode 저장
	return 1; //1반환
}


int deleteNode(Node* head, int key) //Node를 삭제하는 함수
{
	if (head == NULL) { //head가 NULL이라면
		printf("\n Nothing to delete!!\n");
		return -1; //-1 반환
	}

	if (head->left == NULL) { //head의 left-child가 NULL일때
		printf("\n Nothing to delete!!\n");
		return -1; //-1 반환
	}

	/* head->left is the root */
	Node* root = head->left; //Node 포인터 변수 root선언 후 head의 left-child 저장
	Node* parent = NULL; //Node 포인터 변수 parent 선언
	Node* ptr = root; //Node 포인터 변수 ptr 선언 후 root 저장

	while((ptr != NULL)&&(ptr->key != key)) { //ptr이 NULL이 아니고 ptr의 key가 key가 아닐때 반복
		if(ptr->key != key) {//ptr의 key값이 key가 아니라면
			parent = ptr;	/* save the parent */ //parent에 ptr 저장
			if(ptr->key > key) //ptr의 key가 key보다 크다면
				ptr = ptr->left; //ptr에 ptr left-child 저장
			else //ptr의 key가 key보다 작거나 같다면
				ptr = ptr->right;	//ptr에 ptr right-child 저장
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) //ptr이 NULL이라면
	{
		printf("No node for key [%d]\n ", key);
		return -1; //-1 반환
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) //ptr의 left-child가 NULL이고 ptr의 right-child가 NULL이라면
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)	//parent의 left-child가 ptr이라면
				parent->left = NULL;	//parent의 left-child를 NULL로 초기화
			else	//parent의 left-child가 ptr이 아니라면
				parent->right = NULL;	//parent의 right-child를 NULL로 초기화
		} else { //parent의 left-child가 ptr이 아니라면
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; //head의 left-child를 NULL로 초기화
		}
		free(ptr); //ptr해제
		return 1; //1반환
	}
	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //ptr의 left-child가 NULL이거나 ptr의 right-child가 NULL이라면
	{
		Node* child; //Node 포인터 변수 child 선언
		if (ptr->left != NULL) //ptr의 left-child가 NULL이 아니라면
			child = ptr->left; //child에 ptr의 left-child 저장
		else //ptr의 left-child가 NULL이 아니라면
			child = ptr->right; //child에 ptr의 right-child 저장
		if(parent != NULL) //parent가 NULL이 아니라면
		{
			if(parent->left == ptr)	//parent의 left-child가 ptr이라면
				parent->left = child;	//parent의 left-child에 child 저장
			else	//parent의 left-child가 ptr이 아니라면
                parent->right = child;	//parent의 right-child에 child 저장
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; //root에 child 저장
		}
		free(ptr); //ptr해제
		return 1; //1반환
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate; //Node 포인터 변수 canditate
	parent = ptr; //parent에 ptr 저장
	candidate = ptr->right; //candidate에 ptr의 right-child 저장

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) //candidate의 left-child가 NULL이 아닐때
	{
		parent = candidate;	//parent에 candidate 저장
		candidate = candidate->left; //candidate에 candidate의 left-child 저장
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) //parent의 right-child가 candidate이라면
		parent->right = candidate->right; //parent의 right-child에 candidate의 right-child 저장
	else //parent의 right-child가 candidate가 아니라면
		parent->left = candidate->right; //parent의 left-child에 candidate의 right-child 저장

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; //ptr의 key값에 candidate의 key값 저장

	free(candidate); //candidate 해제
	return 1; //1반환
}


void freeNode(Node* ptr) //Node를 free하는 함수
{
	if(ptr) {	//ptr이 NULL이라면
		freeNode(ptr->left);	//ptr의 left-child를 free
		freeNode(ptr->right);	//ptr의 right-child를 free
		free(ptr);	//ptr 해제
	}
}

int freeBST(Node* head) //BST를 free하는 함수
{

	if(head->left == head)	//head의 left-child가 head이라면
	{
		free(head);	//head 해제
		return 1;	//1 반환
	}

	Node* p = head->left; //Node 포인터 변수 p 선언 후 head의 left-child 저장

	freeNode(p); //p 해제

	free(head); //head 해제
	return 1; //1반환
}



Node* pop() //stack을 pop하는 함수
{
	if (top < 0) return NULL; //top이 0보다 작으면 NULL을 return
	return stack[top--]; //stack[top]을 return하고 top을 -1
}

void push(Node* aNode) //stack에 push하는 함수
{
	stack[++top] = aNode; //top을 +1하고 stack[top]에 aNode 저장
}


void printStack() //화면에 출력하는 함수
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue() //deQueue 함수
{
	if (front == rear) { //front가 rear와 일치할때
		// printf("\n....Now Queue is empty!!\n" );
		return NULL; //NULL을 리턴
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front]; //queue[front] 리턴

}

void enQueue(Node* aNode) //enQueue 함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) { //enQueue 함수
		// printf("\n....Now Queue is full!!\n");
		return; //return NULL
	}

	queue[rear] = aNode; //queue[rear]에 aNode 저장
}
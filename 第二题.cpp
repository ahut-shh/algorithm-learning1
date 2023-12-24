#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef struct node {
	int data;
	struct node* lchild, * rchild;
	int flag;
}tree,*Tree;

typedef struct strcknode {
	Tree data;
	struct strcknode* next;
}stack,*Stack;

Stack init_stack()
{
	Stack S = (Stack)malloc(sizeof(stack));
	if (S)
	{
		S->data = NULL;
		S->next = NULL;
	}
	return S;
}

void push_stack(Tree T, Stack S)
{
	Stack H= (Stack)malloc(sizeof(stack));
	H->data = T;
	H->next = S->next;
	S->next = H;
}

int empty(Stack S)
{
	if (S->next == NULL)
		return 1;
	else
		return 0;
}

Stack pop_stack(Stack S)
{
	if (empty(S))
		return NULL;
	else
	{
		Stack H;
		H = S->next;
		S->next = H->next;
		return H;
	}
}

Stack getpop(Stack S)
{
	if (empty(S))
	{
		return NULL;
	}
	else
	{
		Stack node = S->next;
		return node;
	}
}

void preorder(Tree T)//先序遍历
{
	if (T)
	{
		printf("%d", T->data);
		preorder(T->lchild);
		preorder(T->rchild);
	}
}

void preorderIterative(Tree T)
{
	if (T == NULL)
		return;

	Stack S = init_stack();
	push_stack(T, S);
	while (!empty(S))
	{
		Tree H = getpop(S)->data;
		printf("%d ", H->data);
		pop_stack(S);
		if (H->rchild)push_stack(H->rchild, S);
		if (H->lchild)push_stack(H->lchild, S);
	}
}


void inorder(Tree T)//中序遍历
{
	if (T)
	{
		inorder(T->lchild);
		printf("%d", T->data);
		inorder(T->rchild);
	}
}

void inorderIterative(Tree T)
{
	if (T==NULL)
		return;
	Stack S = init_stack();
	Tree H=T;

	while (!empty(S)||H)
	{
		while (H)
		{
			push_stack(H, S);
			H = H->lchild;
		}
		H = getpop(S)->data;
		printf("%d ", H->data);
		pop_stack(S);
		
		H = H->rchild;
		
	}
}


void postorder(Tree T)//后序遍历
{
	if (T)
	{
		postorder(T->lchild);
		postorder(T->rchild);
		printf("%d", T->data);
	}
}

void postorderIterative(Tree T)
{
	if (T == NULL)
		return;
	Stack S = init_stack();
	Tree H=T;
	while (H || !empty(S))
	{
		while (H)
		{
			push_stack(H, S);
			H = H->lchild;
		}
		Tree temp = getpop(S)->data;
		if (temp->rchild && temp->rchild->flag == 0)
		{
			temp = temp->rchild;
			push_stack(temp, S);
			H = temp->lchild;
		}
		else
		{
			/*temp = pop_stack(S)->data;*/
			printf("%d ", temp->data);
			pop_stack(S);
			temp->flag = 1;
		}
	}
}


void Leveorder(Tree T)//层序遍历
{
	if (!T)
		return;

	Tree q[MAXSIZE];
	int front = 1, rear = 1;
	q[1] = T;
	while (front <= rear)
	{
		Tree p = q[front];
		front++;
		printf("%d", p->data);
		if (p->lchild)
		{
			rear++;
			q[rear] = p->lchild;
		}
		if (p->rchild)
		{
			rear++;
			q[rear] = p->rchild;
		}
	}
}

void creatTree(Tree* T) {
	int data;
	scanf("%d", &data);

	if (data == -1) {
		*T = NULL;
	}
	else {
		*T = (Tree)malloc(sizeof(tree));
		(*T)->data = data;
		(*T)->flag = 0;
		creatTree(&((*T)->lchild));
		creatTree(&((*T)->rchild));
	}
}

int main()
{
	Tree T;
	creatTree(&T);
	printf("层序遍历:");
	Leveorder(T);
	printf("\n");

	printf("先序遍历:");
	preorder(T);
	printf("\n");

	printf("中序遍历:");
	inorder(T);
	printf("\n");

	printf("后序遍历:");
	postorder(T);
	printf("\n");

	printf("先序非递归遍历:");
	preorderIterative(T);
	printf("\n");

	printf("中序非递归遍历:");
	inorderIterative(T);
	printf("\n");

	printf("后序非递归遍历:");
	postorderIterative(T);
	printf("\n");
}
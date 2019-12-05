#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 256


typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;


char string[MAX_STACK_SIZE] = "";
char str2[MAX_STACK_SIZE] = "";
char *str3[MAX_STACK_SIZE];
char *str4[MAX_STACK_SIZE];
char del1[3] = " \t\n";
char del2[10] = " =+-*/%;()";
char *token;

int number[MAX_STACK_SIZE];



// ���� �ʱ�ȭ �Լ�
void init(StackType *s)
{
	s->top = -1;
}


// ���� ���� ���� �Լ�
int is_empty(StackType *s)
{
	return (s->top == -1);
}


// ��ȭ ���� ���� �Լ�
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}


// �����Լ�
void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}


// �����Լ�
element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}


// ��ũ�Լ�
element peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[s->top];
}


//�������� �켱���� ��ȯ
int prec(char op)
{
	switch (op)
	{
	case ';': return 0;
	case '=': return 1;
	case '(': case ')': return 2;
	case '+': case '-': return 3;
	case '*': case '/': case '%': return 4;
	}
	return -1;
}


void spacing_first()
{
	int i = 0, j = 0;
	int len = strlen(string);
	char ch;

	for (i = 0; i < MAX_STACK_SIZE; i++) {
		ch = string[i];

		switch (ch) {
		case '=': case '+': case '-': case '*': case '/': case '%': case ';': case '(': case ')': // ������
			for (j = len + i + 1; j >= i + 1; j--)
			{
				string[j + 2] = string[j];
			}
			string[i] = ' ';
			string[i + 1] = ch;
			string[i + 2] = ' ';
			i += 2;
			break;
		default:
			break;
		}
	}
}


void spacing_second()
{
	int i = 0, j = 0, k = 0, num = 0;
	int len = strlen(str2);
	char ch;

	for (i = 0; i < MAX_STACK_SIZE; i++) {
		ch = str2[i];

		switch (ch) {
		case '=': case '+': case '-': case '*': case '/': case '%': case ';': case '(': case ')': // ������
			for (j = len + i + 1; j >= i; j--)
			{
				str2[j + 1] = str2[j];
			}
			str2[i + 1] = ' ';
			i += 1;
			break;
		case ' ':
			break;
		default:
			i += number[k++];
			for (j = len + i + 1; j >= i; j--)
			{
				str2[j + 1] = str2[j];
			}
			str2[i] = ' ';
			break;
		}
	}
}


// ���� ǥ�� ���� -> ���� ǥ�� ����
void infix_to_postfix(char *exp)
{
	int i = 0, j = 0;
	char ch, top_op;
	char str1[MAX_STACK_SIZE] = "";
	int len = strlen(exp);
	StackType s;


	init(&s);                                       // ���� �ʱ�ȭ
	for (i = 0; i<len; i++){
		ch = exp[i];
		// �������̸�
		switch (ch){
		case '=': case '+': case '-': case '*': case '/': case '%': case ';': // ������
			// ���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			{
				str1[j++] = pop(&s);
			}
			push(&s, ch);
			break;
		case '(':       // ���� ��ȣ
			push(&s, ch);
			break;
		case ')':       // ������ ��ȣ
			top_op = pop(&s);
			// ���� ��ȣ�� ���������� ���
			while (top_op != '('){
				str1[j++] = top_op;
				top_op = pop(&s);
			}
			break;
		case ' ':
			break;
		default:                // �ǿ�����
			str1[j++] = ch;
			break;
		}
	}
	while (!is_empty(&s))   // ���ÿ� ����� �����ڵ� ���
	{
		str1[j++] = pop(&s);
	}
	strcpy(str2, str1);
}


int main(void)
{
	int i = 0, a = 0, num = 0;

	gets(string);
	infix_to_postfix(string);

	printf("\n");

	puts(str2);

	spacing_first(string);

	token = strtok(string, del2);

	printf("\n");

	while (token != NULL) {
		str3[i++] = token;
		printf("%s ", token);
		token = strtok(NULL, del2);
		num++;
	}

	
	for (a = 0; a < i; a++)
	{
		number[a] = strlen(str3[a]);
	}

	spacing_second();


	printf("\n \n");

	
	puts(str2);


	return 0;
}
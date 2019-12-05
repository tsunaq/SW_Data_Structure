# SW_Data_Structure

## 1. 설계목적
중위 산술 문장을 후위 산술 문장으로 변환

## 2. 요구사항
* 연산자 : =, +, -, *, /, %, blank, ;  
* 토큰 별로 구분  
* delimiter(구별자) 사용   
* 상수 표현  
* Error Message 출력  
  - 이상한 기호(@, # 등)  
  - 이상한 연산자(+*, > 등)  
  - 피연산자가 연속해서 2개 등장  
  - 연산자가 연속해서 2개 등장  
  - 기타 Error Message  
  
## 3. 코드
<pre><code>#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;


// 스택 초기화 함수
void init(StackType *s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType *s)
{
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE-1));
}

// 삽입함수
void push(StackType *s, element item)
{
	if( is_full(s) ) {
	fprintf(stderr,"스택 포화 에러\n");
	return;
	}
	else s->stack[++(s->top)] = item;
}
// 삭제함수
element pop(StackType *s)
{
	if( is_empty(s) ) {
	fprintf(stderr, "스택 공백 에러\n");
	exit(1);
}
else return s->stack[(s->top)--];
}
// 피크함수
element peek(StackType *s)
{
	if( is_empty(s) ) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[s->top];
}


//연산자의 우선순위 반환
int prec(char op)
{
	switch(op)
	{
		case ';' : return 0;
		case '=' : return 1;
		case '(' : case ')' : return 2;
		case '+' : case '-' : return 3;
		case '*' : case '/' : case '%' : return 4;
	}
	return -1;
}
// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char exp[])
{  
	int i=0;
	char ch, top_op;  
	int len=strlen(exp);
	StackType s;

	init(&s);     // 스택 초기화
	for(i=0; i<len; i++){
		ch = exp[i];
		// 연산자이면
		switch(ch){
			case ';': case '=': case '+': case '-': case '*': case '/': // 연산자
			// 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while(!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			printf("%c", pop(&s));
			push(&s, ch);
			break;
			case '(': // 왼쪽 괄호
			push(&s, ch);
			break;
			case ')': // 오른쪽 괄호
			top_op = pop(&s);
			// 왼쪽 괄호를 만날때까지 출력
			while( top_op != '(' ) {
			printf("%c", top_op);
			top_op = pop(&s);
			}
		break;
		default:  // 피연산자

		printf("%c", ch);
		break;
		}
	}
	while( !is_empty(&s) ) // 스택에 저장된 연산자들 출력
	printf("%c", pop(&s));
}
//
int main()
{
	infix_to_postfix("average=((temp1+temp2)*23)/(num1-num2);");
 
	return 0;
}
</code></pre>

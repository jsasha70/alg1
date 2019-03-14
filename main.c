/*

Янович Александр
дз 4

сделал только этот пункт:
5. **Реализовать алгоритм перевода из инфиксной записи арифметического выражения в постфиксную.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long ull;
typedef unsigned char uc;
double enterDouble(char *text);
int enterInt(char *text);
void enterInt2(char *text, int *n, int *m);
void enterString(char *text, char *s, int maxLen);
static int steps;

#define BUF_LEN 1000
static char mem[BUF_LEN * 3 / 2];
static int memIdx = 0;

char* getSubstr(char *s, int len) {
    char *ret = mem + memIdx;
    for(int i=0; i<len; i++) {
        mem[memIdx++] = s[i];
    }
    mem[memIdx++] = 0;
    return ret;
}

char* getWord(char **s) {
    int len = 0;
    while(**s == ' ') (*s)++; // пропускаем пробелы
    switch(**s) {
    case '+': case '-': case '*': case '/': case '(': case ')':
        len = 1;
        break;

    default:
        while((*s)[len] != ' '
              && (*s)[len] != '+'
              && (*s)[len] != '-'
              && (*s)[len] != '*'
              && (*s)[len] != '/'
              && (*s)[len] != '('
              && (*s)[len] != ')'
              && (*s)[len] != 0)
            len++;
    }

    char *ret = getSubstr(*s, len);
    (*s) += len;
    return ret;
}

typedef struct {
    char* buf[BUF_LEN];
    int len, tmp;
} Stack;

void push(Stack *stack, char *s) {
    stack->buf[stack->len++] = s;
}

char* pop(Stack *stack) {
    if(stack->len == 0) return NULL;
    return stack->buf[--stack->len];
}

char* last(Stack *stack) {
    if(stack->len == 0) return NULL;
    return stack->buf[stack->len - 1];
}

void action1(char *next, Stack *texas) {
    push(texas, next);
}

void action2(Stack *calif, Stack *texas, int *stop, int *same) {
    char *s = pop(texas);
    if(s == NULL) {
        printf("invalid expression\n");
        *stop = 1;
        return;
    }
    push(calif, s);
    *same = 1;
}

void action3(Stack *texas, int *stop) {
    char *s = pop(texas);
    if(s == NULL) {
        printf("invalid expression\n");
        *stop = 1;
        return;
    }
}

void action4(int *stop) {
    *stop = 1;
}

void action5(int *stop) {
    printf("invalid expression\n");
    *stop = 1;
}

void task5() {
    char expr[1024];
    enterString("enter expression", expr, BUF_LEN-1);

    Stack calif, texas;
    calif.len = 0;
    texas.len = 0;
    char *expr1 = expr;

    char *next = NULL, *last1;
    int stop = 0, same = 0;
    while(1) {
        steps++;

        if(!same)
            next = getWord(&expr1);

        stop = 0;
        same = 0;
        last1 = last(&texas);
        if(last1 == NULL) last1 = "";

        switch(*next) {
        case 0:
            switch(*last1) {
            case 0:
                action4(&stop); break;
            case '(':
                action5(&stop); break;
            default:
                action2(&calif, &texas, &stop, &same);
            }
            break;

        case '+': case '-':
            switch(*last1) {
            case 0: case '(':
                action1(next, &texas); break;
            default:
                action2(&calif, &texas, &stop, &same);
            }
            break;

        case '*': case '/':
            switch(*last1) {
            case '*': case '/':
                action2(&calif, &texas, &stop, &same); break;
            default:
                action1(next, &texas);
            }
            break;

        case '(':
            action1(next, &texas);
            break;

        case ')':
            switch(*last1) {
            case 0:
                action5(&stop); break;
            case '(':
                action3(&texas, &stop); break;
            default:
                action2(&calif, &texas, &stop, &same);
            }
            break;

        default:
            push(&calif, next);
        }

        if(stop)
            break;
    }

    // выводим полученную формулу
    printf("result:\n");
    for(int i=0; i<calif.len; i++)
        printf("%s ", calif.buf[i]);
    printf("\n");
}


typedef void (*TaskFunc)(void);

int main() {
    TaskFunc tasks[] = {task5};
    char* taskNames[] = {"5"};
    int taskCount = (int)(sizeof(tasks)/sizeof(TaskFunc));
    int taskCount2 = (int)(sizeof(taskNames)/sizeof(char*));

    if(taskCount != taskCount2 || taskCount < 1) {
        printf("array sizes dont match: %d != %d\n", taskCount, taskCount2);
        return 1;
    }

    char task[21];
    int done;
    while(1) {
        printf("\nEnter task name (%s", taskNames[0]);
        for(int i=1; i<taskCount; i++)
            printf(", %s", taskNames[i]);
        printf("); 0 to exit: ");
        scanf("%20s", task);

        if(strcmp(task, "0") == 0) {
            break;
        } else {
            done = 0;
            steps = 0;
            for(int i=0; i<taskCount; i++) {
                if(strcmp(task, taskNames[i]) == 0) {
                    tasks[i]();
                    done = 1;
                    break;
                }
            }

            if(done)
                printf("\nsteps: %d\n", steps);
            else
                printf("invalid task name: %s\n", task);
        }
    };

    return 0;
}

double enterDouble(char *text) {
    printf("%s: ", text);
    double ret;
    scanf("%lf", &ret);
    return ret;
}

int enterInt(char *text) {
    printf("%s: ", text);
    int ret;
    scanf("%d", &ret);
    return ret;
}

void enterInt2(char *text, int *n, int *m) {
    printf("%s: ", text);
    scanf("%d %d", n, m);
}

void enterString(char *text, char *s, int maxLen) {
    if(text != NULL) printf("%s: ", text);

    int i = 0;
    char c;
    while(1) {
        scanf("%c", &c);
        if(c=='\n') {
            if(i>0) break;
            else continue;
        }
        s[i++] = c;
        if(i >= maxLen) break;
    }
    s[i] = 0;
}

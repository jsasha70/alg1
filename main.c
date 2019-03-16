/*

Янович Александр
дз 6

1. Реализовать простейшую хэш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
(я сделал чуть более сложную функцию - придумал сам)

2. Переписать программу, реализующее двоичное дерево поиска.

а) Добавить в него обход дерева различными способами;

б) Реализовать поиск в двоичном дереве поиска;

в) *Добавить в программу обработку командной строки с помощью которой можно указывать
из какого файла считывать данные, каким образом обходить дерево.

3. (не делал) *Разработать базу данных студентов из двух полей “Имя”, “Возраст”, “Табельный номер”
в которой использовать все знания, полученные на уроках.

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


void task1() {
    // Реализовать простейшую хэш-функцию.

    char s[1000];
    enterString("enter string", s, 999);
    int hash = 0;
    int tmp;
    int i = 0;
    unsigned char c;
    while(s[i]) {
        c = (unsigned char) s[i++];
        hash <<= (c & 3);
        hash += c;
        tmp = hash & 0xff0000;
        tmp >>= 16;
        hash = (hash & 0xffff) ^ tmp;
        steps++;
    }
    printf("hash: %d\n", hash);
}

void task2() {
}


typedef void (*TaskFunc)(void);

int main() {
    TaskFunc tasks[] = {task1, task2};
    char* taskNames[] = {"1", "2"};
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

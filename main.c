/*

Янович Александр
дз 3

1. Попробовать оптимизировать пузырьковую сортировку. Сравнить количество операций сравнения
оптимизированной и не оптимизированной программы. Написать функции сортировки,
которые возвращают количество операций.

2. *Реализовать шейкерную сортировку.

3. Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив.
Функция возвращает индекс найденного элемента или -1, если элемент не найден.

4. (не сделал - не хватило времени) *Подсчитать количество операций для каждой из сортировок и сравнить его
с асимптотической сложностью алгоритма.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long ull;
double enterDouble(char *text);
int enterInt(char *text);
void enterString100(char *text, char s[101]);
static int steps;

void randIntArray1000(int size, int *a) {
    // заполнение массива случайными числами от 0 до 1000
    for(int i=0; i<size; i++)
        a[i] = rand()%1001;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int sortPuzyrOrig(int size, int *a) {
    // исходный алгоритм пузырьковой сортировки
    int steps1 = steps;

    int i, j;
    for(i = 0; i < size; i++) {
        for(j = 0; j < size - 1; j ++) {
            steps++;
            if (a[j ] > a[j + 1] ) {
                swap(&a[j ], &a[j + 1] );
            }
        }
    }

    return steps - steps1;
}

int sortPuzyrOptim(int size, int *a) {
    // оптимизированный алгоритм пузырьковой сортировки
    int steps1 = steps;

    int i, j, done;
    for(i = 0; i < size; i++) {
        done = 1;
        for(j = 0; j < size - i - 1; j ++) { // !!! тут главная оптимизация (не проверяем последние числа - они уже на месте) !!!
            steps++;
            if (a[j ] > a[j + 1] ) {
                swap(&a[j ], &a[j + 1] );
                done = 0;
            }
        }

        if(done)
            break;
    }

    return steps - steps1;
}

void printArray(char *text, int size, int *a) {
    if(*text != 0)
        printf("%s\n", text);
    for(int i=0; i<size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void task1() {
    // 1. Попробовать оптимизировать пузырьковую сортировку. Сравнить количество операций сравнения
    // оптимизированной и не оптимизированной программы. Написать функции сортировки,
    // которые возвращают количество операций.

    srand((unsigned int)time(NULL));

    int size = enterInt("enter size of array");
    int rpt = enterInt("enter repeat count");
    if(size<2 || rpt<1) {
        printf("invalid params\n");
        return;
    }

    int *a = calloc((ull)size, sizeof (int));
    int *a1 = calloc((ull)size, sizeof (int));
    int n1, n2;

    for(int i=0; i<rpt; i++) {
        randIntArray1000(size, a);
        if(rpt == 1) printArray("orig:", size, a);

        memcpy(a1, a, sizeof (int) * (ull)size);
        n1 = sortPuzyrOrig(size, a1);
        if(rpt == 1) printArray("sorted:", size, a1);

        memcpy(a1, a, sizeof (int) * (ull)size);
        n2 = sortPuzyrOptim(size, a1);
        if(rpt == 1) printArray("", size, a1);

        if(i == 0) printf("stats:\n");
        printf("%5d %5d\n", n1, n2);
    }
}

int sortShaker(int size, int *a) {
    // алгоритм шейкерной сортировки
    int steps1 = steps;

    int i, j, done;
    int nn = size/2 + size%2; // число проходов
    for(i = 0; i < nn; i++) {
        done = 1;
        for(j = i; j < size - i - 1; j ++) {
            steps++;
            if (a[j ] > a[j + 1] ) {
                swap(&a[j ], &a[j + 1] );
                done = 0;
            }
        }
        if(done) break;

        for(j = size - i - 1; j > i; j --) {
            steps++;
            if (a[j ] < a[j - 1] ) {
                swap(&a[j ], &a[j - 1] );
                done = 0;
            }
        }
        if(done) break;
    }

    return steps - steps1;
}

void task2() {
    // 2. *Реализовать шейкерную сортировку.

    srand((unsigned int)time(NULL));

    int size = enterInt("enter size of array");
    if(size < 2) {
        printf("invalid params\n");
        return;
    }

    int *a = calloc((ull)size, sizeof (int));
    randIntArray1000(size, a);
    printArray("orig:", size, a);

    sortShaker(size, a);
    printArray("sorted:", size, a);
}

int searchBin(int size, int *a, int val) {
    int n1 = 0;
    int n2 = size - 1;
    int n = (n1 + n2) / 2;
    int val1;

    while (n2 > n1) {
        steps++;
//        printf("n1=%d; n=%d; n2=%d\n", n1, n, n2);
        val1 = a[n];
        if(val1 == val)
            break;
        else if(val1 < val)
            n1 = n + 1;
        else
            n2 = n - 1;
        n = (n1 + n2) / 2;
    }

    return a[n] == val ? n : -1;
}

void task3() {
    // 3. Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив.
    // Функция возвращает индекс найденного элемента или -1, если элемент не найден.

    srand((unsigned int)time(NULL));

    int size = enterInt("enter size of array");
    if(size < 2) {
        printf("invalid params\n");
        return;
    }

    int *a = calloc((ull)size, sizeof (int));
    randIntArray1000(size, a);
    sortShaker(size, a);
    printArray("sorted array:", size, a);
    steps = 0;

    int val, steps1, idx;
    while(1) {
        val = enterInt("\nenter value for search (-1 - exit)");
        if(val == -1) break;

        steps1 = steps;
        idx = searchBin(size, a, val);
        printf("found index: %d\nsteps: %d\n", idx, steps - steps1);
    }
}


typedef void (*TaskFunc)(void);

int main() {
    TaskFunc tasks[] = {task1, task2, task3};
    char* taskNames[] = {"1", "2", "3"};
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

void enterString100(char *text, char s[101]) {
    printf("%s: ", text);
    scanf("%100s", s);
}

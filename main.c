/*

Янович Александр
дз 4

1. *Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием
и нахождение количество маршрутов.
Например, карта:
3 3
1 1 1
0 1 0
0 1 0

2. Решить задачу о нахождении длины максимальной последовательности с помощью матрицы.

3. ***Требуется обойти конём шахматную доску размером NxM, пройдя через все поля доски
по одному разу. Здесь алгоритм решения такой же как и в задаче о 8 ферзях.
Разница только в проверке положения коня.

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
    // 1. *Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием
    // и нахождение количество маршрутов.
    // Например, карта:
    // 3 3
    // 1 1 1
    // 0 1 0
    // 0 1 0

    int n, m;
    char lin[256];
    enterInt2("enter length of line and number of lines", &n, &m);
    if(n<2 || m<2 || n>255) {
        printf("invalid params\n");
        return;
    }
    printf("format of a line: 1-s and 0-s without space; for example 11101\n");

    int *map = calloc((ull)(n * m), sizeof(int));

    for(int i = 0; i < m; i++) {
        printf("enter line %d: ", i+1);
        scanf("%255s", lin);
        if(strlen(lin) != (ull)n) {
            printf("line length must be %d\n", n);
            return;
        }
        for(int j = 0; j < n; j++) {
            switch(lin[j]) {
            case '0':
                break;
            case '1':
                map[i * n + j] = 1;
                break;
            default:
                printf("invalid symbol (not 1 or 0)\n");
                return;
            }
        }
    }

    // вычисления делаем прямо в массиве map

    // сначала в первой строке и первом столбце обнуляем элементы после первого нуля
    int founZero = 0;
    for(int i = 0; i < m; i++) {
        steps++;
        if(founZero)
            map[i*n] = 0;
        else if(map[i*n] == 0)
            founZero = 1;
    }
    for(int j = 0; j < n; j++) {
        steps++;
        if(founZero)
            map[j] = 0;
        else if(map[j] == 0)
            founZero = 1;
    }

    // затем проходим последовательно остальные элементы
    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            steps++;
            if(map[i*n + j])
                map[i*n + j] = map[(i-1)*n + j] + map[i*n + (j-1)];
        }
    }

    // выводим результат
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            printf("%3d ", map[i*n + j]);
        }
        printf("\n");
    }
}

void task2() {
    // 2. Решить задачу о нахождении длины максимальной последовательности с помощью матрицы.

    char s1[256], s2[256];
    enterString("enter sequence 1 (chars)", s1, 255);
    enterString("enter sequence 2 (chars)", s2, 255);

    int n = (int)strlen(s1);
    int m = (int)strlen(s2);
    int nn = n + 1;
    int mm = m + 1;
    int *tab = calloc((ull)(nn*mm), sizeof(int));
    int ii, jj, len1, len2;

    for(int i = 0; i < m; i++) {
        ii = i + 1;
        for(int j = 0; j < n; j++) {
            steps++;
            jj = j + 1;
            if(s2[i] == s1[j]) {
                tab[ii*nn + jj] = tab[(ii-1)*nn + (jj-1)] + 1;
            } else {
                len1 = tab[ii*nn + (jj-1)];
                len2 = tab[(ii-1)*nn + jj];
                tab[ii*nn + jj] = len1 > len2 ? len1 : len2;
            }
        }
    }

    printf("\n      ");
    for(int i = 0; i < n; i++)
        printf("%1c  ", s1[i]);
    printf("\n");
    for(int i = 0; i < mm; i++) {
        if(i == 0)
            printf("  ");
        else
            printf("%1c ", s2[i-1]);

        for(int j = 0; j < nn; j++)
            printf("%2d ", tab[i*nn + j]);
        printf("\n");
    }

    // получаем саму последовательность
    ii = mm - 1;
    jj = nn - 1;
    int idx = tab[ii*nn + jj];
    char ss[256];
    memset(ss, 0, 256);
    while(ii>0 && jj>0 && idx>0) {
        steps++;
        if(s1[jj-1] == s2[ii-1]) {
            ss[--idx] = s1[jj-1];
            ii--;
            jj--;
        } else {
            if(tab[(ii-1)*nn + jj] > tab[ii*nn + (jj-1)])
                ii--;
            else
                jj--;
        }
    }

    printf("\nthe subsequence: \"%s\"\n", ss);
}

typedef struct {
    int width, height, boardSize, tmp;
    uc *board;
} boardDescription;

static const int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2}; // для перебора возможных ходов
static const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

static inline uc getCell(int x, int y, boardDescription *b) {
    steps++;
    return b->board[x + y*b->width];
}

static inline uc* getCellAddr(int x, int y, boardDescription *b) {
    steps++;
    return b->board + x + y*b->width;
}

static inline int isFreeCell(int x, int y, boardDescription *b) {
    return x<0 || x>=b->width || y<0 || y>=b->height ? 0 : (getCell(x, y, b) == 0);
}

int nextStep(int x, int y, uc count, boardDescription *b) {
    if(count >= b->boardSize)
        return 1;
    count++;

    int x1, y1;
    for(int i=0; i < 8; i++) {
        x1 = x + dx[i];
        y1 = y + dy[i];
        if(isFreeCell(x1, y1, b)) {
            *getCellAddr(x1, y1, b) = count;
            if(nextStep(x1, y1, count, b)) return 1;
            *getCellAddr(x1, y1, b) = 0;
        }
    }
    return 0;
}

int firstStep(boardDescription *b) {
    for(int y=0; y < b->height; y++) {
        for(int x=0; x < b->width; x++) {
            *getCellAddr(x, y, b) = 1;
            if(nextStep(x, y, 1, b)) return 1;
            *getCellAddr(x, y, b) = 0;
        }
    }
    return 0;
}

void task3() {
    // 3. ***Требуется обойти конём шахматную доску размером NxM, пройдя через все поля доски
    // по одному разу. Здесь алгоритм решения такой же как и в задаче о 8 ферзях.
    // Разница только в проверке положения коня.

    boardDescription b;

    enterInt2("enter board size (width space height)", &b.width, &b.height);
    if(b.width<3 || b.height<3 || b.width*b.height>255) {
        printf("invalid params\n");
        return;
    }

    b.boardSize = b.width * b.height;
    b.board = calloc((ull)b.boardSize, sizeof(uc));

    int ret = firstStep(&b);
    if(ret) {
        for(int y=0; y < b.height; y++) {
            for(int x=0; x < b.width; x++) {
                printf("%3d ", b.board[x + y*b.width]);
            }
            printf("\n");
        }
    } else {
        printf("solution not found\n");
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

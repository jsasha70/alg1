// Янович Александр
// дз 2

#include <stdio.h>
#include <string.h>

typedef unsigned long long ull;
double enterDouble(char *text);
int enterInt(char *text);
void enterString100(char *text, char s[101]);
static int steps;

ull parceDec(ull add, char* str) {
    // парсинг записи десятичного числа (проверка на посторонние символы типа минуса не производится)
    steps++;
    return *str == 0 ? add : parceDec(add*10 + ((unsigned char)(*str) - '0'), str + 1);
}

char* getBin(ull num, char* str) {
    // получение записи в двоичном виде
    steps++;
    char* s = num > 1 ? getBin(num >> 1, str) : str;
    *s = '0' + (char)(num & 1);
    return ++s;
}

void task1() {
    // Реализовать функцию перевода из 10 системы в двоичную используя рекурсию.
    char d[101];
    enterString100("enter decimal number", d);

    // парсинг записи десятичного числа (проверка на посторонние символы типа минуса не производится)
    ull num = parceDec(0, d);
    printf("got: %lld\n", num);

    // получение записи в двоичном виде
    char bin[101];
    *getBin(num, bin) = 0; // после числа записываем признак конца строки
    printf("binary representation: %s\n", bin);
}

void task2a() {
    // Реализовать функцию возведения числа a в степень b: без рекурсии
    double a, res=1;
    int b;
    printf("enter A and B (separated by space): ");
    scanf("%lf %d", &a, &b);

    if(b > 0) {
        for(int i=0; i < b; i++) {
            steps++;
            res *= a;
        }
    } else if(b < 0) {
        for(int i=0; i < -b; i++) {
            steps++;
            res /= a;
        }
    } else if(a > -0.0000001 && a < 0.0000001) {
        printf("undetermined result: 0^0\n");
        return;
    }

    printf("%lf^%d = %lf\n", a, b, res);
}

double powerRec(double a, int b) {
    steps++;
    if(b == 0) {
        return 1;
    } else if (b > 0) {
        return a * powerRec(a, b-1);
    } else { // b < 0
        return powerRec(a, b+1) / a;
    }
}

void task2b() {
    // Реализовать функцию возведения числа a в степень b: рекурсивно
    double a;
    int b;
    printf("enter A and B (separated by space): ");
    scanf("%lf %d", &a, &b);
    if(b == 0 && a > -0.0000001 && a < 0.0000001) {
        printf("undetermined result: 0^0\n");
        return;
    } else {
        printf("%lf^%d = %lf\n", a, b, powerRec(a, b));
    }
}

double powerRec2(double a, int b) {
    steps++;
    if(b == 0) {
        return 1;
    } else if (b > 0) {
        if(b%2 == 0) {
            double a2 = powerRec2(a, b/2);
            return a2 * a2;
        } else {
            return a * powerRec2(a, b-1);
        }
    } else { // b < 0
        if((-b)%2 == 0) {
            double a2 = powerRec2(a, b/2);
            return 1 / (a2 * a2);
        } else {
            return powerRec2(a, b+1) / a;
        }
    }
}

void task2c() {
    // Реализовать функцию возведения числа a в степень b: *рекурсивно, используя свойство чётности степени
    double a;
    int b;
    printf("enter A and B (separated by space): ");
    scanf("%lf %d", &a, &b);
    if(b == 0 && a > -0.0000001 && a < 0.0000001) {
        printf("undetermined result: 0^0\n");
        return;
    } else {
        printf("%lf^%d = %lf\n", a, b, powerRec2(a, b));
    }
}

#define NN1 3
#define NN2 20

void task3a() {
    // Исполнитель Калькулятор ... Сколько существует программ, которые число 3 преобразуют в число 20: с использованием массива
    int progCount[NN2 + 1];
    memset(progCount, 0, sizeof (progCount));
    progCount[NN1] = 1;

    int i1;
    for(int i=NN1+1; i<=NN2; i++) {
        steps++;

        i1 = i - 1;
        if(i1 >= NN1) {
            progCount[i] += progCount[i1];
        }

        if(i%2 == 0) {
            i1 = i / 2;
            if(i1 >= NN1) {
                progCount[i] += progCount[i1];
            }
        }
    }

    printf("prog count: %d\n", progCount[NN2]);
}

int progCountRec(int n1, int n2) {
    steps++;

    if(n2 == n1)
        return 1;

    int ret = 0;

    int n = n2 - 1;
    if(n >= n1)
        ret += progCountRec(n1, n);

    if(n2%2 == 0) {
        n = n2 / 2;
        if(n >= n1)
            ret += progCountRec(n1, n);
    }

    return ret;
}

void task3b() {
    // Исполнитель Калькулятор ... Сколько существует программ, которые число 3 преобразуют в число 20: с использованием рекурсии
    printf("prog count: %d\n", progCountRec(NN1, NN2));
}

typedef void (*TaskFunc)(void);

int main() {
    TaskFunc tasks[] = {task1, task2a, task2b, task2c, task3a, task3b};
    char* taskNames[] = {"1", "2a", "2b", "2c", "3a", "3b"};
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

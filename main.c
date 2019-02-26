// автор - Янович Александр

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int x, y;
} PointInt;

typedef struct {
    double x, y;
} PointDouble;

double enterDouble(char *text);
int enterInt(char *text);
PointInt enterPointInt(char *text);
PointDouble enterPointDouble(char *text);

void task1() {
    // Ввести вес и рост человека. Рассчитать и вывести индекс массы тела по формуле I=m/(h*h); где m-масса тела в килограммах, h - рост в метрах.
    double m, h, k;
    m = enterDouble("enter weight (kg)");
    h = enterDouble("enter height (m)");
    if(h > 0){
        k = m / (h*h);
        printf("weight index is %.2lf\n", k);
    } else {
        printf("invalid height\n");
    }
}

int max2(int n1, int n2) { // max of 2 integers
    return n1 > n2 ? n1 : n2;
}

void task2() {
    // Найти максимальное из четырех чисел. Массивы не использовать.
    int n1, n2, n3, n4;
    printf("enter 4 integers, separated by space: ");
    scanf("%d %d %d %d", &n1, &n2, &n3, &n4);
    int max = max2(max2(n1, n2), max2(n3, n4));
    printf("max number of %d, %d, %d, %d is %d\n", n1, n2, n3, n4, max);
}

void task3() {
    // Написать программу обмена значениями двух целочисленных переменных
    int a, b;
    printf("enter 2 integers, separated by space: ");
    scanf("%d %d", &a, &b);
    printf("got: a=%d, b=%d\n", a, b);
    a ^= b;
    b ^= a;
    a ^= b;
    printf("result: a=%d, b=%d\n", a, b);
}

void task4() {
    // Написать программу нахождения корней заданного квадратного уравнения.
    double a, b, c;
    printf("enter a, b, c of equation a*x^2+b*x+c=0, separated by space: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    if(a>-0.000001 && a<0.000001) {
        printf("this is not square equation\n");
        return;
    }
    double d = b*b - 4*a*c;
    double dd = sqrt(d);
    if(dd>-0.000001 && dd<0.000001) {
        double x = -b/(2*a);
        printf("the equation has the single root: %lf\n", x);
    } else {
        double x1 = (-b + dd) / (2*a);
        double x2 = (-b - dd) / (2*a);
        printf("the roots of the equation are %lf and %lf\n", x1, x2);
    }
}

void task5() {
    // С клавиатуры вводится номер месяца. Требуется определить, к какому времени года он относится.
    int m = enterInt("enter month number (1-12)");
    if(m < 1) m += ((12-m)/12)*12; // сделали номер месяца не меньше 1
    if(m > 12) m = (m-1)%12 + 1; // привели номер месяца к диапазону 1-12
    char *s;
    switch ((m/3) % 4) {
    case 0: s = "winter"; break;
    case 1: s = "spring"; break;
    case 2: s = "summer"; break;
    default: s = "autumn"; break;
    }
    printf("month number %d is %s\n", m, s);
}

void task6() {
    // Ввести возраст человека (от 1 до 150 лет) и вывести его вместе с последующим словом «год», «года» или «лет».
    int a = enterInt("enter age");
    if(a<1 || a>150) {
        printf("invalid age\n");
        return;
    }
    char *s;
    int low = a%10;
    int low2 = a%100;
    if(low2>=10 && low2<=20) s = "let";
    else if(low == 1) s = "god";
    else if(low>=2 && low<=4) s = "goda";
    else s = "let";
    printf("%d %s\n", a, s);
}

void task7() {
    // С клавиатуры вводятся числовые координаты двух полей шахматной доски (x1,y1,x2,y2). Требуется определить, относятся ли к поля к одному цвету или нет.
    PointInt p1 = enterPointInt("enter point 1");
    PointInt p2 = enterPointInt("enter point 2");
    if(p1.x<1 || p1.x>8 || p1.y<1 || p1.y>8 || p2.x<1 || p2.x>8 || p2.y<1 || p2.y>8) {
        printf("X and Y must be from 1 to 8\n");
        return;
    }
    if((p1.x+p1.y%2)%2 == (p2.x+p2.y%2)%2) printf("same color\n");
    else printf("different color\n");
}

void task8() {
    // Ввести a и b и вывести квадраты и кубы чисел от a до b.
    printf("enter A and B separated by space: ");
    int a, b;
    scanf("%d %d", &a, &b);
    if(a > b) {
        printf("A must not be greater than B\n");
        return;
    }
    int n, n2, n3;
    n = a;
    while(n <= b) {
        n2 = n*n;
        n3 = n2*n;
        printf("%d^2 = %d; %d^3 = %d\n", n, n2, n, n3);
        n++;
    }
}

void task9() {
    // Даны целые положительные числа N и K. Используя только операции сложения и вычитания, найти частное от деления нацело N на K, а также остаток от этого деления.
    printf("enter N and K separated by space: ");
    int n, k;
    scanf("%d %d", &n, &k);
    if(n<1 || k<1) {
        printf("the numbers must be positive\n");
        return;
    }
    int d=0, r=n;
    while(r>=k) {
        r -= k;
        d++;
    }
    printf("%d/%d = %d; %d%%%d=%d\n", n, k, d, n, k, r);
}

void task10() {
    // Дано целое число N (> 0). С помощью операций деления нацело и взятия остатка от деления определить,
    // имеются ли в записи числа N нечетные цифры. Если имеются, то вывести True, если нет — вывести False.
    int n = enterInt("enter a number");
    if(n < 1) {
        printf("the number must be positive\n");
        return;
    }
    int nn=n, d, ret=0;
    do {
        d = nn%10;
        nn /= 10;
        if(d%2 == 1) {
            ret = 1;
            break;
        }
    } while(nn > 0);
    if(ret) printf("True\n");
    else printf("False\n");
}

void task11() {
    // С клавиатуры вводятся числа, пока не будет введен 0. Подсчитать среднее арифметическое всех положительных четных чисел, оканчивающихся на 8.
    int count=0, sum=0, n;
    while(1) {
        n = enterInt("enter next number (0 to finish)");
        if(n == 0) break;
        if(n>0 && n%10==8) {
            count++;
            sum += n;
        }
    }
    if(!count) {
        printf("nothing entered\n");
        return;
    }
    double ret = ((double)sum) / count;
    printf("%lf\n", ret);
}

int max3(int n1, int n2, int n3) { // max of 3 integers
    int ret = n1;
    if(ret < n2) ret = n2;
    if(ret < n3) ret = n3;
    return ret;
}

void task12() {
    // Написать функцию нахождения максимального из трех чисел.
    printf("enter 3 numbers, separated by space: ");
    int n1, n2, n3;
    scanf("%d %d %d", &n1, &n2, &n3);
    printf("max: %d\n", max3(n1, n2, n3));
}

static int doneRandInit = 0;
int rand100() {
    if(!doneRandInit) {
        srand((unsigned int)time(NULL));
        doneRandInit = 1;
    }
    return rand()%100 + 1;
}

void task13() {
    // Написать функцию, генерирующую случайное число от 1 до 100.
    printf("random (1-100): %d\n", rand100());
    printf("random (1-100): %d\n", rand100());
    printf("random (1-100): %d\n", rand100());
}

void task14() {
    // Автоморфные числа. Натуральное число называется автоморфным, если оно равно последним цифрам своего квадрата.
    // Например, 25 \ :sup: 2 = 625. Напишите программу, которая вводит натуральное число N
    // и выводит на экран все автоморфные числа, не превосходящие N.
    int n = enterInt("enter a number");
    if(n < 1) {
        printf("the number must be positive\n");
        return;
    }
    printf("automorph numbers from 1 to %d:\n", n);
    int dd = 1;
    for(int i=1; i <= n; i++) {
//        dd = 1; так будет чуть меньше умножений на 10
        while(i/dd > 0) dd *= 10;
        if((i*i)%dd == i)
            printf("%d\n", i);
    }
}

typedef void (*TaskFunc)(void);

int main() {
    int task;
    TaskFunc tasks[] = {task1, task2, task3, task4, task5, task6, task7, task8, task9, task10, task11, task12, task13, task14};
    int taskCount = (int)(sizeof(tasks)/sizeof(TaskFunc));


    while(1) {
        printf("\nEnter task number (1-%d, 0 to exit): ", taskCount);
        scanf("%d", &task);

        if(task == 0) {
            break;
        } else if (task>=1 && task<=taskCount) {
            tasks[task-1]();
        } else {
            printf("invalid task number: %d\n", task);
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

PointInt enterPointInt(char *text) {
    printf("%s (X Y separated by space): ", text);
    PointInt p;
    scanf("%d %d", &p.x, &p.y);
    return p;
}

PointDouble enterPointDouble(char *text) {
    printf("%s (X Y separated by space): ", text);
    PointDouble p;
    scanf("%lf %lf", &p.x, &p.y);
    return p;
}

/*

Янович Александр

-------------------------------------------------------------------------------------------------------------------

дз 1
дз 2

-------------------------------------------------------------------------------------------------------------------

дз 3:

1. Попробовать оптимизировать пузырьковую сортировку. Сравнить количество операций сравнения
оптимизированной и не оптимизированной программы. Написать функции сортировки,
которые возвращают количество операций.

2. *Реализовать шейкерную сортировку.

3. Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив.
Функция возвращает индекс найденного элемента или -1, если элемент не найден.

-------------------------------------------------------------------------------------------------------------------

дз 4:

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

-------------------------------------------------------------------------------------------------------------------

дз 5:

5. **Реализовать алгоритм перевода из инфиксной записи арифметического выражения в постфиксную.

-------------------------------------------------------------------------------------------------------------------

дз 6:

1. Реализовать простейшую хэш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
(я сделал чуть более сложную функцию - придумал сам)

-------------------------------------------------------------------------------------------------------------------

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    int x, y;
} PointInt;

typedef struct {
    double x, y;
} PointDouble;

typedef unsigned long long ull;
typedef unsigned char uc;
double enterDouble(char *text);
int enterInt(char *text);
void enterInt2(char *text, int *n, int *m);
void enterString(char *text, char *s, int maxLen);
PointInt enterPointInt(char *text);
PointDouble enterPointDouble(char *text);
static int steps;


void task11() {
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

void task12() {
    // Найти максимальное из четырех чисел. Массивы не использовать.
    int n1, n2, n3, n4;
    printf("enter 4 integers, separated by space: ");
    scanf("%d %d %d %d", &n1, &n2, &n3, &n4);
    int max = max2(max2(n1, n2), max2(n3, n4));
    printf("max number of %d, %d, %d, %d is %d\n", n1, n2, n3, n4, max);
}

void task13() {
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

void task14() {
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

void task15() {
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

void task16() {
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

void task17() {
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

void task18() {
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

void task19() {
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

void task110() {
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

void task111() {
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

void task112() {
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

void task113() {
    // Написать функцию, генерирующую случайное число от 1 до 100.
    printf("random (1-100): %d\n", rand100());
    printf("random (1-100): %d\n", rand100());
    printf("random (1-100): %d\n", rand100());
}

void task114() {
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

void task21() {
    // Реализовать функцию перевода из 10 системы в двоичную используя рекурсию.
    char d[101];
    enterString("enter decimal number", d, 100);

    // парсинг записи десятичного числа (проверка на посторонние символы типа минуса не производится)
    ull num = parceDec(0, d);
    printf("got: %lld\n", num);

    // получение записи в двоичном виде
    char bin[101];
    *getBin(num, bin) = 0; // после числа записываем признак конца строки
    printf("binary representation: %s\n", bin);
}

void task22a() {
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

void task22b() {
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

void task22c() {
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

void task23a() {
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

void task23b() {
    // Исполнитель Калькулятор ... Сколько существует программ, которые число 3 преобразуют в число 20: с использованием рекурсии
    printf("prog count: %d\n", progCountRec(NN1, NN2));
}

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

void task31() {
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

void task32() {
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

void task33() {
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

void task41() {
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

void task42() {
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

void task43() {
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

int nextStepV(int x, int y, uc count, boardDescription *b) {
    int lastStep = 0;
    if(count == b->boardSize - 1) lastStep = 1;

    if(count >= b->boardSize)
        return 1;

    count++;
    int x1, y1, x2, y2;

    // для каждого допустимого поля определяем число допустимых ходов (0 - ход недопустимый)
    int ss[8];
    for(int i=0; i < 8; i++) {
        ss[i] = 0;
        x1 = x + dx[i];
        y1 = y + dy[i];
        if(isFreeCell(x1, y1, b)) {
            for(int j=0; j < 8; j++) {
                x2 = x1 + dx[j];
                y2 = y1 + dy[j];
                if(isFreeCell(x2, y2, b))
                    ss[i]++;
            }
            if(ss[i] == 0 && lastStep) // на последнем ходе следующего хода быть не может
                ss[i] = 1;
        }
    }

    // находим минимум допустимых ходов
    int minSteps = 0;
    for(int i=0; i < 8; i++) {
        if(minSteps == 0 || (ss[i] > 0 && minSteps > ss[i]))
            minSteps = ss[i];
    }

    if(minSteps == 0)
        return 0;

    for(int i=0; i < 8; i++) {
        if(ss[i] == minSteps) {
            x1 = x + dx[i];
            y1 = y + dy[i];
            *getCellAddr(x1, y1, b) = count;
            if(nextStepV(x1, y1, count, b)) return 1;
            *getCellAddr(x1, y1, b) = 0;
        }
    }
    return 0;
}

int firstStepV(boardDescription *b) {
    for(int y=0; y < b->height; y++) {
        for(int x=0; x < b->width; x++) {
            *getCellAddr(x, y, b) = 1;
            if(nextStepV(x, y, 1, b)) return 1;
            *getCellAddr(x, y, b) = 0;
        }
    }
    return 0;
}

void task43v() {
    // Правило Варнсдорфа:
    // При обходе доски конь следует на то поле, с которого можно пойти
    // на минимальное число ещё не пройденных полей.
    // Если таких полей несколько, то можно пойти на любое из них.

    boardDescription b;

    enterInt2("enter board size (width space height)", &b.width, &b.height);
    if(b.width<3 || b.height<3 || b.width*b.height>255) {
        printf("invalid params\n");
        return;
    }

    b.boardSize = b.width * b.height;
    b.board = calloc((ull)b.boardSize, sizeof(uc));

    int ret = firstStepV(&b);
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

void task55() {
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

void task61() {
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



typedef void (*TaskFunc)(void);

int main() {
    TaskFunc tasks[] = {task11, task12, task13, task14, task15, task16, task17, task18, task19, task110, task111, task112, task113, task114,
        task21, task22a, task22b, task22c, task23a, task23b, task31, task32, task33, task41, task42, task43, task43v, task55, task61};
    char* taskNames[] = {"1-1", "1-2", "1-3", "1-4", "1-5", "1-6", "1-7", "1-8", "1-9", "1-10", "1-11", "1-12", "1-13", "1-14",
        "2-1", "2-2a", "2-2b", "2-2c", "2-3a", "2-3b", "3-1", "3-2", "3-3", "4-1", "4-2", "4-3", "4-3v", "5-5", "6-1"};
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

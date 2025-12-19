#include <stdio.h>
#include <ctype.h>
#include <string.h>

char opStack[100];
long long valStack[100];
int opTop = -1, valTop = -1;

void pushOp(char x) {
    opStack[++opTop] = x;
}

char popOp() {
    return opStack[opTop--];
}

void pushVal(long long x) {
    valStack[++valTop] = x;
}

long long popVal() {
    return valStack[valTop--];
}

int precedence(char x) {
    if (x == '^') return 3;
    if (x == '*' || x == '/') return 2;
    if (x == '+' || x == '-') return 1;
    return 0;
}

long long power(long long a, long long b) {
    long long res = 1;
    while (b--) res *= a;
    return res;
}

int main() {
    char infix[100], postfix[200];
    int i = 0, k = 0;

    scanf("%s", infix);

    while (infix[i]) {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
        }
        else if (infix[i] == '(') {
            pushOp(infix[i++]);
        }
        else if (infix[i] == ')') {
            while (opStack[opTop] != '(') {
                postfix[k++] = popOp();
                postfix[k++] = ' ';
            }
            popOp();
            i++;
        }
        else {
            while (opTop != -1 && precedence(opStack[opTop]) >= precedence(infix[i])) {
                postfix[k++] = popOp();
                postfix[k++] = ' ';
            }
            pushOp(infix[i++]);
        }
    }

    while (opTop != -1) {
        postfix[k++] = popOp();
        postfix[k++] = ' ';
    }

    postfix[k] = '\0';

    printf("Postfix: %s\n", postfix);

    i = 0;
    while (postfix[i]) {
        if (isdigit(postfix[i])) {
            long long num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i++] - '0');
            }
            pushVal(num);
        }
        else if (postfix[i] == ' ') {
            i++;
        }
        else {
            long long b = popVal();
            long long a = popVal();
            switch (postfix[i]) {
                case '+': pushVal(a + b); break;
                case '-': pushVal(a - b); break;
                case '*': pushVal(a * b); break;
                case '/': pushVal(a / b); break;
                case '^': pushVal(power(a, b)); break;
            }
            i++;
        }
    }

    printf("Result: %lld\n", popVal());
    return 0;
}

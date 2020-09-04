#include <cstdio>

using namespace std;

const int MAX = 200;
int t;
char c;
int val[MAX], vlen;
int op[MAX], olen;

void insert(int a) {
    while (olen && op[olen - 1] == 3) {
        a = !a;
        --olen;
    }
    val[vlen++] = a;
}

void cal() {
    int a = val[--vlen];
    int b = val[--vlen];
    int cop = op[--olen];
    insert((cop == 1 ? a | b : a & b));
}

int main() {
    t = 1;
    while ((c = getchar()) != EOF) {
        vlen = olen = 0;
        do {
            if (c == '(') op[olen++] = 0;
            else if (c == ')') {
                while (olen && op[olen - 1] != 0) cal();
                --olen;
                insert(val[--vlen]);
            } else if (c == '!') op[olen++] = 3;
            else if (c == '&') {
                while (olen && op[olen - 1] >= 2) cal();
                op[olen++] = 2;
            } else if (c == '|') {
                while (olen && op[olen - 1] >= 1) cal();
                op[olen++] = 1;
            } else if (c == 'V' || c == 'F') insert(c == 'V' ? 1 : 0);
        } while ((c = getchar()) != EOF && c != '\n');
        while (olen) cal();
        printf("Expression %d: %c\n", t, val[0] ? 'V' : 'F');
        ++t;
    }

    return 0;
}
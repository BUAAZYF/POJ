#include <cstdio>

using namespace std;

const int MAX = 20;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int a[MAX], b[MAX], left, right;

int main() {
    for (int i = 0; i < MAX; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    left = 0;
    for (int i = 1; i < MAX; ++i) {
        if (a[i - 1] == 1) {
            ++left;
            a[i - 1] = 0;
            a[i] = 1 - a[i];
            if (i + 1 < MAX) a[i + 1] = 1 - a[i + 1];
        }
    }
    right = 0;
    for (int i = MAX - 2; i >= 0; --i) {
        if (b[i + 1] == 1) {
            ++right;
            b[i + 1] = 0;
            b[i] = 1 - b[i];
            if (i - 1 >= 0) b[i - 1] = 1 - b[i - 1];
        }
    }
    printf("%d\n", min(left, right));

    return 0;
};
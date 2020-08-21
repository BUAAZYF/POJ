#include <cstdio>

using namespace std;

const int MAX = 1000005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int low, high, mid, n, ans;
char s[MAX];
int nxt[MAX];

void compute_nxt(char* pat, int n) {
    int len = 0;
    nxt[0] = 0;
    int i = 1;
    while (i < n) {
        if (pat[i] == pat[len]) {
            ++len;
            nxt[i] = len;
            ++i;
        } else {
            if (len != 0) len = nxt[len - 1];
            else {
                nxt[i] = 0;
                ++i;
            }
        }
    }
}

int main() {
    while((s[0] = getchar()) != EOF && s[0] != '.') {
        n = 1;
        while ((s[n] = getchar()) != EOF && s[n] != '\n') ++n;
        s[n] = '\0';
        compute_nxt(s, n);
        printf("%d\n", n % (n - nxt[n - 1]) == 0 ? n / (n - nxt[n - 1]) : 1);
    }
    
    return 0;
}
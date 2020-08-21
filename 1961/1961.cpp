#include <cstdio>

using namespace std;

const int MAX = 1000005;

int t, n;
char s[MAX];
int nxt[MAX];

void solve(char* pat, int n) {
    int len = 0;
    nxt[0] = 0;
    int i = 1;
    while (i < n) {
        if (pat[i] == pat[len]) {
            ++len;
            nxt[i] = len;
            ++i;
            if (i % (i - nxt[i - 1]) == 0 && i / (i - nxt[i - 1]) > 1)
                printf("%d %d\n", i, i / (i - nxt[i - 1]));
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
    t = 1;
    while (scanf("%d\n", &n) != EOF && n) {
        for(int i = 0;i < n; ++i) s[i] = getchar();
        s[n] = '\0';
        printf("Test case #%d\n", t++);
        solve(s, n);
        putchar('\n');
    }

    return 0;
}
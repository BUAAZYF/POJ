#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 10005;
const int MAXC = 80;

char s[MAX][MAXC];
int next[MAX];
int r, c, mr, mc;

bool cmp(int x, int y) {
    for (int i = 0; i < mr; ++i)
        if (s[i][x] != s[i][y]) return false;
    return true;
}

int main() {
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; ++i) scanf("%s", s[i]);
    next[0] = 0;
    for (int i = 1; i < r; ++i) {
        int t = next[i - 1];
        while (t && strcmp(s[t], s[i])) t = next[t - 1];
        if (strcmp(s[t], s[i]) == 0) next[i] = t + 1;
        else next[i] = 0;
    }
    int x = r - next[r - 1];
    if (x % (x - next[x - 1]) == 0) mr = x - next[x - 1];
    else mr = x;
    next[0] = 0;
    for (int i = 1; i < c; ++i) {
        int t = next[i - 1];
        while (t && (!cmp(i, t))) t = next[t - 1];
        if (cmp(i, t)) next[i] = t + 1;
        else next[i] = 0;
    }
    x = c - next[c - 1];
    if (x % (x - next[x - 1]) == 0) mc = x - next[x - 1];
    else mc = x;
    printf("%d\n", mc * mr);
    return 0;
}
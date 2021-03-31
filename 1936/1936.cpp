#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 100005;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

char s[MAX], t[MAX];

bool issubseq() {
    int m = strlen(s), n = strlen(t);
    if (m > n) return false;
    int j = 0;
    for (int i = 0; i < m; ++i) {
        while (j < n && s[i] != t[j]) ++j;
        if (j == n) return false;
        ++j;
    }
    return true;
}

int main() {
    while (scanf("%s %s", s, t) != EOF) {
        printf("%s\n", issubseq() ? "Yes" : "No");
    }
    return 0;
}
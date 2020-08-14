#include <cstdio>

using namespace std;

const int MAXS = 10005;
const int MAXT = 1000005;
const int PRIME = 31;
const int MOD = 1e9 + 7;

int N, S, T, ans;
char c, s[MAXS], t[MAXT];
int next[MAXS];


void computeLPSArray(char* pat, int M) {
    int len = 0;
    next[0] = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            ++len;
            next[i] = len;
            ++i;
        } else {
            if (len != 0) len = next[len - 1];
            else {
                next[i] = 0;
                ++i;
            }
        }
    }
}

void KMPSearch(char* pat, char* txt) {
    computeLPSArray(pat, S);
    int i = 0, j = 0;
    while (i < T) {
        if (pat[j] == txt[i]) {
            ++j;
            ++i;
        }
        if (j == S) {
            ++ans;
            j = next[j - 1];
        } else if (i < T && pat[j] != txt[i]) {
            if (j != 0) j = next[j - 1];
            else ++i;
        }
    }
}

int main() {
    scanf("%d\n", &N);
    while (N--) {
        ans = 0;
        S = T = 0;
        while ((c = getchar()) != EOF && c != '\n') s[S++] = c;
        while ((c = getchar()) != EOF && c != '\n') t[T++] = c;
        KMPSearch(s, t);
        printf("%d\n", ans);
    }

    return 0;
}
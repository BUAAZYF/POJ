#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 400005;

int n;
char s[MAX];
int nxt[MAX];
vector<int> ans;

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
            if (len != 0)
                len = nxt[len - 1];
            else {
                nxt[i] = 0;
                ++i;
            }
        }
    }
}

int main() {
    while ((s[0] = getchar()) != EOF) {
        n = 1;
        while ((s[n] = getchar()) != EOF && s[n] != '\n') ++n;
        s[n] = '\0';
        compute_nxt(s, n);
        ans.clear();
        for (int i = n - 1; nxt[i] > 0; i = nxt[i] - 1)
            ans.push_back(nxt[i]);
        for (int i = (int)ans.size() - 1; i >= 0; --i) printf("%d ", ans[i]);
        printf("%d\n", n);
    }

    return 0;
}
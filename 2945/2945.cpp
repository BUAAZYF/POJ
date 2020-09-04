#include <cstdio>
#include <string>
#include <cstring>
#include <map>

using namespace std;

const int MAX = 20001;
const int MAXC = 22;

int n, m;
char cur[MAXC];
string s;
map<string, int> cnt;
int ans[MAX];

int main() {
    while (scanf("%d%d", &n, &m) != EOF && n) {
        cnt.clear();
        for (int i = 0; i < n; ++i) {
            scanf("%s", cur);
            s = string(cur);
            if (cnt.find(s) == cnt.end()) cnt[s] = 0;
            ++cnt[s];
        }
        memset(ans, 0, sizeof(ans));
        for (map<string, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) ++ans[it->second];
        for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
    }
    
    return 0;
}
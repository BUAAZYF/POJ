#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 505;

int N, M;
int a[MAX], b[MAX];
vector<int> gcis[MAX], ans;

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) scanf("%d", &a[i]);
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d", &b[i]);
        gcis[i].clear();
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (a[i] == b[j]) {
                if (gcis[j].empty()) gcis[j].push_back(a[i]);
                for (int k = 0; k < j; ++k) {
                    if (b[k] < b[j] && gcis[k].size() >= gcis[j].size()) {
                        gcis[j] = gcis[k];
                        gcis[j].push_back(b[j]);
                    }
                }
            }
        }
    }
    ans.clear();
    for (int j = 0; j < M; ++j)
        if (gcis[j].size() > ans.size()) ans = gcis[j];

    printf("%d\n", (int)ans.size());
    if (!ans.empty()) {
        for (int i = 0; i < ans.size() - 1; ++i) printf("%d ", ans[i]);
        printf("%d\n", ans[ans.size() - 1]);
    } else{
        printf("\n");
    }

    return 0;
}
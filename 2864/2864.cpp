#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 105;
int N, D, attend;
bool found;
int cnt[MAX];

int main() {
    while (scanf("%d%d", &N, &D) != EOF && N) {
        memset(cnt, 0, sizeof(cnt));
        found = false;
        for (int i = 0; i < D; ++i) {
            for (int j = 0; j < N; ++j) {
                scanf("%d", &attend);
                if(attend) ++cnt[j];
            }
        }
        for (int i = 0; i < D; ++i) {
            if (cnt[i] == D) {
                found = true;
                break;
            }
        }
        printf("%s\n", found ? "yes" : "no");
    }

    return 0;
}
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 1005;

int n, k, ans, sz, less, total;
int left[MAXN], right[MAXN];
int light[MAXN], heavy[MAXN];
char op;
bool same[MAXN];

int main(){
    // freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    memset(same, false, MAXN * sizeof(bool));
    memset(light, 0, MAXN * sizeof(int));
    memset(heavy, 0, MAXN * sizeof(int));
    total = ans = 0;
    while (k-- > 0){
        scanf("%d", &sz);
        for (int i = 0; i < sz; ++i) scanf("%d", &left[i]);
        for (int i = 0; i < sz; ++i) scanf("%d", &right[i]);
        scanf("\n%c", &op);
        if (op == '=') {
            for (int i = 0; i < sz; ++i) same[left[i]] = true;
            for (int i = 0; i < sz; ++i) same[right[i]] = true;
        }
        else if (op == '>'){
            ++total;
            for (int i = 0; i < sz; ++i) ++heavy[left[i]];
            for (int i = 0; i < sz; ++i) ++light[right[i]];
        }
        else{
            ++total;
            for (int i = 0; i < sz; ++i) ++light[left[i]];
            for (int i = 0; i < sz; ++i) ++heavy[right[i]];
        }
    }
    for (int i = 1; i <= n; ++i){
        if (same[i]) continue;
        if (light[i] == total || heavy[i] == total){
            if (ans != 0){
                ans = 0;
                break;
            }
            ans = i;
        }
    }
    printf("%d\n", ans);

    return 0;
}
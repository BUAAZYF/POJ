#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 300;
const int INF = 0x3f3f3f3f;

int main() {
    int n, points, times, submissions, cnt, ans_cnt = 0, ans_points = INF;
    char name[MAX], ans_name[MAX];
    scanf("%d", &n);
    while (n--) {
        scanf("%s", name);
        cnt = points = 0;
        for (int i = 0; i < 4; ++i) {
            scanf("%d%d", &submissions, &times);
            if (times == 0) continue;
            ++cnt;
            points += times + 20 * (submissions - 1);
        }
        if (cnt > ans_cnt || cnt == ans_cnt && points < ans_points) {
            ans_cnt = cnt;
            ans_points = points;
            strcpy(ans_name, name);
        }
    }
    printf("%s %d %d\n", ans_name, ans_cnt, ans_points);

    return 0;
}
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAX = 1000005;
const int MAXL = 10;
const int MAXT = 1005;

int t, n, m, x;
char op[MAXL];
short team[MAX];
queue<int> team_que, member_que[MAXT];

int main() {
    t = 1;
    while (scanf("%d", &n) != EOF && n) {
        while (!team_que.empty()) team_que.pop();
        for (int i = 1; i <= n; ++i) {
            while (!member_que[i].empty()) member_que[i].pop();
            scanf("%d", &m);
            while (m--) {
                scanf("%d", &x);
                team[x] = i;
            }
        }
        printf("Scenario #%d\n", t++);
        while (scanf("%s", op) != EOF && strcmp(op, "STOP") != 0) {
            if (strcmp(op, "ENQUEUE") == 0) {
                scanf("%d", &x);
                if (member_que[team[x]].empty()) team_que.push(team[x]);
                member_que[team[x]].push(x);
            } else {
                printf("%d\n", member_que[team_que.front()].front());
                member_que[team_que.front()].pop();
                if (member_que[team_que.front()].empty()) team_que.pop();
            }
            getchar();
        }
        printf("\n");
    }

    return 0;
}
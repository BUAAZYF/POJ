#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

const int MAX = 10005;

int maxcost, policy, rem_len, idx, cost, rem_cnt, rem_item;
bool rem[MAX];
char op;
map<int, int> process;

int main() {
    while (scanf("%d%d", &maxcost, &rem_len) != EOF) {
        policy = rem_cnt = 1;
        memset(rem, false, sizeof(rem));
        process.clear();
        while (rem_len--) {
            scanf("%d", &idx);
            rem[idx] = true;
        }
        getchar();
        while ((op = getchar()) != 'e') {
            if (op == 'a') {
                scanf("%d", &cost);
                if (cost <= maxcost) {
                    if (process.find(cost) == process.end()) process[cost] = 0;
                    ++process[cost];
                }
            } else if (op == 'p') {
                scanf("%d", &policy);
            } else {
                if (process.empty()) {
                    if (rem[rem_cnt]) printf("-1\n");
                } else {
                    map<int, int>::iterator it;
                    if (policy == 1)
                        it = process.begin();
                    else {
                        it = process.end();
                        --it;
                    }
                    rem_item = it->first;
                    --process[rem_item];
                    if (process[rem_item] == 0) process.erase(rem_item);
                    if (rem[rem_cnt]) printf("%d\n", rem_item);
                }
                ++rem_cnt;
            }
            getchar();
        }
        putchar('\n');
    }

    return 0;
}
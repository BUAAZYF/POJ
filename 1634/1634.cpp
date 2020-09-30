#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX = 30005;

int n, m, q, id;
struct emp{
    int id, salary, height, boss, subs;
    friend bool operator<(const emp& a, const emp& b){
        return a.salary > b.salary;
    }
}emps[MAX];

int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%d%d", &m, &q);
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &emps[i].id, &emps[i].salary, &emps[i].height);
            emps[i].boss = -1;
            emps[i].subs = 0;
        }
        sort(emps, emps + m);
        for (int i = m - 1; i > 0; --i) {
            int b = i - 1;
            while (emps[i].height > emps[b].height) --b;
            emps[i].boss = b;
        }
        for (int i = m - 1; i >= 0; --i) 
            emps[emps[i].boss].subs += 1 + emps[i].subs;
        while (q--) {
            scanf("%d", &id);
            for (int i = 0; i < m; ++i) {
                if (id == emps[i].id) {
                    printf("%d %d\n", emps[i].boss == -1 ? 0 : emps[emps[i].boss].id, emps[i].subs);
                    break;
                }
            }
        }

    }

    return 0;
}
#include <cstdio>
#include <stack>

using namespace std;

int N, cur, idx;
bool conflict;
stack<int> stk;

int main() {
    while (scanf("%d", &N) && N) {
        while (scanf("%d", &cur) && cur) {
            conflict = false;
            idx = 1;
            while (!stk.empty()) stk.pop();
            while (idx < cur) stk.push(idx++);
            ++idx;
            for (int i = 1; i < N; ++i) {
                scanf("%d", &cur);
                if (conflict) continue;
                if (cur == idx) ++idx;
                else if (!stk.empty() && cur == stk.top()) stk.pop();
                else if (idx < cur) {
                    while (idx < cur) stk.push(idx++);
                    ++idx;
                } else conflict = true;
            }
            printf("%s\n", conflict ? "No" : "Yes");
        }
        printf("\n");
    }

    return 0;
}
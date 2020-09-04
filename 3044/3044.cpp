#include <cstdio>
#include <stack>

using namespace std;

int N, W, x, y;
stack<int> skyline;
int ans;

int main() {
    scanf("%d%d", &N, &W);
    ans = 0;
    for (int i = 0; i < N; ++i) {
        scanf("%d%d", &x, &y);
        if (y == 0) {
            ans += skyline.size();
            while(!skyline.empty()) skyline.pop();
            continue;
        }
        while (!skyline.empty() && skyline.top() > y) {
            ++ans;
            skyline.pop();
        }
        if (skyline.empty() || !skyline.empty() && skyline.top() < y) skyline.push(y);
    }
    ans += skyline.size();
    while(!skyline.empty()) skyline.pop();
    printf("%d\n", ans);

    return 0;
}
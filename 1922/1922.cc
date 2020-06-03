#include <cmath>
#include <iostream>

using namespace std;

int main() {
    int dst = 4500;
    int n, speed, start;
    while (true) {
        int ans = 0x7fffffff;
        cin >> n;
        if (n == 0) break;
        for (int i = 0; i < n; ++i) {
            cin >> speed >> start;
            if (start < 0) continue;
            ans = min(ans, int(ceil(dst * 3.6 / speed)) + start);
        }
        cout << ans << endl;
    }

    return 0;
}
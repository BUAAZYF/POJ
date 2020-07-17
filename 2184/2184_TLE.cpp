#include <algorithm>
#include <cstdio>
#include <cstring>
#include<set>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 105;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n;
Pr cow;
set<Pr> cur, nxt;

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        nxt = cur;
        scanf("%d%d", &cow.first, &cow.second);
        if(cow.first <= 0 && cow.second <= 0) continue;
        for(set<Pr>::reverse_iterator it = cur.rbegin(); it != cur.rend(); ++it){
            if(it->first + cow.first <= 0 && it->second + cow.second <= 0) break;
            nxt.insert(make_pair(it->first + cow.first, it->second + cow.second));
        }
        nxt.insert(cow);
        swap(cur, nxt);
    }
    int ans = 0;
    for(set<Pr>::iterator it = cur.begin(); it != cur.end(); ++it){
        if(it->first >= 0 && it->second >= 0) ans = max(ans, it->first + it->second);
    }
    printf("%d\n", ans);


    return 0;
}
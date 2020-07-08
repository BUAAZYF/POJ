#include <algorithm>
#include <cstdio>

using namespace std;

typedef pair<short, short> Pr;

const int MAX = 30005;

Pr parent[MAX];
short size[MAX];

void init_unionset(){
    for(int i = 1; i < MAX; ++i){
        parent[i] = make_pair<short, short>(i, 0);
        size[i] = 1;
    }
}

Pr find(int x){
    if (x != parent[x].first) {
        short len = parent[x].second;
        parent[x] = find(parent[x].first);
        parent[x].second += len;
    }
    return parent[x];
}

void merge(short x, short y){
    x = find(x).first;
    y = find(y).first;
    if (x != y){
        parent[x] = make_pair(y, size[y]);
        size[y] += size[x];
    }
}

long long P;
int x, y, dis;
char op;

int main() {
    // freopen("in.txt", "r", stdin);
    init_unionset();
    scanf("%lld\n", &P);
    while (P-- > 0) {
        scanf("%c", &op);
        if(op == 'M'){
            scanf("%d%d\n", &x, &y);
            merge(x, y);
        } else {
            scanf("%d\n", &x);
            printf("%d\n", (int)find(x).second);
        }

    }

    return 0;
}
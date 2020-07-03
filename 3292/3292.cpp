#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int MAX = (1000000 + 5) / 4;

int n;
int ishprimes[MAX];
vector<int> hprimes;
vector<int> semihprimes;

void precomputeprime() {
    memset(ishprimes, 0, MAX * sizeof(int));
    ishprimes[0] = 1;
    for (int i = 1; i <= MAX; ++i) {
        if (ishprimes[i] == 0) {
            ishprimes[i] = (i << 2) + 1;
            hprimes.push_back((i << 2) + 1);
        }
        for (int j = 0; j < hprimes.size() && hprimes[j] <= ishprimes[i] && ((i << 2) + 1) * hprimes[j] < MAX * 4; ++j)
            ishprimes[((i << 2) + 1) * hprimes[j] >> 2] = hprimes[j];
    }
}

void computesemihprime() {
    for (int i = 1; i < MAX; ++i) {
        if (ishprimes[i] == (i << 2) + 1) continue;
        int div = ((i << 2) + 1) / ishprimes[i];
        if(div != 1 && (div - 1) % 4 == 0 && ishprimes[div >> 2] == div) semihprimes.push_back((i << 2) + 1);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    precomputeprime();
    computesemihprime();
    while (scanf("%d", &n) != EOF && n != 0) {
        vector<int>::iterator pos = upper_bound(semihprimes.begin(), semihprimes.end(), n);
        printf("%d %d\n", n, (int)(pos - semihprimes.begin()));
    }

    return 0;
}
#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 10005;

int x;
bool notprime[MAX];
vector<int> primes, presum;
int vaild[MAX];

int main() {
    for (int i = 2; i < MAX; ++i) {
        if (notprime[i]) continue;
        primes.push_back(i);
        for (int j = i * 2; j < MAX; j += i) notprime[j] = true;
    }
    presum.resize(primes.size() + 1);
    presum[0] = 0;
    for (int i = 0; i < primes.size(); ++i) presum[i + 1] = presum[i] + primes[i];
    for (int i = 0; i < presum.size(); ++i) {
        for (int j = i + 1; j < presum.size(); ++j) {
            if (presum[j] - presum[i] >= MAX) break;
            ++vaild[presum[j] - presum[i]];
        }
    }
    while (scanf("%d", &x) != EOF && x) {
        printf("%d\n", vaild[x]);
    }

    return 0;
}
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> names;

int N, W, S;

int main() {
    scanf("%d", &N);
    names.resize(N);
    for (int i = 0; i < N; ++i) cin >> names[i];
    cin >> W;
    getchar();
    cin >> S;
    int cur = W - 1;
    while (!names.empty()) {
        cur = (cur + S - 1) % names.size();
        cout << names[cur] << endl;
        names.erase(cur + names.begin());
    }

    return 0;
}
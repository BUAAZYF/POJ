#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int MAX = 15;

int cnt, n, i, j;
string names[MAX];

int main() {
    cnt = 1;
    while (scanf("%d\n", &n) != EOF && n) {
        i = 0, j = n - 1;
        for(int k = 0; k < n; ++k){
            if (k % 2 == 0) cin >> names[i++];
            else cin >> names[j--];
        }
        cout << "SET " << cnt << endl;
        for(int k = 0; k < n; ++k) cout << names[k] << endl;
        ++cnt;
}

    return 0;
}
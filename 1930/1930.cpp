#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

const int INF = 0x3f3f3f3f;
int p10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
                     100000000, 1000000000};

string s;
int n, num, den, rnum, rden, g;

int main() {
    while (cin >> s && s != "0") {
        rden = INF;
        n = s.size() - 5;
        for (int i = 0; i < n; ++i) {
            num = atoi(s.substr(i + 2).c_str()) +
                  (p10[n - i] - 1) * atoi(s.substr(2, i).c_str());
            den = (p10[n - i] - 1) * p10[i];
            g = gcd(num, den);
            num /= g;
            den /= g;
            if (den < rden) {
                rnum = num;
                rden = den;
            }
        }
        cout << rnum << '/' << rden << endl;
    }

    return 0;
}
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int MAX = 100;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

string a, b;
vector<string> fibs;

string caladd(string num1, string num2) {
    int n1 = num1.size(), n2 = num2.size();
    string res(max(n1, n2), '0');
    int i = 0, j = 0, carry = 0;
    while (i < n1 || j < n2) {
        res[i] = carry;
        if (i < n1) res[i] += num1[i] - '0';
        if (j < n2) res[i] += num2[j] - '0';
        carry = res[i] >= 10 ? 1 : 0;
        res[i] = res[i] % 10 + '0';
        ++i;
        ++j;
    }
    if (carry == 1) res += '1';
    return res;
}

bool cmp(const string num1, const string num2) {
    if (num1.size() < num2.size()) return true;
    if (num1.size() == num2.size()) {
        if (num1 == num2) return false;
        for (int i = num1.size() - 1; i >= 0; --i){
            if (num1[i] < num2[i]) return true;
            if (num1[i] > num2[i]) return false;
        }
        return true;
    }
    return false;
}

void calfibs() {
    fibs.clear();
    fibs.push_back("1");
    fibs.push_back("2");
    int i = 0;
    while (fibs[fibs.size() - 1].size() <= MAX) {
        fibs.push_back(caladd(fibs[i], fibs[i + 1]));
        ++i;
    }
}

int main() {
    calfibs();
    while (cin >> a >> b && !(a == "0" && b == "0")) {
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        cout << upper_bound(fibs.begin(), fibs.end(), b, cmp) - 
        lower_bound(fibs.begin(), fibs.end(), a, cmp)  << endl;
    }

    return 0;
}
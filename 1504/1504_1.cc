#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    string a, b, sum;
    while (n-- > 0) {
        ostringstream ostr;
        cin >> a >> b;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int na = atoi(a.c_str()), nb = atoi(b.c_str());
        ostr << na + nb;
        sum = ostr.str();
        reverse(sum.begin(), sum.end());
        cout << atoi(sum.c_str()) << endl;
    }
}
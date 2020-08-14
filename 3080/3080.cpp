#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int MAXM = 10;

int t, m, cl;
string genes[MAXM], common;

string findcommon(string& a, string& b) {
    string ans = "";
    for (int len = a.size(); len >= 3; --len) {
        if (ans != "") break;
        for (int i = 0; i <= a.size() - len; ++i)
            if (b.find(a.substr(i, len)) != string::npos && (ans == "" || ans > a.substr(i, len)))
                ans = a.substr(i, len);
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d\n", &m);
        for (int i = 0; i < m; ++i) cin >> genes[i];
        common = genes[0];
        for (int i = 1; i < m; ++i) {
            common = findcommon(common, genes[i]);
            if (common == "") break;
        }
        if (common == "")
            cout << "no significant commonalities" << endl;
        else
            cout << common << endl;
    }

    return 0;
}
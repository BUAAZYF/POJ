#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int N = 1999;

int main() {
    string s = "", cur;
    while (getline(cin, cur)) s += cur;
    int pos = 0;
    while (s.size() > 1) {
        pos = (pos + N - 1 + s.size()) % s.size();
        s.erase(s.begin() + pos);
        if (pos == s.size()) pos = 0;
    }
    if (s.empty() || s[0] == ' ') cout << "No\n";
    else if (s[0] == '?') cout << "Yes\n";
    else cout << "No comments\n";

    return 0;
}
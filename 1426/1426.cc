#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) != EOF && n != 0) {
        if (n == 1) {
            printf("%d\n", 1);
            continue;
        }
        vector<string> reminder(n, "");
        reminder[0] = "0", reminder[1] = "1";
        bool found = false;
        while (!found) {
            for (int i = 1; i < n; ++i) {
                if (reminder[i] == "" or reminder[i] == "u") continue;
                if ((i * 10 + 1) % n == 0) {
                    cout << reminder[i] << "1" << endl;
                    found = true;
                    break;
                }
                if (reminder[(i * 10 + 1) % n] == "") reminder[(i * 10 + 1) % n] = reminder[i] + "1";
                if ((i * 10) % n == 0) {
                    cout << reminder[i] << "0" << endl;
                    found = true;
                    break;
                }
                if (reminder[(i * 10) % n] == "") reminder[(i * 10) % n] = reminder[i] + "0";
                reminder[i] = "u";
            }
        }
    }
}
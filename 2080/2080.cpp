#include <cstdio>

using namespace std;

const char* days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int month_days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int start_day = 6;

int n, year, month, day, dayofweek;

bool isleap(int x) {
    if (x % 100 == 0) return x % 400 == 0;
    return x % 4 == 0;
}

int main() {
    while (scanf("%d", &n) != EOF && n != -1) {
        dayofweek = (start_day + n) % 7;
        ++n;
        year = 2000;
        while (n > 365 + isleap(year)) {
            n -= (365 + isleap(year));
            ++year;
        }
        month = 1;
        int add = isleap(year);
        while (n > month_days[month] + (month == 2 ? add : 0)) {
            n -= (month_days[month] + (month == 2 ? add : 0));
            ++month;
        }
        day = n;
        printf("%d-", year);
        if (month < 10) printf("0");
        printf("%d-", month);
        if (day < 10) printf("0");
        printf("%d %s\n", day, days[dayofweek]);
    }

    return 0;
}
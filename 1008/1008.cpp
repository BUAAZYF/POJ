#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int ZONE = 32;

const string HaabMonth[19] = {"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"};
const string TzolkinDay[20] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};
const int haab_year = 365;
const int tzolkin_year = 13 * 20;

int n, numday, month, year, days;
string month_name, day_name;

int cal_habb_month(string& month_name) {
    int ans = -1;
    for (int i = 0; i < 19; ++i) {
        if (month_name == HaabMonth[i]) {
            ans = i;
            break;
        }
    }
    return ans;
}

int main() {
    scanf("%d\n", &n);
    printf("%d\n", n);
    while (n--) {
        cin >> numday;
        getchar();
        cin >> month_name >> year;
        days = 0;
        if (year > 0) days += year * haab_year;
        month = cal_habb_month(month_name);
        days += month * 20;
        days += numday;
        year = days / tzolkin_year;
        days %= tzolkin_year;
        month = days % 13 + 1;
        day_name = TzolkinDay[days % 20];
        cout << month  << " " << day_name << ' ' << year << endl;
    }

    return 0;
}
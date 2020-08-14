#include <cstdio>
#include <cstring>

using namespace std;

const char DAYOFWEEK[7][4] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
const char MONTH[12][4] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
const int MONTHDAYS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char TIMEZONE[6][4] = {"UT", "GMT", "EDT", "CDT", "MDT", "PDT"};
const int TIMEZONESHIFT[6] = {0, 0, -4, -5, -6, -7};

bool isleapyear(int x) {
    if (x % 100 == 0) return x % 400 == 0;
    return x % 4 == 0;
}

char cur[4];
int year, month, day, hours, minutes, seconds, dayweek;
int zonesign, hours_shift, minutes_shift;

int main() {
    freopen("in.txt", "r", stdin);
    while ((cur[0] = getchar()) != EOF) {
        cur[3] = '\0';
        for (int i = 1; i < 3; ++i) cur[i] = getchar();
        for (int i = 0; i < 7; ++i) {
            if (strcmp(DAYOFWEEK[i], cur) == 0) {
                dayweek = i;
                break;
            }
        }
        getchar();
        scanf("%d", &day);
        getchar();
        for (int i = 0; i < 3; ++i) cur[i] = getchar();
        for (int i = 0; i < 12; ++i) {
            if (strcmp(MONTH[i], cur) == 0) {
                month = i;
                break;
            }
        }
        getchar();
        for (int i = 0; i < 3; ++i) cur[i] = getchar();
        year = (cur[0] - '0') * 10 + (cur[1] - '0');
        if (cur[2] == ' ')
            year += 1900;
        else
            year = year * 100 + (cur[2] - '0') * 10 + (getchar() - '0');
        scanf("%d", &hours);
        getchar();
        scanf("%d", &minutes);
        getchar();
        scanf("%d", &seconds);
        getchar();
        cur[0] = getchar();
        hours_shift = minutes_shift = 0;
        if (cur[0] == '+' || cur[0] == '-') {
            zonesign = cur[0] == '-' ? 1 : -1;
            hours_shift = zonesign * ((getchar() - '0') * 10 + (getchar() - '0'));
            minutes_shift = zonesign * ((getchar() - '0') * 10 + (getchar() - '0'));
        } else {
            if (cur[0] == 'U') {
                cur[1] = getchar();
                cur[2] = '\0';
            } else {
                cur[1] = getchar();
                cur[2] = getchar();
                cur[3] = '\0';
            }
            for (int i = 0; i < 6; ++i) {
                if (strcmp(TIMEZONE[i], cur) == 0) {
                    hours_shift = -TIMEZONESHIFT[i];
                    break;
                }
            }
        }
        getchar();
        hours_shift += 3;
        minutes += minutes_shift;
        if (minutes < 0) {
            minutes += 60;
            --hours;
        }
        if (minutes >= 60) {
            minutes -= 60;
            ++hours;
        }
        hours += hours_shift;
        if (hours < 0) {
            hours += 24;
            --day;
            dayweek = (dayweek - 1 + 7) % 7;
        }
        if (hours >= 24) {
            hours -= 24;
            ++day;
            dayweek = (dayweek + 1 + 7) % 7;
        }
        if (day == 0) {
            if (month == 0) {
                --year;
                month = 11;
                day = MONTHDAYS[month];
            } else {
                --month;
                day = MONTHDAYS[month];
                if (month == 1 && isleapyear(year)) ++day;
            }
        } else if (day > MONTHDAYS[month] && !(month == 1 && isleapyear(year))) {
            day = 1;
            ++month;
            if (month == 12) {
                month = 0;
                ++year;
            }
        }

        printf("%s, ", DAYOFWEEK[dayweek]);
        if (day < 10) printf("0");
        printf("%d %s ", day, MONTH[month]);
        if (year < 1000) printf("0");
        if (year < 100) printf("0");
        if (year < 10) printf("0");
        printf("%d ", year);
        if (hours < 10) printf("0");
        printf("%d:", hours);
        if (minutes < 10) printf("0");
        printf("%d:", minutes);
        if (seconds < 10) printf("0");
        printf("%d", seconds);
        printf(" +0300\n");
    }

    return 0;
}
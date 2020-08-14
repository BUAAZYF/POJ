#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

const int ZONE = 32;

const char TIMEZONE[ZONE][5] = {"UTC", "GMT", "BST", "IST", "WET", "WEST", "CET", "CEST", "EET", "EEST",
                                "MSK", "MSD", "AST", "ADT", "NST", "NDT", "EST", "EDT", "CST", "CDT", 
                                "MST", "MDT", "PST", "PDT", "HST", "AKST", "AKDT", "AEST", "AEDT", 
                                "ACST", "ACDT", "AWST"};
const double TIMEZONESHIFT[ZONE] = {0, 0, 1, 1, 0, 1, 1, 2, 2, 3, 3, 4, -4, -3, -3.5, -2.5, -5, -4, -6,
                                    -5, -7, -6, -8, -7, -10, -9, -8, 10, 11, 9.5, 10.5, 8};

char cur[5];
int T, hours, minutes, zone_idx;

int findzone(char* name) {
    for (int i = 0; i < ZONE; ++i)
        if (strcmp(cur, TIMEZONE[i]) == 0) return i;
    return -1;
}

int main() {
    scanf("%d\n", &T);
    for(int t = 0; t < T; ++t) {
        hours = minutes = 0;
        for (int i = 0; i < 4; ++i) cur[i] = '\0';
        cur[0] = getchar();
        if (cur[0] == 'n') {
            hours = 12;
            minutes = 0;
            for (int i = 0; i < 3; ++i) getchar();
        } else if (cur[0] == 'm') {
            hours = 24;
            minutes = 0;
            for (int i = 0; i < 7; ++i) getchar();
        } else {
            hours = cur[0] - '0';
            cur[0] = getchar();
            if (cur[0] != ':') {
                hours = hours * 10 + cur[0] - '0';
                getchar();
            }
            minutes = (getchar() - '0') * 10 + getchar() - '0';
            getchar();
            cur[0] = getchar();
            if (cur[0] == 'p' && hours < 12) hours += 12;
            if (cur[0] == 'a' && hours == 12) hours = 0;
            for (int i = 0; i < 3; ++i) getchar();
        }
        getchar();
        for (int i = 0; i < 4; ++i) cur[i] = getchar();
        if (cur[3] != ' ') {
            getchar();
            cur[4] = '\0';
        } else cur[3] = '\0';
        zone_idx = findzone(cur);
        hours -= int(TIMEZONESHIFT[zone_idx]);
        if (int(TIMEZONESHIFT[zone_idx]) != TIMEZONESHIFT[zone_idx]) minutes -= (TIMEZONESHIFT[zone_idx] >= 0 ? 1 : -1) * 30;
        for (int i = 0; i < 4; ++i) cur[i] = getchar();
        if (isupper(cur[3])) {
            char c;
            while( (c = getchar()) != EOF && c != '\n') ;
            cur[4] = '\0';
        } else cur[3] = '\0';
        zone_idx = findzone(cur);
        hours += int(TIMEZONESHIFT[zone_idx]);
        if (int(TIMEZONESHIFT[zone_idx]) != TIMEZONESHIFT[zone_idx]) minutes += (TIMEZONESHIFT[zone_idx] >= 0 ? 1 : -1) * 30;
        while (minutes >= 60) {
            minutes -= 60;
            ++hours;
        }
        while (minutes < 0) {
            minutes += 60;
            --hours;
        }
        while (hours < 0) hours += 24;
        hours %= 24;
        if (hours == 0 && minutes == 0) printf("midnight");
        else if (hours == 12 && minutes == 0) printf("noon");
        else {
            printf("%d:", hours % 12 == 0 ? 12 : hours % 12);
            if (minutes < 10) printf("0");
            printf("%d ", minutes);
            printf("%s", hours >= 12 ? "p.m." : "a.m.");
        }
        if (t < T - 1) putchar('\n');
    }

    return 0;
}
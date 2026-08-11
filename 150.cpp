#include <iostream>
#include <string>
#include <map>
using namespace std;

string monthName[13] = {
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

map<string, int> monthNum = {
    {"January", 1}, {"February", 2}, {"March", 3}, {"April", 4},
    {"May", 5}, {"June", 6}, {"July", 7}, {"August", 8},
    {"September", 9}, {"October", 10}, {"November", 11}, {"December", 12}
};

map<string, int> dayNum = {
    {"Sunday", 0}, {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3},
    {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}
};

long long gregorianJDN(int y, int m, int d) {
    int a = (14 - m) / 12;
    y += 4800 - a;
    m += 12 * a - 3;

    return d + (153 * m + 2) / 5 + 365LL * y + y / 4 - y / 100 + y / 400 - 32045;
}

long long julianJDN(int y, int m, int d) {
    int a = (14 - m) / 12;
    y += 4800 - a;
    m += 12 * a - 3;

    return d + (153 * m + 2) / 5 + 365LL * y + y / 4 - 32083;
}

void jdnToGregorian(long long jd, int &y, int &m, int &d) {
    long long a = jd + 32044;
    long long b = (4 * a + 3) / 146097;
    long long c = a - (146097 * b) / 4;
    long long e = (4 * c + 3) / 1461;
    long long f = c - (1461 * e) / 4;
    long long g = (5 * f + 2) / 153;

    d = f - (153 * g + 2) / 5 + 1;
    m = g + 3 - 12 * (g / 10);
    y = 100 * b + e - 4800 + g / 10;
}

void jdnToJulian(long long jd, int &y, int &m, int &d) {
    long long c = jd + 32082;
    long long e = (4 * c + 3) / 1461;
    long long f = c - (1461 * e) / 4;
    long long g = (5 * f + 2) / 153;

    d = f - (153 * g + 2) / 5 + 1;
    m = g + 3 - 12 * (g / 10);
    y = e - 4800 + g / 10;
}

int weekday(long long jd) {
    return (jd + 1) % 7;
}

int main() {
    string day, month;

    while (cin >> day) {
        if (day == "#") break;

        int d, y;
        cin >> d >> month >> y;

        int m = monthNum[month];
        int w = dayNum[day];

        long long g = gregorianJDN(y, m, d);
        long long j = julianJDN(y, m, d);

        int yy, mm, dd;

        if (weekday(g) == w) {
            jdnToJulian(g, yy, mm, dd);
            cout << day << " " << dd << "* " << monthName[mm] << " " << yy << '\n';
        } else {
            jdnToGregorian(j, yy, mm, dd);
            cout << day << " " << dd << " " << monthName[mm] << " " << yy << '\n';
        }
    }

    return 0;
}

#include <iostream>
#include <string>

using namespace std;

int readNumber(const string& text, int start, int length) {
    int value = 0;
    for (int i = 0; i < length; ++i) {
        value = value * 10 + text[start + i] - '0';
    }
    return value;
}

bool isLeapYear(int year) {
    return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

bool hasValidDate(const string& number) {
    const int days[13] = {0, 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31};
    int year = readNumber(number, 6, 4);
    int month = readNumber(number, 10, 2);
    int day = readNumber(number, 12, 2);

    if (year < 1900 || year > 2011 || month < 1 || month > 12) {
        return false;
    }
    int lastDay = days[month] + (month == 2 && isLeapYear(year));
    return 1 <= day && day <= lastDay;
}

bool hasValidChecksum(const string& number) {
    int value = 0;
    for (char digit : number) {
        value *= 2;
        value += digit == 'X' ? 10 : digit - '0';
    }
    return value % 11 == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string number;
    int regionCount;
    cin >> number >> regionCount;

    bool knownRegion = false;
    for (int i = 0; i < regionCount; ++i) {
        string region;
        cin >> region;
        if (number.compare(0, 6, region) == 0) {
            knownRegion = true;
        }
    }

    if (!knownRegion || !hasValidDate(number) || !hasValidChecksum(number)) {
        cout << 'I';
        return 0;
    }

    int order = readNumber(number, 14, 3);
    cout << (order == 0 ? 'I' : order % 2 == 0 ? 'F' : 'M');
    return 0;
}

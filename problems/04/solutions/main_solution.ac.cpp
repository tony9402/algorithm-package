#include<iostream>
#include<set>

using namespace std;

int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
set<string> region;

bool is_leap_year(int year) {
    return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

int get_valid_days(int year, int month) {
    return month == 2 && is_leap_year(year) ? (days[month] + 1) : days[month];
}

bool valid_region(string code) {
    return region.find(code) != region.end();
}

bool valid_birth_code(string code) {
    int year = stoi(code.substr(0, 4));
    int month = stoi(code.substr(4, 2));
    int day = stoi(code.substr(6));
    if(!(1900 <= year && year <= 2011)) return false;
    if(!(1 <= month && month <= 12)) return false;
    if(!(1 <= day && day <= get_valid_days(year, month))) return false;
    return true;
}

char order_code(string code) {
    int code_integer = stoi(code);
    if(code_integer == 0) return 'I';
    return code_integer % 2 == 0 ? 'F' : 'M';
}

bool checksum(string code) {
    int x = 0;
    for(char a: code) {
        x *= 2;
        if(a == 'X') x += 10;
        else x += a - '0';
    }
    return x % 11 == 1;
}

int main() {
    // 빠른 입출력을 위해 사용됩니다.
    ios::sync_with_stdio(false);
    cin.tie(0);

    string sn;
    cin >> sn;

    int N;
    cin >> N;

    for(int i = 0; i < N; ++i) {
        string region_str;
        cin >> region_str;
        region.insert(region_str);
    }

    bool flag = valid_region(sn.substr(0, 6));
    flag &= valid_birth_code(sn.substr(6, 8));
    flag &= checksum(sn);

    cout << (flag ? order_code(sn.substr(14, 3)) : 'I');

    return 0;
}
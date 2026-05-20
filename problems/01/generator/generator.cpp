// #include "testlib.h"
#include "../../testlib.h"
#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/*
 * 윤년 확인
 */
bool is_leap_year(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int calculate_checksum(int sum) {
    return ((1 - sum) % 11 + 11) % 11;
}

/*
 * 지역 코드 생성
 */
vector<string> generate_codes(int N) {
    set<string> codes;
    while((int)codes.size() < N) {
        string code = rnd.next("[1-9]{1,1}[0-9]{5,5}");
        codes.insert(code);
    }
    vector<string> code_for_shuffle(codes.begin(), codes.end());
    shuffle(code_for_shuffle.begin(), code_for_shuffle.end());
    return code_for_shuffle;
}

/*
 * 올바른 YYYYMMDD 생성
 */
string generate_birth() {
    int year = rnd.next(1900, 2011);
    int month = rnd.next(1, 12);
    int offset = 0;
    if(is_leap_year(year) && month == 2) offset = 1;
    int day = rnd.next(1, days[month] + offset);

    ostringstream oss;

    oss << setfill('0')
        << setw(4) << year
        << setw(2) << month
        << setw(2) << day;

    return oss.str();
}

/*
 * 남자, 여자 순서코드 생성
 * 남자: 홀수
 * 여자: 짝수
 */
string sequence_code(bool male) {
    int code = rnd.next(1, 999);

    if(male) code |= 1;
    else code &= ~1;

    if(code == 0) code += 2;

    ostringstream oss;
    oss << setfill('0') << setw(3) << code;
    return oss.str();
}

/*
 * 올바른 코드, 올바르지 않은 코드 상관없이 랜덤
 */
void generate_random(
    int min_N = 1,
    int max_N = 50
) {
    string token = rnd.next("[0-9]{17,17}");
    if(rnd.next(0, 1) == 1) token += 'X';
    else token += rnd.next("[0-9]{1,1}");
    cout << token << '\n';

    int N = rnd.next(min_N, max_N);
    cout << N << '\n';
    vector<string> codes = generate_codes(N);
    for(string code: codes) cout << code << '\n';
}

/*
 * 올바른 신분증 번호 출력
 */
void generate_valid(
    bool male,
    int min_N = 1,
    int max_N = 50
) {
    int N = rnd.next(min_N, max_N);
    vector<string> codes = generate_codes(N);
    string birth = generate_birth();
    string seq_code = sequence_code(male);

    int idx = rnd.next(0, N - 1);

    string token = codes[idx] + birth + seq_code;

    ensure(token.size() == 17);

    int sum = 0;
    for(int i = 0; i < 17; ++i) {
        int x = (int)token[i] - 48;
        int w = 1 << (17 - i);
        sum = (sum + x * w % 11) % 11;
    }
    int checksum = calculate_checksum(sum);
    if(checksum == 10) token += 'X';
    else token += (char)(checksum + '0');

    ensure((sum + checksum) % 11 == 1);

    cout << token << '\n';
    cout << N << '\n';
    for(string code: codes) cout << code << '\n';
}

/*
 * 윤년인데 29일 체크를 잘못한 경우
 */
void generate_edgecase1(
    bool male,
    int min_N = 1,
    int max_N = 50
) {
    int N = rnd.next(min_N, max_N);
    vector<string> codes = generate_codes(N);

    string birth;
    { // generate birth (edge case)
        vector<int> leap_years;
        for(int year = 1900; year <= 2011; ++year) {
            if(is_leap_year(year)) leap_years.push_back(year);
        }
        int idx = rnd.next(0, (int)leap_years.size() - 1);
        int year = leap_years[idx];
        int month = 2;
        int day = 29;

        ostringstream oss;

        oss << setfill('0')
            << setw(4) << year
            << setw(2) << month
            << setw(2) << day;

        birth = oss.str();
    }

    string seq_code = sequence_code(male);

    int idx = rnd.next(0, N - 1);

    string token = codes[idx] + birth + seq_code;

    ensure(token.size() == 17);

    int sum = 0;
    for(int i = 0; i < 17; ++i) {
        int x = (int)token[i] - 48;
        int w = 1 << (17 - i);
        sum = (sum + x * w % 11) % 11;
    }
    int checksum = calculate_checksum(sum);
    if(checksum == 10) token += 'X';
    else token += (char)(checksum + '0');

    ensure((sum + checksum) % 11 == 1);

    cout << token << '\n';
    cout << N << '\n';
    for(string code: codes) cout << code << '\n';
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);

    int min_N = opt<int>("minN");
    int max_N = opt<int>("maxN");
    bool male = opt<bool>("male", true);
    string mode = opt<string>("mode", "random");

    if(mode == "random") {
        generate_random(min_N, max_N);
    }
    else if(mode == "edgecase1") {
        generate_edgecase1(male, min_N, max_N);
    }
    else {
        generate_valid(male, min_N, max_N);
    }

    return 0;
}

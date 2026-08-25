#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    set<string> names;
    map<string, int> occurrences;
    while (n--) {
        string name;
        cin >> name;

        string alias = name;
        for (int length = 1; length <= static_cast<int>(name.size());
             ++length) {
            string prefix = name.substr(0, length);
            auto candidate = names.lower_bound(prefix);
            if (candidate == names.end() ||
                candidate->compare(0, prefix.size(), prefix) != 0) {
                alias = prefix;
                break;
            }
        }

        int count = occurrences[name];
        if (count == 0) {
            cout << alias << '\n';
        } else {
            cout << name << count + 1 << '\n';
        }
        occurrences[name] = count + 1;
        names.insert(name);
    }
}

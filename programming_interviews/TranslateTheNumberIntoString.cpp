#include <cstdio>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <priority_queue>

using namespace std;

class Solution {
public:
    stringstream ss;
    void solve(int number) {
        string number_in_str;
        ss<<number;
        ss>>number_in_str;
        cout<<number_in_str<<endl;

        int length = number_in_str.size();
        int counts[length + 1];
        counts[1] = 1;
        if (is_valid(number_in_str.substr(length - 2, 2))) {
            counts[2] = 2;
        }
        else {
            counts[2] = 1;
        }

        for (int i = 3; i <= length; i++) {
            int cur_count = counts[i - 1];
            if (is_valid(number_in_str.substr(length - i, 2))) {
                cur_count += counts[i - 2];
            }
            counts[i] = cur_count;
        }

        cout<<counts[length]<<endl;
        cout<<ss.str()<<endl;
    };

    bool is_valid(string s) {
        ss<<s;
        int n;
        ss>>n;
        ss.clear();
        return (10 <= n) && (n <= 25);
    }
};
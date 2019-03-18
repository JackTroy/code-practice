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

using namespace std;

stringstream ss;
int gap[3] = {3600, 60, 1};
int N, K;

struct record {
    string plate;
    int secs;
    bool io;
};

struct secs_cars {
    int secs, cars;
};

// sort by secs
struct cmp_by_time{
    bool operator() (record a, record b) const {
        return a.secs < b.secs;
    }
};

int time_str2int(string time) {
    istringstream iss(time);
    int secs = 0;
    for (int i = 0; i < 3; i++) {
        string part;
        getline(iss, part, ':');
        int n = atoi(part.c_str());
        secs += n * gap[i];
    }
    return secs;
}

// will the string vanish ?
string time_int2string(int secs) {
    char time[10];
    int hour = secs / gap[0];
    secs -= hour * gap[0];
    int minutes = secs / gap[1];
    secs -= minutes * gap[1];
    sprintf(time, "%02d:%02d:%02d", hour, minutes, secs);
    return string(time);
}

void solve() {
    vector<record> records;
    vector<string> max_plates;
    vector<int> queries;
    int max_period = -1;

    cin>>N>>K;

    for (int i = 0; i < N; i++) {
        string plate, time, io;
        cin>>plate; cin>>time; cin>>io;

        int secs = time_str2int(time);
        bool i_or_o = io == "in" ? true : false;
        record rc = { plate, secs, i_or_o };

        records.push_back(rc);
    }
    for (int i = 0; i < K; i++) {
        string query_time;
        cin>>query_time;
        queries.push_back(time_str2int(query_time));
    }

    // check records
    sort(records.begin(), records.end(), cmp_by_time());
    vector<record> valid_records;
    map<string, record> in_records;
    map<string, int> car_period;
    for (int i = 0; i < records.size(); i++) {
        record rc = records[i];
        if (rc.io) {
            in_records[rc.plate] = rc;
        }
        else {
            map<string, record>::iterator in = in_records.find(rc.plate);
            if (in != in_records.end()) {
                // for query
                valid_records.push_back(in->second);
                valid_records.push_back(rc);

                // for max period
                int period = rc.secs - in->second.secs;
                map<string, int>::iterator car = car_period.find(rc.plate);
                if (car != car_period.end()) {
                    car->second += period;
                    period = car->second;
                }
                else {
                    car_period[rc.plate] = period;
                }
                if (period > max_period) {
                    max_plates.clear();
                    max_plates.push_back(rc.plate);
                    max_period = period;
                }
                else if (period == max_period) {
                    max_plates.push_back(rc.plate);
                }

                in_records.erase(in);
            }
        }
    }

    // deal with query
    sort(valid_records.begin(), valid_records.end(), cmp_by_time());
    int car_numbers = 0, record_idx = 0;
    int v_records_size = valid_records.size(), queries_size = queries.size();
    for (int i = 0; i < queries_size; i++) {
        int query_sec = queries[i];

        while (true) {
            if (!(record_idx < v_records_size)) break;
            if (query_sec < valid_records[record_idx].secs) break;
            if (valid_records[record_idx].io)   car_numbers++;
            else                                car_numbers--;
            record_idx++;
        }

        cout<<car_numbers<<endl;
    }

    sort(max_plates.begin(), max_plates.end());
    vector<string>::iterator i;
    for (i = max_plates.begin(); i != max_plates.end(); ++i) {
        cout<<*i<<" ";
    }
    cout<<time_int2string(max_period);
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    solve();
}

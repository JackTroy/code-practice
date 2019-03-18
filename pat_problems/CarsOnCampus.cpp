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

// sort by plate
bool cmp_by_plate_time(record& a, record& b) {
    int r = a.plate.compare(b.plate);
    if (r != 0) return r < 0;
    else        return a.secs < b.secs;
}

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
    sort(records.begin(), records.end(), cmp_by_plate_time);
    vector<record> valid_records;
    map<string, record> in_records;
    map<string, int> car_period;
    int records_size = records.size();
    for(int i = 0; i < records_size - 1; i++) {
        if(records[i].plate.compare(records[i+1].plate) == 0
           && records[i].io && !records[i+1].io) {
            valid_records.push_back(records[i]);
            valid_records.push_back(records[i+1]);
            int this_period = records[i+1].secs - records[i].secs;
            int all_period = car_period[records[i].plate] + this_period;
            car_period[records[i].plate] = all_period;
            if(all_period > max_period) {
                max_period = all_period;
                max_plates.clear();
                max_plates.push_back(records[i].plate);
            }
            else if (all_period == max_period) {
                max_plates.push_back(records[i].plate);
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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    solve();
}

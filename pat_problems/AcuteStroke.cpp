#include <cstdio>
#include <cmath>
#include <cstring>
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
bool slices[60][1286][128];
int M, N, L, T;
int directions[6][3] = {
    {1, 0, 0}, {-1 ,0, 0},
    {0, 1, 0}, {0, -1, 0},
    {0, 0, 1}, {0, 0, -1}
    };

struct idx {
    int l, m, n;
};

bool valid_idx(int l, int m, int n) {
    return l >= 0 && l < L
        && m >= 0 && m < M
        && n >= 0 && n < N;
}

int dfs_volume(int l, int m, int n) {
    if (!slices[l][m][n])   return 0;
    slices[l][m][n] = false;
    int vol = 1;
    for (int i = 0; i < 6; i++) {
        int nl = l + directions[i][0];
        int nm = m + directions[i][1];
        int nn = n + directions[i][2];
        if (valid_idx(nl, nm, nn)) {
            vol += dfs_volume(nl, nm, nn);
        }
    }
    return vol;
}

int bfs_volume(int l, int m, int n) {
    int vol_count = 1;
    slices[l][m][n] = false;

    queue<idx> q;
    idx a = {l, m, n};
    q.push(a);


    while (!q.empty()) {
        a = q.front();
        q.pop();

        for (int i = 0; i < 6; i++) {
            int nl = a.l + directions[i][0];
            int nm = a.m + directions[i][1];
            int nn = a.n + directions[i][2];
            if (valid_idx(nl, nm, nn) && slices[nl][nm][nn]) {
                idx b = {nl, nm, nn};
                slices[nl][nm][nn] = false;
                vol_count++;
                q.push(b);
            }
        }
    }
    return vol_count;
}

void solve() {
    cin>>M>>N>>L>>T;
    for (int l = 0; l < L; l++) {
        for (int m = 0; m < M; m++) {
            for (int n = 0; n < N; n++) {
                cin>>slices[l][m][n];
            }
        }
    }

    int vol_count = 0;
    for (int l = 0; l < L; l++) {
        for (int m = 0; m < M; m++) {
            for (int n = 0; n < N; n++) {
                if (slices[l][m][n]) {
                    int vol = bfs_volume(l, m, n);
                    vol_count +=  vol < T ? 0 : vol;
                }
            }
        }
    }

    cout<<vol_count<<endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    solve();
}

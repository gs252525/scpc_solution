#include <bits/stdc++.h>
#include <array>

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define rrep(i, n) for (int i = 1; i <= n; i++)
#define all(v) (v).begin(), (v).end()
#define ll long long
#define pb push_back

const int MAXN = 50100;

int a2[MAXN];
int a4[MAXN];
int a16[MAXN];
int a256[MAXN];
int a3[MAXN];
int a9[MAXN];
int a81[MAXN];
int a6561[MAXN];

int psum1[MAXN][400][6];
ll bucket1[MAXN][7];
int bn1[MAXN];
int bnt1[MAXN];

void solve1(vector<int>& a, vector<pair<int, int>>& queries, vector<ll>& results) {
    int n = a.size() - 1;
    rep(i, n) rep(j, 7) bucket1[i][j] = 0;
    vector<int> tmp;
    rrep(i, n) tmp.pb(a[i]);
    sort(all(tmp));
    tmp.erase(unique(all(tmp)), tmp.end());
    int sz = tmp.size();
    vector<int> cnt(sz);
    vector<int> chk(sz);
    rrep(i, n) {
        int t = lower_bound(all(tmp), a[i]) - tmp.begin();
        cnt[t]++;
    }
    int pv = 0;
    rep(i, sz) {
        if (tmp[i] == 1) continue;
        if (!chk[i] && cnt[i] >= tmp[i]) {
            bucket1[pv][0] = tmp[i];
            chk[i] = 1;
            bn1[i] = pv;
            bnt1[i] = 0;
            ll f = (ll)tmp[i] * tmp[i];
            for (int j = 1;; j++, f *= f) {
                bucket1[pv][j] = f;
                int l = lower_bound(all(tmp), f) - tmp.begin();
                if (l < sz && tmp[l] == f) {
                    chk[l] = 1;
                    bn1[l] = pv;
                    bnt1[l] = j;
                }
                if (f >= 50000) break;
            }
        }
        pv++;
    }
    rrep(i, n) {
        rep(j, pv) rep(k, 6) psum1[i][j][k] = psum1[i - 1][j][k];
        int t = lower_bound(all(tmp), a[i]) - tmp.begin();
        if (chk[t]) {
            psum1[i][bn1[t]][bnt1[t]]++;
        }
    }
    for (auto& query : queries) {
        int l = query.first;
        int r = query.second;
        ll ans = 0;
        rep(i, pv) {
            ll c = 0;
            rep(j, 6) {
                if (bucket1[i][j] == 0) break;
                c += psum1[r][i][j] - psum1[l - 1][i][j];
                ans += (c / bucket1[i][j]);
                c /= bucket1[i][j];
            }
        }
        results.push_back(ans);
    }
}

void solve(vector<int>& a, vector<pair<int, int>>& queries, vector<ll>& results) {
    int n = a.size() - 1;
    rrep(i, n) {
        a2[i] = a2[i - 1];
        a4[i] = a4[i - 1];
        a16[i] = a16[i - 1];
        a256[i] = a256[i - 1];
        a3[i] = a3[i - 1];
        a9[i] = a9[i - 1];
        a81[i] = a81[i - 1];
        a6561[i] = a6561[i - 1];
        if (a[i] == 1) a[i] = 0;
        else if (a[i] == 2) {
            a2[i]++; a[i] = 0;
        }
        else if (a[i] == 4) {
            a4[i]++; a[i] = 0;
        }
        else if (a[i] == 16) {
            a16[i]++; a[i] = 0;
        }
        else if (a[i] == 256) {
            a256[i]++; a[i] = 0;
        }
        else if (a[i] == 3) {
            a3[i]++; a[i] = 0;
        }
        else if (a[i] == 9) {
            a9[i]++; a[i] = 0;
        }
        else if (a[i] == 81) {
            a81[i]++; a[i] = 0;
        }
        else if (a[i] == 6561) {
            a6561[i]++; a[i] = 0;
        }
    }
    int Q = queries.size();
    vector<array<int, 3>> query(Q);
    rep(i, Q) {
        query[i][0] = queries[i].first;
        query[i][1] = queries[i].second;
        query[i][2] = i;
    }
    int m = 1;
    while (m * m <= n) m++;
    sort(all(query), [&](auto a, auto b) {
        if (a[0] / m != b[0] / m) return a[0] < b[0];
        return a[1] < b[1];
    });
    int cnt[MAXN] = {};
    int ans[MAXN] = {};
    int l = 1, r = 0;
    int tmp = 0;
    rep(i, Q) {
        auto& [l1, r1, idx] = query[i];
        while (r < r1) {
            r++;
            if (a[r] != 0 && a[r] <= n) {
                cnt[a[r]]++;
                int rr = a[r];
                while (cnt[rr] % rr == 0) {
                    tmp++;
                    if (rr * rr > n) break;
                    else {
                        cnt[rr] = 0;
                        rr = rr * rr;
                        cnt[rr]++;
                    }
                }
            }
        }
        while (l > l1) {
            l--;
            if (a[l] != 0 && a[l] <= n) {
                cnt[a[l]]++;
                int rr = a[l];
                while (cnt[rr] % rr == 0) {
                    tmp++;
                    if (rr * rr > n) break;
                    else {
                        cnt[rr] = 0;
                        rr = rr * rr;
                        cnt[rr]++;
                    }
                }
            }
        }
        while (r > r1) {
            if (a[r] != 0 && a[r] <= n) {
                cnt[a[r]]--;
                int rr = a[r];
                while (cnt[rr] < 0) {
                    cnt[rr] += rr;
                    rr = rr * rr;
                    assert(rr < n);
                    cnt[rr]--;
                    tmp--;
                }
            }
            r--;
        }
        while (l < l1) {
            if (a[l] != 0 && a[l] <= n) {
                cnt[a[l]]--;
                int rr = a[l];
                while (cnt[rr] < 0) {
                    cnt[rr] += rr;
                    rr = rr * rr;
                    assert(rr < n);
                    cnt[rr]--;
                    tmp--;
                }
            }
            l++;
        }
        ans[idx] = tmp;
        int t2 = a2[r1] - a2[l1 - 1];
        int t4 = a4[r1] - a4[l1 - 1];
        int t16 = a16[r1] - a16[l1 - 1];
        int t256 = a256[r1] - a256[l1 - 1];
        int t3 = a3[r1] - a3[l1 - 1];
        int t9 = a9[r1] - a9[l1 - 1];
        int t81 = a81[r1] - a81[l1 - 1];
        int t6561 = a6561[r1] - a6561[l1 - 1];
        int c = t2 >> 1;
        ans[idx] += c;
        c += t4;
        c >>= 2;
        ans[idx] += c;
        c += t16;
        c >>= 4;
        ans[idx] += c;
        c += t256;
        c >>= 8;
        ans[idx] += c;
        c = t3 / 3;
        ans[idx] += c;
        c += t9;
        c /= 9;
        ans[idx] += c;
        c += t81;
        c /= 81;
        ans[idx] += c;
        c += t6561;
        c /= 6561;
        ans[idx] += c;
    }
    rep(i, Q) results.push_back(ans[i]);
}

int main() {
    int n = 50000; // Size of array
    int Q = 50000; // Number of queries
    vector<int> a(n + 1);
    // Initialize a with random values between 2 and 200
    srand(time(0));
    rrep(i, n) a[i] = 2 + rand() % 199;

    // Generate random queries
    vector<pair<int, int>> queries(Q);
    rep(i, Q) {
        int l = 1 + rand() % n;
        int r = 1 + rand() % n;
        if (l > r) swap(l, r);
        queries[i] = { l, r };
    }

    vector<ll> results1, results2;
    solve1(a, queries, results1);
    solve(a, queries, results2);

    // Compare the results
    bool is_same = (results1 == results2);
    if (is_same) {
        cout << "The results are the same!" << endl;
    } else {
        cout << "The results are different!" << endl;
        rep(i, Q) {
            if (results1[i] != results2[i]) {
                cout << "Query: " << queries[i].first << " " << queries[i].second << endl;
                cout << "solve1: " << results1[i] << " solve: " << results2[i] << endl;
                break;
            }
        }
    }

    return 0;
}

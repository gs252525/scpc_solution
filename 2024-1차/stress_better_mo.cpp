#include <bits/stdc++.h>
#include <array>

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define rrep(i, n) for (int i = 1; i <= n; i++)
#define all(v) (v).begin(), (v).end()
#define ll long long
#define pb push_back

const int MAXN = 50100;
int psum1[MAXN][400][6];
int psum2[MAXN][400][5];
ll bucket1[MAXN][7];
ll bucket2[MAXN][7];
int bn1[MAXN];
int bn2[MAXN];
int bnt1[MAXN];
int bnt2[MAXN];

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

void solve2(vector<int>& a, vector<pair<int, int>>& queries, vector<ll>& results) {
    int n = a.size() - 1;
    rep(i, n) rep(j, 7) bucket2[i][j] = 0;
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
            bucket2[pv][0] = tmp[i];
            chk[i] = 1;
            bn2[i] = pv;
            bnt2[i] = 0;
            ll f = (ll)tmp[i] * tmp[i];
            for (int j = 1;; j++, f *= f) {
                bucket2[pv][j] = f;
                int l = lower_bound(all(tmp), f) - tmp.begin();
                if (l < sz && tmp[l] == f) {
                    chk[l] = 1;
                    bn2[l] = pv;
                    bnt2[l] = j;
                }
                if (f >= 50000) break;
            }
        }
        pv++;
    }
    int Q = queries.size(); 
    vector<array<int, 3>> query(Q);
    vector<int> ans(Q);
    int m = 1;
    while (m * m < Q) m++;
    rep(i, Q) {
        query[i][0] = queries[i].first;
        query[i][1] = queries[i].second;
        query[i][2] = i;
    }
    sort(all(query), [&](auto x, auto y) {
        if (x[0] / m != y[0] / m) {
            return x[0] < y[0];
        }
        return x[1] < y[1];
    });
    vector<int> v(n + 1);
    rrep(i, n) v[i] = lower_bound(all(tmp), a[i]) - tmp.begin();
    int ans_tmp = 0;
    int blah[400][5] = {};
    int prv[400] = {};
    auto add = [&](int x){
    if(!chk[v[x]]) return; 
    int p = bn2[v[x]], q = bnt2[v[x]]; 
    blah[p][q]++; 
    while(blah[p][q]==bucket2[p][q]){
      ans_tmp++; 
      blah[p][q]=0; 
      q++; 
      if(!bucket2[p][q]) break; 
      blah[p][q]++; 
    }
  };
  auto erase = [&](int x){
    if(x==0) return;
    if(!chk[v[x]]) return; 
    int p = bn2[v[x]], q = bnt2[v[x]]; 
    blah[p][q]--; 
    while(blah[p][q]==-1){
      ans_tmp--; 
      blah[p][q] = bucket2[p][q]-1; 
      q++; 
      blah[p][q]--; 
      if(!bucket2[p][q]) break; 
    }
  };
    int l = 0, r = 0;
    for (auto [l1, r1, idx] : query) {
        while (r < r1) add(++r);
        while (l1 < l) add(--l);
        while (r > r1) erase(r--);
        while (l < l1) erase(l++);
        ans[idx] = ans_tmp;
    }
    rep(i, Q) results.push_back(ans[i]);
}

int main() {
    // Test inputs
    int t = 1; // Number of test cases
    int n = 50000; // Size of array
    int Q = 50000; // Number of queries
    vector<int> a(n + 1);
    // Initialize a with random values between 2 and 200
    srand(time(0));
    rrep(i, n) a[i] = 2 + rand() % 1;

    // Generate random queries
    vector<pair<int, int>> queries(Q);
    rep(i, Q) {
        int l = 1 + rand() % n;
        int r = 1 + rand() % n;
        if(l>r) swap(l,r); 
        queries[i] = {l, r};
        //cout << l<<" " << r << endl; 
    }
    cout << "wtf?" << endl; 
    vector<ll> results1, results2;
    solve1(a, queries, results1);
    cout << "sex\n"; 
    solve2(a, queries, results2);
    cout << "wtf?" << endl; 
    // Compare the results
    rep(i,Q){
      //cout << results1[i] << " " << results2[i] << endl; 
      if(results1[i]!=results2[i]){
        cout << results1[i] << " " << results2[i] << endl; 
        cout << queries[i].first << " " << queries[i].second << endl; 
        break; 
      }
    }
    bool is_same = (results1 == results2);
    if (is_same) {
        cout << "The results are the same!" << endl;
    } else {
        cout << "The results are different!" << endl;
    }

    return 0;
}

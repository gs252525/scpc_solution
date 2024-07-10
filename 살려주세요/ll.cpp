#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define rrep(i, n) for (int i = 1; i <= n; i++)
#define all(v) (v).begin(), (v).end()
#define ll long long
#define pb push_back

const int MAXN = 50100;
ll bucket[MAXN][7];
int bn[MAXN];  // tmp[i] 가 어느 bucket에 있는지
int bnt[MAXN]; // tmp[i] 가 bucket 의 몇번째인지


ll num[MAXN][500]; 
int cnt[MAXN]; 


void solve() {
  int n;
  cin >> n;
  rep(i, n) rep(j, 7) bucket[i][j] = 0;
  vector<int> a(n + 1);
  vector<int> tmp;
  rrep(i, n) {
    cin >> a[i];
    tmp.pb(a[i]);
  }
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
    if (tmp[i] == 1)
      continue;
    if (!chk[i] && cnt[i] >= tmp[i]) {
      bucket[pv][0] = tmp[i];
      chk[i] = 1;
      bn[i] = pv;
      bnt[i] = 0;
      ll f = (ll)tmp[i] * tmp[i];
      for (int j = 1;; j++, f *= f) {
        bucket[pv][j] = f;
        int l = lower_bound(all(tmp), f) - tmp.begin();
        if (l < sz && tmp[l] == f) {
          chk[l] = 1;
          bn[l] = pv;
          bnt[l] = j;
        }
        if (f >= 50000)
          break;
      }
    }
    pv++;
  }
  //rrep(i, n) rep(j, pv) rep(k, 6) psum[i][j][k] = 0;
  /*
  rrep(i, n) {
    rep(j, pv) rep(k, 6) psum[i][j][k] = psum[i - 1][j][k];
    int t = lower_bound(all(tmp), a[i]) - tmp.begin();
    if (chk[t]) {
      psum[i][bn[t]][bnt[t]]++;
    }
  }
  */
  vector<int> v(n+1); 
  rrep(i,n){
    v[i] = lower_bound(all(tmp),a[i]) - tmp.begin(); 
  }
  rrep(i,n){
    int t = v[i]; 
    cnt[i] = cnt[i-1]; 
    rep(j,pv) num[i][j] = num[i-1][j]; 
    if(chk[t]){
      int p = bn[t], q = bnt[t]; 
      int prv = num[i-1][p]/bucket[p][q]; 
      if(prv%(bucket[p][q]) == bucket[p][q]-1) cnt[i]++;
      num[i][p] += bucket[p][q]; 
    }
  }
  
  int Q;
  cin >> Q;
  while (Q--) {
    int l, r;
    cin >> l >> r;
    ll ans = cnt[r] - cnt[l-1];
    
    cout << ans << endl;
  }
}

int32_t main(void) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  cin >> t;
  rrep(i, t) {
    cout << "Case #" << i << endl;
    solve();
  }
}
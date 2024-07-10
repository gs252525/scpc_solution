#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define rrep(i, n) for (int i = 1; i <= n; i++)
#define all(v) (v).begin(), (v).end()
#define ll long long
#define pb push_back

const int MAXN = 50100;
int psum[MAXN][400][4];
ll bucket[MAXN][7];
int bn[MAXN];  // tmp[i] 가 어느 bucket에 있는지
int bnt[MAXN]; // tmp[i] 가 bucket 의 몇번째인지

int decom[85][85][400][4]; 
int decomcnt[85][85]; 


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
  rrep(i,n) v[i] = lower_bound(all(tmp),a[i]) - tmp.begin(); 
  for(int i=0; 60*i<n; i++){
    //60*i start 
    int blah[400][4] = {}; 
    int up = 0; 
    for(int j=i; j<n; j++){
      int t = v[j]; 
      if(chk[t]){
        int p = bn[t], q = bnt[t]; 
        blah[p][q]++; 
        int r = q; 
        while(blah[p][r]>=bucket[p][r]){
          up++; 
          blah[p][r] = 0; 
          if(bucket[p][r+1]==0) break; 
          r++; 
          blah[p][r]++; 
        }
      }
      if(j!=i && j%60==0){
        int l = j/60; 
        decomcnt[i][l] = up; 
        rep(u,pv){
          rep(f,4){
            decom[i][l][u][f] = blah[u][f]; 
          }
        }
      }
    }
  }

  int Q;
  cin >> Q;
  while (Q--) {
    int l, r;
    cin >> l >> r;
    int ans = 0;
    /*
    rep(i, pv) {
      int c = 0;
      rep(j, 6) {
        if (bucket[i][j] == 0)
          break;
        c += psum[r][i][j] - psum[l - 1][i][j];
        ans += (c / bucket[i][j]);
        c /= bucket[i][j];
      }
    }
    */
    int x = (l+59)/60;
    int y = r/60; 
    int blah[400][4] = {}; 
    if(x<y){
      ans = decomcnt[x][y]; 
      x = 60*x; 
      rep(i,pv) rep(j,4) blah[i][j] = decom[x][y][i][j]; 
      while(l<x){

      }
    }
    
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
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <array>

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define rrep(i, n) for (int i = 1; i <= n; i++)
#define all(v) (v).begin(), (v).end()
#define ll long long
#define pb push_back
#define ff first 
#define ss second 

const int MAXN = 50100;
int psum[MAXN][400][5];
ll bucket[MAXN][7];
int bn[MAXN];  // tmp[i] 가 어느 bucket에 있는지
int bnt[MAXN]; // tmp[i] 가 bucket 의 몇번째인지

int l; 
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
  int Q;
  cin >> Q;
  vector<array<int,3>> query(Q); 
  vector<int> ans(Q); 
  int m = 1; 
  while(m*m<Q) m++; 
  rep(i,Q){
    cin >> query[i][0] >> query[i][1]; query[i][2] = i; 
  }
  sort(all(query),[&](auto x, auto y){
    if(x[0]/m != y[0]/m){
      return x[0] < y[0]; 
    }
    return x[1] < y[1]; 
  }); 
  vector<int> v(n+1); 
  rrep(i,n) v[i] = lower_bound(all(tmp),a[i]) - tmp.begin(); 
  int ans_tmp = 0; 
  int blah[400][5] = {}; 

  auto add_ = [&](vector<int>& vi){
    sort(all(vi)); 
    for(int i=0; i<vi.size(); ){
      int x = vi[i]; 
      int p = bn[x], q = bnt[x], r = upper_bound(all(vi),x) - lower_bound(all(vi),x); 
      i+=r; 
      if(!chk[x]) continue;
      blah[p][q]+=r; 
      while(blah[p][q]>=bucket[p][q]){
        int l = blah[p][q] / bucket[p][q];
        ans_tmp += l;
        blah[p][q]= blah[p][q] % bucket[p][q]; 
        q++; 
        if(!bucket[p][q]) break; 
        blah[p][q]+=l; 
      }
    }
    
  };

  auto erase_ = [&](vector<int>& vi){
    sort(all(vi)); 
    for(int i=0; i<vi.size(); i++){
      int x = vi[i]; 
      int p = bn[x], q = bnt[x], r = upper_bound(all(vi),x) - lower_bound(all(vi),x);  
      i+=r; 
      if(!chk[x]) continue; 
      //cout << x << " erase " << r << endl; 
      blah[p][q] -= r; 
      while(blah[p][q]<0){
        int k = -blah[p][q]; 
        int l = (k+bucket[p][q]-1)/bucket[p][q]; 
        ans_tmp -= l; 
        blah[p][q] += l*bucket[p][q]; 
        q++; 
        if(!bucket[p][q]) break; 
        blah[p][q] -= l;  
      }
    }
    
  };
  int l = 1, r = 0; 
  for(auto [l1, r1, idx]:query){
    vector<int> toadd; 
    vector<int> toerase;
    while(r<r1){
      toadd.pb(v[++r]); 
    } 
    while(l1<l){
      toadd.pb(v[--l]); 
    } 
    while(r>r1){
      toerase.pb(v[r--]); 
    } 
    while(l<l1){
      toerase.pb(v[l++]); 
    }
    add_(toadd); 
    erase_(toerase); 
    ans[idx] = ans_tmp; 
  }
  rep(i,Q) cout << ans[i] << endl; 
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
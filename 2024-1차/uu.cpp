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


int a2[MAXN]; 
int a4[MAXN]; 
int a16[MAXN]; 
int a256[MAXN];
int a3[MAXN]; 
int a9[MAXN]; 
int a81[MAXN]; 
int a6561[MAXN]; 

void solve() {
  int n; cin >> n; 
  vector<int> a(n+1); 
  rrep(i,n){
    a2[i] = a2[i-1]; 
    a4[i] = a4[i-1]; 
    a16[i] = a16[i-1]; 
    a256[i] = a256[i-1]; 
    a3[i] = a3[i-1]; 
    a9[i] = a9[i-1]; 
    a81[i] = a81[i-1]; 
    a6561[i] = a6561[i-1]; 
    cin >> a[i]; 
    if(a[i]==1) a[i] = 0;
    else if(a[i]==2){
      a2[i]++; a[i] = 0; 
    }
    else if(a[i]==4){
      a4[i]++; a[i] = 0; 
    }
    else if(a[i]==16){
      a16[i]++; a[i] = 0; 
    }
    else if(a[i]==256){
      a256[i]++; a[i] = 0; 
    }
    else if(a[i]==3){
      a3[i]++; a[i] = 0; 
    }
    else if(a[i]==9){
      a9[i]++; a[i] = 0; 
    }
    else if(a[i]==81){
      a81[i]++; a[i] = 0; 
    }
    else if(a[i]==6561){
      a6561[i]++; a[i] = 0; 
    }
  }
  int Q; cin >> Q; 
  vector<array<int,3>> query(Q); 
  rep(i,Q){
    cin >> query[i][0] >> query[i][1]; 
    query[i][2] = i; 
  }
  int m = 1; 
  while(m*m<=n) m++; 
  sort(all(query),[&](auto a, auto b){
    if(a[0]/m != b[0]/m) return a[0] < b[0]; 
    return a[1] < b[1];  
  }); 
  int cnt[MAXN] = {}; 
  int ans[MAXN] = {}; 
  int l =1, r = 0; 
  int tmp = 0; 
  rep(i,Q){
    auto &[l1,r1,idx] = query[i]; 
    while(r<r1){
      r++; 
      if(a[r]!=0 && a[r]<=n){
        cnt[r]++; 
        int rr = r; 
        while(cnt[rr]%rr==0){
          tmp++; 
          if(rr*rr>n) break; 
          else {
            cnt[rr] = 0; 
            rr = rr*rr; 
            cnt[rr]++; 
          }
        }
      }
    }
    while(l>l1){
      l--; 
      if(a[l]!=0 && a[l]<=n){
        cnt[l]++; 
        int rr = l; 
        while(cnt[rr]%rr==0){
          tmp++; 
          if(rr*rr>n) break; 
          else {
            cnt[rr] = 0; 
            rr = rr*rr; 
            cnt[rr]++; 
          }
        }
      }
    }
    while(r>r1){
      if(a[r]!=0 && a[r]<=n){
        cnt[r]--; 
        int rr = r; 
        while(cnt[rr]<0){
          cnt[rr]+=rr; 
          rr = rr*rr; 
          cnt[rr]--; 
          tmp--; 
        }
      }
      r--; 
    }
    while(l<l1){
      if(a[l]!=0 && a[l]<=n){
        cnt[r]--; 
        int rr = r; 
        while(cnt[rr]<0){
          cnt[rr]+=rr; 
          rr = rr*rr; 
          cnt[rr]--; 
          tmp--; 
        }
      }
      l++; 
    }
    ans[idx] = tmp; 
    int t2 = a2[r1]-a2[l1-1];
    int t4 = a4[r1]-a4[l1-1];
    int t16=a16[r1]-a16[l1-1]; 
    int t256=a256[r1]-a256[l1-1];  
    int t3 = a3[r1]-a3[l1-1]; 
    int t9 = a9[r1]-a9[l1-1]; 
    int t81 = a81[r1]-a81[l1-1]; 
    int t6561=a6561[r1]-a6561[l1-1]; 
    //cout << t2 << " " << t4 << " " << t3 << " " << ans[idx] << endl; 
    int c = t2>>1; 
    ans[idx]+=c; 
    c+= t4; 
    c>>=2; 
    ans[idx]+=c; 
    c += t16;
    c>>=4;
    ans[idx]+=c; 
    c += t256; 
    c>>=8; 
    ans[idx] += c; 

    c = t3/3; 
    ans[idx] += c; 
    c += t9; 
    c/=9; 
    ans[idx] += c; 
    c += t81; 
    c/=81; 
    ans[idx] += c; 
    c += t6561; 
    c /= 6561; 
    ans[idx] += c; 
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
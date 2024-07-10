#include <bits/stdc++.h> 

using namespace std; 

#define rep(i,n) for(int i=0; i<n; i++)
#define rrep(i,n) for(int i=1; i<=n; i++)
#define all(v) (v).begin(), (v).end() 
#define ll long long 

void solve(){
  int n; cin >> n; 
  vector<int> v(n); 
  rep(i,n) cin >> v[i]; 
  sort(all(v)); 
  ll ans = 0; 
  rep(i,n/4){
    ans += v[n-1-i] - v[i]; 
  }
  ans = ans*2LL; 
  cout << ans << endl; 
  return; 
}

int main(void){
  int t; cin >> t; 
  rrep(i,t){
    cout << "Case #"  << i << endl; 
    solve(); 
  }
}
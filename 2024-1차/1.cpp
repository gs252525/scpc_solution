#include <bits/stdc++.h> 

using namespace std; 

#define rep(i,n) for(int i=0; i<n; i++)
#define rrep(i,n) for(int i=1; i<=n; i++)
#define all(v) (v).begin(), (v).end() 

void solve(){
  int n; cin >> n; 
  string s; cin >> s; 
  int ans = 0; 
  for(int i=0; i<n; ){
    if(s[i]=='B') {
      i++; continue; 
    }
    int j=i+1; 
    while(j<n && s[j]=='B') j++; 
    if(j==n){
      i = j; continue; 
    }
    if(j-i>2) {
      i = j; continue; 
    }
    ans += (3-(j-i)); 
    i=j; 
  }
  cout << ans << endl; 
}

int main(void){
  int t; cin >> t; 
  rrep(i,t){
    cout << "Case #"  << i << endl; 
    solve(); 
  }
}
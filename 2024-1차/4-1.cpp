#include <bits/stdc++.h> 

using namespace std; 

#define rep(i,n) for(int i=0; i<n; i++)
#define rrep(i,n) for(int i=1; i<=n; i++)
#define all(v) (v).begin(), (v).end() 
#define ll long long 
#define pb push_back

const int MAXN = 100100; 

int L[MAXN],R[MAXN],LL[MAXN],RR[MAXN]; 


void solve(){
  int n,C; cin >> n >> C; 
  vector<int> a(n); 
  vector<int> b(n); 
  rep(i,n) cin >> a[i]; 
  rep(i,n) cin >> b[i]; 
  sort(all(a)); 
  sort(all(b)); 
  int ans = 0; 
  rep(i,n) ans = max(ans, abs(a[i]-b[i])); 
  if(ans>C){
    cout << -1 << endl; return; 
  }
  rep(i,n) L[i]=R[i]=LL[i]=RR[i]=0; 
  for(int i=0; i<n; i++){
    if(i && abs(a[i]-b[i-1])<=C) L[i] = 1; 
    if(i!=n-1 && abs(a[i]-b[i+1])<=C) R[i] = 1; 
  }
  for(int i=n-1; i>=0; i--){
    if(L[i]==0) LL[i] = i-1; 
    else {
      if(i==n-1) LL[i] = n-1; 
      else LL[i] = LL[i+1]; 
    }
  }
  for(int i=0; i<n; i++){
    if(R[i]==0) RR[i] = i+1; 
    else {
      if(i==0) RR[i] = 0; 
      else RR[i] = RR[i-1]; 
    }
  }
  for(int i=0; i<n; i++){
    if(i!=n-1){
      int j = (upper_bound(all(b),a[i]+C) - b.begin()) - 1; 
      j = min(j,LL[i+1]);
      
      ans = max(ans, abs(a[i]-b[j])); 
    }
    if(i!=0){
      int j = lower_bound(all(b),a[i]-C) - b.begin(); 
      //cout << i << " " << j << " " << RR[i-1] << endl;
      j = max(j,RR[i-1]); 
      //cout << i << " " << a[i]-b[j] << endl;
      ans = max(ans,abs(a[i]-b[j])); 
    }
  }
  cout << ans << endl; 
}

int main(void){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t; cin >> t; 
  rrep(i,t){
    cout << "Case #"  << i << endl; 
    solve(); 
  }
}
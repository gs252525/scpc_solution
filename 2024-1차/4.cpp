#include <bits/stdc++.h> 
#include <random>

using namespace std; 

#define rep(i,n) for(int i=0; i<n; i++)
#define rrep(i,n) for(int i=1; i<=n; i++)
#define all(v) (v).begin(), (v).end() 
#define ll long long 
#define pb push_back

const int MAXN = 100100; 

int L[MAXN],R[MAXN],LL[MAXN],RR[MAXN]; 


int solve1(int N, int CC, vector<int>& aa, vector<int>& bb){
  // int n,C; cin >> n >> C; 

  int n,C; n = N; C = CC; 
  vector<int> a(n); 
  vector<int> b(n); 
  //rep(i,n) cin >> a[i]; 
  //rep(i,n) cin >> b[i]; 
  rep(i,n) a[i] = aa[i]; 
  rep(i,n) b[i] = bb[i]; 
  sort(all(a)); 
  sort(all(b)); 
  int ans = 0; 
  rep(i,n) ans = max(ans, abs(a[i]-b[i])); 
  if(ans>C){
    //cout << -1 << endl; 
    return -1; 
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
      j = max(j,RR[i-1]); 
      ans = max(ans,abs(a[i]-b[j])); 
    }
  }
  //cout << ans << endl; 
  return ans; 
}

int solve2(int N, int CC, vector<int>& aa, vector<int>& bb){
  int n,C; n = N; C = CC; 
  vector<int> a(n); 
  vector<int> b(n); 
  //rep(i,n) cin >> a[i]; 
  //rep(i,n) cin >> b[i]; 
  rep(i,n) a[i] = aa[i]; 
  rep(i,n) b[i] = bb[i]; 
  sort(all(a)); 
  sort(all(b)); 

  vector<int> ar(n); 
  rep(i,n) ar[i] = i; 
  int ans = -1; 
  do{
    int c = 0; 
    rep(i,n) c = max(c,abs(a[i]-b[ar[i]])); 
    if(c<=CC) ans = max(ans,c); 
  }while(next_permutation(all(ar)));  
  return ans; 

}

int main(void){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  /*
  int t; cin >> t; 
  rrep(i,t){
    cout << "Case #"  << i << endl; 





    solve1(); 
  }
  */
  srand(static_cast<unsigned int>(std::time(nullptr)));
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1, 100000000);
  while(1){
    int n = rand() % 100000 + 5; 
    vector<int> a(n); 
    vector<int> b(n); 
    int C = dis(gen); 
    rep(i,n) a[i] = dis(gen); 
    sort(all(a)); 
    rep(i,n) b[i] = dis(gen); 
    sort(all(b)); 
    int s1 = solve1(n,C,a,b); 
    s1--;
    int s2 = solve2(n,C,a,b); 
    if(s1!=s2){
      cout << n << " " << C << endl;
      for(auto ai : a) cout << ai << " "; 
      cout << endl; 
      for(auto bi : b) cout << bi << " "; 
      cout << endl;
      cout << s1 << " " << s2; 
      break; 
    }


  }
}
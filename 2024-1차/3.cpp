#include <bits/stdc++.h> 

using namespace std; 

#define rep(i,n) for(int i=0; i<n; i++)
#define rrep(i,n) for(int i=1; i<=n; i++)
#define all(v) (v).begin(), (v).end() 
#define ll long long 
#define pb push_back

const int MAXN = 300100; 

int deg[MAXN]; 
vector<int> adj[MAXN]; 
int dfsn[MAXN]; 

int pv; 
int u,v; 

int dfs(int x, int p){
  dfsn[x] = pv++; 
  //cerr << x << " " << dfsn[x] << endl; 
  if(x==v) return dfsn[x]; 
  for(auto ne : adj[x]){
    if(x==u && ne==v) continue; 
    if(ne==p) continue; 
    return dfs(ne,x); 
  }
}

void solve(){
  int n; cin >> n; 
  set<pair<int,int>> s; 
  rrep(i,n) deg[i] = dfsn[i] = 0; 
  rrep(i,n) adj[i].clear(); 
  bool flag = false; 
  rep(i,n+1){
    int u,v; cin >> u >> v; 
    adj[u].pb(v); 
    adj[v].pb(u); 
    deg[u]++; 
    deg[v]++; 
    if(s.find({u,v})!=s.end()) flag = true; 
    s.insert({u,v}); 
    s.insert({v,u}); 
  } 
  if(flag){
    ll ans = (ll)(n-1)*(n-2)/2LL; 
    cout << ans << endl; return; 
  }
  vector<int> tmp; 
  rrep(i,n){
    if(deg[i]>2) tmp.pb(i); 
  }
  u = tmp[0], v = tmp[1]; 
  //cerr << u << " " << v << endl; 
  dfsn[u] = 0; 
  pv = 0; 
  ll l = dfs(u,u); 
  ll ans = l*(l-1) / 2LL + (ll)(n-l)*(n-l-1)/2LL; 
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
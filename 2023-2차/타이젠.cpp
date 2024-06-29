#include <bits/stdc++.h>
#define pb push_back 
#define rep(i,n) for(int i=0; i<n; i++)
#define rrep(i,n) for(int i=1; i<=n; i++)
#define all(v) (v).begin(), (v).end()
 
using namespace std;


int ne[40]; 

int end_state[40]; 
int cnt[40]; 

int move(int x, int k){
	int n = 0; 
	if(x==5) n = 20; 
	else if(x==22) n = 28; 
	else if(x==10) n = 25; 
	else n = ne[x]; 
	k--; 
	while(k--) n = ne[n]; 
	return n; 
}

long long solve(){
	int N,K; cin >> N >> K; 
	vector<int> v(N); 
	rep(i,N) cin >> v[i]; 
	
	for(int i=0;i<=30;i++){
		end_state[i] = 0; 
		cnt[i] = 0; 
		int st = i; 
		rep(j,N){
			//cout << st << " " << v[j] << " " << move(st,v[j]) << "\n"; 
			st = move(st,v[j]); 
			
			if(st==31){
				cnt[i]++; 
				st = 0; 
			}
		}
		end_state[i] = st; 
	}
	int s = 0; 
	long long ans = 0; 
	rep(i,K){
		ans += cnt[s]; 
		s = end_state[s]; 
		
	}
	return ans; 
}



int main(int argc, char** argv)
{	
	ios::sync_with_stdio(false); cin.tie(NULL);
	int T, test_case;

	cin >> T;
	
	for(int i=0; i<=18; i++) ne[i] = i+1; 
	ne[19] = 30; 
	ne[30] = 31; 
	ne[31] = 31; 
	for(int i=20; i<24;i++) ne[i] = i+1; 
	ne[24] = 15; 
	for(int i=25;i<=29;i++) ne[i] = i+1; 
	
	
	
	for(test_case = 0; test_case  < T; test_case++)
	{
		
		cout << "Case #" << test_case+1 << endl;
		cout << solve() << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
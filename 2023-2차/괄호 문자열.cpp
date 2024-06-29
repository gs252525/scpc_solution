#include <bits/stdc++.h>
#define pb push_back 
#define rep(i,n) for(int i=0; i<n; i++)
#define rrep(i,n) for(int i=1; i<=n; i++)
#define all(v) (v).begin(), (v).end()
 
using namespace std;

int Answer;

long long dp[1000100]; 

long long solve(){
	int n; cin >> n; 
	for(int i=0; i<=n; i++) dp[i] = 0; 
	string s; cin >> s; 
	stack<pair<char,int>> st; 
	long long ans = 0;
	for(int i=0; i<n; i++){
		if(s[i]=='('){
			st.push({'(',i}); continue; 
		}
		if(s[i]=='{'){
			st.push({'{',i}); continue; 
		}
		if(s[i]=='}'){
			if(st.empty()) continue; 
			auto [c,j] = st.top(); 
			st.pop(); 
			if(c=='('){
				while(!st.empty()) st.pop(); 
				continue; 
			}
			dp[i] = (j>=1 ? dp[j-1]:0) + 1; 
			ans += dp[i]; 
		}
		if(s[i]==')'){
			if(st.empty()) continue; 
			auto [c,j] = st.top(); 
			st.pop(); 
			if(c=='{'){
				while(!st.empty()) st.pop(); 
				continue; 
			}
			dp[i] = (j>=1 ? dp[j-1]:0) + 1; 
			ans += dp[i]; 
		}
	}
	return ans; 
}


int main(int argc, char** argv)
{   
    ios_base::sync_with_stdio(false); 
    std::cin.tie(NULL);
	int T, test_case;

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{

		Answer = 0;
		
		cout << "Case #" << test_case+1 << endl;
		cout << solve() << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Author : jinhan814
 * Date : 2021-05-06
 * Source : https://blog.naver.com/jinhan814/222266396476
 * Description : FastIO implementation for cin, cout. (mmap ver.)
 */
constexpr int SZ = 1 << 20;

class INPUT {
private:
    char* p;
    bool __END_FLAG__, __GETLINE_FLAG__;
public:
    explicit operator bool() { return !__END_FLAG__; }
    INPUT() {
        struct stat st; fstat(0, &st);
        p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
    }
    bool IsBlank(char c) { return c == ' ' || c == '\n'; }
    bool IsEnd(char c) { return c == '\0'; }
    char _ReadChar() { return *p++; }
    char ReadChar() {
        char ret = _ReadChar();
        for (; IsBlank(ret); ret = _ReadChar());
        return ret;
    }
    template<typename T> T ReadInt() {
        T ret = 0; char cur = _ReadChar(); bool flag = 0;
        for (; IsBlank(cur); cur = _ReadChar());
        if (cur == '-') flag = 1, cur = _ReadChar();
        for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar()) ret = 10 * ret + (cur & 15);
        if (IsEnd(cur)) __END_FLAG__ = 1;
        return flag ? -ret : ret;
    }
    string ReadString() {
        string ret; char cur = _ReadChar();
        for (; IsBlank(cur); cur = _ReadChar());
        for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar()) ret.push_back(cur);
        if (IsEnd(cur)) __END_FLAG__ = 1;
        return ret;
    }
    double ReadDouble() {
        string ret = ReadString();
        return stod(ret);
    }
    string getline() {
        string ret; char cur = _ReadChar();
        for (; cur != '\n' && !IsEnd(cur); cur = _ReadChar()) ret.push_back(cur);
        if (__GETLINE_FLAG__) __END_FLAG__ = 1;
        if (IsEnd(cur)) __GETLINE_FLAG__ = 1;
        return ret;
    }
    friend INPUT& getline(INPUT& in, string& s) { s = in.getline(); return in; }
} _in;

class OUTPUT {
private:
    char write_buf[SZ];
    int write_idx;
public:
    ~OUTPUT() { Flush(); }
    explicit operator bool() { return 1; }
    void Flush() {
        write(1, write_buf, write_idx);
        write_idx = 0;
    }
    void WriteChar(char c) {
        if (write_idx == SZ) Flush();
        write_buf[write_idx++] = c;
    }
    template<typename T> int GetSize(T n) {
        int ret = 1;
        for (n = n >= 0 ? n : -n; n >= 10; n /= 10) ret++;
        return ret;
    }
    template<typename T> void WriteInt(T n) {
        int sz = GetSize(n);
        if (write_idx + sz >= SZ) Flush();
        if (n < 0) write_buf[write_idx++] = '-', n = -n;
        for (int i = sz; i --> 0; n /= 10) write_buf[write_idx + i] = n % 10 | 48;
        write_idx += sz;
    }
    void WriteString(string s) { for (auto& c : s) WriteChar(c); }
    void WriteDouble(double d) { WriteString(to_string(d)); }
} _out;

/* operators */
INPUT& operator>> (INPUT& in, char& i) { i = in.ReadChar(); return in; }
INPUT& operator>> (INPUT& in, string& i) { i = in.ReadString(); return in; }
template<typename T, typename std::enable_if_t<is_arithmetic_v<T>>* = nullptr>
INPUT& operator>> (INPUT& in, T& i) {
    if constexpr (is_floating_point_v<T>) i = in.ReadDouble();
    else if constexpr (is_integral_v<T>) i = in.ReadInt<T>(); return in; }

OUTPUT& operator<< (OUTPUT& out, char i) { out.WriteChar(i); return out; }
OUTPUT& operator<< (OUTPUT& out, string i) { out.WriteString(i); return out; }
template<typename T, typename std::enable_if_t<is_arithmetic_v<T>>* = nullptr>
OUTPUT& operator<< (OUTPUT& out, T i) {
    if constexpr (is_floating_point_v<T>) out.WriteDouble(i);
    else if constexpr (is_integral_v<T>) out.WriteInt<T>(i); return out; }

/* macros */
#define fastio 1
#define cin _in
#define cout _out
#define istream INPUT
#define ostream OUTPUT
#include <chrono>
#include <array>

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define rrep(i, n) for (int i = 1; i <= n; i++)
#define all(v) (v).begin(), (v).end()
#define ll long long
#define pb push_back

const int MAXN = 50100;
int psum[MAXN][400][6];
ll bucket[MAXN][7];
int bn[MAXN];  // tmp[i] 가 어느 bucket에 있는지
int bnt[MAXN]; // tmp[i] 가 bucket 의 몇번째인지

int san; 

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
  int prv[400] = {}; 
  auto add = [&](int x){
    if(!chk[v[x]]) return; 
    int p = bn[v[x]], q = bnt[v[x]]; 
    blah[p][q]++; 
    while(blah[p][q]==bucket[p][q]){
      ans_tmp++; 
      blah[p][q]=0; 
      q++; 
      if(!bucket[p][q]) break; 
      blah[p][q]++; 
    }
  };
  auto erase = [&](int x){
    if(x==0) return;
    if(!chk[v[x]]) return; 
    int p = bn[v[x]], q = bnt[v[x]]; 
    blah[p][q]--; 
    while(blah[p][q]==-1){
      ans_tmp--; 
      blah[p][q] = bucket[p][q]-1; 
      q++; 
      blah[p][q]--; 
      if(!bucket[p][q]) break; 
    }
  };
  int l = 0, r = 0; 
  for(auto &[l1, r1, idx]:query){
    while(r<r1) add(++r); 
    while(l1<l) add(--l); 
    while(r>r1) erase(r--); 
    while(l<l1) erase(l++); 
    ans[idx] = ans_tmp; 
  }

  //rep(i,Q) cout << ans[i] << endl; 
  rrep(i,Q) san ^= ans[i]; 
  cout << san << endl; 
}

int32_t main(void) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int t = 32; // Number of test cases
  int n = 50000; // Value of n
  int Q = 50000; // Number of queries

  // Seed for random number generation
  srand(time(0));

  // Generate random test case
  /*
  ofstream out("input.txt");
  //out << t << endl;
  for (int i = 1; i <= t; i++) {
    out << n << endl;
    for (int j = 1; j <= n; j++) {
      out << (rand() % (100) + 1) << " ";
    }
    out << endl;
    out << Q << endl;
    for (int j = 0; j < Q; j++) {
      int l = rand() % n + 1;
      int r = rand() % n + 1;
      if (l > r) swap(l, r);
      out << l << " " << r << endl;
    }
  }
  out.close();

  */
  
  // Measure execution time
  auto start = chrono::high_resolution_clock::now();

  // Redirect input from generated file
  freopen("input.txt", "r", stdin);

  rrep(i, t) {
    cout << "Case #" << i << endl;
    solve();
  }

  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> duration = end - start;
  cerr << "Execution time: " << duration.count() << " seconds" << endl;

  return 0;
}

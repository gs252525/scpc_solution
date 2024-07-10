#include <bits/stdc++.h>
#include <chrono>

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

void solve() {
  int n;
  cin >> n;
  cerr << n << endl; 
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
  //rrep(i, n) rep(j, pv) rep(k, 6) psum[i][j][k] = 0;
  rrep(i, n) {
    rep(j, pv) rep(k, 6) psum[i][j][k] = psum[i - 1][j][k];
    int t = lower_bound(all(tmp), a[i]) - tmp.begin();
    if (chk[t]) {
      psum[i][bn[t]][bnt[t]]++;
    }
  }
  int Q;
  cin >> Q;
  while (Q--) {
    int l, r;
    cin >> l >> r;
    int ans = 0;
    rep(i, pv) {
      int c = 0;
      rep(j, 6) {
        if (bucket[i][j] == 0)
          break;
        c += psum[r][i][j] - psum[l - 1][i][j];
        ans += (c / bucket[i][j]);
        c /= bucket[i][j];
      }
    }
    cout << ans << endl;
  }
}

int32_t main(void) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int t = 1; // Number of test cases
  int n = 50000; // Value of n
  int Q = 50; // Number of queries

  // Seed for random number generation
  srand(time(0));

  // Generate random test case
  ofstream out("input.txt");
  //out << t << endl;
  for (int i = 1; i <= t; i++) {
    out << n << endl;
    for (int j = 1; j <= n; j++) {
      out << (rand() % (100000000) + 1) << " ";
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

#include <bits/stdc++.h>
using namespace std;

#define oo 0x3f3f3f3f
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) for(long _ = 0; (_ == 0 ? (_=clock()) != 0 : false); debug("%s time : %.4fs", d, (double)(clock() - _) / CLOCKS_PER_SEC))
#define FO(i,a,b) for (int i=(a);i<=(b);++i)
#define FD(i,a,b) for (int i=(a);i>=(b);--i)
#define FE(i,G,x) for(int i=(G).h[x];~i;i=(G).v[i].nxt)
typedef long long LL;
typedef pair<int, int> PII;

template <class T> inline bool chkmin(T& x, T y) { return x > y ? x = y, true : false; }
template <class T> inline bool chkmax(T& x, T y) { return x < y ? x = y, true : false; }

inline LL read(void) {
    LL x, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
    for (x = 0; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}

#define N 505
template<typename T, size_t n, size_t m>
struct Graph {
    struct { int to, nxt; T w; } v[m];
    int h[n], cnt;
    Graph() { memset(h, -1, sizeof(h)); }
    void clear() { cnt = 0; memset(h, -1, sizeof(h)); }
    void add(int x, int y, const T& w = 0) { v[cnt] = {y, h[x], w}; h[x] = cnt++; }
};
Graph<bool, N, 2 * N> G;

LL f[N][N], g[N][N];
int n, t, x, y, T, a[N];

void solve(int x, int fa) {
    FE(i, G, x) { int to = G.v[i].to; if (to != fa) solve(to, x); }
    FE(i, G, x) {
        int v = G.v[i].to;
        if (v == fa) continue;
        FD(j, T, 3)FO(z, 1, j - 2) chkmax(g[x][j], g[x][j - z - 2] + f[v][z]);
        FD(j, T, 2)FO(z, 1, j - 1) chkmax(g[x][j], f[x][j - z - 1] + g[v][z]);
        FD(j, T, 3)FO(z, 1, j - 2) chkmax(f[x][j], f[x][j - z - 2] + f[v][z]);
    }
    FD(i, T, 1) chkmax(f[x][i], f[x][i - 1] + a[x]), chkmax(g[x][i], g[x][i - 1] + a[x]);
}

int main(void) {
    n = read(); T = read();
    FO(i, 1, n) a[i] = read();
    FO(i, 1, n - 1) { x = read(); y = read(); G.add(x, y); G.add(y, x); }
    solve(1, 0); cout << g[1][T] << endl;
    return 0;
}
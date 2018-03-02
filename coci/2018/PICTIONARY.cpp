#include <bits/stdc++.h>
using namespace std;

#define oo 0x3f3f3f3f
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define FO(i,a,b) for(int i=a;i<=b;++i)
#define FD(i,a,b) for(int i=a;i>=b;--i)
#define FE(i,G,x) for(int i=G.h[x];~i;i=G.v[i].nxt)
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

#define N 100005
template<typename T>
struct Graph {
    enum { maxn = 2 * N, maxm = 4 * N };
    struct { int to, nxt; T w; } v[maxm];
    int h[maxn], cnt;
    Graph() { memset(h, -1, sizeof(h)); }
    void add(int x, int y, const T& w) {
        v[cnt].nxt = h[x];
        v[cnt].to = y; v[cnt].w = w;
        h[x] = cnt++;
    }
};
Graph<int> G;
struct Edge {
    int w, x, y;
    bool operator < (const Edge& x) const { return w > x.w; }
} V[N * 25];

int anc[19][2 * N], mx[19][2 * N], dep[2 * N];
int n, m, x, y, q, cnt, p, fa[2 * N];

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }
void dfs(int x, int fa) {
    anc[0][x] = fa; dep[x] = dep[fa] + 1;
    FO(i, 1, 18) anc[i][x] = anc[i - 1][anc[i - 1][x]];
    FO(i, 1, 18) mx[i][x] = min(mx[i - 1][x], mx[i - 1][anc[i - 1][x]]);
    FE(i, G, x) {
        int to = G.v[i].to;
        if (to == fa) continue;
        mx[0][to] = G.v[i].w; dfs(to, x);
    }
}
int query(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    int d = dep[y] - dep[x], ret = oo;
    FD(i, 18, 0) if ((d >> i) & 1) ret = min(ret, mx[i][y]), y = anc[i][y];
    if (x == y) return ret;
    FD(i, 18, 0) if (anc[i][x] != anc[i][y]) {
        ret = min(ret, mx[i][x]); ret = min(ret, mx[i][y]);
        x = anc[i][x], y = anc[i][y];
    }
    ret = min(ret, min(mx[0][x], mx[0][y]));
    return ret;
}

int main(void) {
    n = read(); m = read(); q = read();
    FO(i, 1, m) for (int j = i; j <= n; j += i) V[++cnt] = Edge{i, n + i, j};
    FO(i, 1, 18) mx[i][0] = oo;
    sort(V + 1, V + 1 + cnt);
    FO(i, 1, n + m) fa[i] = i; p = 0;
    FO(i, 1, cnt) {
        x = find(V[i].x); y = find(V[i].y);
        if (x == y) continue;
        p++; fa[x] = y;
        G.add(V[i].x, V[i].y, V[i].w);
        G.add(V[i].y, V[i].x, V[i].w);
        if (p == n + m - 1) break;
    }
    dfs(1, 0);
    while (q--) {
        x = read(); y = read();
        printf("%d\n", m - query(x, y) + 1);
    }
    return 0;
}
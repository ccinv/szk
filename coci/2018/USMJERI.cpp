#include <bits/stdc++.h>
using namespace std;

#define oo 0x3f3f3f3f
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define FO(i,a,b) for(int i=a;i<=b;++i)
#define FD(i,a,b) for(int i=a;i>=b;--i)
#define FE(i,G,x) for(int i=G.h[x];i!=-1;i=G.v[i].nxt)
typedef long long LL;
typedef pair<int, int> PII;

template <class T> inline bool chkmin(T& x, T y) { return x > y ? x = y, true : false; }
template <class T> inline bool chkmax(T& x, T y) { return x < y ? x = y, true : false; }

template <class T> T reads() {
    T x = 0;
    static int f;
    static char c;
    for (f = 1; !isdigit(c = getchar()); ) if (c == '-') f = -1;
    for (x = 0; isdigit(c); c = getchar()) x = x * 10 + c - 48;
    return x * f;
}
#define read   reads<int>
#define readll reads<LL>

#define MO 1000000007
int n, m, x, y, z, ans, low[300005], dep[300005], v[300005];
int anc[19][300005];
struct Graph {
    enum { maxn = 300005, maxm = 300005 * 4 };
    struct { int to, nxt, w; } v[maxm];
    int h[maxn], cnt;
    Graph() { memset(h, -1, sizeof(h)); }
    void clear() { cnt = 0; memset(h, -1, sizeof(h)); }
    void add(int x, int y, int w = 0) { v[cnt].w = w; v[cnt].nxt = h[x]; v[cnt].to = y; h[x] = cnt++; }
} G, P;

void pre(int x, int fa) {
    anc[0][x] = fa; low[x] = dep[x] = dep[fa] + 1;
    FO(i, 1, 18) anc[i][x] = anc[i - 1][anc[i - 1][x]];
    FE(i, G, x) {
        int to = G.v[i].to;
        if (to != fa) pre(to, x);
    }
}
int lca(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    int d = dep[y] - dep[x];
    FD(i, 18, 0) if ((d >> i) & 1) y = anc[i][y];
    if (x == y) return x;
    FD(i, 18, 0) if (anc[i][x] != anc[i][y]) x = anc[i][x], y = anc[i][y];
    return anc[0][x];
}
void build(int x, int fa) {
    FE(i, G, x) {
        int to = G.v[i].to;
        if (to == fa) continue;
        build(to, x); chkmin(low[x], low[to]);
        if (low[to] < dep[x]) P.add(x, to), P.add(to, x);
    }
}
bool color(int x, int c) {
    if (~v[x]) return v[x] == c; else v[x] = c;
    FE(i, P, x) if (!color(P.v[i].to, c ^ P.v[i].w)) return 0;
    return 1;
}

int main(void) {
    n = read(); m = read();
    FO(i, 1, n - 1) {
        x = read(); y = read();
        G.add(x, y); G.add(y, x);
    }
    pre(1, 0);
    FO(i, 1, m) {
        x = read(); y = read(); z = lca(x, y);
        chkmin(low[x], dep[z]); chkmin(low[y], dep[z]);
        if (x != z && y != z) P.add(x, y, 1), P.add(y, x, 1);
    }
    build(1, 0); fill_n(v + 1, n, -1); ans = 1;
    FO(i, 2, n) if (v[i] == -1)
        if (color(i, 0)) ans <<= 1, ans >= MO ? ans -= MO : 2333;
        else { ans = 0; break; }
    printf("%d\n", ans);
    return 0;
}
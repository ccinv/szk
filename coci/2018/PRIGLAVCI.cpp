#include <bits/stdc++.h>
using namespace std;

#define oo 0x3f3f3f3f
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
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

#define CLR(x,y) memset(x,y,sizeof(x))

namespace Dinic {

const int mn = 505;
const int mm = 500005;

template<typename T>
struct Graph {
    enum { maxn = mn, maxm = mm };
    struct Edge {
        int to, nxt;
        T w, cap, flow;
    } v[maxm];
    int h[maxn], cur[maxn], cnt;
    Graph() { memset(h, -1, sizeof(h)); }
    void clear() { cnt = 0; memset(h, -1, sizeof(h)); }
    void add1(int x, int y, T w, T cap) {
        v[cnt] = Edge {y, h[x], w, cap, 0};
        h[x] = cnt++;
    }
    void add(int x, int y, T w, T cap) {
        add1(x, y, w, cap);
        add1(y, x, -w, 0);
    }
};
Graph<int> G;

int f[mn], Ss, Se;
int dfs(int x, int re) {
    if (x == Se || re <= 0) return re;
    int s1 = 0, t;

    for (int& i = G.cur[x]; i != -1; i = G.v[i].nxt) {
        int to = G.v[i].to;
        if (f[to] != f[x] + 1) continue;
        t = dfs(to, min(re, G.v[i].cap - G.v[i].flow));
        G.v[i].flow += t;
        G.v[i ^ 1].flow -= t;
        s1 += t; re -= t;
        if (re == 0) break;
    }
    return s1;
}

bool bfs() {
    memcpy(G.cur, G.h, sizeof(G.h));
    queue<int> Q;
    CLR(f, -1); Q.push(Ss); f[Ss] = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        FE(i, G, u) {
            if (G.v[i].flow >= G.v[i].cap) continue;
            int to = G.v[i].to;
            if (f[to] != -1) continue;
            f[to] = f[u] + 1;
            if (to == Se) return 1;
            Q.push(to);
        }
    }
    return f[Se] != -1;
}

int MF() {
    int ans = 0;
    while (bfs()) ans += dfs(Ss, oo);
    return ans;
}

}
using namespace Dinic;

#define N 105
int n, m, c, k, x1[N], x2[N], yy[N], y2[N], ans[N], l, r, cnt;
vector<int> V[N];
struct Seg { int a, b, c; } lb[N * N];

#define sqr(x) ((x)*(x))
inline int dist(int x, int y) { return sqr(x1[x] - x2[y]) + sqr(yy[x] - y2[y]); }
bool ck(int x) {
    G.clear();
    Ss = n + m + k + 1, Se = n + m + k + 2; cnt = 0;
    FO(i, 1, n) G.add(Ss, i, 0, 1);
    FO(i, 1, n) FO(j, 1, m) if (dist(i, j) <= x) lb[++cnt] = Seg {i, j, G.cnt}, G.add(i, j + n, 0, 1);
    FO(i, 1, k) for (auto x : V[i]) G.add(x + n, n + m + i, 0, c);
    FO(i, 1, k) G.add(n + m + i, Se, 0, c);
    return MF() == n;
}

int main(void) {
    n = read(); m = read(); c = read(); k = read();
    FO(i, 1, n) x1[i] = read(), yy[i] = read();
    FO(i, 1, m) x2[i] = read(), y2[i] = read();
    FO(i, 1, k) { int p = read(); FO(j, 1, p) V[i].push_back(read()); }

    l = 0; r = 1e9;
    if (!ck(r)) return puts("-1"), 0;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (ck(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", l); ck(l);
    FO(i, 1, cnt) if (G.v[lb[i].c].flow == 1) ans[lb[i].a] = lb[i].b;
    FO(i, 1, n) printf("%d\n", ans[i]);
    return 0;
}
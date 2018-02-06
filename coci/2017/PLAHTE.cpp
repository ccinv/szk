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

typedef int Arr[160005];
int n, m, cnt, cnt1, cnt2;
PII a[80005], b[80005], c[80005], M[80005 * 4];
Arr w, id, in, ans, son, fa, dfn, ddfn, V, C, size;
stack<PII> S[160005 * 4];
struct Graph {
    enum { maxn = 80005, maxm = 200005 };
    struct { int to, nxt; } v[maxm];
    int h[maxn], cnt;
    Graph() { memset(h, -1, sizeof(h)); }
    void clear() { cnt = 0; memset(h, -1, sizeof(h)); }
    void add(int x, int y) { v[cnt].nxt = h[x]; v[cnt].to = y; h[x] = cnt++; }
} G, L;

#define LS x<<1
#define RS x<<1|1
#define MID (l+r>>1)

struct {
    int a[80005], ans;
    void clear() { memset(a, 0, sizeof(a)); ans = 0; }
    void add(int x) { if (!a[x]) ans++; a[x]++; }
    void del(int x) { a[x]--; if (!a[x]) ans--; }
} D;

void query(int x, int l, int r, int pos, PII& o) {
    if (!S[x].empty()) if (chkmax(o.fi, S[x].top().fi)) o.se = S[x].top().se;
    if (l == r) return ;
    if (pos <= MID) query(LS, l, MID, pos, o); else query(RS, MID + 1, r, pos, o);
}
void upd(int x, int l, int r, int ll, int rr, int v, int t) {
    if (l >= ll && r <= rr) { if (v != -1) S[x].push(mp(t, v)); else S[x].pop(); return ; }
    if (r < ll || l > rr) return ;
    upd(LS, l, MID, ll, rr, v, t); upd(RS, MID + 1, r, ll, rr, v, t);
}

inline void put(int l, int r) { FO(i, l, r)FE(j, L, ddfn[i]) D.add(L.v[j].to); }
inline void erase(int l, int r) { FO(i, l, r)FE(j, L, ddfn[i]) D.del(L.v[j].to); }
void dfs1(int x) {
    size[x] = 1; int maxx = -1;
    FE(i, G, x) {
        int to = G.v[i].to;
        if (to == fa[x]) continue;
        dfs1(to); size[x] += size[to]; w[x] += w[to];
        if (chkmax(maxx, w[to])) son[x] = to;
    }
}
void dfsn(int x) {
    dfn[x] = ++dfn[0]; ddfn[dfn[x]] = x;
    FE(i, G, x) {
        int to = G.v[i].to;
        if (to == fa[x] || to == son[x]) continue;
        dfsn(to);
    }
    if (son[x]) dfsn(son[x]);
}
void dfs(int x) {
    FE(i, G, x) {
        int to = G.v[i].to;
        if (to == fa[x] || to == son[x]) continue;
        dfs(to); erase(dfn[to], dfn[to] + size[to] - 1);
    }
    if (son[x]) dfs(son[x]), put(dfn[x], dfn[son[x]] - 1);
    else put(dfn[x], dfn[x]);
    ans[x] = D.ans;
}

void trans1(int& x) { x = lower_bound(V + 1, V + 1 + cnt1, x) - V; }
void trans2(int& x) { x = lower_bound(C + 1, C + 1 + cnt2, x) - C; }

int main(void) {
    n = read(); m = read();
    FO(i, 1, n) {
        a[i].fi = read(), a[i].se = read(), b[i].fi = read(), b[i].se = read();
        V[++cnt1] = a[i].se; V[++cnt1] = b[i].se;
    }
    FO(i, 1, m) {
        c[i].fi = read(), c[i].se = read(), id[i] = read();
        C[++cnt2] = id[i], V[++cnt1] = c[i].se;
    }
    sort(V + 1, V + 1 + cnt1); cnt1 = unique(V + 1, V + 1 + cnt1) - (V + 1);
    sort(C + 1, C + 1 + cnt2); cnt2 = unique(C + 1, C + 1 + cnt2) - (C + 1);
    FO(i, 1, n) trans1(a[i].se), trans1(b[i].se); FO(i, 1, m) trans1(c[i].se);
    FO(i, 1, m) trans2(id[i]);

    // Building graph
    FO(i, 1, n) M[++cnt] = mp(a[i].fi, i);
    FO(i, 1, n) M[++cnt] = mp(b[i].fi, i + n + m);
    FO(i, 1, m) M[++cnt] = mp(c[i].fi, i + n);
    sort(M + 1, M + 1 + cnt);
    FO(i, 1, cnt) {
        if (M[i].se > n && M[i].se <= n + m) {
            int p = M[i].se - n; PII o = mp(0, -1);
            query(1, 1, cnt1, c[p].se, o);
            if (o.se != -1) L.add(o.se, id[p]), w[o.se]++;
        } else {
            if (M[i].se <= n) {
                PII o = mp(0, -1);
                query(1, 1, cnt1, a[M[i].se].se, o);
                if (o.se != -1) { G.add(o.se, M[i].se); fa[M[i].se] = o.se; in[M[i].se]++; }
                upd(1, 1, cnt1, a[M[i].se].se, b[M[i].se].se, M[i].se, i);
            } else upd(1, 1, cnt1, a[M[i].se - n - m].se, b[M[i].se - n - m].se, -1, i);
        }
    }

    // DSU on Tree
    FO(i, 1, n) if (!in[i]) dfs1(i);
    FO(i, 1, n) if (!in[i]) dfsn(i);
    FO(i, 1, n) if (!in[i]) D.clear(), dfs(i);
    FO(i, 1, n) printf("%d\n", ans[i]);
    return 0;
}
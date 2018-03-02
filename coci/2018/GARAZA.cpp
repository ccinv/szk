#include <bits/stdc++.h>
using namespace std;

#define oo 0x3f3f3f3f
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define FO(i,a,b) for (int i=(a);i<=(b);++i)
#define FD(i,a,b) for (int i=(a);i>=(b);--i)
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

#define gcd __gcd
struct Seg {
    vector<PII> L, R;
    LL cnt; int all;
    static vector<PII> merge(int all, const vector<PII>& a, const vector<PII>& b) {
        vector<PII> ret(a);
        for (const auto& x : b) {
            int g = gcd(x.fi, all);
            if (g == 1) break;
            if (ret.empty() || g != ret.back().fi) ret.push_back(mp(g, x.se));
            else ret.back().se += x.se;
        }
        return ret;
    }
    static LL cross(const vector<PII>& a, const vector<PII>& b) {
        LL ret = 0;
        for (const auto& x : a)
            for (const auto& y : b)
                if (gcd(x.fi, y.fi) > 1) ret += (LL)x.se * y.se;
                else break;
        return ret;
    }
    Seg operator +(const Seg& o) {
        Seg ret;
        ret.L = merge(all, L, o.L); ret.R = merge(o.all, o.R, R);
        ret.cnt = cnt + o.cnt + cross(R, o.L);
        ret.all = gcd(all, o.all);
        return ret;
    }
    void init(int x) {
        all = x; L.clear(); R.clear(); cnt = 0;
        if (all != 1) {
            cnt = 1;
            L.push_back(mp(x, 1)); R = L;
        }
    }
};

#define N 80005
Seg T[4 * N];
int n, q, op, l, r;

#define LS x << 1
#define RS x << 1 | 1
#define MID (l + r >> 1)
void build(int x, int l, int r) {
    if (l == r)  return T[x].init(read()), (void)0;
    build(LS, l, MID); build(RS, MID + 1, r);
    T[x] = T[LS] + T[RS];
}
void update(int x, int l, int r, int pos, int v) {
    if (l == r) { T[x].init(v); return ; }
    if (pos <= MID) update(LS, l, MID, pos, v);
    else update(RS, MID + 1, r, pos, v);
    T[x] = T[LS] + T[RS];
}
Seg query(int x, int l, int r, int ll, int rr) {
    if (l >= ll && r <= rr) return T[x];
    if (MID >= rr) return query(LS, l, MID, ll, rr);
    if (MID <  ll) return query(RS, MID + 1, r, ll, rr);
    return query(LS, l, MID, ll, rr) + query(RS, MID + 1, r, ll, rr);
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    n = read(); q = read();
    build(1, 1, n);
    while (q--) {
        op = read(); l = read(); r = read();
        if (op == 2) printf("%lld\n", query(1, 1, n, l, r).cnt);
        else update(1, 1, n, l, r);
    }
    return 0;
}

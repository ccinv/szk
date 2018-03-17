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

#define N 300005
struct Seg { int l, r, x; } T[N * 120];
int n, m, op, x, c, la, cnt, d[N], rt[N];
#define MID (l+r>>1)
int query(int x, int l, int r, int pos) {
    if (l == r) return T[x].x;
    if (pos <= MID) return query(T[x].l, l, MID, pos);
    else return query(T[x].r, MID + 1, r, pos);
}
int modify(int k, int l, int r, int pos, int v) {
    int x = ++cnt; T[x] = T[k];
    if (l == r) return T[x].x = v, x;
    if (pos <= MID) T[x].l = modify(T[x].l, l, MID, pos, v);
    else T[x].r = modify(T[x].r, MID + 1, r, pos, v);
    return x;
}

int main(void) {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    n = read(); m = read(); op = read();
    FO(i, 1, n) {
        x = read(); c = read();
        if (op) x ^= la, c ^= la;
        d[i] = d[x] + 1;
        int z = query(rt[x], 0, n, x);
        int nxt = query(z, 1, m, c);
        printf("%d\n", (la = (d[i] - d[nxt])));
        rt[i] = modify(rt[x], 0, n, x, modify(z, 1, m, c, i));
        rt[i] = modify(rt[i], 0, n, i, query(rt[i], 0, n, nxt));
    }
    return 0;
}

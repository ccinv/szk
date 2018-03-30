// FBI warning: O(p^4) version

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

#define N 205
#define M 200005
#define MO 998244353

int n, m, p, q, fac[M], nfac[M], a[N], b[N], f[N], g[N][N], cnt;
PII c[N], d[N];

inline LL ppow(LL a, LL b) {
    LL ret = 1;
    for (; b; b >>= 1) {
        if (b & 1) ret = ret * a % MO;
        a = a * a % MO;
    }
    return ret;
}
inline void R(int& x) { if (x >= MO) x -= MO; }
inline int walk(int x, int y) { return 1ll * fac[x + y] * nfac[x] % MO * nfac[y] % MO; }
int calc(int st, int ed) {
    if (ed < st) return 0;
    cnt = 0; FO(i, 1, q) if (c[i].se >= st && c[i].se <= ed) d[++cnt] = c[i];
    d[++cnt] = mp(n, ed); sort(d + 1, d + 1 + cnt);
    FO(i, 1, cnt) {
        f[i] = walk(d[i].fi, d[i].se - st);
        FO(j, 1, i - 1) if (d[j].fi <= d[i].fi && d[j].se <= d[i].se) {
            f[i] -= 1ll * f[j] * walk(d[i].fi - d[j].fi, d[i].se - d[j].se) % MO;
            R(f[i] += MO);
        }
    }
    return f[cnt];
}
int det() {
    int ans = 1, t;
    FO(i, 1, p)FO(j, i + 1, p)
    while (g[j][i]) {
        t = g[i][i] / g[j][i];
        FO(z, i, p) {
            R(g[i][z] = g[i][z] - 1ll * g[j][z] * t % MO + MO);
            swap(g[i][z], g[j][z]);
        }
        ans *= -1;
    }
    FO(i, 1, p) ans = 1ll * ans * g[i][i] % MO;
    return R(ans += MO), ans;
}

int main(void) {
    freopen("canal.in","r",stdin);
    freopen("canal.out","w",stdout);
    n = read(); m = read(); p = read(); q = read();
    fac[0] = nfac[0] = 1;
    FO(i, 1, n + m) fac[i] = 1ll * fac[i - 1] * i % MO;
    FO(i, 1, n + m) nfac[i] = ppow(fac[i], MO - 2);
    FO(i, 1, p) a[i] = read(); sort(a + 1, a + 1 + p);
    FO(i, 1, p) b[i] = read(); sort(b + 1, b + 1 + p);
    FO(i, 1, q) c[i].fi = read(), c[i].se = read();
    FO(i, 1, p)FO(j, 1, p) g[i][j] = calc(a[i], b[j]);
    printf("%d\n", det());
    return 0;
}


#include <bits/stdc++.h>
using namespace std;

#define oo (1ll<<60)
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

#define N 5005
LL f[N];
int n, x, y, a[N], b[N], lg[N], g[15][N];
map<int, int> M;

inline int query(int x, int y) {
    int l = y - x + 1, p = lg[l];
    return max(g[p][x], g[p][y - (1 << p) + 1]);
}

int main(void) {
    n = read();
    FO(i, 1, n) {
        x = read(); y = read();
        if (x < 0) x = -x; if (y < 0) y = -y;
        M[x] = max(M[x], y);
    }
    n = 0;
    for (auto it = M.begin(); it != M.end(); ++it)
        a[++n] = it->fi, b[n] = it->se;

    lg[1] = 0; FO(i, 2, n) lg[i] = lg[i >> 1] + 1;
    FO(i, 1, n) g[0][i] = b[i];
    for (int i = 1; (1 << i) <= n; ++i) FO(j, 1, n - (1 << i) + 1)
        g[i][j] = max(g[i - 1][j] , g[i - 1][j + (1 << (i - 1))]);

    FO(i, 1, n) f[i] = oo; f[0] = 0;
    FO(i, 1, n) FO(j, 0, i - 1)  f[i] = min(f[i], f[j] + 1ll * query(j + 1, i) * a[i]);
    printf("%lld\n", f[n] * 4);
    return 0;
}
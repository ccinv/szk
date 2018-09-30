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

#define N 10005
int n, m, k, a[N], f[N][N / 2];

int main(void) {
    n = read(); m = read(); k = read();
    FO(i, 0, n - 1) a[i] = read();
    FO(i, n, 10000) a[i] = a[i % n];
    FO(i, 1, 10000) f[i][m] = a[i - 1] != a[i];
    FO(j, 0, m - 1) f[10000][j] = 1;

    FD(j, m - 1, 0)FD(i, 9999, 0) {
        int l = j + 1, r = min(j + k, m);
        if (a[i] != a[i + 1]) f[i][j] = (f[i + 1][l] - f[i + 1][r + 1]) != r - l + 1;
        else f[i][j] = f[i + 1][l] - f[i + 1][r + 1] > 0;
        f[i][j] += f[i][j + 1];
    }
    FO(i, 0, n - 1) printf("%d ", f[i][0] - f[i][1] ? a[i] : !a[i]);
    return 0;
}
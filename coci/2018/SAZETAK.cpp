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

#define MAXM 15
#define MAXS 1100

int m, S;
LL n, ans, a[MAXM], b[MAXS];

LL exgcd(LL a, LL b, LL& x, LL& y) {
    if (b == 0) return x = 1, y = 0, a;
    LL d = exgcd(b, a % b, x, y);
    LL z = x; x = y; y = z - a / b * y;
    return d;
}
LL solve(LL a, LL b) {
    LL x, y;
    LL g = exgcd(a, b, x, y);
    if (g != 1) return 0;
    LL k = b / g; x = (x % k + k) % k;
    LL p = n / a;
    return p / k + (x % k <= p % k);
}

int main(void) {
    n = read(); m = read();
    FO(i, 0, m - 1) a[i] = read();
    FO(i, 0, m - 1) if (n % a[i] == 1) { ans = 1; n--; break; }

    S = (1 << m) - 1;
    FO(s, 1, S) {
        LL x = 1;
        FO(i, 0, m - 1) if ((s >> i) & 1) {
            x = x / __gcd(x, a[i]) * a[i];
            if (x > n) { x = -1; break; }
        }
        b[s] = x;
    }
    FO(s, 1, S) {
        for (int x = (s - 1)&s; x; x = (x - 1)&s) {
            int y = s ^ x;
            if ((~b[x]) && (~b[y]))
                ans += (__builtin_popcount(s) % 2 ? -1 : 1) *
                       solve(b[x], b[y]);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
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

typedef unsigned long long U;
#define N ((1 << 20) + 5)

LL ans; U f[N];
int m, s, p[N], a[N];
unordered_map<U, int> M[4];

mt19937_64 g1(19260817);

int main(void) {
    m = read();s = (1 << m) - 1;
    if (m == 1) return puts("2"), 0;
    FO(i, 0, s) a[i] = read(), p[a[i]]=i;
    FO(i, 0, s/2) f[p[i]]=g1(), f[p[s ^ i]] = f[p[i]];

    M[3][0]=1;
    FO(i, 0, s){
        f[i] ^= f[i -1];
        ans += M[i % 4][f[i]];M[i % 4][f[i]]++;
    }
    printf("%lld\n",1ll * (s + 1) * (s + 2) / 2 - ans);
    return 0;
}

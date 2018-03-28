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

#define N 6000010
char s[3005], S[N * 2];
int c, l, tmp, cnt; char cur[N];

void sc(int x, char fa) {
    while (cur[x] < c) {
        ++cur[x];
        sc(x % tmp * c + cur[x] - 1, cur[x] - 1);
    }
    if (~fa) S[++cnt] = s[fa];
}

int main(void) {
    freopen("life.in", "r", stdin);
    freopen("life.out", "w", stdout);
    scanf("%d%d%s", &c, &l, s);
    printf("%d\n", (int)(pow(c, l) + l - 1));
    if (l > 1) {
        memset(cur, 0, sizeof(cur));
        tmp = pow(c, l - 2);
        FO(i, 1, l - 1) putchar(s[0]);
        sc(0, -1);
        reverse(S + 1, S + 1 + cnt); puts(S + 1);
    } else puts(s);
    return 0;
}


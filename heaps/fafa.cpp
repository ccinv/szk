#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace std::chrono;

#define oo 0x3f3f3f3f
#define fi first
#define se second
#define FO(i,a,b) for (int i=(a);i<=(b);++i)
#define FD(i,a,b) for (int i=(a);i>=(b);--i)
#define FE(i,G,x) for(int i=(G).h[x];~i;i=(G).v[i].nxt)
typedef long long LL;
typedef pair<int, int> PII;

template <class T> inline bool chkmin(T& x, T y) { return x > y ? x = y, true : false; }
template <class T> inline bool chkmax(T& x, T y) { return x < y ? x = y, true : false; }

class Heap {
  public:
    virtual int pop() = 0;
    virtual void push(int x) = 0;
    virtual bool empty() = 0;
    virtual const char* getName() = 0;
};

template<size_t MAXN>
class ZkwHeap: public Heap {
    PII P[4 * MAXN + 10];
    int M, ncnt, rem, nxt[MAXN + 5];
    inline int alloc() {
        if (nxt[0]) {
            int ret = nxt[0];
            nxt[0] = nxt[nxt[0]];
            return ret;
        }
        return ++ncnt;
    }
    inline void pushup(int o) {
#define lson (o<<1)
#define rson (o<<1|1)
        P[o] = P[lson].se < P[rson].se ? P[lson] : P[rson];
#undef lson
#undef rson
    }
    void build(int n) {
        for (M = 1; M < n; M <<= 1);
        FO(i, 1, (M << 1) - 1) P[i].se = oo;
        FO(i, 1, n) P[i + M].fi = i;
    }
    inline void modify(int pos, int val) {
        for (P[pos += M].se = val; pos != 1; pos >>= 1) pushup(pos >> 1);
    }
  public:
    ZkwHeap() { build(MAXN); }
    void push(int x) { modify(alloc(), x); rem++; }
    int pop() {
        int ret = P[1].se;
        nxt[P[1].fi] = nxt[0];
        nxt[0] = P[1].fi;
        modify(P[1].fi, oo); rem--;
        return ret;
    }
    bool empty() { return !rem; }
    const char* getName() { return "ZkwHeap(Array Ver)"; }
};

template<size_t MAXN>
class SkewHeapP: public Heap {
    struct node { node* l, *r; int sum; }* root;
    node* merge(node* x, node* y) {
        if (!x || !y) return x ? x : y;
        if (x->sum > y->sum) swap(x, y);
        x->r = merge(x->r, y);
        swap(x->l, x->r);
        return x;
    };
  public:
    void push(int x) { root = merge(root, new node{ nullptr, nullptr, x }); }
    int pop() {
        int ret = root->sum;
        node* _ = root;
        root = merge(root->l, root->r);
        delete _;
        return ret;
    }
    bool empty() { return root == nullptr; }
    const char* getName() { return "SkewHeap(Pointer Ver)"; }
};

template<size_t MAXN>
class SkewHeapA: public Heap {
    int root, ncnt, nxt[MAXN + 5];
    struct node { int l, r; int sum; } P[MAXN + 5];
    inline int alloc() {
        if (nxt[0]) {
            int ret = nxt[0];
            nxt[0] = nxt[nxt[0]];
            return ret;
        }
        return ++ncnt;
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (P[x].sum > P[y].sum) swap(x, y);
        P[x].r = merge(P[x].r, y);
        swap(P[x].l, P[x].r);
        return x;
    }
  public:
    void push(int x) { int _ = alloc(); P[_] = { 0, 0, x }; root = merge(root, _); }
    int pop() {
        int ret = P[root].sum;
        nxt[root] = nxt[0];
        nxt[0] = root;
        root = merge(P[root].l, P[root].r);
        return ret;
    }
    bool empty() { return !root; }
    const char* getName() { return "SkewHeap(Array Ver)"; }
};

template<size_t MAXN>
class StdPriorityQueue: public Heap {
    priority_queue<int, vector<int>, greater<int> > Q;
  public:
    void push(int x) { Q.push(x); }
    int pop() {
        int ret = Q.top(); Q.pop();
        return ret;
    }
    bool empty() { return Q.empty(); }
    const char* getName() { return "std::priority_queue"; }
};

template<size_t MAXN>
class PairingHeap: public Heap {
    __gnu_pbds::priority_queue<int, greater<int>, __gnu_pbds::pairing_heap_tag> Q;
  public:
    void push(int x) { Q.push(x); }
    int pop() {
        int ret = Q.top(); Q.pop();
        return ret;
    }
    bool empty() { return Q.empty(); }
    const char* getName() { return "pb_ds::pairing_heap"; }
};

template<size_t MAXN>
class Tester {
    int num[MAXN + 5];
    bool ins[2 * MAXN + 5];
  public:
    Tester() {
        mt19937 Rand((unsigned size_t)(new char));
        FO(i, 1, MAXN) num[i] = Rand() % MAXN;
        FO(i, 1, 2 * MAXN) ins[i] = Rand() % 2;
    }
    void test(Heap* x) {
        int cnt = 0, chk = 0;
        auto c = steady_clock::now();
        FO(i, 1, MAXN * 2) {
            int s = ins[i];
            if (s || x->empty()) x->push(num[++cnt]);
            else chk ^= i * x->pop();
        }
        auto ms = duration_cast<chrono::milliseconds>(steady_clock::now() - c);
        printf("%d\t%d\t%d\n", ms.count(), MAXN, chk);
    }
};

template<size_t MAXN>
void mk() {
    auto T = make_shared<Tester<MAXN> >();
#define DO(x) \
    { auto p = make_shared<x<MAXN> >(); \
        T->test((Heap*)p.get()); \
    }
    DO(ZkwHeap);
    DO(SkewHeapA);
    DO(SkewHeapP);
    DO(StdPriorityQueue);
    DO(PairingHeap);
    puts("");
#undef DO
}

int main(void) {
    mk<30000>();
    mk<300000>();
    mk<3000000>();
    mk<6000000>();
    mk<9000000>();
    return 0;
}

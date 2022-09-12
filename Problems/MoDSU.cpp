#include <bits/stdc++.h>
    
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
    
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 5e4 + 5;
const int INF = 2e9;
 
const int X = 225;

struct que {
	int ans, l, r, b, id;
};
 
int resp, ra, cnt;
vector<que> qs;
pii ed[MAXN];
int pai[MAXN], sz[MAXN];
stack<int> st;

int find(int x) {
    if (x == pai[x]) return x;
    return find(pai[x]);
}
 
void join(int a, int b) {
    a = find(a), b = find(b);
    if (sz[a] < sz[b]) {
        swap(a, b);
    }
    pai[b] = a;
    sz[a] += sz[b];
    st.push(b);
    resp--;
}

void rollback() {
    int at = st.top();
    st.pop();
    sz[pai[at]] -= sz[at];
    pai[at] = at;
    resp++;
}

int main() { 
    ios::sync_with_stdio(false);
    cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> ed[i].first >> ed[i].second;
	}
    int q;
    cin >> q;
    que aux;
	for (int i = 0; i < q; i++) {
		cin >> aux.l >> aux.r;
		aux.id = i;
		aux.b = aux.l/X;
		qs.push_back(aux);
	}
	sort(qs.begin(), qs.end(), [&] (que x, que y) {
		if (x.b != y.b) return x.b < y.b;
		return x.r < y.r;
	});
	for (int i = 0; i < q; i++) {
		if (i == 0 || qs[i].b != qs[i - 1].b) {
			// new batch
            while (!st.empty()) st.pop();
            for (int j = 1; j <= n; j++) {
                sz[j] = 1;
                pai[j] = j;
            }
			resp = n, ra = (qs[i].b + 1) * X - 1;
		}
        if (qs[i].r < (qs[i].b + 1) * X) {
            // naive
            for (int j = qs[i].l; j <= qs[i].r; j++) {
                if (find(ed[j].first) != find(ed[j].second)) {
                    cnt++;
                    join(ed[j].first, ed[j].second);
                }
            }
            qs[i].ans = resp;
            while (cnt) {
                rollback();
                cnt--;
            }
        }
        else {
            for (int j = ra + 1; j <= qs[i].r; j++) {
                if (find(ed[j].first) != find(ed[j].second)) {
                    join(ed[j].first, ed[j].second);
                }
            }
            for (int j = qs[i].l; j < (qs[i].b + 1) * X; j++) {
                if (find(ed[j].first) != find(ed[j].second)) {
                    cnt++;
                    join(ed[j].first, ed[j].second);
                }
            }
            ra = qs[i].r;
            qs[i].ans = resp;
            while (cnt) {
                rollback();
                cnt--;
            }
        }
	}

	sort(qs.begin(), qs.end(), [&] (que x, que y) { return x.id < y.id; });
	for (que x : qs) cout << x.ans << '\n';
    return 0;
}
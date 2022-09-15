#include <bits/stdc++.h>
    
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
    
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
const int INF = 2e9;
 
const int X = 400;

struct que {
	int ans, l, r, b, id;
};
 
int resp, ra, cnt;
vector<que> qs;
pii ed[MAXN];
int pai[MAXN], sz[MAXN], len[MAXN];
stack<pii> st;

pii find(int x) {
    if (x == pai[x]) return {x, len[x]};
    pii ans = find(pai[x]);
    return {ans.first, ans.second ^ len[x]};
}
 
void join(int a, int b) {
    pii c = find(a), d = find(b);
    if (sz[c.first] < sz[d.first]) {
        swap(c, d);
    }
    pai[d.first] = c.first;
    sz[c.first] += sz[d.first];
    st.push({d.first, len[d.first]});
    len[d.first] = 1 ^ c.second ^ d.second;
}

void rollback() {
    pii at = st.top();
    st.pop();
    if (at.first) {
        sz[pai[at.first]] -= sz[at.first];
        len[at.first] = at.second;
        pai[at.first] = at.first;
    }
    else resp = 1;
}

int main() { 
    ios::sync_with_stdio(false);
    cin.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 1; i <= m; i++) {
		cin >> ed[i].first >> ed[i].second;
	}
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
                len[j] = 0;
            }
			resp = 1, ra = (qs[i].b + 1) * X - 1;
		}
        if (qs[i].r < (qs[i].b + 1) * X) {
            // naive
            for (int j = qs[i].l; j <= qs[i].r; j++) {
                pii c = find(ed[j].first), d = find(ed[j].second);
                if (c.first != d.first) {
                    cnt++;
                    join(ed[j].first, ed[j].second);
                }
                else {
                    if (resp == 1 && c.second ^ d.second == 0) {
                        cnt++;
                        resp = 0;
                        st.push({0, 0});
                    }
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
                pii c = find(ed[j].first), d = find(ed[j].second);
                if (c.first != d.first) {
                    join(ed[j].first, ed[j].second);
                }
                else {
                    if (resp == 1 && c.second ^ d.second == 0) {
                        resp = 0;
                        st.push({0, 0});
                    }
                }
            }
            for (int j = qs[i].l; j < (qs[i].b + 1) * X; j++) {
                pii c = find(ed[j].first), d = find(ed[j].second);
                if (c.first != d.first) {
                    cnt++;
                    join(ed[j].first, ed[j].second);
                }
                else {
                    if (resp == 1 && c.second ^ d.second == 0) {
                        cnt++;
                        resp = 0;
                        st.push({0, 0});
                    }
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
	for (que x : qs) cout << (x.ans ? "Possible\n" : "Impossible\n");
    return 0;
}
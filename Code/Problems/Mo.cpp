const int X = 700;
 
struct que {
	int ans, l, r, b, id;
};
 
vector<que> qs;
 
int main() {
	int n, q;
	cin >> n >> q;
    // probably receive some input here
	que aux;
	for (int i = 0; i < q; i++) {
		cin >> aux.l >> aux.r;
		aux.id = i;
		aux.l--, aux.r--;
		aux.b = aux.l/X;
		qs.pb(aux);
	}
	sort(qs.begin(), qs.end(), [&] (que x, que y) {
		if (x.b != y.b) return x.b < y.b;
		return x.r < y.r;
	});
	int la, ra, resp;
	for (int i = 0; i < q; i++) {
		if (i == 0 || qs[i].b != qs[i-1].b) {
			// new batch
            // initialize resp
			resp = 0;
			for (int j = qs[i].l; j <= qs[i].r; j++) {
                // go forward
			}
		}
		else {
			for (int j = ra+1; j <= qs[i].r; j++) {
                // go forward
			}
			for (int j = la-1; j >= qs[i].l; j--) {
                // go backwards
			}
			for (int j = la; j < qs[i].l; j++) {
                // go forward
			}
		}
		qs[i].ans = resp;
		la = qs[i].l, ra = qs[i].r;
	}
	sort(qs.begin(), qs.end(), [&] (que x, que y) { return x.id < y.id; });
	for (que x : qs) cout << x.ans << '\n';
    return 0;
}
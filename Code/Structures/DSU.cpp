// Union find (DSU)
//

class DSU {
public:
		void init(int _n, bool _compress = true) {
			n = _n;
			qt = _n;
			compress = _compress;
			size.assign(n + 1, 1);
			for(int i = 0; i <= n; i++) {
				pai.push_back(i);
			}
		}

		int find(int v) {
			if(pai[v] == v) return v;
			if(compress) {
				return pai[v] = find(pai[v]);
			}
			return find(pai[v]);
		}

		void join(int a, int b) {
			a = find(a); b = find(b);
			if(a == b) return;
			if(size[a] > size[b]) swap(a, b);
			size[b] += size[a];
			pai[a] = b;
			roll.push_back(a);
			qt--;
		}

		void rollback() {
			if(roll.empty()) return;
			int cur = roll[roll.size() - 1];
			roll.pop_back();
			size[pai[cur]] -= size[cur];
			pai[cur] = cur;
			qt++;
			return;
		}

		int getQt() {
			return qt;
		}


private:
		int n, qt;
		bool compress;
		vector <int> size, pai, roll;
};
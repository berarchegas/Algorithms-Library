// Union find (DSU) bipartido
// com bipartição (errado)

class DSU {
public:
		void init(int _n) {
			n = _n;
			qt = _n;
            bipartite = 1;
			size.assign(n + 1, 1);
            len.assign(n + 1, 0);
			for(int i = 0; i <= n; i++) {
				pai.push_back(i);
			}
		}

		pii find(int v) {
			if(pai[v] == v) return {v, len[v]};
			pii resp = find(pai[v]);
            return {resp.first, resp.second ^ len[v]};
		}

		void join(int a, int b) {
			pii x = find(a), y = find(b);
			if(x == y) {
                if(x.second == y.second) {
                    rollb.push_back(bipartite);
                    bipartite = false;
                }
                else {
                    rollb.push_back(bipartite);
                }
                roll.push_back({-1, -1});
                return;
            }
			if(size[x.first] > size[y.first]) swap(x, y);
            roll.push_back({x.first, len[x.first]});
			size[y.first] += size[x.first]; 
			pai[x.first] = y.first;
            len[x.first] = (x.second ^ y.second ^ 1);
            rollb.push_back(bipartite);
			qt--;
		}

		void rollback() {
			if(roll.empty()) return;
			pii cur = roll[roll.size() - 1];
			roll.pop_back();
            bipartite = rollb[rollb.size() - 1];
            rollb.pop_back();
            if(cur.first == -1) return;
			size[pai[cur.first]] -= size[cur.first];
			pai[cur.first] = cur.first;
            len[cur.first] = cur.second;
			qt++;
			return;
		}

		int getQt() {
			return qt;
		}

        int getBp() {
            return bipartite;
        }

private:
		int n, qt;
        bool bipartite;
		vector <int> size, pai, len;
        vector <pii> roll;
        vector <bool> rollb;
};
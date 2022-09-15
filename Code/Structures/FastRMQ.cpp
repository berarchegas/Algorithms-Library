// Fast RMQ using Sparse Table
//
// O(N) preprocessing, O(1) query Range Minimum Query
// qry(l, r) returns min from l to r - 1 (0 indexed)
template<class T>
class FastRMQ {
public:
	void init(const vector<T> &a) {
		original = a;
		int n = (int) a.size();
		if(n == 0) return;
		e = 1;
		while((1 << e) < n) e++;
		vector<T> groups;
		for(int i = 0; i < n; i++) {
			if(i % e == 0) {
				groups.push_back(a[i]);
			} else if(a[i] < groups.back()) {
				groups.back() = a[i];
			}
		}
		table.init(groups);
		mask.resize(n);
		for(int i = 0, curMask = 0; i < n; i++) {
			curMask = (curMask << 1) & ((1 << e) - 1);
			while(curMask) {
				int j = i - table.getPos(curMask & -curMask);
				if(a[i] < a[j]) {
					curMask ^= curMask & -curMask;
				} else {
					break;
				}
			}
			curMask |= 1;
			mask[i] = curMask;
		}
	}

	T qry(int l, int r) {
		// query in [l, r)
		if(r - l <= e) {
			return i_qry(r-1, r-l);
		} else {
			T ans = min(i_qry(l+e-1, e), i_qry(r-1, e));
			if(l / e + 1 < r / e) {
				ans = min(ans, table.qry(l / e + 1, r / e));
			}
			return ans;
		}
	}
private:
	int e;
	SparseTable<T> table;
	vector<T> original;
	vector<int> mask;

	T i_qry(int r, int size) {
		int curMask = mask[r] & ((1 << size) - 1);
		int pos = r - table.getPos(curMask);
		return original[pos];
	}
};
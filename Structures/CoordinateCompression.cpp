// 0 indexed
// if x is in arr, getL returns the compressed id of x and getR returns id + 1
// getR is unnecessary most times
// getVal returns the original value that corresponds to id

template<class T>
class CoordinateCompression {
public:
	CoordinateCompression(const vector<T> &a) {
		arr = a;
		sort(arr.begin(), arr.end());
		arr.resize(unique(arr.begin(), arr.end()) - arr.begin());
	}

	int getL(T x) { return lower_bound(arr.begin(), arr.end(), x) - arr.begin(); }
	int getR(T x) { return upper_bound(arr.begin(), arr.end(), x) - arr.begin(); }
    T getVal(int id) { return arr[id]; }
	int size() const { return (int) arr.size(); }
private:
	vector<T> arr;
};
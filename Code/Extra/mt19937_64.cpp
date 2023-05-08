// mt19937_64
//
// Random generator for long long

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());
ll rand = rng();
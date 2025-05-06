#include <bits/stdc++.h>
using namespace std;

#define int long long

struct RollingHash {
    static const int HASH_SIZE = 2;
    static const int BASES[HASH_SIZE];
    static const int MODS[HASH_SIZE];

    vector<int> hashval;

    RollingHash() {
        hashval.assign(HASH_SIZE, 0);
    }

    RollingHash(const string& s) {
        hashval.assign(HASH_SIZE, 0);
        for (char c : s) {
            for (int i = 0; i < HASH_SIZE; ++i) {
                hashval[i] = (hashval[i] * BASES[i] + c) % MODS[i];
            }
        }
    }

    bool operator==(const RollingHash& other) const {
        return hashval == other.hashval;
    }
};

// Static member initialization
const int RollingHash::BASES[HASH_SIZE] = {911, 3571};
const int RollingHash::MODS[HASH_SIZE] = {1000000007, 998244353};

// Global powers array
vector<vector<int>> powers;

// Precompute base powers up to max length
void precompute_powers(int max_len) {
    powers.assign(RollingHash::HASH_SIZE, vector<int>(max_len + 1, 1));
    for (int i = 0; i < RollingHash::HASH_SIZE; ++i) {
        for (int j = 1; j <= max_len; ++j) {
            powers[i][j] = (powers[i][j - 1] * RollingHash::BASES[i]) % RollingHash::MODS[i];
        }
    }
}

// Build prefix hashes for a string
vector<RollingHash> build_prefix_hash(const string& s) {
    int n = s.size();
    vector<RollingHash> prefix(n + 1);  // prefix[0] = zero hash

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < RollingHash::HASH_SIZE; ++j) {
            prefix[i + 1].hashval[j] = (prefix[i].hashval[j] * RollingHash::BASES[j] + s[i]) % RollingHash::MODS[j];
        }
    }
    return prefix;
}

// Get hash of substring [l, r)
RollingHash get_substring_hash(const vector<RollingHash>& prefix, int l, int r) {
    RollingHash result;
    for (int i = 0; i < RollingHash::HASH_SIZE; ++i) {
        result.hashval[i] = (prefix[r].hashval[i] - (prefix[l].hashval[i] * powers[i][r - l]) % RollingHash::MODS[i] + RollingHash::MODS[i]) % RollingHash::MODS[i];
    }
    return result;
}

// Rabin-Karp algorithm
vector<int> rabin_karp(const string& text, const string& pattern) {
    int n = text.size(), m = pattern.size();
    vector<int> match_indices;

    if (m > n) return match_indices;

    precompute_powers(n);
    vector<RollingHash> prefix = build_prefix_hash(text);
    RollingHash pattern_hash(pattern);

    for (int i = 0; i <= n - m; ++i) {
        RollingHash sub_hash = get_substring_hash(prefix, i, i + m);
        if (sub_hash == pattern_hash) {
            match_indices.push_back(i);  // 0-based index
        }
    }

    return match_indices;
}

// Example usage
signed main() {
    cout<<"Testing Rabin-Karp...\n";
    string text = "ababcabcababc";
    string pattern = "abc";

    vector <int> matches = rabin_karp(text,pattern);
    
    assert(matches.size()==3);
    assert(matches[0]==2);
    assert(matches[1]==5);
    assert(matches[2]==10);

    cout<<"Testing passed!\n";
}

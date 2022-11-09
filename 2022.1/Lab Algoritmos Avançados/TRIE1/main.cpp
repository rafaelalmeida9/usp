#include <bits/stdc++.h>
using namespace std;

struct Trie {
	map<char, Trie> mp;
	int cnt = 0;
	int end = 0;

	void add(string& s, int i = 0) {
		cnt++;
		if (i < (int) s.size()) {
			mp[s[i]].add(s, i + 1);
		} else end++;
	}
	
	void remove(string& s, int i = 0) {
        cnt--;
		if (i < (int) s.size()) {
			mp[s[i]].remove(s, i + 1);
		} else end--;
    }

    int search(string& s, int i = 0) {
    if (i == (int) s.size()) return cnt;
    if (mp.count(s[i])) return mp[s[i]].search(s, i + 1);
    return 0;
    }
};

int main(){

    Trie root;

    int n,q; cin >> n >> q;

    for(int i = 0; i < n; i++){
        string s; cin >> s;
        root.add(s);
    }

    for(int i = 0; i < q; i++){
        string t; cin >> t;
        cout << root.search(t) << "\n";
    }

    return 0;
}
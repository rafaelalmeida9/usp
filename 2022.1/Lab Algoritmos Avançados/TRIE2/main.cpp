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

    int t; cin >> t;

    while(t--){
        int x; cin >> x;
        if(x == 1){
            string s; cin >> s;
            root.add(s);
        }
        else if(x == 2){
            string s; cin >> s;
            root.remove(s);
        }
        else if(x == 3){
            string s; cin >> s;
            cout << root.search(s) << "\n";
        }
    }

    return 0;
}
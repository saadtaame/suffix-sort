
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Suffix {
	int index;
	int rank[2];

	Suffix() {}
	Suffix(int index_, int rank_a, int rank_b) {
		index = index_;
		rank[0] = rank_a;
		rank[1] = rank_b;
	}
};

bool suffCmp(const Suffix &S, const Suffix &T) {
	if(S.rank[0] < T.rank[0])
		return true;
	else if(S.rank[0] == T.rank[0])
		return (S.rank[1] < T.rank[1]);
	return false;
}

vector<int> suffixSort( string &s ) {

	int n = (int)s.size();

	vector<int> rnk(n);
	for(int i = 0; i < n; i++)
		rnk[i] = (int)s[i];

	vector<Suffix> suff(n);
	for(int len = 1; ; len *= 2) {
		for(int i = 0; i < n; i++)
			suff[i] = Suffix(
				i,
				rnk[i],
				((i + len < n) ? rnk[i + len]  : -1)
			);

		sort(suff.begin(), suff.end(), suffCmp);
		
		rnk[suff[0].index] = 0;
		for(int i = 1; i < n; i++)
				rnk[suff[i].index] = rnk[suff[i - 1].index] +
					(suffCmp(suff[i - 1], suff[i]) ? 1 : 0);

		if(rnk[suff.back().index] == n - 1)
			break;
	}

	vector<int> sa(n);
	for(int i = 0; i < n; i++)
		sa[i] = suff[i].index;

	return sa;
}

int main( void ) {

	string s;
	cin >> s;

	vector<int> sa = suffixSort(s);

	int n = (int)s.size();
	for(int i = 0; i < n; i++)
		cout << sa[i] << " ";
	cout << endl;
	
	return 0;
}

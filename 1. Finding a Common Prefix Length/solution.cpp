#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Suffix {
    int index;
    pair<int, int> rank;
};

bool compareSuffix(const Suffix& a, const Suffix& b) {
    return a.rank < b.rank;
}

vector<int> computeLCPArray(const string& text, const vector<int>& suffixArray) {
    int n = text.length();
    vector<int> lcpArray(n, 0);
    
    vector<int> inverseSuffixArray(n);
    for (int i = 0; i < n; i++) {
        inverseSuffixArray[suffixArray[i]] = i;
    }
    
    int k = 0;
    
    for (int i = 0; i < n; i++) {
        if (inverseSuffixArray[i] == n - 1) {
            k = 0;
            continue;
        }
        
        int j = suffixArray[inverseSuffixArray[i] + 1];
        
        while (i + k < n && j + k < n && text[i + k] == text[j + k]) {
            k++;
        }
        
        lcpArray[inverseSuffixArray[i]] = k;
        
        if (k > 0) {
            k--;
        }
    }
    
    return lcpArray;
}

vector<int> buildSuffixArray(const string& text) {
    int n = text.length();
    vector<Suffix> suffixes(n);
    
    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank.first = text[i];
        suffixes[i].rank.second = (i + 1 < n) ? text[i + 1] : -1;
    }
    
    sort(suffixes.begin(), suffixes.end(), compareSuffix);
    
    vector<int> suffixArray(n);
    
    for (int k = 4; k < 2 * n; k *= 2) {
        int rank = 0;
        int prevRank = suffixes[0].rank.first;
        suffixes[0].rank.first = rank;
        suffixArray[suffixes[0].index] = 0;
        
        for (int i = 1; i < n; i++) {
            if (suffixes[i].rank.first == prevRank && suffixes[i].rank.second == suffixes[i - 1].rank.second) {
                prevRank = suffixes[i].rank.first;
                suffixes[i].rank.first = rank;
            } else {
                prevRank = suffixes[i].rank.first;
                suffixes[i].rank.first = ++rank;
            }
            suffixArray[suffixes[i].index] = i;
        }
        
        for (int i = 0; i < n; i++) {
            int nextIndex = suffixes[i].index + k / 2;
            suffixes[i].rank.second = (nextIndex < n) ? suffixes[suffixArray[nextIndex]].rank.first : -1;
        }
        
        sort(suffixes.begin(), suffixes.end(), compareSuffix);
    }
    
    vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = suffixes[i].index;
    }
    
    return result;
}

int main() {
	int n;
	cout << "Please enter the number of inputs: ";
	cin >> n;
	
	while (n --) {
	    string text;
	    cout << "Enter the string: ";
	    cin >> text;
	    
	    vector<int> suffixArray = buildSuffixArray(text);
	    vector<int> lcpArray = computeLCPArray(text, suffixArray);
	        
	    int n = suffixArray.size(), id;
	    
	    for (int i = 0; i < n; i ++) {
	        if (suffixArray[i] == 0) {
	        	id = i;
	        	break;
			}
	    }
	    long long rlt = n;
	    int rr = id ? lcpArray[id - 1] : 0;
		for (int i = id - 1; i >= 0 && lcpArray[i]; i --) {
	    	rlt += min(lcpArray[i], rr);
			rr = min(lcpArray[i], rr);
		}
	    int ll = lcpArray[id];
		for (int i = id ; i < n && lcpArray[i]; i ++) {
			rlt += min(lcpArray[i], ll);
			ll = min(lcpArray[i], ll);
		}
		cout << "Result: " << rlt << endl;
	}
    
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct KMP{
    string pattern;
    vector <int> lps; // longest prefix that's a suffix (except the whole string)

    KMP(){}

    KMP(string pat){
        pattern = pat;
        lps = calculate_lps(pattern);
    }
 
    vector <int> calculate_lps(string &pattern){
        lps.erase(lps.begin(),lps.end());
        lps.push_back(0);
        int j=0;
        for(int i=1;i<pattern.size();i++){
            while(pattern[i]!=pattern[j] and j>0){
                j = lps[j-1];
            }

            if(pattern[i]==pattern[j]){
                lps.push_back(j+1);
                j++;
            }
            else{
                lps.push_back(0);
            }
        }

        return lps;
    }

    vector <int> find_matches(string text, string pat){
        pattern = pat;
        lps = calculate_lps(pat);
        return find_matches(text);
    }

    vector <int> find_matches(string text){
        assert(lps.size()==pattern.size() and lps.size()>0);
        int n = text.size();
        int j=0;
        vector <int> ans;

        for(int i=0;i<n;i++){
            // cout<<"j="<<j<<",pattern[j]="<<pattern[j]<<"$$\n";
            while(j>0 and pattern[j]!=text[i]){
                j=lps[j-1];
            }

            if(text[i]==pattern[j]){
                j++;
                if(j==pattern.size()){
                    ans.push_back(i-j+1);
                }
            }
            // cout<<i<<":"<<j<<"\n";
        }

        return ans;
    }



};

signed main(){

    cout<<"Testing KMP...\n";

    KMP kmp;

    vector <int> matches = kmp.find_matches("ababcabcababc","abc");
    assert(matches.size()==3);
    assert(matches[0]==2);
    assert(matches[1]==5);
    assert(matches[2]==10);

    matches = kmp.find_matches("aaaaa","aa");
    assert(matches.size()==4);
    assert(matches[0]==0);
    assert(matches[1]==1);
    assert(matches[2]==2);
    assert(matches[3]==3);   
    
    cout<<"Testing passed!\n";
}
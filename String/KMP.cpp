#include <bits/stdc++.h>
using namespace std;
// O(M+N)
//return LPS array
vector<int> get_LPS(string s){
    int n = s.length();
    vector<int> LPS(n,0);
    for(int j = 1 ; j < n; j++){
        int i = LPS[j-1];
        while(i>0 && s[i]!=s[j])
            i = LPS[i-1];
        if(s[i]==s[j]){
            LPS[j]=i+1;
        }
        else{
           LPS[j]=0;   
        }
    }
    return LPS;
}
// if found returns vector of starting index of substrings in str
// else returns -1
vector<int> Sub_string_KMP(string str,string pattern){
    vector<int> LPS = get_LPS(pattern);
    vector<int> indexes;
    int i = 0, j=0;
    while(i<str.size() && j<pattern.size()){
        while( j > 0 && str[i]!=pattern[j]){
            j=LPS[j-1];
        }
        if(str[i]==pattern[j]){i++;j++;}
        else i++;
        
        if(j==pattern.size()){
            indexes.push_back(i-j);
            j=LPS[j-1];
        }
    }
    
    return indexes;
    
}
int main(){
    string s = "AABAACAADAABAABA";
    string p = "AABA";
    vector<int> V = Sub_string_KMP(s,p);
    if(V.size()==0){
        cout<<"Not substring";
    }
    else{
        for(int i = 0; i< V.size() ;i++){
            cout<<V[i]<<endl;
        }
    }
   
    
}

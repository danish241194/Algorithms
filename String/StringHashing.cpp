#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 6;
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;
const int base = 33;

int add(int a, int b, int mod){
	int res = (a + b) % mod;
	if(res < 0)
		res += mod;
	return res;
}

int mult(int a, int b, int mod){
	int res = (a * 1LL * b) % mod;
	if(res < 0)
		res += mod;
	return res;
}

int power(int a, int b, int mod){
	int res = 1;
	while(b){
		if((b % 2) == 1)
			res = mult(res, a, mod);
		a = mult(a, a, mod);
		b /= 2;
	}
	return res;
}

int pw1[N],pw2[N];
int inv1[N],inv2[N];
int H1[N],H2[N];

void precalc() {
	pw1[0] = 1;
	for(int i = 1; i < N; i++)
		pw1[i] = mult(pw1[i - 1], base, mod1);
    
    pw2[0] = 1;
	for(int i = 1; i < N; i++)
		pw2[i] = mult(pw2[i - 1], base, mod2);
	
    
	int pw_inv_1 = power(base , mod1 - 2 , mod1);
	inv1[0] = 1;
	for(int i = 1; i < N; i++)
		inv1[i] = mult(inv1[i - 1], pw_inv_1, mod1);
    
    
	int pw_inv_2 = power(base , mod2 - 2 , mod2);
	inv2[0] = 1;
	for(int i = 1; i < N; i++)
		inv2[i] = mult(inv2[i - 1], pw_inv_2, mod2);
}

void build_helper(string &s){
	int n = s.length();
	for(int i = 0; i < n ; ++i){
		H1[i] = add((i == 0) ? 0 : H1[i - 1], mult(pw1[i], s[i] - 'a' + 1, mod1), mod1);
	}
    
    for(int i = 0; i < n ; ++i){
		H2[i] = add((i == 0) ? 0 : H2[i - 1], mult(pw2[i], s[i] - 'a' + 1, mod2), mod2);
	}
}

pair<int,int> getHash(int x , int y){
	int res1 = add(H1[y], (x == 0) ? 0 : -H1[x - 1], mod1);
	res1 = mult(res1 , (x == 0) ? 1 : inv1[x], mod1);
    
    int res2 = add(H2[y], (x == 0) ? 0 : -H2[x - 1], mod2);
	res2 = mult(res2 , (x == 0) ? 1 : inv2[x], mod2);
    
	return make_pair(res1,res2);
}

string toString(pair<int,int> p){
    return to_string(p.first)+""+to_string(p.second);
}

bool are_same(pair<int,int> p1,pair<int,int> p2){
    if(p1.first==p2.first && p1.second==p2.second)return true;
    return false;
}

void build(string s){
    precalc();
    build_helper(s);
}


int main() {
	
	string s = "ABCDEFGABCDEFGH";
	build(s);
	cout<< toString(getHash(2, 5)) << " == " << toString(getHash(9, 12)) << endl;
    cout<< toString(getHash(2, 5)) << " == " << toString(getHash(9, 13)) << endl;
    cout<< are_same(getHash(2, 5),getHash(9, 12)) << endl;
    
}

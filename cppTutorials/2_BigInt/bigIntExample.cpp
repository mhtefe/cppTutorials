/**
 * mht
 *
 * I was looking for some original cpp puzzles and there was an interesting question which was asking to calculate factorial of long numbers.
 * 
 * I couldn't hit the target at first shot to be honest. After google it a little, found an interesting code about big integers.
 *
 * https://codeforces.com/blog/entry/16380
 *
 * idea of the code was simple, define the longest 64 bit integer and store it in vector with carry parts or sth.
 *
 * most of the math operators and calculations are defined, but I just cropped initialization and multiplication parts.
 *
 * result is accurate, and output display is true due to good "Print" function.
 */
#include <iostream>
#include <vector>

using namespace std;

typedef int64_t ll;
typedef long long ll;

#define EL printf("\n")
#define pb push_back
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define FORD(i,r,l) for (int i=r;i>=l;i--)

const int base = 1e9;
typedef vector<int> BigInt;

void Set(BigInt &a) {
	while (a.size() > 1 && a.back() == 0) a.pop_back();
}

BigInt Integer(string s) {
	BigInt ans;
	if (s[0] == '-') return ans;
	if (s.size() == 0) { ans.pb(0); return ans; }
	while (s.size() % 9 != 0) s = '0' + s;
	for (int i = 0; i < s.size(); i += 9) {
		int v = 0;
		for (int j = i; j < i + 9; j++) v = v * 10 + (s[j] - '0');
		ans.insert(ans.begin(), v);
	}
	Set(ans);
	return ans;
}

BigInt Integer(char c[]) {
	string s = "";
	FOR(i, 0, strlen(c) - 1) s = s + c[i];
	return Integer(s);
}

BigInt Integer(ll x) {
	string s = "";
	while (x > 0) s = char(x % 10 + '0') + s, x /= 10;
	return Integer(s);
}

BigInt Integer(int x) {
	return Integer((ll)x);
}

BigInt operator * (BigInt a, BigInt b) {
	Set(a);
	Set(b);
	BigInt ans;
	ans.assign(a.size() + b.size(), 0);
	FOR(i, 0, a.size() - 1) {
		ll carry = 0ll;
		for (int j = 0; j < b.size() || carry > 0; j++) {
			ll s = ans[i + j] + carry + (ll)a[i] * (j < b.size() ? (ll)b[j] : 0ll);
			ans[i + j] = s % base;
			carry = s / base;
		}
	}
	Set(ans);
	return ans;
}

BigInt operator * (BigInt a, int b) {
	return a * Integer(b);
}


void Print(BigInt a) {
	Set(a);
	printf("%d", (a.size() == 0) ? 0 : a.back());
	FORD(i, a.size() - 2, 0) printf("%09d", a[i]); EL;
}

int main()
{
	BigInt fact = Integer(1);
	int n = 25;
	for (int i = n; i > 1; i--)
	{
		fact = fact * Integer(i);
	}

	Print(fact);
	return 0;
}
#include<stdio.h>
#include<iostream>

using std::string;

string addBinary(const string& a , const string& b) {
	string c = "";
	char carry = '0';
	int i,j;
	for(i = a.length() - 1, j = b.length() - 1; i>=0 && j>=0; --i,--j) {
		char sumVal = '0';
		if(a[i] == '0' && b[j] == '0') {
			sumVal = carry;
			carry = '0';
		}
		else if(a[i] == '0' || b[j] == '0') {
			if(carry == '0')
				sumVal = '1';
		}
		else {
			sumVal = carry;
			carry = '1';
		}
		c.insert(c.begin(), sumVal);
	}
	while(i >=0 ) {
		if(carry == '0')
			c.insert(c.begin(), a[i]);
		else
		{
			if(a[i] == '0'){
				c.insert(c.begin(), carry);
				carry = '0';
			} else {
				c.insert(c.begin(), '0');
			}
		}

		--i;
	}
	while(j >=0 ) {
		if(carry == '0')
			c.insert(c.begin(), b[j]);
		else
		{
			if(b[j] == '0'){
				c.insert(c.begin(), carry);
				carry = '0';
			} else {
				c.insert(c.begin(), '0');
			}
		}

		--j;
	}
	if(carry == '1') {
		c.insert(c.begin(), '1');
	}
	
	return c;
}

/*int main(int argc, char ** argv) {
	string a = "111";
	string b = "101";
	printf("Result: %s\n", addBinary(a, b).c_str());
	return 0;
}*/
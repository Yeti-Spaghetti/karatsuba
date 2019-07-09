#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

string reverseString(string s){
    int n = s.length();
    for (int i = 0; i < n / 2; i++){
        swap(s[i], s[n - i - 1]);
    }
    return s;
}

string schoolAdd(string a, string b, string bse){
    int base = stoi(bse);

    // fill required string with 0's
    if (a.length() < b.length()){
        int repeat = b.length()-a.length();
        for (int i = 0; i < repeat; i++){
            a.insert(a.begin(), '0');
        }
    } else if (a.length() > b.length()){
        int repeat = a.length()-b.length();
        for (int i = 0; i < repeat; i++){
            b.insert(b.begin(), '0');
        }
    }

    // addition of each number
    string sum;
    int carry = 0;
    for (int i = a.length()-1; i >= 0; i--){
        int numA = a[i] - '0';
        int numB = b[i] - '0';
        int num = numA + numB + carry;
        if (num >= base){
            carry = 1;
            num %= base;
        } else {
            carry = 0;
        }
        sum += to_string(num);
    }
    if (carry == 1){
        sum += '1';
    }

    // reverse string
    int n = sum.length();
    for (int i = 0; i < n / 2; i++){
        swap(sum[i], sum[n - i - 1]);
    }

    return sum;
}

string schoolSub(string a, string b, string bse){
    int base = stoi(bse);
    
    // pad zeros
    if (a.length() < b.length()){
        int repeat = b.length()-a.length();
        for (int i = 0; i < repeat; i++){
            a.insert(a.begin(), '0');
        }
    } else if (a.length() > b.length()){
        int repeat = a.length()-b.length();
        for (int i = 0; i < repeat; i++){
            b.insert(b.begin(), '0');
        }
    }

    // subtraction of each number
    string sum;
    int carry = 0;
    for (int i = a.length()-1; i >= 0; i--){
        int numA = a[i] - '0';
        int numB = b[i] - '0';
        int num = numA - numB + carry;
        if (num < 0){
            carry = -1;
            num += base;
        } else {
            carry = 0;
        }
        sum += to_string(num);
    }

    // reverse string
    sum = reverseString(sum);
    return sum;
}

string mult(string a, string b, string base){
    // pad extra zeros
    if (a.length() < b.length()){
        int diff = b.length()- a.length();
        for (int i = 0; i < diff; i ++){
            a.insert(0, "0");
        }
    } else if (a.length() > b.length()){
        int diff = a.length() - b.length();
        for (int i = 0; i < diff; i++){
            b.insert(0, "0");
        }
    }

    // base case
    if (a.length() == 1 || b.length() == 1){
        int aInt = stoi(a);
        int bInt = stoi(b);
        int int_base = stoi(base);
       
        int num = aInt * bInt;
        int carry = 0;
        if (num >= int_base){
            while (num >= int_base){
                num -= int_base;
                carry++;
            }
        }
        string sum = to_string(carry) + to_string(num);
        return sum;
    }

    // set n and find k 
    int n = a.length();
    int k = a.length() / 2;
    
    // split strings
    string a1 = a.substr(0, n-k);
    string a0 = a.substr(n-k, a.size());
    
    string b1 = b.substr(0, n-k);
    string b0 = b.substr(n-k, a.size());

    // school multiplication
    if (a.length() <= 3){
        string p2 = mult(a1, b1, base);
        string p0 = mult(a0, b0, base);
        string p1 = schoolAdd(mult(a1, b0, base), mult(a0, b1, base), base);
        // pad 0's
        for (int i = 0; i < 2*k; i++){p2 += '0';}
        for (int i = 0; i < k; i++){p1 += '0';}

        return schoolAdd(p2, schoolAdd(p1, p0, base), base);
    // karatsuba multiplication
    } else {
        string p2 = mult(a1, b1, base);
        string p0 = mult(a0, b0, base);
        string p1 = mult(schoolAdd(a1, a0, base), schoolAdd(b1, b0, base), base);
        p1 = schoolSub(p1, schoolAdd(p2, p0, base), base);
        // pad 0's
        for (int i = 0; i < 2*k; i++){p2 += '0';}
        for (int i = 0; i < k; i++){p1 += '0';}

        return schoolAdd(p2, schoolAdd(p1, p0, base), base);
    }
}
int main(){
    string input;
    getline(cin, input);
    string inputNums[3];

    // parse input
    int counter = 0;
	for (int i=0; i<input.length(); i++){
		if (input[i] == ' '){
			counter++;
			i++;
		}
		inputNums[counter] += input[i];
	}

    string addString = schoolAdd(inputNums[0], inputNums[1], inputNums[2]);
    string multString = mult(inputNums[0], inputNums[1], inputNums[2]);

    // remove leading zeros
    while (multString[0] == '0'){
        multString.erase(multString.begin());
    }

    cout << addString << " " << multString << endl;
    return 0;
}
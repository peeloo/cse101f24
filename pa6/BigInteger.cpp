/*
Phil Liu
phzliu
2024 Fall CSE101 PA6
BigInteger.h
Implements BigInteger ADT and its operations
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"
#include "BigInteger.h"

const int power = 9;
const long base = 1000000000;

// class constructors/destructors

BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

BigInteger::BigInteger(long x) {
    if (x == 0) {
        signum = 0;
        digits.insertAfter(0);
    }
    else {
        signum = (x > 0) ? 1 : -1;
        x = (x > 0) ? x : -x;
        while (x > 0) {
            digits.insertAfter(x % base);
            x /= base;
        }

    }
}

BigInteger::BigInteger(std::string s) {
    if (s.length() == 0) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    signum = (s[0] == '-') ? -1 : 1;
    if (s[0] == '+' || s[0] == '-') {
        s = s.substr(1);
    }

    for (uint i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }
    // go to back of str and then section num by power

    std::string num = "";
    long slen = s.length() - 1;

    while (slen >= 0) {
        // accumulate numbers until a sections is filled
        if (num.length() ==  power) {  
            digits.insertAfter(std::stol(num));
            num = "";
        }
        num = s[slen] + num;
        slen--;
    }
    
    // for remaining nums
    if (num != "") {
        digits.insertAfter(std::stol(num));
    }

    // get rid of extra 0s
    digits.moveFront();
	while (digits.peekNext() == 0 && digits.length() > 1){
		digits.eraseAfter();
	}
}

BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = N.digits;
}

// access functions

int BigInteger::sign() const {
    return this->signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (this->signum > N.signum) {
        return 1;
    }
    else if (this->signum < N.signum) {
        return -1;
    }
    else if (this->signum == 0 && N.signum == 0) {
        return 0;
    }

    if (this->digits.length() == N.digits.length()) {
        List copyThis = this->digits;
        List copyN = N.digits;
        copyThis.moveBack();
        copyN.moveBack();

        while (copyThis.position() > 0) {
            int x = copyThis.movePrev();
            int y = copyN.movePrev();
            if (x < y) {
                return -1;
            }
            if (x > y) {
                return 1;
            }
        }
        return 0;
    }
    else {
        if (this->digits.length() > N.digits.length()) {
            return 1;
        }
        else {
            return 0;
        }
    }

}

// manipulation functions

void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

void BigInteger::negate() {
    signum *= -1;
}

// helper funcs

void scalarMultList(List& L, ListElement m) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setBefore(L.moveNext() * m);
    }
}

void negateList(List& L) {
    scalarMultList(L, -1);
}

void sumList(List& S, List A, List B, int sgn) {
    if (sgn == -1) {
        negateList(B);
    }

    S.clear();
    A.moveBack();
    B.moveBack();
    while (A.position() > 0 && B.position() > 0) {
        S.insertAfter(A.movePrev() + B.movePrev());
    }
    // for remaining nums in A or B
    while (A.position() > 0) {
        S.insertAfter(A.movePrev());
    }
    while (B.position() > 0) {
        S.insertAfter(B.movePrev());
    }

    // get rid of extra 0s
    S.moveFront();
	while (S.peekNext() == 0 && S.length() > 1){
		S.eraseAfter();
	}
}

int normalizeList(List& L){
	int sign = 1;
	if (L.peekNext() == 0){
		return 0;
	}
	if (L.peekNext() < 0){
		negateList(L);
		sign = -1;
	}

	long val = 0;
	long carry = 0;
	L.moveBack();
	while (L.position() > 0){
		val = L.peekPrev();
		if (val < 0){
			val += base + carry;
			L.setBefore(val);
			carry = -1;
		}
        else {
			val += carry;
			carry = 0;
			if (val >= base){
				carry = val / base;
				val = val % base;
			}
			L.setBefore(val);
		}
		L.movePrev();
	}
	if (carry != 0){
		L.moveFront();
		L.insertAfter(carry);
	}

	return sign;
}

void shiftList(List& L, int p){
	L.moveBack();
	for (int i = 0; i < p; ++i)
	{
		L.insertAfter(0);
	}
}

// arithmetic operations

BigInteger BigInteger::add(const BigInteger& N) const {
	BigInteger result;
	List A = this->digits;
	List B = N.digits;
	List sum;
	if(this->signum == -1) {
		negateList(A);
	}
	if(N.signum == -1){
		negateList(B);
	}

	sumList(sum, A, B, 1);
	result.signum = normalizeList(sum);
	result.digits = sum;
	return result;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger temp = N;
    negateList(temp.digits);
    return this->add(temp);
}

BigInteger BigInteger::mult(const BigInteger& N) const {
	BigInteger result;
	if (this->signum == 0 || N.signum == 0){
		return result;
	}
	List product;
	List A;
	List B = N.digits;
	int shift = 0;
	product.insertAfter(0);
	B.moveBack();
	while(B.position() > 0){
		A = this->digits;
		scalarMultList(A, B.peekPrev());
		shiftList(A, shift);
		List temp = product;
		sumList(product, temp, A, 1);
		normalizeList(product);
		B.movePrev();
		shift++;
	}
	result.digits = product;
	result.signum = this->signum * N.signum;
	return result;
}

// other functions

std::string BigInteger::to_string() {
	std::string s = "";
	if (this->signum == 0){
		return "0";
	} else if (signum == -1){
		s += "-";
	}

	digits.moveFront();

    // skipping leading zeros
	while (digits.peekNext() == 0 && digits.length() > 1) {
		digits.moveNext();
	}

	while (digits.position() < digits.length()){
		std::string temp = std::to_string(digits.peekNext());
		std::string zeros = "";
		while ((zeros.length() + temp.length()) < power && digits.position() != 0){
			zeros += "0";
		}
		s += (zeros + temp);
		digits.moveNext();
	}
	return s;
}

// overridden operators

std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    return stream << N.BigInteger::to_string();
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    if (A.compare(B) == 0) {
        return true;
    }
    return false;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    if (A.compare(B) == -1) {
        return true;
    }
    return false;
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    if (A.compare(B) != 1) {
        return true;
    }
    return false;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    if (A.compare(B) == 1) {
        return true;
    }
    return false;
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    if (A.compare(B) != -1) {
        return true;
    }
    return false;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    return A.add(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    return A = A.add(B);
}

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    return A.sub(B);
}

BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    return A = A.sub(B);
}

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    return A.mult(B);
}

BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    return A = A.mult(B);
}
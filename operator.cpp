#include "Bigint.h"

Bigint operator+(Bigint& a, Bigint& b) {
	Bigint c;
	int len = max(a.len, b.len);
	for (int i = 1; i <= len; i++)
		c[i] += a[i] + b[i];
	c.flatten(len + 1);
	return c;
}

Bigint operator*(Bigint& a, int b) {
	Bigint c;
	for (int i = 1; i <= a.len; i++)
		c[i] = a[i] * b;
	c.flatten(a.len + 11);
	return c;
}

Bigint operator*(Bigint& a, Bigint& b) {
	Bigint c(0), d(0);
	int lenb = b.len;
	for (int i = 1; i <= lenb; i++) {
		d = a * b[i];
		d.AddTens(i - 1);
		c = c + d;
	}
	return c;
}

Bigint operator/(Bigint& a, int b) {
	Bigint c;
	int remain = 0;
	for (int i = a.len; i >= 1; i--) {
		int num = remain + a[i];
		c[i] = num / b;
		remain = 10 * (num % b);
	}
	c.flatten(a.len);
	return c;
}


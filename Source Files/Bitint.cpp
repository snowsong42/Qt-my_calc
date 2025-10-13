#include "Bigint.h"

//构造
Bigint::Bigint(int x) {
	arr = new int[MAXN];
	memset(arr, 0, MAXN * sizeof(int));	//全部置零
	for (len = 1; x; len++)
		arr[len] = x % 10, x /= 10;
	len--;
}
// 添加拷贝构造函数
Bigint::Bigint(const Bigint& other) {
	arr = new int[MAXN];
	memcpy(arr, other.arr, MAXN * sizeof(int));
	len = other.len;
}

// 添加赋值运算符
Bigint& Bigint::operator=(const Bigint& other) {
	if (this != &other) {
		memcpy(arr, other.arr, MAXN * sizeof(int));
		len = other.len;
	}
	return *this;
}

//展平
void Bigint::flatten(int L) {
	len = L;
	for (int i = 1; i <= len; i++) {
		arr[i + 1] += arr[i] / 10;
		arr[i] %= 10;
	}
	while (!arr[len]) len--;
}

//显示
void Bigint::print() {
	for (int i = max(len, 1); i >= 1; i--)
		printf("%d", arr[i]);
}

//乘十
void Bigint::AddTens(int n) {
	for (int i = len; i >= 0; i--) {
		arr[i + n] = arr[i];
	}
	for (int i = 0; i < n; i++) {
		arr[i] = 0;
	}
	len += n;
}

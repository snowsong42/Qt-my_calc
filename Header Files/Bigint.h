#pragma once
#define MAXN 10000
#include <string>
#include <stdio.h>
#include <iostream>
#include <cstring>  // 添加memset所需头文件

using namespace std;

/*字符串默认大端对齐，高位优先，和日常书写习惯一致。*/
/*但我们的int串要小端对齐，低位优先，才方便增加进位。tips: 不过记得输出要反过来哦*/
/* A = 1 2 3 */
/* a = 3 2 1 0 0 0 ... 0 */
class Bigint {
public:
	int len;
	int* arr;
	Bigint(int x = 0);
	Bigint(const Bigint& other);
	~Bigint() { delete[]arr; }
	Bigint& operator=(const Bigint& other);
	int& operator[](int i) { return arr[i]; }

	void flatten(int L);	//展平
	void AddTens(int n);	//乘十
	void print();
};

Bigint operator+(Bigint& a, Bigint& b);
Bigint operator*(Bigint& a, int b);
Bigint operator/(Bigint& a, int b);
Bigint operator*(Bigint& a, Bigint& b);
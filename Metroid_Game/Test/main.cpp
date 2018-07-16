#include<stdio.h>
#include <iostream>
using namespace std;

void change(int &num) {
	num++;
}

int main() {
	int x = 100;
	printf("Truoc khi goi phuong thuc x = %d \n", x);
	change(x); // truyen tham chieu vao phuong thuc
	printf("Sau khi goi phuong thuc x = %d \n", x);
	system("pause");
	return 0;
}

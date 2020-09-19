#include <stdio.h>

int main(){
	int x = -2147483648;
	printf("%d\n", x >> 31);
	unsigned int y = -2147483648;
	printf("%d\n", y >> 31);
	return 0;
}

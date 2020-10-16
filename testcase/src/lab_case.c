#include "trap.h"

int main(){
	int i = 0;
	nemu_assert(i == 0);
	HIT_GOOD_TRAP;
	return 0;
}

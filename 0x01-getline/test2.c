#include <stdio.h>

int st(const int i)
{
	static int a = i;

	a++;
	printf("static int a is %d\n", a);
	return (a);
}


int main(void)
{
	int i = 0;
	
	printf("on main i is %d\n", st(i));
	i++;
	printf("on main i is %d\n", st(i));
	return (1);
}

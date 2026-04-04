#include<iostream>

using namespace std;

__int128 a;

void Read(__int128 &x)
{
	x = 0;
	int f = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-') f = -1; ch = getchar();	
	}	
	while (isdigit(ch))
	{
		x = x * 10 + ch - 48; ch = getchar();
	}
	x *= f;
} 

void Print(__int128 x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9) Print(x / 10);
	putchar(x % 10 + '0');
}

int main()
{
	Read(a);
	Print(a);
	putchar('\n');
	return 0;
}
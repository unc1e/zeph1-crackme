#include <stdio.h>
#include <windows.h>

char name[100];

/*
unsigned int f1(char* key)
{
	unsigned int r = 0;

	for (int i = 0; i < 4; i++)
	{
		if (key[i] > 57)
			r += key[i] - 55;
		else
			r += key[i] - 48;

		if (i != 3)
			r *= 16;
	}

	return LOWORD(r);
}
*/

void main()
{
	for (;;)
	{
		printf_s("Enter your name(2 chars min and 100 chars max): ");
		fgets(name, sizeof(name), stdin);

		int nl = strlen(name) - 1;
		if (name[nl] == '\n')
			name[nl] = '\x00';
		else nl++;

		if (nl < 2)
			continue;

		DWORD s = 0;
		for (int i = 0; i <= nl; i++)
			s = i * (s + name[i]);

		s = LOBYTE(s) % 15;

		/*/////////////////////////////////////////////////
		//original algorithm (you can just brute serial or make static table xD)

		DWORD h1 = f1("ABCD"); //if chars beetwen A...Z then
		DWORD h2 = f1("EFFF"); //h = StrToHex(str);
		DWORD h3 = f1("CCAD");
		DWORD h4 = f1("BECA");

		DWORD t = ((h1 << 16) + h4) ^ ((h3 << 16) + h2);

		DWORD m = 0;
		do
		{
		t >>= 1;

		if (t & 1)
		m++;
		} while (t);
		//if m == s then profit!
		*///////////////////////////////////////////////////

		// reverse algorithm
		DWORD j = 1;
		DWORD p = 0;

		do
		{
			j <<= 1;
			j++;
			p++;

		} while (p != s);

		DWORD k1 = s * 1972; //random value
		DWORD k2 = s * 4369; //random value
		DWORD k3 = k1; //k1 ^ k3 = 0
		DWORD k4 = k2 ^ j; ////k2 ^ k4 = k2 ^ (k2 ^ j) = (k2 ^ k2) ^ j = 0 ^ j = j; 

		printf_s("Your serial: %X-%X-%X-%X\n", k1, k2, k3, k4);
	}
}
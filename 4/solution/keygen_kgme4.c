#include <stdio.h>
#include <windows.h>

char name[100];
char serial[100];

DWORD hash[100];
DWORD static1[] = {0x69657361, 0x0D83F3231, 0x93EA93D1, 0x7B043, 0x0F31337F, 0x384C4D94};
DWORD static2[] = {0x573, 0x0D32, 0x9EA, 0x7B0, 0x3FC, 0x8D9, 0x0D32, 0x9EA,
                   0x7B0, 0x3FC, 0x8D9, 0x93E, 0x0D32, 0x9EA, 0x8DE, 0x321,
                   0x8AC, 0x8B3, 0x0A73, 0x0C39, 0x9AA, 0x0FBC, 0x9B5, 0x0D32,
                   0x0CEE, 0x7B0, 0x7B0, 0x3FC, 0x2D9, 0x731, 0x9EA, 0x7B0};
char static3[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

DWORD f1(char *str, int nl)
{
	DWORD s = 0;

	for (int i = 0; i < nl; i++)
		s += str[i];

	return s ^ 0x69657361;
}

DWORD f2(char *str)
{
	DWORD s = 0;

	for (int i = 0; i < 32; i++)
		s += str[i];

	return (s * 0x1B) ^ 0x7A657068;
}

DWORD f3(char *str)
{
	DWORD s = 0;
	char t = 0;

	for (int i = 0; i < 8; i++)
	{
		t = str[i];
		if (t >= 0x30)                              //convert chars
			(t > 0x39) ? (t -= 0x37) : (t -= 0x30); //to hex ('A' = 0x0A; '1' = 0x1 ...)

		s += t;      //str
		if (i != 7)  //to
			s *= 16; //int ("ABC91DFE" = 0xABC91DFE)
	}

	return s;
}

void main()
{
	for (;;)
	{
		printf_s("Enter your name (1 chars min and 100 chars max): ");
		fgets(name, sizeof(name), stdin);

		int nl = strlen(name) - 1;
		if (name[nl] == '\n')
			name[nl] = '\x00';
		else nl++;

		if (nl < 1)
			continue;

		for (int i = 0; i <= nl; i++)
			hash[i] = f1(name, nl) ^ static1[i % 6] ^ (nl * 0x29821) ^ 0x70005000;

		for (int i = 0; i < 32; i++)
			serial[i] = static3[(hash[i % (nl + 1)] ^ static2[i]) % 0x3E];

		/*
		//Original algorithm
		DWORD z = f3( - any 8 chars - ) ^ f2(serial);
		int k = 0;
		do
		{
			z >>= 1;
			if (z & 1)
				k++;
		} while (z);
		//if k == 0x1D mission complete
		printf("%X", k);

		//Reverse algorithm
		DWORD b = 1;
		int a = 0;
		while (a != 0x1D)
		{
			b = b * 2 + 1;
			a++;
		}
		printf("%X", b); //b always == 0x3FFFFFFF == z
		*/
		
		DWORD s = (0x3FFFFFFF ^ f2(serial)); //s = f3( - any 8 chars - ) result

		serial[32] = '-';
		sprintf_s(&serial[33], 8 + 1, "%X", s); //reverse result of f3( - any 8 chars - )

		printf("Your serial: %s\n", serial);
	}
}
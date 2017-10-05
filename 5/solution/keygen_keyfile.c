#include <stdio.h>
#include <windows.h>

char key[48];

DWORD k; //eax
DWORD m; //edx

DWORD z;
DWORD u;

void f1(DWORD a, DWORD b, DWORD c, DWORD d)
{
	DWORD64 v = (DWORD64)a * c;
	k = (DWORD)v;
	m = (DWORD)(v >> 32) + (b | d ? b * c + a * d : 0);
}

void f2(DWORD a, DWORD b)
{
	BOOL f = 0;

	if ((signed int)b < 0)
	{
		f = 1;
		b = 0 - b - (a != 0);
		a = 0 - a;
	}

	DWORD a1 = a;
	DWORD b1 = b;

	for (int i = 0; i < 22; i++)
	{
		a = (a >> 1) | ((b & 1) << 31);
		b = b >> 1;
	}

	DWORD n = (DWORD)((((DWORD64)b << 32) | a) / 0x87A44FDD);
	DWORD s = n * 0x21E913;
	DWORD64 p = (DWORD64)n * 0x0F77124E3;
	DWORD q = (DWORD)(p >> 32);
	z = (DWORD)p;
	u = q + s;

	if (u != ((DWORD64)q + s) || u > b1 || (u >= b1 && b1 > z))
	{
		u -= (0x21E913 + (((DWORD64)(z - 0x0F77124E3) != ((DWORD64)z - 0x0F77124E3))));
		z -= 0x0F77124E3;
	}

	u -= (b1 + ((DWORD64)(z - a1) != ((DWORD64)z - a1)));
	z -= a1;

	if (!f)
	{
		u = 0 - u - (z != 0);
		z = 0 - z;
	}
}

void main()
{
	for (;;)
	{
		printf_s("Enter your name (1 chars min and 39 chars max): ");
		fgets(key, 40, stdin);

		int ln = strlen(key) - 1;
		if (key[ln] == '\n')
			key[ln] = '\x00';
		else ln++;

		if (ln < 1)
			continue;

		memset(&key[ln], 0x34, 40 - ln);

		DWORD r = 0x5E160B3A;
		DWORD t = 0x1B8BD;

		for (int i = 0; i < 40; i++)
		{
			key[i] %= 0x34;
			f1((DWORD)key[i], 0, 0x34F63A74, 0x15DCFB3);
			t += m + (((DWORD64)(r + k) != ((DWORD64)r + k)) ? 1 : 0);
			r += k;
		}

		f2(r, t);
		f1(z, u, z, u);

		memcpy(&key[40], &k, 4);
		memcpy(&key[44], &m, 4);

		HANDLE hFile = CreateFileA("key.dat", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
		WriteFile(hFile, key, 48, 0, 0);
		CloseHandle(hFile);

		printf_s("Key file (key.dat) successfully generated! Move it to file.exe folder and run crackme.\n");
	}
}
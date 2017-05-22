#include <stdio.h>
#include <Windows.h>

char name[100];
char serial[18 + 1];

void main()
{
	for (;;)
	{
		printf_s("Enter your name(3 chars min and 100 chars max): ");
		fgets(name, sizeof(name), stdin);

		int nl = strlen(name) - 1;
		if (name[nl] == '\n')
			name[nl] = '\x00';
		else nl++;

		unsigned int s = 0;

		for (int i = 0; i < nl; i++)
		{
			s += name[i];
			if (name[i] < 74)
				s *= 2 * name[i];
			else s *= name[i];
		}

		s %= 1828;
		for (int i = 0; i < nl; i++)
		{
			if (name[i] < 64)
				s = 4 * name[i] * (s + name[i]);
			else s = name[i] * (s + name[i]);
		}

		s %= 8741;
		for (int i = 0; i < nl; i++)
		{
			if (name[i] < 84)
				s = 6 * name[i] * (s + name[i]);
			else s = name[i] * (s + name[i]);
		}

		for (int i = 0; i < nl; i++)
		{
			if (name[i] < 74)
				s = 5 * name[i] * (s + name[i]);
			else s = name[i] * (s + name[i]);
		}

		s %= 11828;
		for (int i = 0; i < nl; i++)
		{
			if (name[i] < 64)
				s = 7 * name[i] * (s + name[i]);
			else s = name[i] * (s + name[i]);
		}

		wsprintfA(serial, "%X%lu", s, s);
		printf_s("Your serial: %s\n", serial);
	}
}
#include <stdio.h>

char serial[16 + 1];
char chars[62];

void main()
{
	for (int i = 0; i < 26; i++)
		chars[i] = i + 65; //A...Z

	for (int i = 26; i < 52; i++)
		chars[i] = i + 71; //a...z

	for (int i = 52; i < 62; i++)
		chars[i] = i - 4; //0...9

	unsigned int k;
	int t = 0;

	for (;;)
	{
		printf_s("Enter a random integer: ");
		scanf_s("%d", &k);

		serial[0] = chars[k % 26]; //only A...Z because ->
		serial[1] = chars[(k * 117) % 62];
		serial[2] = chars[(k * 824) % 62];
		serial[3] = chars[(k * 95) % 62];
		serial[4] = chars[(k * 3) % 62];
		serial[5] = chars[(k * 17) % 62];
		serial[6] = chars[(k * 44) % 62];
		serial[7] = chars[(k * 63) % 62];

		if (serial[0] <= 90 && serial[0] >= 65) // -> it must be done
		{
			t = serial[0] + 4;
			if (t <= 91)
			{
				if (t < 64)
					t += 29;
			}
			else t -= 6;
		}

		serial[8] = t;

		if (serial[1] <= 122 && serial[1] >= 97)
		{
			t = serial[1] + 7;
			if (t <= 123)
			{
				if (t < 96)
					t += 16;
			}
			else t -= 11;
		}

		serial[9] = t;

		if (serial[2] <= 90 && serial[2] >= 65)
		{
			t = serial[2] + 6;
			if (t <= 91)
			{
				if (t < 64)
					t += 23;
			}
			else t -= 10;
		}

		serial[10] = t;

		if (serial[3] <= 122 && serial[3] >= 97)
		{
			t = serial[3] + 5;
			if (t <= 123)
			{
				if (t < 96)
					t += 17;
			}
			else t -= 9;
		}

		serial[11] = t;

		if (serial[4] <= 90 && serial[4] >= 65)
		{
			t = serial[4] + 4;
			if (t <= 91)
			{
				if (t < 64)
					t += 14;
			}
			else t -= 6;
		}

		serial[12] = t;

		if (serial[5] <= 122 && serial[5] >= 97)
		{
			t = serial[5] + 4;
			if (t <= 123)
			{
				if (t < 96)
					t += 11;
			}
			else t -= 5;
		}

		serial[13] = t;

		if (serial[6] <= 90 && serial[6] >= 65)
		{
			t = serial[6] + 5;
			if (t <= 91)
			{
				if (t < 64)
					t += 10;
			}
			else t -= 8;
		}

		serial[14] = t;

		if (serial[7] <= 122 && serial[7] >= 97)
		{
			t = serial[7] + 2;
			if (t <= 123)
			{
				if (t < 96)
					t += 15;
			}
			else t -= 8;
		}

		serial[15] = t;

		printf_s("Your serial: %s\n", serial);
	}
}
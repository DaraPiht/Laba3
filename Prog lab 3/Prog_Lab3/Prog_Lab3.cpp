#include <iostream>
#include "libbmp.h"

short Bit = 7;  // Переменная, хранящая номер текущего читаемого бита
short Byte = 0; // Переменная, хранящая номер текущего читаемого байта
char text[4000]; // Массив, хронящий полученный текст

bool end = false;

void addBit(char bit)  // Добавляем новый бит в строку
{
	if (end) return;
	// Установка бита в нужную позицию при помощи сдвига

	bit = bit << Bit;
	text[Byte] = text[Byte] | bit;
	Bit--;
	// Переход к следующему байту
	if (Bit < 0)
	{
		if (text[Byte] == '\0')
		{
			end = true;
		}

		Bit = 7;
		Byte++;
	}
}

int main()
{

	BmpImg pic;
	pic.read("pic7.bmp");
	
	for (int x = 0; x <= pic.get_width() - 1; x++) // 11r 11b 11g 01r 01b 01g 10r 10b
	{
		for (int y = 0; y <= pic.get_height() - 1; y++)
		{

			char bit1 = pic.red_at(x, y) & 0b1;
			char bit2 = pic.blue_at(x, y) & 0b1;
			char bit3 = pic.green_at(x, y) & 0b1;

			addBit(bit1); addBit(bit2); addBit(bit3);

			if (end) break;
		}

		if (end) break;
	}

	std::cout << text<<"\n";
}
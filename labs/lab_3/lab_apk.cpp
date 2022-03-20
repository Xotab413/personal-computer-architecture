#include <dos.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define COLOR_COUNT 3              //red, green, blue 
unsigned char colors[COLOR_COUNT] = { 0x04,0x02,0x01 };
char color = 0x07; // white
char defColot = 0x07;

struct VIDEO_CARD_BUFFER {
	unsigned char symbol;
	unsigned char color;
};

void changeColorKeyboard() {
	color = colors[0];
	return;
}

void changeColorMouse() {
	color = colors[1];
	return;
}

void print()
{
	char tmp;
	int i, registerr;
	VIDEO_CARD_BUFFER far* screen = (VIDEO_CARD_BUFFER far*)MK_FP(0xB800, 0);
	screen += 48;
	registerr = inp(0x21);                                     // получение ведущего регистра масок
	for (i = 0; i < 8; i++)
	{
		tmp = registerr % 2;
		registerr = registerr >> 1;
		screen->symbol = tmp + '0';
		screen->color = color;
		screen++;
	}
	screen++;
	registerr = inp(0xA1);                                     // получение ведомого регистра масок
	for (i = 0; i < 8; i++)
	{
		tmp = registerr % 2;
		registerr = registerr >> 1;
		screen->symbol = tmp + '0';
		screen->color = color;
		screen++;
	}
	char str1[] = "- mask   ";
	for (i = 0; str1[i]; i++) {
		screen->symbol = str1[i];
		screen->color = defColot;
		screen++;
	}
	screen += 54;			//Чтобы считать регистр запросов, его нужно выбрать (записать в 20h/A0h значение 0Ah), а затем считать содержимое из порта 20h/A0h.
	outp(0x20, 0x0A);       // выбор и получение регистра запросов ведущего

	registerr = inp(0x20);
	for (i = 0; i < 8; i++)
	{
		tmp = registerr % 2;
		registerr = registerr >> 1;
		screen->symbol = tmp + '0';
		screen->color = color;
		screen++;
	}
	screen++;
	outp(0xA0, 0x0A);                 // выбор и получение регистра запросов ведомого
	registerr = inp(0xA0);
	for (i = 0; i < 8; i++)
	{
		tmp = registerr % 2;
		registerr = registerr >> 1;
		screen->symbol = tmp + '0';
		screen->color = color;
		screen++;
	}
	char str2[] = "- request";
	for (i = 0; str2[i]; i++) {
		screen->symbol = str2[i];
		screen->color = defColot;
		screen++;
	}
	screen += 54;

	outp(0x20, 0x0B);                     //Чтобы считать регистр обслуживания, его нужно выбрать (записать в 20h/A0h значение 0Bh), а затем считать содержимое из порта 20h/A0h.
	registerr = inp(0x20);                // выбор и получение сервисного регистра ведущего
	for (i = 0; i < 8; i++)
	{
		tmp = registerr % 2;
		registerr = registerr >> 1;
		screen->symbol = tmp + '0';
		screen->color = color;
		screen++;
	}
	screen++;

	outp(0xA0, 0x0B);                  // выбор и получение сервисного регистра ведомого
	registerr = inp(0xA0);
	for (i = 0; i < 8; i++)
	{
		tmp = registerr % 2;
		registerr = registerr >> 1;
		screen->symbol = tmp + '0';
		screen->color = color;
		screen++;
	}

	char str3[] = "- service";
	for (i = 0; str3[i]; i++) {
		screen->symbol = str3[i];
		screen->color = defColot;
		screen++;
	}

	screen += 54;
	char str4[] = "Master   Slave";
	for (i = 0; str4[i]; i++) {
		screen->symbol = str4[i];
		screen->color = defColot;
		screen++;
	}

}

void interrupt(*old_int08) (...);// IRQ  0 - программируемый интервальный таймер или высокоточный таймер событий №0;
void interrupt(*old_int09) (...);// IRQ  1 - клавиатура
void interrupt(*old_int0A) (...);// IRQ  2 - запрос прерывания от ведомого контроллера прерываний;
void interrupt(*old_int0B) (...);// IRQ  3 - произвольное устройство (в IBM PC/AT — последовательный порт COM2 и COM4);
void interrupt(*old_int0C) (...);// IRQ  4 - произвольное устройство (в IBM PC/AT — последовательный порт COM1 и COM3);
void interrupt(*old_int0D) (...);// IRQ  5 - произвольное устройство (в IBM PC/AT — параллельный порт LPT2);
void interrupt(*old_int0E) (...);// IRQ  6 - произвольное устройство (в IBM PC/AT — контроллер гибких дисков);
void interrupt(*old_int0F) (...);// IRQ  7 - произвольное устройство (в IBM PC/AT — параллельный порт LPT1);

void interrupt(*old_int70) (...);// IRQ  8 - часы реального времени или высокоточный таймер событий №1;
void interrupt(*old_int71) (...);// IRQ  9 - произвольное устройство
void interrupt(*old_int72) (...);// IRQ 10 - произвольное устройство
void interrupt(*old_int73) (...);// IRQ 11 - произвольное устройство или высокоточный таймер событий №2;
void interrupt(*old_int74) (...);// IRQ 12 - произвольное устройство, обычно мышь, либо высокоточный таймер событий №3;
void interrupt(*old_int75) (...);// IRQ 13 - ошибка арифметического сопроцессора
void interrupt(*old_int76) (...);// IRQ 14 - произвольное устройство, обычно первый контроллер ATA (или контроллер Serial ATA в режиме совместимости)
void interrupt(*old_int77) (...);// IRQ 15 - произвольное устройство, обычно второй контроллер ATA (или контроллер Serial ATA в режиме совместимости)

//Новые прерывания

void interrupt  new_int08(...) { print(); old_int08(); }
void interrupt  new_int09(...) { changeColorKeyboard(); print(); old_int09(); }
void interrupt  new_int0A(...) { print(); old_int0A(); }
void interrupt  new_int0B(...) { print(); old_int0B(); }
void interrupt  new_int0C(...) { print(); old_int0C(); }
void interrupt  new_int0D(...) { print(); old_int0D(); }
void interrupt  new_int0E(...) { print(); old_int0E(); }
void interrupt  new_int0F(...) { print(); old_int0F(); }

void interrupt  new_int70(...) { print(); old_int70(); }
void interrupt  new_int71(...) { print(); old_int71(); }
void interrupt  new_int72(...) { print(); old_int72(); }
void interrupt  new_int73(...) { print(); old_int73(); }
void interrupt  new_int74(...) { changeColorMouse(); print(); old_int74(); }
void interrupt  new_int75(...) { print(); old_int75(); }
void interrupt  new_int76(...) { print(); old_int76(); }
void interrupt  new_int77(...) { print(); old_int77(); }

void initialize() {
	//Получение функций прерывания
	old_int08 = getvect(0x08);
	old_int09 = getvect(0x09);
	old_int0A = getvect(0x0A);
	old_int0B = getvect(0x0B);
	old_int0C = getvect(0x0C);
	old_int0D = getvect(0x0D);
	old_int0E = getvect(0x0E);
	old_int0F = getvect(0x0F);

	old_int70 = getvect(0x70);
	old_int71 = getvect(0x71);
	old_int72 = getvect(0x72);
	old_int73 = getvect(0x73);
	old_int74 = getvect(0x74);
	old_int75 = getvect(0x75);
	old_int76 = getvect(0x76);
	old_int77 = getvect(0x77);

	//Установка их в новые функции
	setvect(0x08, new_int08);
	setvect(0x09, new_int09);
	setvect(0x0A, new_int0A);
	setvect(0x0B, new_int0B);
	setvect(0x0C, new_int0C);
	setvect(0x0D, new_int0D);
	setvect(0x0E, new_int0E);
	setvect(0x0F, new_int0F);

	setvect(0x78, new_int70);
	setvect(0x79, new_int71);
	setvect(0x7A, new_int72);
	setvect(0x7B, new_int73);
	setvect(0x7C, new_int74);
	setvect(0x7D, new_int75);
	setvect(0x7E, new_int76);
	setvect(0x7F, new_int77);

	_disable(); // Запрет всех прерываний
	//ICW1 всегда равно 11h.
	outp(0x20, 0x11);	
	//для линий IRQ0 и IRQ8 вектор прерывания будет равен значению ICW2
	//младшие три в 0
	outp(0x21, 0x08);   
	//всегда 04h поскольку единственный ведомый контроллер подключен к IRQ2.
	outp(0x21, 0x04);	
	//
	outp(0x21, 0x01);	

	//ICW1 всегда равно 11h
	outp(0xA0, 0x11);   
	//базовый вектор прерывания
	outp(0xA1, 0x78);
	//ICW3 задаёт номер соответствующей ему линии IRQ ведущего контроллера. На ПК оно всегда равно 02h.
	outp(0xA1, 0x02);
	//первый бит определяет EOI, нулевой всегда в 1(процессор 8086), остальные по 0
	outp(0xA1, 0x01);

	_enable(); // Разрешение прерываний
}

int main() {
	unsigned far* fp;
	initialize();
	system("cls");

	FP_SEG(fp) = _psp;     //получение сегмента данных
	FP_OFF(fp) = 0x2c;     // смещение данных с переменными среды
	_dos_freemem(*fp);

	_dos_keep(0, (_DS - _CS) + (_SP / 16) + 1); // оставляет программу резидентной, первый параметр - код выхода,
												// 2объем памяти, который должен быть зарезервирован после завершения
	return 0;
}
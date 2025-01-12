#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <clocale>
#include <string.h>
#include <malloc.h>
#include <windows.h>

using namespace std;
using namespace System;
using namespace System::IO;

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79





struct z {
	char name[20]; // имя гонщика
	char country[15]; // откуда родом
	char titul[23]; // титул в формуле-1
	long age; //  возраст
	long nvict; // количество побед
	char vict[30]; // последняя победа
};

struct sp {
	char fio[20];
	long nvict;
	struct sp* sled;
	struct sp* pred;
};


int menu(int);
void maxim(struct z*, int);
void minim(struct z*, int);
void odtit(struct z*, int);
void text_data(char*, char*, int);
void kolvo(struct z*, int);
void alfalist(struct z*, int, struct sp**);
void vstavka(struct z*, char*, int, struct sp**);
void listing(struct z*, int);
void diagram(struct z*, int, struct sp**);

int main(array<System::String^>^ args)
{
	int NC;
	char dan[][120] = {
	"Какой гонщик имеет больше всех побед?                    ",
	"Какой гонщик самый молодой?                              ",
	"Есть ли гонщики имеющие одинаковый титул и одногодки?    ",
	"Список гонщиков с победой в Гран-при Германии любого года",
	"Алфавитный и обратный список всех гонщиков               ",
	"Количество гонщиков родом из Великобритании              ",
	"Диаграмма. Процентное соотношение побед гонщиков         ",
	"Выход                                                    "
	};
	char BlankLine[] = "                                                           ";
	int i, n;
	FILE* in;
	struct z* drivers;
	setlocale(LC_CTYPE, "Russian");
	Console::CursorVisible::set(false);
	Console::BufferHeight = Console::WindowHeight;
	Console::BufferWidth = Console::WindowWidth;
	if ((in = fopen("form1.txt", "r")) == NULL)
	{
		printf("\nФайл form1.txt не открыт !");
		getch(); exit(1);
	}
	fscanf(in, "%d", &NC);
	drivers = (struct z*)malloc(NC * sizeof(struct z));
	for (i = 0; i < NC; i++)
		fscanf(in, "%s%s%s%s%ld%ld", drivers[i].name,
			drivers[i].country, drivers[i].titul, drivers[i].vict, &drivers[i].age, &drivers[i].nvict);
	for (i = 0; i < NC; i++)
		printf("\n%-20s %-15s %-23s %ld %ld %-30s",
			drivers[i].name,
			drivers[i].country, drivers[i].titul, drivers[i].age, drivers[i].nvict, drivers[i].vict);
	getch();

	struct sp* spisok =0;
	
	while (1)
	{
		Console::ForegroundColor = ConsoleColor::Gray;
		Console::BackgroundColor = ConsoleColor::Black;
		Console::Clear();
		Console::ForegroundColor = ConsoleColor::White;
		Console::BackgroundColor = ConsoleColor::Red;
		Console::CursorLeft = 10;
		Console::CursorTop = 4;
		printf(BlankLine);
		for (i = 0; i < 8; i++)
		{
			Console::CursorLeft = 10;
			Console::CursorTop = i + 5;
			printf(" %s ", dan[i]);
		}
		Console::CursorLeft = 10;
		Console::CursorTop = 13;
		printf(BlankLine);
		n = menu(8);
		switch (n) {
		case 1: maxim(drivers, NC); break;
		case 2: minim(drivers, NC); break;
		case 3: odtit(drivers, NC); break;
		case 4: listing(drivers, NC); break;
		case 5: alfalist(drivers, NC, &spisok); break;
		case 6: kolvo(drivers, NC); break;
		case 7: diagram(drivers, NC, &spisok); break;
		case 8: exit(0);
		}
	} // конец while(1)...
	return 0;
} // конец main()


int menu(int n)
{
	char dan[][120] = {
	"Какой гонщик имеет больше всех побед?                    ",
	"Какой гонщик самый молодой?                              ",
	"Есть ли гонщики имеющие одинаковый титул и одногодки?    ",
	"Список гонщиков с победой в Гран-при Германии любого года",
	"Алфавитный и обратный список всех гонщиков               ",
	"Количество гонщиков родом из Великобритании              ",
	"Диаграмма. Процентное соотношение побед гонщиков         ",
	"Выход                                                    "
		};
	char BlankLine[] = "                                                           ";
	int y1 = 0, y2 = n - 1;
	char c = 1;
	while (c != ESC)
	{
		switch (c) {
		case DOWN: y2 = y1; y1++; break;
		case UP: y2 = y1; y1--; break;
		case ENTER: return y1 + 1;
		case HOME: return 0;
		case END: y2 = y1; y1 = 7; break;
		}
		if (y1 > n - 1) { y2 = n - 1; y1 = 0; }
		if (y1 < 0) { y2 = 0; y1 = n - 1; }
		Console::ForegroundColor = ConsoleColor::White;
		Console::BackgroundColor = ConsoleColor::DarkRed;
		Console::CursorLeft = 11;
		Console::CursorTop = y1 + 5;
		printf("%s", dan[y1]);
		Console::ForegroundColor = ConsoleColor::White;
		Console::BackgroundColor = ConsoleColor::Red;
		Console::CursorLeft = 11;
		Console::CursorTop = y2 + 5;
		printf("%s", dan[y2]);
		c = getch();
	} // конец while(c!=ESC)...
	exit(0);
}

void maxim(struct z* driver, int NC)
{
	int i = 0; struct z best;
	strcpy(best.name, driver[0].name);
	best.nvict = driver[0].nvict;
	for (i = 1; i < NC; i++)
		if (driver[i].nvict > best.nvict)
		{
			strcpy(best.name, driver[i].name);
			best.nvict = driver[i].nvict;
		}
	Console::ForegroundColor = ConsoleColor::White;
	Console::BackgroundColor = ConsoleColor::Black;
	Console::CursorLeft = 10;
	Console::CursorTop = 15;
	printf("Максимальный кол-во побед %ld", best.nvict);
	Console::CursorLeft = 10;
	Console::CursorTop = 16;
	printf("имеет гонщик %s", best.name);
	getch();
}


void minim(struct z* driver, int NC)
{
	int i = 0; struct z lose;
	strcpy(lose.name, driver[0].name);
	lose.age = driver[0].age;
	for (i = 1; i < NC; i++)
		if (driver[i].age < lose.age)
		{
			strcpy(lose.name, driver[i].name);
			lose.age = driver[i].age;
		}
	Console::ForegroundColor = ConsoleColor::White;
	Console::BackgroundColor = ConsoleColor::Black;
	Console::CursorLeft = 10;
	Console::CursorTop = 15;
	printf("Возраст самого молодого гонщика %ld", lose.age);
	Console::CursorLeft = 10;
	Console::CursorTop = 16;
	printf("имеет %s", lose.name);
	getch();
}

void odtit(struct z* driver, int NC)
{
	int i, j;
	char *s;
	s = "Не найден";
	struct z* best = driver;
	for (i = 0; i < NC - 1; i++) {
		for (j = i + 1; j < NC; j++) {
			if (driver[i].age == driver[j].age && strstr(driver[i].titul, driver[j].titul)) {
				s = "Найден";
				break;
			}
		}
	}
	Console::ForegroundColor = ConsoleColor::White;
	Console::BackgroundColor = ConsoleColor::Black;
	Console::CursorLeft = 10;
	Console::CursorTop = 15;
	printf("%s", s);
	getch();
}


void kolvo(struct z* driver, int NC)
{
	int i, k = 0;
	for (i = 0; i < NC; i++)
		if (strcmp(driver[i].country, "Великобритания") == 0)
			k++;
	Console::ForegroundColor = ConsoleColor::White;
	Console::BackgroundColor = ConsoleColor::Black;
	Console::CursorLeft = 10;
	Console::CursorTop = 15;
	printf("Гонщиков из Великобритании ");
	printf("Всего : %d", k);
	getch();
}

void alfalist(struct z* driver, int NC, struct sp**spisok)
{
	int i, n=0;
	struct sp* nt;
	struct sp* z;
	Console::ForegroundColor = ConsoleColor::White;
	Console::BackgroundColor = ConsoleColor::Red;
	Console::Clear();
	if (!*spisok)
		for (i = 0; i < NC; i++)
			vstavka(driver, driver[i].name, NC, spisok);
	Console::Clear();
	printf("\n Алфавитный список и обратный список гонщиков");
	printf("\n ============================================\n");
	for (nt = *spisok; nt != 0; nt = nt->sled)
		printf("\n %-30s %ld", nt->fio, nt->nvict);
	for (nt = *spisok, z = 0; nt != 0; z = nt, nt = nt->sled);
	for (nt = z; nt != 0; nt = nt->pred)
	{
		Console::CursorLeft = 48;
		Console::CursorTop = 4 + n;
		printf(" %-30s %ld", nt->fio, nt->nvict);
		n += 1;
	}
	getch();
}

void vstavka(struct z* driver, char* fio, int NC, struct sp**spisok)
{
	int i;
	struct sp* nov, * nt, * z = 0;
	for (nt = *spisok; nt != 0 && strcmp(nt->fio, fio) < 0; z = nt, nt = nt->sled);
	if (nt && strcmp(nt->fio, fio) == 0) return;
	nov = (struct sp*)malloc(sizeof(struct sp));
	strcpy(nov->fio, fio);
	nov->sled = nt;
	nov->pred = z;
	nov->nvict = 0;
	for (i = 0; i < NC; i++)
		if (strcmp(driver[i].name, fio) == 0)
			nov->nvict += driver[i].nvict;
	if (!z) *spisok = nov;
	else z->sled = nov;
	if (nt) nt->pred = nov;
	return;
}

void listing(struct z* driver, int NC)
{
	int i;
	struct z* nt;
	Console::ForegroundColor = ConsoleColor::White;
	Console::BackgroundColor = ConsoleColor::Red;
	Console::Clear();
	printf("\n\r Список гонщиков с победой в Гран-при Германии любого года");
		printf("\n\r ====================================================\n\r");
			for (i = 0, nt = driver; i < NC; nt++, i++)
				if (strstr(nt->vict, "Гран-при_Германии"))
					printf("\n\r %-20s %ld победы", nt->name, nt->nvict);
	getch();
}

void diagram(struct z* driver, int NC, struct sp**spisok)
{
	struct sp* nt;
	int len, i, NColor;
	long sum = 0;
	char str1[20];
	char str2[20];
	System::ConsoleColor Color;
	Console::ForegroundColor = ConsoleColor::Black;
	Console::BackgroundColor = ConsoleColor::White;
	Console::Clear();
	for (i = 0; i < NC; i++) sum = sum + driver[i].nvict;
	if (!spisok)
		for (i = 0; i < NC; i++)
			vstavka(driver, driver[i].name, NC, spisok);
	Color = ConsoleColor::Black; NColor = 0;
	for (nt = *spisok, i = 0; nt != 0; nt = nt->sled, i++)
	{
		sprintf(str1, "%s", nt->fio);
		sprintf(str2, "%3.1f%%", (nt->nvict * 100. / sum));
		Console::ForegroundColor = ConsoleColor::Black;
		Console::BackgroundColor = ConsoleColor::White;
		Console::CursorLeft = 5; Console::CursorTop = i + 1;
		printf(str1);
		Console::CursorLeft = 20;
		printf("%s", str2);
		Console::BackgroundColor = ++Color; NColor++;
		Console::CursorLeft = 30;
		for (len = 0; len < nt->nvict * 100 / sum; len++) printf(" ");
		if (NColor == 14)
		{
			Color = ConsoleColor::Black; NColor = 0;
		}
	}
	getch();
	return;
}
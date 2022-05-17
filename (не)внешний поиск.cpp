#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <time.h>
#include <random>
#include <stdio.h>
#include <fstream>

using namespace std;

struct Note //структура, представляющая запись
{
	int key; //ключ
	int number;
};

const int m = 10; //размер таблицы
int kol = 0;

int HashFunction(int k) //хэш-функция деления
{
	return k % m;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int count;
	fstream out, oldout; //поток для записи
	out.open("hash.txt", fstream::out);
	fstream in; //поток для чтения
	in.open("start.txt", fstream::in);

	for (int i = 0; i < m; i++)
		out << i <<  "." << endl;
	out.close();

	string curstr;
	string number;
	int key; //value
	int ind, a; //key

	while (in >> key) //заполнение хэш-файла
	{
		ind = HashFunction(key);

		out.open("hash1.txt", fstream::out);
		oldout.open("hash.txt", fstream::in);

		do
		{
			getline(oldout, curstr); //считываем строку
			if (curstr != "")
			{
				number = "";
				for (int i = 0; i < curstr.length(); i++) //считываем заголовок строки
					if (curstr[i] != '.')
						number += curstr[i];
					else break;
				a = stoi(number);
				if (a == ind)
					curstr += " " + to_string(key); //добавляем наше число в строку
				out << curstr << endl;
			}
		} while (!oldout.eof());

		oldout.close();
		out.close();
		remove("hash.txt");
		rename("hash1.txt", "hash.txt");
	}
	in.close();

	int num;
	cout << "Введите ключ: ";
	cin >> num;

	while (num != -1) //поиск
	{
		bool rec = 0; //найдено ли число?
		ind = HashFunction(num); //определяем строку таблицы
		out.open("hash.txt", fstream::in);
		do
		{
			getline(out, curstr); //считываем строку
			if (curstr != "")
			{
				number = "";
				int i;
				for (i = 0; i < curstr.length(); i++) //считываем заголовок строки
					if (curstr[i] != '.')
						number += curstr[i];
					else break;
				a = stoi(number);
				if (a == ind)
				{
					number = "";
					for (int j = i + 2; j < curstr.length(); j++)
					{
						while (curstr[j] != ' ' && j < curstr.length()) //считали число из строки 
						{
							number += curstr[j];
							j++;
						}
						a = stoi(number);
						if (a == num) //если нашли число
						{
							cout << a << " найден в строке с индексом " << ind << endl;
							rec = 1;
							break;
						}
					}
				}
			}
			if (rec)
				break;
		} while (!out.eof());
		out.close();
		if (!rec)
			cout << "Запись не найдена!" << endl;

		cout << "Введите ключ: ";
		cin >> num;
	}
	out.close();

	system("pause");
	return 0;
}

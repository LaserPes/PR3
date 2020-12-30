#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <time.h>

using namespace std;

void Show(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout << arr[(i * size) + j] << ' ';

		cout << '\n';
	}
}
void SnakeFilling(int* arr, short int size)
{
	int* parr = arr;
	CONSOLE_SCREEN_BUFFER_INFO info_y;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
	int y_coord = info_y.dwCursorPosition.Y + 1;
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int j = 0; j < size; ++j)
	{
		if (j % 2 == 0) {
			
			for (int i = 0; i < size; ++i)
			{
				*arr = rand() % (size * size) + 1;
				position.X = j*4;
				position.Y = y_coord + i;
				SetConsoleCursorPosition(hConsole, position);
				cout << *arr << endl;
				Sleep(50);
			}
		}
		else {
			for (int i = size - 1; i >= 0; --i)
			{
				*arr = rand() % (size * size) + 1;
				position.X = j*4;
				position.Y = y_coord + i;
				SetConsoleCursorPosition(hConsole, position);
				cout  << *arr ;
				Sleep(50);
			}
		}
		
	}
	position.X = 0;
	position.Y = y_coord + size;
	SetConsoleCursorPosition(hConsole, position);
}

void SpiralFilling(int* arr, short int size) // спиральное заполнение
{
	int* parr = arr;
	CONSOLE_SCREEN_BUFFER_INFO info_y;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
	int y_coord = info_y.dwCursorPosition.Y + 1;
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < size / 2; i++)
	{
		
		for (int j = 0; j < (size - i * 2 - 1); j++) //Заполнение вправо
		{
			*arr = rand() % (size * size) + 1;
			position.X = (j + i) * 4;
			position.Y = y_coord + i;
			SetConsoleCursorPosition(hConsole, position);
			cout << *arr;
			Sleep(50);
			arr++;
		}
		
		for (int j = 0; j < (size - i * 2 - 1); j++) //Заполнение вниз
		{
			*arr = rand() % (size * size) + 1;
			position.X = (size - i - 1) * 4;
			position.Y = y_coord + (i + j);
			SetConsoleCursorPosition(hConsole, position);
			cout << *arr;
			Sleep(50);
			arr += size;
		}
		
		for (int j = (size - i * 2 - 1); j > 0; j--)//Заполнение влево
		{
			*arr = rand() % (size * size) + 1;
			position.X = (i + j) * 4;
			position.Y = y_coord + size - 1 - i;
			SetConsoleCursorPosition(hConsole, position);
			cout << *arr;
			Sleep(50);
			arr--;
		}
		
		for (int j = (size - i * 2 - 1); j > 0; j--)//Заполнение вверх
		{
			*arr = rand() % (size * size) + 1;
			position.X = i * 4;
			position.Y = y_coord + (j + i);
			SetConsoleCursorPosition(hConsole, position);
			cout << *arr;
			Sleep(50);
			arr -= size;
		}
		arr += size + 1;
	}

	position.X = 0;
	position.Y = y_coord + size;
	SetConsoleCursorPosition(hConsole, position);
}

void VerticalSwipe(int* arr, int size)
{
	int temp;
	int* parr = arr;
	for (int i = 0; i < (size / 2); i++)
	{
		for (int j = 0; j < (size / 2); j++) // левая половина матрицы
		{
			temp = *(parr + (i * size) + j);
			*(parr + (i * size) + j) = *(parr + ((i + size / 2) * size) + j);
			*(parr + ((i + size / 2) * size) + j) = temp;
		}
		for (int j = 0; j < (size / 2); j++) // правая половина
		{
			temp = *(parr + (i * size) + j + (size / 2));
			*(parr + (i * size) + j + (size / 2)) = *(parr + ((i + size / 2) * size) + j + (size / 2));
			*(parr + ((i + size / 2) * size) + j + (size / 2)) = temp;
		}
	}
}

void Sorting(int* arr, int size) //Сортировка пузырьком
{
	int temp;
	int* psort1 = arr;
	int* psort2 = arr + 1;

	for (int i = 0; i < (size * size - 1); i++)
	{
		for (int j = i + 1; j < (size * size); j++)
		{
			if (*psort1 > *psort2)
			{
				temp = *psort1;
				*psort1 = *psort2;
				*psort2 = temp;
			}
			psort2++;
		}
		psort1++;
		psort2 = psort1 + 1;
	}

	Show(arr, size);
}

int main()
{
	setlocale(LC_ALL, "rus");

	srand(time(NULL));

	int number = 5;
	int arr[100];
	int size, numbOperation, actionNumber;

	

	cout << endl;

	while (number != 0)
	{
		cout << "1. Вывести матрицу змейкой\n";
		cout << "2. Вывести матрицу по спирали\n";
		cout << "3. Переставить блоки матрицы вертикально.\n";
		cout << "4. Отсортировать матрицу. (метод пузырьком)\n";
		cout << "5. Уменьшить, увеличить, умножить или поделить на введеное число.\n";
		cout << "6. Завершить.\n";
		cout << "Выберите пункт: ";
		cin >> number;
		cout << '\n';
		if (number == 1) { // создание матрицы
			cout << "Выберите число: 6, 8, 10: ";
			cin >> size;
			if ((size == 6) || (size == 8) || (size == 10))
				SnakeFilling(arr, size);
			else
				cout << "Вы ввели некорректное число\n";
		}
		
		if (number == 2) { // создание матрицы
			cout << "Выберите число: 6, 8, 10: ";
			cin >> size;
			if ((size == 6) || (size == 8) || (size == 10))
				SpiralFilling(arr, size);
			else
				cout << "Вы ввели некорректное число\n";
		}

		if (number == 3) { // перемещение по вертикали
			VerticalSwipe(arr, size);
			Show(arr, size);
		}

		if (number == 4) { // сортировка
			Sorting(arr, size);
		}

		if (number == 5) {
			cout << "Выберите операцию: \n1 - уменьшить, 2 - увеличить, 3 - умножить, 4 - поделить:\nНомер: ";
			cin >> numbOperation;

			if (numbOperation == 1) {
				cout << "Введите число на которое нужно уменьшить: ";
				cin >> actionNumber;

				for (int i = 0; i < (size * size); i++)
					arr[i] -= actionNumber;

				Show(arr, size);
			}
			else if (numbOperation == 2) {
				cout << "Введите число на которое нужно прибавить: ";
				cin >> actionNumber;

				for (int i = 0; i < (size * size); i++)
					arr[i] += actionNumber;

				Show(arr, size);
			}
			else if (numbOperation == 3) {
				cout << "Введите число на которое нужно умножить: ";
				cin >> actionNumber;

				for (int i = 0; i < (size * size); i++)
					arr[i] *= actionNumber;

				Show(arr, size);
			}
			else if (numbOperation == 4) {
				cout << "Введите число на которое нужно разделить: ";
				cin >> actionNumber;

				for (int i = 0; i < (size * size); i++)
					arr[i] /= actionNumber;

				Show(arr, size);
			}
			else
				cout << "\nВведенного пункта операции не сущетсвует." << endl;
		}

	}

	cout << "..." << endl;
}
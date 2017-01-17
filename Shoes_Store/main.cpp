// Shoes_Store.cpp: определяет точку входа для консольного приложения.
//

#define NOMINMAX

#include "stdafx.h"
#include <iostream> //Для ввода-вывода
#include <string> //Для строк
#include <fstream>//Для файлов
#include <conio.h> //Для задержки консоли
#include <list> //Для работы с структурой
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <iomanip>

using namespace std;

//Структура для работы
struct ShoesStruct
{
	//порядковый номер записи
	int iPosition;
	//Артикул обуви
	std::string sArticle;
	//Наименование
	std::string sName;
	//Количество
	int iCount;
	//Стоимость одной пары
	double dCost;
	//Флаг наличия товара
	bool bHave;
};

//Струкура для сортировки по названию
struct SortNameStruct
{
public:
	bool operator() (const ShoesStruct *first, const ShoesStruct *second)
	{
		return (first->sName < second->sName);
	}
	bool operator() (const ShoesStruct &first, const ShoesStruct &second)
	{
		return (first.sName < second.sName);
	}
};

//Струкура для сортировки по стоимости обуви
struct SortCostStruct
{
public:
	bool operator() (const ShoesStruct *first, const ShoesStruct *second)
	{
		return (first->dCost < second->dCost);
	}
	bool operator() (const ShoesStruct &first, const ShoesStruct &second)
	{
		return (first.dCost < second.dCost);
	}
};

//Лист структур для работы
list<ShoesStruct> shoesList;

//Названия файлов
const char* cNameFile = "shoes_list.txt";

// Ф-ция добавления нового элемента в список
void addShoesV(list<ShoesStruct> &shoesList);
// Ф-ция редактирования записи
void editShoesV(list<ShoesStruct> &shoesList);
// Ф-ция отображения элементов списка на экране
void displayV(list<ShoesStruct> &shoesList);
// Ф-ция удаления всех элементов в списке
void delAllV(list<ShoesStruct> &shoesList);
// Ф-ция удаления одного элемента в списке
void dellOneV(list<ShoesStruct> &shoesList);
// Ф-ция заполнения списка элементами из файла(новые элементы добавляются в конец списка)
void readFileV();
// Ф-ция записи в файла элементов списка
void writeFileV();

// Ф-ция поиска данных
void searchV(list<ShoesStruct> &shoesList);
// Ф-ция сортировки данных
void sortAbonentV();

// Ф-ция работы с меню
int myMenuI(int admin_status);
// Ф-ция вызова меню администратора
int adminMenuI();
// Ф-ция вызова меню пользователя
int userMenuI();
// Ф-ция смены пароля
int changePasswordI();
// Ф-ция проверки правильного пароля
int checkPasswordI();

// Ф-ция добавления новых элементов
void addAbonentV(list<ShoesStruct> &shoesList)
{
	system("Cls");
	std::string TEXT;

	//Создаем временную переменную
	ShoesStruct *shoesStr = new ShoesStruct;

	int i = 0, iBuffer = 0;
	double dBuffer = 0;
	int count;
	cout << "Сколько записей добавить?" << endl;
	cin >> count;
	cin.ignore(); 

	for (i = 0; i < count; i++)
	{
		//Заполняем её
		cout << "Элемент " << shoesList.size() << endl;

		//Ввод инвентарного номера
		//Цикл который выполниться минимум 1 раз
		do
		{
			cout << "Введите инв.номер: ";
			getline(cin, TEXT);

			try
			{
				//Конверт данных в число
				iBuffer = std::stoi(TEXT);
			}
			catch(...)
			{
				cout << "Неправильный формат инвентарного номера!!! Попробуйте еще!!!" << endl;
				//tmp->position = 0;
				iBuffer = -2;
			}

			if (iBuffer != -2 && iBuffer < 0)
			{
				cout << "Неправильный формат инвентарного номера!!! Попробуйте еще!!!" << endl;
			}
		}
		while(iBuffer < 0);

		shoesStr->iPosition = iBuffer;
		iBuffer = 0;

		//Ввод артикула
		//Цикл который выполниться минимум 1 раз
		do
		{
			cout << "Введите артикул: " << endl;
			getline(cin, TEXT);

			if((TEXT == "М") || (TEXT == "м"))
			{
				iBuffer = 0;
			}
			else if((TEXT == "Ж") || (TEXT == "ж"))
			{
				iBuffer = 0;
			}
			else if((TEXT == "Д") || (TEXT == "д"))
			{
				iBuffer = 0;
			}
			else
			{
				iBuffer = -1;
			}
		}

		while(iBuffer < 0);
		iBuffer = 0;

		shoesStr->sArticle = TEXT;

		//Ввод наименования
		cout << "Введите наименование: ";
		getline(cin, TEXT);
		shoesStr->sName = TEXT;

		//Ввод количества пар
		//Цикл который выполниться минимум 1 раз
		do
		{
			cout << "Введите количество пар: ";
			getline(cin, TEXT);

			try
			{
				//Конверт данных в число
				iBuffer = std::stoi(TEXT);
			}
			catch(...)
			{
				cout << "Неправильный формат количества пар!!! Попробуйте еще!!!" << endl;
				//tmp->position = 0;
				iBuffer = -2;
			}

			if (iBuffer != -2 && iBuffer < 0)
			{
				cout << "Неправильный формат количества пар!!! Попробуйте еще!!!" << endl;
			}
		}
		while(iBuffer < 0);

		//Проверка на наличие
		if(iBuffer != 0)
		{
			//Показываем, что обуви имеется в наличии
			shoesStr->bHave = true;
		}
		else
		{
			//Показываем, что обувь не имеется в наличии
			shoesStr->bHave = false;
		}

		shoesStr->iCount = iBuffer;
		iBuffer = 0;

		//Ввод стоимости одной пары
		//Цикл который выполниться минимум 1 раз
		do
		{
			cout << "Введите сумму в рублях, стоимость одной пары обуви: ";
			getline(cin, TEXT);

			try
			{
				//Конверт данных в число
				dBuffer = std::stod(TEXT);
			}
			catch(...)
			{
				cout << "Неправильный формат суммы!!! Попробуйте еще!!!" << endl;
				//tmp->position = 0;
				dBuffer = -2;
			}

			if (dBuffer != -2 && dBuffer < 0)
			{
				cout << "Неправильный формат суммы!!! Попробуйте еще!!!" << endl;
			}
		}
		while(dBuffer < 0);

		shoesStr->dCost = dBuffer;
		dBuffer = 0;

		// Добавляем её в список
		shoesList.push_back( *shoesStr );
	}

	// Освобождаем память
	delete shoesStr;
}

// Ф-ция редактирования существующей записи
void editAbonentV(list<ShoesStruct> &shoesList)
{
	system("Cls");
	std::string TEXT;
	cin.ignore();

	double dBuffer = 0;
	int iInvNomer = 0, iEditChoose = 0, iPosition = 0, iBuffer = 0;	
	bool bInvNomer = false;

	//Проверка на пустоту
	if (shoesList.empty())
	{
		cout << "Элементов не обнаружено!!!" << endl;
		return;
	}	

	//Ввод инвентарного номера
	//Цикл который выполниться минимум 1 раз
	do
	{
		cout << "Введите инв.номер: ";
		getline(cin, TEXT);

		try
		{
			//Конверт данных в число
			iBuffer = std::stoi(TEXT);
		}
		catch(...)
		{
			cout << "Неправильный формат инвентарного номера!!! Попробуйте еще!!!" << endl;
			//tmp->position = 0;
			iBuffer = -2;
		}

		if (iBuffer != -2 && iBuffer < 0)
		{
			cout << "Неправильный формат инвентарного номера!!! Попробуйте еще!!!" << endl;
		}
	}
	while(iBuffer < 0);

	iInvNomer = iBuffer;
	iBuffer = 0;

	//Организовываем цикл по листу структур
	for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
	{
		//Если в структуре имеется нужные нам значения, то сразу печатаем
		if ((*iter).iPosition == iInvNomer)
		{
			cout << "Инв. номер: ";
			cout << (*iter).iPosition << endl;
			cout << "Артикул: ";
			cout << (*iter).sArticle<< endl;
			cout << "Наименование: ";
			cout << (*iter).sName << endl;
			cout << "Количество пар: ";;
			cout << (*iter).iCount << endl;
			cout << "Стоимость одной пары: ";
			cout << fixed << setprecision(3) << (*iter).dCost << endl;
			cout << "Имеется ли в наличии: ";
			if((*iter).bHave == true)
			{
				cout << "Да" << endl;
			}
			else
			{
				cout << "Нет" << endl;
			}
			cout << "\n";

			bInvNomer = true;

			break;
		}
		else
		{
			bInvNomer = false;
		}
	}

	//Если не нашло записи
	if (bInvNomer == false)
	{
		cout << "Записи с таким инвентарным номером не обнаружено!!!" << endl;
		system("pause");
		return;
	}

	//Зацикленное меню редактирования выбранной записи
	do
	{
		cout << "Выберите поле для редактирования: " << endl;
		cout << "1. Артикул товара" << endl;
		cout << "2. Наименование товара" << endl;
		cout << "3. Количество товара" << endl;
		cout << "4. Стоимость товара" << endl;
		cout << "5. Имеется ли в наличии(Да/Нет, Д/Н, д/н)" << endl;
		cout << "0. Выйти из фунции редактирования записи" << endl;

		cin >> iEditChoose;

		//Создаем временную переменную
		ShoesStruct *shoesStr = new ShoesStruct;

		cin.ignore();

		switch(iEditChoose)
		{

			//Редактирование артикула
		case 1:

			cout << "Введите новое значение артикула: ";
			getline(cin, TEXT);

			//Организовываем цикл по листу структур
			for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
			{
				//Если в структуре есть запись с таким инвентарным номер, то заменяем фио сотрудник новым значением
				if ((*iter).iPosition == iInvNomer)
				{
					(*iter).sArticle = TEXT;
					break;
				}
			}

			cout << "Данные артикула изменены!!!" << endl << endl;

			break;

			//Редактирование наименования
		case 2:

			cout << "Введите новое значение наименования: ";
			getline(cin, TEXT);

			//Организовываем цикл по листу структур
			for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
			{
				//Если в структуре есть запись с таким инвентарным номер, то заменяем фио сотрудник новым значением
				if ((*iter).iPosition == iInvNomer)
				{
					(*iter).sName = TEXT;
					break;
				}
			}

			cout << "Данные Имени изменены!!!" << endl << endl;

			break;

			//Редактирование количества пар
		case 3:

			//Ввод количества пар
			//Цикл который выполниться минимум 1 раз
			do
			{
				cout << "Введите новое значение количества пар: ";
				getline(cin, TEXT);

				try
				{
					//Конверт данных в число
					iBuffer = std::stoi(TEXT);
				}
				catch(...)
				{
					cout << "Неправильный формат количества пар!!! Попробуйте еще!!!" << endl;
					//tmp->position = 0;
					iBuffer = -2;
				}

				if (iBuffer != -2 && iBuffer < 0)
				{
					cout << "Неправильный формат количества пар!!! Попробуйте еще!!!" << endl;
				}
			}
			while(iBuffer < 0);

			//Организовываем цикл по листу структур
			for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
			{
				//Если в структуре есть запись с таким инвентарным номер, то заменяем фио сотрудник новым значением
				if ((*iter).iPosition == iInvNomer)
				{
					(*iter).iCount = iBuffer;
					break;
				}
			}

			iBuffer = 0;

			cout << "Данные количества пар изменены!!!" << endl << endl;

			break;

			//Редактирование стоимости одной пары
		case 4:

			//Ввод стоимости одной пары
			//Цикл который выполниться минимум 1 раз
			do
			{
				cout << "Введите новое значение стоимости одной пары: ";
				getline(cin, TEXT);

				try
				{
					//Конверт данных в число
					dBuffer = std::stoi(TEXT);
				}
				catch(...)
				{
					cout << "Неправильный формат стоимости одной пары!!! Попробуйте еще!!!" << endl;
					//tmp->position = 0;
					dBuffer = -2;
				}

				if (dBuffer != -2 && dBuffer < 0)
				{
					cout << "Неправильный формат стоимости одной пары!!! Попробуйте еще!!!" << endl;
				}
			}
			while(dBuffer < 0);

			//Организовываем цикл по листу структур
			for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
			{
				//Если в структуре есть запись с таким инвентарным номер, то заменяем фио сотрудник новым значением
				if ((*iter).iPosition == iInvNomer)
				{
					(*iter).dCost = dBuffer;
					break;
				}
			}

			dBuffer = 0;

			cout << "Данные стоимости одной пары изменены!!!" << endl << endl;

			break;

			//Редактирование имеются ли в наличии
		case 5:

			//Ввод имеются ли в наличии
			//Цикл который выполниться минимум 1 раз
			do
			{
				cout << "Введите новое значение имеются ли в наличии(Да/Нет, Д/Н, д/н): " << endl;
				getline(cin, TEXT);

				if((TEXT != "Да") || (TEXT != "Д") || (TEXT != "д"))
				{
					iBuffer = 1;
				}
				else if((TEXT != "Нет") || (TEXT != "Н") || (TEXT != "н"))
				{
					iBuffer = 0;
				}
				else
				{
					iBuffer = -1;
				}
			}
			while(iBuffer < 0);

			iBuffer = 0;

			//Организовываем цикл по листу структур
			for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
			{
				//Если в структуре есть запись с таким инвентарным номер, то заменяем фио сотрудник новым значением
				if ((*iter).iPosition == iInvNomer)
				{
					if((TEXT == "Да") || (TEXT == "Д") || (TEXT == "д"))
					{
						(*iter).bHave = true;
					}
					else if((TEXT == "Нет") || (TEXT == "Н") || (TEXT == "н"))
					{
						(*iter).bHave = false;
					}

					break;
				}
			}

			cout << "Данные имеются ли в наличии изменены!!!" << endl << endl;

			break;

			//Выход из блока switch
		case 0:
			break;
		default:
			cerr << "Ошибка! Попробуйте снова!" << endl;
		}

		//Цикл замены значения
	}
	while(iEditChoose != 0);
}

// Ф-ция просмотра
void displayV(list<ShoesStruct> &shoesList)
{
	if (shoesList.empty())
	{
		cout << "Элементов не обнаружено!!!" << endl;
		return;
	}

	int iBuffer = 0;
	std::string TEXT = "";
	cin.ignore();

	//Ввод инвентарного номера
	//Цикл который выполниться минимум 1 раз
	do
	{
		cout << "Выберите способ отображения записей: " << endl;
		cout << "1. Показать все записи" << endl;
		cout << "2. Вывести обувь определенного артикула(М/Ж/Д, м/ж/д)" << endl;
		cout << "3. Вывести список женской обуви имеющейся в наличии" << endl;
		cout << "0. Выйти из функции просмотра" << endl;

		getline(cin, TEXT);

		try
		{
			//Конверт данных в число
			iBuffer = std::stoi(TEXT);
		}
		catch(...)
		{
			cout << "Неправильный формат инвентарного номера!!! Попробуйте еще!!!" << endl;
			//tmp->position = 0;
			iBuffer = -2;
		}

		if (iBuffer != -2 && iBuffer < 0)
		{
			cout << "Неправильный формат инвентарного номера!!! Попробуйте еще!!!" << endl;
		}
	}
	while(iBuffer < 0);

	//Обработка выбора пользователя
	switch (iBuffer)
	{
		//Просмотр всех записей
	case 1:

		for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
		{
			cout << "Инв. номер: ";
			cout << (*iter).iPosition << endl;
			cout << "Артикул: ";
			cout << (*iter).sArticle<< endl;
			cout << "Наименование: ";
			cout << (*iter).sName << endl;
			cout << "Количество пар: ";;
			cout << (*iter).iCount << endl;
			cout << "Стоимость одной пары: ";
			cout << fixed << setprecision(3) << (*iter).dCost << endl;
			cout << "Имеется ли в наличии: ";
			if((*iter).bHave == true)
			{
				cout << "Да" << endl;
			}
			else
			{
				cout << "Нет" << endl;
			}
			cout << "\n";
		}

		break;

		//Вывод обуви по определенному артикулу
	case 2:

		//Ввод артикула
		//Цикл который выполниться минимум 1 раз
		do
		{
			cout << "Введите желаемый артикул: " << endl;
			getline(cin, TEXT);

			if((TEXT == "М") || (TEXT == "м"))
			{
				iBuffer = 0;
			}
			else if((TEXT == "Ж") || (TEXT == "ж"))
			{
				iBuffer = 0;
			}
			else if((TEXT == "Д") || (TEXT == "д"))
			{
				iBuffer = 0;
			}
			else
			{
				iBuffer = -1;
			}
		}
		while(iBuffer < 0);

		iBuffer = 0;

		//Обработка введенного артикула
		for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
		{
			//Если в структуре имеется нужные нам значения, то сразу печатаем
			if ((*iter).sArticle == TEXT)
			{
				cout << "Инв. номер: ";
				cout << (*iter).iPosition << endl;
				cout << "Артикул: ";
				cout << (*iter).sArticle<< endl;
				cout << "Наименование: ";
				cout << (*iter).sName << endl;
				cout << "Количество пар: ";;
				cout << (*iter).iCount << endl;
				cout << "Стоимость одной пары: ";
				cout << fixed << setprecision(3) << (*iter).dCost << endl;
				cout << "Имеется ли в наличии: ";
				if((*iter).bHave == true)
				{
					cout << "Да" << endl;
				}
				else
				{
					cout << "Нет" << endl;
				}
				cout << "\n";
			}
		}

		break;

		//Вывод женской обуви
	case 3:

		//Обработка введенного артикула
		for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
		{
			//Если в структуре имеется нужные нам значения, то сразу печатаем
			if (((*iter).sArticle == "Ж") || ((*iter).sArticle == "ж"))
			{
				if((*iter).bHave == true)
				{
					cout << "Инв. номер: ";
					cout << (*iter).iPosition << endl;
					cout << "Наименование: ";
					cout << (*iter).sName << endl;
					cout << "Количество пар: ";;
					cout << (*iter).iCount << endl;
					cout << "\n";
				}				
			}
		}

		break;

		//Выход
	case 0:
		break;

	default:
		cerr << "Ошибка! Попробуйте снова!" << endl;
	}
}

// Ф-ция удаления всех элементов
void delAllV(list<ShoesStruct> &shoesList)
{
	//Проверка на пустоту
	if (shoesList.empty())
	{
		cout << "Элементов не обнаружено!!!" << endl;
		return;
	}

	list<ShoesStruct>::iterator iter;

	for (iter = shoesList.begin(); iter != shoesList.end();)
	{
		shoesList.erase(iter++);
	}
}

// Ф-ция удаления одного элемента
void dellOneV(list<ShoesStruct> &shoesList)
{
	//Проверка на пустоту
	if (shoesList.empty())
	{
		cout << "Элементов не обнаружено!!!" << endl;
		return;
	}
	int iInvNomer = 0;

	cout << "Введите инвентарный номер для удаления: ";

	cin >> iInvNomer;

	int iCountDelete = 0;

	//Организовываем цикл по листу структур
	for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end();)
	{
		//Если в структуре имеется нужные нам значения, то сразу печатаем
		if (iter->iPosition == iInvNomer)
		{
			//Удаляем элемент структуры
			iter = shoesList.erase(iter);
			iCountDelete++;
		}
		else
		{
			++iter;
		}
	}

	cout << "Количество удаленных записей: " << iCountDelete << endl;
}

// Чтение из файла
void readFileV()
{
	bool bHave = true;

	//Поток для чтения
	ifstream ifRead(cNameFile);

	if ( !ifRead.is_open() )
	{
		//Создаем файл
		ofstream ofWrite(cNameFile);

		if( !ofWrite.is_open() )
		{
			cout << "Ошибка, нет доступа к файлу!!!" << endl;

			return;
		}

		//Закрываем файл
		ofWrite.close();
		return;
	}

	string sBuffer, sBufferEmpty;
	ShoesStruct *shoesStr = new ShoesStruct;

	//Для проверки на пустоту самого файла
	getline(ifRead, sBufferEmpty);

	//Если буфер не пустой
	if(sBufferEmpty != "")
	{
		//Записываем в структуру
		shoesStr->iPosition = stoi(sBufferEmpty);

		//Читаем пока файл не пустой
		while ( !ifRead.eof() )
		{			
			//Проверка временного буфера, дабы читать все верно, мы его очищаем ниже
			if(sBufferEmpty == "")
			{
				getline(ifRead, sBuffer);

				//Проверка на случай, если вдруг в конце файла будет пустая строка
				if(sBuffer == "")
				{
					//Выходим из цикла, как только нашли пустую строку
					//такое возможно, если вдруг после всех данных будет один
					//или более пробелов
					break;
				}
				else
				{
					shoesStr->iPosition = stoi(sBuffer);
				}
			}

			//Очищаем временный буфер
			sBufferEmpty = "";

			//Считывание артикула из файла
			getline(ifRead, sBuffer);
			shoesStr->sArticle = sBuffer;

			//Считывание наименования абонента из файла
			getline(ifRead, sBuffer);
			shoesStr->sName = sBuffer;

			//Считывание количества пар обуви из файла
			getline(ifRead, sBuffer);
			shoesStr->iCount = stoi(sBuffer);

			//Считывание стоимости одной пары из файла
			getline(ifRead, sBuffer);
			shoesStr->dCost = stod(sBuffer);

			//Считывание имеются ли в наличии из файла
			getline(ifRead, sBuffer);

			if(sBuffer == "Да")
			{
				bHave = true;
			}
			else
			{
				bHave = false;
			}

			shoesStr->bHave = bHave;

			// и добавляем в список
			shoesList.push_back(*shoesStr);
		}
	}

	//Очищаем и закрываем поток	
	ifRead.close();

	//Удаляем указатель
	delete shoesStr;
}

// Запись в файл
void writeFileV()
{
	//Поток записи 
	ofstream ofWrite(cNameFile);

	string sBuffer;
	ShoesStruct *shoesStr = new ShoesStruct;

	//Если лист пустой и файл не открывается
	if (!ofWrite || shoesList.empty())
	{
		return;
	}

	//Записываем данные в файл
	for (list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
	{
		ofWrite << (*iter).iPosition << endl;
		ofWrite << (*iter).sArticle << endl;
		ofWrite << (*iter).sName << endl;
		ofWrite << (*iter).iCount << endl;
		ofWrite << fixed << setprecision(3) << (*iter).dCost << endl;

		if((*iter).bHave == true)
		{
			ofWrite << "Да" << endl;
		}
		else
		{
			ofWrite << "Нет" << endl;
		}
	}

	//Очищаем и закрываем поток	
	ofWrite.close();

	//Удаляем указатель
	delete shoesStr;
}

// Ф-ция поиска
void searchCommandV(list<ShoesStruct> &shoesList)
{
	std::string sName = "";
	cin.ignore();

	cout << "Введите наименование: ";
	getline(cin, sName);	

	int iCount = 0;

	//Организовываем цикл по листу структур
	for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
	{
		//Если в структуре имеется нужные нам значения, то сразу печатаем
		if ((*iter).sName == sName)
		{
			cout << "Инв. номер: ";
			cout << (*iter).iPosition << endl;
			cout << "Артикул: ";
			cout << (*iter).sArticle<< endl;
			cout << "Наименование: ";
			cout << (*iter).sName << endl;
			cout << "Количество пар: ";;
			cout << (*iter).iCount << endl;
			cout << "Стоимость одной пары: ";
			cout << fixed << setprecision(3) << (*iter).dCost << endl;
			cout << "Имеется ли в наличии: ";
			if((*iter).bHave == true)
			{
				cout << "Да" << endl;
			}
			else
			{
				cout << "Нет" << endl;
			}
			cout << "\n";

			//Увеличиваем счетчик количества записей
			iCount++;
		}
	}

	cout << "Найдено записей: " << iCount << endl;
}

// Ф-ция сортировки значений
void sortAbonentV()
{
	int iSortChoose = 0;

	cout << "Выберите вариант сортировки: " << endl;
	cout << "1. Сортировка по наименованию" << endl;
	cout << "2. Сортировка по стоимости обуви" << endl;
	cout << "0. Выйти из функции сортировка" << endl;

	cin >> iSortChoose;

	if(iSortChoose == 1 || iSortChoose == 2)
	{
		//Сортировка по Фамилии
		if(iSortChoose == 1)
		{
			shoesList.sort(SortNameStruct());
		}
		//Сортировка по году установки телефона
		else
		{
			shoesList.sort(SortCostStruct());
		}

		//Вывод отсортированных записей
		for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
		{
			cout << "Инв. номер: ";
			cout << (*iter).iPosition << endl;
			cout << "Артикул: ";
			cout << (*iter).sArticle<< endl;
			cout << "Наименование: ";
			cout << (*iter).sName << endl;
			cout << "Количество пар: ";;
			cout << (*iter).iCount << endl;
			cout << "Стоимость одной пары: ";
			cout << fixed << setprecision(3) << (*iter).dCost << endl;
			cout << "Имеется ли в наличии: ";
			if((*iter).bHave == true)
			{
				cout << "Да" << endl;
			}
			else
			{
				cout << "Нет" << endl;
			}
			cout << "\n";
		}
	}
	else
	{
		//Выход из функции
		system("pause");
		return;
	}
}

// Меню программы
int myMenuI(int admin_status)
{
	int UserChoose;

	system("Cls");

	switch (admin_status)
	{
	case 1:

		//Вызов меню пользователя
		return 1;

		break;
	case 2:

		if (checkPasswordI() != 0)
		{
			//Вызов меню администратора
			return 2;
		}

		break;
	case 0:
		exit(0);
	default:
		cout << "Не верная операция!!! Попробуйте снова!!!" << endl;
		break;
	}
}

// Ф-ция вызоа меню администратора
int adminMenuI()
{
	system("Cls");

	cout << "\nСделайте выбор:\n" << endl;

	cout << "1. Просмотр записей" << endl;
	cout << "2. Добавить запись" << endl;
	cout << "3. Удалить запись" << endl;
	cout << "4. Искать запись" << endl;
	cout << "5. Редактировать запись" << endl;
	cout << "6. Сортировать записи" << endl;
	cout << "7. Записать все данные в файл" << endl;
	cout << "8. Изменить пароль" << endl;
	cout << "9. Возврат в главное меню" << endl;
	cout << "0. Выход" << endl;

	int iAdminChoose;

	cin >> iAdminChoose;

	return iAdminChoose;
}

// Ф-ция вызоа меню пользователя
int userMenuI()
{
	system("Cls");

	cout << "\nСделайте выбор:\n" << endl;

	cout << "1. Просмотр записей" << endl;
	cout << "4. Искать запись" << endl;
	cout << "6. Сортировать записи" << endl;
	cout << "9. Возврат в главное меню" << endl;
	cout << "0. Выход" << endl;	

	int iUserChoose;
	cin >> iUserChoose;

	return iUserChoose;
}

// Изменение пароля
int changePasswordI()
{
	system("Cls");

	std::string oldPass, newPass, fin;

	ifstream ReadFile("password.doc",ios_base::in);	
	//OpenFile.open("password.txt",ios_base::out | ios_base::trunc); 

	if (!ReadFile.is_open())
	{
		cout << "Не могу открыть файл!!! Создаю новый!!!" << endl;

		//Создаем файл и пишем в него стандартный пароль
		ofstream ofs("password.doc");
		ofs << "123";		
		ofs.close();

		return 0;
	}
	else
	{
		ReadFile >> fin; 
	}

	ReadFile.close();

	cout << "Введите старый пароль: " << endl;
	cin >> oldPass;

	if (oldPass != fin)
	{
		cout << "Не верный пароль!!!" << endl;

		return 0;
	}
	else
	{
		cout << "Пароль верный!!!" << endl;

		cout << "Введите новый пароль: " << endl;
		cin >> newPass;

		ofstream WriteFile("password.doc",ios_base::out | ios_base::trunc);

		if (!WriteFile.is_open())
		{
			cout << "Не могу открыть файл!!! Создаю новый!!!" << endl;

			//Создаем файл и пишем в него стандартный пароль
			ofstream ofs("password.doc");
			ofs << "123";		
			ofs.close();

			return 0;
		}
		else
		{
			WriteFile << newPass;
			WriteFile.close();

			cout << "Пароль изменен!!!" << endl;
		}
	}

	return 0;
}

// Проверка пароля
int checkPasswordI()
{
	system("Cls");

	std::string Pass, fin;

	ifstream ReadFile("password.doc",ios_base::in);	

	if (!ReadFile.is_open())
	{
		cout << "Не могу открыть файл!!! Создаю новый!!!" << endl;

		//Создаем файл и пишем в него стандартный пароль
		ofstream ofs("password.doc");
		ofs << "123";		
		ofs.close();

		return 0;
	}
	else
	{
		ReadFile >> fin; 
	}

	cout << "Введите пароль: ";
	cin >> Pass;

	if (Pass != fin)
	{
		cout << "Не верный пароль!!!" << endl;
		system("pause");
		exit(0);
		return 0;
	}
	else
	{
		ReadFile.close();
		return 1;
	}
}

// Ф-ция входа в программу
int main()
{
	//Для Windows 8, для корректного отображения русских букв в консоли
	///нужно установить в консоли шрифт Lucida Console и запомнить для этого проекта
	// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleCP(1251);
	// установка кодовой страницы win-cp 1251 в поток вывода
	SetConsoleOutputCP(1251);

	//Читаем содержимое из файла
	readFileV();

	//Переменные для работы меню
	//Статус админ или нет
	int iAdminStatus = 0;
	//Выбор пользователя
	int iUserChoose = 0;
	//Для теста, показывает состояние открытия файла
	bool openFile;
	std::string password = "";
	//Для удаления
	int iDellUserChoose = 0;
	//Для проверки циклов
	int iCheckSwitch = 0;

	//Открыть файл только для чтения
	ifstream OpenFile("password.doc",ios_base::in);

	if (!OpenFile.is_open())
	{
		cout << "Не могу открыть файл!!! Создаю новый!!!" << endl;

		//Создаем файл и пишем в него стандартный пароль
		ofstream ofs("password.doc");
		ofs << "123";		
		ofs.close();

		cout << "Стандартный пароль установлен, настоятельно рекомендуем сменить пароль!!!" << endl;
		system("pause");

		openFile = false;
	}
	else
	{
		if(OpenFile.eof())
		{
			cout << "Файл с паролем пустой!!!\nУстановка стандартного пароля 123..." << endl;

			//Создаем файл и пишем в него стандартный пароль
			ofstream ofs("password.doc"); 
			ofs << "123";
			ofs.close();

			cout << "Стандартный пароль установлен, настоятельно рекомендуем сменить пароль после входа в программу!!!" << endl;
			system("pause");
			return 0;
		}
		else
		{
			OpenFile >> password;
			openFile = true;
		}

		OpenFile.close();
	}

	//Бесконечный цикл для меню
	while(true)
	{
		system("Cls");

		cout << "Выберите режим:\n1. Пользователь\n2. Администратор\n0. Выход" << endl;

		cin >> iAdminStatus;
		iUserChoose = myMenuI(iAdminStatus);	

		//Если выбран пользователь
		if(iAdminStatus == 1)
		{
			do
			{
				//Переменная соедржащая результат выбора пользователя
				iCheckSwitch = userMenuI();

				//Блок работающий от выбора пользователя
				switch(iCheckSwitch)
				{
				case 1:	

					//Показать все элементы
					displayV(shoesList);

					break;

				case 4:

					//Искать записи
					searchCommandV(shoesList);

					break;

				case 6:

					//Сортировка
					sortAbonentV();

					break;

					//Выход из меню пользователя
				case 9:
					break;

				case 0:
					exit(0);
					break;
				default:
					cerr << "Ошибка! Попробуйте снова!" << endl;	
				}

				system("pause");
			}
			while(iCheckSwitch != 9);
		}
		//Если выбран админ
		else if(iAdminStatus == 2)
		{
			//Делаем до тех пор, пока не будет выбран режим выхода в главное меню
			do
			{
				//Переменная соедржащая результат выбора пользователя
				iCheckSwitch = adminMenuI();

				//Блок работающий от выбора пользователя
				switch(iCheckSwitch)
				{

				case 1:		

					//Показать все элементы
					displayV(shoesList);

					break;

				case 2:

					//Если зашел админ, добавляем запись

					addAbonentV(shoesList);

					break;

				case 3:

					cout << "Выберите режим:\n1. Удалить все\n2. Удалить одну запись\n0. Вернуться" << endl;

					cin >> iDellUserChoose;

					if (iDellUserChoose == 1)
					{
						delAllV(shoesList);
					}
					else if(iDellUserChoose == 2)
					{
						dellOneV(shoesList);
					}
					else if (iDellUserChoose == 0)
					{
						break;
					}
					else
					{
						cout << "Ошибка! Попробуйте снова!" << endl;
					}

					break;

				case 4:

					//Ф-ция поиска по ФИО сотрудника
					searchCommandV(shoesList);

					break;
				case 5:

					//Ф-ция редактирвания существующей записи
					editAbonentV(shoesList);

					break;

				case 6:

					//Сортировка
					sortAbonentV();

					break;

				case 7:

					cout << "Запись в файл..." << endl;

					//Вызываем функцию записи в файл
					writeFileV();

					cout << "Все данные были успешно записаны!!!" << endl;

					break;
				case 8:

					changePasswordI();

					break;

					//Выход из меню пользователя
				case 9:
					break;

				case 0:
					exit(0);
					break;
				default:
					cerr << "Ошибка! Попробуйте снова!" << endl;			
				}

				system("pause");
			}
			while(iCheckSwitch != 9);
		}
		//Выход
		else if(iAdminStatus == 0)
		{
			exit(0);
		}
	}

	//Задержка консоли
	_getch();

	return 0;
}
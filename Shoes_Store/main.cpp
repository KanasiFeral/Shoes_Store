// Shoes_Store.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#define NOMINMAX

#include "stdafx.h"
#include <iostream> //��� �����-������
#include <string> //��� �����
#include <fstream>//��� ������
#include <conio.h> //��� �������� �������
#include <list> //��� ������ � ����������
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <iomanip>

using namespace std;

//��������� ��� ������
struct ShoesStruct
{
	//���������� ����� ������
	int iPosition;
	//������� �����
	std::string sArticle;
	//������������
	std::string sName;
	//����������
	int iCount;
	//��������� ����� ����
	double dCost;
	//���� ������� ������
	bool bHave;
};

//�������� ��� ���������� �� ��������
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

//�������� ��� ���������� �� ��������� �����
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

//���� �������� ��� ������
list<ShoesStruct> shoesList;

//�������� ������
const char* cNameFile = "shoes_list.txt";

// �-��� ���������� ������ �������� � ������
void addShoesV(list<ShoesStruct> &shoesList);
// �-��� �������������� ������
void editShoesV(list<ShoesStruct> &shoesList);
// �-��� ����������� ��������� ������ �� ������
void displayV(list<ShoesStruct> &shoesList);
// �-��� �������� ���� ��������� � ������
void delAllV(list<ShoesStruct> &shoesList);
// �-��� �������� ������ �������� � ������
void dellOneV(list<ShoesStruct> &shoesList);
// �-��� ���������� ������ ���������� �� �����(����� �������� ����������� � ����� ������)
void readFileV();
// �-��� ������ � ����� ��������� ������
void writeFileV();

// �-��� ������ ������
void searchV(list<ShoesStruct> &shoesList);
// �-��� ���������� ������
void sortAbonentV();

// �-��� ������ � ����
int myMenuI(int admin_status);
// �-��� ������ ���� ��������������
int adminMenuI();
// �-��� ������ ���� ������������
int userMenuI();
// �-��� ����� ������
int changePasswordI();
// �-��� �������� ����������� ������
int checkPasswordI();

// �-��� ���������� ����� ���������
void addAbonentV(list<ShoesStruct> &shoesList)
{
	system("Cls");
	std::string TEXT;

	//������� ��������� ����������
	ShoesStruct *shoesStr = new ShoesStruct;

	int i = 0, iBuffer = 0;
	double dBuffer = 0;
	int count;
	cout << "������� ������� ��������?" << endl;
	cin >> count;
	cin.ignore(); 

	for (i = 0; i < count; i++)
	{
		//��������� �
		cout << "������� " << shoesList.size() << endl;

		//���� ������������ ������
		//���� ������� ����������� ������� 1 ���
		do
		{
			cout << "������� ���.�����: ";
			getline(cin, TEXT);

			try
			{
				//������� ������ � �����
				iBuffer = std::stoi(TEXT);
			}
			catch(...)
			{
				cout << "������������ ������ ������������ ������!!! ���������� ���!!!" << endl;
				//tmp->position = 0;
				iBuffer = -2;
			}

			if (iBuffer != -2 && iBuffer < 0)
			{
				cout << "������������ ������ ������������ ������!!! ���������� ���!!!" << endl;
			}
		}
		while(iBuffer < 0);

		shoesStr->iPosition = iBuffer;
		iBuffer = 0;

		//���� ��������
		//���� ������� ����������� ������� 1 ���
		do
		{
			cout << "������� �������: " << endl;
			getline(cin, TEXT);

			if((TEXT == "�") || (TEXT == "�"))
			{
				iBuffer = 0;
			}
			else if((TEXT == "�") || (TEXT == "�"))
			{
				iBuffer = 0;
			}
			else if((TEXT == "�") || (TEXT == "�"))
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

		//���� ������������
		cout << "������� ������������: ";
		getline(cin, TEXT);
		shoesStr->sName = TEXT;

		//���� ���������� ���
		//���� ������� ����������� ������� 1 ���
		do
		{
			cout << "������� ���������� ���: ";
			getline(cin, TEXT);

			try
			{
				//������� ������ � �����
				iBuffer = std::stoi(TEXT);
			}
			catch(...)
			{
				cout << "������������ ������ ���������� ���!!! ���������� ���!!!" << endl;
				//tmp->position = 0;
				iBuffer = -2;
			}

			if (iBuffer != -2 && iBuffer < 0)
			{
				cout << "������������ ������ ���������� ���!!! ���������� ���!!!" << endl;
			}
		}
		while(iBuffer < 0);

		//�������� �� �������
		if(iBuffer != 0)
		{
			//����������, ��� ����� ������� � �������
			shoesStr->bHave = true;
		}
		else
		{
			//����������, ��� ����� �� ������� � �������
			shoesStr->bHave = false;
		}

		shoesStr->iCount = iBuffer;
		iBuffer = 0;

		//���� ��������� ����� ����
		//���� ������� ����������� ������� 1 ���
		do
		{
			cout << "������� ����� � ������, ��������� ����� ���� �����: ";
			getline(cin, TEXT);

			try
			{
				//������� ������ � �����
				dBuffer = std::stod(TEXT);
			}
			catch(...)
			{
				cout << "������������ ������ �����!!! ���������� ���!!!" << endl;
				//tmp->position = 0;
				dBuffer = -2;
			}

			if (dBuffer != -2 && dBuffer < 0)
			{
				cout << "������������ ������ �����!!! ���������� ���!!!" << endl;
			}
		}
		while(dBuffer < 0);

		shoesStr->dCost = dBuffer;
		dBuffer = 0;

		// ��������� � � ������
		shoesList.push_back( *shoesStr );
	}

	// ����������� ������
	delete shoesStr;
}

// �-��� �������������� ������������ ������
void editAbonentV(list<ShoesStruct> &shoesList)
{
	system("Cls");
	std::string TEXT;
	cin.ignore();

	double dBuffer = 0;
	int iInvNomer = 0, iEditChoose = 0, iPosition = 0, iBuffer = 0;	
	bool bInvNomer = false;

	//�������� �� �������
	if (shoesList.empty())
	{
		cout << "��������� �� ����������!!!" << endl;
		return;
	}	

	//���� ������������ ������
	//���� ������� ����������� ������� 1 ���
	do
	{
		cout << "������� ���.�����: ";
		getline(cin, TEXT);

		try
		{
			//������� ������ � �����
			iBuffer = std::stoi(TEXT);
		}
		catch(...)
		{
			cout << "������������ ������ ������������ ������!!! ���������� ���!!!" << endl;
			//tmp->position = 0;
			iBuffer = -2;
		}

		if (iBuffer != -2 && iBuffer < 0)
		{
			cout << "������������ ������ ������������ ������!!! ���������� ���!!!" << endl;
		}
	}
	while(iBuffer < 0);

	iInvNomer = iBuffer;
	iBuffer = 0;

	//�������������� ���� �� ����� ��������
	for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
	{
		//���� � ��������� ������� ������ ��� ��������, �� ����� ��������
		if ((*iter).iPosition == iInvNomer)
		{
			cout << "���. �����: ";
			cout << (*iter).iPosition << endl;
			cout << "�������: ";
			cout << (*iter).sArticle<< endl;
			cout << "������������: ";
			cout << (*iter).sName << endl;
			cout << "���������� ���: ";;
			cout << (*iter).iCount << endl;
			cout << "��������� ����� ����: ";
			cout << fixed << setprecision(3) << (*iter).dCost << endl;
			cout << "������� �� � �������: ";
			if((*iter).bHave == true)
			{
				cout << "��" << endl;
			}
			else
			{
				cout << "���" << endl;
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

	//���� �� ����� ������
	if (bInvNomer == false)
	{
		cout << "������ � ����� ����������� ������� �� ����������!!!" << endl;
		system("pause");
		return;
	}

	//����������� ���� �������������� ��������� ������
	do
	{
		cout << "�������� ���� ��� ��������������: " << endl;
		cout << "1. ������� ������" << endl;
		cout << "2. ������������ ������" << endl;
		cout << "3. ���������� ������" << endl;
		cout << "4. ��������� ������" << endl;
		cout << "5. ������� �� � �������(��/���, �/�, �/�)" << endl;
		cout << "0. ����� �� ������ �������������� ������" << endl;

		cin >> iEditChoose;

		//������� ��������� ����������
		ShoesStruct *shoesStr = new ShoesStruct;

		cin.ignore();

		switch(iEditChoose)
		{

			//�������������� ��������
		case 1:

			cout << "������� ����� �������� ��������: ";
			getline(cin, TEXT);

			//�������������� ���� �� ����� ��������
			for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
			{
				//���� � ��������� ���� ������ � ����� ����������� �����, �� �������� ��� ��������� ����� ���������
				if ((*iter).iPosition == iInvNomer)
				{
					(*iter).sArticle = TEXT;
					break;
				}
			}

			cout << "������ �������� ��������!!!" << endl << endl;

			break;

			//�������������� ������������
		case 2:

			cout << "������� ����� �������� ������������: ";
			getline(cin, TEXT);

			//�������������� ���� �� ����� ��������
			for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
			{
				//���� � ��������� ���� ������ � ����� ����������� �����, �� �������� ��� ��������� ����� ���������
				if ((*iter).iPosition == iInvNomer)
				{
					(*iter).sName = TEXT;
					break;
				}
			}

			cout << "������ ����� ��������!!!" << endl << endl;

			break;

			//�������������� ���������� ���
		case 3:

			//���� ���������� ���
			//���� ������� ����������� ������� 1 ���
			do
			{
				cout << "������� ����� �������� ���������� ���: ";
				getline(cin, TEXT);

				try
				{
					//������� ������ � �����
					iBuffer = std::stoi(TEXT);
				}
				catch(...)
				{
					cout << "������������ ������ ���������� ���!!! ���������� ���!!!" << endl;
					//tmp->position = 0;
					iBuffer = -2;
				}

				if (iBuffer != -2 && iBuffer < 0)
				{
					cout << "������������ ������ ���������� ���!!! ���������� ���!!!" << endl;
				}
			}
			while(iBuffer < 0);

			//�������������� ���� �� ����� ��������
			for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
			{
				//���� � ��������� ���� ������ � ����� ����������� �����, �� �������� ��� ��������� ����� ���������
				if ((*iter).iPosition == iInvNomer)
				{
					(*iter).iCount = iBuffer;
					break;
				}
			}

			iBuffer = 0;

			cout << "������ ���������� ��� ��������!!!" << endl << endl;

			break;

			//�������������� ��������� ����� ����
		case 4:

			//���� ��������� ����� ����
			//���� ������� ����������� ������� 1 ���
			do
			{
				cout << "������� ����� �������� ��������� ����� ����: ";
				getline(cin, TEXT);

				try
				{
					//������� ������ � �����
					dBuffer = std::stoi(TEXT);
				}
				catch(...)
				{
					cout << "������������ ������ ��������� ����� ����!!! ���������� ���!!!" << endl;
					//tmp->position = 0;
					dBuffer = -2;
				}

				if (dBuffer != -2 && dBuffer < 0)
				{
					cout << "������������ ������ ��������� ����� ����!!! ���������� ���!!!" << endl;
				}
			}
			while(dBuffer < 0);

			//�������������� ���� �� ����� ��������
			for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
			{
				//���� � ��������� ���� ������ � ����� ����������� �����, �� �������� ��� ��������� ����� ���������
				if ((*iter).iPosition == iInvNomer)
				{
					(*iter).dCost = dBuffer;
					break;
				}
			}

			dBuffer = 0;

			cout << "������ ��������� ����� ���� ��������!!!" << endl << endl;

			break;

			//�������������� ������� �� � �������
		case 5:

			//���� ������� �� � �������
			//���� ������� ����������� ������� 1 ���
			do
			{
				cout << "������� ����� �������� ������� �� � �������(��/���, �/�, �/�): " << endl;
				getline(cin, TEXT);

				if((TEXT != "��") || (TEXT != "�") || (TEXT != "�"))
				{
					iBuffer = 1;
				}
				else if((TEXT != "���") || (TEXT != "�") || (TEXT != "�"))
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

			//�������������� ���� �� ����� ��������
			for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
			{
				//���� � ��������� ���� ������ � ����� ����������� �����, �� �������� ��� ��������� ����� ���������
				if ((*iter).iPosition == iInvNomer)
				{
					if((TEXT == "��") || (TEXT == "�") || (TEXT == "�"))
					{
						(*iter).bHave = true;
					}
					else if((TEXT == "���") || (TEXT == "�") || (TEXT == "�"))
					{
						(*iter).bHave = false;
					}

					break;
				}
			}

			cout << "������ ������� �� � ������� ��������!!!" << endl << endl;

			break;

			//����� �� ����� switch
		case 0:
			break;
		default:
			cerr << "������! ���������� �����!" << endl;
		}

		//���� ������ ��������
	}
	while(iEditChoose != 0);
}

// �-��� ���������
void displayV(list<ShoesStruct> &shoesList)
{
	if (shoesList.empty())
	{
		cout << "��������� �� ����������!!!" << endl;
		return;
	}

	int iBuffer = 0;
	std::string TEXT = "";
	cin.ignore();

	//���� ������������ ������
	//���� ������� ����������� ������� 1 ���
	do
	{
		cout << "�������� ������ ����������� �������: " << endl;
		cout << "1. �������� ��� ������" << endl;
		cout << "2. ������� ����� ������������� ��������(�/�/�, �/�/�)" << endl;
		cout << "3. ������� ������ ������� ����� ��������� � �������" << endl;
		cout << "0. ����� �� ������� ���������" << endl;

		getline(cin, TEXT);

		try
		{
			//������� ������ � �����
			iBuffer = std::stoi(TEXT);
		}
		catch(...)
		{
			cout << "������������ ������ ������������ ������!!! ���������� ���!!!" << endl;
			//tmp->position = 0;
			iBuffer = -2;
		}

		if (iBuffer != -2 && iBuffer < 0)
		{
			cout << "������������ ������ ������������ ������!!! ���������� ���!!!" << endl;
		}
	}
	while(iBuffer < 0);

	//��������� ������ ������������
	switch (iBuffer)
	{
		//�������� ���� �������
	case 1:

		for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
		{
			cout << "���. �����: ";
			cout << (*iter).iPosition << endl;
			cout << "�������: ";
			cout << (*iter).sArticle<< endl;
			cout << "������������: ";
			cout << (*iter).sName << endl;
			cout << "���������� ���: ";;
			cout << (*iter).iCount << endl;
			cout << "��������� ����� ����: ";
			cout << fixed << setprecision(3) << (*iter).dCost << endl;
			cout << "������� �� � �������: ";
			if((*iter).bHave == true)
			{
				cout << "��" << endl;
			}
			else
			{
				cout << "���" << endl;
			}
			cout << "\n";
		}

		break;

		//����� ����� �� ������������� ��������
	case 2:

		//���� ��������
		//���� ������� ����������� ������� 1 ���
		do
		{
			cout << "������� �������� �������: " << endl;
			getline(cin, TEXT);

			if((TEXT == "�") || (TEXT == "�"))
			{
				iBuffer = 0;
			}
			else if((TEXT == "�") || (TEXT == "�"))
			{
				iBuffer = 0;
			}
			else if((TEXT == "�") || (TEXT == "�"))
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

		//��������� ���������� ��������
		for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
		{
			//���� � ��������� ������� ������ ��� ��������, �� ����� ��������
			if ((*iter).sArticle == TEXT)
			{
				cout << "���. �����: ";
				cout << (*iter).iPosition << endl;
				cout << "�������: ";
				cout << (*iter).sArticle<< endl;
				cout << "������������: ";
				cout << (*iter).sName << endl;
				cout << "���������� ���: ";;
				cout << (*iter).iCount << endl;
				cout << "��������� ����� ����: ";
				cout << fixed << setprecision(3) << (*iter).dCost << endl;
				cout << "������� �� � �������: ";
				if((*iter).bHave == true)
				{
					cout << "��" << endl;
				}
				else
				{
					cout << "���" << endl;
				}
				cout << "\n";
			}
		}

		break;

		//����� ������� �����
	case 3:

		//��������� ���������� ��������
		for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
		{
			//���� � ��������� ������� ������ ��� ��������, �� ����� ��������
			if (((*iter).sArticle == "�") || ((*iter).sArticle == "�"))
			{
				if((*iter).bHave == true)
				{
					cout << "���. �����: ";
					cout << (*iter).iPosition << endl;
					cout << "������������: ";
					cout << (*iter).sName << endl;
					cout << "���������� ���: ";;
					cout << (*iter).iCount << endl;
					cout << "\n";
				}				
			}
		}

		break;

		//�����
	case 0:
		break;

	default:
		cerr << "������! ���������� �����!" << endl;
	}
}

// �-��� �������� ���� ���������
void delAllV(list<ShoesStruct> &shoesList)
{
	//�������� �� �������
	if (shoesList.empty())
	{
		cout << "��������� �� ����������!!!" << endl;
		return;
	}

	list<ShoesStruct>::iterator iter;

	for (iter = shoesList.begin(); iter != shoesList.end();)
	{
		shoesList.erase(iter++);
	}
}

// �-��� �������� ������ ��������
void dellOneV(list<ShoesStruct> &shoesList)
{
	//�������� �� �������
	if (shoesList.empty())
	{
		cout << "��������� �� ����������!!!" << endl;
		return;
	}
	int iInvNomer = 0;

	cout << "������� ����������� ����� ��� ��������: ";

	cin >> iInvNomer;

	int iCountDelete = 0;

	//�������������� ���� �� ����� ��������
	for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end();)
	{
		//���� � ��������� ������� ������ ��� ��������, �� ����� ��������
		if (iter->iPosition == iInvNomer)
		{
			//������� ������� ���������
			iter = shoesList.erase(iter);
			iCountDelete++;
		}
		else
		{
			++iter;
		}
	}

	cout << "���������� ��������� �������: " << iCountDelete << endl;
}

// ������ �� �����
void readFileV()
{
	bool bHave = true;

	//����� ��� ������
	ifstream ifRead(cNameFile);

	if ( !ifRead.is_open() )
	{
		//������� ����
		ofstream ofWrite(cNameFile);

		if( !ofWrite.is_open() )
		{
			cout << "������, ��� ������� � �����!!!" << endl;

			return;
		}

		//��������� ����
		ofWrite.close();
		return;
	}

	string sBuffer, sBufferEmpty;
	ShoesStruct *shoesStr = new ShoesStruct;

	//��� �������� �� ������� ������ �����
	getline(ifRead, sBufferEmpty);

	//���� ����� �� ������
	if(sBufferEmpty != "")
	{
		//���������� � ���������
		shoesStr->iPosition = stoi(sBufferEmpty);

		//������ ���� ���� �� ������
		while ( !ifRead.eof() )
		{			
			//�������� ���������� ������, ���� ������ ��� �����, �� ��� ������� ����
			if(sBufferEmpty == "")
			{
				getline(ifRead, sBuffer);

				//�������� �� ������, ���� ����� � ����� ����� ����� ������ ������
				if(sBuffer == "")
				{
					//������� �� �����, ��� ������ ����� ������ ������
					//����� ��������, ���� ����� ����� ���� ������ ����� ����
					//��� ����� ��������
					break;
				}
				else
				{
					shoesStr->iPosition = stoi(sBuffer);
				}
			}

			//������� ��������� �����
			sBufferEmpty = "";

			//���������� �������� �� �����
			getline(ifRead, sBuffer);
			shoesStr->sArticle = sBuffer;

			//���������� ������������ �������� �� �����
			getline(ifRead, sBuffer);
			shoesStr->sName = sBuffer;

			//���������� ���������� ��� ����� �� �����
			getline(ifRead, sBuffer);
			shoesStr->iCount = stoi(sBuffer);

			//���������� ��������� ����� ���� �� �����
			getline(ifRead, sBuffer);
			shoesStr->dCost = stod(sBuffer);

			//���������� ������� �� � ������� �� �����
			getline(ifRead, sBuffer);

			if(sBuffer == "��")
			{
				bHave = true;
			}
			else
			{
				bHave = false;
			}

			shoesStr->bHave = bHave;

			// � ��������� � ������
			shoesList.push_back(*shoesStr);
		}
	}

	//������� � ��������� �����	
	ifRead.close();

	//������� ���������
	delete shoesStr;
}

// ������ � ����
void writeFileV()
{
	//����� ������ 
	ofstream ofWrite(cNameFile);

	string sBuffer;
	ShoesStruct *shoesStr = new ShoesStruct;

	//���� ���� ������ � ���� �� �����������
	if (!ofWrite || shoesList.empty())
	{
		return;
	}

	//���������� ������ � ����
	for (list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
	{
		ofWrite << (*iter).iPosition << endl;
		ofWrite << (*iter).sArticle << endl;
		ofWrite << (*iter).sName << endl;
		ofWrite << (*iter).iCount << endl;
		ofWrite << fixed << setprecision(3) << (*iter).dCost << endl;

		if((*iter).bHave == true)
		{
			ofWrite << "��" << endl;
		}
		else
		{
			ofWrite << "���" << endl;
		}
	}

	//������� � ��������� �����	
	ofWrite.close();

	//������� ���������
	delete shoesStr;
}

// �-��� ������
void searchCommandV(list<ShoesStruct> &shoesList)
{
	std::string sName = "";
	cin.ignore();

	cout << "������� ������������: ";
	getline(cin, sName);	

	int iCount = 0;

	//�������������� ���� �� ����� ��������
	for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
	{
		//���� � ��������� ������� ������ ��� ��������, �� ����� ��������
		if ((*iter).sName == sName)
		{
			cout << "���. �����: ";
			cout << (*iter).iPosition << endl;
			cout << "�������: ";
			cout << (*iter).sArticle<< endl;
			cout << "������������: ";
			cout << (*iter).sName << endl;
			cout << "���������� ���: ";;
			cout << (*iter).iCount << endl;
			cout << "��������� ����� ����: ";
			cout << fixed << setprecision(3) << (*iter).dCost << endl;
			cout << "������� �� � �������: ";
			if((*iter).bHave == true)
			{
				cout << "��" << endl;
			}
			else
			{
				cout << "���" << endl;
			}
			cout << "\n";

			//����������� ������� ���������� �������
			iCount++;
		}
	}

	cout << "������� �������: " << iCount << endl;
}

// �-��� ���������� ��������
void sortAbonentV()
{
	int iSortChoose = 0;

	cout << "�������� ������� ����������: " << endl;
	cout << "1. ���������� �� ������������" << endl;
	cout << "2. ���������� �� ��������� �����" << endl;
	cout << "0. ����� �� ������� ����������" << endl;

	cin >> iSortChoose;

	if(iSortChoose == 1 || iSortChoose == 2)
	{
		//���������� �� �������
		if(iSortChoose == 1)
		{
			shoesList.sort(SortNameStruct());
		}
		//���������� �� ���� ��������� ��������
		else
		{
			shoesList.sort(SortCostStruct());
		}

		//����� ��������������� �������
		for ( list<ShoesStruct>::iterator iter = shoesList.begin(); iter != shoesList.end(); iter++)
		{
			cout << "���. �����: ";
			cout << (*iter).iPosition << endl;
			cout << "�������: ";
			cout << (*iter).sArticle<< endl;
			cout << "������������: ";
			cout << (*iter).sName << endl;
			cout << "���������� ���: ";;
			cout << (*iter).iCount << endl;
			cout << "��������� ����� ����: ";
			cout << fixed << setprecision(3) << (*iter).dCost << endl;
			cout << "������� �� � �������: ";
			if((*iter).bHave == true)
			{
				cout << "��" << endl;
			}
			else
			{
				cout << "���" << endl;
			}
			cout << "\n";
		}
	}
	else
	{
		//����� �� �������
		system("pause");
		return;
	}
}

// ���� ���������
int myMenuI(int admin_status)
{
	int UserChoose;

	system("Cls");

	switch (admin_status)
	{
	case 1:

		//����� ���� ������������
		return 1;

		break;
	case 2:

		if (checkPasswordI() != 0)
		{
			//����� ���� ��������������
			return 2;
		}

		break;
	case 0:
		exit(0);
	default:
		cout << "�� ������ ��������!!! ���������� �����!!!" << endl;
		break;
	}
}

// �-��� ����� ���� ��������������
int adminMenuI()
{
	system("Cls");

	cout << "\n�������� �����:\n" << endl;

	cout << "1. �������� �������" << endl;
	cout << "2. �������� ������" << endl;
	cout << "3. ������� ������" << endl;
	cout << "4. ������ ������" << endl;
	cout << "5. ������������� ������" << endl;
	cout << "6. ����������� ������" << endl;
	cout << "7. �������� ��� ������ � ����" << endl;
	cout << "8. �������� ������" << endl;
	cout << "9. ������� � ������� ����" << endl;
	cout << "0. �����" << endl;

	int iAdminChoose;

	cin >> iAdminChoose;

	return iAdminChoose;
}

// �-��� ����� ���� ������������
int userMenuI()
{
	system("Cls");

	cout << "\n�������� �����:\n" << endl;

	cout << "1. �������� �������" << endl;
	cout << "4. ������ ������" << endl;
	cout << "6. ����������� ������" << endl;
	cout << "9. ������� � ������� ����" << endl;
	cout << "0. �����" << endl;	

	int iUserChoose;
	cin >> iUserChoose;

	return iUserChoose;
}

// ��������� ������
int changePasswordI()
{
	system("Cls");

	std::string oldPass, newPass, fin;

	ifstream ReadFile("password.doc",ios_base::in);	
	//OpenFile.open("password.txt",ios_base::out | ios_base::trunc); 

	if (!ReadFile.is_open())
	{
		cout << "�� ���� ������� ����!!! ������ �����!!!" << endl;

		//������� ���� � ����� � ���� ����������� ������
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

	cout << "������� ������ ������: " << endl;
	cin >> oldPass;

	if (oldPass != fin)
	{
		cout << "�� ������ ������!!!" << endl;

		return 0;
	}
	else
	{
		cout << "������ ������!!!" << endl;

		cout << "������� ����� ������: " << endl;
		cin >> newPass;

		ofstream WriteFile("password.doc",ios_base::out | ios_base::trunc);

		if (!WriteFile.is_open())
		{
			cout << "�� ���� ������� ����!!! ������ �����!!!" << endl;

			//������� ���� � ����� � ���� ����������� ������
			ofstream ofs("password.doc");
			ofs << "123";		
			ofs.close();

			return 0;
		}
		else
		{
			WriteFile << newPass;
			WriteFile.close();

			cout << "������ �������!!!" << endl;
		}
	}

	return 0;
}

// �������� ������
int checkPasswordI()
{
	system("Cls");

	std::string Pass, fin;

	ifstream ReadFile("password.doc",ios_base::in);	

	if (!ReadFile.is_open())
	{
		cout << "�� ���� ������� ����!!! ������ �����!!!" << endl;

		//������� ���� � ����� � ���� ����������� ������
		ofstream ofs("password.doc");
		ofs << "123";		
		ofs.close();

		return 0;
	}
	else
	{
		ReadFile >> fin; 
	}

	cout << "������� ������: ";
	cin >> Pass;

	if (Pass != fin)
	{
		cout << "�� ������ ������!!!" << endl;
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

// �-��� ����� � ���������
int main()
{
	//��� Windows 8, ��� ����������� ����������� ������� ���� � �������
	///����� ���������� � ������� ����� Lucida Console � ��������� ��� ����� �������
	// ��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleCP(1251);
	// ��������� ������� �������� win-cp 1251 � ����� ������
	SetConsoleOutputCP(1251);

	//������ ���������� �� �����
	readFileV();

	//���������� ��� ������ ����
	//������ ����� ��� ���
	int iAdminStatus = 0;
	//����� ������������
	int iUserChoose = 0;
	//��� �����, ���������� ��������� �������� �����
	bool openFile;
	std::string password = "";
	//��� ��������
	int iDellUserChoose = 0;
	//��� �������� ������
	int iCheckSwitch = 0;

	//������� ���� ������ ��� ������
	ifstream OpenFile("password.doc",ios_base::in);

	if (!OpenFile.is_open())
	{
		cout << "�� ���� ������� ����!!! ������ �����!!!" << endl;

		//������� ���� � ����� � ���� ����������� ������
		ofstream ofs("password.doc");
		ofs << "123";		
		ofs.close();

		cout << "����������� ������ ����������, ������������ ����������� ������� ������!!!" << endl;
		system("pause");

		openFile = false;
	}
	else
	{
		if(OpenFile.eof())
		{
			cout << "���� � ������� ������!!!\n��������� ������������ ������ 123..." << endl;

			//������� ���� � ����� � ���� ����������� ������
			ofstream ofs("password.doc"); 
			ofs << "123";
			ofs.close();

			cout << "����������� ������ ����������, ������������ ����������� ������� ������ ����� ����� � ���������!!!" << endl;
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

	//����������� ���� ��� ����
	while(true)
	{
		system("Cls");

		cout << "�������� �����:\n1. ������������\n2. �������������\n0. �����" << endl;

		cin >> iAdminStatus;
		iUserChoose = myMenuI(iAdminStatus);	

		//���� ������ ������������
		if(iAdminStatus == 1)
		{
			do
			{
				//���������� ���������� ��������� ������ ������������
				iCheckSwitch = userMenuI();

				//���� ���������� �� ������ ������������
				switch(iCheckSwitch)
				{
				case 1:	

					//�������� ��� ��������
					displayV(shoesList);

					break;

				case 4:

					//������ ������
					searchCommandV(shoesList);

					break;

				case 6:

					//����������
					sortAbonentV();

					break;

					//����� �� ���� ������������
				case 9:
					break;

				case 0:
					exit(0);
					break;
				default:
					cerr << "������! ���������� �����!" << endl;	
				}

				system("pause");
			}
			while(iCheckSwitch != 9);
		}
		//���� ������ �����
		else if(iAdminStatus == 2)
		{
			//������ �� ��� ���, ���� �� ����� ������ ����� ������ � ������� ����
			do
			{
				//���������� ���������� ��������� ������ ������������
				iCheckSwitch = adminMenuI();

				//���� ���������� �� ������ ������������
				switch(iCheckSwitch)
				{

				case 1:		

					//�������� ��� ��������
					displayV(shoesList);

					break;

				case 2:

					//���� ����� �����, ��������� ������

					addAbonentV(shoesList);

					break;

				case 3:

					cout << "�������� �����:\n1. ������� ���\n2. ������� ���� ������\n0. ���������" << endl;

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
						cout << "������! ���������� �����!" << endl;
					}

					break;

				case 4:

					//�-��� ������ �� ��� ����������
					searchCommandV(shoesList);

					break;
				case 5:

					//�-��� ������������� ������������ ������
					editAbonentV(shoesList);

					break;

				case 6:

					//����������
					sortAbonentV();

					break;

				case 7:

					cout << "������ � ����..." << endl;

					//�������� ������� ������ � ����
					writeFileV();

					cout << "��� ������ ���� ������� ��������!!!" << endl;

					break;
				case 8:

					changePasswordI();

					break;

					//����� �� ���� ������������
				case 9:
					break;

				case 0:
					exit(0);
					break;
				default:
					cerr << "������! ���������� �����!" << endl;			
				}

				system("pause");
			}
			while(iCheckSwitch != 9);
		}
		//�����
		else if(iAdminStatus == 0)
		{
			exit(0);
		}
	}

	//�������� �������
	_getch();

	return 0;
}
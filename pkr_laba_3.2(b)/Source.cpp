#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

enum Specialty { КН, ІТ, ПЗ, ВП, СА };
string strSpecialty[] = { "КН","ІТ","ПЗ","ВП","СА" };
struct Student
{
	string prizv;
	Specialty specialty;
	short unsigned kurs;
	short unsigned physic;
	short unsigned math;
	union
	{
		short unsigned programing;
		short unsigned metods;
		short unsigned pedagogika;
	};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Specialty posada, short unsigned kurs);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть кількість студентів:  "; cin >> N;

	Student* p = new Student[N];
	int ispecialty;
	Specialty specialty;
	string prizv;
	int found;
	int menuItem;
	short unsigned kurs{};
	do {
		cout << endl << endl << endl;
		cout << "Меню:" << endl << endl;
		cout << " [1] - Створення студентів" << endl;
		cout << " [2] - Відображення студентів" << endl;
		cout << " [3] - Фізичне впорядкування за алфавітом " << endl;
		cout << " [4] - Чи навчається студент з вказаним прізвищем" << endl;
		cout << " [5] - Індексне порядкування "
			<< endl << endl;
		cout << " [0] - Меню закінчує свою роботу" << endl << endl;
		cout << "Введіть пункт меню: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
			cout << "Введіть ключі пошуку:" << endl;

			cin.get();
			cin.sync();

			cout << " Прізвище: "; getline(cin, prizv);
			cout << " спеціальність (0 - КН, 1 - ІТ, 2 - ПЗ, 3 - ВП, 4 - СА): ";
			cin >> ispecialty;
			specialty = (Specialty)ispecialty;

			cout << " Курс: "; cin >> kurs;
			cout << endl;
			if ((found = BinSearch(p, N, prizv, specialty, kurs)) != -1)
				cout << "Такий студент навчається" << found + 1 << endl;
			else
				cout << "Такого студента не знайдено " << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели неправильне число! "
				"Введіть число вибраного елемента в меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int  specialty{};
	for (int i = 0; i < N; i++)
	{
		cout << "Студент№ " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();
		cout << "Прізвище: "; getline(cin, p[i].prizv);
		cout << "Курс: "; cin >> p[i].kurs;
		cout << "спеціальність (0 - КН, 1 - ІТ, 2 - ПЗ, 3 - ВП, 4 - СА):  "; cin >> specialty;
		p[i].specialty = (Specialty)specialty;
		cout << "  оцінка з фізики: "; cin >> p[i].physic;
		cout << "  оцінка з математики: "; cin >> p[i].math;

		switch (p[i].specialty)
		{
		case КН:
			cout << "оцінка з програмування "; cin >> p[i].programing;
			break;
		case ІТ:
			cout << "оцінка з педагогіки "; cin >> p[i].pedagogika;
			break;
		case ПЗ:
			cout << "оцінка з педагогіки "; cin >> p[i].pedagogika;
			break;
		case ВП:
			cout << "оцінка з чисельних методів "; cin >> p[i].metods;
			break;
		case СА:
			cout << "оцінка з педагогіки "; cin >> p[i].pedagogika;
			break;
		}
	}
}
void Print(Student* p, const int N)
{
	cout << "========================================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування| Чисельні методи|Педагогіка|"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------";
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(3) << right << p[i].kurs << " "
			<< "| " << setw(8) << right << strSpecialty[p[i].specialty] << "    "
			<< "| " << setw(4) << right << p[i].physic << "  "
			<< "| " << setw(6) << right << p[i].math << "  ";
		switch (p[i].specialty)
		{
		case 0:
			cout << "| " << setw(7) << right << p[i].programing << "     |" << setw(18) << "|" << setw(13) << "|" << endl;
			break;
		case 3:
			cout << "| " << setw(15) << "|" << setw(10) << right << p[i].metods << "    |" << setw(13) << "|" << endl;
			break;
		case 1:
		case 2:
		case 4:
			cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << p[i].pedagogika << "    |" << endl;
			break;
		}
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	}
	cout << "==================================================================================================================" << endl;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++)
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].kurs > p[i1 + 1].kurs)
				||
				(p[i1].kurs == p[i1 + 1].kurs &&
					p[i1].prizv > p[i1 + 1].prizv)
				|| (p[i1].kurs == p[i1 + 1].kurs &&
					p[i1].prizv == p[i1 + 1].prizv &&
					p[i1].specialty > p[i1 + 1].specialty))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int BinSearch(Student* p, const int N, const string prizv, const Specialty specialty, short unsigned kurs)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].specialty == specialty && p[m].kurs == kurs)
			return m;
		if ((p[m].prizv < prizv)
			||
			(p[m].prizv == prizv &&
				p[m].kurs < kurs)
			||
			(p[m].prizv == prizv &&
				p[m].kurs == kurs &&
				p[m].specialty < specialty))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int* IndexSort(Student* p, const int N)
{
	int* I = new int[N];
	for (int i = 0; i < N; i++)
		I[i] = i;
	int i, j, value;
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].kurs > p[value].kurs) 
				||
				(p[I[j]].kurs == p[value].kurs &&
					p[I[j]].prizv > p[value].prizv) 
				||
				(p[I[j]].kurs == p[value].kurs &&
					p[I[j]].prizv == p[value].prizv &&
					p[I[j]].specialty > p[value].specialty));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "========================================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування| Чисельні методи| Педагогіка|"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------";
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << p[I[i]].prizv
			<< "| " << setw(3) << right << p[I[i]].kurs << " "
			<< "| " << setw(8) << right << strSpecialty[p[I[i]].specialty] << "    "
			<< "| " << setw(4) << right << p[I[i]].physic << "  "
			<< "| " << setw(6) << right << p[I[i]].math << "  ";
		switch (p[i].specialty)
		{
		case 0:
			cout << "| " << setw(7) << right << p[I[i]].programing << "     |" << setw(18) << "|" << setw(13) << "|" << endl;
			break;
		case 3:
			cout << "| " << setw(15) << "|" << setw(10) << right << p[I[i]].metods << "    |" << setw(13) << "|" << endl;
			break;
		case 1:
		case 2:
		case 4:
			cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << p[I[i]].pedagogika << "    |" << endl;
			break;
		}
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	}
	cout << "==================================================================================================================" << endl;
}
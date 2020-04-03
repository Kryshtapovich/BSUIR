#include <iostream>
#include <string>

using namespace std;

class Worker
{
private:
	string lastName;
	string firstName;
	string middleName;
	int department = 0;
	string position;
	int experience = 0;
public:
	Worker* change_worker(Worker* list, int amount)
	{
		int num;
		cout << "Enter worker number in list: ";
		cin >> num;
		SetData(list, num - 1);
		system("cls");
		return list;
	}
	
	void GetData(Worker* list, int amount)
	{
		cout << "№  " << "Lastname\t\t" << "Firstname\t\t" << "Middlename\t" << "Department\t" << "Position\t\t" << "Experience" << endl;
		for (int i = 0; i < amount; i++)
		{
			cout << i + 1 << "  " << list[i].lastName << "\t\t" << list[i].firstName << "\t\t" << list[i].middleName << '\t' << list[i].department << "\t\t" << list[i].position << "\t\t" << list[i].experience << endl;
		}
		cout << endl << endl;
	}
	
	Worker* list_of_workers(int& amount)
	{
		int yes_or_not = 1;
		Worker* list = 0;
		while (yes_or_not == 1)
		{
			list = add_new(list, amount);
			SetData(list, amount);
			system("cls");
			amount++;
			cout << "Continue (1 - yes, 0 - no): ";
			cin >> yes_or_not;
			system("cls");
		}
		return list;
	}
	
	Worker* add_new(Worker* list, int amount)
	{
		if (amount == 0)
		{
			list = new Worker[amount + 1];
			return list;
		}
		else
		{
			Worker* templist = new Worker[amount + 1];
			for (int i = 0; i < amount; i++)
			{
				templist[i] = list[i];
			}
			delete[]list;
			return templist;
		}
	}

	Worker* add_new_worker(Worker* list, int& amount)
	{
		list = add_new(list, amount);
		SetData(list, amount);
		amount++;
		system("cls");
		return list;
	}
	
	void show_worker(Worker* list, int amount)
	{
		string charact, text;
		int num;
		cout << "Enter data(Lastname, FirstName, Middlename, Department, Position, Experience): ";
		cin.get();
		getline(cin, charact);
		if (charact == "Lastname" || charact == "FirstName" || charact == "Middlename" || charact == "Position")
		{
			cout << "Введите значение: ";
			getline(cin, text);
			system("cls");
			cout << "№  " << "Lastname\t\t" << "Firstname\t\t" << "Middlename\t" << "Department\t" << "Position\t\t" << "Experience" << endl;
			for (int i = 0, j = 0; i < amount; i++)
			{
				if (text == list[i].lastName || text == list[i].firstName || text == list[i].middleName || text == list[i].position)
				{
					cout << j + 1 << "  " << list[i].lastName << "\t\t" << list[i].firstName << "\t\t" << list[i].middleName << '\t' << list[i].department << "\t\t" << list[i].position << "\t\t" << list[i].experience << endl;
					j++;
				}
			}
		}
		else if (charact == "Department" || charact == "Experience")
		{
			cout << "Enter number: ";
			cin >> num;
			system("cls");
			cout << "№  " << "Lastname\t\t" << "Firstname\t\t" << "Middlename\t" << "Department\t" << "Position\t\t" << "Experience" << endl;
			for (int i = 0, j = 0; i < amount; i++)
			{
				if (num == list[i].department || num == list[i].experience)
				{
					cout << j + 1 << "  " << list[i].lastName << "\t\t" << list[i].firstName << "\t\t" << list[i].middleName << '\t' << list[i].department << "\t\t" << list[i].position << "\t\t" << list[i].experience << endl;
					j++;
				}
			}
		}
		cout << endl << endl;
	}

	Worker* SetData(Worker* list, int amount)
	{
		cout << "Lastname: ";
		cin >> list[amount].lastName;
		cout << "FirstName: ";
		cin >> list[amount].firstName;
		cout << "Middlename: ";
		cin >> list[amount].middleName;
		cout << "Department: ";
		cin >> list[amount].department;
		cout << "Position: ";
		cin.get();
		getline(cin, list[amount].position);
		cout << "Experience: ";
		cin >> list[amount].experience;
		return list;
	}

	Worker* delete_worker(Worker* list, int& amount)
	{
		int num;
		Worker* new_list = new Worker[amount - 1];
		cout << "Enter worker number to be deleted: ";
		cin >> num;
		for (int i = 0, j = 0; i < amount; i++)
		{
			if (i == num - 1)
			{
				continue;
			}
			else
			{
				new_list[j] = list[i];
				j++;
			}
		}
		amount--;
		delete[]list;
		system("cls");
		return new_list;
	}

	void ShakerSort(Worker* list, int amount)
	{
		int left = 0, right = amount - 1, flag = 1;
		while ((left < right) && flag > 0)
		{
			flag = 0;
			for (int i = left; i < right; i++)
			{
				if (list[i].experience > list[i + 1].experience)
				{
					Worker temp = list[i];
					list[i] = list[i + 1];
					list[i + 1] = temp;
					flag = 1;
				}
			}
			right--;
			for (int i = right; i > left; i--)
			{
				if (list[i - 1].experience > list[i].experience)
				{
					Worker temp = list[i];
					list[i] = list[i - 1];
					list[i - 1] = temp;
					flag = 1;
				}
			}
			left++;
		}
		GetData(list, amount);
	}

	void main_task(Worker* list, int amount)
	{
		cout << "№  " << "Lastname\t\t" << "Firstname\t\t" << "Middlename\t" << "Department\t" << "Position\t\t" << "Experience" << endl;
		for (int i = 0, j = 0; i < amount; i++)
		{
			if (list[i].experience > 20)
			{
				cout << j + 1 << "  " << list[i].lastName << "\t\t" << list[i].firstName << "\t\t" << list[i].middleName << '\t' << list[i].department << "\t\t" << list[i].position << "\t\t" << list[i].experience << endl;
				j++;
			}
		}
		cout << endl << endl;
	}
};

void menu(int& amount);

int main()
{
	int amount = 0;
	menu(amount);
	return 0;
}

void menu(int& amount)
{
	int n;
	Worker* list = 0;
	list = list->list_of_workers(amount);
	do {
		cout << "1 - Get worker list" << endl;
		cout << "2 - Add workers to list" << endl;
		cout << "3 - Show worker by parameter" << endl;
		cout << "4 - Change worker data" << endl;
		cout << "5 - Delete worker" << endl;
		cout << "6 - Sort workers by experience" << endl;
		cout << "7 - Show workers with experience > 20" << endl;
		cout << "Enter command: ";
		cin >> n;
		system("cls");
		switch (n)
		{
		case 1:
			list->GetData(list, amount);
			break;
		case 2:
			list = list->add_new_worker(list, amount);
			list->GetData(list, amount);
			break;
		case 3:
			list->show_worker(list, amount);
			break;
		case 4:
			list->GetData(list, amount);
			list = list->change_worker(list, amount);
			list->GetData(list, amount);
			break;
		case 5:
			list->GetData(list, amount);
			list = list->delete_worker(list, amount);
			list->GetData(list, amount);
			break;
		case 6:
			list->ShakerSort(list, amount);
			break;
		case 7:
			list->main_task(list, amount);
			break;
		default: break;
		}
	} while (n >= 1 && n <= 7);
	delete[]list;
}
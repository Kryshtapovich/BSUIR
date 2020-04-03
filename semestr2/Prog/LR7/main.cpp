#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int maxlength = 23;

int FileSize(FILE* f)
{
	int count = 0;
	while (!feof(f))
		if (fgetc(f) == '\n') count++;
	return count;
}

struct Person
{
	char login[maxlength];
	char password[maxlength];
	char name[maxlength];
	char* friends = nullptr;
	char city[maxlength];
	char education[maxlength];
	char work[maxlength];
	char hobby[maxlength];
	char* friendslogins = nullptr;
	Person* pNext, * pPrev;
};

struct List
{
	Person* pHead, *pTail;
	int size = 0;
};

void AddToList(List* lst, Person* p)
{
	Person* temp = (Person*)malloc(sizeof(Person));
	if (!temp) exit(1);
	strcpy(temp->login, p->login);
	strcpy(temp->password, p->password);
	strcpy(temp->name, p->name);
	temp->friends = (char*)malloc((strlen(p->friends) + 1) * sizeof(char));
	if (!temp->friends) exit(1);
	strcpy(temp->friends, p->friends);
	strcpy(temp->city, p->city);
	strcpy(temp->education, p->education);
	strcpy(temp->work, p->work);
	strcpy(temp->hobby, p->hobby);
	temp->friendslogins = (char*)malloc((strlen(p->friendslogins) + 1) * sizeof(char));
	if (!temp->friendslogins) exit(1);
	strcpy(temp->friendslogins, p->friendslogins);
	temp->pNext = nullptr;
	temp->pPrev = lst->pTail;
	if (lst->pTail) lst->pTail->pNext = temp;
	lst->pTail = temp;
	if (!lst->pHead) lst->pHead = temp;
}

void DeleteList(List* lst)
{
	Person* temp = lst->pHead;
	Person* pNext = nullptr;
	while (temp) {
		pNext = temp->pNext;
		free(temp);
		temp = pNext;
	}
	free(lst);
}

int Check(int left, int right)
{
	int a;
	while (!scanf("%d", &a) || a < left || a > right)
	{
		rewind(stdin);
		printf("Incorrect input, repeat: ");
	}
	return a;
}

void CheckString(char* f)
{
	rewind(stdin);
	fgets(f, maxlength, stdin);
	if (strlen(f) > 21)
	{
		printf("The word is too long! Try again(8 - 20 characters): ");
		CheckString(f);
	}
}

char* ConCat(const char* p, char* log, const char* exp)
{
	char* temp = (char*)malloc((strlen(p) + strlen(log) + strlen(exp)) * sizeof(char));
	if (!temp) exit(1);
	strcpy(temp, p);
	strcat(temp, log);
	temp[strlen(temp) - 1] = '\0';
	strcat(temp, exp);
	return temp;
}

List* ReadUsers();

Person* LoadFromFile(char*, char*);

void LoadToFile(Person*, const char*);

void SafeLoginPassword(Person* user)
{
	FILE* file = fopen("users\\users.txt", "a");
	if (!file) exit(2);
	fputs(user->login, file);
	fputs(user->password, file);
	fclose(file);
}

void ShowUser(Person*);

Person* FindFriend(List*, Person*);

Person* AddFriend(List*, Person*, Person*);

Person* DeleteFriend(List*, Person*);

char* DeleteSubString(char*, char*);

void SeeFriend(List*, Person*);

void Search(List*, Person*);

Person* SignIn(List*);

Person* Registration(List*);

char* EnterLogin(List*);

char* EnterPassword();

void Menu()
{
	printf("1. Add friend\n");
	printf("2. Delete friend\n");
	printf("3. See friend\n");
	printf("4. Search user\n");
	printf("5. Exit\n");
	printf("Choose the number: ");
}

bool CheckLogin(List* list, char* login)
{
	Person* p = list->pHead;
	for (int i = 0; i < list->size; i++)
	{
		if (!strcmp(login, p->login)) return 0;
		p = p->pNext;
	}
	return 1;
}

int main()
{
	List* list = ReadUsers();
	printf("Sign In or Register(1 - Sign In, 0 - Register): ");
	int choice = Check(0, 1);
	Person* user;
	if (choice) user = SignIn(list);
	else user = Registration(list);
	while (1)
	{
		ShowUser(user);
		Menu();
		choice = Check(1, 5);
		switch (choice)
		{
		case 1:
			user = FindFriend(list, user);
			system("cls");
			break;
		case 2:
			user = DeleteFriend(list, user);
			system("cls");
			break;
		case 3:
			SeeFriend(list, user);
			system("cls");
			break;
		case 4:
			system("cls");
			Search(list, user);
			system("pause");
			system("cls");
			break;
		case 5:
			DeleteList(list);
			return 0;
		}
	}
}

List* ReadUsers()
{
	FILE* file = fopen("users\\users.txt", "r");
	if (!file) exit(2);
	List *list = (List*)malloc(sizeof(List));
	list->size = FileSize(file) / 2;
	list->pHead = list->pTail = nullptr;
	rewind(file);
	char* log = (char*)malloc(maxlength * sizeof(char));
	if (!log) exit(1);
	char* pass = (char*)malloc(maxlength * sizeof(char));
	if (!pass) exit(1);
	for (int i = 0; i < list->size; i++)
	{
		fgets(log, maxlength, file);
		fgets(pass, maxlength, file);
		AddToList(list, LoadFromFile(log, pass));
	}
	free(log); free(pass);
	fclose(file);
	return list;
}

Person* LoadFromFile(char* log, char* pass)
{
	Person* temp = (Person*)malloc(sizeof(Person));
	if (!temp) exit(1);
	strcpy(temp->login, log);
	strcpy(temp->password, pass);
	FILE* file = fopen(ConCat("users\\", temp->login, ".txt"), "r");
	if (!file) exit(2);
	fgets(temp->name, maxlength, file);
	char* buff = (char*)malloc(333 * sizeof(char));
	if (!buff) exit(1);
	fgets(buff, strlen(buff), file);
	temp->friends = (char*)malloc(strlen(buff) * sizeof(char));
	if (!temp->friends) exit(1);
	strcpy(temp->friends, buff);
	free(buff);
	fgets(temp->city, maxlength, file);
	fgets(temp->education, maxlength, file);
	fgets(temp->work, maxlength, file);
	fgets(temp->hobby, maxlength, file);
	buff = (char*)malloc(333 * sizeof(char));
	fgets(buff, strlen(buff), file);
	temp->friendslogins = (char*)malloc(strlen(buff) * sizeof(char));
	if (!temp->friendslogins) exit(1);
	strcpy(temp->friendslogins, buff);
	fclose(file);
	return temp;
}

void LoadToFile(Person* user, const char* mode)
{
	FILE* file = fopen(ConCat("users\\", user->login, ".txt"), mode);
	if (!file) exit(2);
	fputs(user->name, file);
	fputs(user->friends, file);
	fputs(user->city, file);
	fputs(user->education, file);
	fputs(user->work, file);
	fputs(user->hobby, file);
	fputs(user->friendslogins, file);
	fclose(file);
}

void ShowUser(Person* user)
{
	printf("\nName: %s", user->name);
	if (strcmp(user->friends, ""))printf("Friends: %s", user->friends);
	else printf("Friends: \n");
	printf("City: %s", user->city);
	printf("Education: %s", user->education);
	printf("Work: %s", user->work);
	printf("Hobby: %s\n", user->hobby);
}

Person* FindFriend(List* list, Person* user)
{
	char* name = (char*)malloc(maxlength * sizeof(char));
	if (!name) exit(0);
	printf("Enter the name: ");
	rewind(stdin);
	fgets(name, maxlength, stdin);
	int amount = 0;
	Person* temp = list->pHead;
	for (int i = 0; i < list->size; i++)
	{
		char* fname = (char*)malloc(strlen(temp->name) * sizeof(char));
		if (!fname) exit(0);
		char* flogin = (char*)malloc(strlen(temp->login) * sizeof(char));
		if (!flogin) exit(0);
		strcpy(fname, temp->name);
		strcpy(flogin, temp->login);
		fname[strlen(fname) - 1] = '\0';
		flogin[strlen(flogin) - 1] = '\0';
		if (!strcmp(name, temp->name) && !strstr(user->friends, fname) &&
			!strstr(user->friendslogins, flogin) && strcmp(user->name, temp->name) && strcmp(user->login, temp->login))
		{
			amount++;
			ShowUser(temp);
			system("pause");
			return AddFriend(list, user, temp);
		}
		temp = temp->pNext;
	}
	free(temp);
	if (!amount) printf("There're no users with that name!\n");
	return user;
}

Person* AddFriend(List *list, Person* user, Person* guy)
{
	char* f = (char*)malloc(strlen(user->friends) * sizeof(char));
	char* l = (char*)malloc(strlen(user->friendslogins) * sizeof(char));
	if (!f || !l) exit(1);
	if (strlen(user->friends) > 1 && strlen(user->friendslogins) > 1)
	{
		strcpy(f, user->friends);
		f[strlen(f) - 1] = '\0';
		strcat(f, " ");
		strcat(f, guy->name);
		user->friends = (char*)realloc(user->friends, (strlen(f) + 1) * sizeof(char));
		if (!user->friends) exit(1);
		strcpy(user->friends, f);
		strcpy(l, user->friendslogins);
		l[strlen(l) - 1] = '\0';
		strcat(l, " ");
		strcat(l, guy->login);
		user->friendslogins = (char*)realloc(user->friendslogins, (strlen(l) + 1) * sizeof(char));
		if (!user->friendslogins) exit(1);
		strcpy(user->friendslogins, l);
	}
	else
	{
		strcpy(user->friends, guy->name);
		strcpy(user->friendslogins, guy->login);
	}
	LoadToFile(user, "w+b");
	Person* temp = list->pHead;
	for (int i = 0; i < list->size; i++)
	{
		if (!strcmp(user->login, temp->login) && !strcmp(user->password, temp->password))
		{
			temp = user;
			break;
		}
		temp = temp->pNext;
	}
	return user;
}

Person* DeleteFriend(List *list, Person* user)
{
	char* name = (char*)malloc(maxlength * sizeof(char));
	if (!name) exit(1);
	printf("Enter the name: ");
	rewind(stdin);
	fgets(name, maxlength, stdin);
	name[strlen(name) - 1] = '\0';
	if (!strstr(user->friends, name))
	{
		printf("There's no friend with this name!\n");
		free(name);
		printf("Try again?(1 - yes, 0 - no): ");
		int choice = Check(0, 1);
		if (choice) return DeleteFriend(list, user);
		else return user;
	}
	else
	{
		user->friends = DeleteSubString(user->friends, name);
		user->friends[strlen(user->friends) - 1] = '\n';
		Person* p = list->pHead;
		for (int i = 0; i < list->size; i++)
		{
			char* temp = (char*)calloc('0', maxlength * sizeof(char));
			if (!temp) exit(1);
			strcpy(temp, p->login);
			temp[strlen(temp) - 1] = '\0';
			if (strstr(p->name, name) && strstr(user->friendslogins, temp))
			{
				user->friendslogins = DeleteSubString(user->friendslogins, temp);
				user->friendslogins[strlen(user->friendslogins) - 1] = '\n';
				break;
			}
			p = p->pNext;
		}
		LoadToFile(user, "w+b");
		p = list->pHead;
		for (int i = 0; i < list->size; i++)
		{
			if (!strcmp(user->login, p->login) && !strcmp(user->password, p->password))
			{
				p = user;
				return user;
			}
			p = p->pNext;
		}
	}
}

char* DeleteSubString(char* str, char* sub)
{
	char* res = (char*)calloc('0', (strlen(str) - strlen(sub) * sizeof(char)));
	if (!res) exit(1);
	for (int i = 0, j = 0; i < strlen(str); i++)
	{
		if (str[i] == sub[0])
		{
			int count = 1;
			for (int k = i + 1, f = 1; str[k] != ' ' && str[k] != '\n'; k++, f++)
			{
				if (str[k] != sub[f]) break;
				else count++;
			}
			if (count == strlen(sub)) i += count;
			else res[j++] = str[i];
		}
		else res[j++] = str[i];
	}
	return res;
}

void SeeFriend(List *list, Person* user)
{
	char* name = (char*)malloc(maxlength * sizeof(char));
	if (!name) exit(1);
	printf("Enter the name: ");
	rewind(stdin);
	fgets(name, maxlength, stdin);
	name[strlen(name) - 1] = '\0';
	if (strstr(user->friends, name))
	{
		Person* p = list->pHead;
		for (int i = 0; i < list->size; i++)
		{
			char* temp = (char*)malloc(strlen(p->login) * sizeof(char));
			if (!temp) exit(1);
			strcpy(temp, p->login);
			temp[strlen(temp) - 1] = '\0';
			if (strstr(p->name, name) && strstr(user->friendslogins, temp))
			{
				ShowUser(p);
				printf("See friend?(1 - yes, 0 -no): ");
				int choice = Check(0, 1);
				if (choice) return SeeFriend(list, p);
				else return;
			}
			p = p->pNext;
		}
		free(p);
	}
	else
	{
		free(name);
		printf("There's no friend with this name!");
		printf("Try again?(1 - yes, 0 -no): ");
		int choice = Check(0, 1);
		if (choice) SeeFriend(list, user);
		else return;
	}
}

void Search(List *list, Person* user)
{
	printf("Search\n");
	printf("1. By City\n");
	printf("2. By Education\n");
	printf("3. By Work\n");
	printf("4. By Hobby\n");
	printf("Choose the number: ");
	int choice = Check(1, 4), count = 0;
	Person* p = list->pHead;
	char* temp = (char*)malloc(maxlength * sizeof(char));
	if (!temp) exit(1);
	switch (choice)
	{
	case 1:
		printf("Enter the city: ");
		rewind(stdin);
		fgets(temp, maxlength, stdin);
		for (int i = 0; i < list->size; i++)
		{
			if (!strcmp(temp, p->city))
			{
				count++;
				ShowUser(p);
			}
			p = p->pNext;
		}
		if (!count) printf("There're no users with this city!\n");
		break;
	case 2:
		printf("Enter the education: ");
		rewind(stdin);
		fgets(temp, maxlength, stdin);
		for (int i = 0; i < list->size; i++)
		{
			if (!strcmp(temp, p->education))
			{
				count++;
				ShowUser(p);
			}
			p = p->pNext;
		}
		if (!count) printf("There're no users with this education!\n");
		break;
	case 3:
		printf("Enter the work: ");
		rewind(stdin);
		fgets(temp, maxlength, stdin);
		for (int i = 0; i < list->size; i++)
		{
			if (!strcmp(temp, p->work))
			{
				count++;
				ShowUser(p);
			}
		}
		if (!count) printf("There're no users with this work!\n");
		break;
	case 4:
		printf("Enter the hobby: ");
		rewind(stdin);
		fgets(temp, maxlength, stdin);
		for (int i = 0; i < list->size; i++)
		{
			if (!strcmp(temp, p->hobby))
			{
				count++;
				ShowUser(p);
			}
			p = p->pNext;
		}
		if (!count) printf("There're no users with this hobby!\n");
		break;
	}
	free(p);
	free(temp);
}

Person* SignIn(List *list)
{
	rewind(stdin);
	printf("Enter the login: ");
	char* log = (char*)malloc(maxlength * sizeof(char));
	if (!log) exit(1);
	fgets(log, maxlength, stdin);
	printf("Enter the password: ");
	char* pass = (char*)malloc(maxlength * sizeof(char));
	if (!pass) exit(1);
	fgets(pass, maxlength, stdin);
	Person* p = list->pHead;
	for (int i = 0; i < list->size; i++)
	{
		if (!strcmp(log, p->login) && !strcmp(pass, p->password)) return p;
		p = p->pNext;
	}
	free(log); free(pass);
	printf("Wrong login or password! Try agin or rgister?(1 - register, 0 - try again): ");
	int ch = Check(0, 1);
	if (ch == 1) return Registration(list);
	else return SignIn(list);
}

Person* Registration(List* list)
{
	printf("Registration\n");
	char* login = EnterLogin(list);
	char* password = EnterPassword();
	Person* man = (Person*)malloc(sizeof(Person));
	if (!man) exit(1);
	strcpy(man->login, login);
	strcpy(man->password, password);
	free(login); free(password);
	printf("Enter the name: ");
	CheckString(man->name);
	man->friends = (char*)malloc(2 * sizeof(char));
	if (!man->friends) exit(1);
	man->friends[0] = '\n';
	man->friends[1] = '\0';
	printf("Enter the city: ");
	CheckString(man->city);
	printf("Enter the education: ");
	CheckString(man->education);
	printf("Enter the work: ");
	CheckString(man->work);
	printf("Enter the hobby: ");
	CheckString(man->hobby);
	man->friendslogins = (char*)malloc(2 * sizeof(char));
	if (!man->friendslogins) exit(1);
	man->friendslogins[0] = '\n';
	man->friendslogins[1] = '\0';
	LoadToFile(man, "a");
	SafeLoginPassword(man);
	return man;
}

char* EnterLogin(List *list)
{
	char* login = (char*)calloc('0', maxlength * sizeof(char));
	if (!login) exit(1);
	printf("Enter the login(8 - 20 characters): ");
	rewind(stdin);
	fgets(login, maxlength, stdin);
	if (strlen(login) > 21)
	{
		printf("The login is too long!\n");
		free(login);
		EnterLogin(list);
	}
	for (int i = 0; i < maxlength; i++)
	{
		if (i < 8 && login[i] == '\0')
		{
			printf("The login is too short!\n");
			free(login);
			EnterLogin(list);
		}
	}
	if (!CheckLogin(list, login))
	{
		printf("There's a user with that login!\n");
		free(login);
		EnterLogin(list);
	}
	else return login;
}

char* EnterPassword()
{
	char* password = (char*)calloc(maxlength * sizeof(char), '0');
	if (!password) exit(1);
	printf("Enter the password(8 - 20 characters): ");
	rewind(stdin);
	fgets(password, maxlength, stdin);
	if (strlen(password) > 21)
	{
		printf("The password is too long!\n");
		free(password);
		EnterPassword();
	}
	for (int i = 0; i < maxlength; i++)
	{
		if (i < 8 && password[i] == '\0')
		{
			printf("The password is too short!\n");
			free(password);
			EnterPassword();
		}
	}
	return password;
}
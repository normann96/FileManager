#include "stdafx.h"
#include "FindFolder.h"


int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char * pTemp = nullptr;
	char * pNextFolder = new char[260];
	strcat(pNextFolder, "");
	int nSizeCurFolder = 0;
	Info();
	
	
	int nSize = 80;
	char *pFolder = nullptr;

	do 
	{
		switch(ChooseMenu())
		{
		case 1: ShowAllDisk(); break;
		case 2:	pFolder = OpenDisk(&nSizeCurFolder); break;
		case 3:	
			{
				if (pFolder != nullptr)
				{
					ShowFolders(pFolder);
				}
				else
					cout << "Choose a disk!\n"; 
				break;
			}
		case 4:	
			{
				if (pFolder != nullptr && pNextFolder != nullptr)
					pFolder = OpenNextFolder(pFolder, pNextFolder); 
				else
					cout << "Choose a disk!\n"; 
				break;
			}
		case 5: pFolder = OpenPreviousFolder(pFolder); break;
		case 6:	cout << "Find file\n"; break;
		case 7: 
			{
				cout << "You exit!\n";

				if (pFolder != nullptr)
					delete [] pFolder;
				delete [] pNextFolder;

				if (_CrtDumpMemoryLeaks())
					cout << "Memory Leak!\n";
				
				Sleep(1000);
				exit(1); 
				break;
			}
		default: ; break;
		}
	} while (true);

	

	_getch();
	return 0;
}
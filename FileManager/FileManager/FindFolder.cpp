#include "stdafx.h"
#include "FindFolder.h"

void Info()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "\tMENU:\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Enter number from 1 to 8:\n";
	cout << "1. Show all disk in your PC\n";
	cout << "2. Open disk\n";
	cout << "3. Open current folder\n";
	cout << "4. Open next folder\n";
	cout << "5. Open previous folder\n";
	cout << "6. Find file\n";
	cout << "7. Exit\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

int ChooseMenu()
{
	char numberArr[1];
	int a = 5;
	while(true)
	{
		a = _getch();
		if (a > '0' && a < '9')
		{
//			system("CLS");
//			Info();
			numberArr[0] = a;
			cout << char(a);
			cout << '\b';
		}
// 		if (a == 8)
// 		{
// 			numberArr[0] = a;
// 			cout << char(a);
// 			cout << '\b';
// 		}
		if(a == 27 || a == 13)
			break;
	}
	cout << endl;
	return  atoi(numberArr);
}

void ShowAllDisk()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "All local drive on your computer:\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	DWORD dwMask = 1;
	char drive = 'A';
	DWORD dw = GetLogicalDrives();
	for (int i = 0; i < 26; i++)
	{		
		if (dw & dwMask)
			cout << (char)(drive+i) << ":\\ ";
		dwMask <<= 1;
	}
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void GetInputDirectory(char * pBuffer)
{
	SetCurrentDirectory(pBuffer);
	cout << pBuffer;
}

char * OpenPreviousFolder( char * pCurFolder )
{
	int nSizeCurFolder = strlen(pCurFolder);

// íàõîäèì âòîðîé ñëåø ñ êîíöà pCurFolder è èçìåíÿåì ðàçìåð äî âòîðîãî áñëåøà ñ êîíöà

	for (int i = nSizeCurFolder-2; i > 2; i--)
	{
		if (pCurFolder[i] == '\\')
		{
			nSizeCurFolder = i;
			break;
		}
	}
	pCurFolder[nSizeCurFolder+1] = 0;

	GetInputDirectory(pCurFolder);
	strcat(pCurFolder, sAllFile);
	ShowFolders(pCurFolder);
	pCurFolder[strlen(pCurFolder)-3] = 0;
	return pCurFolder;
}

char * OpenDisk( int * nSizeCurFolder )
{
	ShowAllDisk();
	char sDisk[2];		
	char *pDrive = sDisk;
	int nSizeDisk = 0;
	char *pBuffer = new char[100];

	cout << "Enter name drive what you open:\t";
	cin >> sDisk;

	pDrive[1] = 0;
// Èìÿ äèñêà '+' :\\ '+' *.*. Example:  D:\\*.*
	strcpy( pBuffer, pDrive );                
	strcat( pBuffer, sBackSlesh);
	strcat( pBuffer, sAllFile );

	ShowFolders(pBuffer);

	nSizeDisk = strlen(pBuffer)+1;
	*nSizeCurFolder = nSizeDisk - nSizeAllFile+1;
	pBuffer[nSizeDisk-nSizeAllFile] = 0;

	GetInputDirectory(pBuffer);
	cin.ignore(1);
	return pBuffer;
}

char * OpenNextFolder( char * pCurFolder, char * pNextFolder )
{
	int nSizeFolder = 0;
	strcat(pNextFolder, "");
	int nSizeNext = strlen(pNextFolder)+1;
	pNextFolder[nSizeNext] = 0;

	GetInputDirectory(pCurFolder);
	cin.getline(pNextFolder, 100);


	if (strcmp(pNextFolder, "") != 0)
	{
		strcat(pCurFolder, pNextFolder);
		strcat(pCurFolder, "\\*.*");
	}
	else
		strcat(pCurFolder, "*.*");

	ShowFolders(pCurFolder);

	nSizeFolder = strlen(pCurFolder)+1;
	pCurFolder[nSizeFolder - sizeof(char)*nSizeAllFile] = 0;

	GetInputDirectory(pCurFolder);
	return pCurFolder;
}

void ShowFolders( char * pCurFolder )
{
	cout << endl;
// Enter nameFile what do you want find:
#ifdef Test_1
	cout << "Enter nameFile what do you want find:\t";
	cin.getline(pNameFindFile, 100);
#endif
	
//	strcat(pCurFolder, "\*.*");
	int nSizeCurFolder = strlen(pCurFolder);

	WIN32_FIND_DATA wf;								// õðàíèò â ñåáå êó÷ó ïîëåé, ïî êîòîðûì ìû áóäåì ñîáèðàòü èíôîðìàöèþ íàøèõ ôàéëîâ
	HANDLE hFile = FindFirstFile(pCurFolder, &wf);
	if (INVALID_HANDLE_VALUE == hFile)				// íåïðàâèëüíîå çíà÷åíèå îïèñàòåëÿ
	{
		cout << "Error!\n";
		_getch();
		return;
	}

// Ïîèñê ïàïîê â str
	BOOL bOk = TRUE;
	while(bOk)
	{
		if (wf.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			cout << "Folder:  "; 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << wf.cFileName << endl;
#ifdef Test_1
			if (strcmp(wf.cFileName, pNameFindFile) == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				cout << setw(4) << "Congratullation, you finded: \a";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout 	<< pNameFindFile << "\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
#endif // Test_1
		}

		bOk = FindNextFile(hFile, &wf);
	}

// Ïîèñê ôàéëîâ â str
	hFile = FindFirstFile(pCurFolder, &wf);
	bOk = TRUE;
	while(bOk)
	{
		if (!(wf.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << "File:    "; 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout	<< wf.cFileName << endl;
#ifdef Test_2
			if (strcmp(wf.cFileName, pNameFindFile) == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				cout << setw(4) << "Congratullation, you finded: \a";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout 	<< pNameFindFile << "\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
#endif // Test_2
		}
		bOk = FindNextFile(hFile, &wf);
	}
	FindClose(hFile);
//	pCurFolder[nSizeCurFolder-4] = 0;
}

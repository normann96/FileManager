#include "stdafx.h"

void ShowAllDisk();
void Info();
int ChooseMenu();
void GetInputDirectory(char * pBuffer);
void ShowFolders(char * pCurFolder);
char * OpenDisk(int * nSizeBuff);
char * OpenNextFolder(char * pCurFolder, char * pNextFolder);
char * OpenPreviousFolder(char * pCurFolder);

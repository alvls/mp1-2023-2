#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <windows.h>
#include <locale.h>
#include "sortings.h"

struct FileInfo {
	char name[256];
	unsigned long long size;
};

int fileQuantity(char* dirPath) {
	int size = 0;
	WIN32_FIND_DATAA findFileData;
	HANDLE hfind = FindFirstFileA(dirPath, &findFileData);
	if (hfind == INVALID_HANDLE_VALUE) {
		printf("An error occurred while trying to open the directory. Please, try entering different directory.\n");
		return -1;
	}
	while (FindNextFileA(hfind, &findFileData) != 0) 
		if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0 && findFileData.nFileSizeLow != 0)
			size++;
	FindClose(hfind);
	return size;
}

int checkPath(char* dirPath) {
	if (strlen(dirPath) == 0 || dirPath == '\n') {// An empty path is entered
		printf("The path cannot be empty!\n");
		return 0;
	}
	if (strlen(dirPath) == 2 && 'A' <= dirPath[0] <= 'z' && dirPath[1] == ':') { // Disk name is entered
		return 1;
	}
	if (((dirPath[0] < 'A' || dirPath[0] > 'Z') && (dirPath[0] < 'a' || dirPath[0] > 'z')) || (dirPath[1] != ':') || (dirPath[2] != '\\')) {
		printf("Please enter the path including disk name.\n");
		return 0;
	}
	if (strstr(dirPath, "\\\\") != NULL) {
		printf("Please consider replacing all \"\\\\\" with \"\\\".\n");
		return 0;
	}
	char specs[3] = "/?*";
	for (int i = 0; i < 3; i++) {
		if (strchr(dirPath, specs[i]) != NULL) {
			printf("Please check the path for special characters. (The path cannot include %c)\n", specs[i]);
			return 0;
		} 
	}
	return 1;
}

void formPrev(char* dirPath, char* prev) { // Formation of prev
	for (int i = 0; i < 256; i++) {
		prev[i] = dirPath[i];
	}
}

void getPath(char* dirPath) {
	char prev[256];
	do {
		formPrev(dirPath, prev);
		printf("Enter the directory path in \"diskName:\\folder1\\folder2...\" format: ");
		scanf("%255[^\n]", dirPath);
		getchar();
		if (strcmp(dirPath, prev) == 0) dirPath[0] = '\0';
	} while (!checkPath(dirPath));
}

void getFiles(char* dirPath, struct FileInfo* files) {
	WIN32_FIND_DATAA findFileData;
	HANDLE hfind = FindFirstFileA(dirPath, &findFileData);
	int i = 0;
	do {
		if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0 && (findFileData.nFileSizeHigh * (MAXDWORD + 1) + findFileData.nFileSizeLow) != 0) {
			strcpy(files[i].name, findFileData.cFileName);
			files[i].size = (findFileData.nFileSizeHigh * (MAXDWORD + 1) + findFileData.nFileSizeLow);
			i++;
		}
	} while (FindNextFileA(hfind, &findFileData) != 0);
	FindClose(hfind);
}

int main() { // Doesn't work with files named in non-english
	setlocale(LC_ALL, "rus");
	char dirPath[256];
	int size = -1;
	printf("Example of correct directory path: D:\\Documents\\project\n");

	while (size == -1 || size == 0) { // Getting the directory path
		getPath(dirPath);
		printf("%s\n", dirPath);
		strcat(dirPath, "\\*");
		size = fileQuantity(dirPath);
		if (size == 0) {
			printf("The directory is empty. Please, try entering different directory.\n");
		}
	}

	struct FileInfo* files = malloc(size * sizeof(struct FileInfo));
	getFiles(dirPath, files);
	sort(files, size, 4, 0); // files, size, type, ascend
	for (int i = 0; i < size; i++) {
		printf("File name: %s, file size: %llu\n", files[i].name, files[i].size);
	}

	printf("%d\n", size);
	if(files != NULL) free(files);
	system("pause");
	return 0;
}

// нужно ли сортировать папки? (про
// норм, что не работает с файлами, у которых название на русском?
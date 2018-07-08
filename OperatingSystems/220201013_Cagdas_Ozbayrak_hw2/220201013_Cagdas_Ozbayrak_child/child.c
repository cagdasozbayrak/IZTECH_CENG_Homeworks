#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

HANDLE bufferFile; //Shared memory file handle for buffer
HANDLE itemCountFile; //Shared memory file handle for item count
int* buffer; //Shared memory space
int* itemCount; //Holds count of the items in the buffer

void produce(int i, int bufferSize);
void consume(int i, int bufferSize);
void swap(int i, int bufferSize);

int insertItem(int item, int index, int bufferSize); //Returns 1 if function successfully inserts the item to buffer else returns 0
int removeItem(int index); //Returns 1 if function successfully removes the item on the index from the buffer else returns 0
int swapItem(int i1, int i2); //Returns 1 if function successfully swaps the indexes in the buffer else returns 0

void ordinalNumber(int n, char suffix[3]); //Generates appropriate suffix for integer n and stores it in array suffix

HANDLE Mutex; //In order to prevent race conditions

int main(int argc, char** argv)
{
	if (argc < 3) {
		printf("Invalid number of arguments.\n");
		return EXIT_FAILURE;
	}

	char operation[20]; //holds the information about the operation to perform
	for (int i = 0; (operation[i] = getchar()) != 0; i++); //Gets the operation from the main process through the pipe
	int processNo = atoi(argv[2]); //Process no
	int bufferSize = atoi(argv[1]) / sizeof(int); //Buffer size

	srand(time(NULL)*GetCurrentProcessId()); //Seed for rand() function. I multiplied with process id in order to get different random numbers
											 //for each process that runs at the same time.

	//Opening shared memory - buffer
	bufferFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, "Global\Buffer");
	if (bufferFile == NULL) {
		printf("Couldn't create file mapping.\n");
		return EXIT_FAILURE;
	}

	buffer = MapViewOfFile(bufferFile, FILE_MAP_ALL_ACCESS, 0, 0, bufferSize*sizeof(int));
	if (buffer == NULL) {
		printf("Couldn't create buffer.\n");
		return EXIT_FAILURE;
	}

	//Opening shared memory to share the information between processes about how many items currently exist in the buffer 
	itemCountFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, "Global\itemCount");
	if (itemCountFile == NULL) {
		printf("Couldn't create file mapping.\n");
		return EXIT_FAILURE;
	}

	itemCount = MapViewOfFile(itemCountFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
	if (itemCount == NULL) {
		printf("Couldn't create buffer.\n");
		return EXIT_FAILURE;
	}

	Mutex = CreateMutex(NULL, FALSE, NULL);

	//Child process starts the operation given by the main process
	if (strcmp(operation, "producer") == 0) produce(processNo, bufferSize);
	else if (strcmp(operation, "consumer") == 0) consume(processNo, bufferSize);
	else if (strcmp(operation, "swapper") == 0) swap(processNo, bufferSize);
	else {
		printf("Unknown task. Child %d exiting...\n", processNo+1);
		return EXIT_FAILURE;
	}

	UnmapViewOfFile(buffer);
	UnmapViewOfFile(itemCount);
	CloseHandle(bufferFile);
	CloseHandle(itemCountFile);
	CloseHandle(Mutex);
	system("pause");
	return EXIT_SUCCESS;
}

int insertItem(int item, int index, int bufferSize) {
	WaitForSingleObject(Mutex, INFINITE);
	if (*itemCount < bufferSize && buffer[index] == 0) { //If buffer is not full and there is nothing in the index
		buffer[index] = item;
		(*itemCount)++;
		ReleaseMutex(Mutex);
		return 1;
	}
	ReleaseMutex(Mutex);
	return 0;
}

void produce(int i, int bufferSize) {
	int randNum;
	int randIndex;
	char suffix[3];
	while (1) {
		randNum = rand() + 1;
		randIndex = (rand()*rand()) % bufferSize; //Since the seed can't change fast enough I tried to get kind of an independent value for index
		if (insertItem(randNum, randIndex, bufferSize)) {
			ordinalNumber(randIndex + 1, suffix);
			printf("Child %3d produced %d as %d%s entry in the buffer!\n", i + 1, randNum, randIndex + 1, suffix);
		}
		Sleep(1500);
	}
}

int removeItem(int index) {
	WaitForSingleObject(Mutex, INFINITE);
	if (*itemCount > 0 && buffer[index] != 0) { //If buffer isn't empty and there is an item in the index
		buffer[index] = 0;
		(*itemCount)--;
		ReleaseMutex(Mutex);
		return 1;
	}
	ReleaseMutex(Mutex);
	return 0;
}

void consume(int i, int bufferSize) {
	int temp;
	int randIndex;
	char suffix[3];
	while (1) {
		randIndex = rand() % bufferSize;
		temp = buffer[randIndex];
		if (removeItem(randIndex, bufferSize)) {
			ordinalNumber(randIndex + 1, suffix);
			printf("Child %3d consumed %d from %d%s entry from the buffer!\n", i + 1, temp, randIndex + 1, suffix);
		}
		Sleep(1500);
	}
}

int swapItem(int i1, int i2) {
	WaitForSingleObject(Mutex, INFINITE);
	if (*itemCount > 0 && (buffer[i1] != 0 || buffer[i2] != 0) && (i1 != i2)) { //If buffer and the index isn't empty and indexes are different
		int temp = buffer[i1];
		buffer[i1] = buffer[i2];
		buffer[i2] = temp;
		ReleaseMutex(Mutex);
		return 1;
	}
	ReleaseMutex(Mutex);
	return 0;
}

void swap(int i, int bufferSize) {
	int i1, i2;
	char suffix1[3], suffix2[3];
	while (1) {
		i1 = rand() % bufferSize;
		i2 = (rand()*rand()) % bufferSize;
		if (swapItem(i1, i2)) {
			ordinalNumber(i1 + 1, suffix1);
			ordinalNumber(i2 + 1, suffix2);
			printf("Child %3d swapped %d%s index with %d%s index!\n", i + 1, i1 + 1, suffix1, i2 + 1, suffix2);
		}
		Sleep(1500);
	}
}

void ordinalNumber(int n, char suffix[3]) {
	if (n % 100 >= 11 && n % 100 <= 13)
		strcpy_s(suffix, 3, "th");
	else if (n % 10 == 1)
		strcpy_s(suffix, 3, "st");
	else if (n % 10 == 2)
		strcpy_s(suffix, 3, "nd");
	else if (n % 10 == 3)
		strcpy_s(suffix, 3, "rd");
	else
		strcpy_s(suffix, 3, "th");
}
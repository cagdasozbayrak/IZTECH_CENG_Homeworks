#include <stdio.h>
#include <windows.h>

#define PROCESS_COUNT 25

int main(int argc, char* argv[])
{
	srand(time(NULL)); //Seed for the rand() function
	STARTUPINFO si[PROCESS_COUNT];
	PROCESS_INFORMATION pi[PROCESS_COUNT];
	SECURITY_ATTRIBUTES sa[PROCESS_COUNT];
	HANDLE hProcess[PROCESS_COUNT];
	HANDLE writePipe[PROCESS_COUNT], readPipe[PROCESS_COUNT];
	char* operation[3] = { "producer", "consumer", "swapper" };
	int bytesToWrite = 0;
	int bytesWritten = 0;
	int opSelect = 0;

	//Allocating shared memory for buffer
	HANDLE bufferFile;
	bufferFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, PROCESS_COUNT*sizeof(int), "Global\Buffer"); //Buffer size is process_count*int
	if (bufferFile == NULL) {
		printf("Couldn't create file mapping for buffer.\n");
		return EXIT_FAILURE;
	}

	//Allocating shared memory for item count
	HANDLE itemCountFile;
	itemCountFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int), "Global\itemCount");
	if (itemCountFile == NULL) {
		printf("Couldn't create file mapping for item count.\n");
		return EXIT_FAILURE;
	}

	//Creating security attributes for all child processes
	for (int i = 0; i < PROCESS_COUNT; i++) {
		SecureZeroMemory(&sa[i], sizeof(SECURITY_ATTRIBUTES));
		sa[i].bInheritHandle = TRUE;
		sa[i].lpSecurityDescriptor = NULL;
		sa[i].nLength = sizeof(SECURITY_ATTRIBUTES);
	}

	//Creating the pipes
	for (int i = 0; i < PROCESS_COUNT; i++) {
		if (!CreatePipe(&readPipe[i], &writePipe[i], &sa[i], 0)) {
			printf("Unable to create pipe.\n");
			system("pause");
			return EXIT_FAILURE;
		}
	}

	//Creating variables for child processes
	for (int i = 0; i < PROCESS_COUNT; i++) {
		SecureZeroMemory(&si[i], sizeof(STARTUPINFO));
		SecureZeroMemory(&pi[i], sizeof(PROCESS_INFORMATION));
		si[i].cb = sizeof(STARTUPINFO);
		si[i].hStdInput = readPipe[i];
		si[i].hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		si[i].hStdError = GetStdHandle(STD_ERROR_HANDLE);
		si[i].dwFlags = STARTF_USESTDHANDLES;
	}

	//Creating child processes
	for (int i = 0; i < PROCESS_COUNT; i++) {
		char commandLine[60];
		sprintf_s(commandLine, 60, "220201013_Cagdas_Ozbayrak_child.exe %d %d", PROCESS_COUNT*sizeof(int), i); //Used sprintf to generate the string
																											   //to send information about buffer size and
																											   //process no to the child process
		if (!CreateProcess(NULL, commandLine, NULL, NULL, TRUE, NULL, NULL, NULL, &si[i], &pi[i])) {
			system("pause");
			return EXIT_FAILURE;
		}
		hProcess[i] = pi[i].hProcess;
	}

	//Sending operations to perform to the child processes through pipes
	for (int i = 0; i < PROCESS_COUNT; i++) {
		if (i < 3) //To make sure there is at least one of each type of child process
			opSelect = i;
		else //After we assigned at least one of each operations to child processes, we randomly assign tasks the rest of the processes
			opSelect = rand() % 3;

		bytesToWrite = strlen(operation[opSelect]);
		bytesToWrite++;

		//Writing the selected operation to the pipe
		if (!WriteFile(writePipe[i], operation[opSelect], bytesToWrite, &bytesWritten, NULL)) {
			printf("Unable to write to pipe.\n");
			system("pause");
			return EXIT_FAILURE;
		}
	}

	WaitForMultipleObjects(PROCESS_COUNT, hProcess, TRUE, INFINITE);

	for (int i = 0; i < PROCESS_COUNT; i++) {
		CloseHandle(readPipe[i]);
		CloseHandle(writePipe[i]);
		CloseHandle(pi[i].hThread);
		CloseHandle(pi[i].hProcess);
	}

	free(si);
	free(pi);
	free(sa);
	CloseHandle(bufferFile);
	CloseHandle(itemCountFile);

	system("pause");
	return EXIT_SUCCESS;
}
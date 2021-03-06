#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define THREAD_COUNT 16

FILE *fpFill; //file pointer used for filling the file with random letters
FILE *fpSearch; //file pointer used for searching substrings in the file
int nChar = 0; //Counts the number of characters generated and written on the file

void* createFile(void* arg); //creates and opens file for generate and search operations
void* generateRandomLetter(void* arg); //generates random letter and writes it in the file
void* searchSubstring(void* arg); //Searches and counts the substrings in the file
void toLowerCase(char* str); //Changes all of the letters in a string to lower case

//Counter for each substring
int x = 0;
int os = 0;
int cpu = 0;
int disk = 0;
int cache = 0;


int main(){
	clock_t begin = clock();
	int i;
	pthread_t *threads;
	pthread_attr_t *attr;
	char *temp;
	if((threads = (pthread_t *) malloc(THREAD_COUNT * sizeof(pthread_t))) == NULL){ //We allocate space for threads in the memory,
		perror("Error allocating memory.");											//if an error occurs in the process it should be null
		return EXIT_FAILURE;
	}

	if((attr = (pthread_attr_t *) malloc(THREAD_COUNT * sizeof(pthread_attr_t))) == NULL){ //Same as threads, we should check for attributes' pointer
		perror("Error allocating memory.");
		return EXIT_FAILURE;
	}

	if((temp = (char *) malloc(6 * sizeof(char *))) == NULL){
		perror("Error allocating memory.");
		return EXIT_FAILURE;
	}
	temp[5] = '\0';

	//Using the first thread we create the file
	pthread_attr_init(&attr[0]);
	pthread_create(&threads[0], &attr[0], createFile, NULL);
	pthread_join(threads[0], NULL);

	//Since it does not take too much to generate and write random letters I assigned 1/3 of the threads to fill the file
	for(i = 0; i <ceil(THREAD_COUNT/3.0); i++) {
		pthread_attr_init(&attr[i]);
		pthread_create(&threads[i], &attr[i], generateRandomLetter, &i);
		pthread_join(threads[i], NULL);
	}
	fclose(fpFill);
	//After generation and writing operations done, we can search the file for the substrings using all the threads that we allocated
	for(i=0; i<THREAD_COUNT; i++){//Reads 5 chacter long from the string until it reaches to end of the file
		pthread_attr_init(&attr[i]);
		pthread_create(&threads[i], &attr[i], searchSubstring, &i); //Initializes one thread to start the search
		pthread_join(threads[i], NULL);
	}

	printf("X occurs %d times in the file\n", x);
	printf("OS occurs %d times in the file\n", os);
	printf("CPU occurs %d times in the file\n", cpu);
	printf("Disk occurs %d times in the file\n", disk);
	printf("Cache occurs %d times in the file\n", cache);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("The execution took %lf seconds\n", time_spent);
	fclose(fpSearch);
	free(threads);
	free(attr);
	return EXIT_SUCCESS;
}

void* createFile(void* arg){
	fpFill = fopen("big.txt", "a");
	fpSearch = fopen("big.txt", "r");
	if(fpFill == NULL || fpSearch == NULL){
		perror("Error opening file.");
		exit(EXIT_FAILURE);
	}
	pthread_exit(0);
}

void* generateRandomLetter(void* arg){
	srand(time(NULL));
	int i = *((int*)arg);
	int counter = 2500000.0/ceil(THREAD_COUNT/3.0); //Shows how many characters needs to be generated by one thread
	while(nChar < (i+1)*counter && nChar < 2500000){
		char randomletter = 'A' + (random() % 58);
		if(isalpha(randomletter)){
			fprintf(fpFill, "%c", randomletter);
			nChar++;
		}
	}
	pthread_exit(0);
}

void toLowerCase(char* str){
	int i;
	for(int i=0; str[i]; i++){
		str[i] = tolower(str[i]);
	}
}

void* searchSubstring(void* arg){
	FILE *fp = fpSearch;
	int i = *((int*)arg); //Indicates which thread is in the progress.
						  //I also used this as a marker in order to share the search operation between threads
	int counter = (int)(ceil(2500000.0/THREAD_COUNT)); //Shows how many characters needs to be searched by one thread
	fseek(fp, sizeof(char)*i*counter, SEEK_SET); //Sets the fp pointer in the position that the other thread finished searching 

	char temp[6];
	temp[5] = '\0';
	while((fscanf(fpSearch, "%5s", temp) != EOF) && (ftell(fp) < (sizeof(char)*(i+1)*counter))){//Reads a 5 character long string,
		char substr1[2];																		//decides if one of substrings exists in that section
		char substr2[3];
		char substr3[4];
		char substr4[5];
		substr1[1] = '\0';
		substr2[2] = '\0';
		substr3[3] = '\0';
		substr4[4] = '\0'; 
		toLowerCase(temp);
		strncpy(substr1, temp,1); //Takes substrings of temp of sizes 1 to 4 in order to compare them with our substrings
		strncpy(substr2, temp,2);
		strncpy(substr3, temp,3);
		strncpy(substr4, temp,4);

		if(strcmp(substr1, "x") == 0)
			x++;
		else if(strcmp(substr2, "os") == 0)
			os++;
		else if(strcmp(substr3, "cpu") == 0)
			cpu++;
		else if(strcmp(substr4, "disk") == 0)
			disk++;
		else if(strcmp(temp, "cache") == 0)
			cache++;

		int step = sizeof(char)*(strlen(temp)-1); //Since fscanf starts from the last position we need to get back a few characters in file
		fseek(fp, -1*step,SEEK_CUR);			  //for example fscanf read "XoFxP" if we don't take step back we'll mis the second x in the string
	}											  //The reason that step depends on the temp's size is at the end of the file temp's size is decreasing
	pthread_exit(0);							  //such that, let temp "AbCdf" then the next read would be "bCdf'EOF'" so size is decreased.
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "queue.h"

#define TIMESCALE 500
//Since the queues have ms run times, I used timescale in sleep function in order to make the outputs easier to read.

struct Process {
	int processNo;
	int burstTime;
	int remainingBurst;
};

void generateRandomProcesses(struct Process p[]); //Generates random burst time for processes according to the rules given

void buildReadyQueue(struct Queue *readyQueue, struct Process p[]); //Adds the generated processes to the first queue in the sequence order of 
void generateProcessSequence(int pNo[]); //Selects random process no and puts it into pNo array
int searchArray(int processes[], int pNo); //Searches if pNo is already in the array so we don't generate same pNo multiple times

void runQueue1(struct Queue *q1, struct Queue *q2); //Executes all the processes in the first queue (q1) until the queue is empty,
													//if any process does not finish execution sends them to the second queue (q2)
void runQueue2(struct Queue *q2, struct Queue *fcfs); //Same as runQueue1 but it sends unfinished processes to the first-come-first-serve queue
void runFCFS(struct Queue *fcfs);
void runProcess(struct Process *p, struct Queue *q, int quantumTime); //The other "run" functions call this function to simulate the execution of the process,
																	  //executes the process for given quantum time.

void simulateFeedbackQueue(struct Queue *q1, struct Queue *q2, struct Queue *q3); //Calls other functions to simulate the feedback queue

int main() {
	srand(time(NULL));
	struct Process processes[20];
	struct Queue *q1 = queue_new(sizeof(struct Process));
	struct Queue *q2 = queue_new(sizeof(struct Process));
	struct Queue *fcfs = queue_new(sizeof(struct Process));

	generateRandomProcesses(processes);
	buildReadyQueue(q1, processes);
	simulateFeedbackQueue(q1, q2, fcfs);

	queue_free(fcfs);
	queue_free(q2);
	queue_free(q1);

	system("pause");
	return EXIT_SUCCESS;
}

void generateRandomProcesses(struct Process p[]) {
	for (int i = 0; i < 20; i++) {
		int burstTime;
		switch (i) { //First 3 iterations are determined differently in order to have at least one process in each interval
		case 0:
			burstTime = rand() % 5 + 4; // 4ms <= burst time <= 8ms
			break;
		case 1:
			burstTime = rand() % 17 + 8; // 8ms <= burst time <= 24ms
			break;
		case 2:
			burstTime = rand() % 27 + 24; // 24ms <= burst time <= 50ms
			break;
		default:
			burstTime = rand() % 47 + 4; // 4ms <= burst time <= 50ms, general case
		}
		p[i].burstTime = burstTime;
		p[i].processNo = i;
		p[i].remainingBurst = burstTime;
	}
}

void buildReadyQueue(struct Queue *readyQueue, struct Process p[]) {
	int pNo[20];
	memset(pNo, -1, sizeof pNo); //Just to make sure the result of the comparisons in generateProcessSequence function work correctly
								 //setting elements of the array as -1
	generateProcessSequence(pNo);
	for (int i = 0; i < 20; i++) {
		int nextProcess = pNo[i]; //The next process in the sequence.
		queue_put(readyQueue, &p[nextProcess]);
	}
}

void generateProcessSequence(int pNo[]) {
	for (int i = 0; i < 20; i++) {
		int temp = rand() % 20; //Generates a random index
		if (searchArray(pNo, temp) == 0) //If it's not already exists in the sequence, adds it in the sequence
			pNo[i] = temp;
		else
			i--;
	}
}

int searchArray(int processes[], int pNo) {
	for (int i = 0; i < 20; i++) {
		if (processes[i] == pNo)
			return 1;
	}

	return 0;
}



void runQueue1(struct Queue *q1, struct Queue *q2) {
	while (q1->head != NULL) {
		struct Process p;
		queue_get(q1, &p);
		printf("Process %d is started execution in the first queue with %d ms remaining burst time.Quantum time of the queue is 8 ms.\n", p.processNo, p.remainingBurst);
		runProcess(&p, q1, 8);
		if (p.remainingBurst > 0) {
			queue_put(q2, &p);
			printf("Process %d could not finish execution in the first queue, it's dropped to the second queue.\n", p.processNo);
		}
	}
}

void runQueue2(struct Queue *q2, struct Queue *fcfs) {
	while (q2->head != NULL) {
		struct Process p;
		queue_get(q2, &p);
		printf("Process %d is started execution in the second queue with %d ms burst time. Quantum time of the queue is 16 ms.\n", p.processNo, p.remainingBurst);
		runProcess(&p, q2, 16);
		if (p.remainingBurst > 0) {
			queue_put(fcfs, &p);
			printf("Process %d could not finish execution in the second queue, it's dropped to the last queue.\n", p.processNo);
		}
	}
}

void runFCFS(struct Queue *fcfs) {
	while (fcfs->head != NULL) {
		struct Process p;
		queue_get(fcfs, &p);
		printf("Process %d is entered the last queue with %d ms burst time.The process will run until it's finished.\n", p.processNo, p.remainingBurst);
		runProcess(&p, fcfs, 51); //Since our processes have 50 ms burst time at most, this will act as fcfs queue
	}
}

void runProcess(struct Process *p, struct Queue *q, int quantumTime) {
	printf("Running process %d...\n", p->processNo);
	if (quantumTime > 50 || p->remainingBurst < quantumTime) { //If quantumtime > 50 that means the queue is fcfs so process will run until it finishes execution
		Sleep(p->remainingBurst * TIMESCALE);						   //If remaining burst < quantum time, the process will again run until it finishes no matter what queue it is currently in
		p->remainingBurst = 0;
	}
	else {
		Sleep(quantumTime * TIMESCALE);
		p->remainingBurst -= quantumTime;
		if (p->remainingBurst > 0)
			printf("Remaining burst time is %dms\n", p->remainingBurst);
	}

	if (p->remainingBurst == 0)
		printf("Process %d finished execution.\n", p->processNo);
}

void simulateFeedbackQueue(struct Queue *q1, struct Queue *q2, struct Queue *q3) {
	runQueue1(q1, q2);
	runQueue2(q2, q3);
	runFCFS(q3);
}
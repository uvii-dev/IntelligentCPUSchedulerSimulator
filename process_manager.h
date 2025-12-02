#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#define MAX_PROCESSES 10

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
} Process;

// Function declarations
void inputProcesses(Process processes[], int *n);
void resetProcesses(Process processes[], int n);
void calculateMetrics(Process processes[], int n);
void runAllAlgorithms(Process processes[], int n);

#endif
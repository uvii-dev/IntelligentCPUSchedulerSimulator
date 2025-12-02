#include <stdio.h>
#include <stdlib.h>
#include "process_manager.h"
#include "scheduler.h"
#include "ui.h"

void inputProcesses(Process processes[], int *n) {
    printHeader("PROCESS INPUT");
    
    printf("\nEnter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", n);
    
    if(*n > MAX_PROCESSES || *n <= 0) {
        printf("Invalid number of processes! Using default 3 processes.\n");
        *n = 3;
        // Default processes for testing
        processes[0] = (Process){1, 0, 5, 2, -1, 0, 0, 0, 5};
        processes[1] = (Process){2, 1, 3, 1, -1, 0, 0, 0, 3};
        processes[2] = (Process){3, 2, 8, 3, -1, 0, 0, 0, 8};
        printf("Loaded default processes for demonstration.\n");
        return;
    }
    
    printf("\n");
    int i;
    for(i = 0; i < *n; i++) {
        printf("Process %d:\n", i + 1);
        printf("  Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("  Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("  Priority: ");
        scanf("%d", &processes[i].priority);
        
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        printf("\n");
    }
}

void resetProcesses(Process processes[], int n) {
    int i;
    for(i = 0; i < n; i++) {
        processes[i].start_time = -1;
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].remaining_time = processes[i].burst_time;
    }
}

void calculateMetrics(Process processes[], int n) {
    int i;
    for(i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

void runAllAlgorithms(Process processes[], int n) {
    FCFS_Scheduling(processes, n);
    printf("\n\n");
    printf("Press Enter to continue to SJF...");
    getchar(); getchar();
    
    clearScreen();
    SJF_Scheduling(processes, n);
    printf("\n\n");
    printf("Press Enter to continue to Round Robin...");
    getchar();
    
    clearScreen();
    int quantum;
    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);
    RoundRobin_Scheduling(processes, n, quantum);
    printf("\n\n");
    printf("Press Enter to continue to Priority Scheduling...");
    getchar(); getchar();
    
    clearScreen();
    Priority_Scheduling(processes, n);
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "scheduler.h"
#include "ui.h"

void FCFS_Scheduling(Process processes[], int n) {
    printHeader("FIRST COME FIRST SERVE (FCFS) SCHEDULING");
    
    resetProcesses(processes, n);
    
    // Sort by arrival time
    int i, j;
    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if(processes[j].arrival_time > processes[j+1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
    
    int current_time = 0;
    for(i = 0; i < n; i++) {
        if(current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].start_time = current_time;
        processes[i].completion_time = current_time + processes[i].burst_time;
        current_time = processes[i].completion_time;
    }
    
    calculateMetrics(processes, n);
    printProcessTable(processes, n);
    printMetrics(processes, n);
    printGanttChart(processes, n);
}

void SJF_Scheduling(Process processes[], int n) {
    printHeader("SHORTEST JOB FIRST (SJF) SCHEDULING");
    
    resetProcesses(processes, n);
    
    int completed = 0, current_time = 0;
    int shortest = -1, min_burst = INT_MAX;
    int is_completed[MAX_PROCESSES] = {0};
    
    while(completed != n) {
        shortest = -1;
        min_burst = INT_MAX;
        
        // Find process with minimum burst time that has arrived
        int i;
        for(i = 0; i < n; i++) {
            if(processes[i].arrival_time <= current_time && !is_completed[i]) {
                if(processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    shortest = i;
                }
            }
        }
        
        if(shortest == -1) {
            current_time++;
            continue;
        }
        
        processes[shortest].start_time = current_time;
        processes[shortest].completion_time = current_time + processes[shortest].burst_time;
        current_time = processes[shortest].completion_time;
        is_completed[shortest] = 1;
        completed++;
    }
    
    calculateMetrics(processes, n);
    printProcessTable(processes, n);
    printMetrics(processes, n);
    printGanttChart(processes, n);
}

void RoundRobin_Scheduling(Process processes[], int n, int quantum) {
    printHeader("ROUND ROBIN SCHEDULING");
    printf("Time Quantum: %d\n", quantum);
    
    resetProcesses(processes, n);
    
    int remaining[MAX_PROCESSES];
    int i;
    for(i = 0; i < n; i++) {
        remaining[i] = processes[i].burst_time;
    }
    
    int current_time = 0, completed = 0;
    int queue[MAX_PROCESSES * 10], front = 0, rear = 0;
    int in_queue[MAX_PROCESSES] = {0};
    
    // Add first arriving processes to queue
    for(i = 0; i < n; i++) {
        if(processes[i].arrival_time <= current_time && !in_queue[i] && remaining[i] > 0) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }
    
    while(completed != n) {
        if(front == rear) {
            current_time++;
            // Check for new arrivals
            for(i = 0; i < n; i++) {
                if(processes[i].arrival_time <= current_time && !in_queue[i] && remaining[i] > 0) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
            continue;
        }
        
        int idx = queue[front++];
        in_queue[idx] = 0;
        
        if(processes[idx].start_time == -1) {
            processes[idx].start_time = current_time;
        }
        
        int execution_time = (remaining[idx] < quantum) ? remaining[idx] : quantum;
        current_time += execution_time;
        remaining[idx] -= execution_time;
        
        // Add newly arrived processes to queue
        for(i = 0; i < n; i++) {
            if(processes[i].arrival_time <= current_time && !in_queue[i] && remaining[i] > 0 && i != idx) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }
        
        // If current process still has remaining time, add it back to queue
        if(remaining[idx] > 0) {
            queue[rear++] = idx;
            in_queue[idx] = 1;
        } else {
            processes[idx].completion_time = current_time;
            completed++;
        }
    }
    
    calculateMetrics(processes, n);
    printProcessTable(processes, n);
    printMetrics(processes, n);
    printGanttChart(processes, n);
}

void Priority_Scheduling(Process processes[], int n) {
    printHeader("PRIORITY SCHEDULING");
    printf("Note: Lower priority number indicates higher priority\n");
    
    resetProcesses(processes, n);
    
    int completed = 0, current_time = 0;
    int highest_priority = -1, min_priority = INT_MAX;
    int is_completed[MAX_PROCESSES] = {0};
    
    while(completed != n) {
        highest_priority = -1;
        min_priority = INT_MAX;
        
        // Find process with highest priority (lowest number) that has arrived
        int i;
        for(i = 0; i < n; i++) {
            if(processes[i].arrival_time <= current_time && !is_completed[i]) {
                if(processes[i].priority < min_priority) {
                    min_priority = processes[i].priority;
                    highest_priority = i;
                }
            }
        }
        
        if(highest_priority == -1) {
            current_time++;
            continue;
        }
        
        processes[highest_priority].start_time = current_time;
        processes[highest_priority].completion_time = current_time + processes[highest_priority].burst_time;
        current_time = processes[highest_priority].completion_time;
        is_completed[highest_priority] = 1;
        completed++;
    }
    
    calculateMetrics(processes, n);
    printProcessTable(processes, n);
    printMetrics(processes, n);
    printGanttChart(processes, n);
}
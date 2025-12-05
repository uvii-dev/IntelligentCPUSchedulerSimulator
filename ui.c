#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

void printHeader(const char* title) {
    printf("\n");
    printSeparator('=');
    printCentered(title);
    printSeparator('=');
    printf("\n");
}

void printSeparator(char ch) {
    int i;
    for(i = 0; i < LINE_WIDTH; i++) printf("%c", ch);
    printf("\n");
}

void printCentered(const char* text) {
    int len = strlen(text);
    int padding = (LINE_WIDTH - len) / 2;
    int i;
    
    for(i = 0; i < padding; i++) printf(" ");
    printf("%s\n", text);
}

void printProcessTable(Process processes[], int n) {
    printf("\n");
    printSeparator('-');
    printf("| %-3s | %-12s | %-11s | %-8s | %-12s | %-16s |\n", 
           "ID", "Arrival", "Burst", "Priority", "Start", "Completion");
    printf("| %-3s | %-12s | %-11s | %-8s | %-12s | %-16s |\n", 
           "", "Time", "Time", "", "Time", "Time");
    printSeparator('-');
    
    int i;
    for(i = 0; i < n; i++) {
        printf("| %-3d | %-12d | %-11d | %-8d | %-12d | %-16d |\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].priority,
               processes[i].start_time, 
               processes[i].completion_time);
    }
    printSeparator('-');
}

void printMetrics(Process processes[], int n) {
    float avg_waiting = 0, avg_turnaround = 0;
    int i;
    
    for(i = 0; i < n; i++) {
        avg_waiting += processes[i].waiting_time;
        avg_turnaround += processes[i].turnaround_time;
    }
    
    avg_waiting /= n;
    avg_turnaround /= n;
    
    printf("\n");
    printSeparator('-');
    printf("| %-30s | %-15s | %-15s |\n", "Process", "Waiting Time", "Turnaround Time");
    printSeparator('-');
    
    for(i = 0; i < n; i++) {
        printf("| P%-29d | %-15d | %-15d |\n", 
               processes[i].pid, processes[i].waiting_time, processes[i].turnaround_time);
    }
    printSeparator('-');
    
    printf("\n");
    printSeparator('=');
    printf("| %-40s | %-15.2f |\n", "Average Waiting Time", avg_waiting);
    printf("| %-40s | %-15.2f |\n", "Average Turnaround Time", avg_turnaround);
    printSeparator('=');
}

void printGanttChart(Process processes[], int n) {
    printf("\n");
    printHeader("GANTT CHART");
    
    // Create timeline array
    int max_time = 0;
    int i, j;
    for(i = 0; i < n; i++) {
        if(processes[i].completion_time > max_time) {
            max_time = processes[i].completion_time;
        }
    }
    
    // Print the top border
    printf("+");
    for(i = 0; i <= max_time; i++) {
        printf("----+");
    }
    printf("\n");
    
    // Print process labels
    printf("|");
    int current_pos = 0;
    for(i = 0; i < n; i++) {
        int duration = processes[i].completion_time - processes[i].start_time;
        
        // Fill empty spaces before process
        while(current_pos < processes[i].start_time) {
            printf("    |");
            current_pos++;
        }
        
        // Print the process
        printf(" P%-1d", processes[i].pid);
        if(duration > 1) {
            for(j = 1; j < duration; j++) {
                printf("    |");
                current_pos++;
            }
        }
        current_pos++;
    }
    
    // Fill any remaining empty slots
    while(current_pos <= max_time) {
        printf("    |");
        current_pos++;
    }
    printf("\n");
    
    // Print the middle border
    printf("+");
    for(i = 0; i <= max_time; i++) {
        printf("----+");
    }
    printf("\n");
    
    // Print timeline numbers
    printf("0");
    current_pos = 0;
    for(i = 0; i < n; i++) {
        int duration = processes[i].completion_time - processes[i].start_time;
        
        // Move to start position
        while(current_pos < processes[i].start_time) {
            printf("    %d", ++current_pos);
        }
        
        // Print completion time
        for(j = 0; j < duration; j++) {
            current_pos++;
        }
        printf("   %2d", current_pos);
    }
    
    // Ensure we print the final time if needed
    if(current_pos < max_time) {
        printf("   %2d", max_time);
    }
    printf("\n\n");
    
    // Print execution sequence
    printf("Execution Sequence: ");
    for(i = 0; i < n; i++) {
        printf("P%d", processes[i].pid);
        if(i < n-1) printf(" -> ");
    }
    printf("\n");
}

void displayMenu() {
    printHeader("CPU SCHEDULER SIMULATOR");
    
    printf("\n");
    printCentered("MAIN MENU");
    printf("\n");
    
    printf("+------------------------------------------------------------------------------+\n");
    printf("| 1. Input Processes                                                          |\n");
    printf("| 2. First Come First Serve (FCFS)                                            |\n");
    printf("| 3. Shortest Job First (SJF)                                                 |\n");
    printf("| 4. Round Robin                                                              |\n");
    printf("| 5. Priority Scheduling                                                      |\n");
    printf("| 6. Display All Algorithms Comparison                                        |\n");
    printf("| 7. Exit                                                                     |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("\nEnter your choice (1-7): ");
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
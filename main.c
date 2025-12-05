#include <stdio.h>
#include <stdlib.h>
#include "process_manager.h"
#include "scheduler.h"
#include "ui.h"

int main() {
    Process processes[MAX_PROCESSES];
    int n = 0;
    int choice;
    int quantum;
    
    // Default processes for initial testing
    processes[0] = (Process){1, 0, 5, 2, -1, 0, 0, 0, 5};
    processes[1] = (Process){2, 1, 3, 1, -1, 0, 0, 0, 3};
    processes[2] = (Process){3, 2, 8, 3, -1, 0, 0, 0, 8};
    n = 3;
    
    do {
        clearScreen();
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                clearScreen();
                inputProcesses(processes, &n);
                break;
                
            case 2:
                clearScreen();
                if(n > 0) FCFS_Scheduling(processes, n);
                else printf("\nPlease input processes first!\n");
                break;
                
            case 3:
                clearScreen();
                if(n > 0) SJF_Scheduling(processes, n);
                else printf("\nPlease input processes first!\n");
                break;
                
            case 4:
                clearScreen();
                if(n > 0) {
                    printf("\nEnter time quantum for Round Robin: ");
                    scanf("%d", &quantum);
                    RoundRobin_Scheduling(processes, n, quantum);
                } else {
                    printf("\nPlease input processes first!\n");
                }
                break;
                
            case 5:
                clearScreen();
                if(n > 0) Priority_Scheduling(processes, n);
                else printf("\nPlease input processes first!\n");
                break;
                
            case 6:
                clearScreen();
                if(n > 0) {
                    runAllAlgorithms(processes, n);
                } else {
                    printf("\nPlease input processes first!\n");
                }
                break;
                
            case 7:
                clearScreen();
                printHeader("THANK YOU FOR USING CPU SCHEDULER SIMULATOR");
                break;
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        
        if(choice != 7) {
            printf("\nPress Enter to continue...");
            getchar();
            getchar();
        }
        
    } while(choice != 7);
    
    return 0;
}
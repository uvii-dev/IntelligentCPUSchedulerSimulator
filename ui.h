#ifndef UI_H
#define UI_H

#include "process_manager.h"

#define LINE_WIDTH 80

// UI Function declarations
void printHeader(const char* title);
void printSeparator(char ch);
void printCentered(const char* text);
void printProcessTable(Process processes[], int n);
void printMetrics(Process processes[], int n);
void printGanttChart(Process processes[], int n);
void displayMenu();
void clearScreen();

#endif
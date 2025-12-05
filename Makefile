CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = cpu_scheduler
SOURCES = main.c process_manager.c scheduler.c ui.c
HEADERS = process_manager.h scheduler.h ui.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
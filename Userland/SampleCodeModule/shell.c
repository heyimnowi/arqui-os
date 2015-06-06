#include <stdint.h>
#include "define.h"
#include "lib.h"
#include "shell.h"

#define COMMAND_LINE_SIZE	76`
#define GET_TIME			0
#define SET_TIME			1
#define SET_SCREENSAVER		2

char shellBuffer[COMMAND_LINE_SIZE] = {0};
int bufferIndex = 0;

void startShell()
{
	char c;

	printLineStart();
	// Main loop
	while (1) {
		// Keep waiting till there's a key to read
		c = getChar();
		switch (c) {
			case '\n':
				putChar(c);
				parseCommand(shellBuffer);
				printLineStart();
				break;
			case '\b':
				if (bufferIndex > 0) {
					shellBuffer[bufferIndex--] = 0;
					putChar(c);
				}
				break;
			case -1:
				break;
			default:
				if (bufferIndex == COMMAND_LINE_SIZE) {
					putChar('\b');
					bufferIndex--;
				}

				shellBuffer[bufferIndex++] = c;
				putChar(c);
				break;
		}
	}
}

void printLineStart()
{
	printf("#> ");
}

void parseCommand(const char * line)
{
	char command[80] = {0};
	char args[80] = {0};

	// We need at least the command to be scanned
	int hasCommand = sscanf(line, "%s %s", command, args);
	if (hasCommand == 0)
		return;

	if (strcmp(command, HELP_COMMAND) == 0) {
		help();
	} else if (strcmp(command, SET_TIME_COMMAND) == 0) {

	} else if (strcmp(command, GET_TIME_COMMAND) == 0) {

	} else if (strcmp(command, SET_SCREENSAVER_COMMAND) == 0) {
		int seconds = 0;
		if (sscanf(args, "%d", &seconds) > 0 && seconds > 0)
			setScreensaver(seconds);

	} else {
		printf("Command not found.\n");
	}

	clearBuffer();
}

static void clearBuffer(void)
{
	int i;
	for (i = 0; i < 76; i++)
		shellBuffer[i] = 0;

	bufferIndex = 0;
}

/*
 * Shell functions
 */
static void help()
{
	int opt;
	printf("Hi, I'm help, available commands:\n");
	printf("Please select your option\n");
	printf("0 - GET TIME\n");
	printf("1 - SET TIME\n");

	sscanf("%d",opt);

	switch(arg){
		case GET_TIME:
			print("Descripcion de Time");
			break;
		case SET_TIME:
			printf("Descripcion de Set");
			break;
	}
}

static void setTime()
{
	uint8_t hour, minute, second, year, day, month;
	char c,d;
	date current_date;

	// -------------------- YEAR ---------------- //
	printf("Enter year:\n");
	do {
		sscanf("%d",year);
	}
	while ( year < 0 )

	// -------------------- MONTH ---------------- //
	printf("Enter months:\n");
	do {
		sscanf("%d",month);
	}
	while ( month < 0 || month > 12)
	
	
	// -------------------- DAY ---------------- //
	printf("Enter days:\n");
	do {
		sscanf("%d",day);
	}
	while ( day < 0 || day > 31)
	
	// -------------------- HOUR ---------------- //
	printf("Enter hours:\n");
	do {
		sscanf("%d",hour);
	}
	while ( hour < 0 || hour > 23)

	// -------------------- MINUTE ---------------- //
	printf("Enter minutes:\n");
	do {
		sscanf("%d",minute);
	}
	while ( minute < 0 || minute > 59)

	// -------------------- SECOND ---------------- //
	printf("Enter seconds:\n");
	do {
		sscanf("%d",second);
	}
	while ( second < 0 || second > 59)


	current_date->hour = hour;
	current_date->minute = minute;
	current_date->second = second;
	current_date->day = day;
	current_date->month = month;
	current_date->year = year;

	execSysCall( SYS_TIME, &current_date, 1, 1 );
	printf("Complete.\n");
}

static void getTime()
{
	date current_date;
	execSysCall( SYS_TIME, &current_date, 1, 1 );
	printf("Current date and time: %02i:%02i:%02i %02i/%02i/%02i", current_date->hour, current_date->minute, 
	current_date->second, current_date->day, current_date->month, current_date->year);
}

static void setScreensaver(int seconds)
{
	execSysCall(SYS_SCREENSAVER, seconds, 0, 0);
}

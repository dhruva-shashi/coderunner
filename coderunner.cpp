#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>

char LANGUAGE[100];
char CODE_FILE_PATH[100];
char INPUT_FILE_PATH[100];
char OUTPUT_FILE_PATH[100];
char COMMAND[10000];

int NO_OF_ARGS = 11;
int TIME_IN_SECONDS;
int VALIDATION_XOR;

static void alarm_handler(int signo) {
	if (strcmp(LANGUAGE, "cpp") == 0)
		system("kill `pidof codefile`");
	if (strcmp(LANGUAGE, "java") == 0)
		system("kill `pidof java`");
	if (strcmp(LANGUAGE, "python") == 0)
		system("pkill -9 python");

	system(strcat("echo Time Limit Exceeded > ", OUTPUT_FILE_PATH));

	exit(0);
}

// Function to print coderunner version
void print_version() {
	printf("coderunner 2.0\n");
}

// Function to print help message
void print_help() {
	printf("Usage: ");
	printf("coderunner [--version] [--help] [-l <language>] [-c <code_file_path>] [-i <input_file_path>] [-o <output_file_path>] [-t <time (in seconds)>]\n\n");
	
	printf("Coderunner is a tool for compiling and running code. It also provides a check on the breach of time limit. Coderunner can be installed on Linux systems and is suitable for competitive programmers. Running the \"coderunner\" command compiles the file given by the code_file_path and executes the program. The input is redirected from the path given by input_file_path to the path given by output_file_path\n\n");

	printf("Arguments for coderunner\n");
	printf("--version\t\tVersion of coderunner\n");
	printf("--help\t\t\tManual of coderunner\n\n");

	printf("-l, cpp\t\t\tExecutes a C++ program\n");
	printf("-l, java\t\tExecutes a Java program\n");
	printf("-l, python\t\tExecutes a Python program\n\n");

	printf("-c <code_file_path>\tThe path for the code file\n");
	printf("-i <input_file_path>\tThe path for the input file\n");
	printf("-o <output_file_path>\tThe path for the output file\n");
	printf("-t <time (in seconds)>\tTime limit for code execution in seconds\n\n");
}

// Helper function to print an error message
void print_error(char* error_message) {
	printf("Error: %s\n", error_message);
}

// Parses arguments and initializes the variables accordingly
int parse_args(char* arg1, char* arg2) {
	if (strcmp(arg1, "-l") == 0) {
		VALIDATION_XOR ^= 1;

		if (strcmp(arg2, "cpp") != 0 && strcmp(arg2, "java") != 0 && strcmp(arg2, "python") != 0) {
			print_error("Wrong compiler");
			return 1;
		}

		strcpy(LANGUAGE, arg2);
		return 0;
	}
	if (strcmp(arg1, "-c") == 0) {
		VALIDATION_XOR ^= 2;

		if (access(arg2, F_OK)) {
			print_error("Code file not found");
			return 1;
		}

		strcpy(CODE_FILE_PATH, arg2);
		return 0;
	}
	if (strcmp(arg1, "-i") == 0) {
		VALIDATION_XOR ^= 4;

		if (access(arg2, F_OK)) {
			print_error("Input file not found");
			return 1;
		}

		strcpy(INPUT_FILE_PATH, arg2);
		return 0;
	}
	if (strcmp(arg1, "-o") == 0) {
		VALIDATION_XOR ^= 8;

		strcpy(OUTPUT_FILE_PATH, arg2);
		return 0;
	}
	if (strcmp(arg1, "-t") == 0) {
		VALIDATION_XOR ^= 16;

		TIME_IN_SECONDS = arg2[0]-'0';

		if (!(TIME_IN_SECONDS >= 1 && TIME_IN_SECONDS <= 9)) {
			print_error("Wrong time provided. Time should be between 1 and 9 seconds");
			return 1;
		}

		return 0;
	}

	return 2;
}

int main(int argc, char **argv) {
	if (argc == 1) {
		char* home = getenv("HOME");
		char coderunner_path[100];

		strcpy(coderunner_path, "");
		strcat(coderunner_path, home);
		strcat(coderunner_path, "/.coderunner/coderunner-ui");

		if (access(coderunner_path, F_OK)) {
			print_error("Coderunner UI not installed. Install by running the following command\n\ncoderunner --install\n");
			return 1;
		}

		system(coderunner_path);
		return 0;
	}

	if (argc == 2 && strcmp(argv[1], "--install") == 0) {
		system("rm -rf ~/.coderunner");
		system("mkdir ~/.coderunner");
		system("wget -O ~/.coderunner/master.zip https://github.com/dhruva-shashi/coderunner/archive/master.zip");
		system("unzip ~/.coderunner/master.zip -d ~/.coderunner");
		system("mv ~/.coderunner/coderunner-master/* ~/.coderunner");
		system("rm -rf ~/.coderunner/coderunner-master");
		system("rm ~/.coderunner/master.zip");
		return 0;
	}

	if (argc == 2 && strcmp(argv[1], "--version") == 0) {
		print_version();
		return 0;
	}

	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		print_help();
		return 0;
	}

	if (argc != 11) {
		printf("Error: Number of arguments is incorrect: Expected 11, Found %d\n", argc);
		print_help();
		return 0;
	}

	VALIDATION_XOR = 0;

	for (int i = 1; i < NO_OF_ARGS; i += 2) {
		int err_val = parse_args(argv[i], argv[i+1]);

		if (err_val == 2)
			printf("Error: Incorrect argument: %s %s\n", argv[i], argv[i+1]);

		if (err_val)
			return 0;
	}

	// VALIDATION_XOR should be 31. Otherwise, argument vectors might be repititive
	if (VALIDATION_XOR != 31) {
		print_error("Repetitive argument vector found");
		return 0;
	}

	if (strcmp(LANGUAGE, "cpp") == 0) {
		strcpy(COMMAND, "");

		strcat(COMMAND, "g++ ");
		strcat(COMMAND, CODE_FILE_PATH);
		strcat(COMMAND, " -o codefile 2> ");
		strcat(COMMAND, OUTPUT_FILE_PATH);

		if (system(COMMAND))
			return 0;
	}

	signal(SIGALRM, alarm_handler);
	alarm(TIME_IN_SECONDS);

	if (strcmp(LANGUAGE, "cpp") == 0) {
		strcpy(COMMAND, "");

		strcat(COMMAND, "cat ");
		strcat(COMMAND, INPUT_FILE_PATH);
		strcat(COMMAND, " | ");
		strcat(COMMAND, "./codefile > ");
		strcat(COMMAND, OUTPUT_FILE_PATH);

		system(COMMAND);
		return 0;
	}
	if (strcmp(LANGUAGE, "java") == 0) {
		strcpy(COMMAND, "");

		strcat(COMMAND, "cat ");
		strcat(COMMAND, INPUT_FILE_PATH);
		strcat(COMMAND, " | ");
		strcat(COMMAND, "java ");
		strcat(COMMAND, CODE_FILE_PATH);
		strcat(COMMAND, " > ");
		strcat(COMMAND, OUTPUT_FILE_PATH);
		strcat(COMMAND, " 2> ");
		strcat(COMMAND, OUTPUT_FILE_PATH);

		system(COMMAND);
		return 0;
	}
	if (strcmp(LANGUAGE, "python") == 0) {
		strcpy(COMMAND, "");

		strcat(COMMAND, "cat ");
		strcat(COMMAND, INPUT_FILE_PATH);
		strcat(COMMAND, " | ");
		strcat(COMMAND, "python3 ");
		strcat(COMMAND, CODE_FILE_PATH);
		strcat(COMMAND, " > ");
		strcat(COMMAND, OUTPUT_FILE_PATH);
		strcat(COMMAND, " 2> ");
		strcat(COMMAND, OUTPUT_FILE_PATH);

		system(COMMAND);
		return 0;
	}

	return 0;
}

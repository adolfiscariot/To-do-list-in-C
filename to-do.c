//This is my very first C project. It's a simple to do list. It is currently March 4th 2025 at 5:54 am. 

//Create a to do list where user can view, add and delete tasks. Tasks should be stored in a file called tasks.txt

#include <stdio.h>

//the task struct
typedef struct {
	char *description;
	int completed;
} Task;

//define task length
#define TASK_LENGTH 100


//add task
int main() {
	//take in user input
	printf("Input a task: ");
	char task_input[TASK_LENGTH]; //buffer for holding task
	fgets(task_input, TASK_LENGTH, stdin); //get user input 

	//put user input in tasks.txt file
	int task_counter = 0;
	FILE *fp;
	if (task_counter == 0)
		fp = fopen("tasks.txt", "w");
	else
		fp = fopen("tasks.txt", "a");
	fputs(task_input, fp);
	task_counter +=1;
	fclose(fp);
}

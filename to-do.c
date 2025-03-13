//This is my very first C project. It's a simple to do list. It is currently March 4th 2025 at 5:54 am. 

//Create a to do list where user can view, add and delete tasks. Tasks should be stored in a file called tasks.txt

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TASK_LENGTH 100

//the task struct
typedef struct {
	char *description;
} Task;


//add task
int main() {
	//create new task
	Task task;

	//take in user input
	printf("Input a task: ");
	char task_input[TASK_LENGTH];
	fgets(task_input, TASK_LENGTH, stdin); 

	//remove new line from string input
	task_input[strcspn(task_input, "\n")] = '\0';

	//copy task_input into task.description
	task.description = calloc(1, TASK_LENGTH);
	if(task.description==NULL)
		perror("Mem alloc failed");	
       	strcpy(task.description, task_input);

	//open file
	FILE *fp = fopen("tasks.txt", "a");
	if (fp==NULL){
		perror("Issue opening file");
		return -1;
	}

	//put input in file
	fputs(task.description, fp);
	fputs("\n", fp);
	printf("The task has been added\n");

	//free the memory and close the file
	free(task.description);	
	fclose(fp);
}

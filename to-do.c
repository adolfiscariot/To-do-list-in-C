//This is my very first C project. It's a simple to do list. It is currently March 4th 2025 at 5:54 am. 

//Create a to do list where user can view, add and delete tasks. Tasks should be stored in a file called tasks.txt

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TASK_LENGTH 100
#define TOTAL_TASKS 10

//the task struct
typedef struct {
	char *description;
} Task;

int task_counter = 0;

//add task
void add_task() {
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
		return;
	}

	//put input in file
	fputs(task.description, fp);
	fputs("\n", fp);
	printf("The task has been added\n");

	//free the memory and close the file
	free(task.description);	
	fclose(fp);
}
void show_tasks(){
	//open file
	FILE *fp = fopen("tasks.txt", "r");
	//if fille is null throw error
	if(fp == NULL){
		perror("Couldn't open file");
		return;
	}
	//create buffer to store fetched tasks
	char *fetched_tasks = calloc(TOTAL_TASKS, TASK_LENGTH);
	//while fgets != NULL print tasks
	while ((fgets(fetched_tasks, TASK_LENGTH, fp)) != NULL)
		printf("%d: %s\n", ++task_counter, fetched_tasks);
	//free memory and close file
	free(fetched_tasks);
	fclose(fp);
}
int main(void){
	//tell user welcome to task manager and select a choice
	printf("WELCOME TO THE TASK MANAGER!\n");
	printf("Please select a choice.Press...\n");
	printf("1 to show tasks\n2 to add a task\n");
	//create buffer to store user input
	char user_input[4];
	//get user input and store it in buffer
	fgets(user_input, sizeof(int), stdin);
	//convert string user input to an int
	int converted_user_input = atoi(user_input);
	//switch case for which choice they select
	switch(converted_user_input){
		case 1: show_tasks(); break;
		case 2: add_task(); break;
	}
}

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
	char *completed;
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

	//user input for task completion
	printf("Is it completed? 1 for yes, 0 for no...");
	char completed_input;
	fgets(&completed_input, sizeof(int), stdin);

	//remove new line from string input
	task_input[strcspn(task_input, "\n")] = '\0';

	//copy task_input into task.description
	task.description = calloc(1, TASK_LENGTH);
	if(task.description==NULL)
		perror("Mem alloc failed");	
       	strcpy(task.description, task_input);
	
	//make task.completed yes or no
	if (completed_input == 0)
		task.completed = "No";
	else if (completed_input == 1)
		task.completed = "Yes";

	//open file
	FILE *fp = fopen("tasks.txt", "a");
	if (fp==NULL){
		perror("Issue opening file");
		return;
	}

	//put input in file
	fputs(task.description, fp);
	fputs("Completed? ", fp);
	fputs(task.completed, fp);
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
	printf("-----TASK MANAGER-----\n");
	while ((fgets(fetched_tasks, TASK_LENGTH, fp)) != NULL)
		printf("%d: %s", ++task_counter, fetched_tasks);

	//free memory and close file
	free(fetched_tasks);
	fclose(fp);
}

//add function to delete task
void delete_task(){

	//ask user which idea they want to delete
	printf("Which idea do you want to delete?...");
	
	//open tasks.txt (check for error)
	FILE *fp = fopen("tasks.txt", "r");
	if (fp == NULL){
		perror("Couldn't open file");
		return;
	}
	
	//open temp.txt
	FILE *fp2 = fopen("temp.txt", "w");
	if (fp2 == NULL){
		perror("Couldn't open file");
		return;
	}
	
	//get user's choice
	int user_choice;
	scanf("%d", &user_choice);
	
	//initialize line counter and task buffer
	int line_counter = 0;
	char task_buffer[TASK_LENGTH];

	//read from tasks.txt
	while ((fgets(task_buffer, TASK_LENGTH, fp)) != NULL){
		//add line counter
		line_counter++;
		if (line_counter != user_choice)
			fputs(task_buffer, fp2);
	}
	//close the files
	fclose(fp2);
	fclose(fp);

	//delete tasks.txt and eename tempt.txt to tasks.txt
	remove("tasks.txt");
	rename("temp.txt", "tasks.txt");

	//print task deleted
	printf("Task %d deleted!\n", user_choice);
	return;
}

int main(void){
	//tell user welcome to task manager and select a choice
	printf("WELCOME TO THE TASK MANAGER!\n");
	printf("Please select a choice.Press...\n");
	printf("1 to show tasks\n2 to add a task\n3 to delete task\n\n");

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
		case 3: delete_task(); break;
	}
}

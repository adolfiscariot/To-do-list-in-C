//This is my very first C project. It's a simple to do list. It is currently March 4th 2025 at 5:54 am. 

//Create a to do list where user can view, add and delete tasks. Tasks should be stored in a file called tasks.txt

#include <stdio.h>
#include <stdbool.h>

//define max length of each task
#define MAX_LENGTH 100

//create task struct 
typedef struct {
	char description[MAX_LENGTH]; 
}Task;

//add task counter
int task_counter = 0;

//function to show tasks
void show_tasks() {
	//check if there are tasks present 
	if(task_counter == 0)
		printf("No tasks available\n");
	
	//otherwise open a file pointer and read each line of the tasks file
	FILE *fp;
	char s [1024]; //buffer to store each line we read
			 
	int local_task_counter = 0;
	fp = fopen("tasks.txt", "r");
	if (fp == NULL)
		printf("Couldn't open file\n");
	else
		while (fgets(s, sizeof s, fp) != NULL)
			printf("%d: , %s\n", ++local_task_counter, s);
	
	//close file
	fclose(fp);
}

//write new tasks. Function returns bool on if task was created successfully
void add_tasks() {
	//create new task
	Task new_task;

	//ask user to input task
	printf("Add a task...");

	//add user input to task description
	fgets(new_task.description, MAX_LENGTH, stdin);
	printf("Task description: %s\n", new_task.description); //open file and put tasks in there 
	FILE *fp; 
	if(task_counter == 0) 
		fp = fopen("tasks.txt", "w");
	else
		fp = fopen("tasks.txt", "a");
	if(fp == NULL) {
		printf("File couldn't open\n");
		return;
	} else {
		fputs(new_task.description, fp);
		task_counter++;
	}

	fclose(fp);
	printf("Task added successfully!");
	return;
}

//write switch case statement to select read, add, display
int main(void) {
	printf("What do you wanna do? Press\n"
			"...1 for Show Tasks\n"
			"...2 for Add Tasks\n");
	char user_input[10];
	fgets(user_input, sizeof(user_input), stdin);
	switch(user_input[0]){
		case '1':

			show_tasks();
			break;
		case '2':
			add_tasks();
			break;
	}
	return 0;
}

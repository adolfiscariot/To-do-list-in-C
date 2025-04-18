//This is my very first C project. It's a simple to do list. It is currently March 4th 2025 at 5:54 am. 

//Create a to do list where user can view, add, update and delete tasks. Tasks should be stored in a file called tasks.txt

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TASK_LENGTH 100
#define TOTAL_TASKS 10

//the task struct
struct Task{
	char *description;
	char *completed;
};

int task_counter = 0;

//function to add a task
void add_task() {
	//create new task
	struct Task task;

	//take in user input
	printf("Input a task: ");
	char task_input[TASK_LENGTH];
	fgets(task_input, TASK_LENGTH, stdin); 

	//remove new line from string input
	task_input[strcspn(task_input, "\n")] = '\0';

	//copy task_input into task.description
	task.description = calloc(1, TASK_LENGTH);
	if(task.description==NULL)
		perror("Task.Description memory alloc failed");	
       	strcpy(task.description, task_input);
	
	//user input for task completion
	printf("Is it completed? 1 for yes, 0 for no...");
	int completed_input;
	scanf("%d", &completed_input);

	//allocate memory for task completed
	task.completed = calloc(1, 10);
	if (task.completed == NULL)
		perror("Task.Completed memory alloc failed");

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
	fputs(". Completed? ", fp);
	fputs(task.completed, fp);
	fputs("\n", fp);
	printf("The task has been added\n");

	//free the memory and close the file
	free(task.description);	
	fclose(fp);
}

//function to show tasks
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

//function to delete a task
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

//function to select a task
int pick_a_task(){
	//pick a task
	printf("\nWhich task do you want to update?\n");
	int task_to_update;
	scanf("%d", &task_to_update);
	return task_to_update;
}

//function to update task completion
void update_task_completion(){
	//show tasks first
	show_tasks();

	//user inputs task to be updated
	int task_to_update = pick_a_task();

	//check current state of task.completed
	FILE *fp = fopen("tasks.txt", "r");	
	if (fp == NULL){
		printf("Couldn't open file");
		return;
		}
 
	FILE *fp2 = fopen("temp.txt", "w");	
	if (fp2 == NULL){
		printf("Couldn't open file");
		return;
		}

	//loop through list until you get to task number user input
	int task_counter = 0;
	char task_buffer[TASK_LENGTH];

	/*while task isn't the one you want just add it to temp.txt*/
	while ((fgets(task_buffer, TASK_LENGTH, fp)) != NULL){
		task_counter++;

		/*if you land on the task you want...*/
		if (task_counter == task_to_update){
			printf("Task buffer: %s\n", task_buffer);
		
			/*put task in description from start to .*/
			char task_description[TASK_LENGTH];
			sscanf(task_buffer, "%[^.]", task_description);

			printf("Is the task completed? 1 for yes, 0 for no\n");
			int completed_input;
			scanf("%d", &completed_input);

			/*turn completed input to yes/no*/
			char task_completed[TASK_LENGTH];
			if (completed_input == 0)
				strcpy(task_completed, "No\n");
			else if (completed_input == 1)
				strcpy(task_completed, "Yes\n");

			/*add task completed and description to temp.txt*/
			fputs(task_description, fp2);
			fputs(". ", fp2);
			fputs(task_completed, fp2);

			printf("Task updated\n");
		}
		else {
			fputs(task_buffer, fp2);
		}
	}
	remove("tasks.txt");
	rename("temp.txt", "tasks.txt");
}

int main(void){
	//tell user welcome to task manager and select a choice
	printf("WELCOME TO THE TASK MANAGER!\n");
	printf("Please select a choice.Press...\n");
	printf("1 to show tasks\n2 to add a task\n3 to delete task\n4 to update  task completion\n\n");

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
		case 4: update_task_completion(); break;
	}
}

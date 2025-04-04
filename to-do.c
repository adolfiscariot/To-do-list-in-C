//This is my very first C project. It's a simple to do list. It is currently March 4th 2025 at 5:54 am. 

//Create a to do list where user can view, add and delete tasks. Tasks should be stored in a file called tasks.txt

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TASK_LENGTH 100
#define TOTAL_TASKS 5

//the task struct
typedef struct{
	char *description;
	char *completed;
}Task;

/*the dynamic array struct*/
typedef struct{
	Task *tasks; /*pointer to the tasks in the array*/
	int capacity; /*max size of array*/
	int size; /*how full the array is*/
}TaskArray;

int task_counter = 0;

/*Function to initialize task array*/
void initialize_array(TaskArray *array){
	array->tasks = (Task *) calloc(TOTAL_TASKS, TASK_LENGTH);	
	if (array->tasks == NULL){
		perror("Mem alloc failed");
		exit(1);
	}
	array->capacity = TOTAL_TASKS;
	array->size = 0;
}
	
/*Function to push task onto array*/
void push(TaskArray *array, Task value){
	if (array->size >= array->capacity){
		/*create a new capacity and a new array*/
		int new_capacity = array->capacity * 2;
		Task *new_array = (Task *)  realloc(array->tasks, (new_capacity * sizeof(Task)));
		if (new_array == NULL){
			perror("Mem alloc failed\n");
			exit(1);
		}
		/*Reassign array task to new array*/
		array->tasks = new_array;
		array->capacity = new_capacity;
	}	
	/*insert element in next open position*/
	array->tasks[array->size] = value;
	/*Add size by 1*/	
	array->size++;
}

//function to add a task
void add_task(Task *task, TaskArray *array) {
	//take in user input
	printf("Input a task: ");
	char task_input[TASK_LENGTH];
	fgets(task_input, TASK_LENGTH, stdin); 

	//remove new line from string input
	task_input[strcspn(task_input, "\n")] = '\0';

	//copy task_input into task.description
	task->description = calloc(1, TASK_LENGTH);
	if(task->description==NULL){
		perror("Task.Description memory alloc failed");	
		exit(1);
	}
       	strcpy(task->description, task_input);
	printf("Task description is: %s\n", task->description);
	
	//user input for task completion
	printf("Is it completed? 1 for yes, 0 for no...");
	int completed_input;
	scanf("%d", &completed_input);
	getchar();

	//allocate memory for task completed
	task->completed = calloc(1, 4);
	if (task->completed == NULL){
		perror("Task.Completed memory alloc failed");
		exit(1);
	}

	//make task.completed yes or no
	if (completed_input == 0)
		strcpy(task->completed, "No");
	else if (completed_input == 1)
		strcpy(task->completed, "Yes");
	printf("Task completed is: %s\n", task->completed);

	/*push to array whatever is in the task*/
	push(array, *task);

}

//function to show tasks
void show_tasks(TaskArray *array){
	/**/
	for (int i = 0; i < array->size; i++)
		printf("%s. %s\n", array->tasks[i].description, array->tasks[i].completed);

}

//function to select a task
int pick_a_task(){
	//pick a task
	printf("\nPick a task...\n");
	int task_to_update;
	scanf("%d", &task_to_update);
	return task_to_update;
}

/*function to delete a task*/
void delete_task(){

	//ask user which idea they want to delete
	int user_choice = pick_a_task();
	
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



//function to update task completion
void update_task_completion(TaskArray *array, Task *task){
	//show tasks first
	show_tasks(array);

	//user inputs task to be updated
	int task_to_update = pick_a_task();

	//check current state of task.completed
	FILE *fp = fopen("tasks.txt", "r");	
	if (fp == NULL){
		perror("Couldn't open file\n");
		return;
		}

	//open temporary file
	FILE *fp2 = fopen("temp.txt", "w");
	if (fp2 == NULL){
		perror("Couldn't open temp.txt\n");
		return;
	}
 
	//loop through list until you get to task number user input
	int task_counter = 0;
	char task_buffer[TASK_LENGTH];
	while ((fgets(task_buffer, TASK_LENGTH, fp)) != NULL){
		task_counter++;
		//update the task and store it in temp.txt
		if (task_counter == task_to_update){
			printf("Is it completed? 1 for yes, 0 for no...");
			int answer;
			scanf("%d", &answer);
			
			//create strings to store the data
			char task_description[TASK_LENGTH];
			char task_status[100];

			//put struct in the above locations
			sscanf(task_buffer, "%[^.]. Completed? %s\n", task_description, task_status);
			//set task_status to yes or no
			if (answer == 1)
				strcpy(task_status, "Yes");
			else
				strcpy(task_status, "No");

			//print into a file
			fprintf(fp2, "%s. Completed? %s\n", task_description, task_status);

			printf("The task has been updated\n");

		}
		else
			fputs(task_buffer, fp2);
	}
	remove("tasks.txt");
	rename("temp.txt", "tasks.txt");
}

//main function
int main(void){
	//tell user welcome to task manager and select a choice
	printf("WELCOME TO THE TASK MANAGER!\n");
	printf("Please select a choice.Press...\n");
	printf("1 to show tasks\n2 to add a task\n3 to delete task\n4 to update task completion\n\n");

	//create buffer to store user input
	char user_input[4];

	//get user input and store it in buffer
	fgets(user_input, sizeof(int), stdin);

	//convert string user input to an int
	int converted_user_input = atoi(user_input);

	TaskArray *array;
	Task task;
	initialize_array(array);

	//switch case for which choice they select
	switch(converted_user_input){
		case 1: show_tasks(array); break;
		case 2: add_task(&task, array); break;
		case 3: delete_task(); break;
		case 4: update_task_completion(array, &task); break;
	}
}

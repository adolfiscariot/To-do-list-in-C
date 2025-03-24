#include <stdio.h>

struct Task{
	char* description;
	char* completed;
};

void add_task(struct Task *task){
	task->description = "yes";
	printf("%s\n", task->description);
}

int main(void){
	struct Task task;
	add_task(&task);	
}


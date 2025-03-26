#include <stdio.h>

struct Task{
	char* description;
	char* completed;
};

void add_task(struct Task *task){
	task->description = "yes\n";
	FILE *fp = fopen("shit.bin", "wb");
	if(fp == NULL){
		perror("file didn't open");
		return;
	}
	fwrite((task->description), 100, 1, fp);
	printf("nimeweka %s\n", task->description);
}

void show_task(struct Task *task){
	FILE *fp = fopen("shit.bin", "rb");
	char shit[100];
	while (fread(&shit, 100, 1, fp) > 0)
		printf("%s\n", task->description);
}

int main(void){
	struct Task task;
	printf("choose 1 or 2...\n");
	int input;
	scanf("%d", &input);
	switch(input){
		case 1: add_task(&task); break;
		case 2: show_task(&task); break;
	}
}


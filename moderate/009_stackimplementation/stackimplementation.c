#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _frame {
	int data;
	struct _frame *next;
} frame_t;

typedef struct _stack {
	struct _frame *head;
	unsigned size;
} stack_t;

stack_t *stack_init(void)
{
	stack_t *out = (stack_t *) malloc(sizeof(stack_t));
	out->head = NULL;
	out->size = 0;
	return out;
}

void stack_destroy(stack_t *stk)
{
	free(stk);
}

void stack_push(stack_t *stk, int data)
{
	frame_t *frame = (frame_t *) malloc(sizeof(frame_t));
	frame->data = data;
	frame->next = stk->head;
	stk->head = frame;
	stk->size += 1;
}

int stack_pop(stack_t *stk)
{
	if (stk->head == NULL)
		printf("Stack empty.\n");
	frame_t *frame = stk->head;
	int data = frame->data;
	stk->head = frame->next;
	stk->size -= 1;
	free(frame);
	return data;
}

void force_suffix(FILE *fp, const char insert)
{
	long pos = ftell(fp);
	fseek(fp, 0 - sizeof(char), SEEK_END);
	if (fgetc(fp) != insert)
	{
		fseek(fp, 0, SEEK_END);
		fputc(insert, fp);
		fflush(fp);
	}
	fseek(fp, pos, SEEK_SET);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: %s %s\n", argv[0], "filename");
		return 0;
	}
	FILE *file = fopen(argv[1], "r+");
	if (!file)
	{
		perror("Could not open file.\n");
		return 1;
	}
	force_suffix(file, '\n');
	char *str = (char *) malloc(sizeof(char) * 400);
	while (fscanf(file, "%[^\n]\n", str))
	{
		unsigned i = 0;
		stack_t *stack = stack_init();
		char *token = strtok(str, " ");
		while (token != NULL)
		{
			stack_push(stack, atoi(token));
			token = strtok(NULL, " ");
			i++;
		}
		unsigned j;
		unsigned mode = 1;
		for (j = i; j > 0; j--)
		{
			int n = stack_pop(stack);
			if (mode)
			{
				printf("%d", n);
				if (j > 2)
					printf("%c", ' ');
			}
			mode = !mode; /* alternate */
		}
		printf("%c", '\n');
		stack_destroy(stack);

		if (feof(file))
			break;
	}
	free(str);
	fclose(file);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CELL_COUNT	30000
/* debug mode: compile with -D DEBUG for progress bar + memory viewer (SLOW) */

/* linked-list stack implementation */

typedef struct _frame {
	int data;
	struct _frame *next;
} frame_t;

typedef struct _stack {
	struct _frame *head;
	unsigned size;
} stack_t;

void stack_push(stack_t *stk, const int data)
{
	frame_t *frame = (frame_t *) malloc(sizeof(frame_t));
	frame->data = data;
	frame->next = stk->head;
	stk->head = frame;
	stk->size += 1;
}

int stack_pop(stack_t *stk)
{
	/* popping from empty stack will cause a segfault */
	if (stk->head == NULL)
		printf("Stack empty.\n");
	frame_t *frame = stk->head;
	int data = frame->data;
	stk->head = frame->next;
	stk->size -= 1;
	free(frame);
	return data;
}

stack_t *stack_init(void)
{
	stack_t *out = (stack_t *) malloc(sizeof(stack_t));
	out->head = NULL;
	out->size = 0;
	return out;
}

void stack_destroy(stack_t *stk)
{
	/* pop all stack frames if not empty */
	while (stk->head != NULL)
		stack_pop(stk);
	free(stk);
}

/* brainfuck interpreter */

typedef enum {
	INVALID_COMMAND,
	INCREMENT_PTR,
	DECREMENT_PTR,
	INCREMENT_DATA,
	DECREMENT_DATA,
	OUTPUT_DATA,
	INPUT_DATA,
	LEFT_BRACKET,
	RIGHT_BRACKET
} bfuck_t;

bfuck_t interpret_cmd(const char c)
{
	bfuck_t cmd;
	switch (c)
	{
		case '>': cmd = INCREMENT_PTR; break;
		case '<': cmd = DECREMENT_PTR; break;
		case '+': cmd = INCREMENT_DATA; break;
		case '-': cmd = DECREMENT_DATA; break;
		case '.': cmd = OUTPUT_DATA; break;
		case ',': cmd = INPUT_DATA; break;
		case '[': cmd = LEFT_BRACKET; break;
		case ']': cmd = RIGHT_BRACKET; break;
		default : cmd = INVALID_COMMAND; break;
	}
	return cmd;
}

int out_of_bounds(const bfuck_t cmd, unsigned *ptr)
{
	int underflow = (cmd == DECREMENT_PTR && *ptr < 0); /* underflow */
	int overflow = (cmd == INCREMENT_PTR && *ptr > CELL_COUNT); /* overflow */
	return (underflow || overflow);
}

void execute_cmd(const bfuck_t cmd, unsigned *ptr, unsigned char *cells)
{
	if (out_of_bounds(cmd, ptr)) /* bounds checking */
		return;
	/* interpreter will write to stdout and take bytes from stdin */
	switch (cmd)
	{
		case INCREMENT_PTR: (*ptr)++; break;
		case DECREMENT_PTR: (*ptr)--; break;
		case INCREMENT_DATA: cells[*ptr]++; break;
		case DECREMENT_DATA: cells[*ptr]--; break;
		case OUTPUT_DATA: putc(cells[*ptr], stdout); break; /* stdout */
		case INPUT_DATA: cells[*ptr] = getc(stdin); break; /* stdin */
		case INVALID_COMMAND: break; /* ignore */
		default: break;
	}
}

int next_matching_bracket(int i, const char *program)
{
	unsigned len = strlen(program);
	unsigned j = 0;
	bfuck_t cmd = INVALID_COMMAND;
	while (cmd != RIGHT_BRACKET && j != 0)
	{
		if (i < len) /* if fail, jump past the end of the program */
			return (int) len + 1;

		cmd = interpret_cmd(program[i++]);
		if (cmd == LEFT_BRACKET) /* skip pairs of nested [] */
			j++;
		else if (cmd == RIGHT_BRACKET)
			j--;
	}
	return i + 1; /* jump to char after ']' */
}

#ifdef DEBUG
void debug(int i, const char *program, unsigned ptr, unsigned char *cells, int jmp)
{
	bfuck_t cmd = interpret_cmd(program[i]);
	const static char *cmd_names[] = {
		"INVALID_COMMAND",
		"INCREMENT_PTR",
		"DECREMENT_PTR",
		"INCREMENT_DATA",
		"DECREMENT_DATA",
		"OUTPUT_DATA",
		"INPUT_DATA",
		"LEFT_BRACKET",
		"RIGHT_BRACKET"
	};
	static int iterations = 0;
	iterations++;
	if (iterations > 10000)
		abort(); /* debug mode is very slow */
	system("sleep 0.01 && clear");

	/* program progress bar */
	printf("DEBUG\n");
	printf("\n%s\n", program);
	int x;
	for (x = 0; x < i; x++)
	{
		printf("%c", ' ');
	}
	printf("^\n");

	/* display cell contents */
	unsigned len = 12;
	for (x = 0; x < ptr; x++)
		printf("\t");
	printf("v\n");
	for (x = 0; x < len; x++)
		printf("%d\t", x);
	printf("\n");
	for (x = 0; x < len; x++)
		printf("%d\t", cells[x]);
	printf("\n");
	if (jmp > -1)
		printf("\nJMP VALUE: %d\n", jmp);
	/* other parameters */
	printf("current i: %d, char: %c, command: %s\n", i, program[i], cmd_names[cmd]);
	printf("current ptr: %u\n", ptr);
	printf("end\n");
}
#endif

void run_program(const char *program)
{
	unsigned ptr = 0; /* data cell ptr */
	unsigned char *cells; /* cells */
	cells = (unsigned char *) calloc(CELL_COUNT, sizeof(unsigned char));
	stack_t *stk = stack_init(); /* nested bracket stack */

	unsigned len = strlen(program);
	int i = 0; /* program ptr */
	while (i < len)
	{
		static int jmp = -1; /* [] loop jump-to value, inert value is -1 */
		bfuck_t cmd = interpret_cmd(program[i]);
		if (cmd == LEFT_BRACKET)
		{
			if (!cells[ptr])
				i = next_matching_bracket(i, program); /* skip forward */
			else
			{
				stack_push(stk, jmp); /* push current jmp value to stack */
				jmp = i;
			}
		}
		else if (cmd == RIGHT_BRACKET)
		{
			if (!cells[ptr])
			{
				/* note: if this isn't a nested loop,
				         jmp value should return to it's inert value of -1 */
				jmp = stack_pop(stk); /* pop previous jmp value from stack */
			}
			else
				i = jmp;
		}
		else
			execute_cmd(cmd, &ptr, cells);

		#ifdef DEBUG
	 		debug(i, program, ptr, cells, jmp);
		#endif

		i++;
	}
	printf("%c", '\n');
	stack_destroy(stk);
	free(cells);
}

int valid_syntax(const char *program)
{
	/* checks if nested brackets are well formed */
	int nested_depth = 0;
	unsigned i;
	unsigned len = strlen(program);
	for (i = 0; i < len; i++)
	{
		bfuck_t cmd = interpret_cmd(program[i]);
		if (cmd == LEFT_BRACKET)
			nested_depth++;
		else if (cmd == RIGHT_BRACKET)
			nested_depth--;
	}
	return (nested_depth == 0);
}

/* main */

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: %s %s\n", argv[0], "filename");
		return 0;
	}
	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		perror("Could not open file.\n");
		return 1;
	}
	char program[1000] = "";
	while (fscanf(file, "%[^\n]\n", program))
	{
		if (valid_syntax(program))
			run_program(program);
		else
			printf("%s\n", "Syntax error.");
		if (feof(file))
			break;
	}
	fclose(file);
	return 0;
}

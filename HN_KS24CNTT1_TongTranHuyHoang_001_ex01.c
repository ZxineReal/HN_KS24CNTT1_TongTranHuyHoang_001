#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Operation {
    char action[MAX];
    char value[MAX];
} Operation;

typedef struct Stack {
    Operation *operation;
    int capacity;
    int top;
} Stack;

char str[MAX];
int index = 0;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Stack overflow!\n");
        return NULL;
    }
    stack->operation = (Operation*)malloc(sizeof(Operation) * capacity);
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

Operation addOperation() {
    Operation operation;
    printf("Moi ban nhap hanh dong:\n");
    fgets(operation.action, MAX, stdin);
    operation.action[strcspn(operation.action, "\n")] = '\0';

    printf("Moi ban nhap ki tu:\n");
    fgets(operation.value, MAX, stdin);
    operation.value[strcspn(operation.value, "\n")] = '\0';
    if (strlen(operation.value) != 1) {
        printf("Chi duoc them 1 ky tu!\n");
        return;
    }
    return operation;
}

void push(Stack* stack, Operation operation) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow!\n");
        return;
    }
    stack->top++;
    stack->operation[stack->top] = operation;
}

int isEmpty(Stack* stack) {
    if (stack->top == -1) {
        return 1;
    }
    return 0;
}

Operation pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        return;
    }
    return stack->operation[stack->top--];
}

Operation peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        return;
    }
    return stack->operation[stack->top];
}

int main() {
    Stack* UNDO = createStack(MAX);
    Stack* REDO = createStack(MAX);
    int choice;

    do {
        printf("---TEXT EDITOR---\n");
        printf("1. INSERT\n");
        printf("2. UNDO\n");
        printf("3. REDO\n");
        printf("4. HIEN THI\n");
        printf("5. THOAT\n");
        printf("Lua chon cua ban:\n");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                Operation operation = addOperation();
                push(UNDO, operation);
                str[index] = operation.value[0];
                index++;
                break;
            case 2:
                if (isEmpty(UNDO)) {
                    printf("UNDO stack isEmpty!\n");
                    break;
                }
                Operation currentUndo = pop(UNDO);
                push(REDO, currentUndo);
                index--;
                str[index] = "";
                break;
            case 3:
                if (isEmpty(REDO)) {
                    printf("REDO stack isEmpty!\n");
                    break;
                }
                Operation currentRedo = pop(REDO);
                push(UNDO, currentRedo);
                str[index] = currentRedo.value[0];
                index++;
                break;
            case 4:
                if (index == 0) {
                    printf("Van ban hien khong co ki tu nao!\n");
                    break;
                }
                for (int i = 0; i < index; i++) {
                    printf("%c", str[i]);
                }
                printf("\n");
                break;
            case 5:
                return 0;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 5);
    return 0;
}
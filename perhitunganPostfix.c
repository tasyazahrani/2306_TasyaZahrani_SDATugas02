#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 100

// -------------------- STACK MENGGUNAKAN ARRAY --------------------
typedef struct {
    int data[MAX_SIZE];
    int top;
} IntArrayStack;

void initIntArrayStack(IntArrayStack *s) {
    s->top = -1;
}

bool isArrayStackEmpty(IntArrayStack *s) {
    return (s->top == -1);
}

bool isArrayStackFull(IntArrayStack *s) {
    return (s->top == MAX_SIZE - 1);
}

void pushIntToArrayStack(IntArrayStack *s, int value) {
    if (isArrayStackFull(s)) {
        printf("Stack array penuh!\n");
        return;
    }
    s->data[++(s->top)] = value;
}

int popIntFromArrayStack(IntArrayStack *s) {
    if (isArrayStackEmpty(s)) {
        printf("Stack array kosong!\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// -------------------- STACK MENGGUNAKAN LINKED LIST --------------------
typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} IntLinkedListStack;

void initLinkedListStack(IntLinkedListStack *s) {
    s->top = NULL;
}

bool isLinkedListStackEmpty(IntLinkedListStack *s) {
    return (s->top == NULL);
}

void pushIntToLinkedListStack(IntLinkedListStack *s, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Heap penuh, tidak bisa push!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

int popIntFromLinkedListStack(IntLinkedListStack *s) {
    if (isLinkedListStackEmpty(s)) {
        printf("Stack linked list kosong!\n");
        exit(1);
    }
    Node *temp = s->top;
    int popped = temp->data;
    s->top = temp->next;
    free(temp);
    return popped;
}

// -------------------- EVALUASI POSTFIX --------------------
int evaluatePostfixArray(char postfix[]) {
    IntArrayStack valueStack;
    initIntArrayStack(&valueStack);
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        
        if (isdigit(c)) {
            pushIntToArrayStack(&valueStack, c - '0');
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            int val2 = popIntFromArrayStack(&valueStack);
            int val1 = popIntFromArrayStack(&valueStack);
            switch (c) {
                case '+': pushIntToArrayStack(&valueStack, val1 + val2); break;
                case '-': pushIntToArrayStack(&valueStack, val1 - val2); break;
                case '*': pushIntToArrayStack(&valueStack, val1 * val2); break;
                case '/': 
                    if (val2 == 0) {
                        printf("Error: Pembagian dengan nol!\n");
                        exit(1);
                    }
                    pushIntToArrayStack(&valueStack, val1 / val2);
                    break;
                case '^': pushIntToArrayStack(&valueStack, (int)pow(val1, val2)); break;
            }
        }
    }
    
    return popIntFromArrayStack(&valueStack);
}

int evaluatePostfixLinkedList(char postfix[]) {
    IntLinkedListStack valueStack;
    initLinkedListStack(&valueStack);
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        
        if (isdigit(c)) {
            pushIntToLinkedListStack(&valueStack, c - '0');
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            int val2 = popIntFromLinkedListStack(&valueStack);
            int val1 = popIntFromLinkedListStack(&valueStack);
            switch (c) {
                case '+': pushIntToLinkedListStack(&valueStack, val1 + val2); break;
                case '-': pushIntToLinkedListStack(&valueStack, val1 - val2); break;
                case '*': pushIntToLinkedListStack(&valueStack, val1 * val2); break;
                case '/': 
                    if (val2 == 0) {
                        printf("Error: Pembagian dengan nol!\n");
                        exit(1);
                    }
                    pushIntToLinkedListStack(&valueStack, val1 / val2);
                    break;
                case '^': pushIntToLinkedListStack(&valueStack, (int)pow(val1, val2)); break;
            }
        }
    }
    
    return popIntFromLinkedListStack(&valueStack);
}

// -------------------- MAIN PROGRAM --------------------
int main() {
    char expression[MAX_SIZE];
    
    printf("\n=== EVALUATOR EKSPRESI POSTFIX ===\n");
    printf("Masukkan ekspresi postfix: ");
    fgets(expression, MAX_SIZE, stdin);
    
    // Hapus newline jika ada
    size_t len = strlen(expression);
    if (len > 0 && expression[len-1] == '\n') {
        expression[len-1] = '\0';
    }
    
    int resultArray = evaluatePostfixArray(expression);
    int resultLinkedList = evaluatePostfixLinkedList(expression);
    
    printf("\n=== HASIL PERHITUNGAN ===\n");
    printf("Menggunakan Array Stack    : %d\n", resultArray);
    printf("Menggunakan Linked List    : %d\n", resultLinkedList);
    
    return 0;
}

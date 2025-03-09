#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 100

// STACK BERBASIS LINKED LIST 
// Struktur node untuk implementasi linked list
typedef struct StackNode {
    char data;
    struct StackNode* next;
} StackNode;

// Struktur stack menggunakan linked list
typedef struct {
    StackNode* top;
} LinkedListStack;

// Inisialisasi stack linked list
void initLinkedListStack(LinkedListStack* s) {
    s->top = NULL;
}

// Memeriksa apakah stack linked list kosong
bool isLinkedListStackEmpty(LinkedListStack* s) {
    return (s->top == NULL);
}

// Memasukkan karakter ke stack linked list
void pushToLinkedListStack(LinkedListStack* s, char value) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Alokasi memori gagal!\n");
        exit(1);
    }
    
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

// Mengeluarkan karakter dari stack linked list
char popFromLinkedListStack(LinkedListStack* s) {
    if (isLinkedListStackEmpty(s)) {
        printf("Stack kosong!\n");
        return '\0';
    }
    
    StackNode* temp = s->top;
    char value = temp->data;
    
    s->top = s->top->next;
    free(temp);
    
    return value;
}

// Melihat karakter teratas dari stack linked list
char peekLinkedListStack(LinkedListStack* s) {
    if (isLinkedListStackEmpty(s))
        return '\0';
    
    return s->top->data;
}

// Membebaskan semua memori yang dialokasikan untuk stack linked list
void freeLinkedListStack(LinkedListStack* s) {
    StackNode* current = s->top;
    StackNode* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    s->top = NULL;
}

// Mendapatkan preseden dari operator
int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

// Memeriksa apakah ekspresi tanda kurung seimbang
bool areParenthesesBalanced(char expression[]) {
    LinkedListStack s;
    initLinkedListStack(&s);
    
    for (int i = 0; expression[i] != '\0'; i++) {
        // Jika karakter saat ini adalah tanda kurung buka, masukkan ke stack
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[') {
            pushToLinkedListStack(&s, expression[i]);
        }
        // Jika karakter saat ini adalah tanda kurung tutup
        else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']') {
            // Jika stack kosong, tidak ada tanda kurung buka yang cocok
            if (isLinkedListStackEmpty(&s)) {
                freeLinkedListStack(&s);
                return false;
            }
            
            // Memeriksa apakah tanda kurung tutup cocok dengan yang di atas stack
            char topChar = popFromLinkedListStack(&s);
            bool isMatching = false;
            
            if ((expression[i] == ')' && topChar == '(') || 
                (expression[i] == '}' && topChar == '{') || 
                (expression[i] == ']' && topChar == '[')) {
                isMatching = true;
            }
            
            if (!isMatching) {
                freeLinkedListStack(&s);
                return false;
            }
        }
    }
    
    // Jika stack kosong, semua tanda kurung telah cocok
    bool result = isLinkedListStackEmpty(&s);
    freeLinkedListStack(&s);
    return result;
}

// Fungsi untuk mengkonversi ekspresi infix ke postfix
void infixToPostfix(char infix[], char postfix[]) {
    LinkedListStack stack;
    initLinkedListStack(&stack);
    
    int i = 0; // indeks untuk infix
    int j = 0; // indeks untuk postfix
    
    while (infix[i] != '\0') {
        char c = infix[i];
        
        // Jika karakter adalah operand (huruf/angka), tambahkan ke output
        if (isalnum(c)) {
            postfix[j++] = c;
        }
        // Jika karakter adalah tanda kurung buka, masukkan ke stack
        else if (c == '(') {
            pushToLinkedListStack(&stack, c);
        }
        // Jika karakter adalah tanda kurung tutup, keluarkan dan tambahkan ke output sampai tanda kurung buka yang cocok
        else if (c == ')') {
            char stackTop;
            while (!isLinkedListStackEmpty(&stack)) {
                stackTop = peekLinkedListStack(&stack);
                if (stackTop == '(')
                    break;
                
                postfix[j++] = popFromLinkedListStack(&stack);
            }
            
            // Keluarkan tanda kurung buka
            if (!isLinkedListStackEmpty(&stack)) {
                popFromLinkedListStack(&stack); // Hapus '(' dari stack
            }
        }
        // Jika karakter adalah operator
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            char stackTop;
            // Keluarkan operator dengan preseden yang lebih tinggi atau sama dan tambahkan ke output
            while (!isLinkedListStackEmpty(&stack)) {
                stackTop = peekLinkedListStack(&stack);
                if (stackTop == '(' || getPrecedence(c) > getPrecedence(stackTop))
                    break;
                
                postfix[j++] = popFromLinkedListStack(&stack);
            }
            
            // Masukkan operator saat ini
            pushToLinkedListStack(&stack, c);
        }
        
        i++;
    }
    
    // Keluarkan semua operator yang tersisa dari stack dan tambahkan ke output
    char stackTop;
    while (!isLinkedListStackEmpty(&stack)) {
        stackTop = popFromLinkedListStack(&stack);
        if (stackTop == '(') {
            printf("Ekspresi tidak valid: Tanda kurung tidak cocok\n");
            exit(1);
        }
        postfix[j++] = stackTop;
    }
    
    // Null terminate ekspresi postfix
    postfix[j] = '\0';
    
    // Bebaskan semua memori yang dialokasikan untuk stack
    freeLinkedListStack(&stack);
}

int main() {
    char expression[MAX_SIZE];
    char postfix[MAX_SIZE];
    
    printf("\n=== KONVERTER INFIX KE POSTFIX ===\n");
    printf("Masukkan ekspresi infix: ");
    fgets(expression, MAX_SIZE, stdin);
    
    // Hapus karakter newline jika ada
    size_t len = strlen(expression);
    if (len > 0 && expression[len-1] == '\n') {
        expression[len-1] = '\0';
    }
    
    // Periksa apakah tanda kurung seimbang
    if (!areParenthesesBalanced(expression)) {
        printf("Error: Ekspresi memiliki tanda kurung yang tidak seimbang!\n");
        return 1;
    }
    
    infixToPostfix(expression, postfix);
    printf("Ekspresi postfix: %s\n", postfix);
    
    return 0;
}
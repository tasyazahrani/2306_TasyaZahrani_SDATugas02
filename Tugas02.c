#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 100

// STACK BERBASIS ARRAY
// Struktur stack menggunakan array
typedef struct {
    char data[MAX_SIZE];
    int top;
} CharArrayStack;

// Struktur stack integer untuk evaluasi postfix
typedef struct {
    int data[MAX_SIZE];
    int top;
} IntArrayStack;

// Inisialisasi stack array karakter
void initCharArrayStack(CharArrayStack *s) {
    s->top = -1;
}

// Inisialisasi stack array integer
void initIntArrayStack(IntArrayStack *s) {
    s->top = -1;
}

// Memeriksa apakah stack array kosong
bool isArrayStackEmpty(void *s, bool isInt) {
    if (isInt)
        return (((IntArrayStack*)s)->top == -1);
    else
        return (((CharArrayStack*)s)->top == -1);
}

// Memeriksa apakah stack array penuh
bool isArrayStackFull(void *s, bool isInt) {
    if (isInt)
        return (((IntArrayStack*)s)->top == MAX_SIZE - 1);
    else
        return (((CharArrayStack*)s)->top == MAX_SIZE - 1);
}

// Memasukkan karakter ke stack array karakter
void pushCharToArrayStack(CharArrayStack *s, char c) {
    if (isArrayStackFull(s, false)) {
        printf("Stack penuh!\n");
        return;
    }
    s->data[++(s->top)] = c;
}

// Memasukkan integer ke stack array integer
void pushIntToArrayStack(IntArrayStack *s, int value) {
    if (isArrayStackFull(s, true)) {
        printf("Stack penuh!\n");
        return;
    }
    s->data[++(s->top)] = value;
}

// Mengeluarkan karakter dari stack array karakter
char popCharFromArrayStack(CharArrayStack *s) {
    if (isArrayStackEmpty(s, false)) {
        printf("Stack kosong!\n");
        return '\0';
    }
    return s->data[(s->top)--];
}

// Mengeluarkan integer dari stack array integer
int popIntFromArrayStack(IntArrayStack *s) {
    if (isArrayStackEmpty(s, true)) {
        printf("Stack kosong!\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// Melihat karakter teratas pada stack
char peekCharArrayStack(CharArrayStack *s) {
    if (isArrayStackEmpty(s, false))
        return '\0';
    return s->data[s->top];
}

// STACK MENGGUNAKAN LINKED LIST 
// Struktur node untuk implementasi linked list
typedef struct StackNode {
    union {
        char charData;
        int intData;
    } data;
    struct StackNode* next;
} StackNode;

// Struktur stack menggunakan linked list
typedef struct {
    StackNode* top;
    bool isInt; // true jika stack menyimpan int, false jika menyimpan char
} LinkedListStack;

// STACK MENGGUNAKAN LINKED LIST
typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} IntLinkedListStack;

void initLinkedListStack(LinkedListStack* s, bool isInt) {
    s->top = NULL;
    s->isInt = isInt;
}

void initIntLinkedListStack(IntLinkedListStack *s) {
    s->top = NULL;
}

bool isLinkedListStackEmpty(LinkedListStack* s) {
    return (s->top == NULL);
}

bool isIntLinkedListStackEmpty(IntLinkedListStack *s) {
    return (s->top == NULL);
}

// Memasukkan elemen ke stack linked list
void pushToLinkedListStack(LinkedListStack* s, void* value) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Alokasi memori gagal!\n");
        exit(1);
    }
    
    if (s->isInt)
        newNode->data.intData = *((int*)value);
    else
        newNode->data.charData = *((char*)value);
    
    newNode->next = s->top;
    s->top = newNode;
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

// Mengeluarkan elemen dari stack linked list
void* popFromLinkedListStack(LinkedListStack* s, void* result) {
    if (isLinkedListStackEmpty(s)) {
        printf("Stack kosong!\n");
        return NULL;
    }
    
    StackNode* temp = s->top;
    
    if (s->isInt)
        *((int*)result) = temp->data.intData;
    else
        *((char*)result) = temp->data.charData;
    
    s->top = s->top->next;
    free(temp);
    
    return result;
}

int popIntFromLinkedListStack(IntLinkedListStack *s) {
    if (isIntLinkedListStackEmpty(s)) {
        printf("Stack linked list kosong!\n");
        exit(1);
    }
    Node *temp = s->top;
    int popped = temp->data;
    s->top = temp->next;
    free(temp);
    return popped;
}

// Melihat elemen teratas dari stack linked list
void* peekLinkedListStack(LinkedListStack* s, void* result) {
    if (isLinkedListStackEmpty(s))
        return NULL;
    
    if (s->isInt)
        *((int*)result) = s->top->data.intData;
    else
        *((char*)result) = s->top->data.charData;
    
    return result;
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

// PROBLEM 1: TANDA KURUNG SEIMBANG 
// Memeriksa apakah pasangan tanda kurung cocok
bool isMatchingPair(char character1, char character2) {
    if (character1 == '(' && character2 == ')')
        return true;
    else if (character1 == '{' && character2 == '}')
        return true;
    else if (character1 == '[' && character2 == ']')
        return true;
    else
        return false;
}

// Memeriksa apakah ekspresi tanda kurung seimbang
bool areParenthesesBalanced(char expression[]) {
    CharArrayStack s;
    initCharArrayStack(&s);
    
    for (int i = 0; expression[i] != '\0'; i++) {
        // Jika karakter saat ini adalah tanda kurung buka, masukkan ke stack
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[') {
            pushCharToArrayStack(&s, expression[i]);
        }
        // Jika karakter saat ini adalah tanda kurung tutup
        else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']') {
            // Jika stack kosong, tidak ada tanda kurung buka yang cocok
            if (isArrayStackEmpty(&s, false)) {
                return false;
            }
            
            // Memeriksa apakah tanda kurung tutup cocok dengan yang di atas stack
            char topChar = popCharFromArrayStack(&s);
            if (!isMatchingPair(topChar, expression[i])) {
                return false;
            }
        }
    }
    
    // Jika stack kosong, semua tanda kurung telah cocok
    return isArrayStackEmpty(&s, false);
}

// PROBLEM 2: KONVERSI INFIX KE POSTFIX
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

// Fungsi untuk mengkonversi ekspresi infix ke postfix
void infixToPostfix(char infix[], char postfix[]) {
    LinkedListStack stack;
    initLinkedListStack(&stack, false);
    
    int i = 0; 
    int j = 0; 
    
    while (infix[i] != '\0') {
        char c = infix[i];
        
        // Jika karakter adalah operand (huruf/angka), tambahkan ke output
        if (isalnum(c)) {
            postfix[j++] = c;
        }
        // Jika karakter adalah tanda kurung buka, masukkan ke stack
        else if (c == '(') {
            pushToLinkedListStack(&stack, &c);
        }
        // Jika karakter adalah tanda kurung tutup, keluarkan dan tambahkan ke output sampai tanda kurung buka yang cocok
        else if (c == ')') {
            char stackTop;
            while (!isLinkedListStackEmpty(&stack)) {
                peekLinkedListStack(&stack, &stackTop);
                if (stackTop == '(')
                    break;
                
                popFromLinkedListStack(&stack, &stackTop);
                postfix[j++] = stackTop;
            }
            
            // Keluarkan tanda kurung buka
            if (!isLinkedListStackEmpty(&stack)) {
                popFromLinkedListStack(&stack, &stackTop); // Hapus '(' dari stack
            }
        }
        // Jika karakter adalah operator
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            char stackTop;
            // Keluarkan operator dengan preseden yang lebih tinggi atau sama dan tambahkan ke output
            while (!isLinkedListStackEmpty(&stack)) {
                peekLinkedListStack(&stack, &stackTop);
                if (stackTop == '(' || getPrecedence(c) > getPrecedence(stackTop))
                    break;
                
                popFromLinkedListStack(&stack, &stackTop);
                postfix[j++] = stackTop;
            }
            
            // Masukkan operator saat ini
            pushToLinkedListStack(&stack, &c);
        }
        
        i++;
    }
    
    // Keluarkan semua operator yang tersisa dari stack dan tambahkan ke output
    char stackTop;
    while (!isLinkedListStackEmpty(&stack)) {
        popFromLinkedListStack(&stack, &stackTop);
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

// PROBLEM 3: PERHITUNGAN EKSPRESI POSTFIX
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
    initIntLinkedListStack(&valueStack);
    
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

// Function to use both array and linked list implementations
int evaluatePostfix(char postfix[]) {
    int resultArray = evaluatePostfixArray(postfix);
    int resultLinkedList = evaluatePostfixLinkedList(postfix);
    
    printf("\n=== HASIL PERHITUNGAN ===\n");
    printf("Menggunakan Array Stack    : %d\n", resultArray);
    printf("Menggunakan Linked List    : %d\n", resultLinkedList);
    
    return resultArray; // Return the array implementation result for compatibility
}

// Fungsi untuk memeriksa apakah ekspresi postfix hanya berisi angka dan operator
bool isValidPostfixForEvaluation(char postfix[]) {
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (!isdigit(postfix[i]) && 
            postfix[i] != '+' && 
            postfix[i] != '-' && 
            postfix[i] != '*' && 
            postfix[i] != '/' && 
            postfix[i] != '^') {
            return false;
        }
    }
    return true;
}

int main() {
    int choice;
    char expression[MAX_SIZE];
    char postfix[MAX_SIZE];
    char input[MAX_SIZE];
    
    do {
        printf("\n===== MENU OPERASI STACK =====\n");
        printf("1. Periksa Keseimbangan Tanda Kurung\n");
        printf("2. Konversi Infix ke Postfix dan Hitung Hasil\n");
        printf("3. Keluar\n");
        printf("Pilih menu (1-3): ");
        
        // Membaca input sebagai string terlebih dahulu
        if (fgets(input, MAX_SIZE, stdin) == NULL) {
            printf("Error membaca input!\n");
            continue;
        }
        
        // Validasi input - pastikan hanya berisi digit
        bool validInput = true;
        for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++) {
            if (!isdigit(input[i])) {
                validInput = false;
                break;
            }
        }
        
        if (!validInput || sscanf(input, "%d", &choice) != 1) {
            printf("Pilihan tidak valid! Silakan coba lagi.\n");
            continue; // Kembali ke awal loop
        }
        
        switch(choice) {
            case 1:
                printf("\n===== PEMERIKSA KESEIMBANGAN TANDA KURUNG =====\n");
                printf("Masukkan ekspresi dengan tanda kurung: ");
                fgets(expression, MAX_SIZE, stdin);
                
                // Hapus karakter newline jika ada
                size_t len = strlen(expression);
                if (len > 0 && expression[len-1] == '\n') {
                    expression[len-1] = '\0';
                }
                
                if (areParenthesesBalanced(expression)) {
                    printf("Ekspresi memiliki tanda kurung yang seimbang.\n");
                } else {
                    printf("Ekspresi TIDAK memiliki tanda kurung yang seimbang.\n");
                }
                break;
                
            case 2:
                printf("\n===== KONVERSI INFIX KE POSTFIX DAN HITUNG HASIL =====\n");
                printf("Masukkan ekspresi infix (contoh: 3+5*2): ");
                fgets(expression, MAX_SIZE, stdin);
                
                // Hapus karakter newline jika ada
                len = strlen(expression);
                if (len > 0 && expression[len-1] == '\n') {
                    expression[len-1] = '\0';
                }
                
                infixToPostfix(expression, postfix);
                printf("Ekspresi postfix: %s\n", postfix);
                
                // Cek apakah ekspresi hanya mengandung angka dan operator
                // untuk dapat dievaluasi
                if (isValidPostfixForEvaluation(postfix)) {
                    int result = evaluatePostfix(postfix);
                    printf("Hasil dari perhitungan postfix: %d\n", result);
                } else {
                    printf("Ekspresi postfix mengandung variabel atau simbol yang tidak dapat dievaluasi.\n");
                    printf("Hanya ekspresi dengan angka (0-9) dan operator yang dapat dihitung.\n");
                }
                break;
                
            case 3:
                printf("Keluar dari program...\n");
                break;
                
            default:
                printf("Pilihan tidak valid! Silakan coba lagi.\n");
        }
    } while (choice != 3);
    
    return 0;
}
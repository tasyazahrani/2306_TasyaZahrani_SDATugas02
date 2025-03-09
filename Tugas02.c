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

// STACK BERBASIS LINKED LIST 

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

// Inisialisasi stack linked list
void initLinkedListStack(LinkedListStack* s, bool isInt) {
    s->top = NULL;
    s->isInt = isInt;
}

// Memeriksa apakah stack linked list kosong
bool isLinkedListStackEmpty(LinkedListStack* s) {
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

// TUGAS 1: TANDA KURUNG SEIMBANG 
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

// TUGAS 2: INFIX KE POSTFIX

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

// TUGAS 3: EVALUASI POSTFIX

// Fungsi untuk mengevaluasi ekspresi postfix
int evaluatePostfix(char postfix[]) {
    IntArrayStack valueStack;
    LinkedListStack operatorStack;
    
    initIntArrayStack(&valueStack);
    initLinkedListStack(&operatorStack, false);
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        
        // Jika karakter adalah digit, masukkan nilainya ke stack
        if (isdigit(c)) {
            pushIntToArrayStack(&valueStack, c - '0'); // Konversi char ke int
        }
        // Jika karakter adalah operand (huruf), kita akan menganggap nilainya 1 untuk kesederhanaan
        else if (isalpha(c)) {
            pushIntToArrayStack(&valueStack, 1); // Anggap nilai 1 untuk variabel
        }
        // Jika karakter adalah operator
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            // Simpan dulu operator dalam stack linked list (untuk demonstrasi)
            pushToLinkedListStack(&operatorStack, &c);
            char operator;
            popFromLinkedListStack(&operatorStack, &operator);
            
            // Dapatkan dua operand
            int val2 = popIntFromArrayStack(&valueStack);
            int val1 = popIntFromArrayStack(&valueStack);
            
            switch (operator) {
                case '+':
                    pushIntToArrayStack(&valueStack, val1 + val2);
                    break;
                case '-':
                    pushIntToArrayStack(&valueStack, val1 - val2);
                    break;
                case '*':
                    pushIntToArrayStack(&valueStack, val1 * val2);
                    break;
                case '/':
                    if (val2 == 0) {
                        printf("Error: Pembagian dengan nol!\n");
                        exit(1);
                    }
                    pushIntToArrayStack(&valueStack, val1 / val2);
                    break;
                case '^':
                    pushIntToArrayStack(&valueStack, (int)pow(val1, val2));
                    break;
            }
        }
        // Abaikan spasi dan karakter lainnya
        else if (c != ' ') {
            printf("Karakter tidak valid dalam ekspresi: %c\n", c);
            exit(1);
        }
    }
    
    // Hasil akhir seharusnya menjadi satu-satunya nilai yang tersisa di stack
    int result = popIntFromArrayStack(&valueStack);
    
    // Periksa apakah stack kosong (ekspresi valid)
    if (!isArrayStackEmpty(&valueStack, true)) {
        printf("Error: Ekspresi tidak valid (terlalu banyak operand)\n");
        exit(1);
    }
    
    // Bebaskan stack linked list
    freeLinkedListStack(&operatorStack);
    
    return result;
}

int main() {
    int choice;
    char expression[MAX_SIZE];
    char postfix[MAX_SIZE];
    char input[MAX_SIZE];
    
    do {
        printf("\n===== MENU OPERASI STACK =====\n");
        printf("1. Periksa Keseimbangan Tanda Kurung\n");
        printf("2. Konversi Infix ke Postfix\n");
        printf("3. Evaluasi Ekspresi Postfix\n");
        printf("4. Keluar\n");
        printf("Pilih menu (1-4): ");
        
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
                printf("\n--- PEMERIKSA KESEIMBANGAN TANDA KURUNG ---\n");
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
                printf("\n--- KONVERTER INFIX KE POSTFIX ---\n");
                printf("Masukkan ekspresi infix: ");
                fgets(expression, MAX_SIZE, stdin);
                
                // Hapus karakter newline jika ada
                len = strlen(expression);
                if (len > 0 && expression[len-1] == '\n') {
                    expression[len-1] = '\0';
                }
                
                infixToPostfix(expression, postfix);
                printf("Ekspresi postfix: %s\n", postfix);
                break;
                
            case 3:
                printf("\n--- EVALUATOR EKSPRESI POSTFIX ---\n");
                printf("Masukkan ekspresi postfix: ");
                fgets(expression, MAX_SIZE, stdin);
                
                // Hapus karakter newline jika ada
                len = strlen(expression);
                if (len > 0 && expression[len-1] == '\n') {
                    expression[len-1] = '\0';
                }
                
                int result = evaluatePostfix(expression);
                printf("Hasil dari ekspresi postfix: %d\n", result);
                break;
                
            case 4:
                printf("Keluar dari program...\n");
                break;
                
            default:
                printf("Pilihan tidak valid! Silakan coba lagi.\n");
        }
    } while (choice != 4);
    
    return 0;
}
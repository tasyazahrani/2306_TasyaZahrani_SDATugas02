#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 100

//  STACK BERBASIS ARRAY 

// Struktur stack integer untuk evaluasi postfix
typedef struct {
    int data[MAX_SIZE];
    int top;
} IntArrayStack;

// Inisialisasi stack array integer
void initIntArrayStack(IntArrayStack *s) {
    s->top = -1;
}

// Memeriksa apakah stack array kosong
bool isArrayStackEmpty(IntArrayStack *s) {
    return (s->top == -1);
}

// Memeriksa apakah stack array penuh
bool isArrayStackFull(IntArrayStack *s) {
    return (s->top == MAX_SIZE - 1);
}

// Memasukkan integer ke stack array integer
void pushIntToArrayStack(IntArrayStack *s, int value) {
    if (isArrayStackFull(s)) {
        printf("Stack penuh!\n");
        return;
    }
    s->data[++(s->top)] = value;
}

// Mengeluarkan integer dari stack array integer
int popIntFromArrayStack(IntArrayStack *s) {
    if (isArrayStackEmpty(s)) {
        printf("Stack kosong!\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// Fungsi untuk mengevaluasi ekspresi postfix
int evaluatePostfix(char postfix[]) {
    IntArrayStack valueStack;
    initIntArrayStack(&valueStack);
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        
        // Jika karakter adalah digit, masukkan nilainya ke stack
        if (isdigit(c)) {
            pushIntToArrayStack(&valueStack, c - '0'); // Konversi char ke int
        }
        // Jika karakter adalah operand (huruf), kita akan menganggap nilainya 1 untuk kesederhanaan
        else if (isalpha(c)) {
            pushIntToArrayStack(&valueStack, 1); 
        }
        // Jika karakter adalah operator
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            // Dapatkan dua operand
            int val2 = popIntFromArrayStack(&valueStack);
            int val1 = popIntFromArrayStack(&valueStack);
            
            // Lakukan operasi
            switch (c) {
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
    if (!isArrayStackEmpty(&valueStack)) {
        printf("Error: Ekspresi tidak valid (terlalu banyak operand)\n");
        exit(1);
    }
    
    return result;
}

int main() {
    char expression[MAX_SIZE];
    
    printf("\n=== EVALUATOR EKSPRESI POSTFIX ===\n");
    printf("Masukkan ekspresi postfix: ");
    fgets(expression, MAX_SIZE, stdin);
    
    // Hapus karakter newline jika ada
    size_t len = strlen(expression);
    if (len > 0 && expression[len-1] == '\n') {
        expression[len-1] = '\0';
    }
    
    int result = evaluatePostfix(expression);
    printf("Hasil dari ekspresi postfix: %d\n", result);
    
    return 0;
}
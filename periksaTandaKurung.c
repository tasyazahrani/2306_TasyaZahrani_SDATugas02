#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 100

// STACK BERBASIS ARRAY 

// Struktur stack menggunakan array
typedef struct {
    char data[MAX_SIZE];
    int top;
} CharArrayStack;

// Inisialisasi stack array karakter
void initCharArrayStack(CharArrayStack *s) {
    s->top = -1;
}

// Memeriksa apakah stack array kosong
bool isArrayStackEmpty(CharArrayStack *s) {
    return (s->top == -1);
}

// Memeriksa apakah stack array penuh
bool isArrayStackFull(CharArrayStack *s) {
    return (s->top == MAX_SIZE - 1);
}

// Memasukkan karakter ke stack array karakter
void pushCharToArrayStack(CharArrayStack *s, char c) {
    if (isArrayStackFull(s)) {
        printf("Stack penuh!\n");
        return;
    }
    s->data[++(s->top)] = c;
}

// Mengeluarkan karakter dari stack array karakter
char popCharFromArrayStack(CharArrayStack *s) {
    if (isArrayStackEmpty(s)) {
        printf("Stack kosong!\n");
        return '\0';
    }
    return s->data[(s->top)--];
}

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
            if (isArrayStackEmpty(&s)) {
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
    return isArrayStackEmpty(&s);
}

int main() {
    char expression[MAX_SIZE];
    
    printf("\n=== PEMERIKSA KESEIMBANGAN TANDA KURUNG ===\n");
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
    
    return 0;
}
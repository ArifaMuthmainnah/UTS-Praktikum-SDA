#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Struktur Stack untuk menyimpan string
typedef struct {
    char data[MAX_SIZE][MAX_SIZE]; // Stack menyimpan string
    int top;
} Stack;

// Fungsi untuk inisialisasi stack
void initStack(Stack *s) {
    s->top = -1;
}

// Fungsi untuk mengecek apakah stack kosong
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Fungsi untuk mengecek apakah stack penuh
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Fungsi untuk menambahkan elemen ke stack (string)
void push(Stack *s, char item[]) {
    if (isFull(s)) {
        printf("Stack penuh!\n");
        return;
    }
    strcpy(s->data[++(s->top)], item);
}

// Fungsi untuk menghapus elemen dari stack (string)
char* pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack kosong!\n");
        return "";
    }
    return s->data[(s->top)--];
}

// Fungsi untuk melihat elemen teratas stack (string)
char* peek(Stack *s) {
    if (isEmpty(s)) {
        return "";
    }
    return s->data[s->top];
}

// Fungsi untuk mengecek apakah karakter adalah operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Fungsi untuk menentukan prioritas operator
int precedence(char ch) {
    switch (ch) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

// Fungsi untuk mengubah ekspresi Infix ke Postfix
void infixToPostfix(char infix[], char postfix[]) {
    Stack s;
    initStack(&s);
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            char temp[2] = {ch, '\0'};
            push(&s, temp);
        } else if (ch == ')') {
            while (!isEmpty(&s) && strcmp(peek(&s), "(") != 0) {
                postfix[j++] = pop(&s)[0];
            }
            pop(&s); // Hapus '(' dari stack
        } else if (isOperator(ch)) {
            while (!isEmpty(&s) && precedence(peek(&s)[0]) >= precedence(ch)) {
                postfix[j++] = pop(&s)[0];
            }
            char temp[2] = {ch, '\0'};
            push(&s, temp);
        }
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s)[0];
    }

    postfix[j] = '\0';
}

// Fungsi untuk membalik string
void reverseString(char str[]) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// Fungsi utama
int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE], prefix[MAX_SIZE];
    int choice;

    printf("Konversi Ekspresi Aritmatika\n");
    printf("1. Infix ke Postfix\n");
    printf("2. Postfix ke Infix\n");
    printf("3. Infix ke Prefix\n");
    printf("4. Prefix ke Infix\n");
    printf("5. Prefix ke Postfix\n");
    printf("6. Postfix ke Prefix\n");
    printf("Pilih menu: ");
    scanf("%d", &choice);
    getchar(); // Untuk menghapus newline setelah scanf

    switch (choice) {
        case 1:
            printf("Masukkan ekspresi Infix: ");
            fgets(infix, MAX_SIZE, stdin);
            infix[strlen(infix) - 1] = '\0'; // Menghapus newline dari fgets
            infixToPostfix(infix, postfix);
            printf("Hasil Postfix: %s\n", postfix);
            break;
        
        default:
            printf("Pilihan tidak valid!\n");
    }

    return 0;
}

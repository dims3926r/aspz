#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define DATE_LEN 15
#define ADDR_LEN 100

typedef struct {
    char name[NAME_LEN];
    char birth_date[DATE_LEN];
    char address[ADDR_LEN];
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("База даних заповнена.\n");
        return;
    }
    printf("Введіть ім'я: ");
    scanf(" %[^\n]", students[student_count].name);
    printf("Введіть дату народження (ДД.ММ.РРРР): ");
    scanf(" %[^\n]", students[student_count].birth_date);
    printf("Введіть адресу: ");
    scanf(" %[^\n]", students[student_count].address);
    student_count++;
    printf("Студента додано!\n");
}

void edit_student() {
    char name[NAME_LEN];
    printf("Введіть ім'я студента для редагування: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Введіть нове ім'я: ");
            scanf(" %[^\n]", students[i].name);
            printf("Введіть нову дату народження: ");
            scanf(" %[^\n]", students[i].birth_date);
            printf("Введіть нову адресу: ");
            scanf(" %[^\n]", students[i].address);
            printf("Дані оновлено!\n");
            return;
        }
    }
    printf("Студента не знайдено.\n");
}

void delete_student() {
    char name[NAME_LEN];
    printf("Введіть ім'я студента для видалення: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("Студента видалено!\n");
            return;
        }
    }
    printf("Студента не знайдено.\n");
}

void search_student() {
    char query[NAME_LEN];
    printf("Введіть ім'я для пошуку: ");
    scanf(" %[^\n]", query);
    printf("Результати пошуку:\n");
    for (int i = 0; i < student_count; i++) {
        if (strstr(students[i].name, query) != NULL) {
            printf("Ім'я: %s, Дата народження: %s, Адреса: %s\n", 
                   students[i].name, students[i].birth_date, students[i].address);
        }
    }
}

void list_students() {
    if (student_count == 0) {
        printf("База даних порожня.\n");
        return;
    }
    printf("Список студентів:\n");
    for (int i = 0; i < student_count; i++) {
        printf("%d. Ім'я: %s, Дата народження: %s, Адреса: %s\n", 
               i + 1, students[i].name, students[i].birth_date, students[i].address);
    }
}

int main() {
    int choice;
    do {
        printf("\nМеню:\n");
        printf("1. Додати студента\n");
        printf("2. Редагувати студента\n");
        printf("3. Видалити студента\n");
        printf("4. Пошук студента\n");
        printf("5. Показати всіх студентів\n");
        printf("0. Вийти\n");
        printf("Ваш вибір: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_student(); break;
            case 2: edit_student(); break;
            case 3: delete_student(); break;
            case 4: search_student(); break;
            case 5: list_students(); break;
            case 0: printf("Вихід...\n"); break;
            default: printf("Невірний вибір!\n");
        }
    } while (choice != 0);

    return 0;
}

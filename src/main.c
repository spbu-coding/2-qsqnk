#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*void bubble_sort(long long int* array_of_numbers, int array_length) {
    for (int i = 0; i < array_length - 1; i++) {
        for (int j = 0; j < array_length - i - 1; j++) {
            if (array_of_numbers[j] > array_of_numbers[j + 1]) {
                //swap
                array_of_numbers[j] ^= array_of_numbers[j + 1];
                array_of_numbers[j + 1] ^= array_of_numbers[j];
                array_of_numbers[j] ^= array_of_numbers[j + 1];
            }
        }

    }
}*/

extern void bubble_sort(long long int* array_of_numbers, int array_length);

bool check_for_same_arguments(char* first_argument, char* second_argument) {
    if (strlen(first_argument) >= strlen("--to=") && strlen(second_argument) >= strlen("--to=")) {
        //проверка на --to=
        if (strncmp(first_argument, second_argument, 5) == 0) {
            return 1;
        }
        //проверка на --from=
        if (strncmp(first_argument, second_argument, 7) == 0) {
            return 1;
        }
    }
    return 0;
}

//does arg contain --from= or --to=
bool is_argument_correct(char* argument) {
    if (strlen(argument) < strlen("--to=")) {
        return 0;
    }
    if (strncmp(argument, "--to=", 5) == 0 || strncmp(argument, "--from=", 7) == 0) {
        return 1;
    }
    return 0;
}

int check_arguments(int count_of_arguments, char** arguments) {
    if (count_of_arguments - 1 < 1) {
        return -1;
    }
    if (count_of_arguments - 1 > 2) {
        return -2;
    }
    if (count_of_arguments - 1 == 2) {
        if (!is_argument_correct(arguments[1]) && !is_argument_correct(arguments[2])) {
            return -4;
        }
        if (check_for_same_arguments(arguments[1], arguments[2])) {
            return -3;
        }
    }
    if (count_of_arguments - 1 == 1) {
        if (!is_argument_correct(arguments[1])) {
            return -4;
        }
    }
    return 0;
}

char* get_type_of_argument(char* argument) {
    if (strncmp(argument, "--to=", 5) == 0) {
        return "--to=";
    }
    return "--from=";
}

void scan_arguments(int count_of_arguments, char** arguments, long long int* from, long long int* to) {
    long long int temp_from = 0;
    long long int temp_to = 0;
    for (int i = 0; i < count_of_arguments; i++) {
        if (is_argument_correct(arguments[i])) {
            if (strcmp(get_type_of_argument(arguments[i]), "--from=") == 0) {
                //+7 = +strlen(--from=)
                if (strtoll(arguments[i] + 7, NULL, 10)) {
                    temp_from = strtoll(arguments[i] + 7, NULL, 10);
                }
            }
            if (strcmp(get_type_of_argument(arguments[i]), "--to=") == 0) {
                //+5 = +strlen(--to=)
                if (strtoll(arguments[i] + 5, NULL, 10)) {
                    temp_to = strtoll(arguments[i] + 5, NULL, 10);
                }
            }

        }
    }
    *from = temp_from;
    *to = temp_to;
}

void read_array(long long int* array, int* count_of_elements) {
    char c;
    int i = 0;
    scanf("%lli%c", &array[i], &c);
    while (c != '\n') {
        i++;
        scanf("%lli%c", &array[i], &c);
    }
    *count_of_elements = i + 1;
}

void distribute_numbers(long long int* array_of_numbers, long long int* small_elements, long long int* normal_elements,
                        int count_of_elements, long long int* big_elements, long long int from, long long int to, int* big_count,
                        int* small_count, int* normal_count) {
    int count_small = 0;
    int count_big = 0;
    int count_normal = 0;
    for (int i = 0; i < count_of_elements; i++) {
        if (array_of_numbers[i] <= from) {
            small_elements[count_small] = array_of_numbers[i];
            count_small++;
        }
        if (array_of_numbers[i] >= to && to != 0) {
            big_elements[count_big] = array_of_numbers[i];
            count_big++;
        }
        if (array_of_numbers[i] > from && (array_of_numbers[i] < to || to == 0)) {
            normal_elements[count_normal] = array_of_numbers[i];
            count_normal++;
        }
    }
    *small_count = count_small;
    *big_count = count_big;
    *normal_count = count_normal;
}

void copy_array(long long int* copy_from, long long int* copy_to, int count_of_elements) {
    for (int i = 0; i < count_of_elements; i++) {
        copy_to[i] = copy_from[i];
    }
}

void numbers_output(long long int* small_elements, int count_small, long long int* big_elements, int count_big) {
    for (int i = 0; i < count_small; i++) {
        fprintf(stdout, "%lli ", small_elements[i]);
    }
    for (int i = 0; i < count_big; i++) {
        fprintf(stderr, "%lli ", big_elements[i]);
    }
}

int main(int argc, char* argv[]) {
    long long int from = 0;
    long long int to = 0;
    long long int* array_of_numbers;
    long long int* small_elements;
    long long int* big_elements;
    long long int* normal_elements;
    long long int* normal_elements_sorted;
    array_of_numbers = (long long int*)malloc(100 * sizeof(long long int));
    small_elements = (long long int*)malloc(100 * sizeof(long long int));
    big_elements = (long long int*)malloc(100 * sizeof(long long int));
    normal_elements = (long long int*)malloc(100 * sizeof(long long int));
    normal_elements_sorted = (long long int*)malloc(100 * sizeof(long long int));
    int count_of_elements = 0;
    int count_of_small_elements = 0;
    int count_of_big_elements = 0;
    int count_of_normal_elements = 0;
    //count of elements changed position after sorting
    int count_of_changed_elements = 0;
    if (check_arguments(argc, argv)) {
        return check_arguments(argc, argv);
    }
    scan_arguments(argc, argv, &from, &to);
    read_array(array_of_numbers, &count_of_elements);
    distribute_numbers(array_of_numbers, small_elements, normal_elements, count_of_elements, big_elements,
                       from, to, &count_of_big_elements, &count_of_small_elements, &count_of_normal_elements);
    copy_array(normal_elements, normal_elements_sorted, count_of_normal_elements);
    bubble_sort(normal_elements_sorted, count_of_normal_elements);
    //counting of elements changed position after sorting
    for (int i = 0; i < count_of_normal_elements; i++) {
        if (normal_elements[i] != normal_elements_sorted[i]) {
            count_of_changed_elements++;
        }
    }
    numbers_output(small_elements, count_of_small_elements, big_elements, count_of_big_elements);
    return count_of_changed_elements;
}
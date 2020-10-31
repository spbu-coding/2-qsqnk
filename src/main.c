#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

extern void bubble_sort(long long int* array_of_numbers, int array_length);

bool check_for_same_arguments(char* first_argument, char* second_argument) {
    if (strlen(first_argument) >= strlen("--to=") && strlen(second_argument) >= strlen("--to=")) {
        if (strncmp(first_argument, second_argument, 5) == 0) {
            return 1;
        }
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

void scan_arguments(int count_of_arguments, char** arguments,
                    long long int* from, long long int* to, bool* is_from, bool* is_to) {
    long long int temp_from = 0;
    long long int temp_to = 0;
    for (int i = 0; i < count_of_arguments; i++) {
        if (is_argument_correct(arguments[i])) {
            if (strcmp(get_type_of_argument(arguments[i]), "--from=") == 0) {
                *is_from = 1;
                //+7 = +strlen(--from=)
                if (strtoll(arguments[i] + 7, NULL, 10)) {
                    temp_from = strtoll(arguments[i] + 7, NULL, 10);
                }
            }
            if (strcmp(get_type_of_argument(arguments[i]), "--to=") == 0) {
                *is_to = 1;
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

void read_array(long long int* array, int* count_of_elements, long long int from,
                long long int to, bool is_from, bool is_to) {
    char c;
    long long int temp_number = 0;
    *count_of_elements = 0;
    do {
        scanf("%lli%c", &temp_number, &c);
        if (temp_number <= from && is_from) {
            fprintf(stdout, "%lli ", temp_number);
        }
        if (temp_number >= to && is_to) {
            fprintf(stderr, "%lli ", temp_number);
        }
        if ((!is_from || temp_number > from) && (!is_to || temp_number < to)) {
            array[*count_of_elements] = temp_number;
            *count_of_elements = *count_of_elements + 1;
        }
    } while (c != '\n');
}

void copy_array(long long int* copy_from, long long int* copy_to, int count_of_elements) {
    for (int i = 0; i < count_of_elements; i++) {
        copy_to[i] = copy_from[i];
    }
}

int count_changed_elements(long long int* first_array, long long int* second_array, int array_length) {
    int result = 0;
    for (int i = 0; i < array_length; i++) {
        if (first_array[i] != second_array[i]) {
            result++;
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    long long int from = 0;
    long long int to = 0;
    long long int* array_of_numbers;
    long long int* array_of_sorted_numbers;
    bool is_from = 0;
    bool is_to = 0;
    array_of_numbers = (long long int*)malloc(100 * sizeof(long long int));
    array_of_sorted_numbers = (long long int*)malloc(100 * sizeof(long long int));
    int count_of_elements = 0;
    if (check_arguments(argc, argv)) {
        return check_arguments(argc, argv);
    }
    scan_arguments(argc, argv, &from, &to, &is_from, &is_to);
    read_array(array_of_numbers, &count_of_elements, from, to, is_from, is_to);
    copy_array(array_of_numbers, array_of_sorted_numbers, count_of_elements);
    bubble_sort(array_of_sorted_numbers, count_of_elements);
    return count_changed_elements(array_of_numbers, array_of_sorted_numbers, count_of_elements);
}
#include <stdio.h>
#include <stdlib.h>

/**
 * TODO:
 * In this file, you will write two functions:
 *
 * 1. reverse_arr: will take in two inputs a char* array and the number of
 * elements in the array. It's responsible for reversing the input array. You
 * should be modifying this array in place. Meaning that you shouldn't returning
 * anything from this function.
 *
 * 2. swap: will take in two elements from the array and swap them. Returns
 * nothing.
 *
 * Example:
 * Given an array ["hello", "my", "name", "is"], after calling reverse_arr
 * will result in ["is", "name", "my", "hello"]
 */

void swap(char** arr, int i, int n) {
    char* temp = arr[i];
    arr[i] = arr[n - i - 1];
    arr[n - i - 1] = temp;
}

void reverse_arr(char** arr, int n) {
    for (int i = 0; i < n/2; i++) {
        swap(arr, i, n);
    }
}

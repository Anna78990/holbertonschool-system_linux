#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

#include <stdio.h>


void bubble_sort(int arr[], int size)
{
    int swap, swapped;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++)
	{
            if (arr[j] > arr[j + 1])
	    {
                swap = arr[j];
		swapped = arr[j + 1];
		arr[j] = swapped;
		arr[j + 1] = swap;
            }
        }
    }
}

int main()
{
    int arr[] = {5, 2, 8, 1, 3};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    bubble_sort(arr, size);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}


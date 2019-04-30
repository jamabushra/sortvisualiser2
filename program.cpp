#include "splashkit.h"

#define NUM_VALS 100

void draw_values(const int values[], int size)
{
    int x = 0;
    int y;
    int rect_height;
    int rect_width = screen_width() / size;

    for (int i = 0; i < size; i++)
    {
        rect_height = values[i];
        y = screen_height() - rect_height;

        fill_rectangle(COLOR_RED, x, y, rect_width, rect_height);
        draw_rectangle(COLOR_WHITE, x, y, rect_width, rect_height);

        x += rect_width;
    }
}

void swap(int &value1, int &value2)
{
    int temporary_position = value1;
    value1 = value2;
    value2 = temporary_position;
}

void draw_sort(int values[], int size)
{
    clear_screen(COLOR_WHITE);
    draw_values(values, size);
    refresh_screen(60);
}
//---------------------------------------------------------------------------------------------------------------------------------------------
//THE TIME COMPLEXITY OF BUBBLE SORT IS O(n^2) (O of n squared)
//Other sorting types that are O(n^2) include Insersion sort and selection sort
void bubble_sort(int values[], int size)
{
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (values[i] > values[i + 1])
            {
                swap(values[i], values[i + 1]);
                draw_sort(values, size);
            }
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//the array ive chosen is merge sort because it runs based on the idea of
//divide and conquer. It does this by diving the array into two parts
//and sorting the two parts separately then merging them. This is much better then
//bubble sort and has a faster run time as n number of values increases
//THE TIME COMPLEXITY OF MERGE SORT IS THE DESIRED O(n log n) (this is how we know its faster, better then bubble sort)

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int values[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp valuesays */
    int L[n1], R[n2];

    /* Copy data to temp valuesays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = values[l + i];
    for (j = 0; j < n2; j++)
        R[j] = values[m + 1 + j];

    /* Merge the temp valuesays back into values[l..r]*/
    i = 0; // Initial index of first subvaluesay
    j = 0; // Initial index of second subvaluesay
    k = l; // Initial index of merged subvaluesay
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            values[k] = L[i];
            i++;
        }
        else
        {
            values[k] = R[j];
            j++;
        }
        draw_sort(values, r);
        k++;
    }

    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1)
    {
        values[k] = L[i];
        i++;
        k++;
        draw_sort(values, r);
    }

    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2)
    {
        values[k] = R[j];
        j++;
        k++;
        draw_sort(values, r);
    }
}

/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void merge_sort(int values[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        merge_sort(values, l, m);
        merge_sort(values, m + 1, r);
        draw_sort(values, r);
        merge(values, l, m, r);
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void random_fill_array(int values[], int size)
{
    for (int i = 0; i < size; i++)
    {
        values[i] = rnd(screen_height()) + 1;
    }
}

void handle_input(int values[], int size)
{
    if (key_typed(R_KEY))
    {
        random_fill_array(values, size);
    }
    else if (key_typed(S_KEY)) //runs a bubble sort
    {
        bubble_sort(values, size);
    }
    else if (key_typed(D_KEY)) //runs another sort algorithm
    {
        merge_sort(values, 0, size - 1);
    }
}

int main()
{
    int values[NUM_VALS];

    open_window("Sort Visualiser", 800, 600);

    random_fill_array(values, NUM_VALS);

    while (not quit_requested())
    {
        process_events();
        handle_input(values, NUM_VALS);

        draw_sort(values, NUM_VALS);
    }

    return 0;
}
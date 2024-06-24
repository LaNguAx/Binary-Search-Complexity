/*
 * Assignment 1
 * 
 * Authors:
 * Itay Andre Aknin
 * Roi Israel Forer
 * 
 * 4/2/2024
 * 
 */

#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

int TOTAL_COMPARISONS = 0;
int Q1_COUNTER_SUM = 0;
int Q2_COUNTER_SUM = 0;
int Q3_COUNTER_SUM = 0;
int comparisons_counter = 0;


int randomNumber() {

    //srand(static_cast<unsigned int>(time(0)));

    // Generate a random number between 1 and 100
    int randomNumber = rand() %20001 - 10000;
    
    return randomNumber;

}


void loadArray(int* arr, int size) {


    for (int i = 0; i < size; i++)
        arr[i] = randomNumber();

}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << std::endl;

}

void merge(int arr[], int const left, int const mid, int const right) {
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    // Create temp arrays
    int* leftArray = new int[subArrayOne],
        * rightArray = new int[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = arr[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = arr[mid + 1 + j];

    int indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into arr[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    // Copy the remaining elements of leftArray[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    // Copy the remaining elements of rightArray[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    // Deallocate memory used for temporary arrays
    delete[] leftArray;
    delete[] rightArray;
}
void mergeSort(int arr[], int const begin, int const end) {
    if (begin >= end)
        return; // Returns recursively

    int mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}


int binarySearch(int* arr, int size, int target) {

    int found = 0;
    int left = 0;
    int right = size - 1;

    // if target is out of range
    if (target < arr[left] || target > arr[right]) return found;

    while (left < right) {

        comparisons_counter++;

        int mid = (left + right) / 2;

        // if its found
        if (arr[left] == target || arr[right] == target || arr[mid] == target) return found = target;

        // target is on the right
        else if (target > arr[mid]) left = mid + 1;
        else if (target < arr[mid]) right = mid - 1;

    }

    return found;
}

// Q1
/* 
   * findSum1 return values *
    
    retVal == 0 -- no number found
    retVal == -1 -- 2 nums from v are sum
    retVal != 0 && retVal!= -1 -- found number
*/
int findSum1(int* v, int* w, int size_v, int size_w, int sum) {

    //check nums in v then find num in w
    // pointer search in v then binary search in w
    
    int* left_v = v;
    int* right_v = v + size_v - 1;

    int foundNumber = 0;

    while (left_v < right_v && foundNumber == 0) {

        int currentSum = *left_v + *right_v;
        
        comparisons_counter++;

        // if the 2 numbers from v add up to sum then return -1 because the algo shouldn't search for a 3rd number
        if (currentSum == sum) return -1;

        // search for foundNumber>0 to add to currentSum
        else if (currentSum < sum) {

            foundNumber = binarySearch(w, size_w, sum-currentSum);

            left_v++;
        }

        // search for foundNumber<0 to add to currentSum
        else if (currentSum > sum) {
            foundNumber = binarySearch(w, size_w, sum - currentSum);
            right_v--;
        }

    }
    return foundNumber;
}

//Q2 -- solution is answer to q1.

//Q3 -- findSum1 with W instead of V.

int main() {

    srand(time(0));

    for (int i = 0; i < 500; i++) {

        int CURRENT_ITERATION_COUNTER = 0;
        int q1_counter = 0;
        int q2_counter = 0;
        int q3_counter = 0;

        // random number between 50-100
        int n = rand() % 51 + 50;
        int v_len = n;
        int w_len = n*n;
        //int w_len = n * n;
        //std::cout << w_len << std::endl;


        int *V = new int[v_len];
        int *W = new int[w_len];
        int s = randomNumber();

        loadArray(V, v_len);
        loadArray(W, w_len);

        mergeSort(V, 0, v_len-1);
        mergeSort(W, 0, w_len-1);
    
        //printArray(V, v_len);
        //printArray(W, w_len);

        std::cout << "*********************************" << std::endl;

        std::cout << "Requested sum is: " << s << std::endl;

        // Q1 
        std::cout << "Q1:" << std::endl;
        int res1 = findSum1(V, W, v_len, w_len, s);
        std::cout << "Found Number is: " << res1 << std::endl;

        CURRENT_ITERATION_COUNTER += comparisons_counter;
        q1_counter = CURRENT_ITERATION_COUNTER;
        Q1_COUNTER_SUM += q1_counter;
        std::cout << "Q1 did: " << q1_counter << " comparisons." << std::endl;

        TOTAL_COMPARISONS += CURRENT_ITERATION_COUNTER;
        CURRENT_ITERATION_COUNTER = 0;

        // Q2
        // since T(findSum) = O(nlogn) = O(n^2logn) --> solution is findSum1.
        std::cout << "Q2:" << std::endl;
        int res2 = findSum1(V, W, v_len, w_len, s);
        std::cout << "Found Number is: " << res2 << std::endl;

        CURRENT_ITERATION_COUNTER += comparisons_counter - q1_counter;
        q2_counter = CURRENT_ITERATION_COUNTER;
        Q2_COUNTER_SUM += q2_counter;

        std::cout << "Q2 did: " << q2_counter << " comparisons." << std::endl;

        TOTAL_COMPARISONS += CURRENT_ITERATION_COUNTER;
        CURRENT_ITERATION_COUNTER = 0;

        //Q3 -- same as findSum1 just send W instead of V --> O(n^2logn)
        std::cout << "Q3:" << std::endl;
        int res3 = findSum1(W,V, w_len, v_len, s);
        std::cout << "Found Number is: " << res3 << std::endl;

        CURRENT_ITERATION_COUNTER += comparisons_counter - (q1_counter + q2_counter);
        q3_counter += CURRENT_ITERATION_COUNTER;
        Q3_COUNTER_SUM += q3_counter;
        std::cout << "Q3 did: " << q3_counter << " comparisons." << std::endl;
   
        TOTAL_COMPARISONS += CURRENT_ITERATION_COUNTER;
        CURRENT_ITERATION_COUNTER = 0;

        delete[]V;
        delete[]W;

        comparisons_counter = 0;

        int CURRENT_ITERATION_COUNTER_SUM = q1_counter + q2_counter + q3_counter;

        std::cout << std::endl;
        std::cout << "ARRAY SIZE(v): " << n << std::endl;
        std::cout << "ARRAY SIZE(w): " << n*n << std::endl;
        std::cout << "THIS ITERATION DID IN TOTAL: " << CURRENT_ITERATION_COUNTER_SUM << " comparisons." << std::endl;    
        std::cout << "*********************************" << std::endl;

    }

    
    // SUMMARY OUTPUT
    std::cout << "****** SUMMARY START ******" << std::endl;

    std::cout << "Q1 -- ON AVERAGE did: " << Q1_COUNTER_SUM/500 << " comparisons." << std::endl;
    std::cout << "Q2 -- ON AVERAGE did: " << Q2_COUNTER_SUM/500 << " comparisons." << std::endl;
    std::cout << "Q3 -- ON AVERAGE did: " << Q3_COUNTER_SUM/500 << " comparisons." << std::endl;

    std::cout << std::endl;

    std::cout << "The program IN TOTAL did: " << TOTAL_COMPARISONS << " comparisons." << std::endl;
    std::cout << "The program ON AVERAGE did: " << TOTAL_COMPARISONS / 500 << " comparisons." << std::endl;

    std::cout << "****** SUMMARY END ******" << std::endl;

    return 0;
}

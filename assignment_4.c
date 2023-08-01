// Kieran Herron
// COP 3502C - 01
// Assignment 4
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated


// extra merge function
void mergefunc(int pData[], int l, int midVal, int r) {
    
    // declarations of helper variables for the merge function
    int i;
    int j;
    int k;
    // clearer to illustrate this way, even if there is a small efficiency loss
    int p;
    int q;
    int index1 = (midVal - l) + 1;
    int index2 = (r - midVal);

    int L[index1];
    int R[index2];
    
    for(i = 0; i < index1; i++) {
        L[i] = pData[l + i];
    }
    for(j = 0; j < index2; j++) {
        L[j] = pData[midVal + 1 + j];
    }

    p = 0;
    q = 0;
    // k and while loop
    k = 1;
    while(p < index1 && q < index2) {
        if(L[p] <= R[q]) {
            pData[k] = L[p];
            p++;
        }
        else {
            pData[k] = R[q];
            q++;
        }
        k++;
    }

    while(p < index1) {
        pData[k] = L[p];
        p++;
        k++;

    }

    while(q < index2) {
        pData[k] = R[q];
        q++;
        k++;
        
    }

}

void mergeSort(int pData[], int l, int r)
{
    int midVal;
    if(l < r) {
        midVal = (1+((r-1)/2));
        mergeSort(pData, l, midVal);
        mergeSort(pData, midVal+1, r);

        mergefunc(pData, l, midVal, r);
    }
}



// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
    // setting key and helper variables
    int key;
    int i;
    int j;

    for(i = 1; i< n; i++) {
        key = pData[i];
        j = (i-1);

    }

    while(j >= 0 && pData[j] > key) {
        pData[j+1] = pData[j];
        j = (j-1);

    }
    pData[j+1] = key;

	
}
// extra swap function, for bubble and selection sort
void swapfunc(int * a1, int * a2) {
    int tempVal = *a1;
    *a1 = *a2;
    *a2 = tempVal;

}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
    int i;
    int j;
    // pseudoboolean swapped
    int swapped;
    // wider loop to check through arrays
    for(i = 0; i < (n-1); i++) {
        swapped = 0;
        // swaps vals if conditions are met
        for(j = 0; j < (n-i -1); j++) {
            if(pData[j] > pData[j+1]) {
                swapfunc(&pData[j], &pData[j+1]);
                swapped = 1;
            }
        }

        if(swapped == 0) {
            break;
        }
    }



	
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated


void selectionSort(int* pData, int n)
{
    int i;
    int j;
    int minimum;

    for(i = 0; i < n-1; i++) {
        minimum = i;
        for(j = i+1; j<n; j++) {
            if(pData[j] < pData[minimum]) {
                minimum = j;
            }
            if(minimum != i) {
                swapfunc(&pData[minimum], &pData[i]);
            }
        }
    }
    
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
        int exitval;
        scanf("%d", exitval);
	}
	
}
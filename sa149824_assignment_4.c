#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// swaps values passed by reference
void swap (int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

// merge function for merge sort below
void merge (int pData[], int l, int m, int r) {
  int i, j, k;
  
  int sizeOne = m - l + 1;
  int sizeTwo = r - m;

  int *arrOne = malloc(sizeof(int) * sizeOne);
  int *arrTwo = malloc(sizeof(int) * sizeTwo);
  
  extraMemoryAllocated += sizeof(int) * sizeOne;
  extraMemoryAllocated += sizeof(int) * sizeTwo;

  for (i = 0; i < sizeOne; i++)
    arrOne[i] = pData[l + i];
  for (i = 0; i < sizeTwo; i++)
    arrTwo[i] = pData[m + 1 + i];

  i = 0;
  j = 0;
  k = l;

  while (i < sizeOne && j < sizeTwo) {
    if (arrOne[i] <= arrTwo[j]) {
      pData[k] = arrOne[i];
      i++;
    }
    else {
      pData[k] = arrTwo[j];
      j++;
    }
    k++;
  }

  while (i < sizeOne) {
    pData[k] = arrOne[i];
    i++;
    k++;
  }

  while (j < sizeTwo) {
    pData[k] = arrTwo[j];
    j++;
    k++;
  }

  free(arrOne);
  free(arrTwo);
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {
	if (l < r) {
    int m = (l + r) / 2;

    mergeSort(pData, l, m);
    mergeSort(pData, m + 1, r);
    merge(pData, l, m, r);
  }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n) {
  int j;
  
	for (int i = 1; i < n; i++) {
    int holdVal = pData[i];
    for (j = i - 1; j >= 0; j--) {
      if (pData[j] > holdVal)
        pData[j + 1] = pData[j];
      else
        break;
    }
    pData[j + 1] = holdVal;
  }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n) {
		for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < n - i - 1; j++) {
        if (pData[j] > pData[j + 1])
          swap(&pData[j], &pData[j+1]);
      }
  }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n) {
  for (int i = 0; i < n - 1; i++) {
    int minVal = i;
    for (int j = i + 1; j < n; j++) {
      if (pData[minVal] > pData[j])
        minVal = j;
    }
    if (minVal != i)
      swap(&pData[i], &pData[minVal]);
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

    int num = 0;
    for (int i = 0;i < dataSz; i++) {
			fscanf(inFile, "%d ", &num);
			int *data = *ppData + i;
			*data = num;
    }
	}

  fclose(inFile);
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
	}
	
}
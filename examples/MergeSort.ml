# This example is yet to be tested

# Merges two subarrays of arr[].
# First subarray is arr[l..m]
# Second subarray is arr[m+1..r]
void merge(Vector<int>[size] arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	# create temp arrays
	Vector<int>[n1] L;
	Vector<int>[n2] R;

	# Copy data to temp arrays L[] and R[]
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	# Merge the temp arrays back into arr[l..r]
	i = 0; # Initial index of first subarray
	j = 0; # Initial index of second subarray
	k = l; # Initial index of merged subarray
	for ( ; i < n1 && j < n2 ; ) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	``` Copy the remaining elements of L[], if there
	are any ```
	for ( ; i < n1 ; ) {
		arr[k] = L[i];
		i++;
		k++;
	}

	``` Copy the remaining elements of R[], if there
	are any ```
	for ( ; j < n2 ; ) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

``` l is for left index and r is right index of the
sub-array of arr to be sorted ```
void mergeSort(Vector<int>[size] arr, int l, int r)
{
	if (l < r) {
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

# UTILITY FUNCTIONS
# Function to print an array
void printArray(Vector<int>[size] A)
{
	int i;
	for (i = 0; i < size; i++)
		print(“”A[i]””);
	print("\n");
}

int main()
{
	int arr_size = 6;
	Vector<int>[arr_size] arr;
	arr[0] = 12;
	arr[1] = 11;
	arr[2] = 13;
	arr[3] = 5;
	arr[4] = 6;
	arr[5] = 7;

	print("Given array is \n");
	printArray(arr); #prints “12 11 13 5 6 7 “

	mergeSort(arr, 0, arr_size - 1);

	print("\nSorted array is \n");
	printArray(arr); #prints “5 6 7 11 12 13 “
	return 0;
}


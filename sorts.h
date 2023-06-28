using namespace std;

template <typename T>
void shellsort(vector<T> &v,int &trocas, int &compar) {

    int h = 1;
    int i, j;

    while (h < v.size()) {
        compar++;
        h = h*3+1;
    }
    compar++;
    while (h > 1) {
        compar++;
        h /= 3;
        for (i = h; i < v.size(); i++) {
            compar++;
            T aux = v[i];
            j = i; 
            while (j >= h && aux < v[j-h]) {
                compar+=2;
                v[j] = v[j-h];
                j -= h;
                trocas++;
            }
            compar+=2;
            v[j] = aux;
        }
        compar++;
    }
    compar++;
}

template<typename T>
void quicksort(vector<T> &v, int began, int end,int &trocas, int &compar)
{
	int i, j, pivo, aux;
	i = began;
	j = end-1;
	pivo = v[(began + end) / 2];
	while(i <= j)
	{
        compar++;
		while(v[i] < pivo && i < end)
		{
            compar+=2;
			i++;
		}
        compar+=2;
		while(v[j] > pivo && j > began)
		{
            compar+=2;
			j--;
		}
        compar+=2;
		if(i <= j)
		{
			aux = v[i];
			v[i] = v[j];
			v[j] = aux;
			i++;
			j--;
            trocas++;
		}
        compar++;
	}
    compar++;
	if(j > began)
		quicksort(v, began, j+1, trocas, compar);
    compar++;
	if(i < end)
		quicksort(v, i, end, trocas, compar);
    compar++;
}

template<typename T>
void merge(vector<T> &v, int p, int q, int r, int &trocas, int &compar) {
  
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++){
    compar++;
    L[i] = v[p + i];
  }
  compar++;
  for (int j = 0; j < n2; j++){
    compar++;
    M[j] = v[q + 1 + j];
  }
  compar++;
  // Maintain current index of sub-vays and main vay
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    compar+=2;
    if (L[i] <= M[j]) {
      v[k] = L[i];
      i++;
      trocas++;
    } else {
      v[k] = M[j];
      j++;
      trocas++;
    }
    compar++;
    k++;
  }
  compar+=2;

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    compar++;
    v[k] = L[i];
    i++;
    k++;
    trocas++;
  }
  compar++;

  while (j < n2) {
    compar++;
    v[k] = M[j];
    j++;
    k++;
    trocas++;
  }
  compar++;
}

template<typename T>
void mergesort(vector<T> &v, int l, int r, int &trocas, int &compar) {
  if (l < r) {
    // m is the point where the vay is divided into two subvays
    int m = l + (r - l) / 2;

    mergesort(v, l, m, trocas, compar);
    mergesort(v, m + 1, r, trocas, compar);

    // Merge the sorted subvays
    merge(v, l, m, r, trocas, compar);
  }
}
template<typename T>
void heapify(vector<T> &v, int n, int i, int &trocas, int &compar) {
  // Find largest among root, left child and right child
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && v[left] > v[largest])
    largest = left;
compar+=2;

  if (right < n && v[right] > v[largest])
    largest = right;
compar+=2;

  // Swap and continue heapifying if root is not largest
  if (largest != i) {
    swap(v[i], v[largest]);
    trocas++;
    heapify(v, n, largest, trocas, compar);
  }
  compar++;
}

// main function to do heap sort
template<typename T>
void heapsort(vector<T> &v, int n, int &trocas, int &compar) {
  // Build max heap
  for (int i = n / 2 - 1; i >= 0; i--){
    compar++;
    heapify(v, n, i, trocas, compar);
  }
  compar++;
  // Heap sort
  for (int i = n - 1; i >= 0; i--) {
    compar++;
    swap(v[0], v[i]);
    trocas++;
    // Heapify root element to get highest element at root again
    heapify(v, i, 0, trocas, compar);
  }
  compar++;
}
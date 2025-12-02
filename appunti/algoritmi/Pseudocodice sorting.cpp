//Pseiudocodice

//SelectionSort
void SelectionSort(int A[n]){
    for (int i = 1; i <n-1; i = i+1){
        m = min(A,i,n);
        if (m!=i) swap(A,i,m);
    }
}

int min (int A[],int i, int n){
    for (int j = i+1; j<n; j = j+1){
        if (A[j]<A[i]) i = j;
    }
    retur i;
}

void swap (int A[], int i, int m){
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}


//InsertionSort

void InsertionSort (int A[n]){
    for (int i = 2; i<n; i = i+1){
        int j = i;
        while (j>1 && A[j] < A[j-1]){
            swap(A,j,j-1);
            j = j-1;
        }
    }
}


//MergeSort
void MergeSort (int A[], int p, int r){
    if (p<r){
        q = ⌊(p + r)/2⌋
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge (A,p,q,r);
    }
}

void Merge (int A[n], int p, int q, int r){
    int B[n];
    i = p;
    j = q+1;
    k = i;
    while (i<= q && j<=r){
        if (A[i]<=A[j]) {
            B[k] = A[i];
            i = i+1;
        } else {
            B[k] A[j];
            j = j+1;
        }
        k = k+1;
    }

    while (i<=q){
        B[k] = A[i];
        k = k+1;
        i = i+1;
    }

    while (j<=r){
        B[k] = A[j];
        k = k+1;
        j = j+1;
    }

    for ( k = 1; k<r-p+1; k = k+1){
        A[p+k-1] = B[k];
    }
}

//QuickSort

void QuickSort (int A[]; int p, int r){
    if (p<r){
        q = partition(A,p,r);
        QuickSort(A,p,q-1);
        QuickSort(A,q+1,r);
    }
}

int partition (int A[], int p, int r){
    int x = A[r];
    i = p-1;
    for (int j = p; j<r-1; j = j+1){
        if (A[j] <= x){
            swap(A,i+1,j);
            i = i+1;
        }
    }
    swap(A,i+1,r);
    return i;
}

int rpatition (int A[], int p, int r){
    i = random(p,r);
    swap(A,i,r);
    retur partition(A,p,r);
}


//CountingSort

void CountingSort (int A[]){
    a = min(A);
    b = max(A);
    k = b-a+1;
    int B[k];

    for (int i = 1; i<k; i = i+1){
        B[i] = 0;
    }

    for (int i = 1; i<n; i = i+1){
        B[A[i]-a+1] = B[A[i]-a+1]+1;
    }

    j = 1;
    for (int i = 1; i<k; i = i+1){
        while (B[i]>0){
            A[j] = i+a-1;
            B[i] = B[i]-1;
            j = j+1;
        } 
    }
}



//Versione con chiavi e dati

struct cell{
    key chiave;
    data d;
}

void CountingSortK (cell A[n]){
    a = minkey(A);
    b = maxkey(A);
    k = b-a+1;
    int B[k];
    int C[n];

    for (int i = 1; i<k; i = i+1){
        B[i] = 0;
    }

    for (int i = 1; i<n; i = i+1){
        B[A[i].chiave-a+1] = B[A[i].chiave-a+1]+1;
    }

    for (int i = 2; i<k; i = i+1){
        B[i] = B[i]+B[i-1];
    }

    for (int i = n; i>1; i = i-1){
        C[B[A[i].chiave-a+1]] = A[i];
        B[A[i].chiave-a+1] = B[A[i].chiave-a+1]-1;
    }

    for (int i = 1; i<n; i = i+1;){
        A[i] = C[i];
    }
}
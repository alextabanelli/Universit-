package algorithm.sorting;

/**
 * This class contains various sorting algorithms
 */
public class Sorting {

    /**
     * Sorts the specified array into ascending numerical order in &Theta;(n<sup>2</sup>)
     * <p>
     * Implements the selectionsort algorithm.
     * <ul>
     * <li> Worst/Average/Best-case cost: &Theta;(n<sup>2</sup>)
     * </ul>
     * @param A the array to be sorted
     */
    private static void swap(int A[],int i, int j){
        int tmp;
        tmp = A[i];
        A[i]=A[j];
        A[j]=tmp;
    } 

    public static void selectionsort(int A[]) {
        for (int i = 0;i<A.length-1;i++){
            int m = i;
            for (int j = i+1;j<A.length;j++){
                if (A[j]<A[m]) m = j;
            }
            if (m != i) swap(A,i,m);
        }
    }

    /**
     * Sorts the specified array into ascending numerical order in O(n<sup>2</sup>)
     * <p>
     * Implements the insertionsort algorithm.
     * <ul>
     * <li> Worst/Average-case cost: &Theta;(n<sup>2</sup>)
     * <li> Best-case cost: &Theta;(n)
     * </ul>
     * @param A the array to be sorted
     */
    public static void insertionsort(int A[]) {
        for (int i = 1; i < A.length; i++){
            int j = i;
            while (j>0 && A[j]<A[j-1]){
                swap(A, j, j-1);
                j = j-1;
            }
        }
    }

    /**
     * Sorts the specified array into ascending numerical order in &Theta;(nlogn)
     * <p>
     * Implements the mergesort algorithm.
     * <ul>
     * <li> Worst/Average/Best-case cost: &Theta;(nlogn)
     * </ul>
     * @param A the array to be sorted
     */

     public static void merge(int A[], int p, int q, int r) {
        int B[] = new int[r-p+1];
        int i = p;
        int j = q;
        int k = 0;
        while (i<=q && j<=r){
            if (A[i]<=A[j]) {
                B[k] = A[i];
                i = i+1;
            }else{
                B[k] = A[j];
                j = j+1;
            }
            k = k+1;
        }
        while (i<=q){
            B[k-1] = A[i];
            k++;
            i++;
        }

        while (j<=r){
            B[k-1] = A[j];
            k++;
            j++;
        }

        for (k = 0; k<r-p+1;k++){
            A[p+k] = B[k];
        }

     }

     public static void mergesort1(int A[], int p, int r) {
        if(p<r){
            int q = (p+r)/2;
            mergesort1(A, p, q);
            mergesort1(A, q+1, r);
            merge(A,p,q,r);
        }
     }


    public static void mergesort(int A[]) {
        mergesort1(A,0,A.length-1);
    }

    /**
     * Sorts the specified array into ascending numerical order in O(n<sup>2</sup>) and O(nlogn) on the average
     * <p>
     * Implements the quicksort algorithm.
     * <ul>
     * <li> Worst-case cost:  &Theta;(n<sup>2</sup>)
     * <li> Average/Best-case cost: &Theta;(nlogn)
     * </ul>
     * @param A the array to be sorted
     */

    public static int partition (int A[], int p, int r){
        int x = A[r];
        int i = p-1;
        for (int j = p;j<r-1;j++){
            if (A[i]<= x) {
                swap(A, i+1, j);
                i++;
            } 
        }
        swap(A, i+1, r);
        return i+1;
    }


    

    public static void quicksort1(int A[], int p, int r) {
        if (p<r){
            int q = partition(A, p, r);
            quicksort1(A, p, q-1);
            quicksort1(A, q+1, r);
        }
    }

    public static void quicksort(int A[]) {
        quicksort1(A,0,A.length);
    }


    /**
     * Sorts the specified array into ascending numerical order in &Theta;(n+k)
     * <p>
     * Implements the countingsort algrithm.
     * <ul>
     * <li> Worst/Average/Best-case cost: &Theta;(n+k), where k = max(<code>A</code>)-min(<code>A</code>)+1
     * </ul>
     * @param A the array to be sorted
     */
    public static void countingsort(int A[]) {
        int a = A[0];
        int b = A[0];
        for (int i = 0;i<A.length;i++){
            if (A[i]<a) a = A[i];
            if (A[i]>b) a = A[i];
        }
        int k = b-a+1;
        int B[] = new int[k];
        for (int i = 0;i<k;i++){
            B[i] = 0;
        }
        for (int i = 1;i<A.length;i++){
            B[A[i] - a + 1] = B[A[i] - a + 1] + 1;
        }
        int j = 1;
        for (int i = 0;i<k;i++){
            while (B[i]>0){
                A[j] = i+a-1;
                B[i] = B[i]-1;
                j = j+1;
            }
        }
    }
            
}

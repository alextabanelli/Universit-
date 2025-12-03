package algorithm.sorting;

/**
 * This class contains various sorting algorithms
 */
public class Sorting {
	/**
     * Sorts the specified array according to the ordering induced by the compareTo() method in &Theta;(n<sup>2</sup>)
     * <p>
     * Implements the selectionsort algorithm.
     * <ul>
     * <li> Worst/Average/Best-case cost: &Theta;(n<sup>2</sup>)
     * </ul>
     * @param A the array to be sorted
     * @param <T> class of the object in the array
     */
	
	private static <T extends Comparable<T>> void swap(T A[], int i, int j)
	{
		T temp;
		
		temp=A[i];
		A[i]=A[j];
		A[j]=temp;
	}
	
    public static <T extends Comparable<T>> void selectionsort(T A[])
    {
    	int m;

        for(int c=0;c<A.length-1;c++)
        {
            m=c;

            for(int c2=c+1;c2<A.length;c2++)
            {
                if(A[c2].compareTo(A[m])<0)
                m=c2;
            }

            if(m!=c)
            swap(A,c,m);
        }
    }
	
    /**
     * Sorts the specified array into ascending numerical order in &Theta;(n<sup>2</sup>)
     * <p>
     * Implements the selectionsort algorithm.
     * <ul>
     * <li> Worst/Average/Best-case cost: &Theta;(n<sup>2</sup>)
     * </ul>
     * @param A the array to be sorted
     */

     private static void swap(int A[], int i, int j)
     {
         int temp;
 
         temp=A[i];
         A[i]=A[j];
         A[j]=temp;
     }

    public static void selectionsort(int A[])
    {
        int m;

        for(int c=0;c<A.length-1;c++)
        {
            m=c;

            for(int c2=c+1;c2<A.length;c2++)
            {
                if(A[c2]<A[m])
                m=c2;
            }

            if(m!=c)
            swap(A,c,m);
        }
    }
    
    /**
     * Sorts the specified array according to the ordering induced by the compareTo() method in O(n<sup>2</sup>)
     * <p>
     * Implements the insertionsort algorithm.
     * <ul>
     * <li> Worst/Average-case cost: &Theta;(n<sup>2</sup>)
     * <li> Best-case cost: &Theta;(n)
     * </ul>
     * @param A the array to be sorted
     * @param <T> class of the object in the array
     */
    public static <T extends Comparable<T>> void insertionsort(T A[])
    {
    	int c2;

        for(int c=1;c<A.length;c++)
        {
            c2=c;

            while(c2>0 && A[c2].compareTo(A[c2-1])<0)
            {
                swap(A,c2,c2-1);
                c2--;
            }
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
    public static void insertionsort(int A[])
    {
        int c2;

        for(int c=1;c<A.length;c++)
        {
            c2=c;

            while(c2>0 && A[c2]<A[c2-1])
            {
                swap(A,c2,c2-1);
                c2--;
            }
        }
    }
    
    /**
     * Sorts the specified array according to the ordering induced by the compareTo() method in &Theta;(nlogn)
     * <P>
     * Implements the mergesort algorithm.
     * <ul>
     * <li> Worst/Average/Best-case cost: &Theta;(nlogn)
     * </ul>
     * @param A the array to be sorted
     * @param <T> class of the object in the array
     */
    public static <T extends Comparable<T>> void mergesort(T A[])
    {
    	mergesort1(A,0,A.length-1);
    }
    
    private static <T extends Comparable<T>> void mergesort1(T A[], int p, int r)
    {
    	int q;

        if(p<r)
        {
            q=p+(r-p)/2;
            mergesort1(A,p,q);
            mergesort1(A,q+1,r);
            merge(A,p,q,r);
        }
    }
    
    private static <T extends Comparable<T>> void merge(T A[], int p ,int q, int r)
    {
        int c,c2,k;
        T B[];
        
        @SuppressWarnings("unchecked")
        T[] temp = (T[]) new Comparable[r-p+1];
        B=temp;

        c=p;
        c2=q+1;
        k=0;

        while(c<=q && c2<=r)
        {
            if(A[c].compareTo(A[c2])<=0)
            {
                B[k]=A[c];
                c++;
            }
            else
            {
                B[k]=A[c2];
                c2++;
            }

            k++;
        }

        while(c<=q)
        {
            B[k]=A[c];
            k++;
            c++;
        }

        while(c2<=r)
        {
            B[k]=A[c2];
            k++;
            c2++;
        }

        for(k=0;k<r-p+1;k++)
        {
            A[p+k]=B[k];
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
    public static void mergesort(int A[])
    {
        mergesort1(A,0,A.length-1);
    }

    private static void mergesort1(int A[], int p, int r)
    {
        int q;

        if(p<r)
        {
            q=p+(r-p)/2;
            mergesort1(A,p,q);
            mergesort1(A,q+1,r);
            merge(A,p,q,r);
        }
    }

    private static void merge(int A[], int p ,int q, int r)
    {
        int B[]=new int[r-p+1];
        int c,c2,k;

        c=p;
        c2=q+1;
        k=0;

        while(c<=q && c2<=r)
        {
            if(A[c]<=A[c2])
            {
                B[k]=A[c];
                c++;
            }
            else
            {
                B[k]=A[c2];
                c2++;
            }

            k++;
        }

        while(c<=q)
        {
            B[k]=A[c];
            k++;
            c++;
        }

        while(c2<=r)
        {
            B[k]=A[c2];
            k++;
            c2++;
        }

        for(k=0;k<r-p+1;k++)
        {
            A[p+k]=B[k];
        }
    }
    
    /**
     * Sorts the specified array according to the ordering induced by the compareTo() method in O(n<sup>2</sup>) and O(nlogn) on the average
     * <p>
     * Implements the quicksort algorithm.
     * <ul>
     * <li> Worst-case cost:  &Theta;(n<sup>2</sup>)
     * <li> Average/Best-case cost: &Theta;(nlogn)
     * </ul>
     * @param A the array to be sorted
     * @param <T> class of the object in the array
     */
    public static <T extends Comparable<T>> void quicksort(T A[])
    {
    	quicksort1(A,0,A.length-1);
    }
    
    private static <T extends Comparable<T>> void quicksort1(T A[], int p, int r)
    {
    	int q;

        if(p<r)
        {
            q=partition(A,p,r);
            quicksort1(A,p,q-1);
            quicksort1(A,q+1,r);
        }
    }
    
    private static <T extends Comparable<T>> int partition(T A[], int p, int r)
    {
        T x=A[r];
        int c=p;

        for(int c2=p;c2<r;c2++)
        {
            if(A[c2].compareTo(x)<=0)
            {
                swap(A,c,c2);
                c++;
            }
        }

        swap(A,c,r);

        return c;
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
    public static void quicksort(int A[])
    {
        quicksort1(A,0,A.length-1);
    }

    private static void quicksort1(int A[],int p, int r)
    {
        int q;

        if(p<r)
        {
            q=partition(A,p,r);
            quicksort1(A,p,q-1);
            quicksort1(A,q+1,r);
        }
    }

    private static int partition(int A[], int p, int r)
    {
        int x=A[r],c=p;

        for(int c2=p;c2<r;c2++)
        {
            if(A[c2]<=x)
            {
                swap(A,c,c2);
                c++;
            }
        }

        swap(A,c,r);

        return c;
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

     private static int min(int A[])
     {
        int m=A[0];

        for(int c=0;c<A.length;c++)
        {
            if(A[c]<m)
            m=A[c];
        }

        return m;
     }

     private static int max(int A[])
     {
        int m=A[0];

        for(int c=0;c<A.length;c++)
        {
            if(A[c]>m)
            m=A[c];
        }

        return m;
     }

    public static void countingsort(int A[])
    {
        int a=min(A),b=max(A),k=b-a+1,c2=0;

        int B[]=new int[k];

        for(int c=0;c<k;c++)
        {
            B[c]=0;
        }

        for(int c=0;c<A.length;c++)
        {
            B[A[c]-a]++;
        }

        for(int c=0;c<k;c++)
        {
            while(B[c]>0)
            {
                A[c2]=c+a;
                B[c]--;
                c2++;
            }
        }
    }
    
    /**
	* Sorts the specified array according to the ordering induced by the compareTo() method in O(n log n)
	* using the heapsort algorithm.
	* <ul>
	* <li> Worst-case: &Theta;(n log n)
	* <li> Best-case: &Theta;(n)		
	* </ul>
	* @param A the array to be sorted
	* @param <T> class of the object in the array
	*/
	public static <T extends Comparable<T>> void heapsort(T A[])
	{
		heapify(A, A.length - 1, 0);
		for (int c = (A.length - 1); c > 0; c--) {
			T k = findmax(A);
			deletemax(A, c);
			A[c] = k;
		}
	}
	
	/**
	* Transforms the array A with n elements in an arrayheap.
	* It proceeds recursively by fist creating sub arrayheaps rooted at index i
	*/	
	private static <T extends Comparable<T>> void heapify(T A[], int n, int i)
	{
		if (i >= n) return;
		heapify(A, n, left(i));
		heapify(A, n, right(i));
		fixheap(A, n, i);
	}
	
	/**
	* Returns the index of the left son
	*/	
	private static int left(int i)
	{
		return ( 2*i + 1 );
	}

	/**
	* Returns the index of the right son
	*/	
	private static int right(int i)
	{
		return ( 2*i + 2 );
	}
		
	/**
	* Fix the sub arrayheap rooted at position i of a the arrayheap A of length c, 
	* assuming only the root can be ill-placed
	*/		
	private static <T extends Comparable<T>> void fixheap(T A[], int c, int i)
	{
		int l = left(i), r = right(i);
		if (l > c) return;
		int max = l;
		if (r <= c && A[l].compareTo(A[r]) < 0)
			max = r;
		if (A[i].compareTo(A[max]) < 0)
		{
			swap(A, i, max);
			fixheap(A, c, max);
		}
	}
	
	/**
	* Returns the maximal element from an arrayheap A
	*/	
	private static <T> T findmax(T A[])
	{
		return A[0];
	}

	/**
	* Removes the maximal element in an arrayheap A of length c
	*/		
	private static <T extends Comparable<T>> void deletemax(T A[], int c)
	{
		if (c <= 0) return;
		A[0] = A[c];
		c--;
		fixheap(A, c, 0);
	}
}

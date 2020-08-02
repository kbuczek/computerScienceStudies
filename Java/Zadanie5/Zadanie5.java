import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.RecursiveTask;

public class Zadanie5 {

    public static void printArray(int arr[])
    {
        int n = arr.length;
        for (int i=0; i<n; ++i)
            System.out.print(arr[i]+" ");
        System.out.println();
    }

    public static void main(String[] args) {

        ForkJoinPool pool = new ForkJoinPool();
        int arr1[] = {10, 7, 8, 9, 1, 5, 4, 3, 12, 15, 43, 2, 13, 61, 14, 20};
        int arr2[] = {10, 7, 8, 9, 1, 5, 4, 3, 12, 15, 43, 2, 13, 61, 14, 20};
        int n = arr1.length-1;

        long startTime = System.nanoTime();
        QuickSortClass q1 = new QuickSortClass();
        q1.quickSort(arr1, 0, n);
        long estimatedTime = System.nanoTime();
        System.out.println("Tablica postorowana przez 1 proces w czasie: " + (estimatedTime-startTime) + " ns");
        printArray(arr1);

        startTime = System.nanoTime();
        QuickSortClass q2 = new QuickSortClass(arr2, 0, n);
        pool.invoke(q2);
        estimatedTime = System.nanoTime();
        System.out.println("Tablica posortowana wątkami w czasie: " + (estimatedTime-startTime) + " ns");
        printArray(arr2);
        pool.shutdown();

    }
}

class QuickSortClass extends RecursiveAction
{
    public static int numThreads = Runtime.getRuntime().availableProcessors();
    public static int count = 0;
    int  arr[];
    int low;
    int high;

    public QuickSortClass(int[] arr, int low, int high) {
        this.arr = arr;
        this.low = low;
        this.high = high;
    }

    public QuickSortClass(){

    }


    int partition(int arr[], int low, int high) {
        int pivot = arr[high]; //ustawiamy pivot na koniec
        int i = (low - 1); // index of smaller element
        for (int j = low; j < high; j++) {
            // If current element is smaller than the pivot
            if (arr[j] < pivot) {
                i++; //miejsca mniejsze od pivot zaczynaja sie od poczatku listy
                // swap arr[i] and arr[j], i - miejsce z wart. mniejsza od pivot
                swap(arr, i, j);
            }
        }

        // swap arr[i+1] and arr[high] (or pivot)
        swap(arr, i+1, high);

        return i + 1; //miejsce po liczbach mniejszych od pivot (miejsce pivot)
    }

    void quickSort(int arr[], int low, int high) {
        if (low < high) //sa przynajmniej 2 elementy do posortowania
        {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    @Override
    protected void compute() {
        if (low < high) {
            int pi = partition(arr, low, high);
            QuickSortClass t1 = new QuickSortClass(arr, low, pi - 1);
            QuickSortClass t2 = new QuickSortClass(arr, pi + 1, high);
            t1.fork();
            t2.compute();
            t1.join();
        }

    }

    void swap(int[] a, int p, int r) {
        int t = a[p];
        a[p] = a[r];
        a[r] = t;
    }
}

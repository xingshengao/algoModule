### 手撕快排
* l>=r 直接return
* 选中基准arr[l]
* 先-j再+i
* 循环内如果i<j交换ij
* 循环外交换l,i
* 递归子区间[l, i - 1] [i + 1, r]
```java
public class Main {
    public static void qsort(int[] arr, int l, int r) {
        if (l >= r) return;
        int key = arr[l];
        int i = l, j = r;
        while (i < j) {
            while (i < j && arr[j] >= key) --j; // 先j后i
            while (i < j && arr[i] <= key) ++i;

            // swap(arr[i], arr[j]);
            if (i < j) {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
        // swap(arr[i], arr[l]);
        int temp = arr[i];
        arr[i] = arr[l];
        arr[l] = temp;
        qsort(arr, l, i - 1);
        qsort(arr, i + 1, r);
    }
        

    public static void main(String[] args) {
        int[] arr = new int[]{1, 2, 3, 444, 555, 1, 22, 333, 44, 54};
        qsort(arr, 0, arr.length - 1);
        System.out.println(Arrays.toString(arr));
    }

}
```
package array;
import java.util.ArrayList;

public class ArrayListTest {
    public void main(String[] args) {
        
    }

    public void testArrayList() {
        ArrayList<Integer> arr = new ArrayList<Integer>(10);

        for (int idx = 0; idx < 10; idx++) {
            arr.add(idx);
        }

        for (int item : arr) {
            System.out.println(item);
        }
    }
}
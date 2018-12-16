
import java.util.Arrays;

public class UnionFindTree{
    private int[] itemID;

    
    //constructor
    public UnionFindTree( int size){
        itemID =  new int[size];
        for(int i = 0; i< size; i++)
        {
            itemID[i] = i;
        }
    }
    
    public boolean quickFind( int p, int q)
    {
        if(rootof(p) == rootof(q))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    public void quickUnion( int p, int q){
        itemID[q] = p;
    }
    
    public void printItemID(){
        System.out.println(Arrays.toString(itemID));
    }
    
    public int rootof( int x)
    {
        while(itemID[x] != x){
            x = itemID[x];
        }
        return x;
    }
   public static void main(String[] args)
   {
       UnionFindTree u1 = new UnionFindTree(10);
       u1.quickUnion(1,2);
       u1.quickUnion(2,3);
       u1.quickUnion(3,4);

       u1.quickUnion(5,6);
       u1.quickUnion(6,7);
       u1.quickUnion(7,8);
        
       System.out.println("1:4"+u1.quickFind(1,4));
       System.out.println("5:8"+u1.quickFind(5,8));
       System.out.println("1:2"+u1.quickFind(1,5));
       
       u1.printItemID();
       
       u1.quickUnion(4,5);
       System.out.println("1:2"+u1.quickFind(1,5));
   }
}
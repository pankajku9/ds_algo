import java.util.Arrays;

public class UnionFind{
    private int[] itemID;

    
    //constructor
    public UnionFind( int size){
        itemID =  new int[size];
        for(int i = 0; i< size; i++)
        {
            itemID[i] = i;
        }
    }
    
    public boolean quickFind( int p, int q)
    {
        if(itemID[p] == itemID[q]){
            return true;
        }
        else
        {
            return false;
        }
    }
    
    public void quickUnion( int p, int q){
        
        int idOfP = itemID[p];
        int idOfQ = itemID[q];
        
        for(int i = 0; i < itemID.length; i++)
        {
            if(itemID[i] == idOfQ)
            {
                itemID[i] = idOfP;
            }
        }
    }
    
    public void printItemID(){
        System.out.println(Arrays.toString(itemID));
    }
   public static void main(String[] args)
   {
       UnionFind u1 = new UnionFind(10);
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
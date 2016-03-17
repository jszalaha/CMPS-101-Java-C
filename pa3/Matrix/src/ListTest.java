/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 3
 */
//-----------------------------------------------------------------------------
//  ListTest.java
//  A test client for the List ADT. The correct output is given below.
//-----------------------------------------------------------------------------

public class ListTest{
   public static void main(String[] args){
      List A = new List();
      List B = new List();
      
      // Tester object using the same toString() method as the 
      // Entry object in Matrix.java
      class OBJ{
	   	   private int index;
	   	   private double value;
	   	   
	   	   OBJ(int i, double v){
	   		   index = i;
	   		   value = v;
	   	   }
	   	   public String toString() {
	   		   String S;
	   		   S = "(" + this.index + "," + this.value + ")";        	
	   		   return S;
	   	   }
      }      
      
      for(int i=1; i<=10; i++){
    	 OBJ obj = new OBJ(i, i-2);
         A.append(obj);
         B.prepend(obj);
      }
      System.out.println(A);
      System.out.println(B);
      
      for(A.moveTo(0); A.getIndex()>=0; A.moveNext()){
         System.out.print(A.getElement()+" ");
      }
      System.out.println();
      for(B.moveTo(B.length()-1); B.getIndex()>=0; B.movePrev()){
         System.out.print(B.getElement()+" ");
      }
      System.out.println();
      
      System.out.println(A.equals(B));
      
      A.moveTo(2);
      A.insertBefore(new OBJ(1, -1));
      A.moveTo(8);
      A.insertAfter(new OBJ(0,-2));
      A.moveTo(5);
      A.delete();
      System.out.println(A);
      A.clear();
      System.out.println(A.length());
      
      
   }	   
   
}

// Output of this program:
// (1,-1.0) (2,0.0) (3,1.0) (4,2.0) (5,3.0) (6,4.0) (7,5.0) (8,6.0) (9,7.0) (10,8.0)
// (10,8.0) (9,7.0) (8,6.0) (7,5.0) (6,4.0) (5,3.0) 4,2.0) (3,1.0) (2,0.0) (1,-1.0)
// (1,-1.0) (2,0.0) (3,1.0) (4,2.0) (5,3.0) (6,4.0) (7,5.0) (8,6.0) (9,7.0) (10,8.0)
// (1,-1.0) (2,0.0) (3,1.0) (4,2.0) (5,3.0) (6,4.0) (7,5.0) (8,6.0) (9,7.0) (10,8.0)
// false
// (1,-1.0) (2,0.0) (1,-1.0) (3,1.0) (4,2.0) (6,4.0) (7,5.0) (0,-2.0) (8,6.0) (9,7.0) (10,8.0)
// 0
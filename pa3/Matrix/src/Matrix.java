/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 3
 */
//-----------------------------------------------------------------------------
//  Matrix.java
//-----------------------------------------------------------------------------
public class Matrix {
    
    private List[] row;
    private int size;
    
    // Constructor
    Matrix(int n) {
        if( n < 1 ) {
            throw new RuntimeException(
                    "Matrix Error: new matrix must be at least 1 x 1");
        }
        size = n+1;
        row = new List[size];
        for(int i = 0; i < size; i++){
            this.row[i] = new List();
        }        
    }
    // Makes a new n+1 x n+1 zero Matrix. pre: n>=1
    // matrix is n+1 x n+1 because row[0] will always be ignored
    
    // Access functions //////////////////////////////////////////////////////
    int getSize() {
        return this.size;
    }
    // Returns n, the number of rows and columns of this Matrix
    int getNNZ() {
        int count = 0;
        for(int i = 1; i < this.getSize(); i++){
        	if(this.row[i].length() > 0){
        		count += this.row[i].length();
        	}
        }
        return count;
    }
    // Returns the number of non-zero entries in this Matrix
    public boolean equals(Object obj) {
        boolean flag = true;
        Matrix M = (Matrix)obj;
        if (this.getSize() == M.getSize()){
            int i = 1;
            while(flag && i < this.getSize()){
                if(this.row[i].equals(M.row[i])){
                    i++;
                }else { flag = false; }
            }
        }else {flag = false;}
        return flag;
    }
    // overrides Object's equals() method
    
    // Manipulation procedures ///////////////////////////////////////////////
    void makeZero() {
        for(int i = 1; i < this.getSize(); i++){
            this.row[i].clear();
        }
    }
    // sets this Matrix to the zero state
    Matrix copy() {
        Matrix mat = new Matrix(this.getSize()-1);
        for(int i = 1; i < this.getSize(); i++){
            this.row[i].moveTo(0);
            while( this.row[i].getIndex() >= 0){
                mat.row[i].append(this.row[i].getElement());
                this.row[i].moveNext();
            }            
        }
        return mat;
    }
    // returns a new Matrix having the same entries as this Matrix
    void changeEntry(int i, int j, double x) {
    	// check case where row doesn't exist
        if(this.getSize()-1 < i || i < 0){
            throw new RuntimeException(
                    "Matrix Error: changeEntry(), row does not exist");
        }
        // check case where column is out of bounds
        if(this.getSize()-1 < j || j < 0){
            throw new RuntimeException(
                    "Matrix Error: changeEntry(), row does not exist");
        }
        
        // declare holder entries
        Entry E, F;
        // create new entry with column=j and value=x
        F = new Entry(j,x);
        // initialize flag
        boolean flag = true;
        // check that the row has non-zero entries
        if(this.row[i].length() > 0){
        	// start at the front of the row
        	this.row[i].moveTo(0);
        
	        while(flag){
	        	// hold current entry
	        	E = (Entry)this.row[i].getElement();
	        	// if the current column is less than j move forward
	        	if(E.column < j){
	        		this.row[i].moveNext();        		
	        	}
	        	// if the cursor has passed the jth column insert the new entry 
	        	// in front of the cursor and end loop
	        	if(E.column > j && x != 0){
	        		this.row[i].insertBefore(F);
	        		flag = false;
	        	}
	        	// if the current column is equal to j insert the new entry
	        	// after the cursor and delete the entry highlighted, then
	        	// end loop
	        	if(E.column == j){
                            if(x != 0){
	        		this.row[i].insertAfter(F);
                            }
	        		this.row[i].delete();
	        		flag = false;
	        	}
	        	// if the cursor falls off the end of the list without
	        	// ever encountering the jth column then append the 
	        	// new entry to the end of the row and end loop
	        	if(this.row[i].getIndex() < 0){
                            if(x != 0){
	        		this.row[i].append(F);
                            }
                            flag = false;
	        	}
                    
	        }
        }
        // otherwise if the row is a zero-row append the new entry
        // to the empty row
        else { 
            if(x != 0){
        	this.row[i].append(F);
            }
        }
    }
    // changes ith row, jth column of this Matrix to x
    // pre: 1<=i<=getSize(), 1<=j<=getSize()
    
    Matrix scalarMult(double x) {
    	// create new matrix with same size as this matrix
        Matrix xM = new Matrix(this.getSize()-1);
        // declare holder entries
        Entry E, xE;
        
        // for every row in this matrix
        for( int i = 1; i < this.getSize(); i++){
        	// check that the row has non-zero elements
            if(this.row[i].length() > 0){
            	// start at the front
                this.row[i].moveTo(0);
                // while the cursor doesn't fall off the end
                while(this.row[i].getIndex() >= 0){
                	// hold the highlighted entry
                    E = (Entry)this.row[i].getElement();
                    // create new entry with same column as
                    // highlighted entry and value= the value 
                    // of the highlighted entry multiplied by x
                    xE = new Entry(E.column,x*E.value);
                    // append the new entry to the corresponding row
                    // of the new matrix
                    xM.row[i].append(xE);
                    // move to the next non-zero entry of the current row
                    this.row[i].moveNext();
                }
            }
        }        
        return xM;
    }
    // returns a new Matrix that is the scalar product of this Matrix with x
    
    Matrix add(Matrix M) {
        
        // check case where matrices are different sizes
        if(this.getSize() != M.getSize()){
            throw new RuntimeException(
                "Matrix Error: add() called on matrices of differing size");
        }
        
        // create new size x size matrix that will be the sum of matrix A (this)
        // and matrix B (M)
        Matrix ThisPlusM = new Matrix(this.getSize()-1);
        // make a copy of M for the duration of the operation to account for
        // the case when you are adding a matrix to itself, in which case we
        // would be performing list traversals on the same list
        Matrix B = M.copy();
        // create holder entry variables for A, B, and A+B respectively
        Entry ThisEntry, MEntry, E;
        
        // for all rows of the matrices
        for(int i = 1; i < this.getSize(); i++){
            
            // case when the ith row of A and B are both non-zero rows
            if(this.row[i].length() > 0 && B.row[i].length() > 0){
                
                // set cursors to first non-zero element in each
                this.row[i].moveTo(0);
                B.row[i].moveTo(0);
                // initialize flag
                boolean flag = false;
                
                // while both cursors haven't fallen off the ends
                while (!flag){
                    
                    // case when both cursors are still highlighting a non-zero
                    // element in the row
                    if(this.row[i].getIndex() >= 0 && B.row[i].getIndex() >= 0 ){
                        // set holder entry variables to the non-zero entries
                        // being highlighted
                        ThisEntry = (Entry)this.row[i].getElement();
                        MEntry = (Entry)B.row[i].getElement();
                        
                        // case when non-zero entries are in the same column
                        if(ThisEntry.column == MEntry.column){
                            // place the sum of the two non-zero entries in the
                            // same column of the new matrix
                            E = new Entry(
                                    ThisEntry.column, 
                                    ThisEntry.value + MEntry.value);
                            ThisPlusM.row[i].append(E);
                            // move both cursors forward
                            this.row[i].moveNext();
                            B.row[i].moveNext();
                        }
                        
                        // case when A's ith row cursor is highlighting a column 
                        // less than B's
                        else if(ThisEntry.column < MEntry.column){
                            // fill the columns of the sum with the non-zero
                            // entries of A's ith row until it catches up to B
                            // or falls off the end of the row
                            while( this.row[i].getIndex() >= 0
                                    && ThisEntry.column < MEntry.column){
                                 E = new Entry(
                                    ThisEntry.column, 
                                    ThisEntry.value);
                                ThisPlusM.row[i].append(E);
                                this.row[i].moveNext();
                                if(this.row[i].getIndex() >= 0){
                                    ThisEntry =(Entry)this.row[i].getElement();
                                }
                            }
                        }
                        
                        // case when B's ith row cursor is highlighting a column
                        // less than A's
                        else if(MEntry.column < ThisEntry.column){
                            // fill the columns of the sum with the non-zero
                            // entries of B's ith row until it catches up to 
                            // A or falls off the end of the row
                            while(B.row[i].getIndex() >= 0
                                    && MEntry.column < ThisEntry.column){
                                 E = new Entry(
                                    MEntry.column, 
                                    MEntry.value);
                                ThisPlusM.row[i].append(E);
                                B.row[i].moveNext();
                                if(B.row[i].getIndex() >= 0){
                                    MEntry =(Entry)B.row[i].getElement();
                                }
                            }
                        }
                        
                        // check if both cursors have fallen off the end of
                        // their rows, if so break the while loop
                        if(this.row[i].getIndex() < 0 && B.row[i].getIndex() < 0){
                            flag = true;
                        }
                    }
                    
                    // case when B's ith row cursor has fallen off the end of
                    // its row but A's has not
                    else if(this.row[i].getIndex() >= 0 && B.row[i].getIndex() < 0){
                        // transfer over the rest of the non-zero entries in A's 
                        // ith row's to the A+B matrix 
                        while(this.row[i].getIndex() >= 0){
                            ThisEntry = (Entry)this.row[i].getElement();
                            E = new Entry(
                                ThisEntry.column, 
                                ThisEntry.value);
                            ThisPlusM.row[i].append(E);
                            this.row[i].moveNext();
                        }
                        
                        // check if both cursors have fallen off the end of
                        // their rows, if so break the while loop
                        if(this.row[i].getIndex() < 0 && B.row[i].getIndex() < 0){
                            flag = true;
                        }
                    }
                    
                    // case when A's ith row cursor has fallen off the end of
                    // its row but B's has not
                    else if(this.row[i].getIndex() < 0 && B.row[i].getIndex() >= 0){
                        // transfer over the rest of the non-zero entries in B's 
                        // ith row's to the A+B matrix
                        while(B.row[i].getIndex() >= 0){
                            MEntry =(Entry)B.row[i].getElement();
                            E = new Entry(
                                MEntry.column, 
                                MEntry.value);
                            ThisPlusM.row[i].append(E);
                            B.row[i].moveNext();
                        }
                        
                        // check if both cursors have fallen off the end of
                        // their rows, if so break the while loop
                        if(this.row[i].getIndex() < 0 && B.row[i].getIndex() < 0){
                            flag = true;
                        }
                    }
                }
            }
            
            // case when the ith row of B is a zero row and A's is not
            else if(this.row[i].length() > 0 && B.row[i].length() <= 0){
                // copy all non-zero entries of A's ith row into the ith row of
                // A+B
                this.row[i].moveTo(0);
                while(this.row[i].getIndex() >= 0){
                    ThisEntry = (Entry)this.row[i].getElement();
                    E = new Entry(
                        ThisEntry.column, 
                        ThisEntry.value);
                    ThisPlusM.row[i].append(E);
                    this.row[i].moveNext();
                }
            }
            
            // case when the ith row of A is a zero row and B's is not
            else if(this.row[i].length() <= 0 && B.row[i].length() > 0){
                // copy all non-zero entries of B's ith row into the ith row of
                // A+B
                B.row[i].moveTo(0);
                while(B.row[i].getIndex() >= 0){
                    MEntry =(Entry)B.row[i].getElement();
                    E = new Entry(
                        MEntry.column, 
                        MEntry.value);
                    ThisPlusM.row[i].append(E);
                    B.row[i].moveNext();
                }
            }            
        }        
        return ThisPlusM;
    }
    // returns a new Matrix that is the sum of this Matrix with M
    // pre: getSize()==M.getSize()
    
    Matrix sub(Matrix M) {
        
        // check case where matrices are different sizes
        if(this.getSize() != M.getSize()){
            throw new RuntimeException(
                "Matrix Error: add() called on matrices of differing size");
        }
        
        // create new size x size matrix that will be the difference of 
        // matrix A (this)and matrix B (M)
        Matrix ThisMinusM = new Matrix(this.getSize()-1);
        // make a copy of M for the duration of the operation to account for
        // the case when you are subtracting a matrix from itself, in which case we
        // would be performing list traversals on the same list
        Matrix B = M.copy();
        // create holder entry variables for A, B, and A-B respectively
        Entry ThisEntry, MEntry, E;
        
        // checks case when you are subtracting a matrix from itself in which
        // case no action is needed and the zero matrix is returned
        if(!this.equals(B)){
        
            // for all rows from 0 to the size of the matrices
            for(int i = 1; i < this.getSize(); i++){
                // initialize flag
                boolean flag = false;

                // check that the ith row of A and B are both non-zero rows
                if(this.row[i].length() > 0 && B.row[i].length() > 0){

                    // set cursors to first non-zero element in each
                    this.row[i].moveTo(0);
                    B.row[i].moveTo(0);

                    // while both cursors haven't fallen off the ends
                    while (!flag){

                        // case when both cursors are still highlighting a non-zero
                        // element in the row
                        if(this.row[i].getIndex() >= 0 && B.row[i].getIndex() >= 0 ){
                            // set holder entry variables equal to the non-zero
                            // entries being highlighted
                            ThisEntry = (Entry)this.row[i].getElement();
                            MEntry = (Entry)B.row[i].getElement();

                            // case when non-zero entries are in the same column
                            if(ThisEntry.column == MEntry.column){
                                // place the difference of the two non-zero entries
                                // in the same column of the new matrix only if the
                                    // difference is non-zero
                                E = new Entry(
                                        ThisEntry.column, 
                                        ThisEntry.value - MEntry.value);
                                if(E.value != 0){
                                    ThisMinusM.row[i].append(E);
                                }
                                // move both cursors forward
                                this.row[i].moveNext();
                                B.row[i].moveNext();
                            }

                            // case when A's ith row cursor is highlighting a column 
                            // less than B's
                            else if(ThisEntry.column < MEntry.column){
                                // fill the columns of the sum with the non-zero
                                // entries of A's ith row until it catches up to B
                                // or falls off the end of the row
                                while( this.row[i].getIndex() >= 0
                                        && ThisEntry.column < MEntry.column){
                                     E = new Entry(
                                        ThisEntry.column, 
                                        ThisEntry.value);
                                    ThisMinusM.row[i].append(E);
                                    this.row[i].moveNext();
                                    if(this.row[i].getIndex() >= 0){
                                        ThisEntry =(Entry)this.row[i].getElement();
                                    }
                                }
                            }
                            // case when B's ith row cursor is highlighting a column
                            // less than A's
                            else if(MEntry.column < ThisEntry.column){
                                // fill the columns of the difference 
                                // with the negative of the non-zero
                                // entries of B's ith row until it catches up to 
                                // A or falls off the end of the row
                                while(B.row[i].getIndex() >= 0
                                        && MEntry.column < ThisEntry.column){
                                     E = new Entry(
                                        MEntry.column, 
                                        -MEntry.value);
                                    ThisMinusM.row[i].append(E);
                                    B.row[i].moveNext();
                                    if(B.row[i].getIndex() >= 0){
                                        MEntry =(Entry)B.row[i].getElement();
                                    }
                                }
                            }

                            // check if both cursors have fallen off the end of
                            // their rows, if so break the while loop
                            if(this.row[i].getIndex() < 0 && B.row[i].getIndex() < 0){
                                flag = true;
                            }
                        }
                        // case when B's ith row cursor has fallen off the end of
                        // its row but A's has not
                        else if(this.row[i].getIndex() >= 0 && B.row[i].getIndex() < 0){
                            // transfer over the rest of the non-zero entries in A's 
                            // ith row's to the A+B matrix 
                            while(this.row[i].getIndex() >= 0){
                                ThisEntry = (Entry)this.row[i].getElement();
                                E = new Entry(
                                    ThisEntry.column, 
                                    ThisEntry.value);
                                ThisMinusM.row[i].append(E);
                                this.row[i].moveNext();
                            }

                            // check if both cursors have fallen off the end of
                            // their rows, if so break the while loop
                            if(this.row[i].getIndex() < 0 && B.row[i].getIndex() < 0){
                                flag = true;
                            }
                        }
                        // case when A's ith row cursor has fallen off the end of
                        // its row but B's has not
                        else if(this.row[i].getIndex() < 0 && B.row[i].getIndex() >= 0){
                            // transfer over the negatives of the rest of the 
                            // non-zero entries in B's 
                            // ith row to the A-B matrix
                            while(B.row[i].getIndex() >= 0){
                                MEntry =(Entry)B.row[i].getElement();
                                E = new Entry(
                                    MEntry.column, 
                                    -MEntry.value);
                                ThisMinusM.row[i].append(E);
                                B.row[i].moveNext();
                            }

                            // check if both cursors have fallen off the end of
                            // their rows, if so break the while loop
                            if(this.row[i].getIndex() < 0 && B.row[i].getIndex() < 0){
                                flag = true;
                            }
                        }
                    }
                }
                // case when the ith row of B is a zero row and A's is not
                else if(this.row[i].length() > 0 && B.row[i].length() <= 0){
                    // copy all non-zero entries of A's ith row into the ith row of
                    // A-B
                    this.row[i].moveTo(0);
                    while(this.row[i].getIndex() >= 0){
                        ThisEntry = (Entry)this.row[i].getElement();
                        E = new Entry(
                            ThisEntry.column, 
                            ThisEntry.value);
                        ThisMinusM.row[i].append(E);
                        this.row[i].moveNext();
                    }
                }
                // case when the ith row of A is a zero row and B's is not
                else if(this.row[i].length() <= 0 && B.row[i].length() > 0){
                    // copy the negative of all non-zero entries of B's ith row into 
                    // the ith row of A-B
                    B.row[i].moveTo(0);
                    while(B.row[i].getIndex() >= 0){
                        MEntry =(Entry)B.row[i].getElement();
                        E = new Entry(
                            MEntry.column, 
                            -MEntry.value);
                        ThisMinusM.row[i].append(E);
                        B.row[i].moveNext();
                    }
                }            
            } 
        }
        return ThisMinusM;
    }
    // returns a new Matrix that is the difference of this Matrix with M
    // pre: getSize()==M.getSize()
    
    Matrix transpose() {        
    	
        // create empty transpose matrix
        Matrix tran = new Matrix(this.getSize()-1);
        // declare holder entry variables for the element in question of A and
        // the one to be placed in the transpose
        Entry E, F;
        
        // for every row of A
        for (int i = 1; i < this.getSize(); i++){
            // do nothing if the row is a zero row
            if(this.row[i].length() > 0){        	
                // start at the first node
                this.row[i].moveTo(0);
                // while the cursor doesn't fall off the end
                while(this.row[i].getIndex() >= 0){
                    // hold the highlighted non-zero entry of A 
                    E = (Entry)this.row[i].getElement();
                    // create a new Entry with the same value whose column is the 
                    // current row
                    F = new Entry(i,E.value);
                    // append this entry to the row of the transpose matrix indexed
                    // by the column of the highlighted entry of A
                    tran.row[E.column].append(F);
                    // move to the next non-zero entry
                    this.row[i].moveNext();
                }
            }
        }        
        return tran;
    }
    // returns a new Matrix that is the transpose of this Matrix
    
    Matrix mult(Matrix M) {        
        // check case if matrix A (this) and matrix B (M) are different sizes
        if(this.getSize() != M.getSize()){
            throw new RuntimeException(
            "Matrix Error: cannot call mult() on matrices of differing size");
        }
        int counter = 0;
        // create two matrices: one to hold the product of A and B
        // the other to hold the transpose of B
        Matrix transM, prod;
        transM = M.transpose();
        prod = new Matrix(this.getSize()-1);
        // declare holder entry variable
        Entry E;        
        // for every row of A
        for (int i = 1; i < this.getSize(); i++){
            if(this.row[i].length() > 0){ 
                // and every column of B
                for(int j = 1; j < transM.getSize(); j++){
                    // if neither is a zero row
                    // append an entry to the row of the product matrix indexed by 
                    // the current row of A, with column=j, and value=the dot 
                    // product of the ith row of A and the jth column of B
                    // (the jth row of B transpose)
                    if(transM.row[j].length() > 0){
                        E = new Entry(j,dot(this.row[i],transM.row[j]));
                        if(E.value != 0){
                            prod.row[i].append(E); 
                        }
                    }
                }
            }
        }        
        return prod;
    }
    // returns a new Matrix that is the product of this Matrix with M
    // pre: getSize()==M.getSize()
    
    private static double dot(List P, List Q) {
        // declarations
        double sum = 0;
        boolean flag = false;
        Entry S, T;
        
        // check both lists are non-empty
        if(P.length() > 0 && Q.length() > 0){
            // starting with the first element in each
            P.moveTo(0);
            Q.moveTo(0);
            // while neither list cursor has fallen off the end
            while (!flag){
                // hold each highlighted non-zero entry
                S = (Entry)P.getElement();
                T = (Entry)Q.getElement();
                
                // if they are in the same column then add their product to the
                // running sum and move both cursors forward
                if(S.column == T.column){
                    sum += (S.value)*(T.value);
                    P.moveNext();
                    Q.moveNext();
                }
                // otherwise assuming neither cursor has fallen of the end and 
                // P's cursor is behind Q's column-wise the move P's cursor 
                // forward until it catches up to or passes Q
                else if(P.getIndex() >= 0 
                        && Q.getIndex() >= 0 
                        && S.column < T.column){
                    P.moveNext();
                }
                // otherwise in the opposite case do the same for Q's cursor
                else if(P.getIndex() >= 0 
                        && Q.getIndex() >= 0 
                        && S.column > T.column){
                    Q.moveNext();
                }
                // when one of the cursors falls off the end of the list break
                // the loop
                if(P.getIndex() < 0 || Q.getIndex() < 0){
                    flag = true;
                }
            }
        }        
        return sum;
    }
    // returns the dot product of two lists P and Q

    // Other functions ///////////////////////////////////////////////////////
    
    public String toString() {
    	String S = "";
    	
    	for(int i = 1; i < this.getSize(); i++){
    		if(this.row[i].length() > 0){
    			S += i + ": " + this.row[i].toString() + "\n";
    		}
    	}    	
    	return S;
    }    
    // overrides Object's toString() method
        
    // Private Entry class which is the data object being held by the list ADT    
    private class Entry {
        int column;
        double value;
        
        Entry(int col, double val){
            this.column = col;
            this.value = val;
        }
        public boolean equals(Object obj) {
            Entry E = (Entry)obj;
            return (E.column == this.column && E.value == this.value);
        }        
        public String toString() {
        	String S;
        	S = "(" + this.column + "," + this.value + ")";        	
        	return S;
    	}
    }
}

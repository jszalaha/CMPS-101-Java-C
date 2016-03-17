/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 3
 */
//-----------------------------------------------------------------------------
//  List.java
//-----------------------------------------------------------------------------
public class List {
	
	private	Node front;
	private Node back;
	private Node cursor;
	private int cursorIndex;
	private int length;	
	
	// Constructor
	List()
	{ 
		front = back = cursor = null; 
		length = 0; 
		cursorIndex = -1;
	} 	
	// Creates a new empty list.
	
	// Access functions //////////////////////////////////////////	
	int length()
	{
		return this.length;
	}	
	// Returns number of elements in this list.
	
	int getIndex()
	{
		return this.cursorIndex;
	}
	// Returns the index of the cursor element in this list, or
	// returns -1 if the cursor element is undefined.
	
	Object front()
	{
		if( this.length() <= 0 ){
	         throw new RuntimeException(
                         "List Error: front() called on empty List");
	    }
		return this.front.data;		
	}
	// Returns front element in this list. Pre: length()>0
	
	Object back()
	{
		if( this.length() <= 0 ){
	         throw new RuntimeException(
                         "List Error: back() called on empty List");
	    }
		return this.back.data;
	}
	// Returns back element in this List. Pre: length()>0
	
	Object getElement()
	{
            if( this.length() <= 0 || this.getIndex() < 0)
            {
                throw new RuntimeException(
                    "List Error: getElement() called on empty List "
                    + "or element does not exist"
		);
             }
            else { return this.cursor.data; }
				
	} 
	// Returns cursor element in this list.
	// Pre: length()>0, getIndex()>=0
	
	public boolean equals(Object obj)
	{
            List L = (List)obj;
            boolean flag = true;
            
            if(this.length() == L.length()){
                this.moveTo(0);
                L.moveTo(0);
                while(flag && this.getIndex() >= 0 && L.getIndex() >= 0){
                    if(this.cursor.equals(L.cursor)){
                        this.moveNext();
                        L.moveNext();
                    }else { flag = false; }
                }
            }else { flag = false; }
                
            return flag;
	}
	// Returns true if this List and L are the same object
	// sequence.
	
	// Manipulation procedures ////////////////////////////////////////
	void clear()
	{
		this.front = this.back = null;
		this.length = 0;
		this.cursor = null;
		this.cursorIndex = -1;
	} 
	// Re-sets this List to the empty state.
	
	void moveTo(int i)
	{
		if ( i >= 0 && i <= length()-1 )
                {
                    this.cursor = this.front;
                    this.cursorIndex = i;

                    for (int j = 0; j < this.cursorIndex; j++) 
                    {
                        this.cursor = this.cursor.next;
                    }
		}
		else { this.cursorIndex = -1; this.cursor = null; }
	} 	
	// If 0<=i<=length()-1, moves the cursor to the element
	// at index i, otherwise the cursor becomes undefined.
	
	void movePrev()
	{
		if ( getIndex() > 0 && getIndex()<= length()-1 ){
			this.cursor = this.cursor.previous;
			this.cursorIndex--;
		}else { this.cursor = null; this.cursorIndex = -1; }
	} 
	// If 0<getIndex()<=length()-1, moves the cursor one step toward the
	// front of the list. If getIndex()==0, cursor becomes undefined.
	// If getIndex()==-1, cursor remains undefined. This operation is
	// equivalent to moveTo(getIndex()-1).
	
	void moveNext()
	{
		if ( getIndex() >= 0 && getIndex() < length()-1 ){
			this.cursor = this.cursor.next;
			this.cursorIndex++;
		}
		else { this.cursor = null; this.cursorIndex = -1; }
	} 
	// If 0<=getIndex()<length()-1, moves the cursor one step toward the
	// back of the list. If getIndex()==length()-1, cursor becomes
	// undefined. If index==-1, cursor remains undefined. This
	// operation is equivalent to moveTo(getIndex()+1).
	
	void prepend(Object data)
	{
		Node node = new Node(data);
		if ( this.length() == 0 ){ this.front = this.back = node; }
		else {
			node.next = this.front;
			this.front.previous = node;
			this.front = node;
		}
		this.length++;
		if( this.cursorIndex >= 0 ){ this.cursorIndex++; }
	} 
	// Inserts new element before front element in this List.
	
	void append(Object data)
	{
		Node node = new Node(data);
		if ( this.length() == 0 ){ this.front = this.back = node; }
		else {
			node.previous = this.back;
			this.back.next = node;
			this.back = node; 
			}
		this.length++;
	} 
	// Inserts new element after back element in this List.
	
	void insertBefore(Object data)
	{
		Node node = new Node(data);
		if ( this.length() > 0 && this.getIndex() >= 0 ){
			if( this.cursor == this.front ){
				prepend(data);
			}else {
				node.next = this.cursor;
				node.previous = this.cursor.previous;
				this.cursor.previous.next = node;
				this.cursor.previous = node;
				this.length++;
				this.cursorIndex++;
			}
		}else throw new RuntimeException(
			"Cursor Error: insertBefore() called while "
                        + "cursor is undefined"
			);
	} 
	// Inserts new element before cursor element in this
	// List. Pre: length()>0, getIndex()>=0
	
	void insertAfter(Object data)
	{
		Node node = new Node(data);
		if ( this.length() > 0 && this.getIndex() >= 0 ){
			if( this.cursor == this.back ){
				append(data);
			}else {
				node.previous = this.cursor;
				node.next = this.cursor.next;
				this.cursor.next.previous = node;
				this.cursor.next = node;
				this.length++;
			}
		}else throw new RuntimeException(
			"Cursor Error: insertAfter() called while cursor is undefined"
			);
	} 
	// Inserts new element after cursor element in this
	// List. Pre: length()>0, getIndex()>=0
	
	void deleteFront()
	{
		if( this.length() <= 0 ){ throw new RuntimeException( 
			"List Error: deleteFront() called on empty list" ); }
		if ( this.length() > 1 ){ 
                    this.front = this.front.next; this.length--; 
                }
		else { this.front = this.back = null; } 
		if ( this.cursorIndex >= 0 ){ this.cursorIndex--; }
	} 
	// Deletes the front element in this List. Pre: length()>0
	
	void deleteBack()
	{
		if ( this.cursorIndex == length() ){ 
                    this.cursor = null; 
                    this.cursorIndex = -1;
                }
		if( this.length() <= 0 ){ throw new RuntimeException( 
			"List Error: deleteBack() called on empty list" ); }
		if ( this.length() > 1 ){ 
                    this.back = this.back.previous; 
                    this.length--;
                }
		else { this.front = this.back =  null; }
	} 
	// Deletes the back element in this List. Pre: length()>0
	
	void delete()
	{
		if( this.length() <= 0 ){ throw new RuntimeException( 
			"List Error: delete() called on empty list" ); }
		if( this.getIndex() < 0 ){ throw new RuntimeException( 
			"List Error: delete() called while cursor is undefined" 
                        ); }
		if( this.length() > 1 ){
			this.cursor.previous.next = this.cursor.next;
			this.cursor.next.previous = this.cursor.previous;
			this.cursor = null;
			this.cursorIndex = -1;
			this.length--;
		}else { this.front = this.back = null; }
	} 
	// Deletes cursor element in this List. Cursor is undefined after this
	// operation. Pre: length()>0, getIndex()>=0
	
	// Other methods //////////////////////////////////////////////////	
	public String toString()
	{
		String S = "";
		Node N = this.front;
		
		while( N != null ){
			S += N.data.toString() + " ";
			N = N.next;
		}
		
		return S;
	}
	// Overrides Object's toString method. Creates a string
	// consisting of a space separated sequence of integers
	// with front on the left and back on the right. The
	// cursor is ignored.
	
	//Node class
	private class Node
	{
		//Fields
		Object data;
		Node previous;
		Node next;
		
		//Constructor
		Node(Object data){ 
                    this.data = data; 
                    this.next = null; 
                    this.previous = null; 
                }
		
                public boolean equals(Object obj){
                    Node N = (Node)obj;
                    return (this.data.equals(N.data));
                }
                
		//toString: Overrides Object's toString method.
		public String toString(){ 
			String S = this.data.toString();
			return S;
		}
	}
}

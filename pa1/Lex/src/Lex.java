/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 1
 */
//-----------------------------------------------------------------------------
//  Lex.java
//-----------------------------------------------------------------------------
import java.io.*;

public class Lex {

    public static void main(String[] args) throws IOException {
        //First, verifies that the number of files entered after the command to
        //run the program is 2. Otherwise it terminates with an error code.
        if (args.length != 2) {
            System.err.println(
                    "Input Error: Incorrect Number of Command Arguments."
                    + " Required: 2");
            System.exit(1);
        } 
        
        //Then
        else {
            
            //Declarations and Initializations//////////////////////////////////
            int n = 0;
            int h, i, j, z;
            String s = null;
            boolean flag;            
            List list = new List();            
            BufferedReader reader = new BufferedReader(new FileReader(args[0]));
            BufferedReader reader2 = new BufferedReader(new FileReader(args[0]));
            BufferedWriter writer = new BufferedWriter(new FileWriter(args[1]));            
            
            //Uses reader to count the number of lines in the
            //input file, args[0], and stores it into a variable, n
            while (reader.readLine() != null){ n++; }
            reader.close();
            
            //Creates a string, input, of length n
            String[] input = new String[n];
            
            //Uses reader2 to read and store each line as a string into input
            for (i = 0; i < n; i++){ input[i] = reader2.readLine(); }
            reader2.close();
            
            //Creates the first node of list using the index of the first string
            //in input
            list.prepend(0);
            //Sets the cursor to the first node in list
            list.moveTo(0);
            
////////////// Sorting Algorithm ///////////////////////////////////////////////
            
            //For each iteration of j from 1 to n (length of input)
            for ( j = 1; j < n; j++ ) {
                
                //Moves the list cursor to the first node
                list.moveTo(0);
                //Sets the string s equal to the jth element of input
                s = input[j];
                //Resets flag
                flag = false;
                
                while ( !flag )
                {
                    //Compares s to the element of input whose index is
                    //represented by the int stored in the list cursor's
                    //data variable. A negative value means s comes before the
                    //string in question alphabetically
                    if ( s.compareTo(input[list.getElement()]) < 0 ) 
                    {
                        //Inserts the value of j into a new node in front
                        //of the cursor and breaks the while loop
                        list.insertBefore(j);
                        flag = true;
                    }                  
                    //Moves to the next node in the list for comparison
                    else { list.moveNext(); }
                    
                    //If the loop has cycled through all nodes in list and the
                    //cursor has fallen off the end, this puts the value of j
                    //in a new node at the end of the list and breaks the 
                    //while loop
                    if ( list.getIndex() < 0 ) 
                    {
                        list.append(j);
                        flag = true;
                    }
                }
            }

//////////////////////////////////////////////////////////////////////////////
            
            //Resets list cursor
            list.moveTo(0);
            
            for ( h = 0; h < n; h++ ) 
            {
                //Writes each string in sorted order to args[1] followed by a 
                //newline
                writer.write(input[list.getElement()]);
                list.moveNext();
                //Except for the last entry
                if ( list.getIndex() > 0 && list.getIndex() != n-1 ) 
                {
                    writer.newLine();
                }
            }
            writer.close();
        }

    }
}
/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 3
 */
//-----------------------------------------------------------------------------
//  Sparse.java
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class Sparse {
    public static void main(String[] args) throws IOException{
        
        //First, verifies that the number of files entered after the command to
        //run the program is 2. Otherwise it terminates with an error code.
        if (args.length != 2) {
            System.err.println(
                    "Input Error: Incorrect Number of Command Arguments."
                    + " Required: 2");
            System.exit(1);
        }
        
        // declarations
        Scanner scan = new Scanner(new File(args[0]));
        BufferedWriter writer = new BufferedWriter(new FileWriter(args[1]));
        int Size, ANNZ, BNNZ, row, col;
        double val;
        Matrix A, B, Op;
                
        // read info line
        Size = scan.nextInt();
        ANNZ = scan.nextInt();
        BNNZ = scan.nextInt();
        
        //create matrices A and B
        A = new Matrix(Size);
        B = new Matrix(Size);
        
        // read loop A
        for(int i = 0; i < ANNZ; i++){
            row = scan.nextInt();
            col = scan.nextInt();
            val = scan.nextDouble();
            
            A.changeEntry(row, col, val);
        }
        // read loop B
        for(int i = 0; i < BNNZ; i++){
            row = scan.nextInt();
            col = scan.nextInt();
            val = scan.nextDouble();
            
            B.changeEntry(row, col, val);
        }
        scan.close();
        
        // A
        writer.write("A has " + A.getNNZ() + " non-zero entries:\n");
        writer.write(A.toString() + "\n");
        
        // B
        writer.write("B has " + B.getNNZ() + " non-zero entries:\n");
        writer.write(B.toString() + "\n");
        
        // (1.5)*A
        Op = A.scalarMult(1.5);
        writer.write("(1.5)*A has " + Op.getNNZ() + " non-zero entries:\n");
        writer.write(Op.toString() + "\n");
        
        // A+B
        Op = A.add(B);
        writer.write("A+B has " + Op.getNNZ() + " non-zero entries:\n");
        writer.write(Op.toString() + "\n");
        
        // A+A
        Op = A.add(A);
        writer.write("A+A has " + Op.getNNZ() + " non-zero entries:\n");
        writer.write(Op.toString() + "\n");
        
        // B-A
        Op = B.sub(A);
        writer.write("B-A has " + Op.getNNZ() + " non-zero entries:\n");
        writer.write(Op.toString() + "\n");
        
        // A-A
        Op = A.sub(A);
        writer.write("A-A has " + Op.getNNZ() + " non-zero entries:\n");
        writer.write(Op.toString() + "\n");
        
        // Transpose(A)
        Op = A.transpose();
        writer.write("Transpose(A) has " + Op.getNNZ() + " non-zero entries:\n");
        writer.write(Op.toString() + "\n");
        
        // A*B
        Op = A.mult(B);
        writer.write("A*B has " + Op.getNNZ() + " non-zero entries:\n");
        writer.write(Op.toString() + "\n");
        
        // B*B
        Op = B.mult(B);
        writer.write("B*B has " + Op.getNNZ() + " non-zero entries:\n");
        writer.write(Op.toString() + "\n");
        
        writer.close();
    }
    
}

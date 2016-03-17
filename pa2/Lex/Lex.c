/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 2
 */
//-----------------------------------------------------------------------------
// Lex.h
//-----------------------------------------------------------------------------
#include <string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

    int j, n = 0;
    int count = 0;
    int flag;
    FILE *in, *out;
    char line[MAX_LEN];
    char *s;
    List list;

    //verifies the correct number of arguments
    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    //opens the in file and out file
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    //checks that they exist
    if(in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if(out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    //counts number of lines in argv[1]
    while ( fgets(line, MAX_LEN, in) != NULL)
    {
        n++;
    }
    //dynamically allocates an array of strings of size lines counted
    char **input = (char **)myMalloc(n*sizeof(char *));
    for (int i = 0; i < n; i++){
        input[i] = (char *)myMalloc(MAX_LEN*sizeof(char *));
    }
    //closes argv[1] and reopens it
    fclose(in);
    in = fopen(argv[1], "r");
    //copies each line of argv[1] into the input array
    while ( fgets(line, MAX_LEN, in) != NULL)
    {
        strcpy(input[count],line);
        count++;
    }
    fclose(in);
    //creates new list
    list = newList();
    //puts 0 as the data in its first node
    append(list, 0);
    //sets cursor to index 0
    moveTo(list, 0);

    //-------------------------------------------------------------------------

    //For each iteration of j from 1 to n (length of input)
    for( j = 1; j < n; j++ ){
        //Moves the list cursor to the first node
        moveTo(list, 0);
        //Sets the string s equal to the jth element of input
        s = input[j];
        //resets flag
        flag = 0;

        while(flag == 0){
            //Compares s to the element of input whose index is
            //represented by the int stored in the list cursor's
            //data variable. A negative value means s comes before the
            //string in question alphabetically
            if ( strcmp(s, input[getElement(list)]) < 0 ){
                //Inserts the value of j into a new node in front
                //of the cursor and breaks the while loop
                insertBefore(list, j);
                flag = 1;
            }
            //Moves to the next node in the list for comparison
            else { moveNext(list); }

            //If the loop has cycled through all nodes in list and the
            //cursor has fallen off the end, this puts the value of j
            //in a new node at the end of the list and breaks the
            //while loop
            if ( getIndex(list) < 0 ){
                append(list, j);
                flag = 1;
            }
        }
    }
    //-------------------------------------------------------------------------

    //resets list cursor
    moveTo(list, 0);

    for(int h = 0; h < n; h++){
        //Writes each string in sorted order to args[1] followed by a
        //newline
        fprintf(out, "%s", input[getElement(list)]);
        moveNext(list);
    }
    //close out file
    fclose(out);
    //free input array data
    for (int i = 0; i < n; i++) {
        myFree(input[i]);
        input[i] = NULL;
    }
    myFree(input);
    input = NULL;

    //free list data
    freeList(&list);
    list = NULL;

    printf("globalMalloc = %d\n", globalMalloc);

    return(0);
}

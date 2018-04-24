/* Daryl Vogel
 * dev160130@utdallas.edu
 * CS 3377.002
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "header.h"
#include "record.h"
#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

char* concatenate(const char*, const char*);

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};
  BinaryFileHeader *header = new BinaryFileHeader();
  BinaryFileRecord *record = new BinaryFileRecord();

  ifstream file("cs3377.bin", ios::in|ios::binary);	//The file that we will be reading our objects from.
  if (file){	//Check to make sure it opened properly
    file.read((char*) header, sizeof(BinaryFileHeader));	//Read in the header object
  }

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  char buffer[50];	//Buffer is the char* where we store the string representations of the numbers.

  sprintf(buffer, "%x", header->magicNumber);	//Store the numbers as strings
  setCDKMatrixCell(myMatrix, 1, 1, concatenate("Magic: 0x", buffer));	//print those strings

  sprintf(buffer, "%d", header->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, concatenate("Version: ", buffer));

  sprintf(buffer, "%ld", header->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, concatenate("NumRecords: ", buffer));

  for (unsigned int i = 0;i < header->numRecords;i++){	//Loop through the number of records there are
    file.read((char *)record, sizeof(BinaryFileRecord));	//Read in one object at a time.
    sprintf(buffer, "%d", record->strLength);	//Convert it's number to a string
    setCDKMatrixCell(myMatrix, i+2, 1, concatenate("strlen", buffer));	//Print out it's info.
    setCDKMatrixCell(myMatrix, i+2, 2, record->stringBuffer);
  }

  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
  delete header;
  delete record;
}

//Used to concatenate 2 strings together
char* concatenate(const char* str1, const char* str2){
  int length = strlen(str1) + strlen(str2) + 1;	//Find the length of the combined string
  char *ans = new char[length];
  strcpy(ans, str1);	//Copy the first string and concatenate the second.
  strcat(ans, str2);
  return ans;
}

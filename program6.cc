/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
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

  ifstream file("cs3377.bin", ios::in|ios::binary);
  if (file){
    file.read((char*) header, sizeof(BinaryFileHeader));
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
  char buffer[50];

  sprintf(buffer, "%x", header->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, concatenate("Magic: 0x", buffer));

  sprintf(buffer, "%d", header->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, concatenate("Version: ", buffer));

  sprintf(buffer, "%d", header->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, concatenate("NumRecords: ", buffer));

  for (int i = 0;i < header->numRecords;i++){
    file.read((char *)record, sizeof(BinaryFileRecord));
    sprintf(buffer, "%d", record->strLength);
    setCDKMatrixCell(myMatrix, i+2, 1, concatenate("strlen", buffer));
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

char* concatenate(const char* str1, const char* str2){
  int length = strlen(str1) + strlen(str2) + 1;
  char *ans = new char[length];
  strcpy(ans, str1);
  strcat(ans, str2);
  return ans;
}

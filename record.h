//Daryl Vogel
//dev160130@utdallas.edu
//CS 3377.002

#include <stdint.h>

const int maxRecordStringLength = 25;

class BinaryFileRecord{
	public:
		uint8_t strLength;
		char stringBuffer[maxRecordStringLength];
};

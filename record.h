#include <stdint.h>

const int maxRecordStringLength = 25;

class BinaryFileRecord{
	public:
		uint8_t strLength;
		char stringBuffer[maxRecordStringLength];
};

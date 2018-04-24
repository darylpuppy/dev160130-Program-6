//Daryl Vogel
//dev160130@utdallas.edu
//CS 3377.002

#include <stdint.h>

class BinaryFileHeader{
	public:
		uint32_t magicNumber;
		uint32_t versionNumber;
		uint64_t numRecords;
};

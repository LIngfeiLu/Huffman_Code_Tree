/*  Junxi Li, A91105747
    Lingfei Lu, A91046735
 */

#include <ostream>

using namespace std;

/* class BitOuputStream has writeBit, flush, termnation functions
 */
class BitOutputStream{
private:
	char buf;
	int nbits;
	ostream & out;
	

public:

/*
 * constructor of BitOutPutStream class
 */
	BitOutputStream(ostream & os) : out(os), buf(0), nbits(0){}

/*
 * WriteBit will write 1 bit at a time to buf, if buf is full, then write buf to
 * output file
 */
	void writeBit(int i); 

/*
 * flush will read one byte to output file when buf is full
 */
	void flush();

/*
 * termination will used to terminate the last few bits in the file
 */
  void termination();
 
};

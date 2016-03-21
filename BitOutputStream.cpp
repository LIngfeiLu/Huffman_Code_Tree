/*  Junxi Li, A91105747
    Lingfei Lu, A91046735
 */

#include "BitOutputStream.hpp"
#include <stdio.h>

using namespace std;
/*
 * WriteBit will write 1 bit at a time to buf, if buf is full, then write buf to
 * output file
 */
void BitOutputStream::writeBit(int i) {
	//write i to the least significant bit of buf
	buf = (buf << 1) | i ;
	//increase nbits
	nbits++;
  	//if nbits is 8, that means buf is full, then write to output file
  	if(nbits == 8){
  		//write to output file
		flush();
  }
}

/*
 * flush will read one byte to output file when buf is full
 */
void BitOutputStream::flush() {
	//write buf to output file
	out.put(buf);
	//sync output file
	out.flush();
	//reset buf and nbits
	buf = 0;
	nbits = 0;
}

/*
 * termination will used to terminate the last few bits in the file
 */
void BitOutputStream::termination() {
  //if buf is empty then just return	
  if(nbits == 0)  return;
  //else shift buf accordingly to fir 8 bit
  buf = buf << (8-nbits);
  //write ot file
  flush();
}

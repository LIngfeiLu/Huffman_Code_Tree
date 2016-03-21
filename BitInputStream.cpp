/*  Junxi Li, A91105747
    Lingfei Lu, A91046735
 */

#include "BitInputStream.hpp"

using namespace std;

/*
 * initialize will put every byte of input file to vector bytes
 */
void BitInputStream::initialize() {
  while(1){
    //get one byte at a time
    char c = in.get();
    //check if reach the end of the file
    if(!(in.good())) break;
    //add to vector bytes
    bytes.push_back(c);
  }
}


/*
 * readBit read one bit at time return the int representation of that bit
 */
int BitInputStream::readBit() {
  //check which byte we are currently at
  char c = bytes[index/8];
  // go to specfic bit using bit manipulation
  int offset = 7 - (index % 8);
  //increase index by 1
  index++;
  //return that bit
  return (c >> offset) & 1;
}


/*
 * readByte will read 8 bit at once by calling readBit 8 times and then return
 * that byte
 */
unsigned char BitInputStream::readByte() {
  unsigned char c = 0;
  //call readBit 8 times
  for(int i = 7; i >= 0; i--){
    //add bit to char c by using bit manipulation
    c = c | (readBit() << i);
  }
  return c;
}

/*
 * isEnd will check if we reach end of the file
 */
bool BitInputStream::isEnd() const  {
  //the size of the file is 8 times of vector byte
  if(index == bytes.size() * 8)	return true;
  return false;
}

/*
 * getBytes will return vector bytes
 */
vector<char> BitInputStream::getBytes() const  {
  return bytes;
}

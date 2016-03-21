/*  Junxi Li, A91105747
    Lingfei Lu, A91046735
 */

#include <iostream>
#include <vector>

using namespace std;

/*
 * class BitInputStream has readByte, readBit, isEnd, getBytes function
 * which can handle read one bit case that iostream class does not support
 */
class BitInputStream{
    //private variable
  private:
    //bytes store every byte of the input file
    vector<char> bytes;
    //index help determine which byte we are reading
    unsigned int index;
    //in is reference to inputfile
    istream & in;

  public:
    
/* constructor of class BitInputStream
 */
    BitInputStream(istream & is) :in(is), index(0){}

/*
 * initialize will put every byte of input file to vector bytes
 */
    void initialize();

/*
 * readByte will read 8 bit at once by calling readBit 8 times and then return
 * that byte
 */
    unsigned char readByte();

/*
 * readBit read one bit at time return the int representation of that bit
 */
    int readBit();

/*
 * isEnd will check if we reach end of the file
 */
    bool isEnd() const;


/*
 * getBytes will return vector bytes
 */
    vector<char> getBytes() const;
};

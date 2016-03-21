/*  Junxi Li, A91105747
    Lingfei Lu, A91046735
 */

#include "HCNode.hpp"
#include "HCTree.hpp"

using namespace std;
int size = 0;

/*
 * in order traverse the already built tree, use '0' to represent merger node
 * use '1' to represent leave node and the next 8 bytes to represent the
 * character in the leave node
 */
void in_order(HCNode* node, BitOutputStream & outputFile)
{
  //if the node has child, then it is a merge node.
  if(node->c0 && node->c1){
    outputFile.writeBit(0);
    //recurse on left and then on right child
    in_order(node->c0, outputFile);
    in_order(node->c1, outputFile);
  }
  //if the node has no child, then it is a child node, write the character
  //in the next 8 bytes.
  else{
    outputFile.writeBit(1);
    //store symbol in temp char
    unsigned char temp_char = node->symbol;
    int temp_num = 0;

    //write the symbol to the next 8 bytes
    for(int i = 7; i >= 0; i--){
      outputFile.writeBit((temp_char >> i) & 1);
    }
  }
}

/*
 * printSize function wirtes the size of Tree at the begining of  the header.
 *
 */
void printSize(BitInputStream & inputFile, BitOutputStream & outputFile)
{
  //get the size of the file
  int size = inputFile.getBytes().size();
  //use 32 bit to represent the size of the file
  for(int i = 0; i < 32; i++)
  {
    outputFile.writeBit((size >> (31-i)) & 1);
  }
}

int main(int argc, char **argv)
{
  //vector of frequency of each character
  vector<int> freqs(256, 0);
  //create a tree on the stack
  HCTree forCall;
  unsigned char c;

  //open input and output 2 files
  ifstream inputFile;
  inputFile.open(argv[1], ios::binary);
  //open output file
  ofstream outputFile;
  outputFile.open(argv[2], ios::binary);



  //check is input file is empty or not
  if ( inputFile.peek() == ifstream::traits_type::eof() ){
    //close files
    inputFile.close();
    outputFile.close();
    return 0;
  }
  //create a vector of frequency by read the input file
  while(1){	
    //get one character at a time
    c = inputFile.get();
    //chekc if end of file
    if(!(inputFile.good())) break;
    //read next frequency
    freqs[c]++;
  }

  inputFile.close();
  inputFile.open(argv[1]);
  //call build function to build the hoffman tree
  forCall.build(freqs);
  //getRoot() return the root of the hoffman tree
  HCNode* root = forCall.getRoot();

  //get the size of the tree and store it in global variable size
  BitInputStream in(inputFile);
  BitOutputStream out(outputFile);

  in.initialize();
  //write the size to output file
  printSize(in, out); 
  //in order traverse the tree to finish header
  in_order(root, out);
  //encode the character in the tree
  while(1){
    c = in.readByte();
    forCall.encode(c, out);
    if(in.isEnd())  break;
  }
  out.termination();
  //close files
  inputFile.close();
  outputFile.close();
}


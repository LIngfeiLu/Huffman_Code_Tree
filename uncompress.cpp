/*  Junxi Li, A91105747
    Lingfei Lu, A91046735
 */

#include "HCNode.hpp"
#include "HCTree.hpp"
#include <math.h>
#include <stdio.h>
using namespace std;
/*
 * getlength function read the inputfile compressed file and return the size of
 * the tree which is the first 32 bytes
 */
unsigned int getLength(BitInputStream & in){
  //size if the first 32 bit of compressed file, so call readByte 4 times
  unsigned int length = in.readByte();
  length = (length << 8) | in.readByte();
  length = (length << 8) | in.readByte();
  length = (length << 8) | in.readByte();
  //return the size of the origin file
  return length;
}

/*
 * findRoot will traverse the tree the and return the root of the tree
 */
HCNode* findRoot(HCNode* node){
  //while from bottom to top to find the root of the tree
  while(node->p != 0){
    node = node->p;
  }
  return node;
}

/* set a pointer from child to parent for every node 
 */
void linkParents(HCNode* parent, HCNode* child){
  if(child == 0)  return;
  //in order traverse the tree
  child->p = parent;
  linkParents(child, child->c0);
  linkParents(child, child->c1);
}


/*
 * buildTree read the header of the compressed file and reconstruct the tree.
 * if read a '0' means this is a merger node, then create a empty merge node
 * id read a '1' means this is a leave node, then read the next 8 bytes chuck
 * because the next 8 bytes is the character itself
 */
HCNode* buildTree(BitInputStream & inputFile){
  //if read a 1, then recursively create a leave node
  if(inputFile.readBit()){
    return new HCNode(0, inputFile.readByte(), 0, 0, 0);
  }
  //if read a 0, then recursively create a merge node
  else{
    return new HCNode(0, 0, buildTree(inputFile), buildTree(inputFile), 0);
  }
}
/*
 * in order traverse the tree, only for testing
 */
void in_order(HCNode* node){
  if(node == 0) return;
  in_order(node->c0);
  //print symbol to standard out
  cout << node->symbol << endl;
  in_order(node->c1);
}

int main(int argc, char **argv)
{
  //open input and output file
  ifstream inputFile;
  inputFile.open(argv[1], ios::binary);
  ofstream outputFile;
  outputFile.open(argv[2], ios::binary);

  //check is input file is empty
  if ( inputFile.peek() == ifstream::traits_type::eof() ){
    //close input and output file
    inputFile.close();
    outputFile.close();
    return 0;
  }

  //create BitInputStream and BitOutputStream object
  BitInputStream in(inputFile);
  BitOutputStream out(outputFile);

  //create bytes vector
  in.initialize();

  //get the size of the tree
  int length = getLength(in);

  //build the tree and return the root.
  HCNode* root = buildTree(in); 

  //recursively link the parent
  linkParents(root, root->c0);
  //in_order(root);
  HCTree forCall;
  //set the root of forCall
  forCall.setRoot(root);
  int count = 0;
  //decode the already built tree
  while(1){ 
    if(count == length)  break;
    count++;
    //if decode -1, then break
    int store = forCall.decode(in);
    //if(store == -1) break;
    //write to the output file
    for(int i = 7; i >= 0; i--){
      out.writeBit((store >> i) & 1);
    }
  }
  //termination the process
  out.termination();
  //close input and output files
  inputFile.close();
  outputFile.close();
}




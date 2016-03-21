/*  Junxi Li, A91105747
    Lingfei Lu, A91046735
 */

#include "HCTree.hpp"
#include <stack>
using namespace std;

/*
 * recursively delete the the node in the tree
 */
void deleteAll(HCNode *curr)
{
  //if curr is null, return immediately
  if(!curr) return;
  deleteAll(curr->c0);
  deleteAll(curr->c1);
  //delete curr pointer
  delete curr;
}

/*
 * destructor of HCTree
 */
HCTree::~HCTree(){
  deleteAll(root);
  root = 0;
}

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){
  //use priority queue to decide the structure of the tree
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> queue;

  //loop through frequency to create the priority queue
  for(int i = 0; i < freqs.size(); i++){

    if(freqs[i] > 0){
      HCNode *temp_node = new HCNode(freqs[i], i, 0, 0, 0);
      queue.push(temp_node);
    }
  }
  //corner case, is queue is size of 1
  if(queue.size() == 1){
    leaves[queue.top()->symbol] = queue.top();
  }
  //pop node from priority queue. 
  while(queue.size() > 1){
    HCNode *first = queue.top();

    queue.pop();
    HCNode *second = queue.top();
    queue.pop();

    //create node for tree
    HCNode *parent = new HCNode(first->count+second->count, first->symbol, first, second, 0);
    queue.push(parent);

    first->p = parent;
    second->p  = parent;

    if(first->c0 == 0 && first->c1 == 0) leaves[first->symbol] = first;
    if(second->c0 == 0 && second->c1 == 0)  leaves[second->symbol] = second;
  }
  root = queue.top();
  queue.pop();
}



void HCTree::encode(byte symbol, BitOutputStream& out) const
{
  HCNode* temp = leaves[symbol];
  stack<char> st;
  if(temp == root){
    st.push('0');
  }
  while(temp != root){
    if(temp == temp->p->c0) st.push('0');
    else  st.push('1');
    temp = temp->p;
  }
  while(st.size() > 0){
    out.writeBit((st.top() == '0' ? 0 : 1));
    st.pop();
  }
}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const{

  string code = "";

  HCNode* temp = leaves[symbol];
  if(temp == root){
    code += "0";
  }
  //if we are in left child, then write '0' to code
  while(temp != root){
    if(temp == temp->p->c0)  code.insert(0, "0");
    //else write '1' to code
    else  code.insert(0, "1");
    temp = temp->p;
  }
  out << code;
}

int HCTree::decode(BitInputStream& in) const{
  HCNode *curr = root;
  if(!(curr->c0)){
    in.readBit();
    //if(in.isEnd()) return -1;
    return curr->symbol;
  }

  while(curr->c0)
  {
    int bit = in.readBit();
    //if(in.isEnd()) return -1;
    //cout << bit << " in HCTree! \n";
    if(bit == 0 && curr)
    {
      curr = curr->c0;
    }

    else if(bit == 1 && curr)
    {
      curr = curr -> c1;
    }

  }
  return curr->symbol;
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const
{
  HCNode *curr = root;

  char buffer;
  //if curr does not have left child, then break
  if(!(curr->c0))
  {
    in.get(buffer);
    if(!(in.good()))  return -1;
    return curr->symbol;
  }

  //if curr has left child
  while(curr->c0)
  {

    in.get(buffer);
    if(!(in.good()))  return -1;

    //if character is '0', then go to left
    if(buffer == '0' && curr)
      curr = curr->c0;
    //else go to right
    else if(buffer == '1'&& curr) 
      curr = curr->c1;
  }
  return curr->symbol;

}

/*
 * getRoot the call object
 */
HCNode* HCTree::getRoot() const
{
  return root;
}

/*
 * set the root of calling object
 */
void HCTree::setRoot(HCNode* node){
  root = node;
}



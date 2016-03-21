/*  Junxi Li, A91105747
    Lingfei Lu, A91046735
*/
#include "HCNode.hpp"



  /** Less-than comparison, so HCNodes will work in std::priority_queue
   *  We want small counts to have high priority.
   *  And we want to break ties deterministically.
   */
  bool HCNode::operator<(const HCNode& other){
    //compare two node
  	if(count != other.count)
      //if count true if this->count greater than other.count
  		return this->count > other.count;
    //else return true if this->symbol greater than other.symbol
  	return this->symbol > other.symbol;
  }

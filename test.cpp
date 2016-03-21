#include <iostream>
#include <queue>

using namespace std;

int main(){
  priority_queue<int*> a;
  int x = 1;
  int *y = &x;
  a.push(y);
  *y = 2;
  cout << *(a.top()) << endl;

}

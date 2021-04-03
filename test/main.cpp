
#include <iostream>

using namespace std;

int EQ(bool false_condition, const char *msg) {
  cout << msg << " : ";
  if (false_condition) {
    cout << "PASSED\n";
    return 0;
  }
  cout << "FAILED\n";
  exit(1);
}

int main() { return 0; }
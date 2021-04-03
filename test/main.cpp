
#include "register.hpp"
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

void test_assignment() {
  u32 a = 8;
  Register R{&a};
  EQ(R == 8, "Assignment");
}

void test_set_bit() {
  u32 a = 8;
  Register R{&a};

  R[0] = 1;
  EQ(R == (a | 1), "Set bit");

  R[1] = 1;
  EQ(R == (a | 1 | 2), "Set bit");

  R[2] = 1;
  EQ(R == (a | 1 | 2 | 4), "Set bit");
}

void test_clear_bit() {
  u32 a = 0xff;
  Register R{&a};

  R[0] = 0;
  EQ(R == 0xfe, "Clear bit");

  R[1] = 0;
  EQ(R == 0xfc, "Clear bit");

  R[2] = 0;
  EQ(R == 0xf8, "Clear bit");
}

void test_check_bit(){
  u32 a = 0xf;
  Register R{&a};

  EQ(R[3] == 1, "Bit equal");

}


int main() {

  test_assignment();
  test_set_bit();
  test_clear_bit();
  test_check_bit();

  return 0;
}
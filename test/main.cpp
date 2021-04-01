
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

  R.set_bit(0);
  EQ(R == (a | 1), "Set bit");

  R.set_bit(1);
  EQ(R == (a | 1 | 2), "Set bit");

  R.set_bit(2);
  EQ(R == (a | 1 | 2 | 4), "Set bit");
}

void test_clear_bit() {
  u32 a = 0xff;
  Register R{&a};

  R.clear_bit(0);
  EQ(R == 0xfe, "Clear bit");

  R.clear_bit(1);
  EQ(R == 0xfc, "Clear bit");

  R.clear_bit(2);
  EQ(R == 0xf8, "Clear bit");
}

int main() {

  test_assignment();
  test_set_bit();
  test_clear_bit();

  return 0;
}
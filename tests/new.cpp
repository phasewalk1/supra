/*
  This is an example test file that does nothing for now and is only used for
  debugging the 'Tester class'
*/

#include <supra/tester.hpp>

int main() {
  if (1 > 0) {
    return 0;
  } else {
    throw tester::SupraException("This is a test exception");
  }
}
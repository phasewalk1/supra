/*
  This is an example test file that does nothing for now and is only used for
  debugging the 'Tester class'
*/

#include <iostream>
#include <supra/tester.hpp>

#define SUPRA_TEST true

/******************************************************************************
 *                        Define behavior of the test                         *
 ******************************************************************************/
std::optional<testing::SupraException> test() {
  if (1 < 0) {
    return std::nullopt;
  } else {
    return testing::SupraException("This is a test exception");
  }
}

/******************************************************************************
 *                              Run the Test                                  *
 ******************************************************************************/
int main() {
  std::optional<testing::SupraException> status = test();
  switch (status.has_value()) {
  case SUPRA_FAIL:
    std::cerr << status.value().what() << std::endl;
    return 1;
  case SUPRA_PASS:
    return 0;
  }
}
#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>

class Test
{
private:
  /* data */
public:
  Test() = default;
  ~Test();
  Test(const Test &test);
  Test(Test &&test);
  Test &operator=(const Test &test);
  Test &operator=(Test &&test);
};

#endif // TEST_HPP_
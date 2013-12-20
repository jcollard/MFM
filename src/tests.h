#ifndef TESTS_H
#define TESTS_H

#include "manhattandir_test.hpp"
#include "bitfield_test.hpp"
#include "point_test.hpp"

int test_main(int argc, char** argv)
{
  PointTest::Test_pointAdd();
  PointTest::Test_pointMultiply();

  BitFieldTest::Test_bitfieldAllocate();
  BitFieldTest::Test_bitfieldSize();
  BitFieldTest::Test_bitfieldRead();
  BitFieldTest::Test_bitfieldWrite();
  BitFieldTest::Test_bitfieldInsert();

  ManhattanDirTest::Test_manhattandirConversion();

  return 0;
}

#endif /*TESTS_H*/

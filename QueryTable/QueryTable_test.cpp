#define BOOST_TEST_MODULE QueryTableTest
#include <boost/test/included/unit_test.hpp>
#include <string>
#include "QueryTable.h"

using namespace sharedon;

BOOST_AUTO_TEST_SUITE(QueryTableTest)

BOOST_AUTO_TEST_CASE(test1)
{
  QueryTable qt;
  BOOST_CHECK(qt.isAddrHasFile("1.txt", "ABCD") == false);
  BOOST_CHECK(qt.deleteFromFile("1.txt", "ABCD") == -1);
  BOOST_CHECK(qt.addToFile("1.txt", "ABCD") == 0);
  BOOST_CHECK(qt.addToFile("1.txt", "ABCD") == -1);
  BOOST_CHECK(qt.isAddrHasFile("1.txt", "ABCD") == true);
  BOOST_CHECK(qt.addToFile("1.txt", "AAAA") == 0);
  BOOST_CHECK(qt.isAddrHasFile("1.txt", "AAAA") == true);
  BOOST_CHECK(qt.addToFile("2.txt", "ABCD") == 0);
  BOOST_CHECK(qt.isAddrHasFile("2.txt", "ABCD") == true);
  BOOST_CHECK(qt.deleteFromFile("1.txt", "AAAA") == 0);
  BOOST_CHECK(qt.isAddrHasFile("1.txt", "AAAA") == false);
}

BOOST_AUTO_TEST_SUITE_END()


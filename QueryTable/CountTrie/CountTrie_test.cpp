#define BOOST_TEST_MODULE CountTrieTest
#include <boost/test/included/unit_test.hpp>
#include <string>
#include "CountTrie.h"

using namespace sharedon;

BOOST_AUTO_TEST_SUITE(CountTrieTest)

BOOST_AUTO_TEST_CASE(test1)
{
  CountTrie ct;
  BOOST_CHECK(ct.findEntry("abc") == false);
  BOOST_CHECK(ct.findEntry("") == false);
  BOOST_CHECK(ct.getCount() == 0);
  std::string s("aaa");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        s[0] = 'a'+i;
        s[1] = 'a'+j;
        s[2] = 'a'+k;
        BOOST_CHECK(ct.insertEntry(s) == 0);
      }
    }
  }
  BOOST_CHECK(ct.getCount() ==  8);
  BOOST_CHECK(ct.findEntry("aaa") == true);
  BOOST_CHECK(ct.findEntry("aa") == false);
  BOOST_CHECK(ct.findEntry("bbb") == true);
  BOOST_CHECK(ct.findEntry("bbbb") == false);

  BOOST_CHECK(ct.deleteEntry("abcd") == -1);
  BOOST_CHECK(ct.getCount() ==  8);
  BOOST_CHECK(ct.deleteEntry("ab") == -1);
  BOOST_CHECK(ct.getCount() ==  8);
  BOOST_CHECK(ct.deleteEntry("abb") == 0);
  BOOST_CHECK(ct.getCount() ==  7);
  BOOST_CHECK(ct.findEntry("abb") == false);
  BOOST_CHECK(ct.deleteEntry("abb") == -1);
  BOOST_CHECK(ct.getCount() ==  7);

  BOOST_CHECK(ct.findEntry("abb") == false);
  BOOST_CHECK(ct.insertEntry("abb") == 0);
  BOOST_CHECK(ct.getCount() ==  8);
  BOOST_CHECK(ct.findEntry("abb") == true);
}

BOOST_AUTO_TEST_CASE(test2)
{
  CountTrie ct;
  BOOST_CHECK(ct.insertEntry("abc") == 0);
  BOOST_CHECK(ct.getCount() == 1);
  BOOST_CHECK(ct.findEntry("abc") == true);
  BOOST_CHECK(ct.deleteEntry("abc") == 0);
  BOOST_CHECK(ct.getCount() == 0);
  BOOST_CHECK(ct.findEntry("abc") == false);
  BOOST_CHECK(ct.insertEntry("abc") == 0);
  BOOST_CHECK(ct.getCount() == 1);
  BOOST_CHECK(ct.findEntry("abc") == true);
  BOOST_CHECK(ct.deleteEntry("abc") == 0);
  BOOST_CHECK(ct.getCount() == 0);
  BOOST_CHECK(ct.findEntry("abc") == false);
}

BOOST_AUTO_TEST_CASE(test3)
{
  CountTrie ct;
  std::string s("aaa");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        s[0] = 'a'+i;
        s[1] = 'a'+j;
        s[2] = 'a'+k;
      }
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()




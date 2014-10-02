#define BOOST_TEST_MODULE CountTrieNodeTest
#include "CountTrieNode.h"
#include <boost/test/included/unit_test.hpp>

using namespace sharedon;

BOOST_AUTO_TEST_SUITE(CountTrieNodeTest)

BOOST_AUTO_TEST_CASE(test1)
{
  CountTrieNode* p1 = new CountTrieNode;
  p1->addRecord('a');
  p1->addRecord('b');
  p1->addRecord('b');
  CountTrieNode* p2 = p1->getNode('a');
  CountTrieNode* p3 = p1->getNode('b'); 
  CountTrieNode* pnull = p1->getNode('c');
  p2->addRecord('d');
  CountTrieNode* p4 = p2->getNode('d');
  BOOST_CHECK(pnull == NULL);
  BOOST_CHECK(p1->branchNum() == 2);
  BOOST_CHECK(p2->branchNum() == 1);
  BOOST_CHECK(p3->branchNum() == 0);
  BOOST_CHECK(p4->branchNum() == 0);
  delete p1;
}

BOOST_AUTO_TEST_CASE(test2)
{

  CountTrieNode* p1 = new CountTrieNode;
  p1->addRecord('a');
  p1->addRecord('b');
  p1->addRecord('b');
  CountTrieNode* p2 = p1->getNode('a');
  CountTrieNode* p3 = p1->getNode('b'); 
  CountTrieNode* pnull = p1->getNode('c');
  p2->addRecord('d');
  CountTrieNode* p4 = p2->getNode('d');
  p2->deleteRecord('e');
  BOOST_CHECK(p2->branchNum() == 1);
  p2->deleteRecord('d');
  BOOST_CHECK(p2->branchNum() == 0);
  p1->deleteRecord('a');
  BOOST_CHECK(p1->branchNum() == 1);
  p1->deleteRecord('b');
  BOOST_CHECK(p1->branchNum() == 0);
  delete p1;
}

BOOST_AUTO_TEST_CASE(test3)
{
  CountTrieNode* p1 = new CountTrieNode;
  p1->addRecord('a');
  p1->addRecord('b');
  p1->addRecord('b');
  CountTrieNode* p2 = p1->getNode('a');
  CountTrieNode* p3 = p1->getNode('b'); 
  CountTrieNode* pnull = p1->getNode('c');
  p2->addRecord('d');
  CountTrieNode* p4 = p2->getNode('d');
  p2->deleteRecord('e');
  BOOST_CHECK(p2->branchNum() == 1);
  p1->deleteRecord('a');
  BOOST_CHECK(p1->branchNum() == 1);
  delete p1;
}

BOOST_AUTO_TEST_SUITE_END()



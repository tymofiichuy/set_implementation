#include <iostream>
#include <gtest/gtest.h>
#include "multitype_set.h"

TEST(StructureTest, LNKTest){
  EXPECT_EQ(1, 1);
}

TEST(BasicOperationsTest, PositiveDataComparisonTest){
  node a;
  a.data = 1;
  EXPECT_TRUE(a.data_comparison(1));
}

TEST(BasicOperationsTest, NegativeDataComparisonTest_type){
  node a;
  a.data = 1;
  EXPECT_FALSE(a.data_comparison('a'));
}

TEST(BasicOperationsTest, NegativeDataComparisonTest_value){
  node a;
  a.data = 1;
  EXPECT_FALSE(a.data_comparison(2));
}


TEST(BasicSetLogicTest, SingleInsertionTest){
  multitype_set S;
  EXPECT_NO_THROW(S.set_insert(1));
}

TEST(BasicSetLogicTest, MultipleInsertionTest){
  multitype_set S;
  EXPECT_NO_THROW({
    S.set_insert(1);
  S.set_insert(5);
  });
}

TEST(BasicSetLogicTest, MultipleTypeInsertionTest){
  multitype_set S;
  EXPECT_NO_THROW({
    S.set_insert(1);
  S.set_insert('a');
  S.set_insert(1.2F);
  S.set_insert("nia");
  });
}

TEST(BasicSetLogicTest, NegativeInsertionTest){
  multitype_set S;
  S.set_insert(1);
  EXPECT_ANY_THROW(S.set_insert(1));
}

TEST(BasicSetLogicTest, PositiveSearchTest){
  multitype_set S;
  S.set_insert(1.0F);
  S.set_insert('a');
  S.set_insert(2);
  ASSERT_TRUE(S.set_search(2));
}

TEST(BasicSetLogicTest, NegativeSearchTest){
  multitype_set S;
  S.set_insert(1.0F);
  S.set_insert('a');
  S.set_insert(2);
  ASSERT_FALSE(S.set_search(2.0F));
}

TEST(BasicSetLogicTest, PositiveDeleteTest){
  multitype_set S;
  S.set_insert(1);
  EXPECT_NO_THROW({
    S.set_delete(1);
    S.set_insert(1);
});
}

TEST(BasicSetLogicTest, NegativeDeleteTest){
  multitype_set S;
  S.set_insert(2);
  EXPECT_ANY_THROW(S.set_delete(1));
}

TEST(BasicSetLogicTest, SetClearTest){
  multitype_set S;
  S.set_insert(1);
  S.set_insert(2);
  S.set_clear();
  ASSERT_FALSE(S.head);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
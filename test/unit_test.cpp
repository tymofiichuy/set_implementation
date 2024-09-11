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

  ASSERT_TRUE(S.set_search(1.0F));
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

TEST(AdvancedSetLogicTest, PositiveIsSubsetTest){
  multitype_set A;
  multitype_set B;

  A.set_insert(1);
  A.set_insert('a');
  A.set_insert(2.0F);

  B.set_insert('a');

  ASSERT_TRUE(A.is_subset(B));
}

TEST(AdvancedSetLogicTest, NegativeIsSubsetTest){
  multitype_set A;
  multitype_set B;

  A.set_insert(1);
  A.set_insert('a');
  A.set_insert(2.0F);

  B.set_insert('b');

  ASSERT_FALSE(A.is_subset(B));
}

TEST(AdvancedSetLogicTest, EqualtyTest){
  multitype_set A;
  multitype_set B;

  A.set_insert(1);
  A.set_insert('a');

  B.set_insert(1);
  B.set_insert('a');

  ASSERT_TRUE(A == B);
}

TEST(AdvancedSetLogicTest, NonEqualtyTest){
  multitype_set A;
  multitype_set B;

  A.set_insert(1);
  A.set_insert('a');

  B.set_insert(1);
  B.set_insert('b');

  ASSERT_FALSE(A == B);
}

TEST(AdvancedSetLogicTest, SetUnionTest){
  multitype_set A;
  multitype_set B;
  multitype_set* C;
  multitype_set D;

  A.set_insert(1);
  A.set_insert('a');

  B.set_insert(1);
  B.set_insert('b');

  C = A.set_union(B);

  D.set_insert(1);
  D.set_insert('a');
  D.set_insert('b');

  ASSERT_TRUE(*C == D);
  delete C;
}

TEST(AdvancedSetLogicTest, SetIntersectionTest){
  multitype_set A;
  multitype_set B;
  multitype_set* C;
  multitype_set D;

  A.set_insert(1);
  A.set_insert('a');

  B.set_insert(1);
  B.set_insert('b');

  C = A.set_intersection(B);

  D.set_insert(1);

  ASSERT_TRUE(*C == D);
  delete C;
}

TEST(AdvancedSetLogicTest, SetDifferenceTest){
  multitype_set A;
  multitype_set B;
  multitype_set* C;
  multitype_set D;

  A.set_insert(1);
  A.set_insert('a');

  B.set_insert(1);
  B.set_insert('b');

  C = A.set_difference(B);

  D.set_insert('a');

  ASSERT_TRUE(*C == D);
  delete C;
}

TEST(AdvancedSetLogicTest, SetSymDifferenceTest){
  multitype_set A;
  multitype_set B;
  multitype_set* C;
  multitype_set D;

  A.set_insert(1);
  A.set_insert('a');

  B.set_insert(1);
  B.set_insert('b');

  C = A.set_sym_difference(B);

  D.set_insert('a');
  D.set_insert('b');

  ASSERT_TRUE(*C == D);
  delete C;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
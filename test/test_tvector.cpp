#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(v1, v2);

}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(v1);
	EXPECT_NE(&v1, &v2);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v[-2] = 9);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v[v.size() + 1] = 9);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v1(5);
	for (int i = 0; i < v1.size(); ++i) {
		v1[i] = i;
	}
	TDynamicVector<int> chek(v1);
	v1 = v1;
	EXPECT_EQ(v1, chek);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	const int val = 5;
	TDynamicVector<int> v1(val), v2(val);
	v1[0] = 9;
	v2[0] = 4;
	v2 = v1;
	EXPECT_EQ(v1, v2);

}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(8);
	v2 = v1;
	EXPECT_EQ(v1.size(), v2.size());

}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int>	v1(5);
	TDynamicVector<int> v2(4);
	v1[0] = 9;
	v2[0] = 4;
	v2 = v1;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	for (int i = 0; i < v1.size(); ++i) {
		v1[i] = 1;
		v2[i] = 1;
	}
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(5);
	for (int i = 0; i < v1.size(); ++i) {
		v1[i] = 1;
	}
	EXPECT_TRUE(v1 == v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(5), v2(6);
	EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(5), chek(5);
	for (int i = 0; i < v1.size(); ++i) {
		v1[i] = 3;
		chek[i] = 4;
	}
	v1 = v1 + 1;
	EXPECT_EQ(v1, chek);

}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(5), chek(5);
	for (int i = 0; i < v1.size(); ++i) {
		v1[i] = 4;
		chek[i] = 3;
	}
	v1 = v1 - 1;
	EXPECT_EQ(v1, chek);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(5), chek(5);
	for (int i = 0; i < v1.size(); ++i) {
		v1[i] = 4;
		chek[i] = 12;
	}
	v1 = v1 * 3;
	EXPECT_EQ(v1, chek);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5), v2(5), chek(5);
	for (int i = 0; i < v1.size(); ++i) {
		v1[i] = 2;
		v2[i] = 3;
		chek[i] = 5;
	}
	v1 = v1 + v2;
	EXPECT_EQ(v1, chek);

}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(8), v2(10);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5), v2(5), chek(5);
	for (int i = 0; i < v1.size(); ++i) {
		v1[i] = 2;
		v2[i] = 3;
		chek[i] = 1;
	}
	v1 = v2 - v1;
	EXPECT_EQ(v1, chek);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(8), v2(10);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5), v2(5);
	int chek = 0;
	for (int i = 0; i < v1.size(); ++i) {
		v1[i] = 1;
		v2[i] = 0;
	}
	int res = v1 * v2;
	EXPECT_EQ(res, chek);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(8), v2(10);
	ASSERT_ANY_THROW(v1 * v2);
}


// ------------ TESTS MOVE ------- //

TEST(TDynamicVector, moved_values) {
	TDynamicVector<int> v1(3), chek(3);
	for (int i = 0; i < v1.size(); ++i) {
		v1[i] = i;
		chek[i] = i;
	}
	TDynamicVector<int> v2 = std::move(v1);
	EXPECT_EQ(v2, chek);
}

TEST(TDynamicVector, null_size_of_original_vector) {
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2 = std::move(v1);
	EXPECT_EQ(0, v1.size());

}

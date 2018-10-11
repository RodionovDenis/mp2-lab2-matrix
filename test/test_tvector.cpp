#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one) //скопированный вектор равен исходному
{
	TVector<int> v(20, 1);
	TVector<int> v_copy = v;
	EXPECT_EQ(v, v_copy);
}

TEST(TVector, copied_vector_has_its_own_memory) //скопированный вектор имеет свою память
{
	TVector<int> v(20, 1);
	TVector<int> v_copy = v;
	EXPECT_NE(&v, &v_copy);
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index) //бросает искл, когда заданный элемент с отрицательным индексом
{
	TVector<int> v(4);
	ASSERT_ANY_THROW(v[-1]);
}

TEST(TVector, throws_when_set_element_with_too_large_index) //бросает искл, когда установленный элемент со слишком большим индексом
{
	TVector<int> v(4, 2);
	ASSERT_ANY_THROW(v[6]);
}

TEST(TVector, can_assign_vector_to_itself) //назначить вектор самому себе
{
	TVector<int> v(4, 2);
	ASSERT_NO_THROW(v = v);
	v = v;
	TVector<int> v1 = v;
	EXPECT_EQ(v, v1);
}

TEST(TVector, can_assign_vectors_of_equal_size) //присвоить векторы равного размера
{
	TVector<int> v1(5, 0), v2(5, 2);
	v1 = v2;
	EXPECT_EQ(v1, v2);
}

TEST(TVector, assign_operator_change_vector_size) //после присваивания с разными размерами меняется размер
{
	TVector<int> v1(10, 0), v2(12, 3);
	v1 = v2;
	EXPECT_EQ(v1.GetSize(), v2.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size) //можно присваивать с разными размерами
{
	TVector<int> v1(7, 0), v2(5, 2);
	v1 = v2;
	EXPECT_EQ(v1, v2);
}

TEST(TVector, compare_equal_vectors_return_true) //сравнивая равные векторы, вернется true
{
	TVector<int> v1(7, 0), v2(7, 0);
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i;
		v2[i] = i;
	}
	EXPECT_EQ(true, v1 == v2);
}

TEST(TVector, compare_vector_with_itself_return_true) //сравнить вектор с собой true
{
	TVector<int> v1(7, 0);
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	EXPECT_EQ(true, v1 == v1);
}

TEST(TVector, vectors_with_different_size_are_not_equal) //векторы разного размера не равны
{
	TVector<int> v1(7, 0), v2(10, 0);
	EXPECT_EQ(false, v1 == v2);
}

TEST(TVector, can_add_scalar_to_vector) //можно добавить скаляр в вектор
{
	TVector<int> v1(7, 0), v2;
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	v2 = v1 + 2;
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = i + 2;
	EXPECT_EQ(v1, v2);
}

TEST(TVector, can_subtract_scalar_from_vector) //вычитание скаляра
{
	TVector<int> v1(7, 0), v2;
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	v2 = v1 - 2;
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = i - 2;
	EXPECT_EQ(v1, v2);
}

TEST(TVector, can_multiply_scalar_by_vector) //умножение на скаляр
{
	TVector<int> v1(7, 0), v2;
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	v2 = v1 * 2;
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = i * 2;
	EXPECT_EQ(v1, v2);
}

TEST(TVector, can_add_vectors_with_equal_size) //можно складывать вектора равных размеров
{
	TVector<int> v1(5), v2(5),v3;
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i;
		v2[i] = i;
	}
	v3 = v1 + v2;
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = 2 * i;
	EXPECT_EQ(v3, v1);
}

TEST(TVector, cant_add_vectors_with_not_equal_size) //запрещено сложение с разным размером
{
	TVector<int> v1(5), v2(3);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size) //можно вычитать разные размеры
{
	TVector<int> v1(5), v2(5), v3;
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i;
		v2[i] = i;
	}
	v3 = v1 - v2;
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = 0;
	EXPECT_EQ(v3, v1);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size) //нельзя вычитать разные размеры
{
	TVector<int> v1(5), v2(3);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size) // можно искать скал произв разных размеров
{
	TVector<int> v1(5), v2(5);
	int res = 0;
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i;
		v2[i] = i;
	}
	res = v1 * v2;
	EXPECT_EQ(30,res);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size) //нельзя искать скал произв разных размеров
{
	TVector<int> v1(5), v2(3);
	ASSERT_ANY_THROW(v1 * v2);
}


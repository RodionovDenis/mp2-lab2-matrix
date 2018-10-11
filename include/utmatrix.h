// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <iomanip> 

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

string exeption = "Data isn't correct";

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
	  for (int i = 0; i < v.Size; i++)
		  out << v.pVector[i] <<' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s = 10, int si = 0)
{
	if (s <= 0 || si < 0 || s > MAX_VECTOR_SIZE)
		throw exeption;
	Size = s;
	StartIndex = si;
	pVector = new ValType[s];
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos >= StartIndex + Size || pos < 0)
		throw exeption;
	return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (this == &v)
		return true;
	if (StartIndex != v.StartIndex || Size != v.Size)
		return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != v.pVector[i])
			return false;
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return ((*this) == v) ? false : true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this == &v)
		return *this;
	if (Size != v.Size)
	{
		Size = v.Size;
		delete[] pVector;
		pVector = new ValType[Size];
	}
	if (StartIndex != v.StartIndex)
		StartIndex = v.StartIndex;
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> v((*this).Size, (*this).StartIndex);
	for (int i = 0; i < Size; i++)
		v.pVector[i] = pVector[i] + val;
	return v;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	return (*this) + (-1 * val);
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> mul((*this).Size, (*this).StartIndex);
	for (int i = 0; i < Size; i++)
		mul.pVector[i] = pVector[i] * val;
	return mul;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size != v.Size)
		throw exeption;
	TVector<ValType> add(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		add.pVector[i] = pVector[i] + v.pVector[i];
	return add;

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size != v.Size)
		throw exeption;
	TVector<ValType> diff(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		diff.pVector[i] = pVector[i] - v.pVector[i];
	return diff;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (Size != v.Size)
		throw exeption;
	ValType mul = {};
	for (int i = 0; i < Size; i++)
		mul += pVector[i] * v.pVector[i];
	return mul;
} /*-------------------------------------------------------------------------*/


//Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector< TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

//   ввод / вывод
  friend istream & operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
      for (int i = 0; i < mt.Size; i++)
	  {
		  for (int j = 0; j < i; j++)
			  out << "0"<<' ';
		  out << mt.pVector[i]<< endl;
	  }
	  return out;
  }
};
template <class ValType>
TMatrix<ValType>::TMatrix(int s = 10) : TVector< TVector<ValType> >(s)
{
	if (s < 0 || s > MAX_MATRIX_SIZE)
		throw exeption;
	for (int i = 0; i < Size; i++)
	{
		TVector<ValType> v(Size - i, i);
		pVector[i] = v;
	}

} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) : TVector< TVector<ValType> >(mt.Size)
{
	for (int i = 0; i < Size; i++)
		pVector[i] = mt.pVector[i];
	
}
template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) : TVector< TVector<ValType> >(mt.Size)
{
	for (int i = 0; i < Size; i++)
		pVector[i] = mt.pVector[i];
}
template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this == &mt)
		return true;
	if (Size != mt.Size)
		return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != mt.pVector[i])
			return false;
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return (*this == mt) ? false : true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this == &mt)
		return *this;
	if (Size != mt.Size)
	{
		Size = mt.Size;
		delete[] pVector;
		pVector = new TVector<ValType>[Size];
	}
	for (int i = 0; i < Size; i++)
		pVector[i] = mt.pVector[i];
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size)
		throw exeption;
	TMatrix<ValType> matrix_add(Size);
	for (int i = 0; i < Size; i++)
		matrix_add.pVector[i] = pVector[i] + mt.pVector[i];
	return matrix_add;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size)
		throw exeption;
	TMatrix<ValType> matrix_diff(Size);
	for (int i = 0; i < Size; i++)
		matrix_diff.pVector[i] = pVector[i] - mt.pVector[i];
	return matrix_diff;
} /*-------------------------------------------------------------------------*/

 //TVector О3 Л2 П4 С6
 //TMatrix О2 Л2 П3 С3
#endif

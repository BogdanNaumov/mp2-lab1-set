// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <iostream>
#include <string>

using namespace std;

typedef unsigned int TELEM;

class TBitField
{
private:
  int  BitLen; // длина битового поля - макс. к-во битов
  TELEM *pMem; // память для представления битового поля
  int  MemLen; // к-во эл-тов Мем для представления бит.поля

  // методы реализации
  int   GetMemIndex(const int n) const // индекс в pМем для бита n       (#О2)
  {
	  if (n<0 || n>BitLen) { throw"index not found";}
	  return (n / (sizeof(TELEM) * 8));
  }
  TELEM GetMemMask (const int n) const; // битовая маска для бита n       (#О3)
public:
	TBitField::TBitField(int len)
	{
		if (len < 0) { throw"len<0";}
		BitLen = len;
		if (len%sizeof(TELEM)==0){ MemLen = len / sizeof(TELEM); }
		else
		{
			MemLen = (len / sizeof(TELEM)) + 1;
			pMem = new TELEM[MemLen];
			for (int i = 0; i < MemLen; i++) { pMem[i] = 0; }
		}
		
	}      
	TBitField::TBitField(const TBitField& bf)    //                                   (#П1)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (size_t i = 0; i < MemLen; i++) { pMem[i] = bf.pMem[i];}
	}
	TBitField::~TBitField()                      //                                    (#С)
	{
		if (pMem != nullptr) { delete[] pMem;}
		pMem = nullptr;
		BitLen = 0;
		MemLen = 0;
	}

  // доступ к битам
  int GetLength(void) const      // получить длину (к-во битов)           (#О)
  {
	  return BitLen;
  }
  void SetBit(const int n)       // установить бит                       (#О4)
  {

  }
  void ClrBit(const int n)       // очистить бит                         (#П2)
  {

  }
  int  GetBit(const int n) const // получить значение бита               (#Л1)
  {

  }

  // битовые операции
  int operator==(const TBitField &bf) const // сравнение                 (#О5)
  {
	  int flag = 1;
	  if ((BitLen == bf.BitLen) && (MemLen == bf.MemLen)) 
	  {
		  for (int i = 0; i < MemLen; i++) { if (pMem[i] != bf.pMem[i]) { flag = 0; break; } }
	  }
	  else { flag = 0; }
	  return flag;
  }
  int operator!=(const TBitField &bf) const // сравнение
  {

  }
  TBitField& operator=(const TBitField &bf) // присваивание              (#П3)
  {
	  if (this != &bf)
	  {
		  return *this;
		  delete[] pMem;
		  BitLen = bf.BitLen;
		  MemLen = bf.MemLen;
		  pMem = new TELEM[MemLen];
		  for (int i = 0; i < MemLen; i++) { pMem[i] = bf.pMem[i]; }
	  }
	  return *this;
  }
  TBitField  operator|(const TBitField &bf); // операция "или"            (#О6)
  TBitField  operator&(const TBitField &bf); // операция "и"              (#Л2)
  TBitField  operator~(void);                // отрицание                  (#С)

  friend istream &operator>>(istream &istr, TBitField &bf)       //      (#О7)
  {
	  string tmp;
	  istr >> tmp;
	  if (tmp.size() != bf.GetLength()) 
	  {
		  throw"unsing lenght";
	  }
	  else 
	  {
		  for (int i = 0; i < bf.GetLength(); i++) 
		  {
			  if (tmp[i] == '0') 
			  {
				  bf.ClrBit(i);
			  }
			  if (tmp[i] == '1')
			  {
				  bf.SetBit(i);
			  }
			  else { throw "string unsigned";}
		  }
	  }
  }
  friend ostream& operator<<(ostream& ostr, const TBitField& bf) //      (#П4)
  {
	  for (int i = 0; i < bf.GetLength(); i++) 
	  {
		  if (bf.GetBit(i)) { ostr << 1; }
		  else { ostr << 0; }
	  }
  }
};
// Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до BitLen
//   массив pМем рассматривается как последовательность MemLen элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)
// О8 Л2 П4 С2

#endif

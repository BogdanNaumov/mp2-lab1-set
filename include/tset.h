// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество

#ifndef __SET_H__
#define __SET_H__

#include "tbitfield.h"

class TSet
{
private:
  int MaxPower;       // максимальная мощность множества
  TBitField BitField; // битовое поле для хранения характеристического вектора
public:
    TSet::TSet(int mp) :BitField(mp) 
    {
        MaxPower = mp;
    }
  TSet::TSet(const TSet &s):BitField(s.BitField)      // конструктор копирования
  {
      MaxPower = s.MaxPower;
  }
  TSet(const TBitField& bf); // конструктор преобразования типа
  operator TBitField();      // преобразование типа к битовому полю
  // доступ к битам
  int GetMaxPower(void) const;     // максимальная мощность множества
  void InsElem(const int Elem)       // включить элемент в множество
  {
      if (Elem<0 || Elem>MaxPower) { throw"error";}
      BitField.SetBit(Elem);
  }
  void DelElem(const int Elem)       // удалить элемент из множества
  {
      if (Elem<0 || Elem>MaxPower) { throw"error";}
      BitField.clr
  }
  int TSet::IsMember(const int Elem) const // проверить наличие элемента в множестве
  {
      if (Elem<0 || Elem>MaxPower) {
          throw exception("неверное значение ELEM");
      }
      return BitField.GetBit(Elem);
  }
  // теоретико-множественные операции
  int operator== (const TSet &s) const; // сравнение
  int operator!= (const TSet &s) const; // сравнение
  TSet& operator=(const TSet &s);  // присваивание
  TSet operator+ (const int Elem); // объединение с элементом
                                   // элемент должен быть из того же универса
  TSet operator- (const int Elem); // разность с элементом
                                   // элемент должен быть из того же универса
  TSet operator+ (const TSet &s);  // объединение
  TSet operator* (const TSet &s);  // пересечение
  TSet operator~ (void);           // дополнение

  friend istream &operator>>(istream &istr, TSet &bf);
  friend ostream &operator<<(ostream &ostr, const TSet &bf);
};
#endif

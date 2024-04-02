//
// (c) 2024 S-Patriarch
// Строковый калькулятор. Версия 1.2.1
//
#ifndef PL_CONIO_HH
#include "pl/conio.hh"
#endif

#include <iostream>
#include <stack>
#include <cmath>
//------------------------------------------------------------------------------
namespace cl {
   const double PI = std::acos(-1);
   //---------------------------------------------------------------------------
   double sin(double x) {return (std::round(std::sin(x)*10000000)/10000000);}
   //---------------------------------------------------------------------------
   double cos(double x) {return (std::round(std::cos(x)*10000000)/10000000);}
   //---------------------------------------------------------------------------
   double ctg(double x) 
   {
      double a = cos(x);
      double b = sin(x);
      return (a/b);
   }
}
//------------------------------------------------------------------------------
struct Leksema {
   // структура, описывающая любое число или операцию
   char _type;    // 0 для чисел, '+' для операции сложения и т.д.
   double _value; // значение
};
//------------------------------------------------------------------------------
bool maths(std::stack<Leksema>& sn, std::stack<Leksema>& so, Leksema& item)
   // матемиатиическая функция, которая производит расчеты
   // функция имеет тип bool, чтобы при возникновении какой-либо ошибки
   // возвращать false
{
   double a {};
   double b {};
   double res {};
   bool is_res {true};
   
   a = sn.top()._value; // берется верхнее число из стека с числами
   sn.pop();            // удаляется верхнее число из стека с числами

   // проверяется тип верхней операции из стека с операциями
   switch (so.top()._type) { 
   case '+': // если тип верхней операции из стека с операциями сложение
      b = sn.top()._value;
      sn.pop();
      res = a+b;  
      item._type = '0';
      item._value = res;
      sn.push(item); // результат операции кладется обратно в стек с числами
      so.pop();
      break;
   case '-': 
      b = sn.top()._value;
      sn.pop();
      res = b-a;
      item._type = '0';
      item._value = res;
      sn.push(item);
      so.pop();
      break;
   case '*': 
      b = sn.top()._value;
      sn.pop();
      res = a*b;  
      item._type = '0';
      item._value = res;
      sn.push(item);
      so.pop();
      break;
   case '/': 
      b = sn.top()._value;
      if (a==0) {
         std::cerr << "E: Деление на 0.\n";
         is_res = false;
      }
      else {
         sn.pop();
         res = b/a;  
         item._type = '0';
         item._value = res;
         sn.push(item);
         so.pop();
      }
      break;
   case '^': 
      b = sn.top()._value;
      sn.pop();
      res = std::pow(b,a);
      item._type = '0';
      item._value = res;
      sn.push(item);
      so.pop();
      break;
   case 's': 
      res = cl::sin(a);  
      item._type = '0';
      item._value = res;
      sn.push(item);
      so.pop();
      break;
   case 'c': 
      res = cl::cos(a);  
      item._type = '0';
      item._value = res;
      sn.push(item);
      so.pop();
      break;
   case 't':
      if (cl::cos(a)==0) {
         std::cerr << "E: Неверный аргумент для тангенса.\n";
         is_res = false;
      }
      else {
         res = std::tan(a);  
         item._type = '0';
         item._value = res;
         sn.push(item);
         so.pop();
      }
      break;
   case 'g': 
      if (cl::sin(a)==0) {
         std::cerr << "E: Неверный аргумент для котангенса.\n";
         is_res = false;
      }
      else {
         res = cl::ctg(a);  
         item._type = '0';
         item._value = res;
         sn.push(item);
         so.pop();
      }
      break;
   case 'e': 
      res = std::exp(a);  
      item._type = '0';
      item._value = res;
      sn.push(item);
      so.pop();
      break;
   default:
      std::cerr << "E:\n";
      is_res = false;
      break;
  	}
   return is_res;
}
//------------------------------------------------------------------------------
int get_rang(char ch)
{
   if (ch=='+' || ch=='-') return 1;
   if (ch=='*' || ch=='/') return 2;
   if (ch=='^') return 3;
   if (ch=='s' || ch=='c' || ch=='t' || ch=='g' || ch=='e') return 4;
   return 0;
}
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
   std::cout << pl::mr::clrscr;
   std::cout << "Строковый калькулятор. Версия 1.2.1\n"
             << "(c) 2024 S-Patriarch\n\n";
   std::cout << "Для использования:\n"
             << "  - числа Пи   введите 'p'\n"
             << "  - числа Е    введите 'exp(1)'\n"
             << "  - тангенса   введите 'tan(x)'\n"
             << "  - котангенса введите 'ctg(x)'\n\n";
   std::cout << "Пример:\n"
             << "  Выражение: sin(exp(6)/3-5)^2+cos(exp(6)/3-5)^2\n"
             << "  Ответ:     1\n\n";

   std::cout << "Выражение: ";
   
   Leksema item;           // объект типа Leksema
   std::stack<Leksema> sn; // стек с числами
   std::stack<Leksema> so; // стек с операциями

   char ch {}; // переменная в которую будет записываться текущий 
               // обрабатываемый символ
   double value {};
   bool is_flag {1};

   for (;;) {
      ch = std::cin.peek(); // смотрим на первый символ
      if (ch=='\n') break;  // если достигнут конец строки, выходим из цикла
      if (ch==' ') {
         std::cin.ignore();
         continue;
      }
      if (ch=='s' || ch=='c' || ch=='t' || ch=='e') {
         char arr[3];
         for (int i=0; i!=3; i++) {
            ch = std::cin.peek();
            arr[i] = ch;
            std::cin.ignore();
         }
         if (arr[0]=='s' && arr[1]=='i' && arr[2]=='n') {
            item._type = 's';
            item._value = 0;
            so.push(item);
            continue;
         }
         if (arr[0]=='c' && arr[1]=='o' && arr[2]=='s') {
            item._type = 'c';
            item._value = 0;
            so.push(item);
            continue;
         }
         if (arr[0]=='t' && arr[1]=='a' && arr[2]=='n') {
            item._type = 't';
            item._value = 0;
            so.push(item);
            continue;
         }
         if (arr[0]=='c' && arr[1]=='t' && arr[2]=='g') {
            item._type = 'g';
            item._value = 0;
            so.push(item);
            continue;
         }
         if (arr[0]=='e' && arr[1]=='x' && arr[2]=='p') {
            item._type = 'e';
            item._value = 0;
            so.push(item);
            continue;
         }
      }
      if (ch=='p') {
         item._type = '0';
         item._value = cl::PI;
         sn.push(item);
         is_flag = 0;
         std::cin.ignore();
         continue;   
      }
      if ((ch>='0' && ch<='9') || (ch=='-' && is_flag==1)) { // если прочитано число
         std::cin >> value;
         item._type = '0';
         item._value = value;
         sn.push(item); // число кладется в стек с числами
         is_flag = 0;
         continue;   
      }
      // если прочитана операция
      if (ch=='+' || (ch=='-' && is_flag==0) || ch=='*' || ch=='/' || ch=='^') {
         // если стек пуст
         if (so.size()==0) {
            item._type = ch;
            item._value = 0;
            so.push(item);
            std::cin.ignore();
            continue;
         }
         // если стек не пуст, но приоритет текущей операции выше верхней в 
         // стеке операций
         if (so.size()!=0 && get_rang(ch)>get_rang(so.top()._type)) {
            item._type = ch;
            item._value = 0;
            so.push(item);
            std::cin.ignore();
            continue;
         }
         // если стек не пуст, но приоритет текущей операции ниже либо равен
         // верхней в стеке операций
         if (so.size()!=0 && get_rang(ch)<=get_rang(so.top()._type)) {
            if (maths(sn,so,item)==false) return 0;
            continue;
         }
      }
      if (ch=='(') {
         item._type = ch;
         item._value = 0;
         so.push(item);
         std::cin.ignore();
         continue;
      }
      if (ch==')') {
         while (so.top()._type!='(') {
            if (maths(sn,so,item)==false) return 0;
            else continue;   
         }
         so.pop();
         std::cin.ignore();
         continue;
      }
      else {
         std::cout << "E: Неверно введено выражение.\n";
         return 0;
      }   
   }
   while (so.size()!=0) {
      if (maths(sn,so,item)==false) return 0;
      else continue;   
   }

   std::cout << "Ответ:     " << sn.top()._value << "\n\n";
   return 0;
}


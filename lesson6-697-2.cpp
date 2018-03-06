// Section CSC160 - Computer Science I: C++

// File Name:lesson7_697_2

// Student:Aidan Coopman

// Homework Number:lesson 7 #2

// Description: I programmed the problem as stated in the textbook. The overloaded operators << and >> confused me
// in the class instructions so I followed the textbook description wanting the format a/b

// Last Changed:



#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//decalring a class
class Rational
{
  
public :
  
  //constructors and destructor
  Rational();
  //since the default is y=1, it cam take whole numbers
  Rational(int x, int y=1);
  ~Rational();
  
  
  //friend functions with overloaded operators
  friend Rational operator + (Rational & in1, Rational &in2);
  friend ostream &operator << (ostream & out, Rational & c);  
  friend istream &operator >> (istream & in, Rational & x);  
  friend Rational operator - (Rational & in1, Rational &in2);
  friend Rational operator * (Rational & in1, Rational &in2);
  friend Rational operator / (Rational & in1, Rational &in2);
  
  //comparison operators
  friend bool operator == (Rational & in1, Rational &in2);
  friend bool operator < (Rational & in1, Rational &in2);
  friend bool operator <= (Rational & in1, Rational &in2);
  friend bool operator > (Rational & in1, Rational &in2);
  friend bool operator >= (Rational & in1, Rational &in2);
  
  //a member function to return the current numerator and denominator.
  int get_num();
  int get_den();
  
private :
  //a private member variables to hold the numerator and denominator values
  int num;
  int den;
  
  //this reduces the fraction and if negative, puts the numerator as the negative
  void reduce(); 
};

//------------------------------------------------------------------------

int main( )
{
  //test the three constructor cases
  Rational num1(3,4);
  Rational num2(1,2);
  Rational num3(17);
  Rational out;
  Rational a;
  
  //this is from the instructions on page 697 on how these operators want to be overloaded
  cout << "Testing << and >> operators, please enter num and den in the format 'a/b'\n";
  cin >> a;
  cout << "You entered the fraction " << a << endl;
  
  out = num1+num2;
  cout << "Test 1 for adding:                   " << num1 << " + " << num2 << " = " << out << endl;
  
  out = num1-num2;
  cout << "Test 2 for subtraction:              " << num1 << " - " << num2 << " = "<< out << endl;
  
  out = num1*num2;
  cout << "Test 3 for multiplying:              " << num1 << " * " << num2 << " = "<< out << endl;
  
  out = num1/num3;  
  cout << "Test 4 for dividing:                 " << num1 << " / " << num2 << " = "<< out << endl;
  
  cout << "Test 6 for eq:                       ";
  if(num1==num2) cout << "True\n";
  else         cout << "False\n";
  
  cout << "Test 7 for less:                     ";
  bool is_less = (num1<num2);
  if(is_less == 0) cout << "False\n";
  else             cout << "True\n";
  
  cout << "Test 8 for greater than:             ";
  bool is_greater = (num1>num2);
  if(is_greater == 0) cout << "False\n";
  else             cout << "True\n";
  
  cout << "Test 9 for less than or equal:       ";
  bool is_less_equal = (num1<=num2);
  if(is_less_equal == 0) cout << "False\n";
  else             cout << "True\n";
  
  cout << "Test 10 for greater than or equal:   ";
  bool is_greater_equal = (num1>=num2);
  if(is_greater_equal == 0) cout << "False\n";
  else             cout << "True\n";
  
  return 0;
  
}
//define the function of the class
//----------------------------------------------------------
// default constructor

Rational::Rational()
{
  num = 0;
  den = 1;
  reduce();
}
//----------------------------------------------------------
//an overloaded constructor that accepts two values for an initial fraction
Rational::Rational(int x, int y)
{
  //Note we allow negative numbers for this assignment 
  num = x;
  den = y;
  reduce();
}
//----------------------------------------------------------
//destructor
Rational::~Rational()
{
  
}
//-----------------------------------------------------------------------
ostream &operator << (ostream & out, Rational & c)
{
  out << c.num << "/" << c.den;
}
//------------------------------------------------------------------------
istream &operator >> (istream & in, Rational & x)
{
  char slash;
  int a,b;
  in >> a;   //num
  in >> slash;
  in >> b;   //den
  x.num = a;
  x.den = b;
  x.reduce();
}
//------------------------------------------------------------------------
Rational operator + (Rational & in1, Rational &in2)
{
  Rational out;
  
  int a = in1.num;
  int b = in1.den;
  int c = in2.num;
  int d = in2.den;
  
  out.num = (a*d)+(b*c);
  out.den = b*d;
  
  out.reduce();
  return out;
}
//------------------------------------------------------------------------
Rational operator * (Rational & in1, Rational &in2)
{
  Rational out;
  
  int a = in1.num;
  int b = in1.den;
  int c = in2.num;
  int d = in2.den;
  
  out.num = a*c;
  out.den = b*d;
  
  out.reduce();  
  return out;
}

//-----------------------------------------------------------
Rational operator / (Rational & in1, Rational &in2)
{
  Rational out;
  
  int a = in1.num;
  int b = in1.den;
  int c = in2.num;
  int d = in2.den;
  
  out.num = a*d;
  out.den = c*b;
  
  out.reduce();
  return out;
}
//-----------------------------------------------------------
bool operator == (Rational & in1, Rational &in2)
{
  bool is_equal = 0;
  
  int a = in1.num;
  int b = in1.den;
  int c = in2.num;
  int d = in2.den;
  
  if( (b*c) == (a*d))
    is_equal = 1;
  
  return is_equal;
}
//-----------------------------------------------------------
bool operator < (Rational & in1, Rational &in2)
{
  int a = in1.num;
  int b = in1.den;
  int c = in2.num;
  int d = in2.den;
  bool is_less = 0; //not less than
  
  if( (a*d) < (c*b))
    is_less = 1; //true
  
  return is_less;
}
//-----------------------------------------------------------
bool operator <= (Rational & in1, Rational &in2)
{
  int a = in1.num;
  int b = in1.den;
  int c = in2.num;
  int d = in2.den;
  bool is_less_equal = 0; //not less than
  
  if( (a*d) < (c*b))
    is_less_equal = 1; //true
  else if((a*d) == (c*d))
    is_less_equal = 1; //true
  else;
  
  return is_less_equal;
}
//-----------------------------------------------------------
Rational operator - (Rational & in1, Rational &in2)
{
  Rational out;
  
  int a = in1.num;
  int b = in1.den;
  int c = in2.num;
  int d = in2.den;
  
  out.num = (a*d)-(b*c);
  out.den = b*d;
  
  out.reduce();
  return out;
}
//-----------------------------------------------------------
bool operator > (Rational & in1, Rational &in2)
{
  int a = in1.num;
  int b = in1.den;
  int c = in2.num;
  int d = in2.den;
  
  bool is_greater = 0; //not greater than
  
  if( (a*d) > (c*b))
    is_greater = 1; //true
  
  return is_greater;
}
//-----------------------------------------------------------
bool operator >= (Rational & in1, Rational &in2)
{
  int a = in1.num;
  int b = in1.den;
  int c = in2.num;
  int d = in2.den;
  bool is_greater_equal = 0; //not greater than
  
  if( (a*d) > (c*b))
    is_greater_equal = 1; //true
  else if((a*d) == (c*d))
    is_greater_equal = 1; //true
  else;
  
  return is_greater_equal;
}
//------------------------------------------------------------
void Rational::reduce()
{
  int count;
  
  //find the gcd between the num and den and divide by it
  if(num<den)
    count = num;
  else
    count = den;
  
  for(int i = count; i>0; i--)
    {
      if(((num%i) == 0)&&((den%i) == 0))
	{
	  num = num/i;
	  den = den/i;
	  break;
	}
    }
  //make the number positive if both the num and den are negitive
  if((num < 0)&&(den<0))
    {
      num= -num;
      den= -den;
    }
  else if(den <0)
    {
      num = -num;
      den = -den;
    }
  else if(den == 0)
    {
      cout << "Warning denemator is equal to 0\n";
    }
  else;
}

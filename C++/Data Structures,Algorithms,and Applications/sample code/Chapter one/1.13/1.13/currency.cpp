#include<iostream>
#include"currency.h"

currency::currency()
{
	setValue(0);
}

currency::currency(unsigned long theAmount=0)
{
	setValue(theAmount);
}

void currency::subtract(currency& x)
{
	amount -= x.amount;
}

void currency::setValue(unsigned long theAmount)
{
	amount = theAmount;
}

void currency::input()
{
	long theAmount;
	std::cout << "Please input the amount: " << std::endl;
	std::cin >> theAmount;
	amount = theAmount;
}


void currency::output() const
{
	long theAmount = amount;
	if (theAmount < 0)
	{
		std::cout << '-';
		theAmount = -theAmount;
	}
	long dollars = theAmount / 100;
	std::cout << '$' << dollars << '.';
	int cents = theAmount - dollars * 100;
	if (cents < 10) std::cout << '0';
	std::cout << cents<<std::endl;
}

currency& currency::percent(double x)
{
	//amount *= x*0.01;//方法1
	setValue(amount *= x * 0.01);//方法2
	return *this;
}

currency& currency::multiply(double x)
{
	setValue(amount *= x);
	return *this;
}

currency& currency::divide(double x) 
{
	setValue(amount /= x);
	return *this;
}

#include<iostream>
#include"currency.h"

currency currency::operator+(const currency& x) const
{
	currency result;
	result.amount = amount + x.amount;
	return result;
}

void currency::output(std::ostream& out) const
{
	long theAmount = amount;
	if (theAmount < 0)
	{
		out << '-';
		theAmount = -theAmount;

	}
	long dollars = theAmount / 100;
	out << '$' << dollars << '.';
	int cents = theAmount - dollars * 100;
	if (cents < 10)
	{
		out << '0';
	}
	out << cents;
}

std::ostream& operator<<(std::ostream& out, const currency& x)
{
	long theAmount = x.amount;
	if (theAmount < 0)
	{
		out << '-';
		theAmount = -theAmount;
	}
	long dollars = theAmount / 100;
	out << '$' << dollars << '.';
	int cents = theAmount - dollars * 100;
	if (cents < 10)
	{
		out << '0';
	}
	out << cents;
	return out;
}

currency::currency(long theAmount)
{
	amount=theAmount;
}

currency::currency()
{
	amount = 0;
}

std::istream& operator>>(std::istream& in, currency& x)
{
	in >> x.amount;
	return in;
}

currency currency::operator-(const currency& x) const
{
	currency result;
	result.amount = amount - x.amount;
	return result;
}

currency currency::operator%(double x) const
{
	currency result;
	result.amount = amount * x * 0.01;
	return result;
}

currency currency::operator*(double x) const
{
	currency result;
	result.amount = amount * x;
	return result;
}

currency currency::operator/(double x) const
{
	currency result;
	result.amount = amount / x;
	return result;
}

void currency::operator=(int x)
{
	amount = x;
}

void currency::operator=(double x)
{
	if (x < 0)
	{
		amount = (long)((x - 0.001) * 100);
	}
	else
	{
		amount = (long)((x + 0.001) * 100);
	}
}

#include<iostream>
enum signType
{
	plus,
	minus
};

class currency
{
	friend std::ostream& operator<<(std::ostream&, const currency&);
	friend std::istream& operator>>(std::istream&, currency&);
public:
	currency(long);
	currency();
	~currency(){}
	void operator=(int);
	void operator=(double);
	signType getSign() const
	{
		if (amount < 0)
		{
			return minus;
		}
		else
		{
			return plus;
		}
	}
	unsigned long getDollars() const
	{
		if (amount < 0)
		{
			return (-amount) / 100;
		}
		else
		{
			return amount / 100;
		}
	}
	unsigned int getCents() const
	{
		if (amount < 0)
		{
			return -amount - getDollars() * 100;
		}
		else
		{
			return amount - getDollars() * 100;
		}
	}
	currency operator+(const currency&) const;
	currency operator-(const currency&) const;
	currency operator%(double) const;
	currency operator*(double) const;
	currency operator/(double) const;
	currency& operator+=(const currency& x)
	{
		amount += x.amount;
		return *this;
	}
	void output(std::ostream&) const;
private:
	long amount;
};

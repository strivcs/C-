class currency
{
public:
	currency();
	currency(unsigned long);
	~currency(){}
	void subtract(currency&);
	void setValue(unsigned long);
	void output() const;
	void input();
	currency& percent(double);
	currency& multiply(double);
	currency& divide(double);
private:
	long amount;
};


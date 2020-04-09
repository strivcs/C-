#include<iostream>
#include<string>
#include<cstring>

int main()
{
	using namespace std;
	char charr1[20];
	char charr2[20] = "jaguar";
	string str1;
	string str2 = "panther";

	str1 = str2;
	strcpy_s(charr1, charr2);

	str1 += "paste";
	strcat_s(charr1, "juice");
	
	int len1 = str1.size();
	int len2 = strlen(charr1);
	
	cout << "The string " << str1 << " coutains" << len1 << " characters.\n"
		<< "The string " << charr1 << " contains" << len2 << " characters.\n";
	cin.get();
	return 0;

}
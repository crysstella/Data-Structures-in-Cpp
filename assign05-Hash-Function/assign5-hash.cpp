/*
 * Name: Vo Nguyen
 * ID: 01739843
 * Assignment 5: Five different hash function
                 Each function's histogram
 * Date: 30 June 2020
*/

#include <iostream>
#include <cstdint>
#include <vector>
#include <type_traits>
#include <boost/math/distributions/chi_squared.hpp>
#include <fstream>
#include <functional>

using namespace std;
using boost::math::chi_squared;
using boost::math::cdf;

const int size = 65536;
const int prime = 65413;
const int base = 256;
const double A = (sqrt(5)-1) / 2;
const int number_of_words = 99171;
const double degree_of_number = 65535.0;

uint16_t string_length_hash(string words)
{
	uint16_t length = words.length();
	
	return length; 
}

unsigned char char_to_unsigned(char c)
{
	return static_cast<make_unsigned<char>::type>(c);
}

uint16_t first_charac_hash(string words)
{
	unsigned char first = char_to_unsigned(words[0]);
	uint16_t result = first;
	
	return result;
	
}

uint16_t checksum_hash(string words)
{
	long sum = 0;

	for (size_t i = 0; i < words.length(); ++i)
		sum += char_to_unsigned(words[i]);

	return sum;
}

uint16_t remainder_hash(string words)
{	
	long result = 0;
	
	for (size_t i = 0; i < words.length(); ++i)
		result = (result * base + words[i]) % prime;

	return result;
}

uint16_t multiplicative_hash(string words)
{
	
	double result = 0;
	
	for (size_t i = 0; i < words.length(); ++i)
		result = fmod((result * base + words[i]) * A, 1);

	return result*size;
	
}
void print_histogram(vector<int> hashes)
{
	vector<double> temp;
	int count = 0;
	int sum = 0;
	double largest = 0;
	
	for (int i = 0; i < hashes.size(); ++i)
	{	
		if (count == 1024){
			temp.push_back(sum);
		
			if (sum > largest)
				largest = sum;

			count = 0;
			sum = 0;
		}
		
		sum += hashes[i];
		count ++;
	}

	temp.push_back(sum);
	if (sum > largest)
		largest = sum;

	int x = 1;
	while (largest > 15)
	{
		largest = largest / 2.0;
		x *= 2;
	}
	
	if (largest > 10)
	{
		largest = largest / 1.5;
		x *= 1.5;
	}
	
	for (int  i = 0; i < temp.size(); ++i)
		temp[i] = temp[i]/x;

	int large = round(largest);
	double scale = 0;
	
	if (large < largest)
		large = large + 0.5;
		
	if (sum == 0)
		scale = 0.5;
	else
		scale = 0.25;
	for (double i = large; i > 0; i = i - scale)
	{
		cout.width(5);
		cout << right << i  << " | ";
		for (int j = 0; j < temp.size(); ++j)
		{
			if (temp[j] >= i)
				cout << "*";
			else
				cout << " ";
		}
		cout << "\n";
	}
	
	cout.width(5);
	cout << right << "  0   + ";
	for (int i = 0; i < temp.size(); ++i)
		cout << "-";
		
	cout << endl;
	/*cout << "        ";
	for (int i = 1; i <= temp.size(); ++i)
		cout << i << " ";

	cout << endl;*/

	
}

void test_hash_fn(vector<string> words, function<uint16_t(string)> hash, vector<int> hashes)
{
	uint16_t h = 0;
	for (string word : words){
		h = hash(word);
		hashes[h]++;
	}
		
	//Pearson's X^2 Test
	double expected = number_of_words /double (size);
	double c2 = 0;
	
	for (uint16_t h : hashes )
		c2 += expected - 2*h + double (h*h)/expected;       //c2 = (expected - h)^2/expected

	chi_squared c2d(degree_of_number);
	float p = cdf(c2d, c2);

	cout << "p = " << p << endl;

	print_histogram(hashes);
}


int main()
{
	vector<int> hashes(size);
	vector<string> words;
	
	ifstream myfile;
	myfile.open ("words");

	if (!myfile)
	{
		cout << "Unable to open file" << endl;
		myfile.close();
		exit(1);
	}
	else
	{
		while (!myfile.eof())
		{
			string name;
			getline(myfile, name);
			if (name != "")
			{
				words.push_back(name);
			}
		}
	}
	
	myfile.close();

   	cout << "String length hash method: ";
	test_hash_fn(words, string_length_hash, hashes);
	
	cout << "First character hash method: ";
	test_hash_fn(words, first_charac_hash, hashes);
	
	cout << "Checksum hash method: ";
	test_hash_fn(words, checksum_hash, hashes);
	
	cout << "Remainder hash method: ";
	test_hash_fn(words, remainder_hash, hashes);
	
	
	cout << "Multiplicative hash method: ";
	test_hash_fn(words, multiplicative_hash, hashes);
	
	return 0;
		
}
/*cout << "String length hash method: ";
test_hash_fn(words, string_length_hash, hashes, histogram_string_length);

cout << "First character hash method: ";
test_hash_fn(words, first_charac_hash, hashes, histogram_first);

cout << "Checksum hash method: ";
test_hash_fn(words, checksum_hash, hashes, histogram_checksum);

cout << "Remainder hash method: ";
test_hash_fn(words, remainder_hash, hashes, histogram_remainder);


cout << "Multiplicative hash method: ";
test_hash_fn(words, multiplicative_hash, hashes, histogram_multi);*/
/*int max(vector<int> hashes)
{
	int max = hashes[0];
	
	for (uint16_t h : hashes)
	{
		if (h > max)
			max = h;	
	}
	return max;
}

int min(vector<int> hashes)
{
	int min = hashes[0];
	
	for (uint16_t h : hashes)
	{
		if (h < min)
			min = h;	
	}
	return min;
}
*/
/*void print(int largest, vector<int> temp)
{
	cout << endl;
	for (int i = largest; i > 0; --i)
	{
		cout.width(2);
		cout << i << " | ";
		for (int j = 0; j < temp.size(); ++j)
		{
			if (temp[j] >= i)
				cout << "*";
			else
				cout << " ";
		}
		cout << "\n";
	}
	
	cout.width(2);
	cout << right << " 0  ";
	for (int i = 0; i < 88; ++i)
		cout << "-";

	cout << endl;
}
void histogram_checksum(vector<int> hashes)
{
	int largest = 0;
	vector<int> temp;
	for (int j = 60; j < 1810; j += 20)
	{
		int sum = 0;
		for (int i = j; i < j+20; ++i)
		{
			sum += hashes[i];
		}
		sum = round(sum/(20*10));
		temp.push_back(sum);
		if (sum > largest)
			largest = sum;
	}

	print(largest, temp);

}

void histogram_string_length(vector<int> hashes)
{
	int largest = 0;
	vector<int> temp;
	for (int j = 0; j < 30; j++)
	{
		int sum = 0;
		sum += hashes[j];
		sum = round(sum/800.0);
		temp.push_back(sum);
		if (sum > largest)
			largest = sum;
	}
	
	print(largest, temp);

}

void histogram_first(vector<int> hashes)
{
	int largest = 0;
	vector<int> temp;
	
	for (int j = 60; j < 135; j += 2)
	{
		int sum = 0;
		sum = hashes[j] +  hashes[j+1];
	
		sum = round(sum/(2*300.0));
		temp.push_back(sum);
		if (sum > largest)
			largest = sum;
	}
	
	print(largest, temp);
	
}

void histogram_remainder(vector<int> hashes)
{

	int largest = 0;
	vector<int> temp;
	
	for (int j = 32224; j < 32485; j += 3)
	{
		int sum = 0;
		sum += hashes[j];
		temp.push_back(sum);
		
		if (sum > largest)
			largest = sum;
	}
	//cout << largest << endl;
	//cout << temp.size();
	print(largest, temp);
}

void histogram_multi(vector<int> hashes)
{
	int largest = 0;
	vector<int> temp;
	
	for (int j = 221; j < 308; j ++)
	{
		int sum = 0;
		sum += hashes[j];
		temp.push_back(sum);
		
		if (sum > largest)
			largest = sum;
	}

	print(largest, temp);
	
}
int gcf(int a, int b)
{
	if (a == b)
		return a;
	else if (a == 0 and b == 0)
		return 1;
	else if (a == 0 and b != 0)
		return b;
	else if (a != 0 and b == 0)
		return a;
	else
		if (a > b)
			return gcf(a-b, b);
		else
			return gcf(a, b-a);
}

int gcf_vect(vector<int> temp, int n)
{
	if (n == 1)
		return temp[0];
	else
	{
		return gcf(temp[n-1], gcf_vect(temp,n-1));
	}	
}

int factor_max(int a)
{
	for (int i = a/2; i >= 0; --i)
		if (a % i == 0)
			return i;	
}*/

/*void bad(vector<int> hashes)
{
	vector<int> temp;
	int count = 0;
	int sum = 0;
	int largest = 0;
	
	for (int h : hashes)
	{	
		if (count == 1024){
			temp.push_back(sum);
			if (sum > largest)
				largest = sum;
			count = 0;
			sum = 0;
		}
		else
		{
			sum += h;
			count++;	
		}

	}
	int x = 10;
	while (largest > 100)
	{
		largest = largest/(x);
		x *= 10 ;
	}
	for (int  i = 0; i < temp.size(); ++i)
		temp[i] = temp[i]/x;
	

	if (largest > 60)
		largest = round(largest/2.00);

	if (largest >= 20)	
	{
		if  (largest % 2 != 0)
		{
			cout.width(2);
			cout << right << largest + 1 << " | " << endl;
			largest = largest - 1;
		}
	}

	for (int i = largest; i > 0;)
	{
		cout.width(2);
		cout << i << " | ";
		for (int j = 0; j < temp.size(); ++j)
		{
			if (temp[j] >= i)
				cout << "*";
			else
				cout << " ";
		}
		cout << "\n";
		if (largest < 20)	
			--i;
		else
			i = i - 2;
		
	
	}
		cout.width(2);
		cout << right << " 0 +";
		for (int i = 0; i < temp.size(); ++i)
			cout << "-";
	
		cout << endl;

	
}*/

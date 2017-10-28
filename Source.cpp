#include <iostream>
#include <string>
#include <vector>
#include<sstream>
#include <time.h>
#include <chrono>
#define MAX 1000

using namespace std;



void Zeroing64IntArray(int *p)
{
	for (int i = 0; i < 64; i++)
	{
		p[i] = 0;
	}
}


void Zeroing128IntArray(int *p)					// not used yet
{
	for (int i = 0; i < 128; i++)
	{
		p[i] = 0;
	}
}		


void Zeroing64UintArray(uint32_t *p)
{
	for (int i = 0; i < 64; i++)
	{
		p[i] = 0;
	}
}


void ChangeStrToInt(string s, int *p , int i)
{
	string s1;
	while (i >= 0)
	{
		if (s.size() > 9)
		{
			s1 = s.substr(s.length() - 9, s.length());
			s.erase(s.length() - 9, s.length());
			//cout << s << endl;						//............................. for checking
			p[i] = atoi(s1.c_str());
			i = i - 1;
		}
		else
		{
			p[i] = atoi(s.c_str());
			s.erase();
			i = i - 1;
			break;
		}
	}

}

void ChangeIntToStr(string *s, int *p)
{
	*s = "";
	for (int i = 0; i < 64; i++)
	{
		*s += string(9 - to_string(p[i]).length(), '0').append(to_string(p[i]));
	}
}

void Addition(int *FirstNumber, int *SecondNumber, int *value)
{
	int SecondaryFirstNumber[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		SecondaryFirstNumber[i] = FirstNumber[i];
	}

	int SecondarySecondNumber[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		SecondarySecondNumber[i] = SecondNumber[i];
	}

	Zeroing64IntArray(value);
	int i = 63;
	int carry = 0;
	int NegCarry = 0;
	string c;
	int solution = 0;
	while (i >= 0)
	{
		SecondaryFirstNumber[i] = SecondaryFirstNumber[i]; 
		solution = SecondaryFirstNumber[i] + SecondarySecondNumber[i] + carry ;
		carry = 0;
		NegCarry = 0;
		if (solution > 999999999 + 1)
		{
			c = to_string(solution);
			c = '0' + c.substr(1, c.length());
			carry = 1;
			NegCarry = 0;
			solution = atoi(c.c_str());
			value[i] = solution;
			i = i - 1;
		}
		else if (solution < 0)
		{
			solution += 1000000000;
			NegCarry = 1;
			value[i] = solution;
			i = i - 1;
		}
		else
		{
			value[i] = solution;
			carry = 0;
			i = i - 1;
		}
	}

}

//Not Used
void Addition(double *FirstNumber, double *SecondNumber, double *value)
{
	double SecondaryFirstNumber[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		SecondaryFirstNumber[i] = FirstNumber[i];
	}

	double SecondarySecondNumber[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		SecondarySecondNumber[i] = SecondNumber[i];
	}

//	Zeroing64IntArray(value);
	int i = 63;
	double carry = 0;
	double NegCarry = 0;
	string c;
	double solution = 0;
	while (i >= 0)
	{
		SecondaryFirstNumber[i] = SecondaryFirstNumber[i];
		solution = SecondaryFirstNumber[i] + SecondarySecondNumber[i] + carry;
		carry = 0;
		NegCarry = 0;
		if (solution > 1000000000)
		{
			c = to_string(solution);
			c = '0' + c.substr(1, c.length());
			carry = 1;
			NegCarry = 0;
			solution = atoi(c.c_str());
			value[i] = solution;
			i = i - 1;
		}
		else if (solution < 0)
		{
			solution += 1000000000000;
			NegCarry = 1;
			value[i] = solution;
			i = i - 1;
		}
		else
		{
			value[i] = solution;
			carry = 0;
			i = i - 1;
		}
	}

}


void TwosCompliment(int *Number , int *Twoscomp)// ,int *n)
{
	int x[64] = { 0 };
	x[63] += 1;
	for (int j = 0; j < 64; j++)
	{
		Number[j] = ~Number[j];
	}
	int i = 0;
	Addition(Number, x, Twoscomp);

}


void Subtraction(int *FirstNumber, int *SecondNumber, int *value)
{
	int SecondaryFirstNumber[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		SecondaryFirstNumber[i] = FirstNumber[i];
	}

	int SecondarySecondNumber[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		SecondarySecondNumber[i] = SecondNumber[i];
	}
	int Twoscompl[64] = { 0 };
	int NumberOfExtraBits = 0;
	TwosCompliment(SecondarySecondNumber, Twoscompl);
	Addition(SecondaryFirstNumber, Twoscompl, value);

	for (int j = 0 ; j < 64; j++)
	{
		if (value[j] == 1000000000)
			break;
		else
			NumberOfExtraBits += 1;

	}
	for (int j = 0; j < NumberOfExtraBits+1; j++)
	{
		value[j] = 0;
	}

	//cout << endl << "Subtraction value = ";

	//for (int j = 0  ; j < 64; j++)
	//{
	//	printf("%09d", value[j]);
	//}
	//cout << endl;
}

/*
int* product1(string a, string b)
{

	vector<int> result(a.size() + b.size(), 0);
	for (int i = a.size() - 1; i >= 0; i--)
	{
		for (int j = b.size() - 1; j >= 0; j--)
		{
			result[i + j + 1] += (b[j] - '0') * (a[i] - '0'); //single array to store intermediate values
		}
	}
	for (int j = a.size() + b.size()-1; j >= 0; j--) {
		if (result[j] >= 10) {
			result[j - 1] += result[j] / 10;
			result[j] %= 10;
		}
	}
//	cout << a << " * " << b << " = ";    ........for printing the numbers themselves
	//for (int i = 0; i < a.size() + b.size(); i++) {
	//	cout << result[i];
	//}
	//cout << endl;
	while (result[1] == 0)
	{
	//	result.erase(0, 1);
		//vector<int> result = copy(result.begin() + 1, result.end());
		result.erase(result.begin() + 1);
	}
	int* q = &result[1]; // change vector to array of integers
	cout << endl;
	for (int i = 0; i < 160; i++)
	{
		cout << q[i];
	}
	return q;
}
*/

// working product returning pointer to int array
int product(string a, string b, int *result_array)
{
	string answer;
	result_array[64] = { 0 };
	vector<int> result(a.size() + b.size(), 0);
	for (int i = a.size() - 1; i >= 0; i--)
	{
		for (int j = b.size() - 1; j >= 0; j--)
		{
			result[i + j + 1] += (b[j] - '0') * (a[i] - '0'); //single array to store intermediate values
		}
	}
	for (int j = a.size() + b.size() - 1; j >= 0; j--) {
		if (result[j] >= 10) {
			result[j - 1] += result[j] / 10;
			result[j] %= 10;
		}
	}

	for (int i = 0; i <= result.size()-1; i++)
	{
		int* x = &result.begin()[i];
		answer += to_string(*x);

	}
//	cout << endl << answer << endl;
	ChangeStrToInt(answer, result_array, 63);
	return *result_array;
}


//working Right shifting
void ShiftRight(int *SecondNumber)
{
	int i = 0;
	int carryNew = 0;
	int carryOld = 0;
	while (i < 64)
	{
		carryNew = SecondNumber[i] & 0x00000001;
		if (carryOld == 0)
		{

			SecondNumber[i] = (SecondNumber[i] >> 1) ;
			carryOld = carryNew;
			i = i + 1;

		}
		else
		{
			SecondNumber[i] = SecondNumber[i] >> 1;
			SecondNumber[i] += 500000000;
			carryOld = carryNew;
			i = i + 1;
		}
	}

	//for (int j = 0; j < 64; j++)
	//{
	//	printf("%09d", SecondNumber[j]);
	//}

}
/*
int NumbersToShift(int NumberOfBitsToShift)
{

	if (NumberOfBitsToShift == 0)
		return 0x00000000000000000000000000000000;

	else if (NumberOfBitsToShift == 1)
		return  0x20000000;

	else if (NumberOfBitsToShift == 2)
		return  0x30000000;

	else if (NumberOfBitsToShift == 3)
		return  0x38000000;

	else if (NumberOfBitsToShift == 4)
		return  0x3C000000;

	else if (NumberOfBitsToShift == 5)
		return  0x3E000000;

	else if (NumberOfBitsToShift == 6)
		return  0x3F000000;

	else if (NumberOfBitsToShift == 7)
		return  0x3F800000;

	else if (NumberOfBitsToShift == 8)
		return  0x3FC00000;

	else if (NumberOfBitsToShift == 9)
		return  0x3FE00000;

	else if (NumberOfBitsToShift == 10)
		return  0x3FF00000;

	else if (NumberOfBitsToShift == 11)
		return  0x3FF80000;

	else if (NumberOfBitsToShift == 12)
		return  0x3FFC0000;

	else if (NumberOfBitsToShift == 13)
		return  0x3FFE0000;

	else if (NumberOfBitsToShift == 14)
		return  0x3FFF0000;

	else if (NumberOfBitsToShift == 15)
		return  0x3FFF8000;

	else if (NumberOfBitsToShift == 16)
		return  0x3FFFC000;

	else if (NumberOfBitsToShift == 17)
		return  0x3FFFE000;

	else if (NumberOfBitsToShift == 18)
		return  0x3FFFF000;

	else if (NumberOfBitsToShift == 19)
		return  0x3FFFF800;

	else if (NumberOfBitsToShift == 20)
		return  0x3FFFFC00;

	else if (NumberOfBitsToShift == 21)
		return  0x3FFFFE00;

	else if (NumberOfBitsToShift == 22)
		return  0x3FFFFF00;

	else if (NumberOfBitsToShift == 23)
		return  0x3FFFFF80;

	else if (NumberOfBitsToShift == 24)
		return  0x3FFFFFC0;

	else if (NumberOfBitsToShift == 25)
		return  0x3FFFFFE0;

	else if (NumberOfBitsToShift == 26)
		return  0x3FFFFFF0;

	else if (NumberOfBitsToShift == 27)
		return  0x3FFFFFF8;

	else if (NumberOfBitsToShift == 28)
		return  0x3FFFFFFC;

	else if (NumberOfBitsToShift == 29)
		return  0x3FFFFFFE;

	else if (NumberOfBitsToShift == 30)
		return 0x3FFFFFFF;

}
*/

bool GreaterThan(int *FirstNumber, int* SecondNumber )
{
	int NumberOfEqualBytes = 0;
	for (int i = 0; i < 64; i++)
	{
		if (FirstNumber[i] == SecondNumber[i])
		{
			NumberOfEqualBytes += 1;
		}
		else if (FirstNumber[i] > SecondNumber[i])
		{
			return true;
		}

		else
			return false;
		


	}

}


bool SmallerThan(int *FirstNumber, int* SecondNumber)
{
	int NumberOfEqualBytes = 0;
	for (int i = 0; i < 64; i++)
	{
		if (FirstNumber[i] == SecondNumber[i])
		{
			NumberOfEqualBytes += 1;
		}
		else if (FirstNumber[i] < SecondNumber[i])
		{
			return true;
		}

		else
			return false;



	}

}


bool EqualTo(int *FirstNumber, int* SecondNumber)
{
	int NumberOfEqualBytes = 0;
	for (int i = 0; i < 64; i++)
	{
		if (FirstNumber[i] == SecondNumber[i])
		{
			NumberOfEqualBytes += 1;
		}
	}
	if (NumberOfEqualBytes == 64)
		return true;
	else
		return false;

}


// subtraction with negative indication & sign .. Negative is true when sec > first
void Subtraction_1(int *FirstNumber, int *SecondNumber, int *value, bool &Negative)
{
	int SecondaryFirstNumber[64] = { 0 };
	int SecondarySecondNumber[64] = { 0 }, zero[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		SecondaryFirstNumber[i] = FirstNumber[i];
		SecondarySecondNumber[i] = SecondNumber[i];
	}
	//if (c == 64) 
	//{
	//	for (int i = 0; i < 64;i++)
	//		value[i] = SecondaryFirstNumber[i];
	//}
	if (GreaterThan(SecondaryFirstNumber, SecondarySecondNumber))
		{
			Negative = false;
			if (EqualTo(SecondarySecondNumber, zero))
			{
				for (int i = 0; i < 64;i++)
					value[i] = SecondaryFirstNumber[i];
			}
			else
			{

				
				int Twoscompl[64] = { 0 };
				int NumberOfExtraBits = 0;
				TwosCompliment(SecondarySecondNumber, Twoscompl);
				Addition(SecondaryFirstNumber, Twoscompl, value);

				for (int j = 0; j < 64; j++)
				{
					if (value[j] == 1000000000)
						break;
					else
						NumberOfExtraBits += 1;

				}
				for (int j = 0; j < NumberOfExtraBits + 1; j++)
				{
					value[j] = 0;
				}
			}
				//cout << endl << "Subtraction value = ";

				//for (int j = 0; j < 64; j++)
				//{
				//	printf("%09d", value[j]);
				//}
				//cout << endl;
			
		}
		else
		{
			Negative = true;
			if (EqualTo(SecondaryFirstNumber, zero))
			{
				for (int i = 0; i < 64; i++)
					value[i] = SecondarySecondNumber[i];
			}
			else
			{
				
				int Twoscompl[64] = { 0 };
				int NumberOfExtraBits = 0;
				TwosCompliment(SecondaryFirstNumber, Twoscompl);
				Addition(SecondarySecondNumber, Twoscompl, value);

				for (int j = 0; j < 64; j++)
				{
					if (value[j] == 1000000000)
						break;
					else
						NumberOfExtraBits += 1;

				}
				for (int j = 0; j < NumberOfExtraBits + 1; j++)
				{
					value[j] = 0;
				}
			}
				//cout << endl << "Subtraction value = -";

				//for (int j = 0; j < 64; j++)
				//{
				//	printf("%09d", value[j]);
				//}
				//cout << endl;

			
		}
		//cout << endl << "Subtraction value = ";

		//for (int j = 0  ; j < 64; j++)
		//{
		//	printf("%09d", value[j]);
		//}
		//cout << endl;
}

/*
// working shift left but sending the second number as string 
void ShiftLeftt(string SecondNumber, int NumberOfBitsToShift)
{

	int x = pow(2, NumberOfBitsToShift);
		product(SecondNumber, to_string(x));

	
}
*/

/*
// Working shift left 
int ShiftLeft(int *SecondNumber, int NumberOfBitsToShift, int *solution)
{
	string answer;
	string FullNumberToMultiply , Number , s;
	solution[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		if (s == "000000000")
		{						
		
			Number = string(9 - to_string(SecondNumber[i]).length(), '0').append(to_string(SecondNumber[i]));
			FullNumberToMultiply = FullNumberToMultiply + Number;
			s = FullNumberToMultiply.substr(0, 9);
		}

		else
		{
			Number = string(10 - Number.length(), '0').append(to_string(SecondNumber[i]));
			FullNumberToMultiply = FullNumberToMultiply + Number;
			s = FullNumberToMultiply.substr(0, 9);
		}
	}
	int x = pow(2, NumberOfBitsToShift);
	 product(FullNumberToMultiply, to_string(x),solution);
	return *solution;
}
*/


void ShiftLeft_30(int *SecondNumber , int NumberOfShifts)
{
	int n = 0;
	while (n < NumberOfShifts )
	{
	int i = 63 ;
	int carryNew = 0;
	int carryOld = 0;

		while (i > -1)
		{
			
			carryNew = SecondNumber[i] & 0x20000000;
			if (carryOld == 0)
			{

				SecondNumber[i] = (SecondNumber[i] << 1);
				carryOld = carryNew;
			
			}
			else
			{
				SecondNumber[i] = SecondNumber[i] << 1;
				SecondNumber[i] = SecondNumber[i] | 0x00000001;
				carryOld = carryNew;
			}

			if (SecondNumber[i] > 1000000000)
			{
				SecondNumber[i] -= 1000000000;
				carryOld = 1;

			}
			i = i - 1;
		}
		n++;
	}
	// ........... to print the number
	//for (int j = 0; j < 64; j++)
	//{
	//	printf("%09d", SecondNumber[j]);
	//}

}


/*
// not working well
void ModulusSubtract_1(int *FirstNumber, int *SecondNumber, int *result, int NumberOfBitsToShift)
{
	int SubtractionSolution[64] = { 0 };
	int SecondarySecondNumber[64] = { 0 };
	int shiftedSecondNumber[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		SecondarySecondNumber[i] = SecondNumber[i];
	}
	int NumberOfDivides = 0;
	int LastValidResult[64] = { 0 };
	int solution[64] = { 0 };
	int max_number = 999999990;
	int validity = 0;
	int count = 0;

		for (int i = 0; i < 64; i++)
		{
			LastValidResult[i] = FirstNumber[i];
		}

		ShiftLeft(SecondarySecondNumber, NumberOfBitsToShift, shiftedSecondNumber);
		for (int i = 0; i < 64; i++)
		{
			SecondarySecondNumber[i] = shiftedSecondNumber[i];
		}

		while (count < 10)
		{
			validity = 0;
		//	result = { 0 };
			SubtractionSolution[0] = { 0 };
		for (int i = 0; i < 64; i++)
		{
			solution[i] = LastValidResult[i];
		}

//		Subtraction(LastValidResult, SecondarySecondNumber, result);
		Subtraction(LastValidResult, SecondarySecondNumber, SubtractionSolution);
		NumberOfDivides = NumberOfDivides + pow(2, NumberOfBitsToShift);

		for (int i = 0; i < 64; i++)
		{
//			LastValidResult[i] = result[i];
			LastValidResult[i] = SubtractionSolution[i];
			if (LastValidResult[i] == 0)
				validity++;
		}

		if (validity == 64)
			break;
		
		count++;
		}

	for (int i = 0; i < 64; i++)
	{
		LastValidResult[i] = solution[i];
	}
	/*
	while (NumberOfBitsToShift >= 0)
	{
		while (count < 64) // not working well ... enters the loop even if it's greater than max_number (neg)
		{
			count = 0;
			for (int i = 0; i < 64; i++)
			{
				solution[i] = LastValidResult[i];
			}

			Subtraction(LastValidResult, SecondarySecondNumber, result);

			NumberOfDivides = NumberOfDivides + pow(2, NumberOfBitsToShift);

			for (int i = 0; i < 64; i++)
			{
				LastValidResult[i] = result[i];
			
				if (LastValidResult[i] == 0)
				count++;
		}
	/*		validity = LastValidResult[0];
			i = 0;
			while (i<64)
			{
				int n = 0;

				while (n = 0)
				{
					if (LastValidResult[i] |= 0)
						validity = 
						n += 1;

					else
						i += 1;
				}

			}
		}

	

		for (int i = 0; i < 64; i++)
		{
			LastValidResult[i] = solution[i];
			
		}
		//validity = 0;
		ShiftRight(SecondarySecondNumber);
		NumberOfBitsToShift -= 1;
		
	//	count = 0;
	
//	result[0] = SubtractionSolution[0];
	cout << endl << "Modulus Value: ";
	for (int j = 0; j < 64; j++)
	{
		printf("%09d", LastValidResult[j]);
	}
	cout << endl;
}
*/
/*
void Division_result(int c, int validity, int NumberOfBitsToShift, int subnext , int *DivisionSolution)
{
	int NumberOfDivides[65] = { 0 }, divisionHoldValue[64] = { 0 }, SumOfDivision[64] = { 0 }, MultiplicationResult[65] = {0};
	int secondarg[64] = { 0 };
	int power = 0, remainder = 0, subtractionCount = 0; //, subnext = 0;
	string multiplication = "";
	for (int i = 64; i >= 0; i--)
	{
		if (c == NumberOfBitsToShift)
		{
			subtractionCount = 1;
			if (NumberOfBitsToShift < 30)
			{
				NumberOfDivides[i] = pow(2, NumberOfBitsToShift);
				break;
			}

			else
			{
				power = NumberOfBitsToShift / 30;
				remainder = NumberOfBitsToShift % 30;
				for (int j = 0; j <= power; j++)
				{
					NumberOfDivides[i] = pow(2, 30);
					i--;
				}
				NumberOfDivides[i] = pow(2, remainder);
				break;
			}
		}




		if (validity |= 64 && NumberOfBitsToShift > 0)
		{
			subtractionCount = 1;
			if (NumberOfBitsToShift < 30)
			{
				NumberOfDivides[i] = pow(2, NumberOfBitsToShift);
				break;
			}

			else
			{
				power = NumberOfBitsToShift / 30;
				remainder = NumberOfBitsToShift % 30;
				for (int j = 0; j <= power; j++)
				{
					NumberOfDivides[i] = pow(2, 30);
					i--;
				}
				NumberOfDivides[i] = pow(2, remainder);
				break;
			}

		}
		else if (validity == 64 && NumberOfBitsToShift == 0)
		{
			NumberOfDivides[i] = 0;
			subtractionCount = 0;
			//subnext = 0;
			break;
		}

		else
		{

		}

	}

	for (int i = 0; i < 64; i++)
	{
		multiplication += string(9 - to_string(NumberOfDivides[i]).length(), '0').append(to_string(NumberOfDivides[i]));
	}

	product(multiplication, to_string(subtractionCount), MultiplicationResult);
	secondarg[63] = subnext*pow(2, NumberOfBitsToShift);
	Addition(MultiplicationResult, secondarg, divisionHoldValue);
//	divisionHoldValue[i] = NumberOfDivides[i] * subtractionCount + subnext *pow(2, NumberOfBitsToShift);
	
	
	Addition(DivisionSolution, divisionHoldValue, SumOfDivision);
	for (int i = 0; i < 64; i++)
	{
		DivisionSolution[i] = SumOfDivision[i];
	}
}
*/
/*
// not Working well
void Divide(int *N1, int *N2, int *sol)
{
	int counter1 = 0, counter2 = 0;
	int FirstNumber[64] = { 0 }, FirstNumberSolution[64] = { 0 }, SecNumber[64] = { 0 }, SecNumberSolution[64] = { 0 };
	int constant[64] = { 0 };
	constant[63] = 2;
	int Oddconstant[64] = { 0 };
	Oddconstant[63] = 1;
	sol = { 0 };
	for (int i = 0; i < 64;i++)
	{
		if (N1[i] == 0)
			i++;
		else
		{
			counter1 = i;
			break;
		}
			
	}
	for (int i = 0; i < 64; i++)
	{
		if (N2[i] == 0)
			i++;
		else
		{
			counter2 = i;
			break;
		}

	}

	if (N1[63] % 2 == 1)
	{
		// odd number
		Addition(FirstNumber, Oddconstant, FirstNumberSolution);
		for (int i = 0; i < 64; i++)
		{
			FirstNumber[i] = FirstNumberSolution[i];
		}
		for (int i = counter1; i < 64; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				ShiftRight(N1);
				Addition(FirstNumber, constant, FirstNumberSolution);
				for (int k = 0; k < 64; k++)
				{
					FirstNumber[k] = FirstNumberSolution[k];
				}
			}
		}

	}
	else
	{

		for (int i = counter1; i < 64; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				ShiftRight(N1);
				Addition(FirstNumber, constant, FirstNumberSolution);
				for (int k = 0; k < 64; k++)
				{
					FirstNumber[k] = FirstNumberSolution[k];
				}
			}
		}
	}

	if (N2[63] % 2 == 1)
	{
		// odd number
		// odd number
		Addition(SecNumber, Oddconstant, SecNumberSolution);
		for (int i = 0; i < 64; i++)
		{
			SecNumber[i] = SecNumberSolution[i];
		}
		for (int i = counter2; i < 64; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				ShiftRight(N2);
				Addition(SecNumber, constant, SecNumberSolution);
				for (int k = 0; k < 64; k++)
				{
					SecNumber[k] = SecNumberSolution[k];
				}
			}
		}

	}
	else
	{

		for (int i = counter2; i < 64; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				ShiftRight(N2);
				Addition(SecNumber, constant, SecNumberSolution);
				for (int k = 0; k < 64; k++)
				{
					SecNumber[k] = SecNumberSolution[k];
				}
			}
		}
	}
	Subtraction(FirstNumberSolution, SecNumberSolution, sol);

}
*/
/*
// not working
void PoweringMoreThan30(int *NumberToPower, int NumberOfBitsToShift, int *solution)
{
	int power = 0, remainder = 0;
	int multiplication_result[64] = { 0 };
	string multiplication1 , multiplication2;
	power = NumberOfBitsToShift / 30;
	remainder = NumberOfBitsToShift % 30;
	int SecondaryNumberToPower[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		SecondaryNumberToPower[i] = NumberToPower[i];
		multiplication1 += string(9 - to_string(SecondaryNumberToPower[i]).length(), '0').append(to_string(SecondaryNumberToPower[i]));
	}
	
	for (int k = 0; k < power; k++)
	{
		multiplication2 = multiplication1;
		product(multiplication1, multiplication2, multiplication_result);
		for (int i = 0; i < 64; i++)
		{
			multiplication1 += string(9 - to_string(multiplication_result[i]).length(), '0').append(to_string(multiplication_result[i]));
		}
	}
	for (int i = 0; i < remainder; i++)
	{
		multiplication2 = multiplication1;
		product(multiplication1, multiplication2, solution);
	}

//	ShiftLeft(SecondaryNumberToPower, remainder-1, solution);

}
*/
/*
void Division_result(int NumberOfBitsToShift, int subnext, int subtractionCount,int *DivisionSolution)
{
	int NumberOfDivides[64] = { 0 }, Multiplication_result[65] = { 0 }, subnextarray[64] = { 0 }, additionResult[64] = { 0 };
	int power = 0, remainder = 0;
	string multiplication;
	if (NumberOfBitsToShift < 30)
		{
			NumberOfDivides[63] = pow(2, NumberOfBitsToShift);
			
		}

		else
		{
			power = NumberOfBitsToShift / 30;
			remainder = NumberOfBitsToShift % 30;
			for (int i = 63; i >= 0; i--)
			{
				for (int j = 0; j < power; j++)
				{
					ShiftLeft(DivisionSolution, 30, NumberOfDivides);
					for (int k = 0; k < 64; k++)
					{
						DivisionSolution[k] = NumberOfDivides[k];
						multiplication += string(9 - to_string(NumberOfDivides[k]).length(), '0').append(to_string(NumberOfDivides[k]));
					}
					/*NumberOfDivides[i] = pow(2, 30);
					i--;
				}

				NumberOfDivides[63] = pow(2, remainder);
				product(multiplication, to_string(NumberOfDivides[63]), Multiplication_result);
				break;
			}
		}

	//for (int i = 0; i < 64; i++)
	//{
	//	multiplication += string(9 - to_string(NumberOfDivides[i]).length(), '0').append(to_string(NumberOfDivides[i]));
	//}

	if (subnext == 0 && subtractionCount == 0)
	{

	}

	else if ( subnext == 0 && subtractionCount == 1)
	{
	//	product(multiplication, to_string(subtractionCount), Multiplication_result);
		
		Addition(DivisionSolution, NumberOfDivides, additionResult);
	//	DivisionSolution[0] = *additionResult;
		if (additionResult[62] == 0 && additionResult[63] == 0)
		{

		}
		else
		{
			for (int i = 0; i < 64; i++)
			{
				DivisionSolution[i] = additionResult[i];
			}
		}

	}
	else if ( subnext == 1 && subtractionCount == 1)
	{

	//	product(multiplication, to_string(subtractionCount), Multiplication_result);
		if (NumberOfBitsToShift < 30)
		{
			subnextarray[63] = pow(2, NumberOfBitsToShift);

		}
	
		else
		{
			power = NumberOfBitsToShift / 30;
			remainder = NumberOfBitsToShift % 30;
			for (int i = 63; i >= 0; i--)
			{
				for (int j = 0; j <= power; j++)
				{
					subnextarray[i] = pow(2, 30);

				}
				subnextarray[i] = pow(2, remainder);
				break;
			}
		}
		Addition(NumberOfDivides, subnextarray, additionResult);
//		Addition(Multiplication_result, subnextarray, additionResult);
//		DivisionSolution[0] = *additionResult;
		if (additionResult[62] == 0 && additionResult[63] == 0)
		{

		}
		else
		{
			for (int i = 0; i < 64; i++)
			{
				DivisionSolution[i] = additionResult[i];
			}
		}
	}

	else if (subnext == -1 && subtractionCount == 1)
	{
		if (NumberOfBitsToShift < 30)
		{
			subnextarray[63] = pow(2, NumberOfBitsToShift);

		}

		else
		{
			power = NumberOfBitsToShift / 30;
			remainder = NumberOfBitsToShift % 30;
			for (int i = 63; i >= 0; i--)
			{
				for (int j = 0; j <= power; j++)
				{
					subnextarray[i] = pow(2, 30);

				}
				subnextarray[i] = pow(2, remainder);
				break;
			}
		}

		Addition(DivisionSolution, subnextarray, additionResult);
		if (additionResult[62] == 0 && additionResult[63] == 0)
		{

		}
		else
		{
			for (int i = 0; i < 64; i++)
			{
				DivisionSolution[i] = additionResult[i];
			}
		}
	}
}
*/
/*
// trying to use right shifting .. not complete
void DivisionSolution(int *FirstNumber, int *SecondNumber, int *result, int NumberOfBitsToShift)
{
	int SecondarySecondNumber[64] = { 0 }, LastValidResult[64] = { 0 }, shiftSolution[65] = { 0 }, SecondaryFirstNumber[64] = { 0 };
	LastValidResult[63] = 1;
	int subtractionSolution[65] = { 0 }, FirstNumberHolder[64] = { 0 }, resultNumberHolder[65] = { 0 }, temp[64] = { 0 };
	int solution[64] = { 0 }, holdFirstNumber[64] = { 0 };
	int NumberOfShifts = 0, subtractionCounter = 0, validity = 0, subnext = 0 , oddCounter =0;
	string result_string;
	for (int i = 0; i < 64; i++)
	{
		SecondaryFirstNumber[i] = FirstNumber[i];
		SecondarySecondNumber[i] = SecondNumber[i];
	}

	while (NumberOfBitsToShift > -1)
	{
		int a = NumberOfBitsToShift;
		subtractionCounter = 0;
		int counter = 0;
		validity = 0;
		int power = NumberOfBitsToShift / 30;
		int remainder = NumberOfBitsToShift % 30;

		while (GreaterThan(SecondaryFirstNumber, SecondarySecondNumber))
		{
			for (int i = 0; i < 64; i++)
			{
				holdFirstNumber[i] = SecondaryFirstNumber[i];
			}
			if (counter == 0)
			{
				ShiftLeft(LastValidResult, a, result);
				for (int j = 0; j < 64; j++)
				{
					LastValidResult[j] = result[j];
				}

				if (SecondaryFirstNumber[63] % 2 == 1)
					oddCounter += 1;

				while (a > -1)
				{
					ShiftRight(SecondaryFirstNumber);
					a--;
				}

				counter++;
			}
			else
			{
				if (SecondaryFirstNumber[63] % 2 == 1)
					oddCounter++;
				ShiftRight(SecondaryFirstNumber);
			}

		}

		for (int i = 0; i < 64; i++)
		{
			SecondaryFirstNumber[i] = holdFirstNumber[i];
		}

		Subtraction(SecondaryFirstNumber, SecondarySecondNumber, subtractionSolution);
		for (int i = 0; i < 64; i++)
		{
			if (subtractionSolution[i] == 0)
				validity++;
		}
		if (validity == 64)
		{
			subtractionCounter = 0;
			subnext = 1;
			product(result_string, to_string(subnext), resultNumberHolder);

		}
		else
		{
			subtractionCounter += 1;
			for (int i = 0; i < 64; i++)
			{
				SecondaryFirstNumber[i] = subtractionSolution[i];
				holdFirstNumber[i] = SecondaryFirstNumber[i];
			}
		}

		product(result_string, to_string(subtractionCounter), resultNumberHolder);
		Addition(solution, resultNumberHolder, temp);
		//	ShiftRight(SecondarySecondNumber);
		//	ShiftRight(result);

		for (int i = 0; i < 64; i++)
		{
			solution[i] = temp[i];
			result_string = "";
			result_string += string(9 - to_string(result[i]).length(), '0').append(to_string(result[i]));
			//	result_string += string(9 - to_string(resultNumberHolder[i]).length(), '0').append(to_string(resultNumberHolder[i]));
		}


		NumberOfBitsToShift--;
	}
	for (int i = 0; i < 64; i++)
	{
		result[i] = solution[i];
	}

}
*/
/*
void ModulusSubt_div(int *FirstNumber, int *SecondNumber, int *result, int NumberOfBitsToShift, int *Division)
{

	int SubtractionSolution[65] = { 0 };
	int SecondarySecondNumber[64] = { 0 };
	int counter = 0, NumberOfShifts = 0, remainderOfshifts = 0;
	int NumberOfDivides[64] = { 0 }, OneArray[64] = { 0 }; // new for array
	 OneArray[63] = 1;
	int LastValidResult[64] = { 0 };
	int validity = 0;
	int subtractionCount = 0;
	int subNext[64] = { 0 }, subNextAdded[64] = { 0 }; // new for array
	int NumberOfDividesSolution_sub[64] = { 0 }; // new for array
	string NumberOfDivides_String = "", subNext_string = "", TwoArrayShifted_string = ""; // new for array
	bool NegFlag = false;
	int x = 0 , c =0 ;
	int  AdditionSolution[64] = { 0 };
	int divisionSolution[64] = { 0 }, NumberOfDividesSolution[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		SecondarySecondNumber[i] = SecondNumber[i];
		LastValidResult[i] = FirstNumber[i];
	}

	c = NumberOfBitsToShift;
	while (NumberOfBitsToShift > -1)
	{
		NegFlag = false;
		x = 0;
		Zeroing64IntArray(NumberOfDivides);
		
		if (c == NumberOfBitsToShift)
		{
			c--;
			subtractionCount = 0;
			ShiftLeft_30(OneArray, NumberOfBitsToShift);
			for (int i = 0; i < 64; i++)
			{
				NumberOfDivides[i] = OneArray[i];
				OneArray[i] = 0;
			}
			OneArray[63] = 1;
		}

		else
		{
			Zeroing64IntArray(NumberOfDivides);
			Addition(subNext, OneArray, subNextAdded);
			
			for (int i = 0; i < 64; i++)
			{
				subNext[i] = subNextAdded[i];
			}
		}

		if (c == 0)
		{
			Zeroing64IntArray(subNext);

		}
		if (validity == 64 && NumberOfBitsToShift > 0)
		{
			ShiftRight(SecondarySecondNumber);
			NumberOfBitsToShift -= 1;
			ShiftLeft_30(OneArray, NumberOfBitsToShift);
			for (int i = 0; i < 64; i++)
			{
				NumberOfDivides[i] = OneArray[i];
				OneArray[i] = 0;
			}
			OneArray[63] = 1;
			subtractionCount = 0;

		}

		else if (validity == 64 && NumberOfBitsToShift == 0)
		{
			NumberOfBitsToShift -= 1;
			Zeroing64IntArray(NumberOfDivides);

		}

		else
		{
			validity = 0;
			subtractionCount = 1;
			while (GreaterThan(LastValidResult, SecondarySecondNumber))
			{

				if (counter == 0)
				{
					ShiftLeft_30(SecondarySecondNumber, NumberOfBitsToShift);
					counter++;


				}
				else
				{
					Addition(subNext, OneArray, subNextAdded);
					ShiftLeft_30(SecondarySecondNumber, 1);
					NumberOfBitsToShift += 1;
					for (int i = 0; i < 64; i++)
					{
						subNext[i] = subNextAdded[i];
					}
				}

			}

			ShiftRight(SecondarySecondNumber);
			NumberOfBitsToShift -= 1;
			for (int i = 0; i < 64; i++)
			{
				if (subNext[i] == 0)
					x++;
			}

			if (x == 64)
				Addition(subNext, OneArray, subNextAdded);
			else
				Subtraction(subNext, OneArray, subNextAdded);

		}

		Subtraction(LastValidResult, SecondarySecondNumber, SubtractionSolution);
		validity = 0;
		for (int i = 0; i < 64; i++)
		{
			if (SubtractionSolution[i] == 0)
				validity++;
		}
		if (validity == 64)
		{
			subtractionCount = 0;
			Zeroing64IntArray(subNext);
			NumberOfBitsToShift--;
		}

		else
		{
			subtractionCount = 1;
			NumberOfBitsToShift--;
		}

		if (NumberOfBitsToShift == -1)
		{
			Zeroing64IntArray(NumberOfDivides);
			Zeroing64IntArray(subNext);
		}
		//if (NumberOfBitsToShift == -1)
		//{
		//	Zeroing64IntArray(NumberOfDivides);
		//	Zeroing64IntArray(subNext);
		//}
		ChangeIntToStr(&NumberOfDivides_String, NumberOfDivides);
		product(NumberOfDivides_String, to_string(subtractionCount), NumberOfDividesSolution);

		ShiftLeft_30(OneArray, NumberOfBitsToShift);
		for (int i = 0; i < 64; i++)
		{
			NumberOfDivides[i] = OneArray[i];
			LastValidResult[i] = SubtractionSolution[i];
			OneArray[i] = 0;
		}
		OneArray[63] = 1;

		ChangeIntToStr(&subNext_string, subNextAdded);
		ChangeIntToStr(&TwoArrayShifted_string, NumberOfDivides);
		product(subNext_string, TwoArrayShifted_string, NumberOfDividesSolution_sub);
		if (x == 64)
			Subtraction(NumberOfDividesSolution, NumberOfDividesSolution_sub, AdditionSolution);
		else
			Addition(NumberOfDividesSolution, NumberOfDividesSolution_sub, AdditionSolution);
		Addition(Division, AdditionSolution, divisionSolution);

		for (int i = 0; i < 64; i++)
		{
			Division[i] = divisionSolution[i];

		}
	
	}

	cout << endl << "Division Value: ";
	for (int j = 0; j < 64; j++)
	{
		printf("%09d", Division[j]);
	}
	cout << endl;
}
*/
/*
void ModulusSubt_div(int *FirstNumber, int *SecondNumber, int *result, int NumberOfBitsToShift, int *Division)
{

	int SubtractionSolution[65] = { 0 };
	int SecondarySecondNumber[64] = { 0 };
	int shiftedSecondNumber[65] = { 0 };
	int counter = 0, NumberOfShifts = 0, remainderOfshifts = 0;
	int NumberOfDivides[64] = { 0 }, TwoArray[64] = { 0 }, TwoArrayShifted[64] = { 0 }, OneArray[64] = { 0 }; // new for array
	TwoArray[63] = 2; OneArray[63] = 1;
	int LastValidResult[64] = { 0 };
	int solution[64] = { 0 };
	int validity = 0;
	int c = 0, k = 63;
	int subtractionCount = 0;
	int subNext[64] = { 0 }, subNextAdded[64] = { 0 }, ZeroArray[64] = { 0 }, NumberOfDividesSolution[64] = { 0 }; // new for array
	int SubNextSol[64] = { 0 }, NumberOfDividesSolution_sub[64] = { 0 }; // new for array
	string NumberOfDivides_String = "", subNext_string = "", TwoArrayShifted_string = ""; // new for array
	bool NegFlag = false;
	int x = 0, power = 0, remainder = 0;
	int  AdditionSolution[64] = { 0 };
	int divisionSolution[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		LastValidResult[i] = FirstNumber[i];
		SecondarySecondNumber[i] = SecondNumber[i];
	}
	c = NumberOfBitsToShift;
	while (NumberOfBitsToShift > -1)
	{
		NegFlag = false;
		x = 0;
		subtractionCount = 0;
		if (c == NumberOfBitsToShift)
		{

			if (c == 0)
			{
				Zeroing64IntArray(subNext);
			}
			else
			{
				c--;
				//ShiftLeft_30(OneArray, NumberOfBitsToShift);
				//for (int i = 0; i < 64; i++)
				//{
				//	NumberOfDivides[i] = OneArray[i];
				//	OneArray[i] = 0;
				//}
				//OneArray[63] = 1;
			}
		}

		else
		{
			if (c == 0)
			{
				Zeroing64IntArray(subNext);
			}
			else
			{

				Addition(subNext, OneArray, subNextAdded);
				for (int i = 0; i < 64; i++)
				{
					subNext[i] = subNextAdded[i];
				}
			}
		}


		//if (validity == 64 && NumberOfBitsToShift > 0)
		//{
		//	//for (int i = 0; i < 64; i++)
		//	//{
		//	//	LastValidResult[i] = solution[i];
		//	//}
		//	ShiftRight(SecondarySecondNumber);
		//	subtractionCount = 0;
		//	NumberOfBitsToShift -= 1;
		//	ShiftLeft_30(OneArray, NumberOfBitsToShift);
		//	for (int i = 0; i < 64; i++)
		//	{
		//		NumberOfDivides[i] = OneArray[i];
		//		OneArray[i] = 0;
		//	}
		//	OneArray[63] = 1;
		//	
		//}
		//	else if (validity == 64 && NumberOfBitsToShift == 0)
		//	{
		//		for (int i = 0; i < 64; i++)
		//		{
		//			LastValidResult[i] = solution[i];
		//		}
		//		NumberOfBitsToShift -= 1;
		//		Zeroing64IntArray(NumberOfDivides);
		//	}
		if (validity == 64)
		{
			/*		for (int i = 0; i < 64; i++)
			{
			LastValidResult[i] = solution[i];
			}	NumberOfBitsToShift -= 1;
			if (NumberOfBitsToShift > 0)
			{
				ShiftRight(SecondarySecondNumber);
				ShiftLeft_30(OneArray, NumberOfBitsToShift);
				for (int i = 0; i < 64; i++)
				{
					subtractionCount = 0;
					NumberOfDivides[i] = OneArray[i];
					OneArray[i] = 0;
				}
				OneArray[63] = 1;
			}
			else if (NumberOfBitsToShift == 0)
			{
				Zeroing64IntArray(NumberOfDivides);
			}
		}
		else
		{
			validity = 0;
			while (GreaterThan(LastValidResult, SecondarySecondNumber))
			{

				if (counter == 0)
				{
					ShiftLeft_30(SecondarySecondNumber, NumberOfBitsToShift);
					counter++;


				}
				else
				{
					x = 0;
					Addition(subNext, OneArray, subNextAdded);
					ShiftLeft_30(SecondarySecondNumber, 1);
					NumberOfBitsToShift += 1;
					for (int i = 0; i < 64; i++)
					{
						subNext[i] = subNextAdded[i];
						if (subNext[i] == 0)
							x++;
					}
				}

			}

			ShiftRight(SecondarySecondNumber);
			NumberOfBitsToShift -= 1;
			//subNext -= 1;............................... lw alminus ba2a neg. htedrab w hy3teberha zero !!
			//for (int i = 0; i < 64; i++)
			//{
			//	if (subNext[i] == 0)
			//		x++;
			//}
			//if (x == 64)
			//	NegFlag = true;
			if (x == 64)
				Addition(subNext, OneArray, subNextAdded);
			else
				Subtraction(subNext, OneArray, subNextAdded);
			for (int i = 0; i < 64; i++)
			{
				//			solution[i] = LastValidResult[i];
				subNext[i] = subNextAdded[i];

			}

		}

		Subtraction(LastValidResult, SecondarySecondNumber, SubtractionSolution);
		validity = 0;
		for (int i = 0; i < 64; i++)
		{
			//		LastValidResult[i] = SubtractionSolution[i];
			if (SubtractionSolution[i] == 0)
				validity++;
		}

		if (validity == 64)
		{
			subtractionCount = 0;
			Zeroing64IntArray(subNext);
		}

		else
		{
			subtractionCount = 1;

			
			//if (NumberOfBitsToShift == -1)
			//{
			//	//NumberOfDivides = 0;
			//	//subNext = 0;
			//	Zeroing64IntArray(NumberOfDivides);
			//	Zeroing64IntArray(subNext);
			//}
			//DividingBits += NumberOfDivides*subtractionCount + subNext *pow(2, NumberOfBitsToShift);
			ChangeIntToStr(&NumberOfDivides_String, NumberOfDivides);
			product(NumberOfDivides_String, to_string(subtractionCount), NumberOfDividesSolution);

			ShiftLeft_30(OneArray, NumberOfBitsToShift);
			for (int i = 0; i < 64; i++)
			{
				NumberOfDivides[i] = OneArray[i];
				OneArray[i] = 0;
			}
			OneArray[63] = 1;
			subNext[63] = 1;
			if (NumberOfBitsToShift > -1)
			{

				ChangeIntToStr(&subNext_string, subNext);
				ChangeIntToStr(&TwoArrayShifted_string, NumberOfDivides);
				product(subNext_string, TwoArrayShifted_string, NumberOfDividesSolution_sub);
				if (x == 64)
					Subtraction(NumberOfDividesSolution, NumberOfDividesSolution_sub, AdditionSolution);
				else
					Addition(NumberOfDividesSolution, NumberOfDividesSolution_sub, AdditionSolution);
				Addition(Division, AdditionSolution, divisionSolution);
				for (int i = 0; i < 64; i++)
				{
					Division[i] = divisionSolution[i];
				}
				Zeroing64IntArray(subNext);
				NumberOfBitsToShift--;
			}
		}
	}
		//for (int i = 0; i < 64; i++)
		//{
		//	LastValidResult[i] = solution[i];
		//}
		//cout << endl << "Modulus Value: ";
		//for (int j = 0; j < 64; j++)
		//{
		//	printf("%09d", LastValidResult[j]);
		//}
		//cout << endl;
		cout << endl << "Division Value: ";
		for (int j = 0; j < 64; j++)
		{
			printf("%09d", Division[j]);
		}
		cout << endl;
	

}


*/
/*
void ModulusSubtract_30_div_1(int *FirstNumber, int *SecondNumber, int *result, int NumberOfBitsToShift, int *Division)
{

	int SubtractionSolution[65] = { 0 };
	int SecondarySecondNumber[64] = { 0 };
	int shiftedSecondNumber[65] = { 0 };
	int counter = 0, NumberOfShifts = 0, remainderOfshifts = 0;
	for (int i = 0; i < 64; i++)
	{
		SecondarySecondNumber[i] = SecondNumber[i];
	}
	int NumberOfDivides[64] = { 0 }, TwoArray[64] = { 0 }, TwoArrayShifted[64] = { 0 }, OneArray[64] = { 0 }; // new for array
	TwoArray[63] = 2; OneArray[63] = 1;
	int LastValidResult[64] = { 0 };
	int solution[64] = { 0 };
	int validity = 0;
	int c = 0, k = 63;
	int subtractionCount = 0;
	int subNext[64] = { 0 }, subNextAdded[64] = { 0 }, ZeroArray[64] = { 0 }, NumberOfDividesSolution[64] = { 0 }; // new for array
	int SubNextSol[64] = { 0 }, NumberOfDividesSolution_sub[64] = { 0 }; // new for array
	string NumberOfDivides_String = "", subNext_string = "", TwoArrayShifted_string = ""; // new for array
	bool NegFlag = false;
	int x = 0, power = 0, remainder = 0;
	int  AdditionSolution[64] = { 0 };
	int divisionSolution[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		LastValidResult[i] = FirstNumber[i];
	}


	for (int i = 0; i < 64; i++)
	{
		solution[i] = LastValidResult[i];
	}


	c = NumberOfBitsToShift;
	while (NumberOfBitsToShift > -1)
	{
		NegFlag = false;
		x = 0;
		if (c == NumberOfBitsToShift)
		{
			subtractionCount = 0;
			c--;
			//NumberOfDivides = pow(2, NumberOfBitsToShift);
			ShiftLeft_30(OneArray, NumberOfBitsToShift);
			for (int i = 0; i < 64; i++)
			{
				NumberOfDivides[i] = OneArray[i];
				OneArray[i] = 0;
			}
				OneArray[63] = 1;
			
		}

		else
		{
			//NumberOfDivides =  0 ;
			//subNext += 1;
			Zeroing64IntArray(NumberOfDivides);
			Addition(subNext, OneArray, subNextAdded);
			for (int i = 0; i < 64; i++)
			{
				subNext[i] = subNextAdded[i];
			}
		}

		if (c == 0)
		{
			//NumberOfDivides = 0;
			//subNext = 0;
			Zeroing64IntArray(NumberOfDivides);
			Zeroing64IntArray(subNext);

		}
		SubtractionSolution[0] = { 0 };
		if (validity == 64 && NumberOfBitsToShift > 0)
		{
			for (int i = 0; i < 64; i++)
			{
				LastValidResult[i] = solution[i];
			}
			ShiftRight(SecondarySecondNumber);
			NumberOfBitsToShift -= 1;
			ShiftLeft_30(OneArray, NumberOfBitsToShift);
			for (int i = 0; i < 64; i++)
			{
				NumberOfDivides[i] = OneArray[i];
				OneArray[i] = 0;
			}
			OneArray[63] = 1;
			subtractionCount = 0;

		}

		else if (validity == 64 && NumberOfBitsToShift == 0)
		{

			for (int i = 0; i < 64; i++)
			{
				LastValidResult[i] = solution[i];
			}
			NumberOfBitsToShift -= 1;
			//	NumberOfDivides = 0;
			Zeroing64IntArray(NumberOfDivides);

		}
		else
		{
			validity = 0;
			while (GreaterThan(LastValidResult, SecondarySecondNumber))
			{

				if (counter == 0)
				{
					ShiftLeft_30(SecondarySecondNumber,NumberOfBitsToShift);
					counter++;


				}
				else
				{
					//	subNext += 1;
					Addition(subNext, OneArray, subNextAdded);
					ShiftLeft_30(SecondarySecondNumber, 1);
					NumberOfBitsToShift += 1;
					for (int i = 0; i < 64; i++)
					{
						subNext[i] = subNextAdded[i];
					}
				}

			}

			ShiftRight(SecondarySecondNumber);
			NumberOfBitsToShift -= 1;
			//subNext -= 1;............................... lw alminus ba2a neg. htedrab w hy3teberha zero !!
			for (int i = 0; i < 64; i++)
			{
				if (subNext[i] == 0)
					x++;
			}

			if (x == 64)
				NegFlag = true;
			if (NegFlag)
				Addition(subNext, OneArray, subNextAdded);
			else
				Subtraction(subNext, OneArray, subNextAdded);
			for (int i = 0; i < 64; i++)
			{
				solution[i] = LastValidResult[i];
				subNext[i] = subNextAdded[i];

			}

		}

		Subtraction(LastValidResult, SecondarySecondNumber, SubtractionSolution);
		validity = 0;
		for (int i = 0; i < 64; i++)
		{
			LastValidResult[i] = SubtractionSolution[i];
			if (LastValidResult[i] == 0)
				validity++;
		}

		if (validity == 64)
		{
			subtractionCount = 0;
			//subNext = 0;
			Zeroing64IntArray(subNext);
		}

		else
		{
			subtractionCount = 1;

		}

		if (NumberOfBitsToShift == -1)
		{
			//NumberOfDivides = 0;
			//subNext = 0;
			Zeroing64IntArray(NumberOfDivides);
			Zeroing64IntArray(subNext);
		}
		//DividingBits += NumberOfDivides*subtractionCount + subNext *pow(2, NumberOfBitsToShift);
		ChangeIntToStr(&NumberOfDivides_String, NumberOfDivides);
		product(NumberOfDivides_String, to_string(subtractionCount), NumberOfDividesSolution);

		ShiftLeft_30(OneArray, NumberOfBitsToShift);
		for (int i = 0; i < 64; i++)
		{
			NumberOfDivides[i] = OneArray[i];
			OneArray[i] = 0;
		}
		OneArray[63] = 1;

		ChangeIntToStr(&subNext_string, subNext);
		ChangeIntToStr(&TwoArrayShifted_string, NumberOfDivides);
		product(subNext_string, TwoArrayShifted_string, NumberOfDividesSolution_sub);
		if (NegFlag)
			Subtraction(NumberOfDividesSolution, NumberOfDividesSolution_sub, AdditionSolution);
		else
			Addition(NumberOfDividesSolution, NumberOfDividesSolution_sub, AdditionSolution);
		Addition(Division, AdditionSolution, divisionSolution);
		for (int i = 0; i < 64; i++)
		{
			Division[i] = divisionSolution[i];
		}

		//	Division_result(c, validity, NumberOfBitsToShift, subNext,divisionSolution);
		//Division_result(NumberOfBitsToShift, subNext, subtractionCount, divisionSolution);
		//subNext = 0;
		Zeroing64IntArray(subNext);
	}
	for (int i = 0; i < 64; i++)
	{
		LastValidResult[i] = solution[i];
	}
	cout << endl << "Modulus Value: ";
	for (int j = 0; j < 64; j++)
	{
		printf("%09d", LastValidResult[j]);
	}
	cout << endl;

}
*/
/*
// if number of bits more than 30 shifts
void ModulusSubtract_30(int *FirstNumber, int *SecondNumber, int *result, int NumberOfBitsToShift , double &DividingBits )
{

int SubtractionSolution[65] = { 0 };
int SecondarySecondNumber[64] = { 0 };
int shiftedSecondNumber[65] = { 0 };
int counter = 0, NumberOfShifts = 0, remainderOfshifts = 0;
for (int i = 0; i < 64; i++)
{
SecondarySecondNumber[i] = SecondNumber[i];
}
long double NumberOfDivides = 0;// , DividingBits = 0;
int LastValidResult[64] = { 0 };
int solution[64] = { 0 };
int validity = 0;
int c = 0 , k = 63;
int subtractionCount = 0;
int subNext = 0;
double  AdditionSolution[64] = { 0 };
int divisionSolution[64] = { 0 };
for (int i = 0; i < 64; i++)
{
LastValidResult[i] = FirstNumber[i];
}


for (int i = 0; i < 64; i++)
{
solution[i] = LastValidResult[i];
}


c = NumberOfBitsToShift;
while (NumberOfBitsToShift > -1)
{
//	double DividingBits[64] = { 0 };
if (c == NumberOfBitsToShift)
{
subtractionCount = 0;
c--;
NumberOfDivides = pow(2, NumberOfBitsToShift);


}

else
{
NumberOfDivides = 0;
subNext += 1;
}

if (c == 0)
{
NumberOfDivides = 0;
subNext = 0;
}

//	NumberOfDivides = pow ( 2 , NumberOfBitsToShift);

SubtractionSolution[0] = { 0 };
if (validity == 64 && NumberOfBitsToShift > 0)
{
for (int i = 0; i < 64; i++)
{
LastValidResult[i] = solution[i];
}
ShiftRight(SecondarySecondNumber);
NumberOfBitsToShift -= 1;
NumberOfDivides = powl(2, NumberOfBitsToShift);
subtractionCount = 0;

}

else if (validity == 64 && NumberOfBitsToShift == 0)
{

for (int i = 0; i < 64; i++)
{
LastValidResult[i] = solution[i];
}
NumberOfBitsToShift -= 1;
NumberOfDivides = 0;

}
else
{
validity = 0;
while (GreaterThan(LastValidResult, SecondarySecondNumber))
{

if (counter == 0)
{
//NumberOfShifts = NumberOfBitsToShift / 30;
//remainderOfshifts = NumberOfBitsToShift % 30;
//for (int i = 0; i < NumberOfShifts; i++)
//{
//	ShiftLeft(SecondarySecondNumber, 30, shiftedSecondNumber);
//	for (int i = 0; i < 64; i++)
//	{
//		SecondarySecondNumber[i] = shiftedSecondNumber[i];
//	}
//}
//ShiftLeft(SecondarySecondNumber, remainderOfshifts, shiftedSecondNumber);
//for (int i = 0; i < 64; i++)
//{
//	SecondarySecondNumber[i] = shiftedSecondNumber[i];
//}
ShiftLeft_30(SecondarySecondNumber, NumberOfBitsToShift);
counter++;


}
else
{
subNext += 1;
//	ShiftLeft(SecondarySecondNumber, 1, shiftedSecondNumber);
ShiftLeft_30(SecondarySecondNumber, 1);
NumberOfBitsToShift += 1;
//for (int i = 0; i < 64; i++)
//{
//	SecondarySecondNumber[i] = shiftedSecondNumber[i];
//}
}

}

ShiftRight(SecondarySecondNumber);
NumberOfBitsToShift -= 1;
subNext -= 1;
for (int i = 0; i < 64; i++)
{
solution[i] = LastValidResult[i];
}
}

Subtraction(LastValidResult, SecondarySecondNumber, SubtractionSolution);
validity = 0;
for (int i = 0; i < 64; i++)
{
LastValidResult[i] = SubtractionSolution[i];
if (LastValidResult[i] == 0)
validity++;
}

if (validity == 64)
{
subtractionCount = 0;
subNext = 0;
}

else subtractionCount = 1;
if (NumberOfBitsToShift == -1)
{
NumberOfDivides = 0;
subNext = 0;
}
DividingBits += NumberOfDivides*subtractionCount + subNext *pow(2, NumberOfBitsToShift );
//	Division_result(c, validity, NumberOfBitsToShift, subNext,divisionSolution);
//		Division_result(NumberOfBitsToShift, subNext, subtractionCount, divisionSolution);
subNext = 0;
}
for (int i = 0; i < 64; i++)
{
LastValidResult[i] = solution[i];
}
cout << endl << "Modulus Value: ";
for (int j = 0; j < 64; j++)
{
printf("%09d", LastValidResult[j]);
}
cout << endl;

}
*/
/*
// another function for multiplication
char * multiply(const char num1[], const char num2[]) {
	static char mul[MAX];
	char a[MAX];
	char b[MAX];
	char c[MAX];
	char temp[1000 * MAX];
	int la, lb;
	int i = 0, j, k = 0, x = 0, y;
	long int r = 0;
	long sum = 0;


	while (num1[i]) {
		a[i] = num1[i];
		i++;
	}
	a[i] = '\0';

	i = 0;
	while (num2[i]) {
		b[i] = num2[i];
		i++;
	}
	b[i] = '\0';

	la = strlen(a) - 1;
	lb = strlen(b) - 1;

	for (i = 0; i <= la; i++) {
		a[i] = a[i] - 48;
	}

	for (i = 0; i <= lb; i++) {
		b[i] = b[i] - 48;
	}

	for (i = lb; i >= 0; i--) {
		r = 0;
		for (j = la; j >= 0; j--) {
			int x = b[i] * a[j] + r;
			temp[k++] = x % 10;
			r = x / 10;
		}
		temp[k++] = r;
		x++;
		for (y = 0; y<x; y++) {
			temp[k++] = 0;
		}
	}

	k = 0;
	r = 0;
	for (i = 0; i<la + lb + 2; i++) {
		sum = 0;
		y = 0;
		for (j = 1; j <= lb + 1; j++) {
			if (i <= la + j) {
				sum = sum + temp[y + i];
			}
			y += j + la + 1;
		}
		c[k++] = (sum + r) % 10;
		r = (sum + r) / 10;
	}
	c[k] = r;
	j = 0;
	for (i = k - 1; i >= 0; i--) {
		mul[j++] = c[i] + 48;
	}
	mul[j] = '\0';
	return mul;
}


// not best working div ...but working mod
void ModulusSubtract_30_div(int *FirstNumber, int *SecondNumber, int *result, int NumberOfBitsToShift , int *Division)
{

	int SubtractionSolution[65] = { 0 };
	int SecondarySecondNumber[64] = { 0 };
	int shiftedSecondNumber[65] = { 0 };
	int counter = 0, NumberOfShifts = 0, remainderOfshifts = 0;
	int NumberOfDivides[64] = { 0 }, TwoArray[64] = { 0 }, TwoArrayShifted[64] = {0}, OneArray[64] = { 0 }; // new for array
	TwoArray[63] = 2; OneArray[63] = 1; 
	int LastValidResult[64] = { 0 };
	int solution[64] = { 0 };
	int validity = 0;
	int c = 0;
	int	k = 63;
	int subtractionCount = 0;
	int AdditionSolution_1[64] = { 0 };
	int subNext[64] = { 0 }, subNextAdded[64] = { 0 }, ZeroArray[64] = { 0 }, NumberOfDividesSolution[65] = {0}; // new for array
	int SubNextSol[64] = { 0 }, NumberOfDividesSolution_sub[65] = { 0 }; // new for array
	string NumberOfDivides_String = "" , subNext_string ="" , TwoArrayShifted_string=""; // new for array
	bool NegFlag = false , neg = false;
	int x = 0, power = 0, remainder = 0;
	int  AdditionSolution[65] = { 0 };
	int divisionSolution[64] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		LastValidResult[i] = FirstNumber[i];
		SecondarySecondNumber[i] = SecondNumber[i];
	}


	for (int i = 0; i < 64; i++)
	{
		solution[i] = LastValidResult[i];
	}


	c = NumberOfBitsToShift;
	while (NumberOfBitsToShift > -1)
	{
		NegFlag = false;
		x = 0;
		//power = NumberOfBitsToShift / 30;
		//remainder = NumberOfBitsToShift%30;
		//if (c == 0)
		//{
		//	Zeroing64IntArray(NumberOfDivides);
		//	Zeroing64IntArray(subNext);

		//}

		if (c == NumberOfBitsToShift)
		{
			subtractionCount = 0;
			c--;
			ShiftLeft_30(OneArray, NumberOfBitsToShift);
			for (int i = 0; i < 64; i++)
			{
				NumberOfDivides[i] = OneArray[i];
				OneArray[i] = 0;
			}
			OneArray[63] = 1;
		}

		else
		{
			Zeroing64IntArray(NumberOfDivides);
			Addition(subNext, OneArray, subNextAdded);
			for (int i = 0; i < 64; i++)
			{
				subNext[i] = subNextAdded[i];
			}
		}

		if (c == 0)
		{
			Zeroing64IntArray(NumberOfDivides);
			Zeroing64IntArray(subNext);

		}
		SubtractionSolution[0] = { 0 };
		if (validity == 64 && NumberOfBitsToShift > 0)
		{
			for (int i = 0; i < 64; i++)
			{
				LastValidResult[i] = solution[i];
			}
			ShiftRight(SecondarySecondNumber);
			NumberOfBitsToShift -= 1;
			ShiftLeft_30(OneArray, NumberOfBitsToShift);
			for (int i = 0; i < 64; i++)
			{
				NumberOfDivides[i] = OneArray[i];
				OneArray[i] = 0;
			}
			OneArray[63] = 1;
			subtractionCount = 0;

		}

		else if (validity == 64 && NumberOfBitsToShift == 0)
		{

			for (int i = 0; i < 64; i++)
			{
				LastValidResult[i] = solution[i];
			}
			NumberOfBitsToShift -= 1;
			Zeroing64IntArray( NumberOfDivides );

		}
		else
		{
			validity = 0;
			while (GreaterThan(LastValidResult, SecondarySecondNumber))
			{

				if (counter == 0)
				{
					ShiftLeft_30(SecondarySecondNumber, NumberOfBitsToShift);
					counter++;


				}
				else
				{
					Addition(subNext, OneArray, subNextAdded);
					ShiftLeft_30(SecondarySecondNumber, 1);
					NumberOfBitsToShift += 1;
					for (int i = 0; i < 64; i++)
					{
						subNext[i] = subNextAdded[i];
					}
				}

			}

			ShiftRight(SecondarySecondNumber);
			NumberOfBitsToShift -= 1;
			//subNext -= 1;............................... lw alminus ba2a neg. htedrab w hy3teberha zero !!
			for (int i = 0; i < 64; i++)
			{
				if (subNext[i] == 0)
					x++;
			}

			if (x == 64)
				NegFlag = true;
			if (NegFlag)
				Addition(subNext, OneArray, subNextAdded);
			else
				Subtraction(subNext, OneArray, subNextAdded);
			for (int i = 0; i < 64; i++)
			{
				solution[i] = LastValidResult[i];
				subNext[i] = subNextAdded[i];

			}

		
		}

		Subtraction(LastValidResult, SecondarySecondNumber, SubtractionSolution);
		validity = 0;
		for (int i = 0; i < 64; i++)
		{
			LastValidResult[i] = SubtractionSolution[i];
			if (LastValidResult[i] == 0)
				validity++;
			
		}

		if (validity == 64)
		{
			//subtractionCount = 0;    ..... changed with no negative feedback
			//subNext = 0;
			Zeroing64IntArray(subNext); 
		}

		else
		{
			subtractionCount = 1;

		}
			
		if (NumberOfBitsToShift == -1)
		{
			//NumberOfDivides = 0;
			//subNext = 0;
			Zeroing64IntArray(NumberOfDivides); 
			Zeroing64IntArray(subNext); 
		}
		//DividingBits += NumberOfDivides*subtractionCount + subNext *pow(2, NumberOfBitsToShift);
		ChangeIntToStr(&NumberOfDivides_String, NumberOfDivides);
		product(NumberOfDivides_String, to_string(subtractionCount), NumberOfDividesSolution);
	
		ShiftLeft_30(OneArray, NumberOfBitsToShift);
		for (int i = 0; i < 64; i++)
		{
			NumberOfDivides[i] = OneArray[i];
			OneArray[i] = 0;
		}
		OneArray[63] = 1;

		ChangeIntToStr(&subNext_string, subNext);
		ChangeIntToStr(&TwoArrayShifted_string, NumberOfDivides);
		product(subNext_string, TwoArrayShifted_string , NumberOfDividesSolution_sub);
		//if (NegFlag)
		//{
		//	Subtraction(NumberOfDividesSolution, NumberOfDividesSolution_sub, AdditionSolution);
		//	Subtraction_1(NumberOfDividesSolution, NumberOfDividesSolution_sub, AdditionSolution ,neg );
		//}
		//	
		//else
		//	Addition(NumberOfDividesSolution, NumberOfDividesSolution_sub, AdditionSolution);
		//if (neg)
		//	Subtraction(Division, AdditionSolution, divisionSolution);
		//else
		//Addition(Division, AdditionSolution, divisionSolution);
		if (NegFlag)
			Subtraction(NumberOfDividesSolution, NumberOfDividesSolution_sub, AdditionSolution);
		else
			Addition(NumberOfDividesSolution, NumberOfDividesSolution_sub, AdditionSolution);
		
			Addition(Division, AdditionSolution, divisionSolution);
		for (int i = 0; i < 64; i++)
		{
			Division[i] = divisionSolution[i];
		}

		//	Division_result(c, validity, NumberOfBitsToShift, subNext,divisionSolution);
		//Division_result(NumberOfBitsToShift, subNext, subtractionCount, divisionSolution);
		//subNext = 0;
		Zeroing64IntArray(subNext); 
	}
	for (int i = 0; i < 64; i++)
	{
		LastValidResult[i] = solution[i];
		result[i] = LastValidResult[i];
	}
	cout << endl << "Modulus Value: ";
	for (int j = 0; j < 64; j++)
	{
		printf("%09d", LastValidResult[j]);
	}
	cout << endl;
	cout << endl << "Division Value: ";
	for (int j = 0; j < 64; j++)
	{
		printf("%09d", Division[j]);
	}
	cout << endl;
}


void divide_1(int *FirstNumber, int *SecondNumber, int *result, int NumberOfBitsToShift)
{
	int SecondaryFirstNumber[64] = { 0 },LastValidResult[64] = { 0 }, OneArray[64] = { 0 }, SecondarySecondNumber[64] = { 0 };
	OneArray[63] = 1;
	bool FirstTime = true , Negative = false;
	int NumberOfDivisions[64] = { 0 }, subtractionsolution[64] = { 0 }, additionSolution[64] = { 0 }, answer[64] = { 0 };
	int  TotalNumberOfShifts[64] = { 0 }, holdValue[64] = { 0 }, productSolution[65] = { 0 }, TwoArray[64] = { 0 };
	int subtractionCount = 0, NumberOfShifts = 0;
	TwoArray[63] = 2;
	string TotalNumberOfShifts_str;

	for (int i = 0; i < 64; i++)
	{
		SecondaryFirstNumber[i] = FirstNumber[i];
		SecondarySecondNumber[i] = SecondNumber[i];
		
	}
	while (NumberOfBitsToShift > -1)
	{
		Negative = false;
		subtractionCount = 0;
		while (GreaterThan(SecondaryFirstNumber, SecondarySecondNumber))
		{
			if (FirstTime)
			{
				NumberOfShifts = NumberOfBitsToShift;
				//ShiftLeft_30(OneArray, NumberOfShifts);
				//TotalNumberOfShifts[63] = NumberOfBitsToShift;
				ShiftLeft_30(SecondarySecondNumber, NumberOfBitsToShift);
				FirstTime = false;
				//for (int i = 0; i < 64; i++)
				//{
				//	TotalNumberOfShifts[i] = OneArray[i];
				//		OneArray[i] = 0;
				//}
				//OneArray[63] = 1;
			}
			else
			{
				ShiftLeft_30(SecondarySecondNumber, 1);
				NumberOfShifts++;
				//Addition(TotalNumberOfShifts, OneArray, holdValue); // adding one for total number of shifts
				//for (int i = 0; i < 64; i++)
				//{
				//	TotalNumberOfShifts[i] = holdValue[i];
				//}
			}
		}
// mmkn 2a2ool hena condition greater than alsecondary second & aloriginal sec .. lw aah yed5ol lw 
		// la2  ,yed5olsh w ybreak 5ales 
		ShiftRight(SecondarySecondNumber);
		NumberOfShifts--;
		ShiftLeft_30(OneArray, NumberOfShifts);
		for (int i = 0; i < 64; i++)
		{
			TotalNumberOfShifts[i] = OneArray[i];
				OneArray[i] = 0;
		}
		OneArray[63] = 1;
		//Subtraction(TotalNumberOfShifts, OneArray, holdValue); // removing one from total number of shifts
		//for (int i = 0; i < 64; i++)
		//{
		//	TotalNumberOfShifts[i] = holdValue[i];
		//}




		while (Negative == false)
		{
			Subtraction_1(SecondaryFirstNumber, SecondarySecondNumber, subtractionsolution, Negative);
			if (Negative == false)
			{
				//ShiftLeft_30(OneArray, NumberOfShifts);
				//NumberOfShifts++;
				subtractionCount++;
				//Addition(TotalNumberOfShifts, OneArray, additionSolution); // add one * number of shifts for each minus
				for (int i = 0; i < 64; i++)
				{
					SecondaryFirstNumber[i] = subtractionsolution[i];
				//	NumberOfShifts[i] = additionSolution[i];
				//	OneArray[i] = 0;
				}
			//	OneArray[63] = 1;

			}
			else
			{
				break;
			}

		}

		//Subtraction_1(SecondarySecondNumber, subtractionsolution, SecondaryFirstNumber, Negative); // to get last positive first number before last minus op.
		//Subtraction(NumberOfShifts, OneArray, subtractionsolution);
		ChangeIntToStr(&TotalNumberOfShifts_str, TotalNumberOfShifts);
		product(TotalNumberOfShifts_str, to_string(subtractionCount), productSolution);
		Addition(NumberOfDivisions, productSolution, answer);
		for (int i = 0; i < 64; i++)
		{
			NumberOfDivisions[i] = answer[i];
			result[i] = NumberOfDivisions[i];
		}
		NumberOfBitsToShift--;


	}

	if (SmallerThan(SecondarySecondNumber, SecondNumber) == true ) //&& !EqualTo(SecondNumber, SecondarySecondNumber))// || SecondarySecondNumber[63] % 2 == 1)
	{											
		ShiftLeft_30(SecondarySecondNumber, 1);

		//if (EqualTo(SecondarySecondNumber, SecondNumber) == true)
		//{
		//	Subtraction(NumberOfDivisions, OneArray, answer);
		//	for (int i = 0; i < 64; i++)
		//	{
		//		NumberOfDivisions[i] = answer[i];
		//		result[i] = NumberOfDivisions[i];
		//	}
		//}
		//else if (SmallerThan(SecondarySecondNumber, SecondNumber) == true)
		//{
		//	//Subtraction(NumberOfDivisions, OneArray, answer);
		//	//for (int i = 0; i < 64; i++)
		//	//{
		//	//	NumberOfDivisions[i] = answer[i];
		//	//	result[i] = NumberOfDivisions[i];
		//	//}
		//}
		//else // if bigger than y3nee
		//{
		//	Subtraction(NumberOfDivisions, OneArray, answer);
		//	for (int i = 0; i < 64; i++)
		//	{
		//		NumberOfDivisions[i] = answer[i];
		//		result[i] = NumberOfDivisions[i];
		//}
		//Subtraction(NumberOfDivisions, OneArray, answer);
		//for (int i = 0; i < 64; i++)
		//{
		//	NumberOfDivisions[i] = answer[i];
		//	result[i] = NumberOfDivisions[i];
		if (SmallerThan(SecondarySecondNumber, SecondNumber) == true)
		{

		}
		else
		{
				Subtraction(NumberOfDivisions, OneArray, answer);
				for (int i = 0; i < 64; i++)
				{
					NumberOfDivisions[i] = answer[i];
					result[i] = NumberOfDivisions[i];
				}
		}
	}
	cout << endl << "Division Value: ";
	for (int j = 0; j < 64; j++)
	{
		printf("%09d", result[j]);
	}
	cout << endl;


}
*/





// best division
void divide(int *FirstNumber, int *SecondNumber, int *result, int NumberOfBitsToShift)
{
	int SecondaryFirstNumber[64] = { 0 }, LastValidResult[64] = { 0 }, OneArray[64] = { 0 }, SecondarySecondNumber[64] = { 0 };
	OneArray[63] = 1;
	bool FirstTime = true, Negative = false;
	int NumberOfDivisions[64] = { 0 }, subtractionsolution[64] = { 0 }, additionSolution[64] = { 0 }, answer[64] = { 0 };
	int  TotalNumberOfShifts[64] = { 0 }, holdValue[64] = { 0 }, productSolution[65] = { 0 }, TwoArray[64] = { 0 };
	int subtractionCount = 0, NumberOfShifts = 0;
	TwoArray[63] = 2;
	string TotalNumberOfShifts_str;

	for (int i = 0; i < 64; i++)
	{
		SecondaryFirstNumber[i] = FirstNumber[i];
		SecondarySecondNumber[i] = SecondNumber[i];

	}
	while (NumberOfBitsToShift > -1)
	{
		Negative = false;
		subtractionCount = 0;
		while (GreaterThan(SecondaryFirstNumber, SecondarySecondNumber))
		{
			if (FirstTime)
			{
				NumberOfShifts = NumberOfBitsToShift;
				//ShiftLeft_30(OneArray, NumberOfShifts);
				//TotalNumberOfShifts[63] = NumberOfBitsToShift;
				ShiftLeft_30(SecondarySecondNumber, NumberOfBitsToShift);
				FirstTime = false;
			}
			else
			{
				ShiftLeft_30(SecondarySecondNumber, 1);
				NumberOfShifts++;

			}
		}
		// mmkn 2a2ool hena condition greater than alsecondary second & aloriginal sec .. lw aah yed5ol lw 
		// la2  ,yed5olsh w ybreak 5ales 
			ShiftRight(SecondarySecondNumber);
			NumberOfShifts--;
			if (NumberOfShifts == -1)
			{
				break;
			}
			else
			{
			ShiftLeft_30(OneArray, NumberOfShifts);
			for (int i = 0; i < 64; i++)
			{
				TotalNumberOfShifts[i] = OneArray[i];
				OneArray[i] = 0;
			}
			OneArray[63] = 1;
			}


		while (Negative == false)
		{
			Subtraction_1(SecondaryFirstNumber, SecondarySecondNumber, subtractionsolution, Negative);
			if (Negative == false)
			{
				//ShiftLeft_30(OneArray, NumberOfShifts);
				//NumberOfShifts++;
				subtractionCount++;
				//Addition(TotalNumberOfShifts, OneArray, additionSolution); // add one * number of shifts for each minus
				for (int i = 0; i < 64; i++)
				{
					SecondaryFirstNumber[i] = subtractionsolution[i];
					//	NumberOfShifts[i] = additionSolution[i];
					//	OneArray[i] = 0;
				}
				//	OneArray[63] = 1;

			}
			else
			{
				break;
			}

		}

		//Subtraction_1(SecondarySecondNumber, subtractionsolution, SecondaryFirstNumber, Negative); // to get last positive first number before last minus op.
		//Subtraction(NumberOfShifts, OneArray, subtractionsolution);
		ChangeIntToStr(&TotalNumberOfShifts_str, TotalNumberOfShifts);
		product(TotalNumberOfShifts_str, to_string(subtractionCount), productSolution);
		Addition(NumberOfDivisions, productSolution, answer);
		for (int i = 0; i < 64; i++)
		{
			NumberOfDivisions[i] = answer[i];
			result[i] = NumberOfDivisions[i];
		}
		NumberOfBitsToShift--;


	}
	/*
	if (SmallerThan(SecondarySecondNumber, SecondNumber) == true) //&& !EqualTo(SecondNumber, SecondarySecondNumber))// || SecondarySecondNumber[63] % 2 == 1)
	{
		ShiftLeft_30(SecondarySecondNumber, 1);

		//if (EqualTo(SecondarySecondNumber, SecondNumber) == true)
		//{
		//	Subtraction(NumberOfDivisions, OneArray, answer);
		//	for (int i = 0; i < 64; i++)
		//	{
		//		NumberOfDivisions[i] = answer[i];
		//		result[i] = NumberOfDivisions[i];
		//	}
		//}
		//else if (SmallerThan(SecondarySecondNumber, SecondNumber) == true)
		//{
		//	//Subtraction(NumberOfDivisions, OneArray, answer);
		//	//for (int i = 0; i < 64; i++)
		//	//{
		//	//	NumberOfDivisions[i] = answer[i];
		//	//	result[i] = NumberOfDivisions[i];
		//	//}
		//}
		//else // if bigger than y3nee
		//{
		//	Subtraction(NumberOfDivisions, OneArray, answer);
		//	for (int i = 0; i < 64; i++)
		//	{
		//		NumberOfDivisions[i] = answer[i];
		//		result[i] = NumberOfDivisions[i];
		//}
		//Subtraction(NumberOfDivisions, OneArray, answer);
		//for (int i = 0; i < 64; i++)
		//{
		//	NumberOfDivisions[i] = answer[i];
		//	result[i] = NumberOfDivisions[i];
		if (SmallerThan(SecondarySecondNumber, SecondNumber) == true)
		{

		}
		else
		{
			Subtraction(NumberOfDivisions, OneArray, answer);
			for (int i = 0; i < 64; i++)
			{
				NumberOfDivisions[i] = answer[i];
				result[i] = NumberOfDivisions[i];
			}
		}
	}
	*/
	
/*	cout << endl << "Division Value: ";
	for (int j = 0; j < 64; j++)
	{
		printf("%09d", result[j]);
	}
	cout << endl;
	*/

}


// best modulus ONLYY
void ModulusSubtract(int *FirstNumber, int *SecondNumber, int *result, int NumberOfBitsToShift)
{

		int SubtractionSolution[65] = { 0 };
		int SecondarySecondNumber[64] = { 0 };
		int shiftedSecondNumber[65] = { 0 };
		int counter = 0;
		for (int i = 0; i < 64; i++)
		{
			SecondarySecondNumber[i] = SecondNumber[i];
		}
		int NumberOfDivides = 0 , DividingBits =0 ;
		int LastValidResult[64] = { 0 };
		int solution[64] = { 0 };
		int validity = 0;


		for (int i = 0; i < 64; i++)
		{
			LastValidResult[i] = FirstNumber[i];
		}


		for (int i = 0; i < 64; i++)
		{
			solution[i] = LastValidResult[i];
		}

		while (NumberOfBitsToShift > -1)
		{

			SubtractionSolution[0] = { 0 };
			if (validity == 64 && NumberOfBitsToShift > 0)
			{
				for (int i = 0; i < 64; i++)
				{
					LastValidResult[i] = solution[i];
				}
				ShiftRight(SecondarySecondNumber);
				NumberOfBitsToShift -= 1;
				NumberOfDivides += 1;
				//NumberOfDivides -= 2;

			}

			else if (validity == 64 && NumberOfBitsToShift == 0)
			{

				for (int i = 0; i < 64; i++)
				{
					LastValidResult[i] = solution[i];
				}
				NumberOfBitsToShift -= 1;
				//NumberOfDivides -= 2;
			}
			else
			{
				validity = 0;
				while (GreaterThan(LastValidResult, SecondarySecondNumber))
				{
		
					if (counter == 0)
					{
				//		ShiftLeft(SecondarySecondNumber, NumberOfBitsToShift, shiftedSecondNumber);
						ShiftLeft_30(SecondarySecondNumber, NumberOfBitsToShift);
						//for (int i = 0; i < 64; i++)
						//{
						//	SecondarySecondNumber[i] = shiftedSecondNumber[i];
						//}
						counter++;
						NumberOfDivides +=  NumberOfBitsToShift;
					}
					else
					{
				//		ShiftLeft(SecondarySecondNumber, 1, shiftedSecondNumber);
						ShiftLeft_30(SecondarySecondNumber, 1);
						NumberOfBitsToShift += 1;
						//for (int i = 0; i < 64; i++)
						//{
						//	SecondarySecondNumber[i] = shiftedSecondNumber[i];
						//}
						NumberOfDivides += 1;
					}

				}

				ShiftRight(SecondarySecondNumber);
				NumberOfBitsToShift -= 1;
	//			NumberOfDivides -= 1;
				for (int i = 0; i < 64; i++)
				{
					solution[i] = LastValidResult[i];
				}
			}

			Subtraction(LastValidResult, SecondarySecondNumber, SubtractionSolution);
			validity = 0;
			for (int i = 0; i < 64; i++)
			{
				LastValidResult[i] = SubtractionSolution[i];
				if (LastValidResult[i] == 0)
					validity++;
			}

		}
		for (int i = 0; i < 64; i++)
		{
			LastValidResult[i] = solution[i];
			result[i] = LastValidResult[i];
		}
/*		cout << endl << "Modulus Value: ";
		for (int j = 0; j < 64; j++)
		{
			printf("%09d", LastValidResult[j]);
		}
		cout << endl;
		*/
}


// working well ... if true choose modulus (div_value not used) , if false choose division & modulus (both used)
void modulus(int *FirstNumber, int *SecondNumber, int *value , bool modulus , int * division_value)
{
	value[64] = { 0 };
	int NumberOfEqualBytes = 0;
	int NumberOfZerosFirst = 0;
	int NumberOfZerosSecond = 0;
	int NumberOfBits_First = 0;
	int NumberOfBits_Sec = 0;
	int NumberOfBitsToShift = 0;
	//int subtraction_result[64] = { 0 }; ... not needed nw after sending the array itself to get the answer
	int count = 0;
	double Division_Value = 0;
	//int division_value[64] = { 0 }; ... not needed nw after sending the array itself to get the answer
	Zeroing64IntArray(division_value);
	for (int i = 0; i < 64; i++)
	{
		if (FirstNumber[i] == SecondNumber[i])
		{
			NumberOfEqualBytes += 1;
		}
		else if (FirstNumber[i] > SecondNumber[i])
		{
			if (SecondNumber[i] |= 0)
			{
	
				while (true)
				{

					if (FirstNumber[i] >= pow(2, NumberOfBits_First))
					{
						NumberOfBits_First += 1;
					}

					else
					{
						break;
					}
				}

				while (true)
				{

					if (SecondNumber[i] >= pow(2, NumberOfBits_Sec))
					{
						NumberOfBits_Sec += 1;
					}

					else
					{
						break;
					}

				}
			}
			else if (SecondNumber[i] == 0)
			{
				while (true)
				{

					if (FirstNumber[i] >= pow(2, NumberOfBits_First))
					{
						NumberOfBits_First += 1;
					}

					else
					{
						break;
					}

				}

				while (true)
				{

	
					if (SecondNumber[i] == 0)
					{
						i++;
						count++;
					}
					else if (SecondNumber[i] >= pow(2, NumberOfBits_Sec))
					{
						NumberOfBits_Sec += 1;
					}

					else
					{
						break;
					}

				}
			}

			break;
		}


	}

//	NumberOfBitsToShift = NumberOfBits_First * count + (NumberOfBits_First- NumberOfBits_Sec)  ;
	NumberOfBitsToShift = 30 * count + (NumberOfBits_First - NumberOfBits_Sec);
	
	if (modulus)
	{
		// best mod only	
		//ModulusSubtract(FirstNumber, SecondNumber, subtraction_result, NumberOfBitsToShift);
		ModulusSubtract(FirstNumber, SecondNumber, value, NumberOfBitsToShift);
	}
	else
	{
		//working div &mod  
//....	ModulusSubtract_30_div(FirstNumber, SecondNumber, value, NumberOfBitsToShift, division_value); // for division try
		divide(FirstNumber, SecondNumber, division_value, NumberOfBitsToShift); // best division

//		divide_1(FirstNumber, SecondNumber, division_value, NumberOfBitsToShift);
		ModulusSubtract(FirstNumber, SecondNumber, value, NumberOfBitsToShift);
	}


}

//working N,K & Q
void Get_K_and_Q(string FirstNumber, string SecondNumber, int *k, int *Q , int *N)
{
	 N[0]= { 0 };
	int N_minus_1[128] = { 0 };
	int Remainder = 0;
	int One[64] = { 0 };
	One[63] += 1;
	Zeroing64IntArray(k);
	Zeroing64IntArray(Q);
	int Final_K[64] = { 0 };
	product(FirstNumber, SecondNumber,N);
	N[63] -= 1;
	while (true)
	{
		Remainder = N[63] % 2;
		if (Remainder == 0)
		{
			Addition(k, One, Final_K);
			ShiftRight(N);
		}
		else
		{
			for (int i = 0; i < 64; i++)
			{
				Q[i] = N[i];
			}
			break;
		}

		for (int i = 0; i < 64; i++)
		{
			k[i] = Final_K[i];
		}
			
	}

}

// give it N return k & q
void Get_K_and_Q_1(int *N, int *k, int *Q)
{
	int N_minus_1[64] = { 0 };
	int Remainder = 0;
	int One[64] = { 0 };
	One[63] += 1;
	Zeroing64IntArray(k);
	Zeroing64IntArray(Q);
	int Final_K[64] = { 0 };
	//product(FirstNumber, SecondNumber, N);
	//N[63] -= 1;
	for (int i = 0; i < 64; i++)
	{
		N_minus_1[i] = N[i];
	}
	N_minus_1[63] -= 1;
	while (true)
	{
		Remainder = N_minus_1[63] % 2;
		if (Remainder == 0)
		{
			Addition(k, One, Final_K);
			ShiftRight(N_minus_1);
		}
		else
		{
			for (int i = 0; i < 64; i++)
			{
				Q[i] = N_minus_1[i];
			}
			break;
		}

		for (int i = 0; i < 64; i++)
		{
			k[i] = Final_K[i];
		}

	}

}


/*
void powerModN(int *base, int *power, int *mod , int *counter)
{
	//int counter[64] = { 0 }, 
	int basePower[64] = { 0 }, result[64] = { 0 }, modulusSol[64] = { 0 }  ;
	string basePower_str;
	for (int i = 0; i < 64; i++)
	{
		result[i] = base[i];
	}
	while (GreaterThan(power, counter))
	{
		ChangeIntToStr(&basePower_str, basePower);
		product(basePower_str, basePower_str, result);
		modulus(result, mod, modulusSol);
		ShiftLeft_30(counter, 1);
		powerModN(modulusSol, power, mod, counter);
	}
}
*/
/*
void powerModn(int * k, int * n)
{

	if (k == Big512(0))
		return Big512(1);
	else if (k == Big512(1))
		return (*this);
	else if ((*this) == Big512(1))
		return (*this);
	Big512 tmp((*this));
	Big512 K(k);
	Big1024 tmp2;
	Big512 result(1);
	while (K > Big512(0))
	{
		if (K.isOdd())
		{
			tmp2 = ((tmp)*result).rem(n);
			for (int j = 0; j < 18; j++)
				result.value[j] = tmp2.value[j + 18];
		}
		tmp2 = (tmp*tmp).rem(n);
		if (tmp2 == Big1024(tmp))
			break;
		for (int j = 0; j < 18; j++)
			tmp.value[j] = tmp2.value[j + 18];
		//if (K.isOdd())
		//	++i;
		K = K.dividebytwo();
	}
	//if (K == Big512(1))
	//{
	//	++i;
	//}

	return result;


}
*/

// working base^exp % (mod)
int * modpow(int * base, int * exp, int * mod , int *result)
{
	int ModulusSolution[65] = { 0 }, productValue[65] = {0}, result_spare[65] = { 0 };
	int base_spare[65] = { 0 }, divisionValue[64] = { 0 }; //, result[65] = { 0 }
	Zeroing64IntArray(result);
	result[63] = 1; 
	string result_str , base_str;
	//base %= mod;
	//result = 1;
	modulus(base, mod, ModulusSolution , true, divisionValue); // divisionValue not used here
	for (int i = 0; i < 64; i++)
	{
		base[i] = ModulusSolution[i];
	}

	while (exp[63] > 0) 
	{
		//if (exp & 1)
		//	result = (result * base) % modulus;
		if (exp[63] & 1)
		{
			ChangeIntToStr(&result_str, result);
			ChangeIntToStr(&base_str, base);
			product(result_str, base_str, productValue);
			modulus(productValue, mod, result , true , divisionValue); //ba7ot al2egaba fe result wda mmkn ybawaz 7aga 3shan feeha value abl kda
			//modulus(productValue, mod, result_spare, true);
			//for (int i = 0; i < 64; i++)
			//{
			//	result[i] = result_spare[i];
			//}
		}

		//base = (base * base) % modulus;
		ChangeIntToStr(&base_str, base);
		product(base_str, base_str, productValue);
		modulus(productValue, mod, base, true , divisionValue);
		//modulus(productValue, mod, base_spare, true);
		//for (int i = 0; i < 64; i++)
		//{
		//	base[i] = base_spare[i];
		//}
		//exp >>= 1;
		ShiftRight(exp);
	}

	//cout << endl << "PowerSolution = ";
	//for (int i = 0; i < 64; i++)
	//{
	//	printf("%09d", result[i]);
	//}
	//cout << endl;
	return result;
}

int * Random_a(int * Max)
{
	time_t seconds;
	time(&seconds);
	srand((unsigned int)seconds);

	int* a = new int [64];
	Zeroing64IntArray(a);
	for (int i = 0; i < 64; i++)
	{
		if (Max[i] == 0)
		{

		}
		else
		{
			a[i] = rand() % Max[i] + 1;
		}

	}

//	cout << endl << "a from the function = ";
//	for (int i = 0; i < 64; i++)
//	{
//		printf("%09d", a[i]);
//	}

	return a;
}

bool MillerRabinTest(int * N)
{
	int K[64] = { 0 }, Q[64] = { 0 }, Power_solution[65] = { 0 }, j[64] = { 0 }, One[64] = { 0 }, K_Minus_1[65] = { 0 } ;
	int Two[65] = { 0 }, Product_solution[65] = { 0 }, Modulus_solution[65] = { 0 }, AdditionValue[64] = { 0 }, j_new[64] = {0};
	int divisionValue[64] = { 0 }; // not used here 
	int i = 0 , counter = 0;
	One[63] = 1, Two[63] = 2;
	int  Q1[64] = { 0 };
	int *rand_a = new int[64];
	string Two_str , Q_str;
	Zeroing64IntArray(rand_a);
	Get_K_and_Q_1(N, K, Q);  
	rand_a = Random_a(N);
	for (int i = 0; i < 64; i++)
	{
		Q1[i] = Q[i];
	}
	modpow(rand_a, Q, N, Power_solution); // ... it took 6.10 min 
//	modpow(Two, Q, N, Power_solution);     // ... it took 6.07 min .. alfar2 bt3 3-5 sec.
	while (i < 64)
	{
		if (Power_solution[i] == 0)
		{
			i++;
		}
		else
			break;
		if (i == 63)
		{
			if (Power_solution[63] == 1)
				return true;

		}
	}

	Subtraction(K, One, K_Minus_1);
	while (GreaterThan(K_Minus_1, j))
	{
		ShiftLeft_30(Two, counter);
		counter++;
		ChangeIntToStr(&Two_str, Two);
		ChangeIntToStr(&Q_str, Q1);  // ........ al Q hena be zero wda 3'alat 
		product(Two_str, Q_str, Product_solution);
		modulus(Product_solution, N, Modulus_solution, true, divisionValue);
		Addition(Modulus_solution, One, AdditionValue);
		i = 0;
		while (i < 64)
		{
			if (AdditionValue[i] == N[i])
			{
				i++;
			}
			else
				break;
			if (i == 63)
			{
				if (AdditionValue[63] == N[63])
					return true;
			}
		}

		Addition(j, One, j_new);
		for (int c = 0; c < 64; c++)
		{
			j[c] = j_new[c];
		}
	}



	return false;
}


// working well 
int * ExtendedEuclid(int * number, int * mod, int * inverse)
{
	// number hwa alrakam also3'ayar ... w mod hwa alrakam alkebeer aw almod alana bal3ab 7awaleh
	int* Number_inv = new int[64];
	int* zero = new int[64];
	int Q[64] = { 0 }, Sub_1[64] = { 0 }, Sub_2[64] = { 0 }, One[64] = { 0 };
	One[63] = 1;
	bool Neg_1 = false , Neg_2 = false , Neg_1_prev = false, Neg_2_prev = false , B1_Neg = false , B2_Neg = false, B3_Neg = false;
	int A_1[64] = { 0 }, A_2[64] = { 0 } , A_3[64] = { 0 };
	A_1[63] = 1;
	int B_1[64] = { 0 }, B_2[64] = { 0 }, B_3[64] = { 0 } , B_3_hold[65] = { 0 };
	B_2[63] = 1;
	int X_1[65] = { 0 }, X_2[65] = { 0 }; // for calculating B1 = A1-X.B1old & B2 = A2-X.B2old
	string B_1_str, B_2_str , Q_str;


	for (int i = 0; i < 64; i++)
	{
		A_3[i] = mod[i];
		B_3[i] = number[i];
		zero[i] = 0;
	}
	

	modulus(A_3, B_3, B_3_hold, false, Q);
	//for (int i = 0; i < 64; i++)
	//{
	//	A_3[i] = B_3[i];    // put B3 in A3
	//	A_1[i] = B_1[i];	// put B1 on A1
	//	A_2[i] = B_2[i];	// put B2 in A2
	//	B_3[i] = B_3_hold[i]; // put remainder of div in B3
	//}
	ChangeIntToStr(&B_1_str, B_1);
	ChangeIntToStr(&B_2_str, B_2);
	ChangeIntToStr(&Q_str, Q);
	product(B_1_str, Q_str, X_1);
	product(B_2_str, Q_str, X_2);
//if (GreaterThan(A_1, X_1))
	//{
	//	Subtraction_1(A_1, X_1, Sub_1, Neg_1);
	//}
	Subtraction_1(A_1, X_1, Sub_1, Neg_1);
	Subtraction_1(A_2, X_2, Sub_2, Neg_2);
//	Neg_1_prev = Neg_1;
//	Neg_2_prev = Neg_2;
	B1_Neg = Neg_1;
	B2_Neg = Neg_2;

	for (int i = 0; i < 64; i++) // updating value of B1 & B2
	{
		A_3[i] = B_3[i];    // put B3 in A3
		A_1[i] = B_1[i];	// put B1 on A1
		A_2[i] = B_2[i];	// put B2 in A2
		B_3[i] = B_3_hold[i]; // put remainder of div in B3
		B_1[i] = Sub_1[i];
		B_2[i] = Sub_2[i];
	}


	//while ( Greater_Than(B_3, One) == true )  // awl 7aga 2a2sem A3/B3 
	while ( ! EqualTo(B_3, One) )
	{
		modulus(A_3, B_3, B_3_hold, false, Q);
		//for (int i = 0; i < 64; i++)
		//{
		//	A_3[i] = B_3[i];    // put B3 in A3
		//	A_1[i] = B_1[i];	// put B1 on A1
		//	A_2[i] = B_2[i];	// put B2 in A2
		//	B_3[i] = B_3_hold[i]; // put remainder of div in B3
		//}
		ChangeIntToStr(&B_1_str, B_1);
		ChangeIntToStr(&B_2_str, B_2);
		ChangeIntToStr(&Q_str, Q);
		product(B_1_str, Q_str, X_1);
		product(B_2_str, Q_str, X_2);
		
		//Subtraction_1(A_1, X_1, Sub_1, Neg_1);
		//Subtraction_1(A_2, X_2, Sub_2, Neg_2);
		// a3mel b2a 4 cases lw alneg1 alhya gdeeda true altanya false wlw 
		// algdeeda false wl2adeema false .. wlw algdeeda false wladeema true
		//wlw algdeeda true wl2adeema true w nafs alklaam da 3la A1 w A2
		// w b3d my5alas y5ale al neg_2_prev hya hya al Neg_1 3shan alcase alb3daha

		if (Neg_1_prev == true && B1_Neg == true) 
		{
			Subtraction_1(X_1, A_1, Sub_1, Neg_1);
			Neg_1_prev = B1_Neg;
			B1_Neg = Neg_1;
		}

		else if ( Neg_1_prev == true && B1_Neg == false)
		{
			Addition(A_1, X_1, Sub_1);
			Neg_1_prev = B1_Neg;
			B1_Neg = true;
		}
		else if (Neg_1_prev == false && B1_Neg == true)
		{
			Addition(A_1, X_1, Sub_1);
			Neg_1_prev = B1_Neg;
			B1_Neg = false;
		}
		else // Neg_1_prev == false && Neg_1 == false
		{
			Subtraction_1(A_1, X_1, Sub_1, Neg_1);
			Neg_1_prev = B1_Neg;
			B1_Neg = Neg_1;
		}


		if (Neg_2_prev == true && B2_Neg == true) 
		{
			Subtraction_1(X_2, A_2, Sub_2, Neg_2);
			Neg_2_prev = B2_Neg;
			B2_Neg = Neg_2;
		}

		else if (Neg_2_prev == true && B2_Neg == false)
		{
			Addition(A_2, X_2, Sub_2);
			Neg_2_prev = B2_Neg;
			B2_Neg = true;
		}
		else if (Neg_2_prev == false && B2_Neg == true)
		{
			Addition(A_2, X_2, Sub_2);
			Neg_2_prev = B2_Neg;
			B2_Neg = false;
		}
		else // Neg_1_prev == false && Neg_1 == false
		{
			Subtraction_1(A_2, X_2, Sub_2, Neg_2);
			Neg_2_prev = B2_Neg;
			B2_Neg = Neg_2;
		}


		for (int i = 0; i < 64; i++) // updating value of B1 & B2
		{
			A_3[i] = B_3[i];    // put B3 in A3
			A_1[i] = B_1[i];	// put B1 on A1
			A_2[i] = B_2[i];	// put B2 in A2
			B_3[i] = B_3_hold[i]; // put remainder of div in B3
			B_1[i] = Sub_1[i];
			B_2[i] = Sub_2[i];
		}

	
	}

	// azon de al7etta bt3t alanswer tele3 negative wla la2 wla eh aw hya flarea hena me7tag 
	// tazbeet lesa bs naw3an mah sha3'al
	/*
	if (EqualTo(B_3 , One) == true )
	{
		ChangeIntToStr(&B_2_str, B_2);
		ChangeIntToStr(&Q_str, Q);
		product(B_2_str, Q_str, X_2);
		

		if (Neg_2_prev == true && B2_Neg == true) 
		{
			Subtraction_1(X_2, A_2, Sub_2, Neg_2);
			Neg_2_prev = B2_Neg;
			B2_Neg = Neg_2;
		}

		else if (Neg_2_prev == true && B2_Neg == false)
		{
			Addition(A_2, X_2, Sub_2);
			Neg_2_prev = B2_Neg;
			B2_Neg = true;
		}
		else if (Neg_2_prev == false && B2_Neg == true)
		{
			Addition(A_2, X_2, Sub_2);
			Neg_2_prev = B2_Neg;
			B2_Neg = false;
		}
		else // Neg_1_prev == false && Neg_1 == false
		{
			Subtraction_1(A_2, X_2, Sub_2, Neg_2);
			Neg_2_prev = B2_Neg;
			B2_Neg = Neg_2;
		}

		//for (int i = 0; i < 64; i++) // updating value of B1 & B2
		//{
		//	B_2[i] = Sub_2[i];
		//}
		
		if (B2_Neg == true )
		{
			Subtraction(mod, Sub_2, Number_inv);
			for (int i = 0; i < 64; i++)
			{
				inverse[i] = Number_inv[i];
			}
			return Number_inv;
		}

		else
		{
			for (int i = 0; i < 64; i++)
			{
				inverse[i] = Sub_2[i];
				Number_inv[i]; Sub_2[i];
			}
			return Number_inv;
		}
	}



	else // if = zero no inverse 
	{
		//for (int j = 0; j < 64; j++)
		//{
		//	inverse[j] = B_2[j];
		//	Number_inv[j] = inverse[j];
		//}
		//return Number_inv;
		return zero;
	}
	*/

	if (EqualTo(B_3, One) == true)
	{
		if (B2_Neg == true)
		{
			Subtraction(mod, Sub_2, Number_inv);
			for (int i = 0; i < 64; i++)
			{
				inverse[i] = Number_inv[i];
			}
			return Number_inv;
		}

		else
		{
			for (int i = 0; i < 64; i++)
			{
				//inverse[i] = Sub_2[i];
				//Number_inv[i]; Sub_2[i];
				inverse[i] = B_2[i];
				Number_inv[i] = B_2[i];
			}
			return Number_inv;
		}
		//for (int i = 0; i < 64; i++)
		//{
		//	inverse[i] = B_2[i];
		//	Number_inv[i] = B_2[i];
		//}
		//return Number_inv;
	}

	else
	{
		return zero;
	}
}





int main()
{
	/*
	string p,q,E ;
	//cin >> p;
	//cin >> q;
	//cin >> E;

  p = "12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871";
//	p = "1236957152874765579811018878656718075962691046572692055656729865937039974807236650723489943282747586518964271406783620730015303505947223727581638441007787155";
//	p = "12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871555555";
//  p = "12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871555555";
// p= "2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473";
//	p = "797897989795789877899577899811657018878656718075962691046572692055656729865937039974807236650723489943282747586518964271406783620730015303505947223727581638441007787155";
//	p = "1759";
//	p = "4321";
//	p = "4337";
//	p = "103";
//...... p = p * q
//  p = "25548364798832019218170326077010425733930233389897468141147917831084690989884562791601588954296621731652139141347541240725432606132471100644835778517336041031200174441223836394229943651678525471050219216183727749114047330431603023948126844573697946795476319956787513765533596926704755530772983549787878951983";
// ...... p = (p-1) * (q-1)
 //p = "25548364798832019218170326077010425733930233389897468141147917831084690989884562791601588954296621731652139141347541240725432606132471100644835778517336026596208292251573235229726077713862677978631329527089723369935343023713696135778845389268960161532146453542764411465765663060172221696312932049443439184640";
// q ="2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473";
 // q = "65537";
//	q = "91347";
//	q = "550";
//	q = "1234";
//	q = "83";
//	q = "2";

//	q = "31843000028789";
//	q = "206542035344199480305431507937063508786550842396217344781188004493631815881580277422040530495778746467677130903446356063371349747436222277568396002968947312456";
	E = "65537";
	int p_no[64] ;
	int q_no[64];
//	int E_no[128];	
	int E_no[64];
	int Addition_value[64];
	int subtraction_value[64];
	int modulus_value[64];
	int Multiplication_value[128];
	int k[64] = { 0 };
	int Q[64] = { 0 };
	int division_solutionnn[64] = { 0 };
	int * division_solution = new int[64];
	char * m = new char[MAX];
	const char * c = p.c_str();
	const char * c1 = p.c_str();
	Zeroing64IntArray(p_no);
	Zeroing64IntArray(q_no);
	Zeroing128IntArray(E_no);
//	Zeroing64IntArray(Addition_value);


	ChangeStrToInt(p, p_no,63);
	ChangeStrToInt(q, q_no,63);
	//ChangeStrToInt(E, E_no,127);
	ChangeStrToInt(E, E_no, 63);
	//........... for checking ONLYYY
	//for (int j = 0; j < 64 ; j++)
	//	{
	//		cout << "P number is " <<  p_no[j] << endl;
	//		cout << "Q number is " << q_no[j] << endl;
	//	}
	//cout << " E Number is ";
	//for (int j = 0; j < 128; j++)
	//	{
	//		cout << E_no[j] ;
	//		
	//	}
	//cout << endl;
	//Subtraction(p_no, q_no, subtraction_value);
	//ShiftLeft(p_no,31, q_no);
	//	powerModN(p_no, q_no, E_no);
//	Get_K_and_Q(p, q, k, Q);
	//cout << endl << " K = 2 ^ ";
	//for (int j = 0; j < 64; j++)
	//{
	//	printf("%09d", k[j]); 
	//}
	//cout << endl << "Q = ";
	//for (int j = 0; j < 64; j++)
	//{
	//	printf("%09d", Q[j]); 
	//}
	//division_solution =  DivisionSolution(p_no, q_no, division_solution,2);
	//for (int i = 0; i < 64; i++)
	//	printf("%09d", division_solution[i]);
	//cout << endl;
	//ShiftLeft_30(q_no , 112);
//	int * K_no = new int[64];
//	//int K_no[64] = { 0 };
//	int Q_no[64] = { 0 };
//	string N = "25548364798832019218170326077010425733930233389897468141147917831084690989884562791601588954296621731652139141347541240725432606132471100644835778517336041031200174441223836394229943651678525471050219216183727749114047330431603023948126844573697946795476319956787513765533596926704755530772983549787878951983";
//	N = "17";
//	ChangeStrToInt(N, E_no, 63);
	//Get_K_and_Q_1(E_no, K_no, Q_no);
	//for (int i = 0; i < 5; i++)
	//{
	//	Zeroing64IntArray(K_no);
	//	K_no = Random_a(p_no);
	//	cout << endl << "a from out of the fun = ";
	//	for (int i = 0; i < 64; i++)
	//	{
	//		printf("%09d", K_no[i]);
	//	}
	//	cout << endl;
	//}
	//cout << endl << "Q_no = ";
	//for (int i = 0; i < 64; i++)
	//{
	//	printf("%09d", Q_no[i]);
	//}
	//cout << endl;
	//m = multiply(c, c1);
	//product(p, p, Multiplication_value);
	//int count[64] = { 0 };
	//count[63] = 1;
	//powerModN(E_no, q_no, p_no,count);
	//int a[64] = { 0 }, b[64] = { 0 };
	//a[63] = 1;
	//b[63] = 2;
	//bool y = false;
	//y =	EqualTo(a, b);

//	divide(p_no, q_no, division_solutionnn, 2);
//	modulus(p_no, q_no, modulus_value, false, division_solutionnn);
	int number[64] = { 0 }, mod[64] = { 0 }, inverse[64] = { 0 };
	int * n = new int[64];
	number[63] = 550;
	mod[63] = 1759;
	//ExtendedEuclid(number, mod, inverse);
	//ExtendedEuclid(p_no, q_no, inverse);
/*	n = ExtendedEuclid(q_no, p_no, inverse);
	cout << endl << "Extended Euclid = ";
	for (int i = 0; i < 64; i++)
	{
		printf("%09d", n[i]);
	}

	

	//bool neg = false;
	//Subtraction_1(p_no, q_no, subtraction_value, neg);
	//Subtraction(q_no, p_no, subtraction_value);


	bool x = MillerRabinTest(p_no);
	if (x)
		cout << endl << "Miller Rabein Passed .... prime number";
	else
		cout << endl << "Miller Rabein not Passed .... not prime number";



	//bool neg = false;
	//Subtraction_1(q_no, p_no, subtraction_value, neg);
	//Subtraction(q_no, p_no, subtraction_value); 

	int * powersolution = new int[65];
	int answer[64] = { 0 };
//	powersolution = modpow(q_no, E_no, p_no, answer);
	powersolution = modpow(q_no, p_no, E_no, answer);
	cout << endl << "PowerSolution = ";
	for (int i = 0; i < 64; i++)
	{
		printf("%09d", powersolution[i]);
	}
	cout << endl;

	modulus(p_no, q_no, modulus_value , false , division_solutionnn);
	//	ShiftLeft(q_no, 1);
	//	ShiftRight(q_no); 	
	//Addition(p_no, q_no, Addition_value);
	//cout << "addition = ";
	//for (int j = 0; j < 64; j++)
	//{
	//	printf("%09d", Addition_value[j]); 
	//}
	//cout << endl;
	//cout << "Multiplication = ";
	//product(p, q);
	Subtraction(p_no, q_no, subtraction_value);
	*/

	string p, q, E, question, message;
	int N[64] = { 0 }, P_Minus_1[64] = { 0 }, Q_Minus_1[64] = { 0 }, Phi[64] = { 0 }, inverse[64] = { 0 }, Encr[64] = { 0 };
	int One[64] = { 0 }, Decr[64] = { 0 }, message_no[64] = { 0 }, Encr_priv[64] = {0}; One[63] = 1;
	int p_no[64] = { 0 }, q_no[64] = { 0 }, E_no[64] = { 0 };
	string P_Minus_1_str, Q_Minus_1_str;
	int * D = new int[64];
	int case_number = 0;
	//const char *question_char = new char[];

	bool flag = true;
	cin >> p; // there's somehting wrong in having inputs .. somehow they dont take p , q & e right
	cin >> q; // you should not put spaces in writning .. ex: p=103 
	cin >> E;
	cin >> message;
	//cin >> question;
	p = p.substr(p.find("=") + 1, p.length());
	q = q.substr(q.find("=") + 1, q.length());
	E = E.substr(E.find("=") + 1, E.length());
	message = message.substr(message.find("=") + 1, message.length());

	product(p, q, N);
	ChangeStrToInt(p, p_no, 63);
	ChangeStrToInt(q, q_no, 63);
	ChangeStrToInt(E, E_no, 63);
	ChangeStrToInt(message, message_no, 63);

	Subtraction(p_no, One, P_Minus_1);
	Subtraction(q_no, One, Q_Minus_1);
	ChangeIntToStr(&P_Minus_1_str, P_Minus_1);
	ChangeIntToStr(&Q_Minus_1_str, Q_Minus_1);
	product(P_Minus_1_str, Q_Minus_1_str, Phi);

	while (flag)
	{
		
		cin >> question;
		if (question == "IsPPrime")
			case_number = 1;
		else if (question == "IsQPrime" )
			case_number = 2;
		else if (question == "PrintN")
			case_number = 3;
		else if (question == "PrintPhi")
			case_number = 4;
		else if (question == "Quit")
			case_number = 5;
		else if (question == "PrintD")
			case_number = 6;
		else if (question == "EncryptPublic")
			case_number = 7;
		else if (question == "EncryptPrivate")
			case_number = 8;
		else if (question == "Decryptmsg")
			case_number = 9;

		switch (case_number)
		{

		case 1:
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			bool x = MillerRabinTest(p_no);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
			if (x)
				cout << endl << "Yes" << endl;
			else
				cout << endl << "No" << endl;

			cout << "time:" << time_span.count() << "sec" << endl;
			break;
		}

		case 2:
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			bool y = MillerRabinTest(q_no);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

			if (y)
				cout << endl << "Yes" << endl;
			else
				cout << endl << "No" << endl;
			cout << "time:" << time_span.count() << "sec" << endl;
			break;

		}
		case 3:
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			product(p, q, N);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
			
			for (int i = 0; i < 64; i++)
			{
				printf("%09d", N[i]);
			}
			cout << endl;
			cout << "time:" << time_span.count() << "sec" << endl;
			break;
		}
		 
		case 4:
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			product(P_Minus_1_str, Q_Minus_1_str, Phi);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

			for (int i = 0; i < 64; i++)
			{
				printf("%09d", Phi[i]);
			}
			cout << endl;
			cout << "time:" << time_span.count() << "sec" << endl;
			break;
		}

		case 5:
		{
			flag = false;
			break;
		}

		case 6:
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			D = ExtendedEuclid(E_no, Phi, inverse);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

			for (int i = 0; i < 64; i++)
			{
			printf("%09d", D[i]);
			}
			cout << endl;
			cout << "time:" << time_span.count() << "sec" << endl;
			break;
		}

		case 7:
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			modpow(message_no, E_no, N, Encr);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

			
			for (int i = 0; i < 64; i++)
			{
				printf("%09d", Encr[i]);
			}
			cout << endl;
			cout << "time:" << time_span.count() << "sec" << endl;
			break;
		}

		case 8:
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			modpow(message_no, D, N, Encr_priv);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

			
			for (int i = 0; i < 64; i++)
			{
				printf("%09d", Encr_priv[i]);
			}
			cout << endl;
			cout << "time:" << time_span.count() << "sec" << endl;
			break;
		}

		case 9:
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			modpow(Encr, D, N, Decr);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

			for (int i = 0; i < 64; i++)
			{
				printf("%09d", Decr[i]);
			}
			cout << endl;
			cout << "time:" << time_span.count() << "sec" << endl;
			break;
		}
	}

}


}


/*
p=12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871
q=2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473
E=65537
message=88
*/
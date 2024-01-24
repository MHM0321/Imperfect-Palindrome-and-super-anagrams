#include<iostream>
#include<fstream>
using namespace std;
void lengths(char a[], int n, int& x, int& y); //gets the lengths of the words separately for use in functions
bool imPerfectPalindromeFirst(char a[], int n, int& x); //finds if 1st word is an imperfect palindrome or not
bool imPerfectPalindromeSecond(char a[], int n, int& x, int& y); //finds if 2nd word is an imperfect palindrome or not
bool possibleSuperAnagram(char a[], int n, int& x, int& y); //checks if both words have the same letters (irrespective of frequency)
bool superAnagram(char a[], int n, int& x, int& y); //after possibility getting checked, it confirms by taking frequecy of letters

int main()
{
	const int size = 41; //fixed size as each word max 20 letters, and +1 for space
	int l1 = 0, l2 = 0; //length of the words, they are passed by reference so they change later
	char check[size] = { '\0' }; //initialized to prevent garbage values

	ifstream input("Input.txt");

	if (!input)
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	while (input.getline(check, size)) //gets the required words pair
	{
		lengths(check, size, l1, l2); //gets length of the words
		imPerfectPalindromeFirst(check, size, l1); //checks
		if (imPerfectPalindromeFirst(check, size, l1) == true)
		{
			cout << "yes ";
		}
		else
		{
			cout << "no ";
		}
		imPerfectPalindromeSecond(check, size, l1, l2); //checks
		if (imPerfectPalindromeSecond(check, size, l1, l2) == true)
		{
			cout << " yes ";
		}
		else
		{
			cout << " no ";
		}
		if (possibleSuperAnagram(check, 30, l1, l2) == true)//checks
		{
			superAnagram(check, 30, l1, l2);//checks
			if (superAnagram(check, 30, l1, l2) == true)
			{
				cout << " yes " << endl;
			}
			else
			{
				cout << " no " << endl;
			}
		}
		else
		{
			cout << " no " << endl;
		}
	}
	system("pause");
	return 0;
}

bool imPerfectPalindromeFirst(char a[], int n, int& x)
{
	int count = 0;
	for (int i = 0, j = x - 1; i < x, j >= 0; i++, j--)
	{//index i will start from first letter to last letter of first word
	 //and j will start from last letter to first letter of first word 
		if (a[i] == a[j])
		{
			count++; //if the opposite words are same, it will increase
		}
	}
	if (count == x - 2 || count == x - 1) //as imperfect can have max difference of two words
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool imPerfectPalindromeSecond(char a[], int n, int& x, int& y)
{
	int count = 0;
	for (int i = x + 1, j = x + y; i <= x + y, j >= x + 1; i++, j--)
	{/*It is done by using length of first word and adding one to
	it to skip to the index of letter next to space i.e first letter
	of second word, similarly when both lengths are added (and
	space is ignored) we get last index i.e last letter of first
	word*/
	//Thus, i will start from first letter to last letter of first word
	//and j will start from last letter to first letter of first word 
		if (a[i] == a[j])
		{
			count++; //increases if opposite letters are same
		}
	}
	if (count == y - 2 || count == y - 1) //as imperfect can have difference of max two
	{
		return true;
	}
	else
	{
		return false;
	}
}

void lengths(char a[], int n, int& x, int& y)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] != ' ' && a[i] != '\0') //first for before space
		{								//then count is skipped for space and restted, and it continues until words exist
			count++;
		}
		else if (a[i] == ' ' && a[i] != '\0')
		{
			x = count; //it will get length of word before space
			count = 0; //resetted for the next word
		}
		else if (a[i] == '\0')
		{
			i = n; //used instead of break
		}
	}
	y = count; //it will get length of word after space
}

bool possibleSuperAnagram(char a[], int n, int& x, int& y)
{
	bool cond1 = false, cond2 = false;
	int count = 0;
	for (int i = 0; i < x; i++) //checks if all first word letters are
	{							//present in the second word
		for (int j = x + 1; j <= x + y; j++)
		{
			if (a[i] == a[j])
			{
				count++; //increases if the letter is present in the
			}			 //second word, otherwise remains same
		}
		if (count == 0) //if any letter is not present in second word,
		{				//it cannot be a super anagram
			return false;
		}
		else
		{
			count = 0; //reset
		}
	}
	cond1 = true;
	for (int k = x + 1; k <= x + y; k++) //checks if all second word letters
	{								 //are present in the first word
		for (int l = 0; l < x; l++)
		{
			if (a[k] == a[l])
			{
				count++; //increases if the letter is present in the
			}			 //second word, otherwise remains same
		}
		if (count == 0) //if any letter is not present in first word,
		{				//it cannot be a super anagram
			return false;
		}
		else
		{
			count = 0;
		}
	}
	cond2 = true;
	if (cond1 == true && cond2 == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool superAnagram(char a[], int n, int& x, int& y)
{
	int count = 0, diff = 0;
	char repititionCheck[41] = { '\0' }; //made to keep the once compared characters of the
	//respective array, so repetiton may not take place
	if (y >= x) //if the length of both the arrays is same or if 2nd word is longer than first word
	{
		for (int i = 0; i < x; i++) //first word
		{
			for (int j = x + 1; j < x + y; j++) //second word
			{
				for (int k = 0; k < x; k++) //for preventing repetition of comparison for first word's character's comparison
				{
					if (a[i] != repititionCheck[k]) //checks if the word has appeared before to prevent repitition
					{
						if (a[i] == a[j]) //finds frequency of first words' characters in the second word
						{
							count++;
						}
					}
					else if (a[i] == repititionCheck[k]) //ignores the repeated word
					{
						k = x; //used instead of break
					}
				}
				repititionCheck[i] = a[i]; //stores the compared characters to avoid repitition
			}
		}
		diff = y - count; //finds the difference between the characters of first word found in
		//the second word (no repitition) and all the letters of second word
		//Basically it gives the accumulated frequency difference
		if (diff <= 2) //as max 2 differnce is allowed
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (x > y) //if first word is longer than second word
	{
		for (int i = x + 1; i < x + y; i++) //second word
		{
			for (int j = 0; j < x; j++) //first word
			{
				for (int k = x + 1; k < x + y; k++) //for preventing repetition of comparison for second word's character's comparison
				{
					if (a[i] != repititionCheck[k]) //checks if the word has appeared before to prevent repitition
					{
						if (a[i] == a[j]) //finds frequency of second words' characters in the first word
						{
							count++;
						}
					}
					else if (a[i] == repititionCheck[k]) //ignores the repeated word
					{
						k = x + y; //used instead of break
					}
				}
				repititionCheck[i] = a[i]; //stores the compared characters to avoid repitition 
			}
		}
		diff = x - count; //finds the difference between the characters of first word found in
		//the second word (no repitition) and all the letters of second word
		//Basically it gives the accumulated frequency difference
		if (diff <= 2) //as max 2 differnce is allowed
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
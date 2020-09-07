// unothestring.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <math.h>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define BP (cout<<endl)

#define DOCK() do{                       \
                                  int dock;     \
                                  cin>>dock;    \
}while(0)

template<typename T>
void printContainer(vector<T> &container)
{
	for (auto it = container.begin(); it != container.end(); ++it)
	{
		cout << *it;
		if (it != container.end() - 1)
			cout << ", ";
	}
}

class Solution
{
public:
	// 125. Valid Palindrome
	bool isPalindrome(string s)
	{
		for (int i = 0, j = s.length() - 1; i < j; i++, j--)
		{
			if (isalnum(s[i]) && isalnum(s[j]))
			{
				if (toupper(s[i]) != toupper(s[j]))
					return false;
			}
			else
			{
				if (!isalnum(s[i]))
					j++;
				else
					i--;
			}
		}

		return true;
	}

	// 3. Longest Substring Without Repeating Characters
	// int lengthOfLongestSubstring(string s)
	// {
	// 	if(s.empty())
	// 		return 0;

	// 	int len = s.length();
	// 	int substrLen = 0, maxSubstrLen = 0;
	// 	int subStrNum = 1;

	// 	unordered_map<char, int> charNum;
	// 	unordered_map<char, int> charIdx;
	// 	char c;

	// 	for(int i = 0; i < len; i++)
	// 	{
	// 		c = s[i];

	// 		if(charNum[c] == subStrNum)
	// 		{
	// 			maxSubstrLen = max(substrLen, maxSubstrLen);
	// 			substrLen = 0;
	// 			subStrNum++;
	// 			for(int j = charIdx[c]+1; j < i; j++)
	// 			{
	// 				charNum[s[j]] = subStrNum;
	// 				substrLen++;
	// 			}
	// 		}
			
	// 		charNum[c] = subStrNum;
	// 		charIdx[c] = i;
	// 		substrLen++;
	// 	}

	// 	return max(substrLen, maxSubstrLen);
    // }

	int lengthOfLongestSubstring(string s)
	{
		if(s.empty())
			return 0;

		int len = s.length();
		int substrLen =0, maxSubstrLen = 0;
		vector<int> charIdx(128, -1);
		char c;
		int endIdx = -1;

		for(int i = 0; i < len; i++)
		{
			c = s[i];

			if(-1 != charIdx[c] && charIdx[c] > endIdx)
			{
				maxSubstrLen = max(substrLen, maxSubstrLen);
				substrLen = i - charIdx[c] - 1;
				endIdx = charIdx[c];
			}

			charIdx[c] = i;
			substrLen++;
		}

		return max(substrLen, maxSubstrLen);
	}

	// 22. Generate Parentheses (backtracking)
	void gps(vector<string> &pss, string ps, int left_ps, int right_ps)
	{
		if (!left_ps && !right_ps)
		{
			pss.push_back(ps);
			return;
		}

		if (left_ps > 0)
			gps(pss, ps + "(", left_ps - 1, right_ps);

		if (right_ps > left_ps)
			gps(pss, ps + ")", left_ps, right_ps - 1);
	}

	vector<string> generateParenthesis(int n)
	{
		vector<string> parentheses;

		gps(parentheses, "", n, n);

		return parentheses;
    }
};



int main()
{
	Solution solu;

	// 125. Valid Palindrome
	// string s = "A man, a plan, a canal: Panama";
	// cout << "String: " << s << endl;
	// cout << "Is palindrome: " << (solu.isPalindrome(s) ? "true" : "false") << endl << endl;
	// string s = "abcabcbb";
	// s = " ";
	// s = "bbbbb";
	// s = "pwwkew";
	// cout << "String: " << s << endl;
	// cout << "Length of longest substring: " << solu.lengthOfLongestSubstring(s) << endl << endl;

	// 22. Generate Parentheses (backtracking)
	while (1)
	{
		int n = -1;
		while (n <= 0)
		{
			cout << "Number of pairs of parentheses: ";
			cin >> n;
		} 
		vector<string> parentheses = solu.generateParenthesis(n);
		cout << "Number of combinations of well-formed parentheses: " << parentheses.size() << endl;
		printContainer(parentheses);
		cout << endl << endl;
	}

	DOCK();

    return 0;
}


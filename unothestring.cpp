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

	// 28. Implement strStr()
	// int strStr(string haystack, string needle)
	// {
    //     if (needle.empty())
	// 		return 0;

	// 	for (int i = 0; i < haystack.length(); ++i)
	// 	{
	// 		if (haystack[i] == needle[0])
	// 		{
	// 			int j = i + 1;
	// 			int k = 1;
	// 			for (; j < haystack.length() && k < needle.length() && haystack[j] == needle[k]; ++j, ++k);
	// 			if (k == needle.length())
	// 				return i;
	// 		}
	// 	}

	// 	return -1;
    // }

	vector<int> pt;
	void createPrefixTable(string &needle)
	{
		pt.clear();
		pt.push_back(-1);
		int num_comm = 0;

		for (int i = 1; i < needle.length(); i++)
		{
			pt.push_back(num_comm);
			if (needle[i] == needle[num_comm])
				num_comm++;
			else
			{
				while (num_comm)
				{
					num_comm = pt[num_comm];
					if (needle[i] == needle[num_comm])
					{
						num_comm++;
						break;
					}
				}
			}
		}
	}

	int KMP(string &s, string &ss)
	{
		int i = 0;
		int j = 0;

		while (i < s.length() && s.length() - i >= ss.length() - j)
		{
			if (s[i] == ss[j])
			{
				++i;
				++j;
				if (j == ss.length())
					return i - j;
			}
			else
			{
				j = pt[j];
				if (j == -1)
				{
					++i;
					++j;
				}
			}
		}

		return -1;
	}

	int strStr(string haystack, string needle)
	{
		if (needle.empty())
			return 0;

		if (needle.length() > haystack.length())
			return -1;

		createPrefixTable(needle);

		return KMP(haystack, needle);
	}

	// 15. 3Sum
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		vector<vector<int>> triplets;
		int n = nums.size();

		if (!n)
			return triplets;

		sort(nums.begin(), nums.end());

		for (int i = 0; i < n - 2; i++)
		{
			if (i != 0 && nums[i] == nums[i-1])
				continue;

			int target = -nums[i];
			int l = i + 1;
			int h = n - 1;

			while(l < h)
			{
				int sum = nums[l] + nums[h];

				if (sum == target)
				{
					triplets.push_back({nums[i], nums[l], nums[h]});
					while(l < h && nums[++l] == nums[l-1]);
					while(l < h && nums[--h] == nums[h+1]);
				}
				else if (sum < target)
					while(l < h && nums[++l] == nums[l-1]);
				else
					while(l < h && nums[--h] == nums[h+1]);
			}
		}
	
		return triplets;
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
	// while (1)
	// {
	// 	int n = -1;
	// 	while (n <= 0)
	// 	{
	// 		cout << "Number of pairs of parentheses: ";
	// 		cin >> n;
	// 	} 
	// 	vector<string> parentheses = solu.generateParenthesis(n);
	// 	cout << "Number of combinations of well-formed parentheses: "
	// 		<< parentheses.size() << endl;
	// 	printContainer(parentheses);
	// 	cout << endl << endl;
	// }

	// 28. Implement strStr()
	while (1)
	{
		string haystack;
		string needle;

		cout << "haystack: ";
		cin >> haystack;
		cout << "needle: ";
		cin >> needle;

		cout << "The index of first occurrence of needle in haystack: "
			<< solu.strStr(haystack, needle) << endl << endl;
	}

	// 15. 3Sum
	// vector<int> nums = {-1,0,1,2,-1,-4};
	// cout << "nums: ";
	// printContainer(nums);
	// cout << endl;
	// vector<vector<int>> triplets = solu.threeSum(nums);
	// cout << "triplets:" << endl;
	// for (auto triplet : triplets)
	// {
	// 	printContainer(triplet);
	// 	cout << endl; 
	// }

	DOCK();

    return 0;
}


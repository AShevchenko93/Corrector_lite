#pragma once
#ifdef CORRECTORDLL_EXPORTS
#define CORRECTORDLL_API __declspec(dllexport) 
#else
#define CORRECTORDLL_API __declspec(dllimport) 
//#pragma comment(lib, "Corrector.lib")
#endif
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <algorithm>

using namespace std;
struct suggest
{
	wchar_t *word;
	size_t length=0;
};

struct answer
{
	int weght = 0;
	int pos;
};

bool operator <(const answer &a, const answer &b)
{
	return a.weght > b.weght;
}

class CORRECTORDLL_API Corrector_lite
{
public:
	Corrector_lite();
	void open(const char *);
	void Create_dictionary();
	vector<suggest> Find(const wchar_t *,int);
	void Sort_answer(vector<answer>);
	~Corrector_lite();
private:
	vector<wchar_t> text;
	vector<suggest> dictionary;
	int number_find_word;
};
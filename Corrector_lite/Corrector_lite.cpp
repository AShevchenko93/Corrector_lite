#include "Corrector_lite.h"




Corrector_lite::Corrector_lite()
{
	number_find_word = 10;
}

void Corrector_lite::open(const char *file_name)
{
	FILE *file = fopen(file_name, "rb");
	if (file == NULL)
	{
		fputs("Ошибка файла", stderr);
		exit(1);
	}
	fseek(file, 0, SEEK_END);
	long lSize = ftell(file);
	rewind(file);
	text.resize(lSize / 2);
	if (text.data() == NULL)
	{
		fputs("Ошибка памяти", stderr);
		exit(2);
	}
	size_t result = fread(text.data(), 1, lSize, file);
	if (result != lSize)
	{
		fputs("Ошибка чтения", stderr);
		exit(3);
	}
	fclose(file);
}

void Corrector_lite::Create_dictionary()
{
	
	bool first_symbol = true;
	int size=0;
	for (int i = 1; i < text.size(); i++)
	{
		if (!iswcntrl(text[i]))
		{
			if (first_symbol)
			{
				size++;
				dictionary.resize(size);
				dictionary[size - 1].word = &text[i];
				dictionary[size - 1].length++;
				first_symbol = false;
			}
			else
			{
				dictionary[size - 1].length++;
			}
		}
		else
			first_symbol = true;
	}
}


vector<suggest> Corrector_lite::Find(const wchar_t *word,int length_word)
{
	vector<suggest> find_word;
	vector<answer> position;
	int n = dictionary.size();
	vector<int> pos;
	for (int i = 0; i < n; i++)
	{
		int k = dictionary[i].length;
		if ((k - 2) < length_word && (k + 2) > length_word)
		{
			bool flag = false;
			int temporary_weight = 0;
			for (int j = 0; j < length_word && j < k; j++)
			{
				wchar_t *test_word = dictionary[i].word;
				if ((*(test_word + j)) == word[j])//тут +1 к индексу text если считывалось с файла
				{
					temporary_weight++;
					flag = true;
				}
			}
			if (flag)
			{
				answer qw;
				qw.pos = i;
				qw.weght = temporary_weight;
				position.push_back(qw);
			}
		}
	}
	if (position.size() > 0)
	{
		sort(position.begin(), position.end());
		if (number_find_word < position.size())
			position.resize(number_find_word);
		find_word.clear();
		for (int i = 0; i < position.size(); i++)
		{
			float chance;
			chance = (float)position[i].weght / (float)dictionary[position[i].pos].length;
			if (chance > 0.6)
			{
				find_word.push_back(dictionary[position[i].pos]);
			}
		}
		position.clear();
	}
	return find_word;
}


void Corrector_lite::Sort_answer(vector<answer> position)
{
	sort(position.begin(), position.end());
	if(number_find_word < position.size())
		position.resize(number_find_word);
}


Corrector_lite::~Corrector_lite()
{
}

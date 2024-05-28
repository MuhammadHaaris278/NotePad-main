#include<iostream>
#include<string>
#include<fstream>
#include <conio.h>
using namespace std;

bool Word_Check_in_Search = false;
int Letters_Count[26] = { 0 };
int arr_of_paths[500] = { 0 };
int arr_of_paths_2[500] = { 0 };
int countt1 = 0;
int idxx = 0;
string total = "";
int globali = 0;
string user_input = "";
string data4 = "";
fstream filing;
int count_for_arr_paths_centinal = 0;


class TrieNode
{
public:
	char data;
	TrieNode* Children[26];
	bool isFound = false;

	TrieNode(char data1)
	{
		data = data1;
		for (int i = 0; i < 26; i++)
		{
			Children[i] = NULL;
		}
		isFound = false;
	}
};

class Trie
{
public:
	TrieNode* root;

	Trie()        // constructor.
	{
		root = new TrieNode('/0');
	}

	void InsertWord(TrieNode* root, string word)
	{
		//base case.
		if (word.length() == 0)
		{
			root->isFound = true;
			return;
		}

		int index = word[0] - 'a';           // to find respective index.
		TrieNode* child;

		if (root->Children[index] != NULL)
		{
			// if present.
			child = root->Children[index];
		}
		else
		{
			//if not present.
			child = new TrieNode(word[0]);
			root->Children[index] = child;
		}

		//recursion
		InsertWord(child, word.substr(1));
	}

	bool SearchWord(TrieNode* root, string word)
	{
		if (word.length() == 0)
		{
			//base case.
			Word_Check_in_Search = root->isFound;           // to resolve the 24 issue.
			return root->isFound;
		}

		int index = word[0] - 'a';           // to find respective index.
		TrieNode* child;

		if (root->Children[index] != NULL)
		{
			// if present.
			child = root->Children[index];
		}
		else
		{
			//if not present.
			return false;
		}
		//recursion
		SearchWord(child, word.substr(1));
	}

	void suggestionsRec(struct TrieNode* root, string currPrefix, string arr[])
	{
		// found a string in Trie with the given prefix
		if (root->isFound)
		{
			if (globali < 20)
			{
				arr[globali] = currPrefix;
				globali++;
			}
		}

		for (int i = 0; i < 26; i++)
		{
			if (root->Children[i])
			{
				// child node character value
				char child = 'a' + i;
				suggestionsRec(root->Children[i], currPrefix + child, arr);
			}
		}
	}

	void printAutoSuggestions(TrieNode* root, const string query)
	{
		char ch = 65;
		string poss_char[20], s;
		int i = 0;
		for (int i = 0;i < 20;i++) 
		{
			poss_char[i] = ch;
			ch++;
		}
		globali = 0;
		suggestionsRec(root, query, poss_char);
		keys(poss_char, query);
	}
	
	TrieNode* rett()
	{
		return root;
	}

	void keys(string poss_char[], string q)
	{
		system("CLS");
		char ch = 'a';
		int selection = 0;

		while (ch != 'o')
		{
			cout << total << endl;
			for (int i = 0;i < 20;i++)
			{
				if (selection == i)
				{
					cout << "-> ";
					cout << poss_char[i] << endl;
				}
				else
				{
					cout << "   " << poss_char[i] << endl;
				}

			}

			ch = _getch();
			if (ch == 'w') 
			{
				selection--;
			}
			else if (ch == 's') 
			{
				selection++;
			}
			system("CLS");
		}

		data4 = data4 + " " + poss_char[selection];
		int i = total.length() - 2;
		total.erase(total.size() - 1, 1);
		while (total[i] != ' ')
		{
			total.erase(total.size() - 1, 1);
			i--;
		}
		total += poss_char[selection] + " ";
		cout << total;
	}
};

class Huffman
{
public:

	struct MinHeapNode
	{
		char data;
		unsigned freq;
		struct MinHeapNode* left, * right;
	};

	struct MinHeapNode* Final_root = NULL;
	struct MinHeapNode* Final_root_2 = NULL;


	struct MinHeap
	{
		unsigned size;
		unsigned capacity;
		struct MinHeapNode** array;
	};

	struct MinHeapNode* newNode(char data, unsigned freq)
	{
		struct MinHeapNode* temp = new MinHeapNode();
		temp->left = temp->right = NULL;
		temp->data = data;
		temp->freq = freq;
		return temp;
	}

	struct MinHeap* createMinHeap(unsigned capacity)
	{
		struct MinHeap* minHeap = new MinHeap();

		minHeap->size = 0;

		minHeap->capacity = capacity;

		minHeap->array = new MinHeapNode * [minHeap->capacity];

		return minHeap;
	}

	void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
	{
		struct MinHeapNode* t = *a;
		*a = *b;
		*b = t;
	}

	void minHeapify(struct MinHeap* minHeap, int idx)
	{
		int smallest = idx;
		int left = 2 * idx + 1;
		int right = 2 * idx + 2;

		if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
		{
			smallest = left;
		}

		if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		{
			smallest = right;
		}

		if (smallest != idx)
		{
			swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
			minHeapify(minHeap, smallest);
		}
	}

	int isSizeOne(struct MinHeap* minHeap)
	{
		return (minHeap->size == 1);
	}

	struct MinHeapNode* extractMin(struct MinHeap* minHeap)
	{
		struct MinHeapNode* temp = minHeap->array[0];

		minHeap->array[0] = minHeap->array[minHeap->size - 1];

		--minHeap->size;

		minHeapify(minHeap, 0);

		return temp;
	}

	void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
	{
		++minHeap->size;
		int i = minHeap->size - 1;

		while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
		{
			minHeap->array[i] = minHeap->array[(i - 1) / 2];
			i = (i - 1) / 2;
		}

		minHeap->array[i] = minHeapNode;
	}

	bool isLeaf(struct MinHeapNode* root)
	{
		return !(root->left) && !(root->right);
	}

	void buildMinHeap(struct MinHeap* minHeap)
	{
		int n = minHeap->size - 1;
		int i;
		for (i = (n - 1) / 2; i >= 0; --i)
		{
			minHeapify(minHeap, i);
		}
	}

	struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
	{
		struct MinHeap* minHeap = createMinHeap(size);

		for (int i = 0; i < size; ++i)
		{
			minHeap->array[i] = newNode(data[i], freq[i]);
		}
		minHeap->size = size;
		buildMinHeap(minHeap);

		return minHeap;
	}

	void printArr(int arr[], int n)
	{
		for (int i = 0; i < n; ++i)
		{
			count_for_arr_paths_centinal++;
			//cout << arr[i];
			filing << arr[i];
		}
		filing << endl;
		cout << "\n\n";
	}

	struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
	{
		struct MinHeapNode* left, * right, * top;
		struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

		while (!isSizeOne(minHeap)) 
		{
			left = extractMin(minHeap);

			right = extractMin(minHeap);
			top = newNode('$', left->freq + right->freq);

			top->left = left;
			top->right = right;

			insertMinHeap(minHeap, top);
		}

		return extractMin(minHeap);
	}

	void printCodes(struct MinHeapNode* root, int arr[], int top)
	{
		if (root->left)
		{
			arr[top] = 0;
			printCodes(root->left, arr, top + 1);
		}

		if (root->right)
		{

			arr[top] = 1;
			printCodes(root->right, arr, top + 1);
		}

		if (isLeaf(root))
		{
			//cout << root->data << " : ";
			filing << root->data << endl;
			printArr(arr, top);
		}
	}

	void encoding()
	{
		fstream filing_1;
		fstream filind_2;
		char data_read;
		string data_read_2;
		filing_1.open("encoding.txt", ios::out);

		for (int i = 0; i < user_input.length(); i++)
		{
			filind_2.open("encodingtemp.txt", ios::in);

			while (!filind_2.eof())
			{
				filind_2 >> data_read;

				if (filind_2.eof())
				{
					break;
				}
				if (user_input[i] == data_read)
				{
					filind_2 >> data_read_2;
					filing_1 << data_read_2;
				}
			}
			filind_2.close();
		}
		filing_1.close();
	}

	void decoding(struct MinHeapNode* root)
	{
		fstream filingg;
		filingg.open("encoding.txt", ios::in);
		char read_encode;
		bool check_leaf = false;
		bool chk = true;


		while (!filingg.eof())
		{
			if (chk == 1)
			{
				filingg >> read_encode;
			}

			check_leaf = isLeaf(root);

			if (check_leaf != 1)
			{
				if (read_encode == '0')
				{
					root = root->left;
					chk = true;
				}
				else
				{
					if (read_encode == '1')
					{
						root = root->right;
						chk = true;
					}
				}
			}

			if (check_leaf == 1)
			{
				cout << root->data;
				root = Final_root_2;
				chk = false;
			}
		}

		filingg.close();

	}

	void HuffmanCodes(char data[], int freq[], int size)
	{
	    Final_root = buildHuffmanTree(data, freq, size);

		Final_root_2 = Final_root;

		int top = 0;

		filing.open("encodingtemp.txt", ios::out);

		printCodes(Final_root, arr_of_paths, top);

		arr_of_paths_2[count_for_arr_paths_centinal] = -1;

		filing.close();

		encoding();

		decoding(Final_root_2);

	}
};


int main()
{
	Trie* obj = new Trie();
	string reading = "";
	char read_Char;
	double count = 0;
	char key = ' ', character_input = '/0';
	string word = "";
	int index = 0, size_for_char_array = 0;

	filing.open("dictionary.txt", ios::in);

	while (!filing.eof())
	{
		filing >> reading;
		obj->InsertWord(obj->root, reading);
	}

	filing.close();

	cout << "\n   Enter Text : " << endl;

	while (character_input != '=')
	{
		character_input = _getch();

		if (character_input != '.' && character_input != '=')
			total += character_input;

		if (character_input == '.')
			total += ' ';

		if (character_input != '.')
			word += character_input;

		system("CLS");

		cout << total;

		if (character_input != '=' && character_input == '.')
		{

			obj->printAutoSuggestions(obj->rett(), word);
			word = "";
		}

		if (character_input == ' ')
		{
			word = "";
		}
	}
	user_input = total;

	for (int i = 0; i < user_input.length(); i++)
	{
		read_Char = user_input[i];
		index = read_Char - 97;

		for (int j = 0; j < user_input.length(); j++)
		{
			if (read_Char == user_input[j])
			{
				count++;
			}
		}

		Letters_Count[index] = count;
		count = 0;
	}

	for (int i = 0; i < 26; i++)
	{
		if (Letters_Count[i] != 0)
		{
			size_for_char_array++;
		}
	}

	char* arr_of_char = new char[size_for_char_array];
	int* arr_of_freq = new int[size_for_char_array];

	int j = 0;

	for (int i = 0; i < 26; i++)
	{
		if (Letters_Count[i] != 0)
		{
			arr_of_char[j] = 97 + i;       // to get that element( char ).
			j++;
		}
	}

	j = 0;

	for (int i = 0; i < 26; i++)
	{
		if (Letters_Count[i] != 0)
		{
			arr_of_freq[j] = Letters_Count[i];
			j++;
		}
	}

	Huffman obj1;

	cout << "\n\t   Decoded Input : \n" << endl;

	obj1.HuffmanCodes(arr_of_char, arr_of_freq, size_for_char_array);

	cout << "\n\n";
	system("pause");
	return 0;
}
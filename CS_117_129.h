#pragma once
#include <iostream>
#include<fstream>
#include<vector>
#include<Windows.h>
#include<string>
using namespace std;

void gotoxy(int x, int y)
{
	COORD coordinates;
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

template <typename T>
class Excell_cells
{
private:

	class cell {
	public:
		T data;
		cell* previous;
		cell* next;
		cell* up;
		cell* down;

		cell(T data)
		{
			this->data = data;
			this->up = nullptr;
			this->down = nullptr;
			this->next = nullptr;
			this->previous = nullptr;


		}

	};


		cell* head;
		cell* temp;
		size_t rows;
		size_t columns;
		string index;



public:
	cell* currentCell;

	class Iterator {

	public:
		cell* temp;
		Iterator(cell* temp)
		{
			this->temp = temp;
		}

		bool operator != (cell* check)
		{
			return check != temp;
		}
		void operator ++ () {
			temp = temp->next;
		}
		void operator -- () {
			temp = temp->previous;
		}
		void operator -- (int) {
			temp = temp->up;
		}
		void operator ++ (int) {
			temp = temp->down;
		}

	};



		

	Excell_cells(char option)
	{
		if (option == 'Y' || option == 'y') {
			LoadData();
			return;
		}
		cell * nc = new cell(1);
		currentCell = temp = head = nc;
		rows = columns = 5;
		index = "1,1";
		for (int i = 1;i <= rows;i++) 
		{
			for (int j = 1;j < columns;j++) 
			{
				InsertRight(j + 1);
				temp = temp->next;
			}
			if (i != rows) {
				temp = head;
				for (int k = 1;k < i;k++) {
					temp = temp->down;
				}
				InsertDown(i + 1);
				temp = temp->down;
			}
		}
	}

	void PrintSheet() {
		cell* temp1 = currentCell;
		cell* temp = head;
		for (int i = 0;i < rows;i++) {
			for (int j = 0;j < columns;j++) {
				if (temp == temp1) {
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					int k = 12;
					SetConsoleTextAttribute(hConsole, k);
					gotoxy(10 * j, 6 * i);
					cout << "---------" << endl;
					gotoxy(10 * j, 6 * i + 1);
					cout << "|       |" << endl;
					gotoxy(10 * j, 6 * i + 2);
					cout << "|   " << temp->data << "   |" << endl;
					gotoxy(10 * j, 6 * i + 3);
					cout << "|       |" << endl;
					gotoxy(10 * j, 6 * i + 4);
					cout << "---------" << endl;
					k = 7;
					SetConsoleTextAttribute(hConsole, k);
				}
				else {
					gotoxy(10 * j, 6 * i);
					cout << "---------" << endl;
					gotoxy(10 * j, 6 * i + 1);
					cout << "|       |" << endl;
					gotoxy(10 * j, 6 * i + 2);
					cout << "|   " << temp->data << "   |" << endl;
					gotoxy(10 * j, 6 * i + 3);
					cout << "|       |" << endl;
					gotoxy(10 * j, 6 * i + 4);
					cout << "---------" << endl;
				}
				temp = temp->next;
			}
			temp = head;
			for (int k = 0;k <= i;k++) {
				temp = temp->down;
			}
			cout << endl;
		}
		cout << endl;
	}

	void InsertRight(T data)
	{
		cell* newCell = new cell(data);
		newCell->previous = temp;
		if (temp->next == nullptr)
			newCell->next = nullptr;
		else {
			newCell->next = temp->next;
			temp->next->previous = newCell;
		}

		if (temp->up == nullptr)
			newCell->up = nullptr;
		else {
			newCell->up = temp->up->next;
			temp->up->next->down = newCell;
		}

		if (temp->down == nullptr || temp->down->next == nullptr)
			newCell->down = nullptr;
		else {
			newCell->down = temp->down->next;
			temp->down->next->up = newCell;
		}
		temp->next = newCell;
	}


	void InsertLeft(T data)
	{
		cell* newCell = new cell(data);
		newCell->next = temp;
		if (temp->previous == nullptr)
			newCell->previous = nullptr;
		else {
			newCell->previous = temp->previous;
			temp->previous->next = newCell;
		}

		if (temp->up == nullptr)
			newCell->up = nullptr;
		else {
			newCell->up = temp->up->previous;
			temp->up->previous->down = newCell;
		}

		if (temp->down == nullptr || temp->down->previous == nullptr)
			newCell->down = nullptr;
		else {
			newCell->down = temp->down->previous;
			temp->down->previous->up = newCell;
		}
		temp->previous = newCell;
	}


	void InsertDown(T data)
	{
		cell* newCell = new cell(data);
		newCell->up = temp;
		if (temp->down == nullptr)
			newCell->down = nullptr;
		else {
			newCell->down = temp->down;
			temp->down->up = newCell;
		}

		if (temp->next == nullptr || temp->next->down == nullptr)
			newCell->next = nullptr;
		else {
			newCell->next = temp->next->down;
			temp->next->down->previous = newCell;
		}

		if (temp->previous == nullptr)
			newCell->previous = nullptr;
		else {
			newCell->previous = temp->previous->down;
			temp->previous->down->next = newCell;
		}

		
		temp->down = newCell;
	}

	void InsertAbove(T data)
	{

		cell* newCell = new cell(data);
		newCell->down = temp;
		if (temp->up == nullptr)
			newCell->up = nullptr;
		else {
			newCell->up = temp->up;
			temp->up->down = newCell;
		}

		if (temp->next == nullptr || temp->next->up == nullptr)
			newCell->next = nullptr;
		else {
			newCell->next = temp->next->up;
			temp->next->up->previous = newCell;
		}

		if (temp->previous == nullptr)
			newCell->previous = nullptr;
		else {
			newCell->previous = temp->previous->up;
			temp->previous->up->next = newCell;
		}
		temp->up = newCell;

	}

	void ReverseDisplay()
	{
		temp = head;
		cout << "Reversed :";
		while (temp->next)
		{
			temp = temp->next;
		}
		while (temp)
		{
			cout << temp->data << " ";
			temp = temp->previous;
		}
	}

	void ChangeValue( T data)
	{
		currentCell->data = data;
		
	}

	void ClearRow(int rows)
	{
		for (int i=1;i <= columns;i++)
		{
			ChangeValue(rows, i, 0);
		}
	}

	void ClearColumn(int columns)
	{
		for (int i=1;i <= rows;i++)
		{
			ChangeValue( i,columns, 0);
		}
	}


	void InsertColumnToRight()
	{
		temp = head;
		for (int i = 0;i < columns - 1;i++)
		{
			temp = temp->next;
		}
		for (int i = 0;i < rows;i++)
		{
			InsertRight(0);
			temp = temp->down;
		}
		columns++;

	}

	void InsertColumnToLeft()
	{
		temp = head;
		for (int i = 0;i < columns - 1;i++)
		{
			temp = temp->next;
		}
		for (int i = 0;i < rows;i++)
		{
			InsertLeft(0);
			temp = temp->down;
		}
		columns++;

	}

	void InsertRowBelow()
	{
		temp = head;
		for (int i = 0;i < rows - 1;i++)
		{
			temp = temp->down;
		}
		for (int i = 0;i < columns ;i++)
		{
			InsertDown(0);
			temp = temp->next;
		}
		rows++;

	}

	void InsertRowAbove()
	{
		temp = head;
		for (int i = 0;i < rows - 1;i++)
		{
			temp = temp->down;
		}
		for (int i = 0;i < columns;i++)
		{
			InsertAbove(0);
			temp = temp->next;
		}
		rows++;

	}

	

	void DeleteRow()
	{
		temp = head;

		size_t row = index[0] - '0';
		for (int i = 0; i < rows - 2; i++)
		{
			temp = temp->down;
		}
		if (row == 1)
		{
			head = head->down;
		}
		else if (row == rows)
		{
			for (int i = 0;i < columns; i++)
			{
				temp->down = nullptr;
				temp = temp->next;
			}
		}
		else
		{
			for (int i = 0; i < columns; i++)
			{
				temp->down->down->up = temp;
				temp->down = temp->down->down;

				temp = temp->next;
			}
		}
		rows--;
	}

	void DeleteColumn()
	{
		temp = head;

		size_t col = index[2] - '0';
		for (int i = 0; i < columns - 2; i++)
		{
			temp = temp->next;
		}
		if (col == 1)
		{
			head = head->next;
		}
		else if (col == columns)
		{
			for (int i = 0;i < rows; i++)
			{
				temp->next = nullptr;
				temp = temp->down;
			}
		}
		else
		{
			for (int i = 0; i < rows; i++) 
			{

				temp->next->next->previous = temp;
				temp->next = temp->next->next;

				temp = temp->down;
			}
		}
		columns--;
	}

	int GetRangeSum(string StartingIndex, string Endingindex)
	{
		int sum = 0;
		bool flag = false;

		size_t Row_st, Row_end, Col_st, Col_end;

		Row_st = StartingIndex[0] - '0';
		Row_end = Endingindex[0] - '0';
		Col_st = StartingIndex[2] - '0';
		Col_end = Endingindex[2] - '0';

		temp = head;

		for (int i = 1; i <= rows;i++)
		{
			for (int j = 1;j <= columns;j++)
			{
				if (i == Row_end && Col_end == j)
				{
					return sum;
				}
				else if (i == Row_st && Col_st == j)
				{
					flag = true;
				}
				if (flag)
				{
					sum += temp->data;
					
				}
				temp = temp->next;
			}
			temp = head;
			for (int k = 1; k <= i; k++)
			{
				temp = temp->down;
			}

		}


	}

	int Sum(string StartingIndex, string EndingIndex)
	{
		int sum = 0;

		size_t Row_st, Row_end, Col_st, Col_end;

		Row_st = StartingIndex[0] - '0';
		Row_end = EndingIndex[0] - '0';
		Col_st = StartingIndex[2] - '0';
		Col_end = EndingIndex[2] - '0';

		SetCurrentCell(StartingIndex);
		for (int i = Row_st; i <= Row_end; i++)
		{
			for (int j = 1;j <= columns;j++) 
			{
				if (i == Row_end && j == Col_end) 
				{
					return sum; 
				}
				   sum += temp->data;
				   temp = temp->next;
			}

			temp = head;
			for (int k = 1; k <= i; k++) 
			{
				temp = temp->down;
			}
		}
		return sum;
	}


	int GetRangeAverage(string StartingIndex, string EndingIndex)
	{
		float sum = 0;
		float count = 0;
		bool flag = false;

		size_t Row_st, Row_end, Col_st, Col_end;

		Row_st = StartingIndex[0] - '0';
		Row_end = EndingIndex[0] - '0';
		Col_st = StartingIndex[2] - '0';
		Col_end = EndingIndex[2] - '0';

		temp = head;

		for (int i = 1; i <= rows;i++)
		{
			for (int j = 1;j <= columns;j++)
			{
				if (i == Row_end && Col_end == j)
				{
					return sum/count;
				}
				else if (i == Row_st && Col_st == j)
				{
					flag = true;
				}
				if (flag)
				{
					sum += temp->data;
					count++;
					
				}
				temp = temp->next;
			}
			temp = head;
			for (int k = 1; k <= i; k++)
			{
				temp = temp->down;
			}

		}
		return sum / count;
	}



	int GetRangeMinimum(string StartingIndex, string EndingIndex)
	{
		int min = INT16_MAX;
		bool flag = false;

		size_t Row_st, Row_end, Col_st, Col_end;

		Row_st = StartingIndex[0] - '0';
		Row_end = EndingIndex[0] - '0';
		Col_st = StartingIndex[2] - '0';
		Col_end = EndingIndex[2] - '0';

		temp = head;

		for (int i = 1;i <= rows;i++)
		{
			for (int j = 1;j <= columns;j++) 
			{
				if (i == Row_end && Col_end == j)
				{
					return min;
				}
				else if (i == Row_st && Col_st == j)
				{
					flag = true;
				}
				if (flag && min > temp->data) 
				{
					min = temp->data;
				}

				  temp = temp->next;
			}

			temp = head;
			for (int k = 1; k <= i; k++) 
			{
				temp = temp->down;
			}
		}
		return min;

	}

	int GetRangeMaximum(string StartingIndex, string EndingIndex)
	{
		int max = 0;
		bool flag = false;
		size_t Row_st, Row_end, Col_st, Col_end;

		Row_st = StartingIndex[0] - '0';
		Row_end = EndingIndex[0] - '0';
		Col_st = StartingIndex[2] - '0';
		Col_end = EndingIndex[2] - '0';

		temp = head;

		for (int i = 1;i <= rows;i++) 
		{
			for (int j = 1;j <= columns;j++) 
			{
				if (i == Row_end && Col_end == j)
				{
					return max;
				}
				else if (i == Row_st && Col_st == j)
				{
					flag = true;
				}
				if (flag && max < temp->data) 
				{
					max = temp->data;
				}

				  temp = temp->next;
			}
			 temp = head;

			for (int k = 1; k <= i; k++) 
			{
				temp = temp->down;
			}
		}
		return max;
	}
	

	void Copy(string startingIndex, string endingIndex)
	{

		bool flag = false;
		vector<T> vctr;
		size_t Row_st, Row_end, Col_st, Col_end;

		Row_st = startingIndex[0] - '0';
		Row_end = endingIndex[0] - '0';
		Col_st = startingIndex[2] - '0';
		Col_end = endingIndex[2] - '0';

		temp = head;

		for (int i = 1;i <= rows; i++)
		{
			for (int j = 1;j <= columns;j++) 
			{
				if (i == Row_end && Col_end == j)
				{
					return;
				}
				else if (i == Row_st && Col_st == j)
				{
					flag = true;
				}
				if (flag) 
				{
					vctr.push_back(temp->data);
				}

				temp = temp->next;
			}
			temp = head;

			for (int k = 1; k <= i; k++)
			{
				temp = temp->down;
			}
		}
	}

	void paste() 
	{
		bool flag = true;
		vector<T> vctr;
		SetCurrentCell(index);

		for (int i = 0;i < vctr.size(); i++) 
		{
			temp->data = vctr[i];
			if (temp->next == nullptr)
			{
				for (int j = 1; j < columns; j++)
				{
					temp = temp->previous;
				}
				if (temp->down != nullptr)
				{
					temp = temp->down;
				}
				else 
				{
					InsertRowBelow();
					temp = currentCell->down;
				}
				flag = false;
			}
			if (flag)
			{
				temp = temp->next;
			}

			flag = true;
		}
	}

	void Cut(string StartingIndex, string EndingIndex)
	{

		bool flag = false;
		vector<T> vctr;
		size_t Row_st, Row_end, Col_st, Col_end;

		Row_st = StartingIndex[0] - '0';
		Row_end = EndingIndex[0] - '0';
		Col_st = StartingIndex[2] - '0';
		Col_end = EndingIndex[2] - '0';

		temp = head;

		for (int i = 1;i <= rows;i++)
		{
			for (int j = 1;j <= columns;j++)
			{
				if (i == Row_end && Col_end == j)
				{
					return;
				}
				else if (i == Row_st && Col_st == j)
				{
					flag = true;
				}
				if (flag) 
				{
					vctr.push_back(temp->data);
					  temp->data = 0;
				}
				temp = temp->next;
			}
			temp = head;

			for (int k = 1; k <= i; k++)
			{
				temp = temp->down;
			}
		}

	}


	void SetCurrentCell(string index) 
	{
		size_t row, column;
		row = index[0] - '0';
		column = index[2] - '0';
		int i = 1, j = 1;

		temp = head;
		while (i < row) 
		{
			temp = temp->down;
			i++;
		}
		while (j < column) 
		{
			temp = temp->next;
			j++;
		}
	}

	void InsertCellByRightShift(string index)
	{
		SetCurrentCell(index);
		InsertLeft(9);

		temp = head;

		for (int i = 0; i < columns - 1; i++)
		{
			temp = temp->next;
		}

		for (int i = 0; i < rows; i++) 
		{
			if (temp->next == nullptr)
			{
				InsertRight(0);
			}
			temp = temp->down;
		}
		columns++;
	}

	void insertCellByDownShift(string index)
	{
		SetCurrentCell(index);
		InsertAbove(9);

		temp = head;

		for (int i = 0; i < rows - 1; i++) 
		{
			temp = temp->down;
		}
		for (int i = 0; i < columns; i++) 
		{
			if (temp->down == nullptr)
			{
				InsertDown(0);
			}
			temp = temp->next;
		}
		rows++;
	}

	void MoveCurrentCellUp()
	{
		if (currentCell->up != nullptr) 
		{
			currentCell = currentCell->up;
			int Row_i = index[0] - '0';
			int Col_i = index[2] - '0';

			Row_i--;
			index = to_string(Row_i) + ',' + to_string(Col_i);
		}
	}

	void MoveCurrentCellDown()
	{
		if (currentCell->down != nullptr)
		{
			currentCell = currentCell->down;
			int Row_i = index[0] - '0';
			int Col_i = index[2] - '0';

			Row_i++;
			index = to_string(Row_i) + ',' + to_string(Col_i);
		}
		else
		{
			InsertRowBelow();
		}

	}

	void MoveCurrentCellLeft()
	{
		if (currentCell->previous != nullptr)
		{
			currentCell = currentCell->previous;
			int Row_i = index[0] - '0';
			int Col_i = index[2] - '0';

			Col_i--;
			index = to_string(Row_i) + ',' + to_string(Col_i);
		}
		

	}

	void MoveCurrentCellRight()
	{
		if (currentCell->next != nullptr)
		{
			currentCell = currentCell->next;
			int Row_i = index[0] - '0';
			int Col_i = index[2] - '0';

			Col_i++;
			index = to_string(Row_i) + ',' + to_string(Col_i);
		}
		else
		{
			InsertColumnToRight();
		}

	}

	void SetCurrentToHead() 
	{
		currentCell = head;
	}

	void StoreData()
	{
		temp = head;

		fstream file;
		file.open("data.txt", ios::out);
		file << rows << "," << columns << endl;

		for (int i = 0;i < rows;i++) 
		{
			for (int j = 0;j < columns;j++) 
			{
				file << temp->data << ",";
				temp = temp->next;
			}
			temp = head;

			for (int k = 0; k <= i; k++)
			{
				temp = temp->down;
			}
			file << endl;
		}
		file.close();
	}

	void LoadData()
	{
		string data;
		fstream file;
		file.open("data.txt", ios::in);
		file >> data;
		size_t r = stoi(GetField(data, 1));
		size_t c = stoi(GetField(data, 2));
		rows = r;
		columns = c;
		file >> data;
		cell* nc = new cell(stoi(GetField(data, 1)));
		currentCell = temp = head = nc;
		index = "1,1";
		int i = 1;

		while (!file.eof())
		{
			if (data == "")
			{
				break;
			}
			cout << data << endl;

			for (int j = 1; j < c; j++) 
			{
				InsertRight(stoi(GetField(data, j + 1)));
				temp = temp->next;
			}
			data = "";
			file >> data;

			if (i != r)
			{
				temp = head;
				for (int k = 1; k < i; k++) 
				{
					temp = temp->down;
				}
				cout << "DATA : " << GetField(data, 1);
				InsertDown(stoi(GetField(data, 1)));
				temp = temp->down;
			}
			i++;
		}
	}

	string GetField(string record, int field)
	{
		int CommaCount = 1;
		string item = "";

		for (int x = 0; x < record.length(); x++)
		{
			if (record[x] == ',')
			{
				CommaCount = CommaCount + 1;
			}
			else if (CommaCount == field)
			{
				item = item + record[x];
			}
		}
		return item;
	}





 };


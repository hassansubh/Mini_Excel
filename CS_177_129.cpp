
#include"CS_117_129.h"
#include<Windows.h>
#include<conio.h>

int main()
{
	char option;
	cout << "Do you want to load previous data? ( y/n ) :: ";
	cin >> option;
    Excell_cells <int> MiniExcel(option);
	bool flag = true;
	MiniExcel.SetCurrentToHead();

    while (true)
    {
        if (flag) 
        {
            system("cls");
            cout << " Again Printed \n\n\n";
            MiniExcel.PrintSheet();
            flag = false;

            Sleep(50);
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            MiniExcel.MoveCurrentCellLeft();
            flag = true;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            MiniExcel.MoveCurrentCellRight();
            flag = true;
        }
        else if (GetAsyncKeyState(VK_UP))
        {
            MiniExcel.MoveCurrentCellUp();
            flag = true;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            MiniExcel.MoveCurrentCellDown();
            flag = true;
        }
        else if (GetAsyncKeyState('A'))
        {
            MiniExcel.InsertColumnToLeft();
            flag = true;
        }
        else if (GetAsyncKeyState('S'))
        {
            MiniExcel.InsertRowBelow();
            flag = true;
        }
        else if (GetAsyncKeyState('D'))
        {
            MiniExcel.InsertColumnToRight();
            flag = true;
        }
        else if (GetAsyncKeyState('W'))
        {
            MiniExcel.InsertRowAbove();
            flag = true;
        }
        else if (GetAsyncKeyState('T'))
        {
            MiniExcel.DeleteColumn();
            flag = true;
        }
        else if (GetAsyncKeyState('R'))
        {
            MiniExcel.DeleteRow();
            flag = true;
        }
        else if (GetAsyncKeyState('I'))
        {
            int input;
            cout << "Enter value : ";
            cin >> input;
            MiniExcel.ChangeValue(input);
            flag = true;
        }
        else if (GetAsyncKeyState('O'))
        {
            MiniExcel.StoreData();
        }
    }
   
}




//1061646-Term Project-AsciiPokeGo
#include "rlutil.h"
#include "Pet.h"
#include "Attack.h"
#include <fstream>
#include <stdlib.h> // for srand() / rand()
#include "math.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// Globals
string icon[34][30]; //寶可夢圖檔
string map[31]; //地圖 
int MyScore = 0; //得分
Pet pets[34]; //所有寶可夢
Pet *mypet[3] = { nullptr,nullptr,nullptr };  Pet newpet[3]; //玩家的寶可夢
Pet *npc1[3] = { nullptr,nullptr,nullptr };   Pet npc_1[3]; 
Pet *npc2[3] = { nullptr,nullptr,nullptr };   Pet npc_2[3];  //13個NPC的寶可夢
Pet *npc3[3] = { nullptr,nullptr,nullptr };   Pet npc_3[3];
Pet *npc4[3] = { nullptr,nullptr,nullptr };   Pet npc_4[3];
Pet *npc5[3] = { nullptr,nullptr,nullptr };   Pet npc_5[3];
Pet *npc6[3] = { nullptr,nullptr,nullptr };   Pet npc_6[3];
Pet *npc7[3] = { nullptr,nullptr,nullptr };   Pet npc_7[3];
Pet *npc8[3] = { nullptr,nullptr,nullptr };   Pet npc_8[3];
Pet *npc9[3] = { nullptr,nullptr,nullptr };   Pet npc_9[3];
Pet *npcA[3] = { nullptr,nullptr,nullptr };   Pet npc_A[3];
Pet *npcB[3] = { nullptr,nullptr,nullptr };   Pet npc_B[3];
Pet *npcC[3] = { nullptr,nullptr,nullptr };   Pet npc_C[3];
Pet *npcD[3] = { nullptr,nullptr,nullptr };   Pet npc_D[3];
int i = 18, j = 19; //初始地圖路徑
int x = 19, y = 18; //初始地圖座標

//載入地圖
void loadmap()
{
	rlutil::cls(); //畫面清空
	ifstream infile("yzumap.txt", ios::in); //讀地圖檔

	if (!infile)
	{
		cerr << "can't open file!" << endl;
		exit(1);
	}

	rlutil::locate(1, 1); //座標

	for (int i = 0; i < 31; i++) //把地圖放進map
		getline(infile, map[i]);

	for (int i = 0; i < 31; i++) //輸出至畫面
	{
		for (int k = 0; k < 91; k++) 
		{
			//對不同標示設定顏色
			if (map[i][k] == '#') { rlutil::setColor(14); cout << map[i][k]; }
			else if (map[i][k] == ';') { rlutil::setColor(2); cout << map[i][k]; }
			else if (map[i][k] == '!') { rlutil::setColor(6); cout << map[i][k]; }
			else if (map[i][k] == '~') { rlutil::setColor(1); cout << map[i][k]; }
			else { rlutil::setColor(15); cout << map[i][k]; }
		}
		cout << endl;
	}
	cout << endl;

	// @ 移動的位置
	rlutil::locate(x + 1, y + 1);
	rlutil::setColor(4);
	cout << "@";
	fflush(stdout);

	infile.close();
}

//載入所有寶可夢屬性
void loadallpet()
{
	ifstream infile("pokemons.csv"); 

	if (!infile)
	{
		cerr << "can't open file!" << endl;
		system("pause");
		exit(1);
	}

	string line;
	int num1 = 0;
	while (getline(infile, line)) //讀一整行
	{
		istringstream templine(line); // string 轉換成 stream
		string data;
		int num2 = 0;
		while (getline(templine, data, ',')) //讀檔讀到逗號
		{
			//一隻寶可夢的屬性資料
			if (num2 == 0) pets[num1].setPetNO(atof(data.c_str()));
			if (num2 == 1) pets[num1].setName(data);
			if (num2 == 2) pets[num1].setType(data);
			if (num2 == 3) pets[num1].setHP(atof(data.c_str()));
			if (num2 == 4) pets[num1].setATK(atof(data.c_str()));
			if (num2 == 5) pets[num1].setDEF(atof(data.c_str()));
			if (num2 == 6) pets[num1].setSpeed(atof(data.c_str()));
			if (num2 == 7) pets[num1].setApility(atof(data.c_str()));
			num2++;
		}
		num1++;
	}

	infile.close();
}

//載入圖檔
void loadallicons()
{
	int j = 0;
	string fn, st1 = "0", st2 = "01020304050607080910111213141516171819202122232425262728293031323334", st3 = ".txt";
	for (int i = 0; i < 34; i++)
	{	
		//組合檔名
		fn = st1 + st2.substr(j, 2) + st3;
		j += 2;
		ifstream infile(fn.c_str(), ios::in); //讀檔

		for (int k = 0; k < 30; k++)
		{
			getline(infile, icon[i][k]);
		}
		infile.close();
	}
}

//抓寵物
void catchpet(int I, int J)
{
	rlutil::cls();
	rlutil::setColor(15);
	//int random = rand() % 34; //隨機挑選一隻

	int random; int r1;

	if (map[I][J] == '~') //水池地形
	{
		r1 = rand() % 16;

		if (r1 >= 9) //設定大於 9 的都要挑水性的寵物
		{
			random = (rand() % 3) + 6;
		}
		else //剩下的隨機挑
		{
			random = rand() % 31;
			while (random == 6 || random == 7 || random == 8)
			{
				random = rand() % 31;
			}
		}
	}
	else if (map[I][J] == ';') //草地地形
	{
		r1 = rand() % 16; 

		if (r1 >= 9) //設定大於 9 的都要挑草性的寵物
		{
			random = (rand() % 3);
		}
		else //剩下的隨機挑
		{
			random = rand() % 31;
			while (random == 0 || random == 1 || random == 2)
			{
				random = rand() % 31;
			}
		}
	}
	else { random = rand() % 34; } //其他地形機率都一樣

	//顯示寵物圖示
	for (int i = 0; i < 21; i++)
	{
		cout << icon[random][i] << endl;
	}

	//顯示該寶可夢的屬性
	cout << "\nName: " << pets[random].getName() << endl
		<< "Type: " << pets[random].getType() << endl
		<< "HP: " << pets[random].getHP() << endl
		<< "Attack: " << pets[random].getATK() << endl
		<< "Defense: " << pets[random].getDEF() << endl
		<< "Speed: " << pets[random].getSpeed() << endl
		<< "Apility: " << pets[random].getApility() << endl << endl;

	//顯示玩家目前擁有的寶可夢
	cout << "\nMy Pokemon : \n\n";
	for (int i = 0; i < 3; i++)
	{
		if (mypet[i] == nullptr) { cout << "no pet." << endl; }
		else { cout << i+1 << ". " << mypet[i]->getName() << endl; }
	}

	//提示訊息
	int choice;
	cout << "\nDo you want to conquer " << pets[random].getName() << "?" << endl
		<< "Yes or No (please input 1 or 0): ";
	cin >> choice;

	//進行抓寶可夢
	if (choice == 1)
	{
		// 1/2機率
		int r = (rand() % 2);
		int a[2] = {}; a[0] = 1;
		if (a[r] == 1)
		{
			//將該寶可夢設定至玩家清單中
			if (mypet[0] == nullptr) { newpet[0] = pets[random]; mypet[0] = &newpet[0]; }
			else if (mypet[1] == nullptr) { newpet[1] = pets[random]; mypet[1] = &newpet[1]; }
			else if (mypet[2] == nullptr) { newpet[2] = pets[random]; mypet[2] = &newpet[2]; }
			else if (mypet[0] != nullptr && mypet[1] != nullptr && mypet[2] != nullptr)
			{
				//超過三隻的情況
				int choice;
				cout << "\nWhich Pokemon do you want to exchange?" << endl
					<< "(Please input 1 ~ 3): ";
				cin >> choice;
				newpet[choice - 1] = pets[random];
				mypet[choice - 1] = &newpet[choice - 1];
			}

			//成功訊息
			int in;
			cout << "\nYou successfully conquered Pokemon.\n"
				<< "Please input 1 to continue the adventure : ";
			cin >> in;
		}
		else //沒抓到寶可夢之訊息
		{
			int in;
			cout << "\nYou didn’t catch it.\n"
				<< "Please input 1 to continue the adventure : ";
			cin >> in;
		}
	}
}

//載入13個NPC的寵物清單
void loadnpcPet()
{
	//迴圈,設定每個NPC隨機三隻寵物
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_1[i] = pets[r]; npc1[i] = &npc_1[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_2[i] = pets[r]; npc2[i] = &npc_2[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_3[i] = pets[r]; npc3[i] = &npc_3[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_4[i] = pets[r]; npc4[i] = &npc_4[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_5[i] = pets[r]; npc5[i] = &npc_5[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_6[i] = pets[r]; npc6[i] = &npc_6[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_7[i] = pets[r]; npc7[i] = &npc_7[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_8[i] = pets[r]; npc8[i] = &npc_8[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_9[i] = pets[r]; npc9[i] = &npc_9[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_A[i] = pets[r]; npcA[i] = &npc_A[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_B[i] = pets[r]; npcB[i] = &npc_B[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_C[i] = pets[r]; npcC[i] = &npc_C[i]; }
	for (int i = 0; i < 3; i++) { int r = (rand() % 34); npc_D[i] = pets[r]; npcD[i] = &npc_D[i]; }

}

//進行對戰
void battle(int I,int J)
{
	rlutil::cls();
	rlutil::setColor(15);

	//用路徑檢查對上的是哪一個NPC,並進行對戰,傳入積分累積
	if (map[I - 1][J] == '1') { ATTACK<int> r1(newpet, npc_1); r1.attack(MyScore, icon); }
	else if (map[I - 1][J] == '2') { ATTACK<int> r2(newpet, npc_2); r2.attack(MyScore,icon); }
	else if (map[I - 1][J] == '3') { ATTACK<Pet> r3(newpet, npc_3); r3.attack(MyScore, icon); }
	else if (map[I - 1][J] == '4') { ATTACK<int> r4(newpet, npc_4); r4.attack(MyScore, icon); }
	else if (map[I - 1][J] == '5') { ATTACK<Pet> r5(newpet, npc_5); r5.attack(MyScore, icon); }
	else if (map[I - 1][J] == '6') { ATTACK<Pet> r6(newpet, npc_6); r6.attack(MyScore, icon); }
	else if (map[I + 1][J] == '7') { ATTACK<int> r7(newpet, npc_7); r7.attack(MyScore, icon); }
	else if (map[I + 1][J] == '8') { ATTACK<int> r8(newpet, npc_8); r8.attack(MyScore, icon); }
	else if (map[I + 1][J] == '9') { ATTACK<int> r9(newpet, npc_9); r9.attack(MyScore, icon); }
	else if (map[I - 1][J] == 'A') { ATTACK<string> rA(newpet, npc_A); rA.attack(MyScore, icon); }
	else if (map[I - 1][J] == 'B') { ATTACK<int> rB(newpet, npc_B); rB.attack(MyScore, icon); }
	else if (map[I - 1][J] == 'C') { ATTACK<int> rC(newpet, npc_C); rC.attack(MyScore, icon); }
	else if (map[I + 1][J] == 'D') { ATTACK<string> rD(newpet, npc_D); rD.attack(MyScore, icon); }
}

// Main loop and input handling
int main() 
{
	srand(time(0));

	rlutil::hidecursor();
	rlutil::saveDefaultColor();
	rlutil::setColor(2);
	cout << "Welcome! Use WASD to move, ESC to quit.\n";
	rlutil::setColor(6);
	rlutil::anykey("Hit any key to start.\n");
	rlutil::setColor(15);
	loadmap(); 
	loadallpet();
	loadallicons();
	loadnpcPet();
	while (1) { 
		// Input
		if (kbhit()) {
			char k = rlutil::getkey();

			//方向控制
			int oldi = i, oldj = j;
			int oldx = x, oldy = y;

			//上下左右有1/10機率進入抓寵物的流程
			if (k == 'a') 
			{ 
				--x; --j; 
				int r = (rand() % 10);
				int a[10] = {}; a[4] = 1;
				if (a[r] == 1) { catchpet(i, j); }
			}
			else if (k == 'd') 
			{
				++x; ++j; 
				int r = (rand() % 10);
				int a[10] = {}; a[4] = 1;
				if (a[r] == 1) { catchpet(i, j); }
			}
			else if (k == 'w') 
			{ 
				--y; --i; 
				int r = (rand() % 10);
				int a[10] = {}; a[4] = 1;
				if (a[r] == 1) { catchpet(i, j); }
			}
			else if (k == 's') 
			{
				++y; ++i; 
				int r = (rand() % 10);
				int a[10] = {}; a[4] = 1;
				if (a[r] == 1) { catchpet(i, j); }
			}
			else if (k == rlutil::KEY_SPACE) //空白鍵結束遊戲,並顯示分數
			{
				rlutil::cls(); rlutil::setColor(15);
				string choice;
				cout << "Do you want to end the game? (input Y or N): ";
				cin >> choice;
				if (choice == "Y") { cout << "Your final score is " << MyScore << endl; break; }
			}

			//不能走的地方
			if (map[i][j] == '*' || map[i][j] == '!'||
				map[i][j] == '1' || map[i][j] == '2'|| 
				map[i][j] == '3' || map[i][j] == '4'|| 
				map[i][j] == '5' || map[i][j] == '6'|| 
				map[i][j] == '7' || map[i][j] == '8'|| 
				map[i][j] == '9' || map[i][j] == 'A'|| 
				map[i][j] == 'B' || map[i][j] == 'C'|| 
				map[i][j] == 'D') { x = oldx; y = oldy;  i = oldi; j = oldj; }
			else if (map[i][j] == '#') { battle(i, j); } //抵達門口,開始對戰
			// Drawing
			loadmap();
		}
	}
	rlutil::resetColor();
	rlutil::showcursor();
	system("pause");
	return 0;
}

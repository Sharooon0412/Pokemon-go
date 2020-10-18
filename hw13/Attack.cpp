//1061646-Term Project-AsciiPokeGo
#include "rlutil.h"
#include "Attack.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

template<typename T >
ATTACK<T>::ATTACK(Pet me[], Pet npc[])
{
	for (int i = 0; i < 3; i++)
	{
		Me[i] = me[i];
		NPC[i] = npc[i];
	}
}

template<typename T >
void ATTACK<T>::attack(int &score,string ic[][30])
{
	rlutil::setColor(15);
	char k = rlutil::KEY_SPACE;
	int cnt = 1; int choice;

	//空白鍵繼續
	while (k == rlutil::KEY_SPACE)
	{
		cout << "\nRound " << cnt << endl << endl;
		showStats(ic); //顯示目前寵物狀態
		if (getCurrentmyPet()->getSpeed() >= getCurrentnpcPet()->getSpeed()) //比較速度決定先攻
		{
			cout << "---------------------------------------------------" << endl;
			cout << getCurrentmyPet()->getName() << " attack " << getCurrentnpcPet()->getName() << endl << endl;
			attackdetail(*getCurrentmyPet(), *getCurrentnpcPet()); //進行攻擊

			//檢查哪一方的寵物都死亡,決定勝利者
			if (getCurrentnpcPet() == nullptr) 
			{
				cout << "\nNPC's Pokemon is all defeated\n\n";
				cout << "\n>>> Player win! <<<\n" << endl;
				score += 100; //玩家贏 得100分
				cout << "\nYou get 100 points!\n" << endl;
				cout << "Please input 1 to continue: ";
				cin >> choice;
				break;
			}
			else if(getCurrentmyPet() == nullptr)
			{
				cout << "\nMy Pokemon is all defeated\n\n";
				cout << "\n>>> NPC win! <<<\n" << endl;
				cout << "Please input 1 to continue: ";
				cin >> choice;
				break;
			}

			cout << "---------------------------------------------------" << endl;
			//後攻
			cout << getCurrentnpcPet()->getName() << " attack " << getCurrentmyPet()->getName() << endl << endl;
			attackdetail(*getCurrentnpcPet(), *getCurrentmyPet());

			if (getCurrentmyPet() == nullptr)
			{
				cout << "\nMy Pokemon is all defeated\n\n";
				cout << "\n>>> NPC win! <<<\n" << endl;
				cout << "Please input 1 to continue: ";
				cin >> choice;
				break;
			}
			else if (getCurrentnpcPet() == nullptr)
			{
				cout << "\nNPC's Pokemon is all defeated\n\n";
				cout << "\n>>> Player win! <<<\n" << endl;
				score += 100;
				cout << "\nYou get 100 points!\n" << endl;
				cout << "Please input 1 to continue: ";
				cin >> choice;
				break;
			}
			cout << "==================================================" << endl;
			cout << "Please input SPACE to continue: ";
			k = rlutil::getkey(); //空白鍵繼續
			cnt++; //下一回合
		}
		else
		{
			cout << "---------------------------------------------------" << endl;
			cout << getCurrentnpcPet()->getName() << " attack " << getCurrentmyPet()->getName() << endl << endl;
			attackdetail(*getCurrentnpcPet(), *getCurrentmyPet());

			if (getCurrentnpcPet() == nullptr)
			{
				cout << "\nNPC's Pokemon is all defeated\n\n";
				cout << "\n>>> Player win! <<<\n" << endl;
				score += 100;
				cout << "\nYou get 100 points!\n" << endl;
				cout << "Please input 1 to continue: ";
				cin >> choice;
				break;
			}
			else if (getCurrentmyPet() == nullptr)
			{
				cout << "\nMy Pokemon is all defeated\n\n";
				cout << "\n>>> NPC win! <<<\n" << endl;
				cout << "Please input 1 to continue: ";
				cin >> choice;
				break;
			}

			cout << "---------------------------------------------------" << endl;
			cout << getCurrentmyPet()->getName() << " attack " << getCurrentnpcPet()->getName() << endl << endl;
			attackdetail(*getCurrentmyPet(), *getCurrentnpcPet());

			if (getCurrentmyPet() == nullptr)
			{
				cout << "\nMy Pokemon is all defeated\n\n";
				cout << "\n>>> NPC win! <<<\n" << endl;
				cout << "Please input 1 to continue: ";
				cin >> choice;
				break;
			}
			else if (getCurrentnpcPet() == nullptr)
			{
				cout << "\nNPC's Pokemon is all defeated\n\n";
				cout << "\n>>> Player win! <<<\n" << endl;
				score += 100;
				cout << "\nYou get 100 points!\n" << endl;
				cout << "Please input 1 to continue: ";
				cin >> choice;
				break;
			}
			cout << "===================================================" << endl;
			cout << "Please input SPACE to continue: ";
			k = rlutil::getkey();
			cnt++;
		}
	
	}
}

template<typename T >
void ATTACK<T>::attackdetail(Pet &m, Pet &y)
{
	//一般攻擊
	int attack = m.getATK() - y.getDEF();
	y.setHP(y.getHP() - (m.getATK() - y.getDEF()));
	cout << y.getName() << " 減少 " << attack << "點 HP" << endl;

	//附加特殊能力
	if (m.getApility() == 1 || y.getApility() == 1)
	{ 
		//每回合回復HP3
		if (m.getApility() == 1) { m.setHP(m.getHP() + 3); cout << m.getName() << "回復 HP 3點" << endl; }
		if (y.getApility() == 1) { y.setHP(y.getHP() + 3); cout << y.getName() << "回復 HP 3點" << endl; }
	}
	if (m.getApility() == 2)
	{ 
		//隨機附加不受防禦影響的傷害1~3
		int r = rand() % 3; 
		int a[3] = {1,2,3}; 
		y.setHP(y.getHP() - a[r]);
		cout << y.getName() << " 受到 " << m.getName() << " Burning 攻擊,減少 " << a[r] << " 點 HP\n";
	}
	if (y.getApility() == 3)
	{
		//反擊1 / 5所受傷害
		int CounterAttack;
		CounterAttack = (m.getATK() - y.getDEF()) / 5;
		m.setHP(m.getHP() - CounterAttack);
		cout << m.getName() << " 受到 "  << CounterAttack << " 點反擊傷害\n";
	}
	if (y.getApility() == 4 && (m.getApility() == 9 || m.getApility() == 11 || m.getApility() == 12))
	{
		//免疫降低能力值的特殊能力
		cout << y.getName() << " 對 " << m.getName() << " 技能免疫" << endl;
	}
	if (y.getApility() == 5)
	{
		//每次攻擊吸收2~3HP
		int r = rand() % 2;
		int a[2] = { 1,0 };
		if (a[r] == 1)
		{
			y.setHP(y.getHP() + 3);
			m.setHP(m.getHP() - 3);
			cout << y.getName() << " 吸收 " << m.getName() << " 3點 HP\n";
		}
		else
		{
			y.setHP(y.getHP() + 2);
			m.setHP(m.getHP() - 2);
			cout << y.getName() << " 吸收 " << m.getName() << " 2點 HP\n";
		}
	}
	if (y.getApility() == 6)
	{
		//1/5機率迴避攻擊
		int r = rand() % 5;
		int a[5] = { 0,0,0,1,0 };
		if (a[r] == 1)
		{
			y.setHP(y.getHP() + attack);
			cout << y.getName() << " 成功迴避 " << m.getName() << " 的攻擊\n";
		}
	}
	if (m.getApility() == 7) 
	{
		//1/5機率兩次攻擊
		int r = rand() % 5;
		int a[5] = { 0,0,0,1,0 };
		if (a[r] == 1)
		{ 
			y.setHP(y.getHP() - (m.getATK() - y.getDEF())); 
			cout << y.getName() << " 再次被 " << m.getName() << " 攻擊,減少 " << m.getATK() - y.getDEF() << " 點 HP" << endl;
		}
	}
	if (m.getApility() == 8)
	{
		//被攻擊的敵方中毒每回合-2HP //屬性
		if (m.getused() == 0)
		{
			cout << y.getName() << " 中毒\n";
			m.setused(1); 
		}
		else if (m.getused() == 1) 	//產生影響的下一回合開始計算
		{
			y.setHP(y.getHP() - 2);
			cout << y.getName() << " 中毒,減少 2點HP\n";
		}

		//被攻擊方死亡後 能力回復
		if (y.getHP() <= 0)
			m.setused(0);
	}
	if (m.getApility() == 9 && y.getApility() != 4)
	{
		if (m.getused() == 0)
		{
			//攻擊時降低敵方速度值2
			y.setSpeed(y.getSpeed() - 2);
			cout << y.getName() << " 降低速度 2點\n";
			m.setused(1); 	//一場只發動一次

		}

		//被攻擊方死亡後 能力回復
		if (y.getHP() <= 0)
			m.setused(0);
	}
	if (y.getApility() == 10) 
	{
		//每次受到的傷害-2
		y.setHP(y.getHP() + 2);
		cout << y.getName() << " 減少所受傷害 2點 \n";
	}
	if (m.getApility() == 11 && y.getApility() != 4)
	{
		if (m.getused() == 0)
		{
			//攻擊時降低敵方防禦力2
			y.setDEF(y.getDEF() - 2);
			cout << y.getName() << " 降低防禦力 2點\n";
			m.setused(1); 	//一場只發動一次
		}

		//被攻擊方死亡後 能力回復
		if (y.getHP() <= 0)
			m.setused(0);
	}
	if (m.getApility() == 12 && y.getApility() != 4)
	{
		if (m.getused() == 0)
		{
			//攻擊時降低敵方攻擊力2
			y.setATK(y.getATK() - 2);
			cout << y.getName() << " 降低攻擊力 2點\n";
			m.setused(1); 	//一場只發動一次
		}

		//被攻擊方死亡後 能力回復
		if (y.getHP() <= 0)
			m.setused(0);
	}
}

template<typename T >
//取得目前玩家寵物的地址
Pet* ATTACK<T>::getCurrentmyPet()
{
	for (int i = 0; i < 3; i++)
	{
		//血量 > 0
		if (Me[i].getHP() > 0)
			return &Me[i];
	}

	return  nullptr;
}

template<typename T >
//取得目前NPC寵物的地址
Pet* ATTACK<T>::getCurrentnpcPet()
{
	for (int i = 0; i < 3; i++)
	{
		//血量 > 0
		if (NPC[i].getHP() > 0)
			return &NPC[i];
	}

	return  nullptr;
}

template<typename T >
void ATTACK<T>::showStats(string ic[][30])
{

	//顯示目前寵物圖示
	rlutil::setColor(14); cout << "NPC" << endl; rlutil::setColor(15);
	for (int i = 0; i < 21; i++) { cout << ic[getCurrentnpcPet()->getPetNO() - 1][i] << endl; }
	rlutil::setColor(14); cout << "Player" << endl; rlutil::setColor(15);
	for (int i = 0; i < 21; i++) { cout << ic[getCurrentmyPet()->getPetNO() - 1][i] << endl; }

	rlutil::setColor(14);
	cout << setw(10) << "NPC " << setw(25) << "Player " << endl;
	rlutil::setColor(15);

	cout << setw(10) << "Name: " << getCurrentnpcPet()->getName() << setw(15) << "Name: " << getCurrentmyPet()->getName() << endl
		<< setw(10) << "Type: "<< getCurrentnpcPet()->getType() << setw(17) << "Type: " << getCurrentmyPet()->getType() << endl
		<< setw(10) << "HP: " << getCurrentnpcPet()->getHP() << setw(21) << "HP: " << getCurrentmyPet()->getHP() << endl
		<< setw(10) << "Attack: "  << getCurrentnpcPet()->getATK() << setw(21) << "Attack: " << getCurrentmyPet()->getATK() << endl
		<< setw(10) << "Defense: "  << getCurrentnpcPet()->getDEF() << setw(22) << "Defense: " << getCurrentmyPet()->getDEF() << endl
		<< setw(10) << "Speed: " << getCurrentnpcPet()->getSpeed() << setw(22) << "Speed: " << getCurrentmyPet()->getSpeed() << endl
		<< setw(10) << "Apility: " << getCurrentnpcPet()->getApility() << setw(21) << "Apility: " << getCurrentmyPet()->getApility() << endl << endl;

	cout << "The Pokemon owned by both sides is: " << endl << endl;
	rlutil::setColor(14);
	cout << setw(10) << "NPC" << setw(25) << "Player" << endl;
	rlutil::setColor(15);
	for (int i = 0; i < 3; i++)
	{
		cout << setw(10) << NPC[i].getName() << setw(25) << Me[i].getName() << endl;
	}
	cout << endl;
}

template class  ATTACK<int>;
template class  ATTACK<Pet>;
template class  ATTACK<string>;
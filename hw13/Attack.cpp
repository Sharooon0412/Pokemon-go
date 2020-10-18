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

	//�ť����~��
	while (k == rlutil::KEY_SPACE)
	{
		cout << "\nRound " << cnt << endl << endl;
		showStats(ic); //��ܥثe�d�����A
		if (getCurrentmyPet()->getSpeed() >= getCurrentnpcPet()->getSpeed()) //����t�רM�w����
		{
			cout << "---------------------------------------------------" << endl;
			cout << getCurrentmyPet()->getName() << " attack " << getCurrentnpcPet()->getName() << endl << endl;
			attackdetail(*getCurrentmyPet(), *getCurrentnpcPet()); //�i�����

			//�ˬd���@�誺�d�������`,�M�w�ӧQ��
			if (getCurrentnpcPet() == nullptr) 
			{
				cout << "\nNPC's Pokemon is all defeated\n\n";
				cout << "\n>>> Player win! <<<\n" << endl;
				score += 100; //���aĹ �o100��
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
			//���
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
			k = rlutil::getkey(); //�ť����~��
			cnt++; //�U�@�^�X
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
	//�@�����
	int attack = m.getATK() - y.getDEF();
	y.setHP(y.getHP() - (m.getATK() - y.getDEF()));
	cout << y.getName() << " ��� " << attack << "�I HP" << endl;

	//���[�S���O
	if (m.getApility() == 1 || y.getApility() == 1)
	{ 
		//�C�^�X�^�_HP3
		if (m.getApility() == 1) { m.setHP(m.getHP() + 3); cout << m.getName() << "�^�_ HP 3�I" << endl; }
		if (y.getApility() == 1) { y.setHP(y.getHP() + 3); cout << y.getName() << "�^�_ HP 3�I" << endl; }
	}
	if (m.getApility() == 2)
	{ 
		//�H�����[�������m�v�T���ˮ`1~3
		int r = rand() % 3; 
		int a[3] = {1,2,3}; 
		y.setHP(y.getHP() - a[r]);
		cout << y.getName() << " ���� " << m.getName() << " Burning ����,��� " << a[r] << " �I HP\n";
	}
	if (y.getApility() == 3)
	{
		//����1 / 5�Ҩ��ˮ`
		int CounterAttack;
		CounterAttack = (m.getATK() - y.getDEF()) / 5;
		m.setHP(m.getHP() - CounterAttack);
		cout << m.getName() << " ���� "  << CounterAttack << " �I�����ˮ`\n";
	}
	if (y.getApility() == 4 && (m.getApility() == 9 || m.getApility() == 11 || m.getApility() == 12))
	{
		//�K�̭��C��O�Ȫ��S���O
		cout << y.getName() << " �� " << m.getName() << " �ޯ�K��" << endl;
	}
	if (y.getApility() == 5)
	{
		//�C�������l��2~3HP
		int r = rand() % 2;
		int a[2] = { 1,0 };
		if (a[r] == 1)
		{
			y.setHP(y.getHP() + 3);
			m.setHP(m.getHP() - 3);
			cout << y.getName() << " �l�� " << m.getName() << " 3�I HP\n";
		}
		else
		{
			y.setHP(y.getHP() + 2);
			m.setHP(m.getHP() - 2);
			cout << y.getName() << " �l�� " << m.getName() << " 2�I HP\n";
		}
	}
	if (y.getApility() == 6)
	{
		//1/5���v�j�ק���
		int r = rand() % 5;
		int a[5] = { 0,0,0,1,0 };
		if (a[r] == 1)
		{
			y.setHP(y.getHP() + attack);
			cout << y.getName() << " ���\�j�� " << m.getName() << " ������\n";
		}
	}
	if (m.getApility() == 7) 
	{
		//1/5���v�⦸����
		int r = rand() % 5;
		int a[5] = { 0,0,0,1,0 };
		if (a[r] == 1)
		{ 
			y.setHP(y.getHP() - (m.getATK() - y.getDEF())); 
			cout << y.getName() << " �A���Q " << m.getName() << " ����,��� " << m.getATK() - y.getDEF() << " �I HP" << endl;
		}
	}
	if (m.getApility() == 8)
	{
		//�Q�������Ĥ褤�r�C�^�X-2HP //�ݩ�
		if (m.getused() == 0)
		{
			cout << y.getName() << " ���r\n";
			m.setused(1); 
		}
		else if (m.getused() == 1) 	//���ͼv�T���U�@�^�X�}�l�p��
		{
			y.setHP(y.getHP() - 2);
			cout << y.getName() << " ���r,��� 2�IHP\n";
		}

		//�Q�����覺�`�� ��O�^�_
		if (y.getHP() <= 0)
			m.setused(0);
	}
	if (m.getApility() == 9 && y.getApility() != 4)
	{
		if (m.getused() == 0)
		{
			//�����ɭ��C�Ĥ�t�׭�2
			y.setSpeed(y.getSpeed() - 2);
			cout << y.getName() << " ���C�t�� 2�I\n";
			m.setused(1); 	//�@���u�o�ʤ@��

		}

		//�Q�����覺�`�� ��O�^�_
		if (y.getHP() <= 0)
			m.setused(0);
	}
	if (y.getApility() == 10) 
	{
		//�C�����쪺�ˮ`-2
		y.setHP(y.getHP() + 2);
		cout << y.getName() << " ��֩Ҩ��ˮ` 2�I \n";
	}
	if (m.getApility() == 11 && y.getApility() != 4)
	{
		if (m.getused() == 0)
		{
			//�����ɭ��C�Ĥ訾�m�O2
			y.setDEF(y.getDEF() - 2);
			cout << y.getName() << " ���C���m�O 2�I\n";
			m.setused(1); 	//�@���u�o�ʤ@��
		}

		//�Q�����覺�`�� ��O�^�_
		if (y.getHP() <= 0)
			m.setused(0);
	}
	if (m.getApility() == 12 && y.getApility() != 4)
	{
		if (m.getused() == 0)
		{
			//�����ɭ��C�Ĥ�����O2
			y.setATK(y.getATK() - 2);
			cout << y.getName() << " ���C�����O 2�I\n";
			m.setused(1); 	//�@���u�o�ʤ@��
		}

		//�Q�����覺�`�� ��O�^�_
		if (y.getHP() <= 0)
			m.setused(0);
	}
}

template<typename T >
//���o�ثe���a�d�����a�}
Pet* ATTACK<T>::getCurrentmyPet()
{
	for (int i = 0; i < 3; i++)
	{
		//��q > 0
		if (Me[i].getHP() > 0)
			return &Me[i];
	}

	return  nullptr;
}

template<typename T >
//���o�ثeNPC�d�����a�}
Pet* ATTACK<T>::getCurrentnpcPet()
{
	for (int i = 0; i < 3; i++)
	{
		//��q > 0
		if (NPC[i].getHP() > 0)
			return &NPC[i];
	}

	return  nullptr;
}

template<typename T >
void ATTACK<T>::showStats(string ic[][30])
{

	//��ܥثe�d���ϥ�
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
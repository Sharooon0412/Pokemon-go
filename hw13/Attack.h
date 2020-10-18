//1061646-Term Project-AsciiPokeGo
#ifndef ATTACK_H
#define ATTACK_H

#include "rlutil.h"
#include "Pet.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

//�i�������class
template<typename T >
class ATTACK
{
public:
	ATTACK(Pet me[],Pet npc[]);

	//��Ԭy�{
	void attack(int &score, string ic[][30]);

	//�ԲӪ������禡,�S���O
	void attackdetail(Pet &m, Pet &y);

	//�q myPetList �̧Ǩ��o�n�i���Ԫ��d���A�d�����`�h���L�A�Ҧ��d�����w�g���`�A�h�Ǧ^nullptr
	Pet* getCurrentmyPet();

	//�q npcPetList �̧Ǩ��o�n�i���Ԫ��d���A�d�����`�h���L�A�Ҧ��d�����w�g���`�A�h�Ǧ^nullptr
	Pet* getCurrentnpcPet();
	
	//����d�����A
	void showStats(string ic[][30]);

private:
	Pet Me[3];
	Pet NPC[3];
};


#endif // ATTACK_H
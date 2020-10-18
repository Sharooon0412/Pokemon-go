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

//進行攻擊的class
template<typename T >
class ATTACK
{
public:
	ATTACK(Pet me[],Pet npc[]);

	//對戰流程
	void attack(int &score, string ic[][30]);

	//詳細的攻擊函式,特殊能力
	void attackdetail(Pet &m, Pet &y);

	//從 myPetList 依序取得要進行對戰的寵物，寵物死亡則跳過，所有寵物都已經死亡，則傳回nullptr
	Pet* getCurrentmyPet();

	//從 npcPetList 依序取得要進行對戰的寵物，寵物死亡則跳過，所有寵物都已經死亡，則傳回nullptr
	Pet* getCurrentnpcPet();
	
	//顯示寵物狀態
	void showStats(string ic[][30]);

private:
	Pet Me[3];
	Pet NPC[3];
};


#endif // ATTACK_H
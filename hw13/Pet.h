//1061646-Term Project-AsciiPokeGo
#ifndef PET_H
#define PET_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

//個別寵物的屬性資訊
class Pet {

public:
	Pet(string nameValue = "", string typeValue = "",
		int HPValue = 0, int ATKValue = 0, int DEFValue = 0, 
		int speedValue = 0, int apilityValue = 0);

	void setPetNO(int petnoValue);
	int getPetNO();

	void setName(string nameValue);
	string getName();

	void setType(string typeValue);
	string getType();

	void setHP(int HPValue);
	int getHP();

	void setATK(int ATKValue);
	int getATK();

	void setDEF(int DEFValue);
	int getDEF();

	void setSpeed(int speedValue);
	int getSpeed();

	void setApility(int apilityValue);
	int getApility();

	void setused(int u);
	int getused();

private:
	int petno;
	char name[15];  
	char type[10];
	int hp; 
	int atk;
	int def;
	int speed;
	int apility;
	int use = 0;
};

#endif //PET_H
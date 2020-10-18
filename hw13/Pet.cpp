//1061646-Term Project-AsciiPokeGo
#include <iostream>
#include "Pet.h" 

Pet::Pet(string nameValue, string typeValue,
	int HPValue, int ATKValue, int DEFValue,
	int speedValue, int apilityValue)
{
	setName(nameValue);
	setType(typeValue);
	setHP(HPValue);
	setATK(ATKValue);
	setDEF(DEFValue);
	setSpeed(speedValue);
	setApility(apilityValue);
}

void Pet::setPetNO(int petnoValue)
{
	petno = petnoValue;
}

int Pet::getPetNO()
{
	return petno;
}

void Pet::setName(string nameValue)
{
	size_t length = nameValue.size();
	length = (length < 15 ? length : 14);
	for (size_t i = 0; i < length; i++)
		name[i] = nameValue[i];
	name[length] = '\0';
}

string Pet::getName()
{
	return string(name);
}

void Pet::setType(string typeValue)
{
	size_t length = typeValue.size();
	length = (length < 10 ? length : 9);
	for (size_t i = 0; i < length; i++)
		type[i] = typeValue[i];
	type[length] = '\0';
}

string Pet::getType()
{
	return string(type);
}

void Pet::setHP(int HPValue)
{
	hp = HPValue;
}

int Pet::getHP()
{
	return hp;
}

void Pet::setATK(int ATKValue)
{
	atk = ATKValue;
}

int Pet::getATK()
{
	return atk;
}

void Pet::setDEF(int DEFValue)
{
	def = DEFValue;
}

int Pet::getDEF()
{
	return def;
}

void Pet::setSpeed(int speedValue)
{
	speed = speedValue;
}

int Pet::getSpeed()
{
	return speed;
}

void Pet::setApility(int apilityValue)
{
	apility = apilityValue;
}

int Pet::getApility()
{
	return apility;
}

void Pet::setused(int u)
{
	use = u;
}

int Pet::getused()
{
	return use;
}
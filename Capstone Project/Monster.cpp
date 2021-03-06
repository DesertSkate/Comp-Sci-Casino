#include "Monster.h"

double Monster::get_drop_chance()
{
	return -1;
}

vector<drop> Monster::get_drop_table() const
{
	return drop_table;
}

vector<double> Monster::get_level_mods() const
{
	return level_mods;
}

void Monster::add_to_drops(drop d)
{
	drop_table.push_back(d);
}

Monster::Monster(string n, int l, vector<double> stats, vector<double> mods, vector<double> cv): Entity(n ,l, stats, mods)
{
	rarity_drop_chance = cv;
}
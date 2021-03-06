#pragma once
#include "Entity.h"
#include "Item.h"

//************************

//**** Inheritance ******

//***********************

class Player : public Entity
{
public:
	double get_xp() const;
	double get_max_xp() const;
	double get_damage();

	int get_knowledge() const;
	int get_attr_points() const;
	int get_points_per_level() const;

	double get_health();
	double get_max_health() const;

	vector<Item> get_inventory() const;
	vector<Item> get_equipped() const;

	vector<int> get_pos() const;

	void set_xp(double);
	void set_max_xp(double);
	void set_knowledge(int);
	void set_attr_points(int);

	void set_equipped(Item, int);

	void set_pos(vector<int>);

	void add_stats(vector<double> s = {0, 0, 0, 0, 0, 0, 0});

	void add_to_inventory(Item);

	void remove_from_inventory(Item);

	Player(string n = "Player", int l = 1, vector<double> stats = { 20, 0, 0, 0, 0, 0, 0 }, vector<double> mods = { 0,0,0,0,0,0,0 });

	static const int points_per_level = 5;
protected:
	double xp = 0;
	double max_xp = 25;
	double max_health;

	int knowledge = 1;
	int attribute_points = 15;
	
	vector<Item> inventory;
	// vector should be: helm, chest, legs, weapon
	vector<Item> equipped;

	vector<int> cur_pos;
};
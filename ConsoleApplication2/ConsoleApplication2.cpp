#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>

using namespace std;

class Map;
class Hero;
class Item;
class  Map
{

public:
	vector <Item> items;
	vector < vector <string> > room; //initializing vector for 2d
	int x, y, exit = 0, enter = 1, exitX = 0, exitY = 0, enterX = 0, enterY = 0, room_type = 0, mid_x, mid_y;
	string way_out = "", way_in = "botom";
	bool Monster_exist = true;
	Map(int a = 5, int b = 5, int ex = 1, int room_ty = 1) //our arguments: 1) the length of the room by X 2) The length of the room by Y 3) 1 - from above 2 - from the right side, default from above 4) the type of room(1 - ordinary square, 2 - L shaped)
	{
		room_type = room_ty;
		exitX = 0;
		exitY = 0;
		x = a;	//initializing variables, that were made through the constructor 
		y = b;
		exit = ex;

	}
	void create_room()		//function, that creates room, walls, and escape (in theory entrance?) 
	{
		srand(time(0));
		system("cls");			//clears console 
		room.resize(y);					   //room size by Y	
		for (int i = 0; i < y; i++)		   //room size by X 
		{
			room[i].resize(x);
		}
		if (room_type == 1)
		{
			for (int i = 0; i < y; i++)		   //filling room by walls and empty space
			{
				for (int a = 0; a < x; a++)
				{
					if (i == 0 || i == y - 1 || a == 0 || a == x - 1)
					{
						room[i][a] = (char)35;
					}
					else
					{
						room[i][a] = (char)32;
					}
				}
			}
			for (int i = 0; i < y; i++)
			{
				for (int a = 0; a < x; a++) //generates exit
				{
					if (i != 0 && (a != 0 && a != x) && i != y && (a != 0 && a != x))  //used for not making exit at the corners
					{
						if (exit == 1)                        //if we selected UP exit
						{
							exit = 0;
							exitY = 0;
							exitX = 1 + rand() % (x - 2);
							way_out = "up";
						}
						if (exit == 2)							//... side exit
						{
							exit = 0;
							exitY = 1 + rand() % (i);
							exitX = x - 1;
							way_out = "side";
						}
						room[exitY][exitX] = (char)32;

					}
				}
			}
			{

				for (int i = 0; i < y; i++)
				{
					for (int a = 0; a < x; a++) //generates entrance
					{
						if (i != 0 && i != y && a != 0 && a != x)  //not making exit at the corners
						{
							if (way_in == "botom" && enter == 1)                        //... UP exit
							{
								enter = 0;
								enterY = y - 1;
								enterX = 1 + rand() % (x - 2);
							}
							if (way_in == "left" && enter == 1)							//... side exit
							{
								enter = 0;
								enterY = 1 + rand() % (y - 2);
								enterX = 0;
							}
							room[enterY][enterX] = (char)32;
						}
					}
				}
			}
		}
		else if (room_type == 2)
		{
			mid_x = 2 + rand() % (x - 2);
			mid_y = 2 + rand() % (y - 2);
			for (int i = 0; i < y; i++)
			{
				for (int a = 0; a < x; a++)
				{
					if (i == 0 || a == 0)
					{
						room[i][a] = (char)35;
					}
					else if (a == x - 1 && i <= mid_y - 1)
					{
						room[i][a] = (char)35;
					}
					else if (a > mid_x && i == mid_y)
					{
						room[i][a] = (char)35;
					}
					else if (a == mid_x && i >= mid_y)
					{
						room[i][a] = (char)35;
					}
					else if (i == y - 1 && a <= mid_x)
					{
						room[i][a] = (char)35;
					}
					else
					{
						room[i][a] = (char)32;
					}

				}
			}
			if (exit == 1)                        //...selected UP exit
			{
				exit = 0;
				exitY = 0;
				exitX = 1 + rand() % (x - 2);
				way_out = "up";
			}
			if (exit == 2)						  //... side exit
			{
				exit = 0;
				exitY = 1 + rand() % (mid_y - 1);
				exitX = x - 1;
				way_out = "side";
			}
			room[exitY][exitX] = (char)32;
			if (way_in == "botom" && enter == 1)                        //if the entrance is DOWN
			{
				enter = 0;
				enterY = y - 1;
				enterX = 1 + rand() % (mid_x - 1);
			}
			if (way_in == "left" && enter == 1)							//... selected side exit
			{
				enter = 0;
				enterY = 1 + rand() % (y - 2);
				enterX = 0;
			}
			room[enterY][enterX] = (char)32;
		}
		for (int j = 0; j < y; j++)		//printing room
		{
			for (int d = 0; d < x; d++)
			{
				cout << room[j][d] << " ";
			}
			cout << endl;
		}
	}
};
class Hero			//here our hero starts
{
public:
	bool onexit = 0;
	double health = 100, damage = 5, defense = 1;  //HP, dmg, def
	int heal_ammount = 0, pos_X = 1, pos_Y = 1, bottle_ammount = 0;		//our heals/or food, position X, position Y
	string weapon = "fist", armour = "flesh";		//cosmetic attributes

	Hero(Map& map)		//this is constructor(it will get map object(maybe entrance with appearing hero))
	{
		system("cls");
		for (int j = 0; j < map.y; j++)
		{
			for (int d = 0; d < map.x; d++)
			{
				cout << map.room[j][d] << " ";
			}
			cout << endl;

		}
	};

	void move(string input, Map map)		//movement mechanic
	{
		if (input == "down") //	if our input down, our hero will move one square down 
		{
			if (pos_Y != map.enterY || pos_X != map.enterX)
				if (map.room[pos_Y][pos_X] == map.room[pos_Y + 1][pos_X]) //check for the walls: it checks what is inside the wall. If it is the same rhat our hero stands in, than hero goes on it	
					pos_Y++;
		}
		if (input == "left")
		{
			if (pos_X != map.enterX || pos_Y != map.enterY)
				if (map.room[pos_Y][pos_X] == map.room[pos_Y][pos_X - 1]) //same as the previous one
					pos_X--;
		}
		if (input == "up")
		{
			if (pos_Y != map.exitY || pos_X != map.exitX)
				if (map.room[pos_Y][pos_X] == map.room[pos_Y - 1][pos_X]) //same...
					pos_Y--;
		}
		if (input == "right")
		{
			if (pos_X != map.exitX || pos_Y != map.exitY)
				if (map.room[pos_Y][pos_X] == map.room[pos_Y][pos_X + 1]) //same...
					pos_X++;
		}
		system("cls");		//clears the console

		if (pos_X != map.exitX || pos_Y != map.exitY)
		{
			onexit = 0;

		}
		if (pos_X == map.exitX && pos_Y == map.exitY)
		{
			onexit = 1;
			cout << "You are on exit, press <Enter> for going next " << endl;

		}
		if (pos_X == map.enterX && pos_Y == map.enterY)
		{
			cout << "You are on enter door, press <Enter> for going back " << endl;
		}
		map.room[pos_Y][pos_X] = "H"; //our Hero symbol on the map
		for (int j = 0; j < map.y; j++) //prints our map, including our Hero movement
		{
			for (int d = 0; d < map.x; d++)
			{
				cout << map.room[j][d] << " ";
			}
			cout << endl;
		}
	}
	void death()
	{
		system("cls");
		cout << "YOU DIED" << endl;
		system("pause");
		exit(0);
	}
	void use_heal()
	{
		if (heal_ammount > 0)
		{
			heal_ammount--;
			if (health + 60 >= 100)
			{
				health = 100;

			}
			else
			{
				health += 60;
			}
			cout << " Your health: " << health << endl << " Your heals(food): " << heal_ammount << endl;
		}
		else
		{
			cout << "you have no heals :(" << endl;
		}
	}
};
class Monster
{
public:
	double health = 100, damage = 15;
	int Mpos_X, Mpos_Y;
	bool dead = false;
	void spawn(Map& map)
	{
		if (map.way_out == "side")
		{
			Mpos_X = map.exitX - 1;
			Mpos_Y = map.exitY;
		}
		else
		{
			Mpos_X = map.exitX;
			Mpos_Y = map.exitY + 1;
		}
		map.room[Mpos_Y][Mpos_X] = 'M'; //our Monster symbol on the map
	}

	void take_damage(double dmg, Map& map, Hero& hero) //Monster takes damage, and fighting back		
	{
		if (dead == false)
		{
			health = health - dmg;
			hero.health = hero.health - damage;
			if (hero.health <= 0)
			{
				hero.death();
			}
			if (health <= 0)
			{
				map.Monster_exist = false;
				map.room[Mpos_Y][Mpos_X] = " ";
				dead = true;
			}
		}
	}
};
class Item
{
public:
	string type;
	int Ipos_X, Ipos_Y;
	bool picked_up = false;
	Item(string type)
	{
		this->type = type;
	}
	void spawn_item(Map& map, Hero hero) //spawning item in the room
	{
		if (map.room_type == 1)
		{
			Ipos_X = 1 + rand() % (map.x - 2);
			Ipos_Y = 1 + rand() % (map.y - 2);
		}
		else if (map.room_type == 2)
		{
			Ipos_X = 1 + rand() % (map.mid_x - 1);
			Ipos_Y = 1 + rand() % (map.mid_y - 1);
		}
		if (type == "sword")
			map.room[Ipos_Y][Ipos_X] = "S";
		else if (type == "food")
			map.room[Ipos_Y][Ipos_X] = "F";
		else if (type == "bottle")
			map.room[Ipos_Y][Ipos_X] = "B";
	}
	void on_pick_up(Map& map, Hero& hero) //after picking up item it will choose the effect/type 
	{
		if (picked_up == false)
		{
			if (type == "sword")
			{
				hero.damage = 25, 0;
				map.room[Ipos_Y][Ipos_X] = " ";
				hero.move("", map);
				picked_up = true;
			}
			else if (type == "food")
			{
				hero.heal_ammount = hero.heal_ammount + 1;
				map.room[Ipos_Y][Ipos_X] = " ";
				hero.move("", map);
				picked_up = true;
			}
			else if (type == "bottle")
			{
				hero.bottle_ammount = hero.bottle_ammount + 1;
				map.room[Ipos_Y][Ipos_X] = " ";
				hero.move("", map);
				picked_up = true;
			}
		}
	}
};
int main()
{
	int room_id = 0;
	srand(time(0));
	Map map1(10, 10, 2, 1); //rooms are created here, transmitted (length X, length Y, exit type, room type)
	Map map2(12, 13, 1, 1);
	Map map3(12, 15, 2, 2);
	Map map4(15, 20, 1, 2);
	vector <Map> dungeon; //a vector of objects is being created here
	dungeon.push_back(map1); //rooms are entered in the vector
	dungeon.push_back(map2);
	dungeon.push_back(map3);
	dungeon.push_back(map4);
	int room_amount = 4;	//the size of the vector is setting here. Reminder(if i will change summ of rooms, then i should change amount here)
	dungeon.resize(room_amount);
	Monster m1, m2, m3, m4; //creating monsters, 1 monster per 1 room
	vector <Monster> monsters; //vector with monsters
	monsters.push_back(m1); //monsters are entered into the vector
	monsters.push_back(m2);
	monsters.push_back(m3);
	monsters.push_back(m4);

	dungeon[0].create_room();
	Hero Boy(dungeon[0]); //hero initialization

	char ch; //нужны для кода ниже
	int code;
	string way, coredore_side;
	Item sword("sword"); //creating sword
	Item food1("food"); //creating food/heal
	Item food2("food"); //creating food/heal
	Item food3("food"); //creating food/heal
	Item bottle1("bottle");
	Item bottle2("bottle");
	Item bottle3("bottle");
	Item bottle4("bottle");
	dungeon[0].items.push_back(bottle1);
	dungeon[1].items.push_back(bottle2);
	dungeon[2].items.push_back(bottle3);
	dungeon[3].items.push_back(bottle4);
	dungeon[0].items.push_back(sword); //objects are entered into the vector of objects, the vector is stored in the object, so each object has its own vector with objects.
	dungeon[0].items.push_back(food1);
	dungeon[0].items.push_back(food2);
	dungeon[0].items.push_back(food3);
	dungeon[0].create_room();
	for (int i = 0; i < dungeon[0].items.size(); i++) //spawning all predefined items
	{
		dungeon[0].items[i].spawn_item(dungeon[0], Boy);
	}

	Boy.pos_X = dungeon[room_id].enterX; //Sets the position of the hero to enter
	Boy.pos_Y = dungeon[room_id].enterY;
	Boy.move("", dungeon[room_id]);
	//Displays information about controls
	cout << "Use WASD for move" << endl << "Use E to pick up items " << endl << "Use F for attack monsters " << endl << "Use Enter for leave room" << endl << "Use I for showing your stats" << endl << "Use H for healing" << endl << "Use Esc for leave the game" << endl; //выводит информацию о том, что какая клавиша делает
	while (room_id != -1 && room_id < room_amount) //the controlled cycle will be repeated until the room_id becomes -1, or Hero reaches the last room 
	{
		if (&Boy != NULL) //checks for the existence(HP) of a hero
		{
			if (room_id != 0)
			{
				if (dungeon[room_id - 1].way_out == "up")
				{
					dungeon[room_id].way_in = "botom";
				}
				else
				{
					dungeon[room_id].way_in = "left";
				}
				dungeon[room_id].create_room();
				for (int a = 0; a < dungeon[room_id].items.size(); a++)
				{
					if (dungeon[room_id].items[a].picked_up == false)
						dungeon[room_id].items[a].spawn_item(dungeon[room_id], Boy);
				}
				if (dungeon[room_id].Monster_exist)
					monsters[room_id].spawn(dungeon[room_id]);
			}
			if (way == "in") //responsible for the position of the hero at the entrance of the next room, or at the exit of the previous one if he goes back
			{
				Boy.pos_X = dungeon[room_id].enterX;
				Boy.pos_Y = dungeon[room_id].enterY;
				Boy.move("", dungeon[room_id]);
			}
			else if (way == "back")
			{
				Boy.pos_X = dungeon[room_id].exitX;
				Boy.pos_Y = dungeon[room_id].exitY;
				Boy.move("", dungeon[room_id]);
			}
			way = "";
			while (room_id != -1) //controlled cycle, reads the pressed keys
			{
				ch = _getch();
				code = static_cast<int>(ch);
				if (ch == 27) //responsible for exiting the program
				{
					room_id = -1;
					break;
				}
				else if (ch == 115)
				{
					Boy.move("down", dungeon[room_id]); //responsible for moving down
				}
				else if (ch == 97)
				{
					Boy.move("left", dungeon[room_id]);//for moving left
				}
				else if (ch == 100)
				{
					Boy.move("right", dungeon[room_id]);//for moving right
				}
				else if (ch == 119)
				{
					Boy.move("up", dungeon[room_id]);//for moving up
				}
				if (ch == 13 && Boy.pos_X == dungeon[room_id].enterX && Boy.pos_Y == dungeon[room_id].enterY)//responsible for moving back between rooms
				{
					way = "back";
					room_id--;
					break;
				}
				if (ch == 13 && Boy.pos_X == dungeon[room_id].exitX && Boy.pos_Y == dungeon[room_id].exitY)//responsible for moving back and forth between rooms
				{
					way = "in";
					room_id++;
					break;
				} //the code below is responsible for dealing damage to the monster
				if (ch == 102 && (Boy.pos_X == monsters[room_id].Mpos_X + 1 || Boy.pos_X == monsters[room_id].Mpos_X - 1 || (Boy.pos_X == monsters[room_id].Mpos_X) && Boy.pos_Y == monsters[room_id].Mpos_Y + 1 || (Boy.pos_X == monsters[room_id].Mpos_X) && Boy.pos_Y == monsters[room_id].Mpos_Y - 1 || (Boy.pos_X == monsters[room_id].Mpos_X) && Boy.pos_Y == monsters[room_id].Mpos_Y))
				{
					monsters[room_id].take_damage(Boy.damage, dungeon[room_id], Boy);
					Boy.move("", dungeon[room_id]);
					cout << monsters[room_id].health << " monster health " << Boy.health << " Your health" << endl;
				}
				//responsible for picking up items in the room
				if (ch == 101)
				{
					for (int i = 0; i < dungeon[room_id].items.size(); i++)
					{
						if ((Boy.pos_X == dungeon[room_id].items[i].Ipos_X + 1 || Boy.pos_X == dungeon[room_id].items[i].Ipos_X - 1 || Boy.pos_X == dungeon[room_id].items[i].Ipos_X) && (Boy.pos_Y == dungeon[room_id].items[i].Ipos_Y || Boy.pos_Y == dungeon[room_id].items[i].Ipos_Y + 1 || Boy.pos_Y == dungeon[room_id].items[i].Ipos_Y - 1))
						{
							dungeon[room_id].items[i].on_pick_up(dungeon[room_id], Boy);
						}
					}
				}
				if (ch == 105) //responsible for getting information about the hero
				{
					Boy.move("", dungeon[room_id]);
					cout << "Health: " << Boy.health << endl << "Damage: " << Boy.damage << endl << "Food amount: " << Boy.heal_ammount << endl << "Bottles: " << Boy.bottle_ammount << endl;
				}
				if (ch == 104) //responsible for the use of food/heals
				{
					Boy.use_heal();
				}
				cout << code << endl;  //outputs the ascii code of the pressed key
			}
		}
	}
	//then the code that will be executed after passing the last room
	cout << "YOU WON :)" << endl;
}

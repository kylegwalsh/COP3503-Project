/*
 * combat.h
 *
 *  Created on: Dec 5, 2015
 *      Author: Kyle
 */

#ifndef COMBAT_H_
#define COMBAT_H_


bool Combat(Player *p, Enemy *e)
{
	string pAction;
	string eAttack;
	char n;

	//beginning of combat
	vector<string> vert;
	vert.push_back("|");
	cout << "======================================================================" << endl;

	//measure string length, output | then required number of spaces then text then spaces and |
	cout << vert[0];
	int spc = 68 - p->PrintCombatStats().length();
	int spc2 = spc / 2;
	if (spc % 2 == 0)
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << p->PrintCombatStats();
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	else
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << p->PrintCombatStats();
		for (int i = -1; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}

	cout << endl;

	cout << vert[0];
	spc = 68 - e->PrintEnemyStats().length();
	spc2 = spc / 2;
	if (spc % 2 == 0)
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << e->PrintEnemyStats();
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	else
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << e->PrintEnemyStats();
		for (int i = -1; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	cout << endl;
	e->PrintAscii();
	cout << vert[0] << "                                                                    " << vert[0] << endl;
	cout << vert[0] << "                                                                    " << vert[0] << endl;
	cout << vert[0] << "                     1. Attack  2. Eat  3. Flee                     " << vert[0] << endl;
	cout << "======================================================================" << endl;

	//enter loop for combat
	while (true)
	{
		n='0';

		while(n!='1'&&n!='2'&&n!='3'){
			n=getch();
		}

		ClearScrn();
		cout << endl << endl << endl << endl;

		//option 1. Attack
		if (n == '1')
		{
			pAction = p->Attack(e);
			eAttack = e->Attack(p);
		}
		//option 2. Eat
		if (n == '2')
		{
			pAction = p->Eat();
			eAttack = e->Attack(p);
		}
		//option 3. Flee
		if (n == '3')
		{
			return true;
		}

		//checks to see if player or enemy is dead
		if (p->GetHealth() == 0)
		{
			return false;
		}
		if (e->GetHealth() == 0)
		{
			p->GainExperience(e);
			return true;
		}

		cout << "======================================================================" << endl;

		//measure string length, output | then required number of spaces then text then spaces and |
		cout << vert[0];
		int spc = 68 - p->PrintCombatStats().length();
		int spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << p->PrintCombatStats();
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << p->PrintCombatStats();
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}

		cout << endl;

		cout << vert[0];
		spc = 68 - e->PrintEnemyStats().length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << e->PrintEnemyStats();
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << e->PrintEnemyStats();
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;
		e->PrintAscii();

		//print pAction
		cout << vert[0];
		spc = 68 - pAction.length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << pAction;
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << pAction;
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;

		//print eAttack
		cout << vert[0];
		spc = 68 - eAttack.length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << eAttack;
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << eAttack;
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;

		cout << vert[0] << "                     1. Attack  2. Eat  3. Flee                     " << vert[0] << endl;
		cout << "======================================================================" << endl;
	}
}

//a special combat loop for the final boss that allows him to drink haterade
bool FinalBossCombat(Player *p, Seminole *e)
{
	string pAction;
	string eAction;
	char n;

	//beginning of combat
	vector<string> vert;
	vert.push_back("|");
	cout << "======================================================================" << endl;

	//measure string length, output | then required number of spaces then text then spaces and |
	cout << vert[0];
	int spc = 68 - p->PrintCombatStats().length();
	int spc2 = spc / 2;
	if (spc % 2 == 0)
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << p->PrintCombatStats();
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	else
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << p->PrintCombatStats();
		for (int i = -1; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}

	cout << endl;

	cout << vert[0];
	spc = 68 - e->PrintEnemyStats().length();
	spc2 = spc / 2;
	if (spc % 2 == 0)
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << e->PrintEnemyStats();
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	else
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << e->PrintEnemyStats();
		for (int i = -1; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	cout << endl;
	e->PrintAscii();
	cout << vert[0] << "                                                                    " << vert[0] << endl;
	cout << vert[0] << "                                                                    " << vert[0] << endl;
	cout << vert[0] << "                     1. Attack  2. Eat  3. Flee                     " << vert[0] << endl;
	cout << "======================================================================" << endl;

	//enter loop for combat
	while (true)
	{
		n='0';

		while(n!='1'&&n!='2'&&n!='3'){
			n=getch();
		}

		ClearScrn();
		cout << endl << endl << endl << endl;

		//option 1. Attack
		if (n == '1')
		{
			pAction = p->Attack(e);
			eAction = e->Attack(p);
		}
		//option 2. Eat
		if (n == '2')
		{
			pAction = p->Eat();
			eAction = e->Attack(p);
		}
		//option 3. Flee
		if (n == '3')
		{
			return true;
		}

		//checks to see if player or enemy is dead
		if (p->GetHealth() == 0)
		{
			return false;
		}
		if (e->GetHealth() == 0)
		{
			if(e->GetHaterade()>0)
			{
				e->DrinkHaterade();
				eAction = "The Nole King drank some Haterade and became stronger!";
			}
			else
			{
				p->GainExperience(e);
				return true;
			}
		}

		cout << "======================================================================" << endl;

		//measure string length, output | then required number of spaces then text then spaces and |
		cout << vert[0];
		int spc = 68 - p->PrintCombatStats().length();
		int spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << p->PrintCombatStats();
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << p->PrintCombatStats();
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}

		cout << endl;

		cout << vert[0];
		spc = 68 - e->PrintEnemyStats().length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << e->PrintEnemyStats();
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << e->PrintEnemyStats();
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;
		e->PrintAscii();

		//print pAction
		cout << vert[0];
		spc = 68 - pAction.length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << pAction;
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << pAction;
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;

		//print eAttack
		cout << vert[0];
		spc = 68 - eAction.length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << eAction;
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << eAction;
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;

		cout << vert[0] << "                     1. Attack  2. Eat  3. Flee                     " << vert[0] << endl;
		cout << "======================================================================" << endl;
	}
}

#endif /* COMBAT_H_ */

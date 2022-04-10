#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

class Planet
{
public:
	string p_name;
	int p_number;
	int x, y, z;
	int weight, profit;
};

void knapsack(Planet p[], int n, int shipsize)
{
	int table[n + 1][shipsize + 1];
	int benefit = 0, weight = 0;

	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= shipsize; j++)
		{
			if (i == 0 || j == 0)
				table[i][j] = 0;
			else if (p[i - 1].weight <= j)
				table[i][j] = max(p[i - 1].profit + table[i - 1][j - p[i - 1].weight], table[i - 1][j]);
			else
				table[i][j] = table[i - 1][j];
		}
	}

	for (int k = 0; k <= n; k++)
	{
		cout << "Row " << k + 1 << ":   " << endl;
		for (int i = 0; i <= 80; i++)
		{
			cout << table[k][i] << " ";
		}
		cout << endl
			 << endl;
	}

	cout << "******************************************" << endl;
	cout << "|  Selected  |   Planet   |    Planet    |" << endl;
	cout << "|   Planet   |   Weight   |    Profit    |" << endl;
	cout << "******************************************" << endl;
	for (int i = 10; i > 1; i--)
	{
		if (table[i][shipsize] != table[i - 1][shipsize])
		{
			cout << "|  " << p[i - 1].p_name << "  |\t   " << p[i - 1].weight << " \t  | \t" << p[i - 1].profit << "\t |" << endl;
			benefit = benefit + p[i - 1].profit;
			weight = weight + p[i - 1].weight;
			shipsize = shipsize - p[i - 1].weight;
		}
	}
	cout << "******************************************" << endl;
	cout << "|   Total    |     " << weight << "     | \t" << benefit << "\t |" << endl;
	cout << "******************************************" << endl;
}

void displayPlanets(Planet p[], int n)
{
	cout << "**********************************************************" << endl;
	cout << "|    Planet      Coordinates     Weight     Profit       |" << endl;
	cout << "**********************************************************" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "|" << p[i].p_number << ": " << p[i].p_name << "\t(" << p[i].x << "," << p[i].y << "," << p[i].z << ") \t   " << p[i].weight << "\t     " << p[i].profit << "  \t |" << endl;
	}
	cout << "**********************************************************" << endl
		 << endl;
}

void readPlanets(Planet p[])
{
	fstream newfile;

	newfile.open("A2Planets.txt", ios::in);
	if (newfile.is_open())
	{
		string tp;
		int whitespace, i, j = 0;
		while (getline(newfile, tp))
		{
			string ns, xs, ys, zs, ws, ps;
			i = 0;
			whitespace = 0;
			while (tp[i] != '\0')
			{
				if (tp[i] == ' ')
				{
					whitespace++;
					i++;
				}
				if (whitespace == 0)
					ns = ns + tp[i];
				else if (whitespace == 1)
					xs = xs + tp[i];
				else if (whitespace == 2)
					ys = ys + tp[i];
				else if (whitespace == 3)
					zs = zs + tp[i];
				else if (whitespace == 4)
					ws = ws + tp[i];
				else if (whitespace == 5)
					ps = ps + tp[i];
				i++;
			}
			p[j].p_name = ns;
			p[j].p_number = j;
			p[j].x = stoi(xs);
			p[j].y = stoi(ys);
			p[j].z = stoi(zs);
			p[j].weight = stoi(ws);
			p[j].profit = stoi(ps);
			j++;
		}
		newfile.close();
	}
}

int main()
{
	const int n = 10;
	Planet p[n];
	int shipsize = 80;

	readPlanets(p);
	displayPlanets(p, n);

	knapsack(p, n, shipsize);

	return 0;
}

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "Program_2.hpp"

using namespace std;

bool readPlanets(string filename, Planet *p, const int n)
{
	ifstream file;

	file.open(filename);
	if (!file.is_open())
		return false;

	for (int i = 0; i < n; i++)
	{
		file >> p[i].p_name >> p[i].x >> p[i].y >> p[i].z >> p[i].weight >> p[i].profit;
		p[i].p_number = i;
	}
	file.close();
	return true;
}

bool readGraph(string filename, Planet *p, Edge *e, int &edgecount)
{
	ifstream file;

	file.open(filename);
	if (!file.is_open())
		return false;

	file >> edgecount;
	for (int i = 0; i < edgecount; i++)
    {
        file >> e[i].planet1 >> e[i].planet2;
        e[i].distance = sqrt(pow(p[e[i].planet2].x - p[e[i].planet1].x, 2) + pow(p[e[i].planet2].y - p[e[i].planet1].y, 2) + pow(p[e[i].planet2].z - p[e[i].planet1].z, 2));
    }
	file.close();
	return true;
}

void planetInfo(Planet *p, const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << right;
		cout << i << ":";
		cout << p[i].p_name << " ";
		cout << "(" << setw(3) << p[i].x << ", ";
		cout << setw(3) << p[i].y << ", ";
		cout << setw(3) << p[i].z << left << ") ";
		cout << "Distance= " << setw(4) << p[i].distance << " ";
		cout << "Predecessor= " << setw(2) << p[i].predecessor << endl;
	}
}

void dijkstra(Edge *e, int edgecount, Planet *p, int n, int start)
{
	int curr, next, shortest, nextStart, totaldis;

	p[0].distance = 0;
	p[0].predecessor = -1;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < edgecount; j++)
		{
			curr = e[j].planet1;
			next = e[j].planet2;
			if (next == start)
				swap(curr, next);

			totaldis = p[curr].distance + e[j].distance;
			if (curr == start && !p[next].visited)
			{
				if (totaldis < p[next].distance)
				{
					p[next].distance = totaldis;
					p[next].predecessor = p[curr].p_number;
				}
			}
		}
		p[start].visited = true;
		shortest = 100000;
		for (int j = 0; j < n; j++)
		{
			if (p[j].distance < shortest && !p[j].visited)
			{
				shortest = p[j].distance;
				nextStart = p[j].p_number;
			}
		}
		start = nextStart;
	}
}

void drawGraph(Planet *p, const int n)
{
	int planets[10][2] = {{4, 4}, {6, 2}, {2, 2}, {4, 6}, {8, 7}, {8, 0}, {0, 0}, {0, 7}, {2, 8}, {6, 8}};
	int x, y, destx, desty, prev, xmove, ymove, xoffset, yoffset;
	char map[10][10] = {0};
	char p_name = 'A';

	//set planets location
	for (int i = 0; i < n; i++)
	{
		x = planets[i][0];
		y = planets[i][1];

		map[x][y] = p_name;
		p_name++;
	}

	//set path symbols
	for (int i = 1; i < 10; i++)
	{
		x = planets[i][0];
		y = planets[i][1];

		prev = p[i].predecessor;
		destx = planets[prev][0];
		desty = planets[prev][1];

		xmove = destx - x;
		if (xmove < 0)
			xoffset = -1;
		else
			xoffset = 1;

		ymove = desty - y;
		if (ymove < 0)
			yoffset = -1;
		else
			yoffset = 1;

		if (xmove != 0)
		{
			xmove += xoffset;
			while(xmove != 0)
			{
				if (!(map[x][y] >= 'A' && map[x][y] <= 'J'))
				{
					if ((xmove == 1 || xmove == -1) && ymove != 0)
						map[x][y] = '+';
					else
						map[x][y] = '-';
				}

				x += xoffset;
				xmove += -xoffset;
			}
			x += -xoffset;
		}

		if (ymove != 0)
		{
			y += yoffset;
			ymove += -yoffset;

			while(ymove != 0)
			{
				if (!(map[x][y] >= 'A' && map[x][y] <= 'J'))
				{
					if (map[x][y] != '+')
						map[x][y] = '|';
				}
				y += yoffset;
				ymove += -yoffset;
			}
		}
	}

	//print graph
	for (int j = 0; j < 10; j++)
	{
		cout << endl;
		for (int i = 0; i < 10; i++)
		{
			if (map[i][j] == 0)
				cout << " ";
			else
				cout << map[i][j];
		}
	}
}

int main()
{
	const int n = 10;
	Planet p[n];

	if (!readPlanets("A2planets.txt", p, n))
	{
		cout << "Could not open planets file\n";
		return 0;
	}

	const int maxedge = 15;
	Edge e[maxedge];
	int edgecount;

	if (!readGraph("Edges.txt", p, e, edgecount))
	{
		cout << "Could not open edges file\n";
		return 0;
	}

	dijkstra(e, edgecount, p, n, 0);
	planetInfo(p, n);
	drawGraph(p, n);

	return (0);
}

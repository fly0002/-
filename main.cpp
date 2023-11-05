#include<iostream>

using namespace std;
#include<easyX.h>

#include<vector>
#include<ctime>
#define wide 1400
#define high 800
ExMessage msg;
DWORD t1=0,t2=0;

class gezi
{
public:
	void moveby(int x, int y)
	{

		m_x=(m_x += x)%wide;
		m_y =(m_y+= y)%high;
		if (m_y < 0)
			m_y += high;
		if (m_x < 0)
			m_x += wide;
	}
	bool peng(gezi& other)
	{
		return m_x == other.m_x && m_y == other.m_y;
	}
	virtual void print()
	{
		setfillcolor(RED);
		fillrectangle(m_x, m_y, m_x+20, m_y+20);


	}
	gezi():gezi(0,0) {};
	gezi(int x,int y):m_x(x),m_y(y),color(RED){}
public:
	int m_x;
	int m_y;
	COLORREF color;

};
class FOOD :public gezi
{
public:
	FOOD() {
		m_x = rand() % (wide / 20) * 20;
		m_y = rand() % (high / 20) * 20;
	}
	void print()
	{
		setfillcolor(BLUE);
		fillrectangle(m_x, m_y, m_x + 20, m_y + 20);
	}

	void newfood()
	{
		m_x = rand() % (wide / 20) * 20;
		m_y = rand() % (high / 20) * 20;
	}
	
};
class snake:public gezi 
{
public:

	void islife()
	{
		for (int i = 1; i < nodes.size(); i++)
		{
			if (nodes[i].m_x == nodes[0].m_x && nodes[i].m_y == nodes[0].m_y)
			{
				HWND hnd = GetHWnd();
				int isok = MessageBox(hnd, "很遗憾，你输了！\n是否再来一局", "游戏结束", MB_OK);
				if (isok == IDOK)
				{
					nodes.clear();
					cntdir = VK_LEFT;
					nodes.push_back(gezi(20, 0));
					nodes.push_back(gezi(40, 0));
					nodes.push_back(gezi(60, 0));
					
					
				}
			}
		}
	}
	snake() :snake(0,0){}
	snake(int x,int y):gezi(x,y) ,cntdir(VK_LEFT){
		
		nodes.push_back(gezi(20, 0));
		nodes.push_back(gezi(40, 0));
		nodes.push_back(gezi(60, 0));

	}
	void zlong()
	{
		nodes.push_back(gezi());
	}
	void print()
	{
		
		for (int i = 0; i < nodes.size(); i++)
		{
			nodes[i].print();
			setfillcolor(CYAN);
			fillrectangle(nodes[0].m_x, nodes[0].m_y, nodes[0].m_x + 20, nodes[0].m_y + 20);
		}
	}
	void run()
	{
		for (int i = nodes.size() - 1; i > 0; i--)
		{
			nodes[i] = nodes[i - 1];
		}
		switch (dir)
		{
		case VK_UP:
			if (cntdir != VK_DOWN)
				cntdir = dir;
			break;
		case VK_DOWN:
			if (cntdir != VK_UP)
				cntdir = dir;
			break;
		case VK_RIGHT:
			if (cntdir != VK_LEFT)
				cntdir = dir;
			break;
		case VK_LEFT:
			if (cntdir != VK_RIGHT)
				cntdir = dir;
			break;

		}
		switch(cntdir)
		{

		case VK_UP:
			nodes[0].moveby(0, -20);
			break;
		case VK_DOWN:
			nodes[0].moveby(0, +20);
			break;
		case VK_RIGHT:
			nodes[0].moveby(20, 0);
			break;
		case VK_LEFT:
			nodes[0].moveby(-20, 0);
			break;

		}
		
		islife();
		
	}
	void move()
	{
		peekmessage(&msg, EX_KEY);
		dir = msg.vkcode;
		
	}
public:
	int dir;
	int cntdir;
	vector<gezi> nodes;
	
};
int main()
{
	srand(time(nullptr));
	initgraph(1400,800);
	
	snake gz;
	FOOD food;
	food.newfood();
	
	
	while(1)
	{
		
		BeginBatchDraw();
		cleardevice();
		food.print();
		gz.print();
		
		EndBatchDraw();
		gz.move();
		t1 = GetTickCount();
		if (t1 - t2 > 100)
		{
			t2 = t1;
			gz.run();
		}
		if (food.peng(gz.nodes[0]))
		{
			t1 = t2;
			gz.zlong();
			food.newfood();

		}
	}
	
	
	return 0;
}
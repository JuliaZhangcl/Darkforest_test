/*
dan<5 kind
5<=dan<=8 rand
dan>8 kill

sci<=15 原始时代
15<sci<=25 科学时代 
25<sci<=30 核能时代
30<sci<=35 电磁时代
35<sci<=45 星舰时代 
45<sci<=50 引力波时代 
50<sci<=60 微观时代 
60<sci<=80 曲率时代
80<sci<=100 光粒/奇点炸弹时代
sci>100 归零时代 
*/
#include<bits/stdc++.h>
using namespace std;

const int SIZE=105;
struct Node
{
	int killer;//猎物 
	int t,x;
};
struct happen
{
	int a,b;//猎人 猎物 
	int x,t;
	int way;//-1战争 0交流 1二向箔 2光粒 3奇点炸弹 4光墓 
};
struct civ
{
	char name[20];//名字 
	bool alive;
	int x;//坐标 
	int start;//诞生时间 
	double sci;//技术值 
	double b,bb;//技术爆炸指数 
	int dan;//危险指数 1~10
	bool hide;//是否建造黑域
	bool kill;//需要用二向箔清理否 01
	int act;//积极度 1~5
	unsigned long long force;//实力 
	int star;//是否成为星际文明及速度 
	vector<int> hunt;//发现了谁 
};
civ c[SIZE];//文明 
Node q[SIZE*SIZE];//黑暗森林广播 
int st=0,ed=0;
happen h[SIZE*SIZE];//事件 
int head=0,tail=0;
int Time;
//a广播b，a发现b，a对b沉默（暂无用），a毁灭b，a与b交流，a攻击b 
bool f[SIZE][SIZE],ff[SIZE][SIZE],clam[SIZE][SIZE],kill[SIZE][SIZE],talk[SIZE][SIZE];
bool KILL(int a,int b)//a毁灭b
{
	if(c[a].sci>100&&c[b].kill&&c[b].star==0&&c[a].force>=1000)
	{
		printf("%s文明向%s文明发射了二向箔\n",c[a].name,c[b].name);
		kill[a][b]=1;
		h[tail]=(happen){a,b,c[a].x,Time,1};
		c[a].force-=10;
		tail++;
		return 1;
	}
	else if(c[a].sci>80&&!c[b].kill&&c[b].star==0&&c[a].force>=1000)
	{
		if(rand()%2==0)
		{
			printf("%s文明向%s文明发射了光粒\n",c[a].name,c[b].name);
			h[tail]=(happen){a,b,c[a].x,Time,2};
		}
		else
		{
			printf("%s文明向%s文明发射奇点炸弹\n",c[a].name,c[b].name);
			h[tail]=(happen){a,b,c[a].x,Time,3};
		}
		kill[a][b]=1;
		c[a].force-=5;
		tail++;
		return 1;
	}
	else if(c[a].sci>60&&c[b].sci<=30&&!c[b].kill&&rand()%3==0&&c[a].star!=0&&c[a].force>=500)
	{
		h[tail]=(happen){a,b,c[a].x,Time,4};
		tail++;
		kill[a][b]=1;
		printf("%s文明向%s文明的方向驶去\n",c[a].name,c[b].name);
		c[a].force-=3;
		if(c[a].x>c[b].x)
			c[a].star=-1;
		else
			c[a].star=1;
		return 1;
	}
	return 0;
}
int main()
{
	bool flag;
	srand(time(0));
	freopen("darkforest.in.txt","r",stdin);
	freopen("darkforest.out.txt","w",stdout);
	int n;
	cin>>n;
	Time=0;
	for(int i=1;i<=n;i++)
	{
		//输入信息：名字，诞生时间，技术爆炸指数，危险指数，积极度，需要用二向箔清理否，坐标
		scanf("%s",c[i].name);
		cin>>c[i].start>>c[i].b>>c[i].bb>>c[i].dan>>c[i].act>>c[i].kill>>c[i].x;
		c[i].alive=1;
		c[i].sci=0;
		c[i].force=0;
	}
	int num=n,len=0;
	while(num>1)
	{
		Time++;
		flag=0;
		while(len<n&&c[len+1].start==Time)
		{
			len++;
			flag=1;
			printf("%s文明诞生\n",c[len].name);
		}
		if(rand()%(100/len)==0&&len>1)//文明被发现
		{
			int a=rand()%len+1,tri=1;
			while((c[a].sci<=5||!c[a].alive||c[a].hide||rand()%(6-c[a].act)==0)&&tri<10)
			{
				a=rand()%len+1;
				tri++;
			}
			if(tri<10)
			{
				tri=1;
				int b=rand()%len+1;
				while((c[b].sci<=5||!c[b].alive||c[b].hide||a==b)&&tri<10)
				{
					b=rand()%len+1;
					tri++;
				}
				if(tri<10&&!ff[a][b])
				{
					ff[a][b]=1;
					c[a].hunt.push_back(b);
					flag=1;
					printf("%s文明发现%s文明\n",c[a].name,c[b].name);
				}
			}
		}
		for(int i=head;i<tail;i++)
		{
			if(!c[h[i].a].alive||c[h[i].a].hide)
				continue; 
			if(!c[h[i].b].alive||c[h[i].b].hide)
				continue; 
			if(h[i].way==-1)
			{
				if(c[h[i].a].x==c[h[i].b].x)
					c[h[i].a].star=c[h[i].b].star;
				if(c[h[i].a].force<=0||c[h[i].b].force<=0)
				{
					if(c[h[i].b].force<=0)
					{
						printf("%s文明在战争中获胜，%s文明毁灭\n",c[h[i].a].name,c[h[i].b].name);
						flag=1;
						c[h[i].b].alive=0;
					}
					else if(c[h[i].a].force<=0)
					{
						printf("%s文明在战争中获胜，%s文明毁灭\n",c[h[i].b].name,c[h[i].a].name);
						flag=1;
						c[h[i].a].alive=0;
					}
				}
				else
				{
					double fa=c[h[i].a].force,fb=c[h[i].b].force;
					c[h[i].a].force-=rand()%1000000/1000000.0*fb;
					c[h[i].b].force-=rand()%1000000/1000000.0*fa;
				}
			}
			else if(h[i].way==4)
			{
				if(c[h[i].a].x==c[h[i].b].x&&c[h[i].b].star==0)
				{
					printf("%s文明将%s文明的星系改造成光墓，%s文明再也无法逃出\n",c[h[i].a].name,c[h[i].b].name,c[h[i].b].name);
					flag=1;
					c[h[i].b].hide=1;
					c[h[i].b].b=0;
					c[h[i].a].force-=20;
				}
			}
			else if(abs(h[i].x-c[h[i].b].x)==Time-h[i].t)
			{
				if(h[i].way==0)
				{
					if(!ff[h[i].b][h[i].a])
					{
						ff[h[i].b][h[i].a]=1;
						c[h[i].b].hunt.push_back(h[i].a);
						flag=1;
						printf("%s文明接收到了%s文明的信息，得知%s文明的存在\n",c[h[i].b].name,c[h[i].a].name,c[h[i].a].name);
					}
				}
				else if(h[i].way==1&&c[h[i].b].star==0)
				{
					printf("%s文明发射的二向箔抵达%s文明的星系，%s文明成为了宇宙中的一幅画\n",c[h[i].a].name,c[h[i].b].name,c[h[i].b].name);
					flag=1;
					c[h[i].b].alive=0;
				}
				else if(h[i].way==2&&c[h[i].b].star==0)
				{
					printf("%s文明发射的光粒抵达%s文明的星系，%s文明在恒星的爆炸中毁灭\n",c[h[i].a].name,c[h[i].b].name,c[h[i].b].name);
					flag=1;
					c[h[i].b].alive=0;
				}
				else if(h[i].way==3&&c[h[i].b].star==0)
				{
					printf("%s文明发射的奇点炸弹抵达%s文明的星系，%s文明被吸入黑洞\n",c[h[i].a].name,c[h[i].b].name,c[h[i].b].name);
					flag=1;
					c[h[i].b].alive=0;
				}
			}
		}
		while((!c[h[head].b].alive||c[h[head].b].hide)&&(head<tail))
			head++;
		for(int i=1;i<=len;i++)
		{
			if(!c[i].alive)
				continue;
			if(c[i].hide)
				continue;
			c[i].sci+=c[i].b;
			c[i].b*=(1.0+c[i].bb);
			c[i].x+=c[i].star;
			c[i].force+=rand()%1000000/100000.0*c[i].sci;
			if(c[i].sci>30&&rand()%20==0&&c[i].star==0&&c[i].force>=10000)//星舰文明 
			{
				if(rand()%2==0)
					c[i].star=1;
				else
					c[i].star=-1;
				printf("%s文明成为星舰文明，游荡在星海中\n",c[i].name);
				flag=1;
			}
			if(c[i].dan>8||(c[i].dan>=5&&rand()%3==0))//清理 
			{
				for(int j=st;j<ed;j++)
					if(c[q[j].killer].alive&&q[j].killer!=i&&!c[q[j].killer].hide&&abs(c[i].x-q[j].x)<=Time-q[j].t&&!kill[i][q[j].killer])
					{
						if(KILL(i,q[j].killer))
							flag=1;
					}
				while(!c[q[st].killer].alive&&st<ed)
					st++;
			}
			for(int j=0;j<c[i].hunt.size();j++)
			{
				int befound=c[i].hunt[j];
				if(!c[befound].alive||c[befound].hide)
					continue;
				if(c[i].dan>8||(c[i].dan>5&&rand()%4==0))//毁灭
				{
					if(!c[befound].star&&!kill[i][befound])
					{
						if(KILL(i,befound))
							flag=1;
						else if((c[i].sci>45||(c[i].sci>30&&c[i].kill))&&!f[i][befound]&&c[i].force>=100)
						{
							q[ed].killer=befound;
							f[i][befound]=1;
							ed++;
							flag=1;
							printf("%s文明广播%s文明的坐标\n",c[i].name,c[befound].name);
						}
					}
					else if(c[i].star&&c[befound].star)
					{
						bool flagg=1;
						for(int j=head;j<tail;j++)
							if((h[j].a==i&&h[j].b==befound)||(h[j].a==befound&&h[j].b==i))
							{
								flagg=0;
								break;
							}
						if(flagg)
						{
							h[tail]=(happen){i,befound,c[i].x,Time,-1};
							tail++;
							flag=1;
							printf("%s文明向%s文明攻击，一场宇宙战争开始了\n",c[i].name,c[befound].name);
							if(c[i].x>c[befound].x)
								c[i].star=-1;
							else
								c[i].star=1;
							c[befound].star=-c[i].star;
						}
					}
				}
				else if(c[i].dan<=4&&c[i].sci>20&&(!talk[i][befound]||rand()%20==0))//交流
				{
					talk[i][befound]=1;
					flag=1;
					h[tail]=(happen){i,befound,c[i].x,Time,0};
					tail++;
					printf("%s文明与%s文明交流\n",c[i].name,c[befound].name);
					c[i].force--;
				}
/*				else//沉默
				{
					if(!clam[i][befound])
					{
						clam[i][befound]=1;
						flag=1;
						printf("%d号文明对%d号文明保持了沉默\n",i,befound);
					}
				}*/ 
			}
			if(c[i].sci>60&&!c[i].hide&&c[i].dan>=7&&c[i].dan+rand()%100+rand()%100>=205&&c[i].star==0)//宇宙安全声明 
			{
				c[i].hide=1;
				flag=1;
				printf("%s文明为自己建造了黑域，从此与世隔绝\n",c[i].name);
				c[i].b=0;
				c[i].force-=20;
			}
			if(rand()%20==0)
				c[i].dan++;
		}
		num=0;
		for(int i=1;i<=n;i++)
			if(c[i].alive&&!c[i].hide)
				num++;
		if(flag)
			printf("\t——第%d世纪记录\n\n",Time);
	}
	cout<<"存活者：";
	for(int i=1;i<=len;i++)
		if(c[i].alive)
		{
			printf("%s文明",c[i].name);
			if(c[i].hide)
				printf("（黑域）");
			printf(" ");
		}
	cout<<"\n\n";
	return 0;
}
/*
宇宙社会学公理：
第一，生存是文明的第一需要
第二，文明不断增长和扩张，但宇宙中的物质总量保持不变
First, survival is the primary need of civilization.
Second, civilization continuously grows and expands, but the total matter in the universe remains constant.

宇宙就是一座黑暗森林，每个文明都是带枪的猎人，像幽灵般潜行于林间，轻轻拨开挡路的树枝，竭力不让脚步发出一点儿声音
，连呼吸都小心翼翼；他必须小心，因为林中到处都有和他一样潜行的猎人。如果他发现了别的生命，能做的只有一件事：开枪
消灭之。在这片森林中，他人就是地狱，就是永恒的威胁，任何暴露自己存在的生命都将很快被消灭。这就是宇宙文明的图景，
这就是对费米悖论的解释。 
The universe is a dark forest. Every civilization is an armed hunter stalking through the trees like a ghost, 
gently pushing aside branches that block the path and trying to tread without sound. Even breathing is done with 
care. The hunter has to be careful, because everywhere in the forest are stealthy hunters like him. If he finds 
other life—another hunter, an angel or a demon, a delicate infant or a tottering old man, a fairy or a demigod—
there's only one thing he can do: open fire and eliminate them. In this forest, hell is other people. An eternal 
threat that any life that exposes its own existence will be swiftly wiped out. This is the picture of cosmic 
civilization. It's the explanation for the Fermi Paradox.
*/

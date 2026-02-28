#include<bits/stdc++.h>
using namespace std;

int main()
{
	freopen("darkforest.in.txt","w",stdout);
	srand(time(0));
	int n,time=1,t;
	cin>>n;
	cout<<n<<endl;
	for(int i=1;i<=n;i++)
	{
		//输入信息：名字，诞生时间，技术爆炸指数，危险指数，积极度，需要用二向箔清理否，坐标
		cout<<i<<"号 "<<time<<' '<<rand()%100/100.0<<' '<<rand()%100/1000.0<<' '<<rand()%10+1<<' '<<rand()%5+1;
		if(rand()%10==0)
			cout<<' '<<1<<' ';
		else
			cout<<' '<<0<<' ';
		cout<<rand()%1000<<endl;
		t=rand()%100;
		time+=t;
	}
	return 0;
}


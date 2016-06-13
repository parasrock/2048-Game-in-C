#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
long value[4][4];
long undo[4][4];
FILE *fp,*pause;
char *ch,name[50];
long total=0;
int z=0,totaltrans=0;
void doundo(int i)
{
	undo[0][i]=value[0][i];
	undo[1][i]=value[1][i];
	undo[2][i]=value[2][i];
	undo[3][i]=value[3][i];
}
void result()
{
	setfillstyle(SOLID_FILL,BLUE);
	bar(200,200,400,330);
	setfillstyle(SOLID_FILL,BLACK);
	bar(220,280,380,320);
	outtextxy(265,220,"WELL DONE!");
	outtextxy(210,250,"Enter name : ");
	gotoxy(30,20);
	gets(name);
	fp=fopen("2048.txt","a");
	fprintf(fp,"%s\n",name);
	fprintf(fp,"%ld\n",total);
}
long getnum(char st[])
{
	long num=0;
	int i=0;
	for(i=0;i<strlen(st);i++)
	{
		if(st[i]=='1')
			num=10*num+1;
		else if(st[i]=='2')
			num=10*num+2;
		if(st[i]=='3')
			num=10*num+3;
		else if(st[i]=='4')
			num=10*num+4;
		if(st[i]=='5')
			num=10*num+5;
		else if(st[i]=='6')
			num=10*num+6;
		if(st[i]=='7')
			num=10*num+7;
		else if(st[i]=='8')
			num=10*num+8;
		if(st[i]=='9')
			num=10*num+9;
		else if(st[i]=='0')
			num=10*num+0;
	}
	return num;
}
void getvalue(long x)
{
	int k=0;
	if(x==0)
		strcpy(ch,"");
	while(x>0)
	{
		switch(x%10)
		{
			case 0:ch[k++]='0';
			break;
			case 1:ch[k++]='1';
			break;
			case 2:ch[k++]='2';
			break;
			case 3:ch[k++]='3';
			break;
			case 4:ch[k++]='4';
			break;
			case 5:ch[k++]='5';
			break;
			case 6:ch[k++]='6';
			break;
			case 7:ch[k++]='7';
			break;
			case 8:ch[k++]='8';
			break;
			case 9:ch[k++]='9';
			break;
		}
		x=x/10;
		ch[k]='\0';
	}
	strrev(ch);
}
void getgame(FILE *pause)
{
	int i=0,j=0,k=0,ff=0;
	char c,st[10];
	while(1)
	{
		c=fgetc(pause);
		if(c==EOF)
			break;
		else if(c==' ')
		{
			i=0;
			value[j][k]=getnum(st);
			k++;
			if(k>3)
			{
				j++;
				k=0;
			}
		}
		else if(c=='\n')
			i=0;
		else
		{
			st[i++]=c;
			st[i]='\0';
		}
	}
	total=getnum(st);
}
void showscore()
{
	typedef struct score
	{
		char name[50];
		long total;
		struct score *next;
	}s;
	struct score *start=NULL,*temp,*ptr,*pptr;
	char c,*string,demo[50];
	int i=0,x=0,a,b,xx;
	FILE *ft;
	ft=fopen("2048.txt","r");
	while(1)
	{
		c=fgetc(ft);
		if(c==EOF)
			break;
		if(x==0 && i==0)
		{
			temp=(s *)malloc(sizeof(s));
			temp->next=NULL;
		}
		if(c=='\n')
		{
			x++;
			if(x%2!=0)
			{
				i=0;
			}
			else
			{
				i=0;
				temp->total=getnum(string);
				if(start==NULL)
					start=temp;
				else
				{
					ptr=start;
					while(ptr->next!=NULL)
						ptr=ptr->next;
					ptr->next=temp;
				}
				temp=(s *)malloc(sizeof(s));
				temp->next=NULL;
			}
		}
		else
		{
			if(x%2==0)
			{
				temp->name[i++]=c;
				temp->name[i]='\0';
			}
			else
			{
				string[i++]=c;
				string[i]='\0';
			}
		}
	}
	ptr=start;
	while(ptr!=NULL)
	{
		pptr=start;
		while(pptr->next!=NULL)
		{
			if(pptr->total<pptr->next->total)
			{
				pptr->total+=pptr->next->total;
				pptr->next->total=pptr->total-pptr->next->total;
				pptr->total-=pptr->next->total;
				strcpy(demo,pptr->name);
				strcpy(pptr->name,pptr->next->name);
				strcpy(pptr->next->name,demo);
			}
			pptr=pptr->next;
		}
		ptr=ptr->next;
	}
	ptr=start;
	cleardevice();
	a=50;
	b=100;
	xx=0;
	outtextxy(200,50,"Show High Score");
	while(ptr!=NULL && xx<5)
	{
		outtextxy(a,b,ptr->name);
		getvalue(ptr->total);
		outtextxy(a+200,b,ch);
		b=b+40;
		xx++;
		ptr=ptr->next;
	}
}
void blockcolor(int a,int b,int x)
{
	if(x!=0)
	{
		setcolor(BLACK);
		switch(x%16384)
		{
			case 2:setfillstyle(SOLID_FILL,BLUE);
			break;
			case 4:setfillstyle(SOLID_FILL,GREEN);
			break;
			case 8:setfillstyle(SOLID_FILL,CYAN);
			break;
			case 16:setfillstyle(SOLID_FILL,WHITE);
			break;
			case 32:setfillstyle(SOLID_FILL,MAGENTA);
			break;
			case 64:setfillstyle(SOLID_FILL,BROWN);
			break;
			case 128:setfillstyle(SOLID_FILL,LIGHTGRAY);
			break;
			case 256:setfillstyle(SOLID_FILL,DARKGRAY);
			break;
			case 512:setfillstyle(SOLID_FILL,LIGHTBLUE);
			break;
			case 1024:setfillstyle(SOLID_FILL,LIGHTGREEN);
			break;
			case 2048:setfillstyle(SOLID_FILL,LIGHTCYAN);
			break;
			case 4096:setfillstyle(SOLID_FILL,LIGHTRED);
			break;
			case 8192:setfillstyle(SOLID_FILL,LIGHTMAGENTA);
			break;
			case 0:setfillstyle(SOLID_FILL,YELLOW);
			break;
		}
		bar(a,b,a+43,b+43);
	}
}
void game()
{
	int i,j,a,b,flag=0,f=0,l,m,getpause=0;
	char key;
	pause=fopen("pause.txt","r");
	if(pause!=NULL)
	{
		getgame(pause);
		getpause=1;
	}
	else
		fclose(pause);
	do
	{
		cleardevice();
		setfillstyle(SOLID_FILL,RED);
		setbkcolor(BLACK);
		pause=fopen("pause.txt","w");
		setcolor(YELLOW);
		getvalue(total);
		outtextxy(220,400,"Total score : ");
		outtextxy(350,400,ch);
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				if(value[i][j]==0)
				{
					f=0;
					break;
				}
				else
					f=1;
			}
			if(f==0)
				break;
		}
		if(f==1)
		{
			fclose(pause);
			remove("pause.txt");
			result();
			break;
		}
		if(flag!=1 && getpause!=1)
		{
			totaltrans++;
			while(1)
			{
				i=rand()%4;
				j=rand()%4;
				if(value[i][j]==0)
				{
					value[i][j]+=2;
					break;
				}
				else
					continue;
			}
		}
		getpause=0;
		bar(200,150,380,330);
		setcolor(BLACK);
		line(245,150,245,330);
		line(290,150,290,330);
		line(335,150,335,330);
		line(200,195,380,195);
		line(200,240,380,240);
		line(200,285,380,285);
		//For navigation hint
		setcolor(WHITE);
		line(600,200,600,210);
		line(600,200,597,203);
		line(600,200,603,203);
		outtextxy(598,190,"W");
		line(600,220,600,230);
		line(600,230,597,227);
		line(600,230,603,227);
		outtextxy(598,233,"S");
		line(580,215,590,215);
		line(580,215,583,212);
		line(580,215,583,218);
		outtextxy(571,211,"A");
		line(610,215,620,215);
		line(620,215,617,212);
		line(620,215,617,218);
		outtextxy(623,211,"D");
		outtextxy(560,250,"q/Q - QUIT");
		setcolor(YELLOW);
		for(i=0,a=170,l=151;i<4;i++,a+=45,l+=45)
			for(j=0,b=205,m=201;j<4;j++,b+=45,m+=45)
			{
				getvalue(value[i][j]);
				if(pause!=NULL)
					fprintf(pause,"%ld ",value[i][j]);
				blockcolor(m,l,value[i][j]);
				setcolor(BLACK);
				outtextxy(b,a,ch);
			}
		fprintf(pause,"\n%ld",total);
		fclose(pause);
		key=getch();
		flag=1;
		if(key=='q' || key=='Q')
			break;
		else if(key=='u' || key=='U')
		{
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					value[i][j]=undo[i][j];
		}
		else if(key=='w' || key=='W')
		{
			for(i=0;i<4;i++)
			{
				if(value[0][i]==0 && value[1][i]==0 && value[2][i]==0 && value[3][i]==0)
				{
				}
				else if(value[1][i]==0 && value[2][i]==0 && value[3][i]==0)
				{
				}
				else if(value[0][i]==0 && value[1][i]==0 && value[2][i]==0)
				{
					doundo(i);
					value[0][i]=value[3][i];
					value[3][i]=0;
					flag=0;
				}
				else if(value[0][i]==0 && value[1][i]==0 && value[3][i]==0)
				{
					doundo(i);
					value[0][i]=value[2][i];
					value[2][i]=0;
					flag=0;
				}
				else if(value[0][i]==0 && value[2][i]==0 && value[3][i]==0)
				{
					doundo(i);
					value[0][i]=value[1][i];
					value[1][i]=0;
					flag=0;
				}
				else if(value[0][i]!=0 && value[1][i]!=0 && value[2][i]==0 && value[3][i]==0)
				{
					if(value[0][i]==value[1][i])
					{
						doundo(i);
						value[0][i]+=value[1][i];
						total+=value[0][i];
						value[1][i]=0;
						flag=0;
					}
				}
				else if(value[2][i]!=0 && value[1][i]!=0 && value[0][i]==0 && value[3][i]==0)
				{
					if(value[2][i]==value[1][i])
					{
						doundo(i);
						value[0][i]=value[2][i]+value[1][i];
						total+=value[0][i];
						value[1][i]=0;
						value[2][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[0][i]=value[1][i];
						value[1][i]=value[2][i];
						value[2][i]=0;
						flag=0;
					}
				}
				else if(value[2][i]!=0 && value[3][i]!=0 && value[0][i]==0 && value[1][i]==0)
				{
					if(value[2][i]==value[3][i])
					{
						doundo(i);
						value[0][i]=value[2][i]+value[3][i];
						total+=value[0][i];
						value[2][i]=0;
						value[3][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[0][i]=value[2][i];
						value[1][i]=value[3][i];
						value[2][i]=0;
						value[3][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]==0 && value[2][i]!=0 && value[3][i]==0)
				{
					if(value[0][i]==value[2][i])
					{
						doundo(i);
						value[0][i]=value[0][i]+value[2][i];
						total+=value[0][i];
						value[2][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[1][i]=value[2][i];
						value[2][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]==0 && value[2][i]==0 && value[3][i]!=0)
				{
					if(value[0][i]==value[3][i])
					{
						doundo(i);
						value[0][i]=value[0][i]+value[3][i];
						total+=value[0][i];
						value[3][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[1][i]=value[3][i];
						value[3][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]==0 && value[1][i]!=0 && value[2][i]==0 && value[3][i]!=0)
				{
					if(value[1][i]==value[3][i])
					{
						doundo(i);
						value[0][i]=value[1][i]+value[3][i];
						total+=value[0][i];
						value[1][i]=0;
						value[3][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[0][i]=value[1][i];
						value[1][i]=value[3][i];
						value[3][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]==0 && value[1][i]!=0 && value[2][i]!=0 && value[3][i]!=0)
				{
					if(value[1][i]==value[2][i])
					{
						doundo(i);
						value[0][i]=value[1][i]+value[2][i];
						total+=value[0][i];
						value[1][i]=value[3][i];
						value[2][i]=0;
						value[3][i]=0;
						flag=0;
					}
					else if(value[2][i]==value[3][i])
					{
						doundo(i);
						value[0][i]=value[1][i];
						value[1][i]=value[2][i]+value[3][i];
						total+=value[1][i];
						value[2][i]=0;
						value[3][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[0][i]=value[1][i];
						value[1][i]=value[2][i];
						value[2][i]=value[3][i];
						value[3][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]==0 && value[2][i]!=0 && value[3][i]!=0)
				{
					if(value[0][i]==value[2][i])
					{
						doundo(i);
						value[0][i]=value[0][i]+value[2][i];
						total+=value[0][i];
						value[1][i]=value[3][i];
						value[2][i]=0;
						value[3][i]=0;
						flag=0;
					}
					else if(value[2][i]==value[3][i])
					{
						doundo(i);
						value[1][i]=value[2][i]+value[3][i];
						total+=value[1][i];
						value[2][i]=0;
						value[3][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[1][i]=value[2][i];
						value[2][i]=value[3][i];
						value[3][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]!=0 && value[2][i]==0 && value[3][i]!=0)
				{
					if(value[0][i]==value[1][i])
					{
						doundo(i);
						value[0][i]+=value[1][i];
						total+=value[0][i];
						value[1][i]=value[3][i];
						value[2][i]=0;
						value[3][i]=0;
						flag=0;
					}
					else if(value[1][i]==value[3][i])
					{
						doundo(i);
						value[1][i]+=value[3][i];
						total+=value[1][i];
						value[2][i]=0;
						value[3][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[2][i]=value[3][i];
						value[3][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]!=0 && value[2][i]!=0 && value[3][i]==0)
				{
					if(value[0][i]==value[1][i])
					{
						doundo(i);
						value[0][i]+=value[1][i];
						total+=value[0][i];
						value[1][i]=value[2][i];
						value[2][i]=0;
						flag=0;
					}
					else if(value[1][i]==value[2][i])
					{
						doundo(i);
						value[1][i]+=value[2][i];
						total+=value[1][i];
						value[2][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]!=0 && value[2][i]!=0 && value[3][i]!=0)
				{
					if(value[0][i]==value[1][i] && value[2][i]==value[3][i])
					{
						doundo(i);
						value[0][i]+=value[1][i];
						total+=value[0][i];
						value[1][i]=value[2][i]+value[3][i];
						total+=value[1][i];
						value[2][i]=value[3][i]=0;
						flag=0;
					}
					else if(value[0][i]==value[1][i])
					{
						doundo(i);
						value[0][i]+=value[1][i];
						total+=value[0][i];
						value[1][i]=value[2][i];
						value[2][i]=value[3][i];
						value[3][i]=0;
						flag=0;
					}
					else if(value[1][i]==value[2][i])
					{
						doundo(i);
						value[1][i]+=value[2][i];
						total+=value[1][i];
						value[2][i]=value[3][i];
						value[3][i]=0;
						flag=0;
					}
					else if(value[2][i]==value[3][i])
					{
						doundo(i);
						value[2][i]+=value[3][i];
						total+=value[2][i];
						value[3][i]=0;
						flag=0;
					}
				}
			}
		}
		else if(key=='s' || key=='S')
		{
			for(i=0;i<4;i++)
			{
				if(value[0][i]==0 && value[1][i]==0 && value[2][i]==0 && value[3][i]==0)
				{
				}
				else if(value[1][i]==0 && value[2][i]==0 && value[3][i]==0)
				{
					doundo(i);
					value[3][i]=value[0][i];
					value[0][i]=0;
					flag=0;
				}
				else if(value[0][i]==0 && value[1][i]==0 && value[2][i]==0)
				{
				}
				else if(value[0][i]==0 && value[1][i]==0 && value[3][i]==0)
				{
					doundo(i);
					value[3][i]=value[2][i];
					value[2][i]=0;
					flag=0;
				}
				else if(value[0][i]==0 && value[2][i]==0 && value[3][i]==0)
				{
					doundo(i);
					value[3][i]=value[1][i];
					value[1][i]=0;
					flag=0;
				}
				else if(value[0][i]!=0 && value[1][i]!=0 && value[2][i]==0 && value[3][i]==0)
				{
					if(value[0][i]==value[1][i])
					{
						doundo(i);
						value[3][i]=value[0][i]+value[1][i];
						total+=value[3][i];
						value[0][i]=0;
						value[1][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[3][i]=value[1][i];
						value[2][i]=value[0][i];
						value[1][i]=0;
						value[0][i]=0;
						flag=0;
					}
				}
				else if(value[2][i]!=0 && value[1][i]!=0 && value[0][i]==0 && value[3][i]==0)
				{
					if(value[2][i]==value[1][i])
					{
						doundo(i);
						value[3][i]=value[2][i]+value[1][i];
						total+=value[3][i];
						value[1][i]=0;
						value[2][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[2][i]=value[1][i];
						value[3][i]=value[2][i];
						value[1][i]=0;
						flag=0;
					}
				}
				else if(value[2][i]!=0 && value[3][i]!=0 && value[0][i]==0 && value[1][i]==0)
				{
					if(value[2][i]==value[3][i])
					{
						doundo(i);
						value[3][i]=value[2][i]+value[3][i];
						total+=value[3][i];
						value[2][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]==0 && value[2][i]!=0 && value[3][i]==0)
				{
					if(value[0][i]==value[2][i])
					{
						doundo(i);
						value[3][i]=value[0][i]+value[2][i];
						total+=value[3][i];
						value[0][i]=0;
						value[2][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[3][i]=value[2][i];
						value[2][i]=value[0][i];
						value[0][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]==0 && value[2][i]==0 && value[3][i]!=0)
				{
					if(value[0][i]==value[3][i])
					{
						doundo(i);
						value[3][i]=value[0][i]+value[3][i];
						total+=value[3][i];
						value[0][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[2][i]=value[0][i];
						value[0][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]==0 && value[1][i]!=0 && value[2][i]==0 && value[3][i]!=0)
				{
					if(value[1][i]==value[3][i])
					{
						doundo(i);
						value[3][i]=value[1][i]+value[3][i];
						total+=value[3][i];
						value[1][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[2][i]=value[1][i];
						value[1][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]==0 && value[1][i]!=0 && value[2][i]!=0 && value[3][i]!=0)
				{
					if(value[3][i]==value[2][i])
					{
						doundo(i);
						value[3][i]=value[3][i]+value[2][i];
						total+=value[3][i];
						value[2][i]=value[1][i];
						value[1][i]=0;
						flag=0;
					}
					else if(value[2][i]==value[1][i])
					{
						doundo(i);
						value[2][i]=value[2][i]+value[1][i];
						total+=value[2][i];
						value[1][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]==0 && value[2][i]!=0 && value[3][i]!=0)
				{
					if(value[2][i]==value[3][i])
					{
						doundo(i);
						value[3][i]=value[2][i]+value[3][i];
						total+=value[3][i];
						value[2][i]=value[0][i];
						value[0][i]=0;
						flag=0;
					}
					else if(value[0][i]==value[2][i])
					{
						doundo(i);
						value[2][i]=value[0][i]+value[2][i];
						total+=value[2][i];
						value[0][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[1][i]=value[0][i];
						value[0][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]!=0 && value[2][i]==0 && value[3][i]!=0)
				{
					if(value[1][i]==value[3][i])
					{
						doundo(i);
						value[3][i]+=value[1][i];
						total+=value[3][i];
						value[2][i]=value[0][i];
						value[0][i]=0;
						value[1][i]=0;
						flag=0;
					}
					else if(value[0][i]==value[1][i])
					{
						doundo(i);
						value[2][i]=value[0][i]+value[1][i];
						total+=value[2][i];
						value[1][i]=0;
						value[0][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[2][i]=value[1][i];
						value[1][i]=value[0][i];
						value[0][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]!=0 && value[2][i]!=0 && value[3][i]==0)
				{
					if(value[1][i]==value[2][i])
					{
						doundo(i);
						value[3][i]=value[1][i]+value[2][i];
						total+=value[3][i];
						value[2][i]=value[0][i];
						value[1][i]=0;
						value[0][i]=0;
						flag=0;
					}
					else if(value[0][i]==value[1][i])
					{
						doundo(i);
						value[3][i]=value[2][i];
						value[2][i]=value[1][i]+value[0][i];
						total+=value[2][i];
						value[1][i]=0;
						value[0][i]=0;
						flag=0;
					}
					else
					{
						doundo(i);
						value[3][i]=value[2][i];
						value[2][i]=value[1][i];
						value[1][i]=value[0][i];
						value[0][i]=0;
						flag=0;
					}
				}
				else if(value[0][i]!=0 && value[1][i]!=0 && value[2][i]!=0 && value[3][i]!=0)
				{
					if(value[0][i]==value[1][i] && value[2][i]==value[3][i])
					{
						doundo(i);
						value[3][i]+=value[2][i];
						total+=value[3][i];
						value[2][i]=value[1][i]+value[0][i];
						total+=value[2][i];
						value[1][i]=0;
						value[0][i]=0;
						flag=0;
					}
					else if(value[2][i]==value[3][i])
					{
						doundo(i);
						value[3][i]+=value[2][i];
						total+=value[3][i];
						value[2][i]=value[1][i];
						value[1][i]=value[0][i];
						value[0][i]=0;
						flag=0;
					}
					else if(value[1][i]==value[2][i])
					{
						doundo(i);
						value[2][i]+=value[1][i];
						total+=value[2][i];
						value[1][i]=value[0][i];
						value[0][i]=0;
						flag=0;
					}
					else if(value[0][i]==value[1][i])
					{
						doundo(i);
						value[1][i]+=value[0][i];
						total+=value[1][i];
						value[0][i]=0;
						flag=0;
					}
				}
			}
		}
		else if(key=='a' || key=='A')
		{
			for(i=0;i<4;i++)
			{
				if(value[i][0]==0 && value[i][1]==0 && value[i][2]==0 && value[i][3]==0)
				{
				}
				else if(value[i][1]==0 && value[i][2]==0 && value[i][3]==0)
				{
				}
				else if(value[i][0]==0 && value[i][1]==0 && value[i][2]==0)
				{
					doundo(i);
					value[i][0]=value[i][3];
					value[i][3]=0;
					flag=0;
				}
				else if(value[i][0]==0 && value[i][1]==0 && value[i][3]==0)
				{
					doundo(i);
					value[i][0]=value[i][2];
					value[i][2]=0;
					flag=0;
				}
				else if(value[i][0]==0 && value[i][2]==0 && value[i][3]==0)
				{
					doundo(i);
					value[i][0]=value[i][1];
					value[i][1]=0;
					flag=0;
				}
				else if(value[i][0]!=0 && value[i][1]!=0 && value[i][2]==0 && value[i][3]==0)
				{
					if(value[i][0]==value[i][1])
					{
						doundo(i);
						value[i][0]+=value[i][1];
						total+=value[i][0];
						value[i][1]=0;
						flag=0;
					}
				}
				else if(value[i][2]!=0 && value[i][1]!=0 && value[i][0]==0 && value[i][3]==0)
				{
					doundo(i);
					if(value[i][2]==value[i][1])
					{
						value[i][0]=value[i][2]+value[i][1];
						total+=value[i][0];
						value[i][1]=0;
						value[i][2]=0;
						flag=0;
					}
					else
					{
						value[i][0]=value[i][1];
						value[i][1]=value[i][2];
						value[i][2]=0;
						flag=0;
					}
				}
				else if(value[i][2]!=0 && value[i][3]!=0 && value[i][0]==0 && value[i][1]==0)
				{
					doundo(i);
					if(value[i][2]==value[i][3])
					{
						value[i][0]=value[i][2]+value[i][3];
						total+=value[i][0];
						value[i][2]=0;
						value[i][3]=0;
						flag=0;
					}
					else
					{
						value[i][0]=value[i][2];
						value[i][1]=value[i][3];
						value[i][2]=0;
						value[i][3]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]==0 && value[i][2]!=0 && value[i][3]==0)
				{
					doundo(i);
					if(value[i][0]==value[i][2])
					{
						value[i][0]=value[i][0]+value[i][2];
						total+=value[i][0];
						value[i][2]=0;
						flag=0;
					}
					else
					{
						value[i][1]=value[i][2];
						value[i][2]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]==0 && value[i][2]==0 && value[i][3]!=0)
				{
					doundo(i);
					if(value[i][0]==value[i][3])
					{
						value[i][0]=value[i][0]+value[i][3];
						total+=value[i][0];
						value[i][3]=0;
						flag=0;
					}
					else
					{
						value[i][1]=value[i][3];
						value[i][3]=0;
						flag=0;
					}
				}
				else if(value[i][0]==0 && value[i][1]!=0 && value[i][2]==0 && value[i][3]!=0)
				{
					doundo(i);
					if(value[i][1]==value[i][3])
					{
						value[i][0]=value[i][1]+value[i][3];
						total+=value[i][0];
						value[i][1]=0;
						value[i][3]=0;
						flag=0;
					}
					else
					{
						value[i][0]=value[i][1];
						value[i][1]=value[i][3];
						value[i][3]=0;
						flag=0;
					}
				}
				else if(value[i][0]==0 && value[i][1]!=0 && value[i][2]!=0 && value[i][3]!=0)
				{
					doundo(i);
					if(value[i][1]==value[i][2])
					{
						value[i][0]=value[i][1]+value[i][2];
						total+=value[i][0];
						value[i][1]=value[i][3];
						value[i][2]=0;
						value[i][3]=0;
						flag=0;
					}
					else if(value[i][2]==value[i][3])
					{
						value[i][0]=value[i][1];
						value[i][1]=value[i][2]+value[i][3];
						total+=value[i][1];
						value[i][2]=0;
						value[i][3]=0;
						flag=0;
					}
					else
					{
						value[i][0]=value[i][1];
						value[i][1]=value[i][2];
						value[i][2]=value[i][3];
						value[i][3]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]==0 && value[i][2]!=0 && value[i][3]!=0)
				{
					doundo(i);
					if(value[i][0]==value[i][2])
					{
						value[i][0]=value[i][0]+value[i][2];
						total+=value[i][0];
						value[i][1]=value[i][3];
						value[i][2]=0;
						value[i][3]=0;
						flag=0;
					}
					else if(value[i][2]==value[i][3])
					{
						value[i][1]=value[i][2]+value[i][3];
						total+=value[i][1];
						value[i][2]=0;
						value[i][3]=0;
						flag=0;
					}
					else
					{
						value[i][1]=value[i][2];
						value[i][2]=value[i][3];
						value[i][3]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]!=0 && value[i][2]==0 && value[i][3]!=0)
				{
					doundo(i);
					if(value[i][0]==value[i][1])
					{
						value[i][0]+=value[i][1];
						total+=value[i][0];
						value[i][1]=value[i][3];
						value[i][2]=0;
						value[i][3]=0;
						flag=0;
					}
					else if(value[i][1]==value[i][3])
					{
						value[i][1]+=value[i][3];
						total+=value[i][1];
						value[i][2]=0;
						value[i][3]=0;
						flag=0;
					}
					else
					{
						value[i][2]=value[i][3];
						total+=value[i][2];
						value[i][3]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]!=0 && value[i][2]!=0 && value[i][3]==0)
				{
					if(value[i][0]==value[i][1])
					{
						doundo(i);
						value[i][0]+=value[i][1];
						total+=value[i][0];
						value[i][1]=value[i][2];
						value[i][2]=0;
						flag=0;
					}
					else if(value[i][1]==value[i][2])
					{
						doundo(i);
						value[i][1]+=value[i][2];
						total+=value[i][1];
						value[i][2]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]!=0 && value[i][2]!=0 && value[i][3]!=0)
				{
					if(value[i][0]==value[i][1] && value[i][2]==value[i][3])
					{
						doundo(i);
						value[i][0]+=value[i][1];
						total+=value[i][0];
						value[i][1]=value[i][2]+value[i][3];
						total+=value[i][1];
						value[i][2]=value[i][3]=0;
						flag=0;
					}
					else if(value[i][0]==value[i][1])
					{
						doundo(i);
						value[i][0]+=value[i][1];
						total+=value[i][0];
						value[i][1]=value[i][2];
						value[i][2]=value[i][3];
						value[i][3]=0;
						flag=0;
					}
					else if(value[i][1]==value[i][2])
					{
						doundo(i);
						value[i][1]+=value[i][2];
						total+=value[i][1];
						value[i][2]=value[i][3];
						value[i][3]=0;
						flag=0;
					}
					else if(value[i][2]==value[i][3])
					{
						doundo(i);
						value[i][2]+=value[i][3];
						total+=value[i][2];
						value[i][3]=0;
						flag=0;
					}
				}
			}
		}
		else if(key=='d' || key=='D')
		{
			for(i=0;i<4;i++)
			{
				if(value[i][0]==0 && value[i][1]==0 && value[i][2]==0 && value[i][3]==0)
				{
				}
				else if(value[i][1]==0 && value[i][2]==0 && value[i][3]==0)
				{
					doundo(i);
					value[i][3]=value[i][0];
					value[i][0]=0;
					flag=0;
				}
				else if(value[i][0]==0 && value[i][1]==0 && value[i][2]==0)
				{
				}
				else if(value[i][0]==0 && value[i][1]==0 && value[i][3]==0)
				{
					doundo(i);
					value[i][3]=value[i][2];
					value[i][2]=0;
					flag=0;
				}
				else if(value[i][0]==0 && value[i][2]==0 && value[i][3]==0)
				{
					doundo(i);
					value[i][3]=value[i][1];
					value[i][1]=0;
					flag=0;
				}
				else if(value[i][0]!=0 && value[i][1]!=0 && value[i][2]==0 && value[i][3]==0)
				{
					doundo(i);
					if(value[i][0]==value[i][1])
					{
						value[i][3]=value[i][0]+value[i][1];
						total+=value[i][3];
						value[i][0]=0;
						value[i][1]=0;
						flag=0;
					}
					else
					{
						value[i][3]=value[i][1];
						value[i][2]=value[i][0];
						value[i][1]=0;
						value[i][0]=0;
					}
				}
				else if(value[i][2]!=0 && value[i][1]!=0 && value[i][0]==0 && value[i][3]==0)
				{
					doundo(i);
					if(value[i][2]==value[i][1])
					{
						value[i][3]=value[i][2]+value[i][1];
						total+=value[i][3];
						value[i][1]=0;
						value[i][2]=0;
						flag=0;
					}
					else
					{
						value[i][2]=value[i][1];
						value[i][3]=value[i][2];
						value[i][1]=0;
						flag=0;
					}
				}
				else if(value[i][2]!=0 && value[i][3]!=0 && value[i][0]==0 && value[i][1]==0)
				{
					if(value[i][2]==value[i][3])
					{
						doundo(i);
						value[i][3]=value[i][2]+value[i][3];
						total+=value[i][3];
						value[i][2]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]==0 && value[i][2]!=0 && value[i][3]==0)
				{
					doundo(i);
					if(value[i][0]==value[i][2])
					{
						value[i][3]=value[i][0]+value[i][2];
						total+=value[i][3];
						value[i][0]=0;
						value[i][2]=0;
						flag=0;
					}
					else
					{
						value[i][3]=value[i][2];
						value[i][2]=value[i][0];
						value[i][0]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]==0 && value[i][2]==0 && value[i][3]!=0)
				{
					doundo(i);
					if(value[i][0]==value[i][3])
					{
						value[i][3]=value[i][0]+value[i][3];
						total+=value[i][3];
						value[i][0]=0;
						flag=0;
					}
					else
					{
						value[i][2]=value[i][0];
						value[i][0]=0;
						flag=0;
					}
				}
				else if(value[i][0]==0 && value[i][1]!=0 && value[i][2]==0 && value[i][3]!=0)
				{
					doundo(i);
					if(value[i][1]==value[i][3])
					{
						value[i][3]=value[i][1]+value[i][3];
						total+=value[i][3];
						value[i][1]=0;
						flag=0;
					}
					else
					{
						value[i][2]=value[i][1];
						value[i][1]=0;
						flag=0;
					}
				}
				else if(value[i][0]==0 && value[i][1]!=0 && value[i][2]!=0 && value[i][3]!=0)
				{
					if(value[i][1]==value[i][2])
					{
						doundo(i);
						value[i][2]=value[i][1]+value[i][2];
						total+=value[i][2];
						value[i][1]=0;
						value[i][0]=0;
						flag=0;
					}
					else if(value[i][2]==value[i][3])
					{
						doundo(i);
						value[i][3]=value[i][2]+value[i][3];
						total+=value[i][3];
						value[i][2]=value[i][1];
						value[i][1]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]==0 && value[i][2]!=0 && value[i][3]!=0)
				{
					doundo(i);
					if(value[i][2]==value[i][3])
					{
						value[i][3]=value[i][2]+value[i][3];
						total+=value[i][3];
						value[i][2]=value[i][0];
						value[i][0]=0;
						flag=0;
					}
					else if(value[i][0]==value[i][2])
					{
						value[i][2]=value[i][0]+value[i][2];
						total+=value[i][2];
						value[i][0]=0;
						flag=0;
					}
					else
					{
						value[i][1]=value[i][0];
						value[i][0]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]!=0 && value[i][2]==0 && value[i][3]!=0)
				{
					doundo(i);
					if(value[i][1]==value[i][3])
					{
						value[i][3]+=value[i][1];
						total+=value[i][3];
						value[i][2]=value[i][0];
						value[i][0]=0;
						value[i][1]=0;
						flag=0;
					}
					else if(value[i][0]==value[i][1])
					{
						value[i][2]=value[i][0]+value[i][1];
						total+=value[i][2];
						value[i][1]=0;
						value[i][0]=0;
						flag=0;
					}
					else
					{
						value[i][2]=value[i][1];
						value[i][1]=value[i][0];
						value[i][0]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]!=0 && value[i][2]!=0 && value[i][3]==0)
				{
					doundo(i);
					if(value[i][1]==value[i][2])
					{
						value[i][3]=value[i][1]+value[i][2];
						total+=value[i][3];
						value[i][2]=value[i][0];
						value[i][1]=0;
						value[i][0]=0;
						flag=0;
					}
					else if(value[i][0]==value[i][1])
					{
						value[i][3]=value[i][2];
						value[i][2]=value[i][1]+value[i][0];
						total+=value[i][2];
						value[i][1]=0;
						value[i][0]=0;
						flag=0;
					}
					else
					{
						value[i][3]=value[i][2];
						value[i][2]=value[i][1];
						value[i][1]=value[i][0];
						value[i][0]=0;
						flag=0;
					}
				}
				else if(value[i][0]!=0 && value[i][1]!=0 && value[i][2]!=0 && value[i][3]!=0)
				{
					doundo(i);
					if(value[i][0]==value[i][1] && value[i][2]==value[i][3])
					{
						value[i][3]+=value[i][2];
						total+=value[i][3];
						value[i][2]=value[i][1]+value[i][0];
						total+=value[i][2];
						value[i][1]=0;
						value[i][0]=0;
						flag=0;
					}
					else if(value[i][0]==value[i][1])
					{
						value[i][1]+=value[i][0];
						total+=value[i][1];
						value[i][0]=0;
						flag=0;
					}
					else if(value[i][1]==value[i][2])
					{
						value[i][2]+=value[i][1];
						total+=value[i][2];
						value[i][1]=value[i][0];
						value[i][0]=0;
						flag=0;
					}
					else if(value[i][2]==value[i][3])
					{
						value[i][3]+=value[i][2];
						total+=value[i][3];
						value[i][2]=value[i][1];
						value[i][1]=value[i][0];
						value[i][0]=0;
						flag=0;
					}
				}
			}
		}
	}while(1);
}
void main()
{
	int gd=DETECT,gm;
	int i,j;
	char key;
	initgraph(&gd,&gm,"c:/turboc3/bgi");
	randomize();
	setfillstyle(SOLID_FILL,RED);
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			value[i][j]=0;
			undo[i][j]=0;
		}
	while(1)
	{
		cleardevice();
		setbkcolor(YELLOW);
		setcolor(RED);
		outtextxy(200,50,"Menu");
		outtextxy(50,100,"1 - Play Game");
		outtextxy(50,150,"2 - Show High score");
		outtextxy(50,200,"3 - Exit");
		flushall();
		key=getch();
		switch(key)
		{
			case '1':game();
			break;
			case '2':showscore();
			getch();
			break;
			case '3':closegraph();
			fcloseall();
			exit(0);
		}
	}
}
#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
#include<string.h>
void gameend(int,int);
void gameplay();
//void makeladder();
//void makesnake();
int checksnakeladder(int);
void gamedisp();
void help();
int gameinput(int);
void gamestart();
int ladder[3][2],snakes[3][2];
class player
{
	int position,lastroll[3],start,sl,sl1;

	public:
	char plname[9];
	void reset()
	{
		position=0;
		lastroll[3]=0;
		lastroll[1]=0;
		lastroll[2]=0;
		sl=0;
		sl1=0;
		start=0;
		plname[0]=NULL;
	}
	int update(int roll)
	{
			lastroll[0]=lastroll[1];
			lastroll[1]=lastroll[2];
			lastroll[2]=roll;
		if(lastroll[2]==0)
			return(-1);
		else if(lastroll[2]==6&&start==0)
		{
			start=1;
			lastroll[2]=0;
			return(0);
		}
		else if(lastroll[2]==6)
			return(0);
		if(start==1)
		{
			//gamedisp(-1,position);
			sl=0;
			if(position+lastroll[2]<=100&&(lastroll[0]!=6||lastroll[1]!=6||lastroll[2]!=6))
			{
				if(lastroll[1]==6)
				{
					position+=lastroll[2];
					position+=lastroll[1];
					//lastroll[1]=0;
				}
				else if(lastroll[0]==6&&lastroll[1]==6)
				{	position+=(lastroll[2]+lastroll[1]+lastroll[0]);
					//position+=lastroll[1];
					//position+=lastroll[0];
					//lastroll[1]=0;
				}
				else
					position+=lastroll[2];
				sl=checksnakeladder(position);
				if(sl>0)
					position=ladder[sl-1][1];
				else if(sl<0)
					position=snakes[(sl*-1)-1][1];
			}
			else if(lastroll[2]+position>100)
			{
				if(lastroll[2]==6)
					lastroll[2]=0;
			}
			else if(lastroll[0]==6&&lastroll[1]==6&&lastroll[2]==6)
				lastroll[2]=0;
		}
		//gamedisp(color,position);
		return(1);
	}

	int getpos()
	{
		return(position);
	}

	void disp(int x,int y)
	{
		char *temp;
		temp=new char[4];
		if(position<100)
		{
			temp[2]=NULL;
			temp[0]=position/10+48;
			temp[1]=position%10+48;
		}
		else
		{
			temp[3]=NULL;
			temp[0]='1';
			temp[1]='0';
			temp[2]='0';
		}
		if(x!=640)
		{
			outtextxy(x,y+12,"You are now at ");
			outtextxy(x+textwidth("You are now at "),y+12,temp);
		}
		else
		{
			outtextxy(x-textwidth("You are now at ")-textwidth(temp),y+12,"You are now at ");
			outtextxy(x-textwidth(temp),y+12,temp);
		}
		if(lastroll[2]==0&&start==1)
			temp[0]='6';
		else
			temp[0]=lastroll[2]+48;
		temp[1]=NULL;
		if(sl==0&&sl1==0)
		{
			if(x!=640)
			{

				/*if(position<100)
				{
					outtextxy(x,y+12,"You are now at ");
					outtextxy(x+textwidth("You are now at "),y+12,temp);
				}
				else
					outtextxy(x,y+12,"You are now at 100!");
				*/
				outtextxy(x,y,"You got a ");
				outtextxy(x+textwidth("You got a "),y,temp);
			}
			else
			{
				/*if(position<100)
				{
					outtextxy(x-textwidth("You are now at ")-16,y+12,"You are now at ");
					outtextxy(x-textwidth(temp),y+12,temp);
				}
				else
					outtextxy(x-textwidth("You are now at 100!"),y+12,"You are now at 100!");
				*/
				outtextxy(x-textwidth("You got a")-16,y,"You got a ");

				outtextxy(x-textwidth(temp),y,temp);
			}
		}
		else if(sl>0)
		{
			if(x!=640)
			{
				/*outtextxy(x,y+12,"You are now at ");
				outtextxy(x+textwidth("You are now at "),y+12,temp);
				*/
				outtextxy(x,y,"You got a ");

				outtextxy(x+textwidth("You got a "),y,temp);
				outtextxy(x+textwidth("You got a   "),y,"and Ladder");
				temp[0]=sl+48;
				outtextxy(x+textwidth("You got a   and Ladder "),y,temp);
			}
			else
			{
				/*outtextxy(x-textwidth("You are now at ")-16,y+12,"You are now at ");
				outtextxy(x-textwidth(temp),y+12,temp);
				*/
				outtextxy(x-textwidth("You got a   and Ladder  "),y,"You got a ");

				outtextxy(x-textwidth(temp)-textwidth(" and Ladder  "),y,temp);
				outtextxy(x-textwidth("and Ladder  "),y,"and Ladder");
				temp[0]=sl+48;
				outtextxy(x-textwidth(temp),y,temp);
			}

		}
		else if(sl<0)
		{
			if(x!=640)
			{
				/*outtextxy(x,y+12,"You are now at ");
				outtextxy(x+textwidth("You are now at "),y+12,temp);
				*/
				outtextxy(x,y,"You got a ");

				outtextxy(x+textwidth("You got a "),y,temp);
				outtextxy(x+textwidth("You got a   "),y,"and Snake");
				temp[0]=(sl*-1)+48;
				outtextxy(x+textwidth("You got a   and Snake "),y,temp);
			}
			else
			{
				/*outtextxy(x-textwidth("You are now at ")-16,y+12,"You are now at ");
				outtextxy(x-textwidth(temp),y+12,temp);
				*/
				outtextxy(x-textwidth("You got a   and Snake  "),y,"You got a ");

				outtextxy(x-textwidth(temp)-textwidth(" and Snake  "),y,temp);
				outtextxy(x-textwidth("and Snake  "),y,"and Snake");
				temp[0]=(sl*-1)+48;
				outtextxy(x-textwidth(temp),y,temp);
			}

		}
		delete temp;
	}
}p[2];

void main()
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"");
	randomize();
	ladder[0][0]=18;
	ladder[0][1]=61;
	ladder[1][0]=35;
	ladder[1][1]=69;
	ladder[2][0]=65;
	ladder[2][1]=99;
	snakes[0][0]=58;
	snakes[0][1]=29;
	snakes[1][0]=73;
	snakes[1][1]=12;
	snakes[2][0]=97;
	snakes[2][1]=2;
	for(;;)
	{
		p[0].reset();
		p[1].reset();
		gamestart();
	}
}

int checksnakeladder(int pos)
{
	for(int i=0;i<3;i++)
	{
		if(pos==ladder[i][0])
		{
			//delete pos;
			return(i+1);
		}
		if(pos==snakes[i][0])
		{
			//delete pos;
			return(-1*(i+1));
		}
	}
	//delete pos;
	return(0);
}
void gamestart()
{
	clrscr();
	cleardevice();
	int *x,*y,option=0,end=0,check=0,mx,my,i;
	setbkcolor(7);
	setcolor(1);
	settextstyle(4,HORIZ_DIR,6);
	outtextxy((getmaxx()-textwidth("Snakes & Ladders"))/2,textheight("S")*0.8,"Snakes & Ladders");
	setcolor(2);
	settextstyle(0,HORIZ_DIR,2);
	x=new int [2];
	x[0]=(getmaxx()/2)-(textwidth("Play")/2);
	x[1]=(getmaxx()/2)-(textwidth("options")/2);
	y=new int[5];
	y[0]=(getmaxy()/2)-(textheight("P")*4);
	y[1]=(getmaxy()/2)-(textheight("P")*2);
	y[2]=(getmaxy()/2);
	y[3]=(getmaxy()/2)+(textheight("P")*2);
	y[4]=(getmaxy()/2)+(textheight("P")*4);
	outtextxy(x[0],y[0],"Play");
	outtextxy(x[1],y[3],"Credits");
	outtextxy(x[1],y[2],"Options");
	outtextxy(x[0],y[1],"Help");
	outtextxy(x[0],y[4],"Exit");
	option=0;
	do
	{
		//setfillstyle(EMPTY_FILL,8);
		setcolor(2);
		rectangle(x[1]-4,y[option]-(textheight("P")/2),x[1]+textwidth("options")+4,y[option]+(textheight("P")*1.25)+2);
		setcolor(14);
		switch(option)
		{
			case 0:outtextxy(x[0],y[0],"Play");
				break;
			case 3:outtextxy(x[1],y[3],"Credits");
				break;
			case 2:outtextxy(x[1],y[2],"Options");
				break;
			case 1:outtextxy(x[0],y[1],"Help");
				break;
			case 4:outtextxy(x[0],y[4],"Exit");
				break;
		}
		end=getch();
		setcolor(getbkcolor());
		rectangle(x[1]-4,y[option]-(textheight("P")/2),x[1]+textwidth("options")+4,(y[option]+textheight("p")*1.25)+2);
		setcolor(2);
		switch(option)
		{
			case 0:outtextxy(x[0],y[0],"Play\0");
				break;
			case 3:outtextxy(x[1],y[3],"Credits\0");
				break;
			case 2:outtextxy(x[1],y[2],"Options\0");
				break;
			case 1:outtextxy(x[0],y[1],"Help\0");
				break;
			case 4:outtextxy(x[0],y[4],"Exit\0");
				break;
		}
		switch(end)
		{
			case 's':
			case 'S':
			case '2':option++;
				if(option>4)
					option=0;
				break;
			case 'w':
			case 'W':
			case '8':option--;
				if(option<0)
					option=4;
				break;
		}
	}while(end!=13&&end!='5');
	/*setfillstyle(SOLID_FILL,8);
	setcolor(2);
	bar3d(x[1]-2,y[option]-(textheight("P")/2),x[1]+textwidth("options")+6,y[option]+(textheight("p")*1.5)+2,0,0);
	setcolor(14);
	switch(option)
	{
		case 0:outtextxy(x[0]+2,y[0],"Play");
			break;
		case 3:outtextxy(x[1]+2,y[3],"Credits");
			break;
		case 2:outtextxy(x[1]+2,y[2],"Options");
			break;
		case 1:outtextxy(x[0]+2,y[1],"Help");
			break;
		case 4:outtextxy(x[0]+2,y[4],"Exit");
			break;
	}
	delay(500); */
	delete x;
	delete y;
	switch(option)
	{
		case 0: clrscr();
			cleardevice();
			if(!gameinput(0))
				break;
			if(!gameinput(1))
				break;
			delay(750);
			gamedisp();
			break;
		case 1: help();
			break;
		case 4: closegraph();
			exit(0);
	}

}

int gameinput(int pnumber)
{
	int *poly,i=0;
	char ch;
	poly=new int[3];
	setfillstyle(SOLID_FILL,2);
	settextstyle(0,HORIZ_DIR,3);
	if(!pnumber)
	{
		poly[0]=(getmaxx()-textwidth("ABCDEFGHI"))/2;
		poly[1]=(getmaxy()/2)+(textheight("A"));
		poly[2]=(getmaxx()+textwidth("ABCDEFGHI"))/2;
		poly[3]=(getmaxy()/2)+(textheight("A")*2.4);
		bar3d(poly[0],poly[1],poly[2],poly[3],0,0);
		poly[0]=(getmaxx()-textwidth("ABCDEFGHI"))/2;
		poly[1]=(getmaxy()/2)-(textheight("A")*2.4);
		poly[2]=(getmaxx()+textwidth("ABCDEFGHI"))/2;
		poly[3]=(getmaxy()/2)-(textheight("A"));
	}
	else
	{
		poly[0]=(getmaxx()-textwidth("ABCDEFGHI"))/2;
		poly[1]=(getmaxy()/2)+(textheight("A"));
		poly[2]=(getmaxx()+textwidth("ABCDEFGHI"))/2;
		poly[3]=(getmaxy()/2)+(textheight("A")*2.4);

	}
	setfillstyle(SOLID_FILL,10);
	do
	{
		setcolor(14);
		bar3d(poly[0],poly[1],poly[2],poly[3],0,0);
		if(p[pnumber].plname[0]==NULL)
		{
			setcolor(7);
			settextstyle(0,HORIZ_DIR,1);
			if(pnumber)
				outtextxy(poly[0]+(poly[2]-poly[0]-textwidth("Enter name of Player 1"))/2,poly[1]+((poly[3]-poly[1]-textheight("A"))/2),"Enter name of Player 2");
			else
				outtextxy(poly[0]+(poly[2]-poly[0]-textwidth("Enter name of Player 1"))/2,poly[1]+((poly[3]-poly[1]-textheight("A"))/2),"Enter name of Player 1");
		}
		else
		{
			setcolor(getbkcolor());
			settextstyle(0,HORIZ_DIR,3);
			outtextxy(poly[0]+(poly[2]-poly[0]-textwidth(p[pnumber].plname))/2,(poly[1]+(textheight("A")*0.2)),p[pnumber].plname);
		}
		ch=getch();
		switch(ch)
		{
			case 8: if(i>0)
				{
					i--;i--;
					p[pnumber].plname[i+1]=NULL;
				}
				break;
			case 13:if(0<i&&i<8)
				{
					p[pnumber].plname[i]=NULL;
					i=8;
				}
				else if(i==0)
				{
					if(pnumber)
						strcpy(p[pnumber].plname,"Player 2");
					else
						strcpy(p[pnumber].plname,"Player 1");
					i=8;
				}
				setcolor(14);
				setfillstyle(SOLID_FILL,2);
				bar3d(poly[0],poly[1],poly[2],poly[3],0,0);
				settextstyle(0,HORIZ_DIR,3);
				outtextxy(poly[0]+(poly[2]-poly[0]-textwidth(p[pnumber].plname))/2,(poly[1]+(textheight("A")*0.2)),p[pnumber].plname);
				break;
			default:if(i<8)
				{
					p[pnumber].plname[i]=ch;
					p[pnumber].plname[i+1]=NULL;
				}
				break;
		}
		if(i<8)
			i++;
	}while(ch!=13);
	delete poly;
	if(!strcmpi(p[pnumber].plname,"home"))
	{
		return(0);
	}
	       return(1);

}

void help()
{
	clrscr();
	cleardevice();
	settextstyle(0,HORIZ_DIR,3);
	setcolor(14);
	outtextxy((getmaxx()-textwidth("You need help?"))/2,(getmaxy()/2)-textheight("A")*2,"You need help?");
	outtextxy((getmaxx()-textwidth("Ask some kid for that :P"))/2,(getmaxy()/2),"Ask some kid for that :P");
	getch();
}

void gamedisp()
{
	int x=160,y=40,xi=32,yi=xi,sl,i;
	char ch[3];
	clrscr();
	cleardevice();
	setcolor(15);
	line(0,20,640,20);
	line(130,20,130,390);
	line(510,20,510,390);
	line(130,390,510,390);
	line(0,340,130,340);
	line(510,340,640,340);
	line(320,390,320,480);
	setcolor(2);
	setfillstyle(SOLID_FILL,9);
	bar3d(x-10,y-10,x+330,y+330,0,0);
	//setfillstyle(SOLID_FILL,15);
	//setcolor(getbkcolor());
	/*bar3d(x,y,x+320,y+320,0,0);
	for(i=1;i<10;i++)
	{	line(x+(32*i),y,x+(32*i),y+(32*10));
		line(x,y+(32*i),x+(32*10),y+(32*i));
	} */
	ch[2]=NULL;
	x=170;y=340;
	//makeladder();
	//makesnake();
	setcolor(getbkcolor());
	settextstyle(0,HORIZ_DIR,1);
	for(i=1;i<101;i++)
	{
		sl=checksnakeladder(i);
		if(sl>0)
			setfillstyle(SOLID_FILL,2);
		else if(sl<0)
			setfillstyle(SOLID_FILL,RED);
		else if(sl==0)
			setfillstyle(SOLID_FILL,15);
		bar3d(x-10,y+20,x+22,y-12,0,0);
		if(i==100)
			outtextxy(x-4,y,"100");
		else
		{	ch[0]=i/10+48;
			ch[1]=i%10+48;
			outtextxy(x,y,ch);
		}
		if(i%10==0)
		{       x+=xi;
			xi=xi*-1;
			y=y-yi;
		}
		x+=xi;
		if(!kbhit())
			delay(50);
		else if(i==100)
			getch();
	}
	setcolor(YELLOW);
       //	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
	outtextxy(2,textheight("C"),"Currently Winning: ");
	outtextxy(2,75,"Ladders are at:");
	outtextxy(2,175,"Snakes are at:");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	outtextxy(2,350,p[0].plname);
	outtextxy(getmaxx()-textwidth(p[1].plname),350,p[1].plname);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	y=7,x=2;
	for(i=0;i<3;i++,y++)
	{
		gotoxy(x,y);
		cout<<i+1<<") "<<ladder[i][0]<<"-"<<ladder[i][1];
	}
	y=13;
	for(i=0;i<3;i++,y++)
	{
		gotoxy(x,y);
		cout<<i+1<<") "<<snakes[i][0]<<"-"<<snakes[i][1];
	}
	gameplay();
}

void makeladder()
{
	int i;
	for(i=0;i<3;i++)
	{
		if(i==0)
		{
			do{
				ladder[i][0]=random(60);
				ladder[i][1]=random(96);
			}while(ladder[i][0]<5||(ladder[i][1]<=(ladder[i][0]+(10-ladder[i][0]%10))));
		}
		else
		{
			do{
			ladder[i][0]=random(60);
			ladder[i][1]=random(96);
			}while(ladder[i][1]<=ladder[i][0]+(10-ladder[i][0]%10)||ladder[i][0]==ladder[i-1][0]||ladder[i][1]==ladder[i-1][1]);
		}
	}
}
/*
void makesnake()
{
	int i;
	for (i=0;i<3;i++)
	{
		if(i==0)
		{
			do
			{
				snakes[i][0]=random(100);
				snakes[i][1]=random(70);
			}while(snakes[i][0]<=snakes[i][1]||snakes[i][1]<5);
		}
		else
		{
			do
			{
				snakes[i][0]=random(96);
				snakes[i][1]=random(70);
			}while(snakes[i][0]<=snakes[i][1]||snakes[i][1]<5||snakes[i][0]==snakes[i-1][0]||snakes[i][1]==snakes[i-1][1]);
		}
	}

}
*/
void gameplay()
{
	char ans[2],ans2='y',*diecheck="Shall we roll the dice? ",*exitcheck="DO YOU REALLY WANT TO EXIT? ";
	ans[1]=NULL;
	int i,pn,y=400,*poly,x[2]={3,640},no=1,j;
	setfillstyle(SOLID_FILL,0);
	poly=new int[3];
	for(i=0;i>=0;i++)
	{
		pn=i%2;
		setcolor(getbkcolor());
		setfillstyle(SOLID_FILL,getbkcolor());
		if(no)
		{
			if(!pn)
			{
				poly[0]=321;
				poly[4]=x[!pn];
			}
			else
			{
				poly[0]=319;
				poly[4]=x[!pn];
			}
			poly[1]=391;
			poly[2]=poly[0];
			poly[3]=480;
			poly[5]=poly[3];
			poly[6]=poly[4];
			poly[7]=poly[1];
			poly[8]=poly[0];
			poly[9]=poly[1];
			fillpoly(5,poly);
		}
		else
		{
			no=1;
			if(pn)
			{
				poly[0]=321;
				poly[4]=x[pn];
			}
			else
			{
				poly[0]=319;
				poly[4]=x[pn];
			}
			poly[1]=391;
			poly[2]=poly[0];
			poly[3]=480;
			poly[5]=poly[3];
			poly[6]=poly[4];
			poly[7]=poly[1];
			poly[8]=poly[0];
			poly[9]=poly[1];
			fillpoly(5,poly);
		}
		setcolor(15);
		p[!pn].disp(x[!pn],y);
		p[pn].disp(x[pn],y);
		setcolor(getbkcolor());
		poly[0]=2+textwidth("Currently winning: ");
		poly[1]=0;
		poly[2]=poly[0];
		poly[3]=19;
		poly[4]=poly[0]+textwidth("ABCDEFGHIJ");
		poly[5]=poly[3];
		poly[6]=poly[4];
		poly[7]=poly[1];
		poly[8]=poly[0];
		poly[9]=poly[1];
		fillpoly(5,poly);
		setcolor(15);
		if(p[0].getpos()>p[1].getpos())
		{
			outtextxy(2+textwidth("Currently Winning: "),8,p[0].plname);
			if(p[0].getpos()>=100)
			{
				delay(1000);
				gameend(0,0);
				break;
			}
		}
		else if (p[0].getpos()<p[1].getpos())
		{
			outtextxy(5+textwidth("Currently Winning: "),8,p[1].plname);
			if(p[1].getpos()>=100)
			{
				delay(1000);
				gameend(0,1);
				break;
			}
		}
		else if(i!=0)
			outtextxy(5+textwidth("Currently Winning: "),8,"Its a TIE!");
		if(pn)
		{
			outtextxy(x[pn]-textwidth(diecheck)-textwidth("Y"),y+24,diecheck);
			ans[0]=getch();
			outtextxy(x[pn]-textwidth(ans),y+24,ans);
		}
		else
		{	outtextxy(x[pn],y+24,diecheck);
			ans[0]=getch();
			outtextxy(x[pn]+1+textwidth(diecheck),y+24,ans);
		}
		if(ans[0]=='y'||ans[0]=='Y')
		{
			do
			{
				no=p[pn].update(random(7));
				if(no==0)
				{
					i--;
				}
			}while(no==-1);
		}
		else
		{
			if(pn)
				outtextxy(x[pn]-textwidth(exitcheck)-textwidth("Y"),y+36,exitcheck);
			else
				outtextxy(x[pn],y+36,exitcheck);
			ans2=getch();
			if(ans2=='y'||ans2=='Y')
			{	gameend(1,pn);
				break;
			}
			else
			{
				i--;
				no--;
			}
		}
		delay(200);
	}
	delete poly;
	delete diecheck;
	delete exitcheck;
}

void gameend(int mode,int pl)
{
	clrscr();
	cleardevice();
	switch(mode)
	{
		case 1: cout<<"'"<<p[pl].plname<<"' ended the game.";
			break;
		case 0: cout<<"GAME ENDED\n'"<<p[pl].plname<<"' WON.";
			break;
	}
	cout<<"\n\nPress any key to continue...";
	getch();
}
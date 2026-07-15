#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct student 
{
	int rollno;
	char name[20];
	float marks;
	struct student *next;
}SLL;
SLL *hp=0;
void add(void);
void show(void);
void delete(void);
void delete_all(void);
void mod(void);
void save_file(void);
void my_exit(void);
void sort(void);
void reverse(void);
void main()
{
	char op;
	while(1){
		printf("\033[96mEnter the choice:\n");
		printf("a/A:add.c s/S:show d/D:delete a record m/M:modify a record t/T:sort i/I:delete_all r/R:reverse e/E:exit\033[0m\n");
		scanf(" %c",&op);
		switch(op)
		{
			case 'a':
			case 'A':add();break;
			case 's':
			case 'S':show();break;
			case 'd':
			case 'D':delete();break;
			case 'm':
			case 'M':mod();break;
			case 't':
			case 'T':sort();break;
			case 'i':
			case 'I':delete_all();break;
			case 'r':
			case 'R':reverse();break;
			case 'e':
			case 'E':my_exit();break;
			default :printf("\033[91munknown option\033[0m\n");
		}

	}
	//	printf("%d %s %f",hp->rollno,hp->name,hp->marks);
}
void reverse(void)
{
	if(hp==0){
		printf("\033[91m!OHO NO RECORD TO REVERSE\033[0m\n");
		return;}
	SLL *p=hp;
	int c=0,i=0;
	while(p)
	{
		c++;
		p=p->next;
	}
	SLL **q=malloc(sizeof(SLL *)*c);
	p=hp;
	while(p)
	{
		q[i++]=p;
		p=p->next;
	}
	for(c--;c>0;c--)
	{	q[c-1]->next=q[c]->next;
		q[c]->next=q[c-1];}
	hp=q[i-1];
	free(q); 
}
void delete_all(void)
{
	if(hp==0){
		printf("\033[91m!OHO NO RECORD TO DELETE\033[0m\n");
		return;}
	int n;
	printf("\033[5;91m     !WARNING    \n   IF YOU SURE THAN ENTER 1\033[0m\n");
	scanf("%d",&n);
	if(n!=1)
		return;

	SLL *del,*prev;
	del=hp;
	while(hp)
	{
		del=hp;
		prev=hp;
		while(del->next)
		{
			prev=del;
			del=del->next;
		}
		if(del==hp)
			hp=0;
		prev->next=del->next;
		free(del);
	}
}
void sort(void)
{
	if(hp==0){
		printf("\033[91m!OHO NO RECORD TO SORT\033[0m\n");
		return;}
	char op;
l:
	printf("\033[33mEnter the choice \nN/n:sort by name\nM/m:sort by marks\033[0m\n");
	scanf(" %c",&op);
	SLL *p,*q,t;
	if(op=='N'||op=='n')
	{//sort by name
		p=hp;
		while(p)
		{
			q=p->next;
			while(q)
			{
				if(strcmp(p->name,q->name)>0)
				{
					t.marks=p->marks;
					t.rollno=p->rollno;
					strcpy(t.name,p->name);

					p->marks=q->marks;
					p->rollno=q->rollno;
					strcpy(p->name,q->name);

					q->marks=t.marks;
					q->rollno=t.rollno;
					strcpy(q->name,t.name);

				}
				q=q->next;
			}
			p=p->next;
		}
	}//IF
	else if(op=='M'||op=='m')
	{
		//sort by marks
		p=hp;
		while(p)
		{
			q=p->next;
			while(q)
			{
				if(p->marks>q->marks)
				{
					t.marks=p->marks;
					t.rollno=p->rollno;
					strcpy(t.name,p->name);

					p->marks=q->marks;
					p->rollno=q->rollno;
					strcpy(p->name,q->name);

					q->marks=t.marks;
					q->rollno=t.rollno;
					strcpy(q->name,t.name);
				}
				q=q->next;
			}
			p=p->next;
		}
	}
	else{
		printf("w\033[91m!OHO WRONG CHOICE REENTER\033[0m\n");
		goto l;}


}
void my_exit(void)
{	
	char op;
l:
	printf("\033[3;91mEnter the choice\nS/s:save and exit\nE/e:exit without saving\033[0m");
	scanf(" %c",&op);


	if(op=='S'||op=='s')
	{	save_file();
	}
	else if(op=='E'||op=='e')
	{
		//exit 
	}	
	else{
		printf("w\033[91m!OHO WRONG CHOICE REENTER\033[0m\n");
		goto l;
	}
	SLL *temp=hp;
	while(hp!=0)
	{
		temp=hp;
		hp=temp->next;
		free(temp);
	}
	exit(0);
}
void save_file(void)
{
	if(hp==0){
		printf("\033[91m!OHO NO RECORD TO SAVE\033[0m\n");
		return;}
	SLL *ptr=hp;
	FILE *fp=fopen("student.dat","w");
	while(ptr){
		fprintf(fp,"%d\t %s\t %f\n",ptr->rollno,ptr->name,ptr->marks);
		ptr=ptr->next;
	}

	fclose(fp);
}
void mod(void)
{
	if(hp==0){
		printf("\034[91m!OHO NO RECORD TO MODIFY\033[0m\n");
		return;}
	char op;
R:
	printf("\033[33mEnter the choice for modification \nR/r:based on rollno \nN/n:based on name \nM/m:based on marks\033[0m\n");
	scanf(" %c",&op);
	if(op=='r'||op=='R')
	{
		int rn;
		SLL *m=hp;
		printf("\033[95mEnter the record rollno to modify:\n");
		scanf("%d",&rn);
		while(m)
		{
			if(m->rollno==rn){
				int newrollno;
n:
				printf("Enter new rollno:\033[0m\n");
				scanf("%d",&newrollno);
				SLL *new=hp;
				while(new){
					if(newrollno==new->rollno)
					{
						printf("\033[5;91m SORRY NO IDENTICAL ROLLNO ALLOWED:\n\033[0m");
						goto n;
					}
					new=new->next;
				}
				m->rollno=newrollno;
				return;
			}
			m=m->next;
		}
		printf("\033[91m!OHO NO SUCH TYPE RECORD FOUND\033[0m\n");
	}
	else if(op=='N'||op=='n')
	{
		int rn;
		SLL *m=hp;
		char name[20];
		printf("\033[95mEnter the record rollno and name to modify:\n");
		scanf("%d%s",&rn,name);
		while(m)
		{
			if((m->rollno==rn)&&(strcmp(m->name,name)==0)){
				printf("Enter new name:\033[0m\n");
				scanf("%s",m->name);
				return;
			}
			m=m->next;
		}
		printf("\033[91m!OHO NO SUCH TYPE RECORD FOUND\033[0m\n");
	}
	else if(op=='m'||op=='M')
	{
		int rn,marks;
		SLL *m=hp;

		printf("\033[95mEnter the record rollno and marks to modify:\n");
		scanf("%d%d",&rn,&marks);
		while(m)
		{
			if((m->rollno==rn)&&(m->marks==marks)){
				printf("Enter new marks:\033[0m\n");
				scanf("%f",&m->marks);
				return;
			}
			m=m->next;
		}
		printf("\033[91m!OHO NO SUCH TYPE RECORD FOUND\033[0m\n");
	}
	else {
		printf("\033[91mOHO wrong choice reenter:\033[0m\n");
		goto R;

	}
}
void delete(void)
{
	if(hp==0){
		printf("\033[91m!OHO NO RECORD TO DELETE\033[0m\n");
		return;}
	char op;
R:
	printf("\033[95mEnter the choice \nR/r:based on rollno \nN/n:based on name\n");
	scanf(" %c",&op);
	SLL *del=hp,*prev;
	if(op=='R'||op=='r')
	{       int num;
l:
		printf("Enter the rollno:\033[0m");
		scanf("%d",&num);
		if(hp->rollno==num){
			hp=hp->next;
			free(del);
			return;
		}
		else
		{
			del=hp;
			while(del)
			{
				if(del->rollno==num)
				{
					prev->next=del->next;
					free(del);
					return;
				}
				prev=del;
				del=del->next;
			}

		}
		printf("\033[91m!OHO NO RECORD TO DELETE\033[0m\n");
	}//rollno
	else if(op=='n'||op=='N')
	{       
		char name[20];

		printf("\033[95mEnter the name:\033[0m");
		scanf("%s",name);
		{
			int c=0;
			SLL *p=hp;
			while(p)
			{if(strcmp(p->name,name)==0)
				c++;
				p=p->next;
			}
			if(c>1)
			{
				p=hp;
				printf("\033[91mOHO identical record found:\033[0m\n");
				while(p){
					if(strcmp(p->name,name)==0)
						printf("%d\t%s\t%f\n",p->rollno,p->name,p->marks);
					p=p->next;
				}
				goto l;
			}
		}
		if(strcmp(hp->name,name)==0){
			hp=hp->next;
			free(del);
			return;
		}
		else
		{
			del=hp;
			while(del)
			{
				if(strcmp(del->name,name)==0)
				{
					prev->next=del->next;
					free(del);
					return;
				}
				prev=del;
				del=del->next;
			}

		}
		printf("\033[91m!OHO NO SUCH TYPE RECORD FOUND\033[0m\n");
	}//name
	else
	{
		printf("\033[91mOHO wrong choice reenter:\033[0m\n");
		goto R;


	}
}
void show(void)
{
	if(hp==0){
		printf("\033[91m!OHO NO RECORD TO SHOW\033[0m\n");
		return;}
	SLL *ptr=hp;
	printf("\033[92mrollno \t name \t marks\033[0m\n");
	while(ptr){
		printf("\033[92m%d\t %s\t %f\n\033[0m",ptr->rollno,ptr->name,ptr->marks);
		ptr=ptr->next;
	}


}
void add(void)
{
	int rn=0;
	SLL *search=hp,*n=calloc(1,sizeof(SLL));
	printf("\033[95mEnter the name and marks:\033[0m\n");
	scanf("%s%f",n->name,&n->marks);
	if(hp==0)
	{
		n->rollno=1;
		hp=n;
	}
	else{
		for(rn=1;;rn++)
		{
			search=hp;
			int flag=0;
			while(search)
			{	
				if(rn==search->rollno)
				{
					flag=1;
					break;
				}
				search=search->next;

			}
			if(flag==0)
				break;
		}
		n->rollno=rn;
		SLL *insert=hp;
		if(hp->rollno>rn)
		{
			n->next=hp;
			hp=n;
		}
		else{
			while((insert->next!=0)&&(insert->next->rollno<rn))
			{
				insert=insert->next;
			}
			n->next=insert->next;
			insert->next=n;}
	}//else

}//func


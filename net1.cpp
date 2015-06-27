#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>
#define PATH "soumya41.txt"//adjacency matrix
#define PATH1 "soumya3.txt"//traffic matrix
#define MAX 9999
#define N 4
struct node{
	struct node *link;
	int data;
};
int **arrr,s1,n,F,*dist,*stack,top=0,***wave,w,**traffic1,w1=0,*T,*R, blocked, k4, served,k5,**trans1,**rec1,asd,length,min4,***path,**traffic2,ulti,**traffic3,*arr,**list,****paths,*mark,top1=-1,**hopcount;
float S,D;
void copy_1(int *);
void DFS(int ,int );
int distance(int *);
int **sort(int **);
void pathfind();
int *reverse(int *);
void show();
int weight(int *);
int wave_assign();//the wavelengths get revised after an assignment
void SPT(int ,int);//finds the path
int **creat(int );//creats adjacency matrix
void display(int **,int );//display a 2d array
int shortpath(int **,int ,int ,int );//find shortest path take input as adjacency matrix,v1,v2,total no of vertices
void creat_wave(int );//craets a 3d matrix to store the wavelengths
void disp1(int );//display a 3d array
int **creat_traffic();//creats a traffic matrix randomly
int **copy(int **);//copy a 2d matrix into another
int rand_int(int, char);
void SPT2(int ,int );
void SPT1();
void LCP1(int ,int );
void storepath();
int *filter(int **);
void packit(int ,int );
int main()
{
	int i,j,k,**traffic,**arr1,**traffic0;
	arrr=creat(1);
	pathfind();
	top=-1;
//	show();
	storepath();
	
	k4=5,k5=5,w=1;
  while(w<=15)
 {
 	w1=0;S=0;D=0;
	printf("\n No of wavelength== %d \n",w);
	F=2;
	traffic1=creat(3);
    traffic0=copy(traffic1); 
   creat_wave(w);
    i=wave_assign();
   
   printf("\n ---> served Trail==%d,blocked== %d ,Wavelength Consumed= %d, Delay= %.6f \n",served,s1-served,w1+1,(S+(D*2))/(S+D));
   //disp1(w);
   w1=0;S=0;D=0;
      F=3;
      storepath();
   traffic1=copy(traffic0); 
  // display(traffic1,n);
    //arrr=creat(1);
   creat_wave(w);
   i=wave_assign();
  printf("\n ---> served Tlcp==%d,blocked==%d ,Wavelength Consumed=%d, Delay= %.6f \n",served,s1-served,w1+1,(S+(D*2))/(S+D));
   w++;
 }

     /* s3=0;w=6;
      for(s3=1;s3<=9;s3++)
    {
      	printf("\n\n no of transmiiter and receiver ==%d\n",s3);
        k4=s3;k5=s3;s1=0;s2=0;
      for(s4=1;s4<=30;s4++)
       {
      	F=0;
         traffic1=creat(3);
         traffic0=copy(traffic1); 
         creat_wave(w);
          i=wave_assign();
         
		 s1+=served;
      
          F=1;
          
		 creat_wave(w);
         traffic1=copy(traffic0);
          i=wave_assign();
          s2+=served;
       }
        printf("\n\n\nAverage served using SPT= %d\n",s1/30);
		printf("\n\n\nAverage served using SPT1 = %d\n",s2/30);           
	 
      }*/
    
}
int **creat(int f)//creats adjacency matrix
{
	char arr[100],c;int i=0,j,k,n1,i1,l,**arrr1;FILE *ptr;
	if(f==1) 
	ptr=fopen(PATH,"r");
	if(f==2)
	ptr=fopen(PATH1,"r");
	if(f==3)
	return creat_traffic();
	fgets(arr,80,ptr);
    i=0;n=0;
	while(arr[i]!='\n')// gets the total no of vertex
	{
		k=arr[i]-'0';
		n=(n*10)+k;
		i++;
	}
	arrr1=(int **)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++)
	arrr1[i]=(int *)malloc(sizeof(int)*n);
	n1=0;i=0;j=0;k=0;
	for(i=0;i<n;i++,j=0)
	{
	 fgets(arr,80,ptr);i1=0;
	 l=strlen(arr)-1;
	  for(i1=0;i1<=l;i1++)
	   {
	     if(isdigit(arr[i1]))
	     {
	      k=0;
	      k=arr[i1]-'0';
	       n1=n1*10+k;
	      if((i==n-1)&&(j==n-1))
	      arrr1[i][j]=n1;	
	     }
	    else
        {
         arrr1[i][j]=n1;
	     n1=0;j++;
	    }
	   }
	}
	fclose(ptr);
	return arrr1;
}
void display(int **arr,int n)//display a 2d array
{
	int i,j;
	for(i=0;i<n;i++)
	{
	  printf("\n");
	  for(j=0;j<n;j++)
       printf(" %d  ",arr[i][j]);
    }
	
}
int shortpath(int **arr,int u,int v,int n)//find shortest path take input as adjacency matrix,v1,v2,total no of vertices
{
	int i,j,k;
	//0 values are already updated to MAX
	for(k=0;k<n;k++)
    for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    if(arr[i][j]>arr[i][k]+arr[k][j])
    arr[i][j]=arr[i][k]+arr[k][j];
    return arr[u][v];
	
}

void SPT(int u,int v)//find shortest path
{
	int *l,*la,lsize=-1,lasize=0,ch,f=0,i,j,k,k1,min2,min1;
	struct node **tree,*p,*q;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	if(arrr[i][j]==0)
	arrr[i][j]=MAX;
	dist=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	dist[i]=MAX;//distance array stores distance of every node from source
	dist[u]=0;
	l=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		if(i!=u)
		{
		 lsize++;
		 l[lsize]=i;
		}
	
	}
	la=(int *)malloc(sizeof(int)*n);
	la[lasize]=u;
	stack=(int *)malloc(sizeof(int)*n);
	tree=(struct node **)malloc(sizeof(struct node *)*n);
	for(i=0;i<n;i++)
   {
	tree[i]=0;
	stack[i]=MAX;
   }
	min2=MAX;
	while(lsize>=0)//finding of minimum distance node
	{
		min2=MAX;
		for(i=0;i<=lasize;i++)
		{
			ch=la[i];
		    for(j=0;j<n;j++)
		   {   
		       if(((arrr[ch][j]+dist[ch])<=min2)&&(dist[j]==MAX))
			    {
				 min2=dist[ch]+arrr[ch][j];
                 k=ch;k1=j;
		     	}
		   }
	    }
	    if(min2!=MAX)//creation of shortest path tree
	    {
	    	dist[k1]=min2;
	    	if(tree[k]==0)
	    	{
	    		p=(struct node *)malloc(sizeof(struct node));
	    		tree[k]=p;
	    		p->data=k1;
	    		p->link=0;
	    	}
	    	else
	    	{
	    		p=tree[k];
	    		while(p!=0)
	    		{
	    			if(p->link==0)
	    			{
	    				q=(struct node *)malloc(sizeof(struct node));
	    				p->link=q;
	    				q->link=0;
	    				q->data=k1;
	    				break;
	    			}
	    			p=p->link;
	    		}
	    	}
	    	
	    }
	    if(k1==v)
	    break;
	    lasize++;
	    la[lasize]=k1;
	    for(i=0;i<lsize;i++)//update the value of l[] &&la[]
	    {
	    	if(l[i]==k1)
	    	{
	    	   l[i]=l[lsize];break; 
			}
		}
		lsize--;
		
	}
	top=0;
	stack[top]=v;
	i=0;
	while(i<n)//finding of path from tree using stack
	{
		p=tree[i];
		while(p!=0)
		{
			if(p->data==stack[top])
			{
				top++;
				stack[top]=i;
				i=-1;
			}
			p=p->link;
		}
		if(stack[top]==u)
		break;
		i++;
	}
}
void creat_wave(int w)//craets a 3d matrix to store the wavelengths
{
	int i,j,k;
	wave=(int ***)malloc(sizeof(int **)*w);
	for(i=0;i<w;i++)
	{
		wave[i]=(int **)malloc(sizeof(int *)*n);
		for(j=0;j<n;j++)
		wave[i][j]=(int *)malloc(sizeof(int)*n);
	}
	for(k=0;k<w;k++)
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{
	  if(arrr[i][j]!=0)
	  wave[k][i][j]=48;
	  if(arrr[i][j]==0)
	  wave[k][i][j]=0;
   }
}
void disp1(int w)//display a 3d array
{
	int i,j,k;
	for(i=0;i<w;i++)
	{
		printf("\n");
		for(j=0;j<n;j++)
		{
			printf("\n");
			for(k=0;k<n;k++)
			{
				printf("%4d",wave[i][j][k]);
			}
		}
	}
}
void packit(int u,int v)
{
	int k,k1,j2,lp,lq,k3,temp,*path2,i=0,j,tp,tp1=-1,**cb;
	path2=reverse(path[u][v]);
	while(path2[i]!=MAX)
	i++;
	tp=i-1;
	if(F==3)
	{
		path2=paths[u][v][ulti];
		while(paths[u][v][ulti][i]!=MAX)
		i++;
		tp=i-1;
	}
	
	cb=(int **)malloc(sizeof(int *)*(n*n));
	for(i=0;i<(n*n);i++)
	cb[i]=(int *)malloc(sizeof(int )*5);
	for(i=0;i<(n*n);i++)
	for(j=0;j<5;j++)
    cb[i][j]=MAX;
    //printf(" \n soumya %d\n",tp);
	for(j=tp;j>=1;j--)
	for(i=0;i<j;i++)
	if((i!=j)&&(traffic1[path2[i]][path2[j]]!=0))//finds all possible paths for grooming
	{
	//	printf(" \n soumya %d bbbbb\n",tp1);
		tp1++;
		cb[tp1][0]=traffic1[path2[i]][path2[j]];
		cb[tp1][1]=path2[i];
		cb[tp1][2]=path2[j];
	}
	
	
	for(j=tp1;j>=2;j--)// sort those paths according to bandwidth
	for(i=1;i<j;i++)
	{
		if(cb[i][0]<cb[i+1][0])
		{
			temp=cb[i][0];
			cb[i][0]=cb[i+1][0];
			cb[i+1][0]=temp;
			temp=cb[i][1];
			cb[i][1]=cb[i+1][1];
			cb[i+1][1]=temp;
			temp=cb[i][2];
			cb[i][2]=cb[i+1][2];
			cb[i+1][2]=temp;
		}
	}
	
	for(k=0;k<w;k++)//check if there is available wavelength for longest path
	{
		k1=0;
		stack=path[u][v];
		if(F==3)
		stack=reverse(paths[u][v][ulti]);
		for(i=tp;i>0;i--)
		{
			j=stack[i];j2=stack[i-1];
			if(wave[k][j][j2]==48)
			k1++;
		}
		if(k1==tp)
		{
			//printf("soumya");
			break;
		}
		
	}
	
/*  display(traffic1,n);
	disp1(w);
	printf("\n at first \n");
	for(i=0;i<=tp1;i++)
	{
		printf("\n bw==%d ,s==%d ,d== %d, T== %d,R == %d \n",cb[i][0],cb[i][1],cb[i][2],cb[i][3],cb[i][4]);
	}
*/	if((k1==tp)&&(trans1[u][n]<k4)&&(rec1[v][n]<k5))//if wavelength , transmitter , receiver is avilable
	{
		if(k>w1)
		w1++;
		cb[0][3]=1;
		cb[0][4]=1;
	//	printf("\n soumya 23\n");	
		for(j=tp;j>0;j--)
		wave[k][stack[j]][stack[j-1]]=48-cb[0][0];
	//	printf("\n soumya 2\n");	
		cb[0][0]=0;
		S++;
	/*	disp1(w);
		printf("\n after main \n");
		for(i=0;i<=tp1;i++)
	{
		printf("\n bw==%d ,s==%d ,d== %d, T== %d,R == %d \n",cb[i][0],cb[i][1],cb[i][2],cb[i][3],cb[i][4]);
	}*/
	         
		stack=reverse(path[u][v]);
		if(F==3)
		stack=paths[u][v][ulti];
		for(i=1;i<=tp1;i++)//for remaining paths
		{
			j=0;
			while(stack[j]!=cb[i][1])
			j++;lp=0;k3=0;lq=j;
			while(stack[j]!=cb[i][2])//checks if wavelength available
			{
				lp++;
				if(wave[k][stack[j]][stack[j+1]]>=cb[i][0])
				k3++;
				j++;
			}
			if((k3==lp)&&(trans1[cb[i][1]][n]<k4)&&(rec1[cb[i][2]][n]<k5))//if wavelength ,transmitter,receiver available
			{
				while(stack[lq]!=cb[i][2])
				{
					wave[k][stack[lq]][stack[lq+1]]=wave[k][stack[lq]][stack[lq+1]]-cb[i][0];
					lq++;
				}
				if(cb[i][3]==MAX)
				cb[i][3]=1;
				if(cb[i][4]==MAX)
				cb[i][4]=1;
				cb[i][0]=0;
           	/*			printf("\n after next  \n");
				for(j=0;j<=tp1;j++)
	          {
		       printf("\n bw==%d ,s==%d ,d== %d, T== %d,R == %d \n",cb[j][0],cb[j][1],cb[j][2],cb[j][3],cb[j][4]);
	          }*/
	         	S++;
             // 				disp1(w);  
			}
			
		}
	  	/*printf("\n after all  \n");
				for(j=0;j<=tp1;j++)
	          {
		       printf("\n bw==%d ,s==%d ,d== %d, T== %d,R == %d \n",cb[j][0],cb[j][1],cb[j][2],cb[j][3],cb[j][4]);
	          }
	    */
		for(i=0;i<n;i++)
		{
			temp=0;lp=0;
		  for(j=0;j<=tp1;j++)
		  {
		  	if((cb[j][1]==i)&&(cb[j][0]==0))
		  	temp=1;
		  	if((cb[j][2]==i)&&(cb[j][0]==0))
			lp=1;
		  }
		  if(lp==1)
		  rec1[i][n]=rec1[i][n]+1;
		  if(temp==1)
		  trans1[i][n]=trans1[i][n]+1;
		}
	/*	printf("\ntrans1\n ");
	          for(j=0;j<n;j++)
	          printf("%4d",trans1[j][n]);
	          printf("\n");
	          printf("\nrec1\n ");
	          for(j=0;j<n;j++)
	          printf("%4d",rec1[j][n]);
	          printf("\n");
			      
	*/			
		for(i=0;i<=tp1;i++)
		{
			if(cb[i][0]==0)
			{
				//printf("soumya %d ",i);
				traffic1[cb[i][1]][cb[i][2]]=0;
				traffic2[cb[i][1]][cb[i][2]]=0;
				hopcount[cb[i][1]][cb[i][2]]=0;
				
			}
		}
		
	}
	
	
	
	traffic2[u][v]=0;
	hopcount[u][v]=0;
//	display(traffic1,n);	
}
int wave_assign()//the wavelengths get revised after an assignment
{
    int maxtp,mink,**list1,i,j,k,k1,tp,i1,j1,min,f=0,k2=0,j2,l=0,f1=0,**trans,**rec,s2,**traffic5,*stack1,i3,i8;
	int t1, r1;
	float min6;
	T=(int *)malloc(sizeof(int)*n);
	R=(int *)malloc(sizeof(int)*n);

	for(i=0;i<n;i++)
	{
		T[i]=0;
	    R[i]=0;
	}
	
	trans=(int **)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++)
		trans[i]=(int *)malloc(sizeof(int)*n);
	
	rec=(int **)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++)
		rec[i]=(int *)malloc(sizeof(int)*n);
	
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{
		trans[i][j]=0;
		rec[i][j]=0;
	}
	
	trans1=(int **)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++)
		trans1[i]=(int *)malloc(sizeof(int)*(n+1));
	
	rec1=(int **)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++)
		rec1[i]=(int *)malloc(sizeof(int)*(n+1));
	
	for(i=0;i<n;i++)
	  for(j=0;j<=n;j++)
	{
		trans1[i][j]=0;
		rec1[i][j]=0;
	}

	traffic2=copy(traffic1);
	traffic3 = copy(traffic1);
	for(i=0;i<n;i++)
	 for(j=0;j<n;j++)
	if(traffic1[i][j]!=0)
		f++;
	while( k2 != (n*n) )
	{
		if(F==0)
	  {
		min=0;
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		if((traffic2[i][j]>0)&&(traffic2[i][j]>min))
		{
		  i1=i;
		  j1=j;
		  min=traffic2[i][j];
	    }
	    length=traffic2[i1][j1];
	  }
	  if(F==2)
	  {
	  	 //display(hopcount,n);
	  	 mink=0;
		 for(i=0;i<n;i++)
		 for(j=0;j<n;j++)
 	     if(hopcount[i][j]>=mink)
		  mink=hopcount[i][j];
	     //	printf("\n largest hopcount==%d\n",mink);  
	    min=0;
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		if((traffic2[i][j]>0)&&(traffic2[i][j]>min)&&(hopcount[i][j]==mink))
		{
		  i1=i;
		  j1=j;
		  min=traffic2[i][j];
	    }
	    //  printf(" \n largest value ==%d , %d to %d",traffic2[i1][j1],i1,j1);
	    length=traffic2[i1][j1];
	    packit(i1,j1); 
	  	
	    }
	  if(F==3)
	  {
//	  	display(traffic1,n);
//	  	printf("\n soumya1 \n");
	 	min=0;
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		if((traffic2[i][j]>0)&&(traffic2[i][j]>min))
		{
		  i1=i;
		  j1=j;
		  min=traffic2[i][j];
	    }
//	    printf("\n MAX req ==%d, %d to %d \n",traffic2[i1][j1],i1,j1);
	    min4=0;
		while(paths[i1][j1][min4]!=0)
		min4++;
		maxtp=0;
		for(i3=0;i3<min4;i3++)
		{
			stack=paths[i1][j1][i3];
			i8=0;
			while((stack[i8]!=MAX)&&(i8<n))
			i8++;
			tp=i8-1;
			stack=reverse(paths[i1][j1][i3]);
			for(k=0;k<w;k++)//check if there is available wavelength 
	      {
	     	 k1=0;
		     for(i=tp;i>0;i--)
		   {
			  j=stack[i];j2=stack[i-1];
			  if(wave[k][j][j2]==48)
			  k1++;
		   }
		  if(k1==tp)
		 break;
		 }
		 if((k1==tp)&&(tp>maxtp))
		 {
		 	maxtp=tp;
		 	ulti=i3;
		 }
			
		}
//		printf("\n path no %d \n",ulti);
		length=traffic2[i1][j1];
	    packit(i1,j1); 
	  } 
	  
        if(F==0)
		{
			stack=path[i1][j1];
			i=0;
			while((stack[i]!=MAX)&&(i<n))
			{
				i++;
			}
			top=i-1;
			dist[j1]=top*5;
		}
		
		/*if(F==1)
		{
			min4=0;
			while(paths[i1][j1][min4]!=0)
			min4++;
			min6=999.99;j=0;
			for(i=0;i<min4;i++)
			{
				if(min6>weight(paths[i1][j1][i])/top)
				{
				    min6=weight(paths[i1][j1][i])/top;
					j=i;
	      		}	
			}
		    stack=reverse(paths[i1][j1][j]);
		    dist=(int *)malloc(sizeof(int)*n);
		    dist[j1]=top*5;
		}*/
		
		/*if(F==1)
		{
		
		 stack=reverse(filter(paths[i1][j1]));
		 dist=(int *)malloc(sizeof(int)*n);
		 dist[j1]=top*5;
	    }*/
		//For dynamically path choose
		/*	min4=0;
		while(F==1)
		{
			LCP1(i1,j1);
			if(dist[j1]!=MAX)
			break;
			min4++;
			if(min4==w)
			break;
		}*/
	    
	    if((min!=0)&&(dist[j1]!=MAX)&&(F!=2)&&(F!=3))
		{
/*			 printf("\n bandwidth== %d\n",length);
			 if(dist[j1]!=MAX)
			{
			   printf("\n shortest path==%d\n",dist[j1]);
			   for(k=top;k>=0;k--)
              printf("-->%4d",stack[k]);
			}
			else
			printf("\nthere is no path \n");*/
			for(k=0;k<w;k++)
			{
				k1=0;f1=0;
				for(i=top;i>0;i--)//it checks whether wavelength is available or not
				{
					j=stack[i];j2=stack[i-1];
					if(wave[k][j][j2]>=length)
					k1++;
				}
				
				if(k1==top)//if available then the values of wave[][][]will be changed otherwise it will go for next wavelength
				{if((trans1[stack[top]][n]<k4)&&(rec1[stack[0]][n]<k5))
				  {
				  	trans1[stack[top]][n] +=1;
				  	rec1[stack[0]][n]+=1;
				  
				 	f1=1;
				 	 
				    for(i=top;i>0;i--)
				    {
					 j=stack[i];j2=stack[i-1];
					 wave[k][j][j2] =0;	// subtract occupied wavelength from the wavelength matrix
					 if(k>w1)
					 w1++;
				    }
				    S++;
				    traffic1[i1][j1]=0;
				    l++;
				  
				  }
				 
				 
				 //
				  i=stack[top];j=stack[top-1];
				  trans[i][j]=trans[i][j]+length;
				  //
				 // display(trans,n);
				  
				  i=stack[0];j=stack[1];
				  rec[i][j]=rec[i][j]+length;
				   /*printf("\n trans1 matrix\n");
				  for(i=0;i<n;i++)
				  {
				  
				   printf("\n");
				   for(j=0;j<=n;j++)
				   printf("%4d",trans1[i][j]);
			      }
			      printf("\n rec1 matrix\n");
			      for(i=0;i<n;i++)
				  {
				  
				   printf("\n");
				   for(j=0;j<=n;j++)
				   printf("%4d",rec1[i][j]);
			      }*/
				 
				 // printf("\n rec matrix\n");
				  //display(rec,n);
				  if(f1==1)
				  {
				  
				   /*printf("\n there is available bandwidth at wavelength no. %d \t",k+1);
				   printf("\n changed wavelength\n");
				   
				  disp1(w);
				   printf("\n changed traffic matrix\n");
				   display(traffic1,n);*/
				   break;
			      }
				}
			}
			if(f1==0)
			{
			/*  printf("\n no bandwidth avilable so no change at wave matrix");
			  
			  disp1(w);
			  
			  printf("\n unchanged traffic matrix\n");
			  display(traffic1,n);*/
		    }
	    }
		traffic2[i1][j1]=0;
		hopcount[i1][j1]=0;
		k2++;
	}
	//determination of required transmitter and receiver
	//no need as we have to leave one transmitter & receiver each time
	for(i=0;i<n;i++)
	{
	 s1=0;s2=0;
	 for(j=0;j<n;j++)
	 {  
	   s1=s1+(trans[i][j]/48);
	   if(trans[i][j]%48!=0)
	   s1++;
	   s2=s2+(rec[i][j]/48);
	   if(rec[i][j]%48!=0)
	   s2++;
	 }
	 if(s1>k4)
	 T[i]=s1-k4;
	 if(s2>k5)
	 R[i]=s2-k5;
    }
    //determination of blocked requests
    traffic5=copy(traffic3);
    //if(F==0)
	//SPT1();
    blocked=0;
    s1=0;
    for(i=0; i<n; i++)
    {
    	for(j=0; j<n; j++)
    	{
    		blocked += traffic1[i][j];
    		s1+= traffic5[i][j];
    	}
    }
    served = s1 - blocked;
    return (f-l);
}
int *filter(int **asd)
{
	int q,i=0,j,k=0,l=0,m,flag,p,f=1;
	while(asd[i]!=0)
	i++;
	for(j=0;j<i;j++)
	{
		k=0;
		while(asd[j][k]!=MAX)
		k++;
		for(l=0;l<w;l++)
		{
			flag=0;
			for(m=0;m<k-1;m++)
			{
				if(wave[l][m][m+1]!=0)
				flag++;
			}
			if(flag==k-1)
			{
				q=l;
				p=j;
				f=0;
				break;
			}
			
		}
	}
	if(f==1)
	return asd[0];
	else
	{
	 
	 return asd[p];
    }
}

int weight(int *asd)
{
	int i=0,j,flag=0,k,l,p;
	while((asd[i]!=MAX)&&(i<n))
	 i++;
    for(j=0;j<i-1;j++)
	{
	 k=asd[j];l=asd[j+1];
	 for(p=0;p<w;p++)
	 if(wave[p][k][l]==0)
	    flag++;
	}
	top=i;
   return flag;
}
int **creat_traffic()//creats a traffic matrix by puting random values
{
	time_t t;
	int **arr,i,j,k;
	srand((unsigned) time(&t));
	arr=(int **)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++)
	arr[i]=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{
		k=rand_int(12,1);
		if(i==j)
		arr[i][j]=0;
		else 
		{
		 if(k<6)
		 arr[i][j]=1;
		 else if(k<10)
		 arr[i][j]=3;
		 else //if(k<14)
		 arr[i][j]=12;
		 //else
		 //arr[i][j]=48;
	   }
	}
	return arr;
}
int **copy(int **traffic3)//copy a 2d matrix
{
	
	int i,j,**traffic2;
	traffic2=(int **)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++)
	traffic2[i]=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	traffic2[i][j]=traffic3[i][j];
	return traffic2;
}
int rand_int(int a, char refresh)
{ int ret, t, p, s;
 static int size1, *arr;
 if(refresh)
 {
     arr=(int *)malloc(sizeof(int)*a);
     for(s=0; s<a; s++)
         arr[s]=s+1;
     size1=a;
 }
 p=rand()%size1;
 ret=arr[p];
 t=arr[size1-1];
 arr[p]=t;
 arr[size1-1]=ret;
 size1--;
 return ret;
}
void LCP1(int u,int v)//find shortest path
{
		int *l,*la,lsize=-1,lasize=0,ch,f=0,i,j,k,k1,min2,min1;
	struct node **tree,*p,*q;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	if(arrr[i][j]==0)
	arrr[i][j]=MAX;
	dist=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	dist[i]=MAX;//distance array stores distance of every node from source
	dist[u]=0;
	l=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		if(i!=u)
		{
		 lsize++;
		 l[lsize]=i;
		}
	
	}
	la=(int *)malloc(sizeof(int)*n);
	la[lasize]=u;
	stack=(int *)malloc(sizeof(int)*n);
	tree=(struct node **)malloc(sizeof(struct node *)*n);
	for(i=0;i<n;i++)
   {
	tree[i]=0;
	stack[i]=MAX;
   }
	min2=MAX;
	while(lsize>=0)//finding of minimum distance node
	{
		min2=MAX;
		for(i=0;i<=lasize;i++)
		{
			ch=la[i];
		    for(j=0;j<n;j++)
		   {   if(wave[min4][ch][j]>0)
		       if(((arrr[ch][j]+dist[ch])<=min2)&&(dist[j]==MAX))
			    {
				 min2=dist[ch]+arrr[ch][j];
                 k=ch;k1=j;
		       }
		   }
	    }
	    if(min2!=MAX)//creation of shortest path tree
	    {
	    	dist[k1]=min2;
	    	if(tree[k]==0)
	    	{
	    		p=(struct node *)malloc(sizeof(struct node));
	    		tree[k]=p;
	    		p->data=k1;
	    		p->link=0;
	    	}
	    	else
	    	{
	    		p=tree[k];
	    		while(p!=0)
	    		{
	    			if(p->link==0)
	    			{
	    				q=(struct node *)malloc(sizeof(struct node));
	    				p->link=q;
	    				q->link=0;
	    				q->data=k1;
	    				break;
	    			}
	    			p=p->link;
	    		}
	    	}
	    	
	    }
	    if(k1==v)
	    break;
	    lasize++;
	    la[lasize]=k1;
	    for(i=0;i<lsize;i++)//update the value of l[] &&la[]
	    {
	    	if(l[i]==k1)
	    	{
	    	   l[i]=l[lsize];break; 
			}
		}
		lsize--;
		
	}
	top=0;
	stack[top]=v;
	i=0;
	while(i<n)//finding of path from tree using stack
	{
		p=tree[i];
		while(p!=0)
		{
			if(p->data==stack[top])
			{
				top++;
				stack[top]=i;
				i=-1;
			}
			p=p->link;
		}
		if(stack[top]==u)
		break;
		i++;
	}
}

void storepath()
{
	int i,j,k;
	path=(int ***)malloc(sizeof(int **)*n);
	for(i=0;i<n;i++)
	path[i]=(int **)malloc(sizeof(int *)*n);
	hopcount=(int **)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++)
	hopcount[i]=(int *)malloc(sizeof(int )*n);
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{
		if(i!=j)
		{
			SPT(i,j);
			hopcount[i][j]=top;
			path[i][j]=stack;
		}
	}

/*	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{
		if(i!=j)
		{
		
		 printf("\n %d th to %d \n",i,j);
		 stack=path[i][j];
		 k=0;
		 while(stack[k]!=MAX)
		 {
			printf("%4d-->",stack[k]);
			k++;
		 }
	    }
	}
	*/

}
void SPT1()
{
	int i,j,k=0,l=0,mik,**traffic2,i1,j1;
	traffic2=(int **)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++)
	traffic2[i]=(int *)malloc(sizeof(int)*n);
	traffic2=copy(traffic1);
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	if((i!=j)&&(traffic2[i][j]!=0))
	k++;
	while(l<k)
	{
		mik=0;
	
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			
		 if((traffic2[i][j]>mik)&&(traffic2[i][j]!=0))
		 {
		 	
		  mik=traffic2[i][j];
		  i1=i;j1=j;
	     }
		 
		}
	
		SPT2(i1,j1);
		traffic2[i1][j1]=0;
		l++;
	}
	
}
void SPT2(int u,int v)
{
	int i,j,k,l,*end,e1=-1,*start,s1=-1,iv,j1,j2,j3,j4;
	end=(int *)malloc(sizeof(int)*n);
	start=(int *)malloc(sizeof(int)*n);
/*	printf("\n i1==%d,j1=%d\n",u,v);
	printf("\n traffic1 \n");
	display(traffic1,n);
	printf("\ntraffic3\n");
	display(traffic3,n);
	disp1(w);*/
	for(i=0;i<n;i++)
	{
		if((i!=v)&&(traffic1[i][v]==0))	
		{
			if(((w*48)-traffic3[i][v])>=traffic1[u][v])
			{
			e1++;
			end[e1]=i;
		   }
	   }
	}
	
	for(i=0;i<n;i++)
	{
		if((i!=u)&&(traffic1[u][i]==0))
		{
			if(((w*48)-traffic3[u][i])>=traffic1[u][v])
			{
			 s1++;
			 start[s1]=i;
		    }
		}
	}
	/*printf("\n end \n");
	for(i=0;i<=e1;i++)
	printf("%4d",end[i]);
	printf("\n start \n");
	for(i=0;i<=s1;i++)
	printf("%4d",start[i]);*/
	for(i=0;i<=s1;i++)
	for(j=0;j<=e1;j++)
		if(start[i]==end[j])
		{
			D++;
		  traffic1[u][v]=0;
		  j3=start[i];
		  /*stack=path[u][i];
			
			while(stack[iv]!=MAX)
			{
				iv++;
			}
			top=iv-1;k=alpha[u][i];
		  for(iv=top;iv>0;iv--)
		  {
		   j1=stack[iv];j2=stack[iv-1];
		   wave1[k][j1][j2] =wave1[k][j1][j2]-traffic3[u][v];
		   	               // subtract occupied wavelength from the wavelength matrix
	     }
	     stack=path[j][v];
			
			while(stack[iv]!=MAX)
			{
				iv++;
			}
			top=iv-1;k=alpha[j][v];
		  for(iv=top;iv>0;iv--)
		  {
		   j1=stack[iv];j2=stack[iv-1];
		   wave1[k][j1][j2] =wave1[k][j1][j2]-traffic3[u][v];
		   	               // subtract occupied wavelength from the wavelength matrix
	     }*/
	     traffic3[u][j3]=traffic3[u][j3]+traffic3[u][v];
	     traffic3[j3][v]=traffic3[j3][v]+traffic3[u][v];
	     traffic3[u][v]=0;
		 break;	  
	    }
	    
	
	/*printf("\ntraffic1\n");
	display(traffic1,n);
	printf("\ntraffic3\n");
	display(traffic3,n);
	disp1(w);*/
}
void pathfind()
{
	int i,j,k;
	mark=(int *)malloc(sizeof(int)*n);
	arr=(int *)malloc(sizeof(int)*n);
	paths=(int ****)malloc(sizeof(int ***)*n);
	for(i=0;i<n;i++)
	{
	 paths[i]=(int ***)malloc(sizeof(int **)*n);
	
    }
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{
		if(i!=j)
		{
		 list=(int **)malloc(sizeof(int *)*pow(n,N));
		 for(k=0;k<n;k++)
		   mark[k]=0;
		  for(k=0;k<pow(n,N);k++)
         list[k]=0;
		 mark[i]=1;
		 top=0;
		 top1=-1;
		 arr[top]=i;
	     DFS(i,j);
		 paths[i][j]=list;
		}
	}
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	if(i!=j)
	paths[i][j]=sort(paths[i][j]);
}
int **sort(int **paths1 )
{
	int n1=0,i,j,k,*temp1;
	while(paths1[n1]!=0)
	n1++;
	for(i=n1-1;i>=0;i--)
	for(j=0;j<i;j++)
	if(distance(paths1[j])>distance(paths1[j+1]))
	{
		temp1=paths1[j];
		paths1[j]=paths1[j+1];
		paths1[j+1]=temp1;
	}
	return paths1;
	
}
int distance(int *paths1)
{
	int i=0;
	while(paths1[i]!=MAX)
	i++;
	return i;
}
void DFS(int s,int d)
{
int i,l;
for(i=0;i<n;i++)
{
	if((arrr[s][i]!=0)&&(mark[i]==0))
	{
		
		if(i!=d)
		{
			top++;
			mark[i]=1;
			arr[top]=i;
			DFS(i,d);
			mark[i]=0;
		}
		if(i==d)
		{
		    top++;
			arr[top]=d;
			copy_1(arr);
	
		}
	top--;	
	}
	
}	
}
void copy_1(int *arr)
{
	
	int *arr1,i;
	arr1=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	arr1[i]=MAX;
	for(i=0;i<=top;i++)
	arr1[i]=arr[i];
	top1++;
	list[top1]=arr1;
}
void show()
{
	int i,j,k,l;
	for(k=0;k<n;k++)
	for(l=0;l<n;l++)
	{
		if(k!=l)
		{
		
		 printf("\n%d th to %d th node all paths are \n",k,l);
         i=0;
         while(paths[k][l][i]!=0)
         {
	
	      j=0;
	     while((paths[k][l][i][j]!=MAX)&&(j<n))
	      {
	
	       printf("%4d-->",paths[k][l][i][j]);
	       j++;
          }
          printf("\n");
		  i++;   
         }
	    }
    }
}
int *reverse(int *asd)
{
	    int i=0,j,*stack1;
	while(asd[i]!=MAX)
		i++;
	    
		
		stack1=(int *)malloc(sizeof(int)*n);
		for(j=0;j<n;j++)
		stack1[j]=MAX;
        for(j=0;j<=i-1;j++)
		stack1[j]=asd[i-j-1];
		top=i-1;
		return stack1;
		
}

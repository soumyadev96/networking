#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#define PATH "soumya.txt"//adjacency matrix
#define PATH1 "soumya1.txt"//traffic matrix
#define MAX 9999
struct node{
	struct node *link;
	int data;
};
int **arrr,n,*dist,*stack,top=-1,***wave,w,**traffic1,w1=0,*T,*R, blocked, k4, served,k5,**trans1,**rec1,asd;
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
int main()
{
	int i,j1,j,k,**traffic,**arr1,**traffic0, totserv=0,l;
	arrr=creat(1);
	display(arrr,n);
	/*printf("\n enter two vertices to determine the shortes path ");
	scanf("%d%d",&i,&j);
    SPT(i,j);
    printf("\n shortest path between %d to %d ==%d\n path  ",i,j,dist[j]);
    for(k=top;k>=0;k--)
    printf("-->%4d",stack[k]);
    printf("\n shortest path between %d to %d = %d \n",i,j,shortpath(arrr,i,j,n));*/
    //printf("\n enter no of wavelength\n");
    //scanf("%d",&w);
    //disp1(w);
    // printf("\n traffic\n");
    //display(traffic1,n);
   // printf("\nEnter no. of transmitter and receiver in each node: ");
    //scanf("%d", &k4);
    

      w=12;k5=12;k4=12;
      /*totserv=0;
      for(j1=1;j1<=9;j1++)
      {
        k4=j1;totserv=0;
        printf("\n no of transmitter==%d \n",k4);
        for(j=1;j<=8;j++)
       {*/ 
	     creat_wave(w);
         traffic1=creat(3);
          display(traffic1,n);
         i=wave_assign();
        // printf("\nleft no of traffic==%d\n",i);
         display(traffic1,n);
         disp1(w);
        printf("\n no of wavelength==%d",w1+1);
       // printf("\n\n no of transmitter each node== %4d",j);
       // for(i=0;i<n;i++)
    	//{
    	// printf("\n Transmitter required at %d th node==%4d && receiver==%4d\n",i,T[i],R[i]);
    	 //printf("\n Transmitter used at %d th node==%4d && receiver==%4d\n",i,trans1[i][n],rec1[i][n]);
        //}    
         printf("\n\n Total blocked requests == %d \nTotal served requests == %d", blocked, served);
	    // totserv += served;
	   //}
	   //printf("\n\n\nAverage served = %d\n", totserv/8);
	   //printf("\n\n\nAverage served = %d\n", totserv/8);
     // }     
     
    
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
	tree[i]=0;
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
int wave_assign()//the wavelengths get revised after an assignment
{
	int i,j,k,k1,i1,j1,min,f=0,k2=0,length,j2,l=0,**traffic2,f1=0,**trans,**rec,s1,s2, **traffic3;
	int t1, r1;
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
		SPT(i1,j1);
		
		if((min!=0)&&(dist[j1]!=MAX))
		{
			 printf("\n bandwidth== %d\n",length);
			 if(dist[j1]!=MAX)
			{
			   printf("\n shortest path==%d\n",dist[j1]);
			   for(k=top;k>=0;k--)
              printf("-->%4d",stack[k]);
			}
			else
			printf("\nthere is no path \n");
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
				{
					i = stack[top], j = stack[top-1];t1=0;	
				  if(trans1[i][j] == 0)
				  {
				  	if(trans1[i][n]<=k4)
				  	{
				  	 t1=1;
				    }
				  }
				  if( trans1[i][j] != 0)
				  {
				  	if((trans1[i][j] + length > 48)&&(trans1[i][n]<=k4))
				  	{
				  		t1=1;
				  	}
				  	if(trans1[i][j] + length <= 48)
				  	{
				  		  t1=1;
				  	}
				  }
				  
				  
				  	i = stack[0], j = stack[1];r1=0;	
				  if(rec1[i][j] == 0)
				  {
				  	if(rec1[i][n]<=k5)
				  	{
				  	  r1=1;
				    }
				  }
				  if( rec1[i][j] != 0)
				  {
				  	if((rec1[i][j] + length > 48)&&(rec1[i][n]<=k5))
				  	{
				  	
				  		r1=1;
				  	}
				  	if(rec1[i][j]+length<=48)
				  	{
				  		r1=1;
				  	}
				  }
				  if((t1==1)&&(r1==1))
				  {
				  
					i = stack[top], j = stack[top-1];t1=0;	
				    if(trans1[i][j] == 0)
				   {
				  	 if(trans1[i][n]<=k4)
				  	 {
				  	
				  	   trans1[i][n] +=1;
				  	   trans1[i][j] += length;
				     }
				   }
				   if( trans1[i][j] != 0)
				   {
				  	if((trans1[i][j] + length > 48)&&(trans1[i][n]<=k4))
				  	{
				  		trans1[i][n] +=1;
				  		trans1[i][j] = trans1[i][j]%48;
				  	}
				  	if(trans1[i][j] + length <= 48)
				  	{
				  		  trans1[i][j] += length;
				  	}
				   }
				  
				  
				  	i = stack[0], j = stack[1];r1=0;	
				   if(rec1[i][j] == 0)
				   {
				  	 if(rec1[i][n]<=k5)
				  	{
				  	
				  	  rec1[i][n] +=1;
				  	  rec1[i][j] += length;
				    }
				   }
				   if( rec1[i][j] != 0)
				   {
				  	if((rec1[i][j] + length > 48)&&(rec1[i][n]<=k5))
				  	{
				  		rec1[i][n] +=1;
				  		rec1[i][j] = rec1[i][j]%48;
				  	}
				  	if(rec1[i][j]+length<=48)
				  	{
				  		rec1[i][j]+=length;
				  	}
				   }
			      
				 	 f1=1;
				 	 
				    for(i=top;i>0;i--)
				    {
					 j=stack[i];j2=stack[i-1];
					 wave[k][j][j2] = wave[k][j][j2]-length;	// subtract occupied wavelength from the wavelength matrix
					 if(k>w1)
					 w1++;
				    }
				    traffic1[i1][j1]=0;
				    l++;
				  
				  }
				 
				 
				 
				  i=stack[top];j=stack[top-1];
				  trans[i][j]=trans[i][j]+length;
				  //
				 // display(trans,n);
				  
				  i=stack[0];j=stack[1];
				  rec[i][j]=rec[i][j]+length;
				 /*  printf("\n trans1 matrix\n");
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
			      }
				*/ 
				 // printf("\n rec matrix\n");
				  //display(rec,n);
				  if(f1==1)
				  {
				  
				   printf("\n there is available bandwidth at wavelength no. %d \t",k+1);
				   printf("\n changed wavelength\n");
				   disp1(w);
				   printf("\n changed traffic matrix\n");
				   display(traffic1,n);
				   break;
			      }
				}
			}
			if(f1==0)
			{
			  printf("\n no bandwidth avilable so no change at wave matrix");
			  disp1(w);
			  printf("\n unchanged traffic matrix\n");
			  display(traffic1,n);
		    }
	    }
		traffic2[i1][j1]=0;
		k2++;
	}
	
	for(i=0;i<n;i++)//determination of required transmitter and receiver
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
    blocked=0;
    s1=0;
    for(i=0; i<n; i++)
    {
    	for(j=0; j<n; j++)
    	{
    		blocked += traffic1[i][j];
    		s1+= traffic3[i][j];
    	}
    }
    served = s1 - blocked;
    
    	
	return (f-l);
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
		k=rand_int(48,1);
		if(i==j)
		arr[i][j]=0;
		else 
		{
		 if(k<6)
		 arr[i][j]=1;
		 else if(k<10)
		 arr[i][j]=3;
		 else if(k<14)
		 arr[i][j]=12;
		 else
		 arr[i][j]=48;
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


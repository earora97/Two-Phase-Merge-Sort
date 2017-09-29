#include "header.h"

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	int order = 0, i = 0, fp, fp1, len=0,colarr[argc-3],yu;
	char arr[2],mychar;
	float memoryused;

	FOR(i,1,argc)
		cout << "argv[" << i << "] =" << argv[i] << endl; 

	FOR(i,0,argc-4)
	{
		mychar=argv[i+4][1];
		yu=(int)mychar-'0';
		colarr[i]=yu;
	}
	
	memoryused=atof(argv[2])*1024*1024;

	if(strcmp(argv[3],"asc")==0)
		order=1;
	
	cout << "Memory in Bytes" << memoryused << endl;

	fp=open(argv[1],O_RDONLY);
	fp1=read(fp,arr,1);
	i=0;

	int a[i],c=0,flag=0,j,k,numberofrec;
	while(arr[0]!='\n')
	{

		if(arr[0]!=' '){
			c++;
			flag=0;
		}
		else
		{
		    flag++;
		    if(flag==2){
			    a[i]=c;
			    i++;
			    c=0;
		    }
		}
		fp1=read(fp,arr,1);
	}

	close(fp);
	a[i]=c;
	FOR(j,0,i+1)
		len=len+a[j];

	len=len-1;
	cout << "Each Record Size is " << len << " Bytes" << endl;
	numberofrec=(float)memoryused/(float)len;
	cout <<"Number of Records that can fit into given Memory are :" <<  numberofrec << endl;

	char ***str;
	str = (char ***) malloc(len*numberofrec);

	FOR(j,0,numberofrec)
	{
		str[j]= (char **) malloc (len);
		FOR(k,0,i+1)
			str[j][k]=(char * ) malloc (a[k]+1);
	}

	int fp2,fp3,f=64,total=0,p,q,r;
	fp2=open(argv[1],O_RDONLY);
	char F[2];

	while(1){
		f++;
		p=0;
		q=0;
		r=0;
		F[0]=(char)f;
		F[1]='\0';
		int flag1=0;
		fp3=read(fp2,str[0][0],a[0]);

		while(p<numberofrec && fp3!=0)
		{
			FOR(q,1,i+1)
			{
				if(q!=i)
				{
				fp3=read(fp2,arr,1);
				fp3=read(fp2,arr,1);
				fp3=read(fp2,str[p][q],a[q]);
				}
				else
				{
				fp3=read(fp2,arr,1);
				fp3=read(fp2,arr,1);
				fp3=read(fp2,str[p][q],a[i]);
				fp3=read(fp2,arr,1);
			   	}
			}
			p++;
			if(p!=numberofrec){
				fp3=read(fp2,str[p][0],a[0]);
			}
		}

		if(fp3==0 && q==0){
			f--;
			break;
		}

		int fp4,g,h;
		fp4 = open(F, O_CREAT | O_RDWR | O_TRUNC, 0777);

		if(p==1){
			;
		}
		else{
			sort_func(str,0,p-1,argc,colarr,order);
		}
		FOR(g,0,p)
		{
			total++;
			FOR(h,0,i+1)
				write(fp4,str[g][h],a[h]);
		}

		FOR(g,0,p)
		{
			FOR(h,0,i+1)
				strcpy(str[g][h],"\0");
		}
		if(fp3==0){
			break;
		}
	    
	}

	f=f-63;
	float arrsize=memoryused/f;
	int nofr=arrsize/len,flagarr[f],FP[f],FP1[f],counter[f],packarr[f];
	if(nofr==0)
	{
		cout << "The sorting is not feasabile in this case" << endl;
		exit(0);
	}

	flagarr[0]=0;p=0;q=0;
	FOR(p,1,f)
		flagarr[p]=flagarr[p-1]+nofr;

	FOR(p,0,f)
	{
		packarr[p]=0;
		counter[p]=0;
	}

	FOR(p,0,f-1)
	{
		int g=65+p,k=flagarr[p],h;
		F[0]=(char)g;
		F[1]='\0';
		FP[p]=open(F,O_RDONLY);

		while(k<flagarr[p+1]){
			FOR(h,0,i+1){
				FP1[p]=read(FP[p],str[k][h],a[h]);
				if(FP1[p]==0){
					counter[p]=1;
				}
		    	}
			k++;
		}
	}
	int can=0,fl3=0,g,flagnul=-1,newvar2=0;
	int FPO = open("Output.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);

	while(can<total){
		int h=colarr[0],flag1=0,min,t;
		FOR(p,0,f-1)
		{
			if(strcmp(str[flagarr[p]+packarr[p]][0],"\0")!=0){
				min=flagarr[p]+packarr[p];
				break;
			}
		}
		FOR(p,0,f-1)
		{
				if(strcmp(str[flagarr[p]+packarr[p]][0],"\0")!=0){
					if(order==1){
					if(strcmp(str[flagarr[p]+packarr[p]][h],str[min][h])<0){
						min=flagarr[p]+packarr[p];
			  		}
					else if(strcmp(str[flagarr[p]+packarr[p]][h],str[min][h])==0){
						FOR(t,1,argc-4){
							if(strcmp(str[flagarr[p]+packarr[p]][colarr[t]],str[min][colarr[t]])<0){
								min=flagarr[p]+packarr[p];
								break;
			  				}
						else if(strcmp(str[flagarr[p]+packarr[p]][colarr[t]],str[min][colarr[t]])>0){
							break;
						}
						}
					}
					}
				if(order==0){
					if(strcmp(str[flagarr[p]+packarr[p]][h],str[min][h])>0){
						min=flagarr[p]+packarr[p];
			  		}
					else if(strcmp(str[flagarr[p]+packarr[p]][h],str[min][h])==0){
						FOR(t,1,argc-4){
							if(strcmp(str[flagarr[p]+packarr[p]][colarr[t]],str[min][colarr[t]])>0){
								min=flagarr[p]+packarr[p];
								break;
			  				}
							else if(strcmp(str[flagarr[p]+packarr[p]][colarr[t]],str[min][colarr[t]])<0){
								break;
							}
						}
					}
				}
		    }
		}
		FOR(h,0,i+1){
			strcpy(str[flagarr[f-1]+packarr[f-1]][h],str[min][h]);
		}

			packarr[f-1]++;
			if(packarr[f-1]==nofr){
			    for(k=flagarr[f-1];k<flagarr[f-1]+nofr;k++){
				FOR(h,0,i+1)
				{
					write(FPO,str[k][h],a[h]);
					if(h!=i)
			    			write(FPO,"  ",2);
				}
			    write(FPO,"\n",1);
			    }
			    packarr[f-1]=0;
			    for(k=flagarr[f-1];k<flagarr[f-1]+nofr;k++){
					FOR(h,0,i+1){
					strcpy(str[k][h],"\0");
				}
			    }
			}
		
		int fl3=0;

	FOR(p,0,f-1){
		int fl4=1;
			if(flagarr[p]+packarr[p]==min){
				packarr[p]++;
				if((packarr[p]+flagarr[p])==flagarr[p+1]){
					for(k=flagarr[p];k<flagarr[p+1];k++){
					   	for(h=0;h<=i;h++){
							strcpy(str[k][h],"\0");
						}
					}
					for(k=flagarr[p];k<flagarr[p+1];k++){
					   	for(h=0;h<=i;h++){
						      FP1[p]=read(FP[p],str[k][h],a[h]);	
						      if(FP1[p]==0 && k==flagarr[p]){
							      counter[p]=1;
							      break;
						      	}
						      else if(FP1[p]==0){
							   counter[p]=1;
						      }
						   }
					   	}
						packarr[p]=0;
					}
				break;
			}
		}
		can++;
	}
		int fi,ff;
		if(packarr[f-1]!=0){

			    for(fi=flagarr[f-1];fi<flagarr[f-1]+packarr[f-1];fi++){
				for(ff=0;ff<=i;ff++){
					write(FPO,str[fi][ff],a[ff]);
					if(ff!=i)
			    write(FPO,"  ",2);
					}
				write(FPO,"\n",1);
			}
		}
	cout << "Number of Records Sorted are:" << can << endl; 
	remove(F);
}

int comparefunc(char **it,char **y,int var1,int iter[])
{
	int i,j,x=var1-4;
	FOR(i,0,x)
	{
		j=iter[i];
		if(strcmp(it[j],y[j])!=0)
		{
			if(strcmp(it[j],y[j])>0)
				return 1;
			else
				return -1;
		}
		else
		 	continue;
	}
	if(i==x)
		return 0;
}

void sort_func(char ***str, int left, int right,int argc,int iter[],int ord)
{
    int i=left, j=right;
    char **x,**temp;
    x = str[(left+right)/2];

	do {
		if(ord==1){
			while((comparefunc(str[i],x,argc,iter) < 0) && (i < right)) {
				i++;
			}
			while((comparefunc(str[j],x,argc,iter) > 0) && (j > left)) {
				j--;
			}
			if(i <= j) {
				temp=str[i];
				str[i]=str[j];
				str[j]=temp;
				i++;
				j--;
			}
		}

		else if(ord==0){

			while((comparefunc(str[i],x,argc,iter) > 0) && (i < right)) {
				i++;
			}
			while((comparefunc(str[j],x,argc,iter) < 0) && (j > left)) {
				j--;
			}
			if(i <= j) {
				temp=str[i];
				str[i]=str[j];
				str[j]=temp;
				i++;
				j--;
			}
		}
	} 
	while(i <= j);
	if(left < j) {
		sort_func(str, left, j,argc,iter,ord);
	}
	if(i < right) {
		sort_func(str, i, right,argc,iter,ord);
	}

}

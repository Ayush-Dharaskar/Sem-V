#include <stdio.h>

int main()
{

	int process,resoures;

	printf("Enter number of processes and number of resources: ");
	scanf("%d %d",&process ,&resoures);

	int maxi[process][resoures], alloc[process][resoures], need[process][resoures], avail[resoures], finish[process]={0};


	printf("Enter all available resources: ");
	for(int i=0; i<resoures;i++)
	{
		scanf("%d",&avail[i]);
		
	}


	for(int i=0;i<process;i++)
	{
		printf("Enter maximum resources for process %d: ",i+1);
		for(int j=0;j<resoures;j++)
		{

			scanf("%d",&maxi[i][j]);
		}
	}

	for(int i=0;i<process;i++)
	{
		printf("Enter allocated resources for process %d: ",i+1);
		for(int j=0;j<resoures;j++)
		{

			scanf("%d",&alloc[i][j]);
		}
	}

	for(int i=0;i<process;i++)
	{

		for(int j=0;j<resoures;j++)
		{

			need[i][j] = maxi[i][j] - alloc[i][j];
		}
		finish[i]=0;
	}

	int safeseq[process];

	int fin =0;
	
	while(fin < process)
	{
		int deadlock=0;
		for(int i=0;i<process;i++)
		{
			if(finish[i] == 0)
			{
				int flag=0;
				for(int j=0;j<resoures;j++)
				{
					if(need[i][j] > avail[j])
					{
						flag=1;
						break;
					}
				}

				if(flag==0)
				{
					safeseq[fin] = i;
					fin++;
					finish[i]=1;
					for(int j=0;j<resoures;j++)
					{
						avail[j] += alloc[i][j]; 
					}
					deadlock=1;	

				}
			}
		}
		if(!deadlock)
		{
			printf("UNSAFE STATE!\n");
			return 0;
		}


	}
	printf("Safe Sequenece: ");
	for(int i=0;i<process;i++)
	{
		printf("%d ",safeseq[i]);
	}

	return 0;





}
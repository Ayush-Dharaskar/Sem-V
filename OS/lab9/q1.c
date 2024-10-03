#include<stdio.h>

int main()
{
	int p,m;

	printf("Enter number of processes and number of memory holes: ");
	scanf("%d %d",&p,&m);

	int process_size[p], hole_size[m],allocated[p];

	for(int i=0;i<p;i++)
	{
		allocated[i]=-2;
		printf("Size of Process %d: ",i+1);
		scanf("%d",&process_size[i]);
	}

	for(int i=0;i<m;i++)
	{
		printf("Size of Hole %d: ",i+1);
		scanf("%d",&hole_size[i]);
	}

	int original_hole_size[m];
	for (int i = 0; i < m; i++) {
        original_hole_size[i] = hole_size[i]; // Store original sizes
    }

    
	//FIRST FIT
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(process_size[i] <= hole_size[j])
			{
				hole_size[j] -= process_size[i];
				allocated[i]= j;
				break;
			}

		}
	}

	printf("First Fit Allocations: ");
	for(int i=0;i<p;i++)
	{
		printf("%d ",allocated[i]+1);
		allocated[i]=-2;
	}


	printf("\n");

	//BEST FIT
	for(int i=0;i<p;i++)
	{
		int mini = -1;
		for(int j=0;j<m;j++)
		{
			if(original_hole_size[j] >= process_size[i])
			{
				if(original_hole_size[mini] > original_hole_size[j])
				{
					mini = j;
				}

			}

			if(mini != -1)
			{
				original_hole_size[mini] -= process_size[i];
				allocated[i] = mini; 
			}
		}
	}

	printf("Best Fit Allocations: ");
	for(int i=0;i<p;i++)
	{
		printf("%d ",allocated[i]+1);
	}



	return 0;


}
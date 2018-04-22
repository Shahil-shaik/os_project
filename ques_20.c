#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0

struct pdata
{
	int tq, tn;
	int *bt, *pid, *priority, *wt, *tat;
}pdata = {2, 0};

void getdata()
{
	int n,b;
	printf("\nEnter the Number of processes : ");
	scanf("%d",&n);
	pdata.bt = realloc(pdata.bt, sizeof(pdata.bt)+(sizeof(int))*n);
	pdata.pid = realloc(pdata.pid, sizeof(pdata.pid)+(sizeof(int))*n);
	pdata.priority = realloc(pdata.priority, sizeof(pdata.priority)+(sizeof(int))*n);
	for (int i = pdata.tn; i < pdata.tn+n ; i++)
	{
        printf("Enter the process ID ");
        scanf("%d",&pdata.pid[i]);
        printf("Enter the arrival time of process");
		scanf("%d",&b);
		printf("Enter the burst time of process");
		scanf("%d",&pdata.bt[i]);
		printf("Enter the priority of process");
        scanf("%d",&pdata.priority[i]);
	}
	pdata.tn = pdata.tn + n;
}

void algorithm()
{
	int twt, ttat;
	float avgwt=0,avgtnt=0;
	tq();
	sortdata();
	waittime();
	turnaroundtime();
	printf("\nProcess ID\tBurst Time\tPriority\tWaiting Time\tTurn Around Time\n");
	for (int i=0; i<pdata.tn; i++)
	{
		twt = twt + pdata.wt[i];
		ttat = ttat + pdata.tat[i];
		printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",pdata.pid[i],pdata.bt[i],pdata.priority[i],pdata.wt[i],pdata.tat[i]);
	}
	for(int i=0;i<pdata.tn;i++)
	{
	avgtnt=avgtnt+pdata.tat[i];
	avgwt=avgwt+pdata.wt[i];
	}
	printf("\n");
	printf("The average waiting time= %f\n",(avgwt/pdata.tn));
	printf("the average turn around time =%f",(avgtnt/pdata.tn));
}
void tq()
{
printf("enter the time quantam ");
	scanf("%d",&pdata.tq);
}

void waittime()
{
	pdata.wt = realloc(pdata.wt, sizeof(pdata.wt)+(sizeof(int))*pdata.tn);
	int bt_rem[pdata.tn];
	int time = 0;
    for (int i = 0; i < pdata.tn; i++)
	{
		bt_rem[i] = pdata.bt[i];
	}
	printf("\n\nReady Queue:\n");
    while (TRUE)
	{
		bool done = TRUE;
        for (int i = 0; i < pdata.tn; i++)
        {
        	if (bt_rem[i] > 0)
			{
				done = FALSE;
				if (bt_rem[i] > pdata.tq)
				{
					time += pdata.tq;
					bt_rem[i] -= pdata.tq;
				}
 				else
				{
					time = time + bt_rem[i];
 					pdata.wt[i] = time - pdata.bt[i];
 					bt_rem[i] = 0;
				}
				printf("P%d - ",i);
			}
		}
 		if (done == TRUE)
 		{
			printf("End\n");
			break;
 		}
	}
}

void turnaroundtime()
{
	pdata.tat = realloc(pdata.tat, sizeof(pdata.tat)+(sizeof(int))*pdata.tn);
	for (int i = 0; i < pdata.tn; i++)
	{
		pdata.tat[i] = pdata.bt[i] + pdata.wt[i];
	}
}

void sortdata()
{
	int temp;
	for (int i = 0; i < pdata.tn - 1; i++)
	{
		for(int j=i+1; j < pdata.tn; j++)
		{
			if(pdata.priority[i]<pdata.priority[j])
			{
				temp = pdata.priority[i];
				pdata.priority[i] = pdata.priority[j];
				pdata.priority[j] = temp;
				temp = pdata.bt[i];
				pdata.bt[i] = pdata.bt[j];
				pdata.bt[j] = temp;
				temp = pdata.pid[i];
				pdata.pid[i] = pdata.pid[j];
				pdata.pid[j] = temp;
			}
		}
	}
}
int main()
{
    printf("\t\t\tPREEMPTIE ROUND ROBIN SCHEULING");
    getdata();
    algorithm();

}


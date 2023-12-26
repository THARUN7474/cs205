#include <stdio.h>
#include <stdlib.h>
int main()
{
    int nop;
    printf("no of process:");
    scanf("%d", &nop);
    int art[nop], rt[nop], temp[nop];
    float waitt[nop], respt[nop];
    int cycle;
    printf("\nenter the time slot allocated to processes in cpu:");
    scanf("%d", &cycle); // time slice allocated
    // this loop for getting data............
    for (int i = 1; i <= nop; i++)
    {
        prinf("\nenter arrival time:");
        scanf("%d", &art[i - 1]); // arrivaial time of each process
        printf("\nenter cpu time required to complete process:");
        scanf("%d", &rt[i - 1]); // req time of each process
        temp[i - 1] = rt[i - 1]; // copy of reqtime of processes
    }
    int sum = 0;
    int count = nop;
    while (count != 0){
        for (int i = 0; i < nop; i++){
            if (temp[i] == 0){
                i++;
                continue;
            }
            if (temp[i] == rt[i]){
                respt[i] = sum;
            }
            if (art[i] <= sum){
                if (temp[i] <= cycle){
                    sum = sum + temp[i];
                    temp[i] = 0;
                    waitt[i] = sum - rt[i];
                    count--;
                    continue;
                }
                else{
                    temp[i] = temp[i] - cycle;
                    sum = sum + cycle;
                    continue;
                }
            }
            else{
                i++;
                continue;
            }
        }
    }
    printf("\nprocess\t\tresponse_time:\t\twaiting_time");

    float total_respt = 0, total_waitt = 0;

    for (int i = 0; i < nop; i++)
    {
        total_respt = total_respt + respt[i];
        total_waitt = total_waitt + waitt[i];
    }
    float avg_respt = total_respt / nop, avg_waitt = total_waitt / nop;
    for (int i = 1; i <= nop; i++)
    {
        printf("\nprocess[%d]\t\tresponse time:%f\t\twaiting time:%f\n", i, respt[i - 1], waitt[i - 1]);
    }
    printf("average response time:%f", avg_respt);
    printf("average waiting time:%f", avg_waitt);
    return 0;
}
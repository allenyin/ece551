#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
    int num_months;
    double incoming_dollars;
    double return_rate;
};
typedef struct _retire_info retire_info;

void retirement(int startAge, //in months
                double initial, //initial savings in dollars
                retire_info working, //info about working
                retire_info retired) {// info about being retired 
    /* $1000 existing, return rate=0.5%=0.005, incoming_dollars=100
     * interest = 1000*0.005+100+1000=1105.
     *
     * I will return the total amount of money at the end of processing
     */
    
    int cur_months = startAge;
    double funds = initial;
    // operate on working first
    while (working.num_months>0) {
        printf("Age %3d month %2d you have $%.2lf\n", cur_months/12, cur_months%12, funds);
        cur_months++;
        working.num_months--;
        funds += funds*working.return_rate + working.incoming_dollars;
    }
    // operate on retirement
    while (retired.num_months>0) {
        printf("Age %3d month %2d you have $%.2lf\n", cur_months/12, cur_months%12, funds);
        cur_months++;
        retired.num_months--;
        funds += funds*retired.return_rate + retired.incoming_dollars;
    }
}

int main(void) {
    retire_info working;
    working.num_months = 489;
    working.incoming_dollars = 1000;
    working.return_rate = 0.045/12;

    retire_info retired;
    retired.num_months = 384;
    retired.incoming_dollars = -4000;
    retired.return_rate = 0.01/12;

    int startAge = 327; // months
    int initial = 21345; // $21345 initial saving
    
    retirement(startAge, initial, working, retired);
    return EXIT_SUCCESS;
}
    
    

#include<stdio.h>
typedef struct date{
    int year;
    int month;
    int day;
}DATE;
typedef struct careercircumstances{
    char faculty[10];
    char title[10];
    char position[15];
}DELEARN;
typedef struct IdentityPersonnel
{
    char Name[15];
    char Gender[10];
    DATE birthday;
    DELEARN career;
}IDP;
int CompareAge(const IDP per[],int size);

int main(){
    IDP per[5]= {
                    {"m1","male",{2006,3,11},{"sc","genius","student"}},
                    {"m2","female",{2007,5,12},{"sc","genius2","pedestrian"}},
                    {"m3","male",{2008,6,23},{"sc","genius3","cleaner"}},
                    {"m4","female",{2009,2,13},{"sc","genius4","guardian"}},
                    {"m5","female",{2010,9,3},{"sc","genius5","teacher"}},
    };
    int k = CompareAge(per, sizeof(per)/sizeof(per[0]));
    printf("The name is:%s",per[k].Name);
}

int CompareAge(const IDP per[], int size){
    if (size <= 0) return -1; 
    
    int k = 0; 
    
    for (int i = 1; i < size; i++) {
        DATE currentDate = per[i].birthday;
        DATE maxDate = per[k].birthday;
        
        if (currentDate.year < maxDate.year) {
            k = i;
        } else if (currentDate.year == maxDate.year) {
            if (currentDate.month < maxDate.month) {
                k = i;
            } else if (currentDate.month == maxDate.month) {
                if (currentDate.day < maxDate.day) {
                    k = i;
                }
            }
        }
    }
    
    return k;
}
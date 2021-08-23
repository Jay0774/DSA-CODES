#include <stdio.h>
#include <stdlib.h>
struct student
{
    int id;
    char *name;
    int age;
};
struct student set()
{
    struct student t;
    printf("Enter Id of Student: \n");
    scanf("%d",&t.id);
    printf("Enter Name of Student: \n");
    scanf("%s",t.name);
    printf("Enter Age of Student: \n");
    scanf("%d",&t.age);
    return t;
}
void print(struct student s)
{
    printf("Id : %d \n",s.id);
    printf("Name : %s \n",s.name);
    printf("Age : %d \n\n",s.age);
}
int main() {
    int n,i;
    printf("Enter Number of Records : \n");
    scanf("%d",&n);
    struct student a[n];
    for(i=0;i<n;i++)
    {
        printf("\nFor Record Number %d Enter details : \n",i+1);
        a[i]=set();
    }
    for(i=0;i<n;i++)
    {
        printf("\nFor Record Number %d Entered details are : \n",i+1);
        print(a[i]);
    }
	return 0;
}

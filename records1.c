/*
A program that scans an entire file and uses flags to identify free spaces
*/

#include <stdio.h>
#include <stdlib.h>

struct st_student
{
    char name[20];
    int st_id;
    int age;
    char gender;
    int flag;
};

main()
{
    int size,num_files;
    int array[10];
    FILE *fp;
    
    struct st_student student;
        
    fp=fopen("students_flag.bin","r+b");
    
    if(fp==NULL)
    {
        printf("ERROR opening file");
        flushall();
        getchar();
        exit(0);
    }
    fseek(fp,0,SEEK_END);
    size=ftell(fp);
    num_files=size/sizeof(student);
    
    fseek(fp,0,SEEK_SET);
    for(int i=0; i<num_files;i++)
    {
        fread(&student,sizeof(student),1,fp);
        array[i]=student.flag;
    }
    for(int i=0;i<10;i++)
    {
        printf("\nhi4%d",array[i]);
    }
    
    
    flushall();
    getchar();
}
//Author Michelle Smith
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 20
const char *PLAYER_FILE="/Users/michellesmith/Downloads/players-1.txt";
const char *SLOTS_FILE="/Users/michellesmith/Downloads/slots-1.txt";
typedef struct

{
    char characterType[20];
    char playerName[20];
}


    playerInfo;

typedef struct

   {
    int slotNumber;
    char slotType[20];
    int followingSlot;
    slotInfo;
   }

playerInfo arr[SIZE];
slotInfo arrSlots[SIZE];
char originalArr[SIZE][200];//for the Player file
char originalArr2[SIZE][200];//for the Slot file
char sortedArr[SIZE][200];//for the sorted player file
int readPlayerFile();
int readSlotFile();
void sortPlayerFile(int lineNum);
void printPlayerFile(int lineNum);
void shufflePlayerFile(int lineNum);
void sortSlots(int lineNum);
int main()
{
    printf("Please enter your choice\nEnter 1 to sort and shuffle the list of Players\nEnter 2 to sort the list of slots\n");
    int choice;
    int lineNum=readPlayerFile();
    int lineNum2=readSlotFile();
    scanf("%d",&choice);
    switch(choice)
    {
        case 1: printf("\n______ORIGINAL ARRAY______");
            printPlayerFile(lineNum);
            sortPlayerFile(lineNum);
            printf("\n______SORTED ARRAY______");
            printPlayerFile(lineNum);
            printf("\n______SHUFFLED ARRAY______");
            shufflePlayerFile(lineNum);
            printPlayerFile(lineNum);
            break;
        case 2:printf("-------Sorted List of Slots-------\n");
            sortSlots(lineNum2);
            break;
        default:printf("Wrong choice entered");
            
    }
    
}
int readPlayerFile()
{
    int lineNum=0;
    FILE *playerInfoPtr;
    if((playerInfoPtr=fopen(PLAYER_FILE,"r+"))==NULL)
    {
        perror("PLAYER FILE NOT FOUND");
        exit(0);
    }
    else{
        while(fgets(originalArr[lineNum],sizeof(originalArr[lineNum]),playerInfoPtr)!=NULL)
        {
            sscanf(originalArr[lineNum],"%s%s",arr[lineNum].characterType,arr[lineNum].playerName);
            lineNum++;
        }
    }
    fclose(playerInfoPtr);
    return lineNum;
}
int readSlotFile()
{
    int lineNum=0;
    char temp[20];
    char tempSlotNumber[20];
    char tempFollowingSlot[20];
    FILE *slotPtr;
    if((slotPtr=fopen(SLOTS_FILE,"r+"))==NULL)
    {
        perror("SLOT FILE NOT FOUND");
        exit(0);
    }
    else{
        while(fgets(originalArr2[lineNum],sizeof(originalArr2[lineNum]),slotPtr)!=NULL)
        {
            sscanf(originalArr2[lineNum],"%s%s%s%s",tempSlotNumber,temp,arrSlots[lineNum].slotType,tempFollowingSlot);
            arrSlots[lineNum].slotNumber=atoi(tempSlotNumber);
            tempFollowingSlot[strlen(tempFollowingSlot)-2]='\0';
            arrSlots[lineNum].followingSlot=atoi(tempFollowingSlot);
            lineNum++;
        }
    }
    fclose(slotPtr);
    return lineNum;
}
void sortSlots(int lineNum)
{
    
    int k=0;//to store the current slotNumber
    int output[lineNum];//array to store the index of the slots
    for(int i=0;i<lineNum;i++)
    {
        int j=0;//
        while(arrSlots[j++].followingSlot!=k);
        j--;
        k=arrSlots[j].slotNumber;
        output[lineNum-i-1]=j;
        //printf("->(%d,%s)",arrSlots[j].slotNumber,arrSlots[j].slotType);
    }
    printf("\n");
    int l=0;
    for(l=0;l<lineNum-1;l++){
        printf("(%d,%s)->",arrSlots[output[l]].slotNumber,arrSlots[output[l]].slotType);
    }
    printf("(%d,%s)\n",arrSlots[output[l]].slotNumber,arrSlots[output[l]].slotType);
}
void sortPlayerFile(int lineNum)
{
    int i,j,k=0;
    for(i=0;i<lineNum;i++)
    {
        for(j=i;j<lineNum;j++)
        {
            if(strcmp(originalArr[i],originalArr[j])>0)
            {
                char temporary[200];
                strcpy(temporary,originalArr[i]);
                strcpy(originalArr[i],originalArr[j]);
                strcpy(originalArr[j],temporary);
            }
        }
        k++;
    }
    
}
void shufflePlayerFile(int lineNum)
{
    int n=lineNum-1;int i;
    //fisher yates
    for(int i=0;i<lineNum;i++)
    {
        int j=(rand()%(i+1)); //j is a random number such that j is between 0 and i (inclusive)
        if(j!=i )
        {
            //swap
            char temp[200];
            strcpy(temp,originalArr[j]);
            strcpy(originalArr[j],originalArr[i]);
            strcpy(originalArr[i],temp);
        }
        
    }
    //this helps to avoid consecutive repetition of characterTypes while shuffling
    for(i=1;i<lineNum;i++)
    {
        if(strncmp(originalArr[i-1],originalArr[i],5)==0)
        {
            //swap
            char temp[200];
            strcpy(temp,originalArr[i]);
            strcpy(originalArr[i],originalArr[n]);
            strcpy(originalArr[n],temp);
            n-=2;
        }
        
        if(strncmp(originalArr[i-1],originalArr[i],5)==0)
        {
            n=n+4;
            i--;
        }
    }
    
}
void printPlayerFile(int lineNum)
{
    int i=0;
    printf("\n\n");
    for(i=0;i<lineNum;i++)
    {
        printf("%s\n",originalArr[i]);
    }
    printf("\n\n");
}


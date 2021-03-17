/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: suresh
 *
 * Created on August 21, 2019, 4:42 PM
 */
#include<iostream>
#include <stdlib.h>
#include <cstring>
#include<string.h>
#include <cmath>
#include <bits/stdc++.h>


using namespace std;

static int DUPLICATE_PIVOT_COUNT=0;

//Function to swap two integer elements
void swap(int* a,int* b)
{
    int var;
    var=*a;
    *a=*b;
    *b=var;

}
//Testing for array of size two, if they were sorted
bool isSorted(int a, int b)
{

    return (a <=b)?1:0;
}


//Function gives the random integer between the range 0 to size-1
int getRandomNumber(int size)
{
    return rand()%size;
}
//Function will partition the the array with pivot element was randomly chosen
int partition(int* p_array,int p_beginIndex,int p_endIndex)
{
    //corner case when array contains only two elements

    int arraySize,randomIndex,pivot,beginIndex,endIndex;
    beginIndex=p_beginIndex;
    endIndex=p_endIndex;
    arraySize = (endIndex-beginIndex+1);
    if(arraySize==2 && isSorted(p_array[p_beginIndex],p_array[p_endIndex]))
            {
                return p_endIndex;
            }
    //Pivot element was randomly chosen
    randomIndex=getRandomNumber(arraySize);
    //Corner use case when array starting index is zero and random number is zero
    randomIndex=randomIndex >0 ?randomIndex:1;
    //Swapping the randomly chosen index with the last element
    swap(&p_array[beginIndex+randomIndex-1],&p_array[endIndex]);
    //Picking Last element as Pivot element
    pivot=p_array[endIndex];
    endIndex--;
    while(true)
    {
        //Looking for the element larger than pivot from left end of the array
        while(p_array[beginIndex]<=pivot && beginIndex < endIndex )
        {
            if(p_array[beginIndex]==pivot)
            DUPLICATE_PIVOT_COUNT++;
            beginIndex++;
        }
        //looking for the element smaller than pivot element from right end of the array
        while(p_array[endIndex]>pivot && endIndex > beginIndex )
        {
            endIndex--;
        }
        if(beginIndex<endIndex)
        {
            //swapping the larger element (larger than pivot from left end ) with the smaller element (smaller than pivot from right end
            swap(&p_array[beginIndex],&p_array[endIndex]);
        }else if((beginIndex==endIndex))
        {
            if(p_array[beginIndex]>=p_array[p_endIndex]){
            swap(&p_array[beginIndex],&p_array[p_endIndex]);
            return beginIndex;
            }
            else return p_endIndex;
        }
        else
        {


                //placing the pivot element at its correct position
                if((beginIndex!=(p_endIndex-1)) && (endIndex!=(p_endIndex-1)))
                swap(&p_array[endIndex],&p_array[p_endIndex]);
                cout<<"no of dupes"<<DUPLICATE_PIVOT_COUNT;
                //returning the pivot position
                return endIndex;

        }
    }


}

void convertchararraytoInt(int* p_array,char* p_chararray)
{
    char *element = strtok(p_chararray, " ");
    int elementcount=0;
     while (element != NULL)
    {
        int index=0,sign=1;
        if(element[0]=='-')
        {

            index++;
            sign=-1;
        }
        int temp=0;
        for(index;element[index]!='\0';index++)
        temp= temp*10+element[index]-'0';
        temp=temp*sign;
        p_array[elementcount]=temp;
        element = strtok(NULL, " ");
        elementcount++;
    }
}
//Function to parse the integers read from console
void applyQuickSort(int* p_array,int p_start,int p_end)
{
    int pivotIndex;
    if(p_start<p_end)
    {
        //Call to partition
        pivotIndex=partition(p_array,p_start,p_end);
        int pivot=p_array[pivotIndex];
        int duplicatescount=0;
        duplicatescount=DUPLICATE_PIVOT_COUNT;
       /* int i,j;
        i=pivotIndex;
        j=pivotIndex;
        while(p_array[j]==pivot && j >=p_start){
                j--;
                i--;
            }
        DUPLICATE_PIVOT_COUNT=DUPLICATE_PIVOT_COUNT-(pivotIndex-i-1);
        while(DUPLICATE_PIVOT_COUNT >0 && i>=p_start && j>=p_start)
        {
            while(p_array[j]!=pivot){
            j--;
            }
             swap(p_array[j],p_array[i]);
             i--;
             j--;
             DUPLICATE_PIVOT_COUNT--;

        }*/
        //call to Quicksort based on the pivot position
        applyQuickSort(p_array,p_start,pivotIndex-duplicatescount-1);
        applyQuickSort(p_array,pivotIndex+1,p_end);

    }

}


/*
 *
 */
int main(int argc, char** argv)
{

    int size,i;
    int* inputArrary;
    std::string input;
    //char* input[];
    getline(std::cin,input);
    size=std::stoi(input);
    inputArrary=new int[size];
    getline(std::cin,input);
    char chararray[input.length()+1];
    strcpy(chararray, input.c_str());
    //call to convert line of integers read from console to array of integers
    convertchararraytoInt(inputArrary,chararray);
    //call to qucksort
    applyQuickSort(inputArrary,0,size-1);

    for(i=0; i<size; i++)
        cout<<"\n"<<inputArrary[i];


    return 0;
}


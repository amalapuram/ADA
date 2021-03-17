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

//Function to swap two integer using pointer assignments
void swap(int* a,int* b)
{
    int var;
    var=*a;
    *a=*b;
    *b=var;

}
//Testing for base case i.e.,array of size two, if they were sorted
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
    //Variables to store array size,pivot
    int arraySize,randomIndex,pivot,beginIndex,endIndex;
    beginIndex=p_beginIndex-1;
    endIndex=p_endIndex;
    //calculating the size of the array
    arraySize = (p_endIndex-p_beginIndex+1);
    //checking base case for the size of array equals to two
    if(arraySize==2 && isSorted(p_array[p_beginIndex],p_array[p_endIndex]))
            {
                //if size two array is sorted, returning the position2 as pivot index
                return p_endIndex;
            }
    //Pivot element was randomly chosen
    randomIndex=getRandomNumber(arraySize);
    //Corner use case when array starting index is zero and random number is zero
    randomIndex=randomIndex >0 ?randomIndex:1;
    //Swapping the randomly chosen index with the last element
    swap(&p_array[p_beginIndex+randomIndex-1],&p_array[endIndex]);
    //Picking Last element as Pivot element
    pivot=p_array[endIndex];


for (int i=p_beginIndex; i<endIndex; i++)
    {
        // comparing current element with the pivot
        if (p_array[i] < pivot)
        {
            beginIndex++;
            swap(&p_array[beginIndex], &p_array[i]);
        }
    }
    beginIndex++;
    //Swapping pivot(element stored at the last index) with the element with the desired pivot index
    swap(&p_array[beginIndex], &p_array[p_endIndex]);
    //returning the pivot index
    return (beginIndex);

}

//Function to convert character array of input elements into integer elements
void convertchararraytoInt(int* p_array,char* p_chararray)
{
    //splitting the character array of elements into tokens using space delimiter
    char *element = strtok(p_chararray, " ");
    //Variable to read input elements
    int elementcount=0;
    //checking till the last element
     while (element != NULL)
    {
        //Variables to store sign of the element
        int index=0,sign=1;
        //Checking if the current element is negative
        if(element[0]=='-')
        {

            index++;
            //setting sign to negative
            sign=-1;
        }
        int temp=0;
        //for each element after split , handling it for multi digit number
        for(index;element[index]!='\0';index++){
        //Handling multi digit number
        temp= temp*10+element[index]-'0';
        }
        //To reflect its sign
        temp=temp*sign;
        //Assigning to integer array
        p_array[elementcount]=temp;
        //Reading the next token
        element = strtok(NULL, " ");
        elementcount++;
    }
}
//Function to parse the integers read from console
void applyRandomizedQuickSort(int* p_array,int p_start,int p_end)
{
    int pivotIndex,duplicatescount=0;
    if(p_start<p_end)
    {
        //Call to partition
        pivotIndex=partition(p_array,p_start,p_end);
        //call to Quick sort elements to the left of the pivot position
        applyRandomizedQuickSort(p_array,p_start,pivotIndex-1);
        //call to Quick sort elements to the right of the pivot position
        applyRandomizedQuickSort(p_array,pivotIndex+1,p_end);

    }

}



//Boolean function checks for the presence of the majority element after sorting
bool findMajority(int* p_arrray,int p_size)
{
    int index,mid;
    //Finding size of n/2, n= number of elements
    if(p_size%2 ==1)
    mid=floor(p_size/2)+1;
    else mid=p_size/2;

    for(index=0; index<mid; index++)
    {
        //check for majority element
        if(p_arrray[index] == p_arrray[index+mid-(p_size%2)])
            return 1;
    }
    //Returning false by default
    return 0;
}
/*
 *
 */
int main(int argc, char** argv)
{

    //Variables to read size of the array, looping variable
    int size,i;
    //Creating a integer pointer to the input elements
    int* inputArrary;
    std::string input;
    //Reading the size of the array as string
    getline(std::cin,input);
    //Converting size in string to int
    size=std::stoi(input);
    //Creating the input array
    inputArrary=new int[size];
    //Reading the input array to string
    getline(std::cin,input);
    //creating character array
    char chararray[input.length()+1];
    //copying the input of integers into the character array
    strcpy(chararray, input.c_str());
    //call to convert line of integers read from console to array of integers
    convertchararraytoInt(inputArrary,chararray);
    //call to Quick sort
    applyRandomizedQuickSort(inputArrary,0,size-1);
    //printing the majority element status
    cout<<endl<<findMajority(inputArrary,size)<<endl;

        return 0;
}


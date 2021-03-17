#include <iostream>
#include <bits/stdc++.h>
/*
*****************************************************************************************************************
* Steps to run the code
*1.compile the code and run executable file(in case of windows)/a.out file(in case of unix)
*2.Enter target string(source string/first string) in terminal window and hit ENTER
*3.Now you are in new line, enter query string (second string) hit enter
*4.You will see output in the following format
*optimal cost value
*new target string
*new query string
*****************************************************************************************************************
*/
using namespace std;
//initializing the gap penalty
static int gap_penalty=30;
//creating computational optimal cost matrix
static int const max_array_size=3000;
static int optimalCost[max_array_size][max_array_size];
//map for storing mismatch penalties
map<string,int> mismatchPenalty_map= {{"AA",-91},{"AC",114},{"AG",31},{"AT",123},
                                      {"CA",114},{"CC",-100},{"CG",125},{"CT",31},
                                      {"GA",31},{"GC",125},{"GG",-100},{"GT",114},
                                      {"TA",123},{"TC",31},{"TG",114},{"TT",-91}};


//function to identify the backtrack path in optimal cost recurrence relation
int _getbacktrackPath(int top,int left,int diagnol,int currentvalue,string t,string g,int i,int j)
{
    //creating the string key to look into mismatch penalty map
    string map_key=string(1,t[i])+string(1,g[j]);
    //current cell(i,j) value of optimal cost matrix comes from top cell (i-1,j)
    if (top+gap_penalty == currentvalue)
    {
        return 0;
    }//current cell(i,j) value of optimal cost matrix comes from left cell (i,j-1)
    else if (left +gap_penalty == currentvalue)
    {
        return 1;
    }//if both characters are equal
    else if (t[i]==g[j])
    {
        return 2;
    }//current cell(i,j) value of optimal cost matrix comes from diagonal cell (i-1,j-1) with a mismatch penalty
    else if (diagnol + mismatchPenalty_map[map_key] == currentvalue)
    {
        return 3;
    }

    return 0;

}

void _printMatrix(string matrixname,int matrix[max_array_size][max_array_size],int rows,int columns)
{
    //prints name of the matrix
    cout<<"Matrix :"<<matrixname<<endl;
    //prints matrix row wise
    for (int i = 0; i <=rows; i++)
    {
        for (int j = 0; j <=columns; j++)
        {
            cout<<"\t"<<matrix[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}






// function computes the optimal cost matrix
void _getOptimalCost(string str_target, string str_query)
{
    //Stores respective strings length
    int target_len = str_target.length();
    int query_len = str_query.length();
    //prints strings
    //cout<<"target length"<<target_len;
    //cout<<"query length"<<query_len;

    int i, j;
    //initializing the optimal cost matrix
    for (i = 0; i <= (target_len); i++)
    {
        //initializing first column
        optimalCost[i][0] = i * gap_penalty;
    }

    for (i = 0; i <= (query_len); i++)
    {
        //initializing the first row
        optimalCost[0][i] = i * gap_penalty;

    }

    string map_key;

     // computing the optimal cost for the given strings
    for (i = 1; i <= target_len; i++)
    {
        for (j = 1; j <= query_len; j++)
        {  //creating the string key to look into mismatch penalty map
            map_key=string(1,str_target[i-1])+string(1,str_query[j-1]);

            //when both characters are equal
            if (str_target[i - 1] == str_query[j - 1])
            {
                optimalCost[i][j] = optimalCost[i - 1][j - 1]+ mismatchPenalty_map[map_key];
            }
            else
            {

                //Recurrence for optimal cost matrix
                optimalCost[i][j] = min({optimalCost[i - 1][j - 1] + mismatchPenalty_map[map_key],
                                        optimalCost[i - 1][j] + gap_penalty,
                                        optimalCost[i][j - 1] + gap_penalty});
            }
        }
    }

    // _printMatrix("Optimal Cost",optimalCost,target_len,query_len);

    //maximum possible length of the solution string
    int max_length = query_len + target_len; //maximum length
    //sets target and query string lengths
    i = target_len;
    j = query_len;
    //maximum possible length for output strings
    int target_position = max_length;
    int query_position = max_length;

    //Declaring solution strings
    int target_final_str[max_length+1], query_final_str[max_length+1];
    //Back tracking for optimal cost value
    while ( !(i == 0 || j == 0))
    {
        //value represents which path should be considered for for current cell in the optimal cost recurrence
        int value=_getbacktrackPath(optimalCost[i - 1][j],optimalCost[i][j - 1],optimalCost[i - 1][j - 1],optimalCost[i][j],str_target,str_query,i-1,j-1);
        switch(value)
        {

        case 0://current cell(i,j) value of optimal cost matrix comes from top cell (i-1,j)
            target_final_str[target_position--] = (int)str_target[i - 1];
            query_final_str[query_position--] = (int)'_';
            i--;
            break;

        case 1://current cell(i,j) value of optimal cost matrix comes from left cell (i,j-1)
            target_final_str[target_position--] = (int)'_';
            query_final_str[query_position--] = (int)str_query[j - 1];
            j--;
            break;

        case 2://if both characters are equal
            target_final_str[target_position--] = (int)str_target[i - 1];
            query_final_str[query_position--] = (int)str_query[j - 1];
            i--;
            j--;
            break;

        case 3://current cell(i,j) value of optimal cost matrix comes from diagonal cell (i-1,j-1) with a mismatch penalty
            target_final_str[target_position--] = (int)str_target[i - 1];
            query_final_str[query_position--] = (int)str_query[j - 1];
            i--;
            j--;
            break;


        }
    }

    //Appends remaining characters of target string to output target string
    while (target_position > 0)
    {
        if (i > 0)
            target_final_str[target_position--] = (int)str_target[--i];
        else
            target_final_str[target_position--] = (int)'_';
    }
    //Appends remaining characters of query string to output query string
    while (query_position > 0)
    {
        if (j > 0)
            query_final_str[query_position--] = (int)str_query[--j];
        else
            query_final_str[query_position--] = (int)'_';
    }

    //holds the lower index of the output strings
    int string_lower_index = 1;
    for (i = max_length; i >= 1; i--)
    {   //both strings containing - indicates lower index
        if ((char)query_final_str[i] == '_' && (char)target_final_str[i] == '_')
        {   //holding the lower index
            string_lower_index = i + 1;
            break;
        }
    }

    // Printing the optimal cost
    cout <<optimalCost[target_len][query_len] <<endl;
    //prints final target string
    for (i = string_lower_index; i <= max_length; i++)
    {
        cout<<(char)target_final_str[i];
    }
    cout <<endl;
    //prints final query string
    for (i = string_lower_index; i <= max_length; i++)
    {
        cout << (char)query_final_str[i];
    }
    cout <<endl;

}


int main()
{

    // input strings

    string s1;
    string s2;
    cin>>s1>>s2;

    //s1="TGGCGGAACT";
    //s2="TGGTGGTACT";
    //cout<<s1<<endl<<s2<<endl;


    /*s1="GGGAATCACGAGAGCAGACAGATCACACAGGTTTATGGGTTCTACGACGAGTGTTTA";
    s2="GGGAATCATGAGAGCAGACGATCACACAAGTTTATGGTTTCTATGATGAATGTTTA";


    s1="AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGCTTCTGAACTGGTTACCTGCCGTGAGTAAATTAAAATTTTATTGACTTAGGTCACTAAATACTTTAACCAATATAGGCATAGCGCACAGACAGATAAAAATTACAGAGTACACAACATCCATGAAACGCATTAGCACCACCATTACCACCACCATCACCATTACCACAGGTAACGGTGCGGGCTGACGCGTACAGGAAACACAGAAAAAAGCCCGCACCTGACAGTGCGGGCTTTTTTTTTCGACCAAAGGTAACGAGGTAACAACCATGCGAGTGTTGAAGTTCGGCGGTACATCAGTGGCAAATGCAGAACGTTTTCTGCGTGTTGCCGATATTCTGGAAAGCAATGCCAGGCAGGGGCAGGTGGCCACCGTCCTCTCTGCCCCCGCCAAAATCACCAACCACCTGGTGGCGATGATTGAAAAAACCATTAGCGGCCAGGATGCTTTACCCAATATCAGCGATGCCGAACGTATTTTTGCCGAACTTTTGACGGGACTCGCCGCCGCCCAGCCGGGGTTCCCGCTGGCGCAATTGAAAACTTTCGTCGATCAGGAATTTGCCCAAATAAAACATGTCCTGCATGGCATTAGTTTGTTGGGGCAGTGCCCGGATAGCATCAACGCTGCGCTGATTTGCCGTGGCGAGAAAATGTCGATCGCCATTATGGCCGGCGTATTAGAAGCGCGCGGTCACAACGTTACTGTTATCGATCCGGTCGAAAAACTGCTGGCAGTGGGGCATTACCTCGAATCTACCGTCGATATTGCTGAGTCCACCCGCCGTATTGCGGCAAGCCGCATTCCGGCTGATCACATGGTGCTGATGGCAGGTTTCACCGCCGGTAATGAAAAAGGCGAACTGGTGGTGCTTGGACGCAACGGTTCCGACTACTCTGCTGCGGTGCTGGCTGCCTGTTTACGCGCCGATTGTTGCGAGATTTGGACGGACGTTGACGGGGTCTATACCTGCGACCCGCGTCAGGTGCCCGATGCGAGGTTGTTGAAGTCGATGTCCTACCAGGAAGCGATGGAGCTTTCCTACTTCGGCGCTAAAGTTCTTCACCCCCGCACCATTACCCCCATCGCCCAGTTCCAGATCCCTTGCCTGATTAAAAATACCGGAAATCCTCAAGCACCAGGTACGCTCATTGGTGCCAGCCGTGATGAAGACGAATTACCGGTCAAGGGCATTTCCAATCTGAATAACATGGCAATGTTCAGCGTTTCTGGTCCGGGGATGAAAGGGATGGTCGGCATGGCGGCGCGCGTCTTTGCAGCGATGTCACGCGCCCGTATTTCCGTGGTGCTGATTACGCAATCATCTTCCGAATACAGCATCAGTTTCTGCGTTCCACAAAGCGACTGTGTGCGAGCTGAACGGGCAATGCAGGAAGAGTTCTACCTGGAACTGAAAGAAGGCTTACTGGAGCCGCTGGCAGTGACGGAACGGCTGGCCATTATCTCGGTGGTAGGTGATGGTATGCGCACCTTGCGTGGGATCTCGGCGAAATTCTTTGCCGCACTGGCCCGCGCCAATATCAACATTGTCGCCATTGCTCAGGGATCTTCTGAACGCTCAATCTCTGTCGTGGTAAATAACGATGATGCGACCACTGGCGTGCGCGTTACTCATCAGATGCTGTTCAATACCGATCAGGTTATCGAAGTGTTTGTGATTGGCGTCGGTGGCGTTGGCGGTGCGCTGCTGGAGCAACTGAAGCGTCAGCAAAGCTGGCTGAAGAATAAACATATCGACTTACGTGTCTGCGGTGTTGCCAACTCGAAGGCTCTGCTCACCAATGTACATGGCCTTAATCTGGAAAACTGGCAGGAAGAACTGGCGCAAGCCAAAGAGCCGTTTAATCTCGGGCGCTTAATTCGCCTCGTGAAAGAATATCATCTGCTGAACCCGGTCATTGTTGACTGCACTTCCAGCCAGGCAGTGGCGGATCAATATGCCGACTTCCTGCGCGAAGGTTTCCACGTTGTCACGCCGAACAAAAAGGCCAACACCTCGTCGATGGATTACTACCATCAGTTGCGTTATGCGGCGGAAAAATCGCGGCGTAAATTCCTCTATGACACCAACGTTGGGGCTGGATTACCGGTTATTGAGAACCTGCAAAATCTGCTCAATGCAGGTGATGAATTGATGAAGTTCTCCGGCATTCTTTCTGGTTCGCTTTCTTATATCTTCGGCAAGTTAGACGAAGGCATGAGTTTCTCCGAGGCGACCACGCTGGCGCGGGAAATGGGTTATACCGAACCGGACCCGCGAGATGATCTTTCTGGTATGGATGTGGCGCGTAAACTATTGATTCTCGCTCGTGAAACGGGACGTGAACTGGAGCTGGCGGATATTGAAATTGAACCTGTGCTGCCCGCAGAGTTTAACGCCGAGGGTGATGTTGCCGCTTTTATGGCGAATC";
    s2="AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTCTCTGACAGCAGCTTCTGAACTGGTTACCTGCCGTGAGTAAATTAAAATTTTATTGACTTAGGTCACTAAATACTTTAACCAATATAGGCATAGCGCACAGACAGATAAAAATTACAGAGTACACAACATCCATGAAACGCATTAGCACCACCATTACCACCACCATCACCACCACCATCACCATTACCATTACCACAGGTAACGGTGCGGGCTGACGCGTACAGGAAACACAGAAAAAAGCCCGCACCTGACAGTGCGGGCTTTTTTTTCGACCAAAGGTAACGAGGTAACAACCATGCGAGTGTTGAAGTTCGGCGGTACATCAGTGGCAAATGCAGAACGTTTTCTGCGGGTTGCCGATATTCTGGAAAGCAATGCCAGGCAGGGGCAGGTGGCCACCGTCCTCTCTGCCCCCGCCAAAATCACCAACCACCTGGTGGCGATGATTGAAAAAACCATTAGCGGCCAGGATGCTTTACCCAATATCAGCGATGCCGAACGTATTTTTGCCGAACTTCTGACGGGACTCGCCGCCGCCCAGCCGGGATTCCCGCTGGCGCAATTGAAAACTTTCGTCGACCAGGAATTTGCCCAAATAAAACATGTCCTGCATGGCATTAGTTTGTTAGGGCAGTGCCCGGATAGCATTAACGCTGCGCTGATTTGCCGTGGCGAGAAAATGTCGATCGCCATTATGGCCGGCGTATTAGAAGCGCGCGGTCACAACGTTACCGTTATCGATCCGGTCGAAAAACTGCTGGCAGTGGGGCATTACCTCGAATCTACTGTCGATATTGCAGAGTCCACCCGCCGTATTGCGGCAAGTCGTATTCCGGCTGATCACATGGTGCTGATGGCAGGTTTCACCGCCGGTAATGAAAAAGGCGAACTGGTGGTACTTGGACGCAACGGTTCCGACTACTCCGCGGCGGTGCTGGCTGCCTGTTTACGCGCCGATTGTTGCGAGATTTGGACGGACGTTGACGGGGTATATACCTGCGACCCGCGTCAGGTGCCCGATGCGAGGTTGTTGAAATCGATGTCCTACCAGGAAGCGATGGAGCTTTCCTACTTCGGCGCTAAAGTTCTTCACCCCCGCACCATTACCCCCATCGCCCAGTTCCAGATCCCTTGCCTGATTAAAAATACCGGAAATCCTCAAGCTCCAGGTACGCTCATTGGTGCCAGTCGTGATGAAGACGAATTACCGGTCAAGGGCATTTCCAATCTGAATAATATGGCAATGTTCAGCGTTTCCGGCCCGGGGATGAAAGGAATGGTCGGCATGGCGGCGCGCGTCTTTGCTGCAATGTCACGCGCCCGTATTTCCGTGGTGCTGATTACGCAATCATCTTCCGAATACAGTATCAGTTTCTGCGTTCCGCAAAGCGACTGTGTGCGAGCTGAACGGGCAATGCAGGAAGAGTTCTACCTGGAACTGAAAGAAGGCTTACTGGAGCCGCTGGCGGTGACGGAACGGCTGGCCATTATCTCGGTGGTAGGTGATGGTATGCGCACCTTGCGTGGGATCTCGGCGAAATTCTTTGCCGCGCTGGCCCGCGCCAATATCAACATTGTCGCTATTGCTCAGGGATCTTCTGAACGCTCAATCTCTGTCGTGGTAAATAACGATGATGCGACCACTGGCGTGCGCGTTACTCATCAGATGCTGTTCAATACCGATCAGGTTATCGAAGTGTTTGTGATTGGCGTCGGTGGCGTTGGCGGTGCGCTGCTGGAGCAACTGAAGCGTCAGCAAAGCTGGTTGAAGAATAAACATATCGACTTACGTGTCTGCGGTGTTGCTAACTCGAAGGCTCTGCTCACCAATGTGCATGGCCTAAATCTGGAAAACTGGCAGGAAGAACTGGCGCAAGCCAAAGAGCCGTTTAATCTCGGGCGCTTAATTCGCCTCGTGAAAGAATATCATCTGCTGAACCCGGTCATTGTTGACTGCACCTCCAGCCAGGCAGTGGCGGATCAATATGCCGACTTCCTGCGCGAAGGTTTCCACGTTGTCACGCCGAACAAAAAGGCCAACACCTCGTCGATGGATTACTACCATCTGTTGCGTCATGCGGCTGAAAAATCGCGGCGTAAATTCCTCTATGACACCAACGTTGGGGCTGGATTACCGGTTATTGAGAACCTGCAAAATCTGCTCAATGCTGGTGATGAATTGATGAAGTTCTCCGGCATTCTTTCAGGTTCGCTTTCTTATATCTTCGGCAAGTTAGACGAAGGCATGAGTTTCTCCGAGGCGACTACGCTGGCGCGGGAAATGGGTTATACCGAACCGGATCCGCGAGATGATCTTTCTGGTATGGATGTAGCGCGTAAACTATTAATTCTCGCTCGTGAAACGGGACGTGAACTGGAGCTGGCGGATATTGAAATTGAACCTGTGCTGCCCGCAGAGTTTAACGCTGAGGGTGATGTTGC";
*/

    // calling the function to calculate the result
    _getOptimalCost(s1, s2);
    return 0;
}

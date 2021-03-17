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
//initializing infinity
static int infinity=25000;
//initializing gap opening and extension penalties
static int gap_opening_penalty=400;
static int gap_extension_penalty=20;
//initializing maximum array size
static int const max_array_size=3000;
//creating computational matrices
static int optimalCost[max_array_size][max_array_size];
static int matrixA[max_array_size][max_array_size];
static int matrixB[max_array_size][max_array_size];

//map for storing mismatch penalties
map<string,int> mismatchPenalty_map= {{"AA",-91},{"AC",114},{"AG",31},{"AT",123},
                                      {"CA",114},{"CC",-100},{"CG",125},{"CT",31},
                                      {"GA",31},{"GC",125},{"GG",-100},{"GT",114},
                                      {"TA",123},{"TC",31},{"TG",114},{"TT",-91}};


//Function to calculate gap penalty
int _getGapPenalty(int gapspread)
{

    int gap_penalty;
    //gamma = delta + (gap spread-1)* beta
    gap_penalty=gap_opening_penalty+(gapspread-1)*gap_extension_penalty;


    return gap_penalty;

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





// returns the optimal cost
void _getOptimalCost(string str_target, string str_query)
{
    //Stores respective strings length
    int target_len = str_target.length();
    int query_len = str_query.length();
    //prints the input strings
    //cout<<"target length"<<target_len;
    //cout<<"query length"<<query_len;


    int i, j;
    //initializing the matrices
    for (i = 1; i <= (target_len); i++)
    {
        //initializing first column of optimal cost matrix
        optimalCost[i][0] = _getGapPenalty(i);
        //initializing first column of matrixA with infinity
        matrixB[i][0]=infinity;
    }

    for (i = 1; i <= (query_len); i++)
    {
        //initializing the first row optimal cost matrix
        optimalCost[0][i] = _getGapPenalty(i);
        //initializing first row of matrixB with infinity
        matrixA[0][i]=infinity;

    }

    string map_key;


    // computing the optimal cost for the given strings
    for (i = 1; i <= target_len; i++)
    {
        for (j = 1; j <= query_len; j++)
        {
            //creating the string key to look into mismatch penalty map
            map_key=string(1,str_target[i-1])+string(1,str_query[j-1]);
            //Recurrence for  matrix A
            matrixA[i][j]=min({
                                optimalCost[i-1][j]+_getGapPenalty(1),
                                matrixA[i-1][j]+gap_extension_penalty});
            //Recurrence for Matrix B
            matrixB[i][j]=min({
                                optimalCost[i][j-1]+_getGapPenalty(1),
                                matrixB[i][j-1]+gap_extension_penalty
            });
            //when both characters in strings are equal
            if (str_target[i - 1] == str_query[j - 1])
            {
                optimalCost[i][j] = optimalCost[i - 1][j - 1]+mismatchPenalty_map[map_key];
            }
            else
            {


                //Recurrence for optimal cost matrix
                optimalCost[i][j] = min({optimalCost[i - 1][j - 1] + mismatchPenalty_map[map_key],
                                         matrixA[i][j],
                                         matrixB[i][j]
                                        });
            }
        }
    }

   // _printMatrix("Optimal Cost",optimalCost,target_len,query_len);
   // _printMatrix("Matrix A",matrixA,target_len,query_len);
   // _printMatrix("Matrix B",matrixB,target_len,query_len);

    //maximum possible length of the solution string
    int max_length = query_len + target_len;
    //sets target and query string lengths
    i = target_len;
    j = query_len;
    //maximum possible length for output strings
    int target_position = max_length;
    int query_position = max_length;

    //Declaring solution strings
    int target_final_str[max_length+1], query_final_str[max_length+1];
    //indicator variable helps in jumping between the matrices (OptimalCost,MatrixA,MatrixB)
    int matrix_num=0;
    //OptimalCost -0
    //MatrixA-1
    //MatrixB-2

    //Back tracking the optimal cost matrix
    while ( !(i == 0 || j == 0))
    {
        //creating the string key to look into mismatch penalty map
        map_key=string(1,str_target[i-1])+string(1,str_query[j-1]);
        //Optimal cost cell value comes from MatrixA
        if(matrix_num==0 && optimalCost[i][j]==matrixA[i][j])
        {
            //prints target string current character in output
            target_final_str[target_position--] = (int)str_target[i - 1];
            //prints query string current character as '-'
            query_final_str[query_position--] = (int)'_';
            i--;
            //checks matrixA recurrence to jump onto next matrix
            matrix_num=(matrixA[i][j]==(matrixA[i-1][j]+gap_extension_penalty))?1:0;
        }//Optimal cost cell value comes from MatrixB
        else if(matrix_num==0 && optimalCost[i][j]==matrixB[i][j])
        {
            //prints target string current character as -
            target_final_str[target_position--] = (int)'_';
            //prints query string current character in output
            query_final_str[query_position--] = (int)str_query[j - 1];
            j--;
            //checks matrixB recurrence to jump onto next matrix
            matrix_num=(matrixB[i][j]==(matrixB[i][j-1]+gap_extension_penalty))?2:0;

        }//Optimal cost cell value comes from Optimal cost matrix itself
        else if(matrix_num==0 && (str_target[i-1]==str_query[j-1] || optimalCost[i-1][j-1]+mismatchPenalty_map[map_key]==optimalCost[i][j]))
        {
            //prints target string current character in output
            target_final_str[target_position--] = (int)str_target[i - 1];
            //prints query string current character in output
            query_final_str[query_position--] = (int)str_query[j - 1];
            i--;
            j--;
        }//checking the MatrixA cell value
        else if(matrix_num==1)
        {
            //prints target string current character in output
            target_final_str[target_position--] = (int)str_target[i - 1];
            //prints query string current character as '-'
            query_final_str[query_position--] = (int)'_';
            i--;
            //checks matrixA recurrence to jump onto next matrix
            matrix_num=(matrixA[i][j]==(matrixA[i-1][j]+gap_extension_penalty))?1:0;
        }//checking the MatrixB cell value
        else if(matrix_num==2)
        {
            //prints target string current character as -
            target_final_str[target_position--] = (int)'_';
            //prints query string current character in output
            query_final_str[query_position--] = (int)str_query[j - 1];
            j--;
            //checks matrixB recurrence to jump onto next matrix
            matrix_num=(matrixB[i][j]==(matrixB[i][j-1]+gap_extension_penalty))?2:0;
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
    {
        //both strings containing - indicates lower index
        if ((char)query_final_str[i] == '_' && (char)target_final_str[i] == '_')
        {   //holding the lower index
            string_lower_index = i + 1;
            break;
        }
    }

    // Printing the optimal cost
    cout <<optimalCost[target_len][query_len]<<endl;


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

    //s1="GGGAATCACGAGAGCAGACAGATCACACAGGTTTATGGGTTCTACGACGAGTGTTTA";
    //s2="GGGAATCATGAGAGCAGACGATCACACAAGTTTATGGTTTCTATGATGAATGTTTA";


    //s1="AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGCTTCTGAACTGGTTACCTGCCGTGAGTAAATTAAAATTTTATTGACTTAGGTCACTAAATACTTTAACCAATATAGGCATAGCGCACAGACAGATAAAAATTACAGAGTACACAACATCCATGAAACGCATTAGCACCACCATTACCACCACCATCACCATTACCACAGGTAACGGTGCGGGCTGACGCGTACAGGAAACACAGAAAAAAGCCCGCACCTGACAGTGCGGGCTTTTTTTTTCGACCAAAGGTAACGAGGTAACAACCATGCGAGTGTTGAAGTTCGGCGGTACATCAGTGGCAAATGCAGAACGTTTTCTGCGTGTTGCCGATATTCTGGAAAGCAATGCCAGGCAGGGGCAGGTGGCCACCGTCCTCTCTGCCCCCGCCAAAATCACCAACCACCTGGTGGCGATGATTGAAAAAACCATTAGCGGCCAGGATGCTTTACCCAATATCAGCGATGCCGAACGTATTTTTGCCGAACTTTTGACGGGACTCGCCGCCGCCCAGCCGGGGTTCCCGCTGGCGCAATTGAAAACTTTCGTCGATCAGGAATTTGCCCAAATAAAACATGTCCTGCATGGCATTAGTTTGTTGGGGCAGTGCCCGGATAGCATCAACGCTGCGCTGATTTGCCGTGGCGAGAAAATGTCGATCGCCATTATGGCCGGCGTATTAGAAGCGCGCGGTCACAACGTTACTGTTATCGATCCGGTCGAAAAACTGCTGGCAGTGGGGCATTACCTCGAATCTACCGTCGATATTGCTGAGTCCACCCGCCGTATTGCGGCAAGCCGCATTCCGGCTGATCACATGGTGCTGATGGCAGGTTTCACCGCCGGTAATGAAAAAGGCGAACTGGTGGTGCTTGGACGCAACGGTTCCGACTACTCTGCTGCGGTGCTGGCTGCCTGTTTACGCGCCGATTGTTGCGAGATTTGGACGGACGTTGACGGGGTCTATACCTGCGACCCGCGTCAGGTGCCCGATGCGAGGTTGTTGAAGTCGATGTCCTACCAGGAAGCGATGGAGCTTTCCTACTTCGGCGCTAAAGTTCTTCACCCCCGCACCATTACCCCCATCGCCCAGTTCCAGATCCCTTGCCTGATTAAAAATACCGGAAATCCTCAAGCACCAGGTACGCTCATTGGTGCCAGCCGTGATGAAGACGAATTACCGGTCAAGGGCATTTCCAATCTGAATAACATGGCAATGTTCAGCGTTTCTGGTCCGGGGATGAAAGGGATGGTCGGCATGGCGGCGCGCGTCTTTGCAGCGATGTCACGCGCCCGTATTTCCGTGGTGCTGATTACGCAATCATCTTCCGAATACAGCATCAGTTTCTGCGTTCCACAAAGCGACTGTGTGCGAGCTGAACGGGCAATGCAGGAAGAGTTCTACCTGGAACTGAAAGAAGGCTTACTGGAGCCGCTGGCAGTGACGGAACGGCTGGCCATTATCTCGGTGGTAGGTGATGGTATGCGCACCTTGCGTGGGATCTCGGCGAAATTCTTTGCCGCACTGGCCCGCGCCAATATCAACATTGTCGCCATTGCTCAGGGATCTTCTGAACGCTCAATCTCTGTCGTGGTAAATAACGATGATGCGACCACTGGCGTGCGCGTTACTCATCAGATGCTGTTCAATACCGATCAGGTTATCGAAGTGTTTGTGATTGGCGTCGGTGGCGTTGGCGGTGCGCTGCTGGAGCAACTGAAGCGTCAGCAAAGCTGGCTGAAGAATAAACATATCGACTTACGTGTCTGCGGTGTTGCCAACTCGAAGGCTCTGCTCACCAATGTACATGGCCTTAATCTGGAAAACTGGCAGGAAGAACTGGCGCAAGCCAAAGAGCCGTTTAATCTCGGGCGCTTAATTCGCCTCGTGAAAGAATATCATCTGCTGAACCCGGTCATTGTTGACTGCACTTCCAGCCAGGCAGTGGCGGATCAATATGCCGACTTCCTGCGCGAAGGTTTCCACGTTGTCACGCCGAACAAAAAGGCCAACACCTCGTCGATGGATTACTACCATCAGTTGCGTTATGCGGCGGAAAAATCGCGGCGTAAATTCCTCTATGACACCAACGTTGGGGCTGGATTACCGGTTATTGAGAACCTGCAAAATCTGCTCAATGCAGGTGATGAATTGATGAAGTTCTCCGGCATTCTTTCTGGTTCGCTTTCTTATATCTTCGGCAAGTTAGACGAAGGCATGAGTTTCTCCGAGGCGACCACGCTGGCGCGGGAAATGGGTTATACCGAACCGGACCCGCGAGATGATCTTTCTGGTATGGATGTGGCGCGTAAACTATTGATTCTCGCTCGTGAAACGGGACGTGAACTGGAGCTGGCGGATATTGAAATTGAACCTGTGCTGCCCGCAGAGTTTAACGCCGAGGGTGATGTTGCCGCTTTTATGGCGAATC";
    //s2="AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTCTCTGACAGCAGCTTCTGAACTGGTTACCTGCCGTGAGTAAATTAAAATTTTATTGACTTAGGTCACTAAATACTTTAACCAATATAGGCATAGCGCACAGACAGATAAAAATTACAGAGTACACAACATCCATGAAACGCATTAGCACCACCATTACCACCACCATCACCACCACCATCACCATTACCATTACCACAGGTAACGGTGCGGGCTGACGCGTACAGGAAACACAGAAAAAAGCCCGCACCTGACAGTGCGGGCTTTTTTTTCGACCAAAGGTAACGAGGTAACAACCATGCGAGTGTTGAAGTTCGGCGGTACATCAGTGGCAAATGCAGAACGTTTTCTGCGGGTTGCCGATATTCTGGAAAGCAATGCCAGGCAGGGGCAGGTGGCCACCGTCCTCTCTGCCCCCGCCAAAATCACCAACCACCTGGTGGCGATGATTGAAAAAACCATTAGCGGCCAGGATGCTTTACCCAATATCAGCGATGCCGAACGTATTTTTGCCGAACTTCTGACGGGACTCGCCGCCGCCCAGCCGGGATTCCCGCTGGCGCAATTGAAAACTTTCGTCGACCAGGAATTTGCCCAAATAAAACATGTCCTGCATGGCATTAGTTTGTTAGGGCAGTGCCCGGATAGCATTAACGCTGCGCTGATTTGCCGTGGCGAGAAAATGTCGATCGCCATTATGGCCGGCGTATTAGAAGCGCGCGGTCACAACGTTACCGTTATCGATCCGGTCGAAAAACTGCTGGCAGTGGGGCATTACCTCGAATCTACTGTCGATATTGCAGAGTCCACCCGCCGTATTGCGGCAAGTCGTATTCCGGCTGATCACATGGTGCTGATGGCAGGTTTCACCGCCGGTAATGAAAAAGGCGAACTGGTGGTACTTGGACGCAACGGTTCCGACTACTCCGCGGCGGTGCTGGCTGCCTGTTTACGCGCCGATTGTTGCGAGATTTGGACGGACGTTGACGGGGTATATACCTGCGACCCGCGTCAGGTGCCCGATGCGAGGTTGTTGAAATCGATGTCCTACCAGGAAGCGATGGAGCTTTCCTACTTCGGCGCTAAAGTTCTTCACCCCCGCACCATTACCCCCATCGCCCAGTTCCAGATCCCTTGCCTGATTAAAAATACCGGAAATCCTCAAGCTCCAGGTACGCTCATTGGTGCCAGTCGTGATGAAGACGAATTACCGGTCAAGGGCATTTCCAATCTGAATAATATGGCAATGTTCAGCGTTTCCGGCCCGGGGATGAAAGGAATGGTCGGCATGGCGGCGCGCGTCTTTGCTGCAATGTCACGCGCCCGTATTTCCGTGGTGCTGATTACGCAATCATCTTCCGAATACAGTATCAGTTTCTGCGTTCCGCAAAGCGACTGTGTGCGAGCTGAACGGGCAATGCAGGAAGAGTTCTACCTGGAACTGAAAGAAGGCTTACTGGAGCCGCTGGCGGTGACGGAACGGCTGGCCATTATCTCGGTGGTAGGTGATGGTATGCGCACCTTGCGTGGGATCTCGGCGAAATTCTTTGCCGCGCTGGCCCGCGCCAATATCAACATTGTCGCTATTGCTCAGGGATCTTCTGAACGCTCAATCTCTGTCGTGGTAAATAACGATGATGCGACCACTGGCGTGCGCGTTACTCATCAGATGCTGTTCAATACCGATCAGGTTATCGAAGTGTTTGTGATTGGCGTCGGTGGCGTTGGCGGTGCGCTGCTGGAGCAACTGAAGCGTCAGCAAAGCTGGTTGAAGAATAAACATATCGACTTACGTGTCTGCGGTGTTGCTAACTCGAAGGCTCTGCTCACCAATGTGCATGGCCTAAATCTGGAAAACTGGCAGGAAGAACTGGCGCAAGCCAAAGAGCCGTTTAATCTCGGGCGCTTAATTCGCCTCGTGAAAGAATATCATCTGCTGAACCCGGTCATTGTTGACTGCACCTCCAGCCAGGCAGTGGCGGATCAATATGCCGACTTCCTGCGCGAAGGTTTCCACGTTGTCACGCCGAACAAAAAGGCCAACACCTCGTCGATGGATTACTACCATCTGTTGCGTCATGCGGCTGAAAAATCGCGGCGTAAATTCCTCTATGACACCAACGTTGGGGCTGGATTACCGGTTATTGAGAACCTGCAAAATCTGCTCAATGCTGGTGATGAATTGATGAAGTTCTCCGGCATTCTTTCAGGTTCGCTTTCTTATATCTTCGGCAAGTTAGACGAAGGCATGAGTTTCTCCGAGGCGACTACGCTGGCGCGGGAAATGGGTTATACCGAACCGGATCCGCGAGATGATCTTTCTGGTATGGATGTAGCGCGTAAACTATTAATTCTCGCTCGTGAAACGGGACGTGAACTGGAGCTGGCGGATATTGAAATTGAACCTGTGCTGCCCGCAGAGTTTAACGCTGAGGGTGATGTTGC";


    // calling the function to calculate the result
    _getOptimalCost(s1, s2);
    return 0;
}

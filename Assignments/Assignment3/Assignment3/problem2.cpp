#include <iostream>
#include <bits/stdc++.h>

using namespace std;

static int gap_penalty=30;
//static int mismatch_penalty=1;
static map<string,int> mismatchPenalty_map;
//map penalties for character A
mismatchPenalty_map.insert(pair<string,int>("AA",-91));
mismatchPenalty_map.insert(pair<string,int>("AC",114));
mismatchPenalty_map.insert(pair<string,int>("AG",31));
mismatchPenalty_map.insert(pair<string,int>("AT",123));
//map penalties for character C
mismatchPenalty_map.insert(pair<string,int>("CA",114));
mismatchPenalty_map.insert(pair<string,int>("CC",-100));
mismatchPenalty_map.insert(pair<string,int>("CG",125));
mismatchPenalty_map.insert(pair<string,int>("CT",31));
//map penalties for character G
mismatchPenalty_map.insert(pair<string,int>("GA",31));
mismatchPenalty_map.insert(pair<string,int>("GC",125));
mismatchPenalty_map.insert(pair<string,int>("GG",-100));
mismatchPenalty_map.insert(pair<string,int>("GT",114));
//map penalties for character T
mismatchPenalty_map.insert(pair<string,int>("TA",123));
mismatchPenalty_map.insert(pair<string,int>("TC",31));
mismatchPenalty_map.insert(pair<string,int>("TG",114));
mismatchPenalty_map.insert(pair<string,int>("TG",-91));



//function to
int _getbacktrackPath(int top,int left,int diagnol,int currentvalue,string t,string g,int i,int j)
{
    string map_key=string(1,t[i])+string(1,g[j]);
    if (top+ gap_penalty == currentvalue)
    {
        return 0;
    }
    else if (left + gap_penalty == currentvalue)
    {
        return 1;
    }
    else if (t[i]==g[j])
    {
        return 2;
    }
    else if (diagnol + mismatchPenalty_map[map_key] == currentvalue)
    {
        return 3;
    }
}






// returns the optimal cost
void _getOptimalCost(string str_target, string str_query)
{
    //Stores respective strings length
    int target_len = str_target.length();
    int query_len = str_query.length();

    int i, j;


    int optimalCost[target_len+1][query_len+1]= {0};

    for (i = 0; i <= (target_len); i++)
    {
        //initialising first column
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
        {
            //when both characters are equal
            if (str_target[i - 1] == str_query[j - 1])
            {
                optimalCost[i][j] = optimalCost[i - 1][j - 1];
            }
            else
            {
                map_key=string(1,t[i])+string(1,g[j]);
                //when both characters are not equal
                optimalCost[i][j] = min({optimalCost[i - 1][j - 1] + mismatchPenalty_map[map_key],optimalCost[i - 1][j] + gap_penalty,optimalCost[i][j - 1] + gap_penalty});
            }
        }
    }


    //computing the solution
    int max_length = query_len + target_len; //maximum length

    i = target_len;
    j = query_len;

    int target_position = max_length;
    int query_position = max_length;

   //Strings holding final values
    int target_final_str[max_length+1], query_final_str[max_length+1];

    while ( !(i == 0 || j == 0))
    {
        int value=_getbacktrackPath(optimalCost[i - 1][j],optimalCost[i][j - 1],optimalCost[i - 1][j - 1],optimalCost[i][j],str_target,str_query,i-1,j-1);
        switch(value)
        {
            //
        case 0:
            target_final_str[target_position--] = (int)str_target[i - 1];
            query_final_str[query_position--] = (int)'_';
            i--;
            break;

        case 1:
            target_final_str[target_position--] = (int)'_';
            query_final_str[query_position--] = (int)str_query[j - 1];
            j--;
            break;

        case 2:
            target_final_str[target_position--] = (int)str_target[i - 1];
            query_final_str[query_position--] = (int)str_query[j - 1];
            i--;
            j--;
            break;

        case 3:
            target_final_str[target_position--] = (int)str_target[i - 1];
            query_final_str[query_position--] = (int)str_query[j - 1];
            i--;
            j--;
            break;


        }
    }
    while (target_position > 0)
    {
        if (i > 0)
            target_final_str[target_position--] = (int)str_target[--i];
        else
            target_final_str[target_position--] = (int)'_';
    }
    while (query_position > 0)
    {
        if (j > 0)
            query_final_str[query_position--] = (int)str_query[--j];
        else
            query_final_str[query_position--] = (int)'_';
    }


    int id = 1;
    for (i = max_length; i >= 1; i--)
    {
        if ((char)query_final_str[i] == '_' && (char)target_final_str[i] == '_')
        {
            id = i + 1;
            break;
        }
    }

   // Printing the final answer
    cout << optimalCost[target_len][query_len] << "\n";

    for (i = id; i <= max_length; i++)
    {
        cout<<(char)target_final_str[i];
    }
    cout <<endl;
    for (i = id; i <= max_length; i++)
    {
        cout << (char)query_final_str[i];
    }

}

int main()
{

    string s1,s2;
    cin>>s1>>s2;
    // calling the function to calculate the result
    _getOptimalCost(s1, s2);
    return 0;
}

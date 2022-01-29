#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

/* takeaways
   - pass 1 eliminate non-celebrities
     - two pointers "c" (candidate) and "other". 
       "c" is set to 0 and "other" is set to n-1 
     - "c" will advance to next if 
       "other" doesn't know "c"; Current "c" 
       can't be a celebrity
     - conversely if "other" does know "c", 
       "other" itself can't a celebrity 
     - there is one two outcomes whenever "knows"
       function is called so one of the pointers
       has to move

   - pass 2 make sure every knows "c"
     - why? in pass 1 there are a lot of checks
       have not been done so we don't know
       for sure the candidate is a celebrity
     - let say if c is 5; we at least haven't 
       verified if 0,1,2,3, or 4 knows 5
*/

class Solution
{
private:
  vector<vector<int>> m_whoKnowsMe;

public:
  Solution(vector<vector<int>> whoKnowsMe)
  {
    m_whoKnowsMe = whoKnowsMe;
  }

  bool knows(int p1, int p2)
  {
    return m_whoKnowsMe[p1][p2] == 1;
  }

  int findCelebrity(int numOfPeople)
  {
    /* 
       - eliminate who is not a celebrity
       - whoever has not been eliminated
         will be the candidate
       - why "c" is just a candidate?
         - we haven't verified if everyone
           knows c during the eliminating
           process
         - let say if c is 5; we at least 
           haven't verified if 0,1,2,3, 
           or 4 knows 5  
     */
    int c = 0, other = numOfPeople - 1;
    while (c < other)
    {
      if (knows(other, c))
        /* 
           - eliminate other as it knows c
             hence it can't be a celebrity
           - move on to the next 
        */
        other--;
      else
        /*  
          - other doesn't know c; can't be
            a celebrity 
        */
        c++;
    }

    /* 
      - verify if everyone knows c,
        and c doesn't know anyone 
    */
    for (int i = 0; i < numOfPeople; i++)
    {
      if (i != c)
      {
        if (!knows(i, c) || knows(c, i))
          return -1;
      }
    }
    return c;
  }
};

/*
  Input: graph = [
    [1,1,0],
    [0,1,0],
    [1,1,1]
  ]
  Output: 1
*/
tuple<vector<vector<int>>, int> testFixture1()
{

  vector<vector<int>> vec{{1, 1, 0},
                          {0, 1, 0},
                          {1, 1, 1}};

  return make_tuple(vec, 3);
}
/*
Input: graph = [
  [1,0,1],
  [1,1,0],
  [0,1,1]
]
Output: -1
*/
tuple<vector<vector<int>>, int> testFixture2()
{

  vector<vector<int>> vec{{1, 0, 1},
                          {1, 1, 0},
                          {0, 1, 1}};

  return make_tuple(vec, 3);
}

void printVec(vector<int> &vec)
{
  if (vec.size() == 0)
  {
    cout << "[]";
    return;
  }

  for (int i = 0; i < vec.size(); i++)
  {
    cout << "[" << vec[i];
    if (i < vec.size() - 1)
      cout << ",";
    cout << "]";
  }
}

void test1()
{
  tuple<vector<vector<int>>, int> testFixture = testFixture1();
  vector<vector<int>> whoKnowsme = get<0>(testFixture);
  int n = get<1>(testFixture);
  Solution *sol = new Solution(whoKnowsme);
  cout << "Test 1 - expect to see 1" << endl;
  cout << "result: " << sol->findCelebrity(n) << endl;
}

void test2()
{
  tuple<vector<vector<int>>, int> testFixture = testFixture2();
  vector<vector<int>> whoKnowsme = get<0>(testFixture);
  int n = get<1>(testFixture);
  Solution *sol = new Solution(whoKnowsme);
  cout << "Test 2 - expect to see -1" << endl;
  cout << "result: " << sol->findCelebrity(n) << endl;
}

main()
{
  test1();
  test2();
  return 0;
}
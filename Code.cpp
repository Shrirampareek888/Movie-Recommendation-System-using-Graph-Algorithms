
//****************** Movie Recommendation System *********************

//------------------------ Header Files ------------------------------
#include<bits/stdc++.h>
using namespace std;
//--------------------------------------------------------------------

// ----------------------- Graph Declaration -------------------------
vector <pair<int, int>> graph[100];
// -------------------------------------------------------------------

// ----------------------- To Store the path -------------------------
vector<int> ans;
// -------------------------------------------------------------------

// ----------------------- Total Size of Graph -----------------------
int tsize = 0;
// -------------------------------------------------------------------


// ---------------- Helping Function for detecting cycles ------------
bool isCyclicUtil(int v, bool visited[], int parent)
{
  visited[v] = true;
  for (auto i = graph[v].begin(); i != graph[v].end(); ++i)
  {
    if (!visited[i->first])
    {
      if (isCyclicUtil(i->first, visited, v))
        return true;
    }
    else if (i->first != parent)
      return true;
  }
  return false;
}
// -------------------------------------------------------------------


// ------------------ Function for detecting cycles ------------------
bool isCyclic()
{
  bool *visited = new bool[tsize];
  for (int i = 0; i < tsize; i++)
    visited[i] = false;
  for (int u = 0; u < tsize; u++)
  {
    if (!visited[u])
      if (isCyclicUtil(u, visited, -1))
        return true;
  }
  return false;
}
// -------------------------------------------------------------------


// ----------- Helping Function for detecting Connected Components ---
void DFSUtil(int v, bool visited[])
{
  visited[v] = true;
  for (auto i = graph[v].begin(); i != graph[v].end(); ++i)
    if (!visited[i->first])
      DFSUtil(i->first, visited);
}
// -------------------------------------------------------------------


// ----------- Function for detecting Connected Components ------------
int connected_comp()
{
  int cnt = 0;
  bool visited[tsize];
  memset(visited, false, sizeof(visited));
  for (int v = 0; v < tsize; v++) {
    if (visited[v] == false) {
      DFSUtil(v, visited);
      cnt++;
    }
  }
  return cnt;
}
// -------------------------------------------------------------------


// ------------------ Function for Storing Path ----------------------
void printPath(vector<int> parent, int j)
{
  if (parent[j] == - 1)
    return;

  printPath(parent, parent[j]);

  ans.push_back(j);
}
// -------------------------------------------------------------------


// ----------------- Function for Finding Path -----------------------
int path(int src, int dest)
{
  priority_queue< pair<int, int>, vector <pair<int, int>> , greater<pair<int, int>> > pq;
  vector<int> dist(100, 10000);
  vector<int> parent(100);
  parent[src] = -1;
  pq.push(make_pair(0, src));
  dist[src] = 0;
  while (!pq.empty())
  {
    int u = pq.top().second;
    pq.pop();
    for (auto i = graph[u].begin(); i != graph[u].end(); ++i)
    {
      int v = (*i).first;
      int weight = (*i).second;
      if (dist[v] > dist[u] + weight)
      {
        dist[v] = dist[u] + weight;
        parent[v] = u;
        pq.push(make_pair(dist[v], v));
      }
    }
  }
  printPath(parent, dest);
  return dist[dest];
}
// -------------------------------------------------------------------


// ----------- Main Function -------------
int main()
{
  // ----------- Input and Output Files -------------
  freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);

  // ----------- Hashing for strings to vertices and vice-versa --
  map<string, int> cast_to_vertices;
  map<string, string> indvfilms;
  map<int, string> vertices_to_movies, vertices_to_cast;

  // -------------------- Storing Count -----------------------------
  int cnt = 0;

  // --------------------- Debug Flag -------------------------------
  int debflag = 0;

  // ------------ For Storing Recommended Movies --------------------
  vector<string> recommended;

  // -------------------- For Storing Desired Cast ------------------
  string c1, c2;



  // -------------------- Loading Cast Data -------------------------
  while (1)
  {
    string tempcast; getline(std::cin, tempcast);
    if (tempcast == "")break;
    if (debflag)
    {
      cout << tempcast << " at node " << cnt << endl;
    }
    cast_to_vertices[tempcast] = cnt; cnt++;
  }
  if (debflag)
  {
    cout << endl << "Cast Loading Successful" << endl << endl;
  }
  // -------------------------------------------------------------------



  // ----------- Loading Movies and Mapping Movies to Cast -------------
  while (1)
  {
    string movname;
    int castcnt = 0;
    getline(std::cin, movname);
    if (movname == "")break;
    cin >> castcnt;
    vertices_to_movies[cnt] = movname;
    if (debflag)
    {
      cout << "For Movie: " << movname << endl;
    }
    while (castcnt--)
    {
      string singcast; cin >> singcast;
      if (debflag)
      {
        cout << singcast << endl;
      }
      graph[cnt].push_back(make_pair(cast_to_vertices[singcast], 1));
      graph[cast_to_vertices[singcast]].push_back(make_pair(cnt, 1));
    }
    if (debflag)
    {
      cout << "Cast Added Successfully" << endl << endl;
    }
    cnt++;
    string tp; getline(std::cin, tp);
  }
  tsize += cnt;
  // -------------------------------------------------------------------



  // ----------- Adding Individual Films to each Cast  -----------------
  while (1)
  {
    string tcast, ifilm;
    getline(std::cin, tcast);
    if (tcast == "")break;
    cin >> ifilm;
    if (debflag)
    {
      cout << "Individual Film of " << tcast << " Added Successfully" << endl << endl;
    }
    indvfilms[tcast] = ifilm;
    string tp; getline(std::cin, tp);
  }
  ans.clear();
  for (auto it = cast_to_vertices.begin(); it != cast_to_vertices.end(); it++)
  {
    vertices_to_cast[it->second] = it->first;
  }
  // -------------------------------------------------------------------



  // ------------ Taking Desired Cast Input ----------------------------
  cin >> c1; cin >> c2;
  // -------------------------------------------------------------------



// ------------Finding and Adding Path Movies --------------------------
  if (graph[cast_to_vertices[c1]].size() != 0 && graph[cast_to_vertices[c2]].size() != 0)
   {
    if (debflag)
      cout << "Recommendation System Path is : " << endl << endl;
    vertices_to_movies[path( cast_to_vertices[c1], cast_to_vertices[c2])] ;
    if (debflag)
      cout << c1 ;
    for (int i = 0; i < ans.size(); i++)
    {
      if (ans[i] >= cast_to_vertices.size())
      {
        recommended.push_back(vertices_to_movies[ans[i]]);
        if (debflag)
          cout << " -> " << vertices_to_movies[ans[i]];
      }
      else {
        if (debflag)
          cout << " -> " << vertices_to_cast[ans[i]] ;
      }
      //cout << ans[i] << " ";
    }
    if (debflag)
      cout << endl << endl;
  }
// -------------------------------------------------------------------



  // ------------ Adding Individual Movie ----------------------------
  recommended.push_back(indvfilms[c1]);
  recommended.push_back(indvfilms[c2]);
  cout << "Recommended Movies Are: " << endl << endl;
  for (int i = 0; i < recommended.size(); i++)
  {
    cout << recommended[i] << endl;
  }
  cout << endl;
// -------------------------------------------------------------------



  // ----------- Finding Max and Min Connected Cast ------------------
  int max_connected_cast = -1, min_connected_cast = 10000;
  string max_connected_cast_name, min_connected_cast_name;
  for (auto it = cast_to_vertices.begin(); it != cast_to_vertices.end(); it++)
  {
    int tmp = graph[it->second].size();
    if (max_connected_cast < tmp)
    {
      max_connected_cast = graph[it->second].size();
      max_connected_cast_name = it->first;
    }
    if (min_connected_cast > tmp)
    {
      min_connected_cast = graph[it->second].size();
      min_connected_cast_name = it->first;
    }
  }
  if (max_connected_cast != -1)
  {
    cout << "Most Connected Actor/Actress is: " << max_connected_cast_name << " with " << max_connected_cast << " relations" << endl << endl;
  }
  if (min_connected_cast != 10000)
  {
    cout << "Least Connected Actor/Actress is: " << min_connected_cast_name << " with " << min_connected_cast << " relations" << endl << endl;
  }
  // -------------------------------------------------------------------



  // ----------- Finding Max and Min Connected Movie -------------------
  int max_connected_movie = -1, min_connected_movie = 10000;
  string max_connected_movie_name, min_connected_movie_name;
  for (auto it = vertices_to_movies.begin(); it != vertices_to_movies.end(); it++)
  {
    if (it->first < cast_to_vertices.size())
      continue;
    int tmp = graph[it->first].size();
    if (max_connected_movie < tmp)
    {
      max_connected_movie = graph[it->first].size();
      string st = it->second;
      max_connected_movie_name = st;
    }
    if (min_connected_movie > tmp)
    {
      min_connected_movie = graph[it->first].size();
      string st = it->second;
      min_connected_movie_name = st;
    }
  }
  if (max_connected_movie != -1)
  {
    cout << "Most Connected Movie is: " << max_connected_movie_name << " with " << max_connected_movie << " relations" << endl << endl;
  }
  if (min_connected_movie != 10000)
  {
    cout << "Least Connected Movie is: " << min_connected_movie_name << " with " << min_connected_movie << " relations" << endl << endl;
  }
// -------------------------------------------------------------------



  // ------------ Finding No Of Connected Components -----------------
  cout << "No of Connected Components are : " << connected_comp() << endl << endl;
// -------------------------------------------------------------------



  // ------------ Finding if cycle exists ----------------------------
  cout << "Cyclic Check: ";
  if (isCyclic())
    cout << "True" << endl;
  else
    cout << "False" << endl;
  // -------------------------------------------------------------------
}
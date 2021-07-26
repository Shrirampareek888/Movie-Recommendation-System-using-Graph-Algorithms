#include<bits/stdc++.h>
using namespace std;
vector <pair<int, int>> graph[100];
vector<int> ans;
int tsize = 0;
map<string, int> cast_to_vertices;
map<string, string> indvfilms;
map<int, string> vertices_to_movies, vertices_to_cast;
set<int> lmovies, lcast,amovies,acast;
int debflag = 0;
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
void DFSUtil(int v, bool visited[])
{
  visited[v] = true;
  for (auto i = graph[v].begin(); i != graph[v].end(); ++i)
    if (!visited[i->first])
      DFSUtil(i->first, visited);
}
int connected_comp()
{
  int cnt = 1;
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
void printPath(vector<int> parent, int j)
{
  if (parent[j] == - 1)
    return;

  printPath(parent, parent[j]);

  ans.push_back(j);
}
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

void printpathh(vector<int>& path)
{
  int size = path.size();

  for (int i = 0; i < size; i++)
  {
    if (path[i] >= cast_to_vertices.size())
    {
      lmovies.insert(path[i]);
      if (debflag)
        cout << vertices_to_movies[path[i]] << " -> ";
    }
    else {
      lcast.insert(path[i]);
      if (debflag)
        cout << vertices_to_cast[path[i]] << " -> ";
    }
  }
  if (debflag)
    cout << endl << endl;
}

int isNotVisited(int x, vector<int>& path)
{
  int size = path.size();
  for (int i = 0; i < size; i++)
    if (path[i] == x)
      return 0;
  return 1;
}

void findpaths(int src, int dst)
{
  queue<vector<int> > q;

  vector<int> path;
  path.push_back(src);
  q.push(path);
  while (!q.empty()) {
    path = q.front();
    q.pop();
    int last = path[path.size() - 1];
    if (last == dst)
      printpathh(path);
    for (int i = 0; i < graph[last].size(); i++) {
      // cout << " g " << graph[last][i].first << " " << endl;
      if (isNotVisited(graph[last][i].first, path)) {
        vector<int> newpath(path);
        newpath.push_back(graph[last][i].first);
        q.push(newpath);
      }
    }
  }
}


int main()
{
cout<<"======================================================================================================================="<<endl;
  cout<<"\t\t\t\t\tWelcome to Movie Recommendation System "<<endl<<endl;
  cout<<"======================================================================================================================="<<endl<<endl;
  cout<<"Enter Movie Data:\n\n";

  int cnt = 0;
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
      cout<<"======================================================================================================================="<<endl<<endl;
    cout << endl << "Cast Loading Successful" << endl << endl;
    cout<<"======================================================================================================================="<<endl<<endl;
  }
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
  if (debflag)
    {
        cout<<"======================================================================================================================="<<endl<<endl;
      cout << "Multicast Movies Added Successfully" << endl << endl;
      cout<<"======================================================================================================================="<<endl<<endl;
    }
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
  if (debflag)
    {
        cout<<"======================================================================================================================="<<endl<<endl;
      cout << "Individual Movies Added Successfully" << endl << endl;
      cout<<"======================================================================================================================="<<endl<<endl;
    }
  ans.clear();
  for (auto it = cast_to_vertices.begin(); it != cast_to_vertices.end(); it++)
  {
    vertices_to_cast[it->second] = it->first;
  }
  cout<<"Enter Favorite Actor/Actress :"<<endl;
  string c1, c2;
  cin >> c1; cin >> c2;
  vector<string> recommended;
  if (graph[cast_to_vertices[c1]].size() == 0 || graph[cast_to_vertices[c2]].size() == 0)
  {

  }
  else {
    if (debflag)
    {
         cout<<"======================================================================================================================="<<endl<<endl;
         cout << "Recommendation System Path is : " << endl << endl;
    }

    vertices_to_movies[path( cast_to_vertices[c1], cast_to_vertices[c2])] ;
    if (debflag)
      cout << c1 ;
    for (int i = 0; i < ans.size(); i++)
    {
      if (ans[i] >= cast_to_vertices.size())
      {
          amovies.insert(ans[i]);
        recommended.push_back(vertices_to_movies[ans[i]]);
        if (debflag)
          cout << " -> " << vertices_to_movies[ans[i]];
      }
      else {
            acast.insert(ans[i]);
        if (debflag)
          cout << " -> " << vertices_to_cast[ans[i]] ;
      }
      //cout << ans[i] << " ";
    }
    if (debflag)
      cout << endl << endl;
  }
  if(recommended.size()==0 && connected_comp()>1)
  {
      cout<<"There is no direct link between movies of the given actors."<<endl;
  }
  recommended.push_back(indvfilms[c1]);
  recommended.push_back(indvfilms[c2]);
  cout<<"======================================================================================================================="<<endl<<endl;
  cout << "\t\t\t\t\t\tRecommendations For You! " << endl << endl;
  cout<<"======================================================================================================================="<<endl<<endl;
  cout<<"Most Recommended:"<<endl<<endl;
  for (int i = 0; i < recommended.size(); i++)
  {
    cout << recommended[i] << endl;
  }
  cout << endl;

  int src = cast_to_vertices[c1]; int dst = cast_to_vertices[c2];

  findpaths(src, dst);
    cout<<"======================================================================================================================="<<endl<<endl;
  cout << "Movies you may also like:" << endl<<endl;
  for (auto it = lmovies.begin(); it != lmovies.end(); it++)
  {
      if(amovies.find(*it)==amovies.end())
    cout << vertices_to_movies[*it] << endl;
  }
    cout<<"======================================================================================================================="<<endl<<endl;
  cout << "You can also watch movies by these actors/actresses:" << endl<<endl;
  for (auto it = lcast.begin(); it != lcast.end(); it++)
  {
      if(acast.find(*it)==acast.end() && src!=*it && dst!=*it)
    cout << vertices_to_cast[*it] << endl;
  }
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
  cout<<"======================================================================================================================="<<endl<<endl;
  cout<<"\t\t\t\tSome facts of the given data that you may like!"<<endl;
    cout<<"======================================================================================================================="<<endl<<endl;
  if (isCyclic())
    cout << "Your Favorite actors have multiple movie links!" << endl;
  else
    cout << "Your Favorite actors have at most 1 movie link" << endl<<endl;
  if (max_connected_cast != -1)
  {
    cout << "Actor/Actress with most movies: " <<endl<< max_connected_cast_name << " with " << max_connected_cast << " relations" << endl << endl;
  }
  if (min_connected_cast != 10000)
  {
    cout << "Actor/Actress with least movies: " <<endl<< min_connected_cast_name << " with " << min_connected_cast << " relations" << endl << endl;
  }
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
    cout << "Movie with maximum cast: " <<endl<< max_connected_movie_name << " with " << max_connected_movie << " relations" << endl << endl;
  }
  if (min_connected_movie != 10000)
  {
    cout << "Movie with minimum cast:" <<endl<< min_connected_movie_name << " with " << min_connected_movie << " relations" << endl << endl;
  }
    cout<<"======================================================================================================================="<<endl<<endl;
}

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <iostream>
#include <vector>
using namespace std;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS> MyGraph;
typedef boost::graph_traits<MyGraph>::vertex_descriptor MyVertex;
typedef boost::graph_traits<MyGraph>::edge_descriptor MyEdge;

class MyVisitor : public boost::default_dfs_visitor
{
  std::vector<MyVertex> stackit;
  std::vector< std::vector<int> > path_list;
  std::size_t longest_list = 0;
public:
  std::unordered_map<int, std::unordered_map<int, std::vector<MyVertex>>> hashmap;

  void discover_vertex(MyVertex v, const MyGraph& g)
	{
    this->stackit.push_back(v);
	}

  void finish_vertex(MyVertex v, const MyGraph & g)
  {
    if( stackit.size() >= longest_list )
    {
      auto it1 = stackit.begin();
      auto it2 = it1 + 1;
      auto it3 = stackit.end();

      for( ; it1 != it3; ++it1)
      {
        for(it2 = it1+1;  ; ++it2)
        {
          if( this->hashmap.count(*it1) == 0)
          {
            this->hashmap[int(*it1)][int(*it1)] = std::vector<MyVertex>(it1,it2);
          }
          else if( this->hashmap[*it1].count(*(it2-1)) == 0)
          {
            this->hashmap[int(*it1)][int(*(it2-1))] = std::vector<MyVertex>(it1, it2);
          }

          if(it2 == it3)
            break;
        }
      }

    }

    longest_list = stackit.size();
    this->stackit.pop_back();
  }

};


int main(void)
{
	MyGraph g;
	boost::add_edge(0, 1, g);
  boost::add_edge(0, 2, g);
	boost::add_edge(1, 2, g);
	boost::add_edge(1, 3, g);
	boost::add_edge(2, 5, g);
  boost::add_edge(6, 7, g);

  MyVisitor vis;

  boost::depth_first_search(g, boost::visitor(vis));

  for(auto v : vis.hashmap[0][1])
    std::cout << v << " ";


  return 0;
}

//
//  Graph.hpp
//  E-R random graph
//
//  Created by Raffaele Marino on 2018-10-15.
//  Copyright © 2018 Raffaele Marino. All rights reserved.
//

// class E-R graph. Nodes goes from 0 to N

// Fixed a value of N this calss build an E-R random graph with edge density equal to p
// The probability density is given as INPUT fro terminal command

#ifndef Graph_h
#define Graph_h
#include "Header.h"
#include "Random.hpp"
class Graph{
    
    
public:
    
    /*declaration public members for Graph.hpp*/
    
    Graph(int argc, const char * argv[]){
        
        
        _argc=argc;
        for (int i=0; i<_argc; ++i) {
            _argv.push_back(argv[i]);
        }
        _graphn=0;
    
        _N=(long unsigned int)atoi(argv[1]); // from the terminal
        p=(double)atof(argv[2]); // from the terminal
        _linx.resize(_N);  // N times N matrix
        _neighofi.resize(_N);
            for (int i=0; i<_N; ++i) {
            _linx[i].resize(_N);
            }
    };
    
    ~Graph(){};
    vector<vector<bool> > build_graph(Random &MyRand);
    long unsigned int degree_site(int &i);
    template<typename T>
    double meanvalue(vector<T>  &a);
    template<typename T>
    double sdvalue(vector<T> &a, const double mean);
    long unsigned  int & orderGraph();
    long unsigned int & sizeGraph();
    template<typename  T>
    void display(vector<T> &d);
    void opengraph();
    double edge_density(){return p;};
    template<typename T>
    void getHC(T i){
        HC=(unsigned int) i;
        hide_a_clique();
    }
    vector<vector<bool> > AdjM(){return _linx;}//adjecency matrix is returned
    
     vector<vector<long unsigned int> > _neighofi;//vector neighbours of site i
    
private:
    /*declaration private variables for Graph.hpp*/
    vector<long unsigned int> _count;  //degree of site i
    vector<vector<bool> > _linx; //adjecency matrix
    vector<string> _argv; // copy of argv vector
    double p; // edge density equal to 0.5
    long unsigned int _N; //order of the graph
    long unsigned int _M; // size of the graph
    unsigned int _graphn; // counter graph
    unsigned int HC; // size of the hidden clique
    int _argc; // copy of argc
    void hide_a_clique(); // hide a clique of size HC

    
    
};

template<typename T>
void Graph::display(vector<T> &d){
    for (int i=0; i<d.size(); ++i) {
        cout<<i<<" "<<d[i]<<endl;
    }
}

inline long unsigned int & Graph::orderGraph(){return _N;}

inline long unsigned int & Graph::sizeGraph(){return _M;}

inline void Graph::hide_a_clique(){
    if(HC==_N){
        cout<<"WARNING you have a complete Graph"<<endl;
        
    }
    for (unsigned int i=0;i<HC;++i){
        for (unsigned int j=i+1;j<HC;++j){
            if (!_linx[i][j]){
                _linx[i][j] = _linx[j][i] = true;
                _M+=2;
                ++_count[i];++_count[j];
                _neighofi[i].push_back(j);
                _neighofi[j].push_back(i);
            };
        };
    };
    for (int i=0; i<HC; ++i) {
        sort(_neighofi[i].begin(),_neighofi[i].end());
    }
}

vector<vector<bool> > Graph::build_graph(Random &MyRand){
    _graphn++;
    cout<<"This is the graph number: "<<_graphn<<endl;
    MyRand.GetNSITE(_N);
    _count.resize(_N);
    _M=0;
    for (long unsigned int i=0; i<_N; ++i) {
            _linx[i][i] = false;
            _count[i]=0;
            _neighofi[i].clear();
    }
    
    for (int i=0;i<_N-1;++i) { // here we are building the graph
        for (int j= i+1;j<_N;++j){
            if ( MyRand.random_number()> p) { //E.R. random graph G(N,p=0.5)
                _linx[i][j] = _linx [j][i] = true;
                _M+=2;
                ++_count[i];++_count[j];
                _neighofi[i].push_back(j);
                _neighofi[j].push_back(i);
            }else {
                _linx[i][j] = _linx[j][i] = false;
            }
        }
    }
    return _linx; // return adjecency as a vector of vector of boolean variables matrix
};


inline long unsigned int Graph::degree_site(int &i){return _count[i];} // degree site i


template<typename T>
inline double Graph::meanvalue(vector<T>  &a){
    double sum=0;
    for(int i=0; i<a.size(); ++i){
        sum+=a[i];
    }
    
    return (double)sum/(double)a.size(); // mean
}

template<typename T>
inline double Graph::sdvalue(vector<T> &a, const double mean){
    double sdv=0;
    double sum=0;
    
    for(int i=0; i<a.size(); ++i){
        sum+=((double)a[i]-mean)*((double)a[i]-mean);
    }
    sdv=sum/(double)(a.size()-1);
    return (long double)sqrt(sdv); // standard deviation
}



#endif /* Graph */

//
//  main.cpp
//  Tester E-R random graph
//
//  Created by Raffaele Marino on 2018-10-15.
//  Copyright © 2018 Raffaele Marino. All rights reserved.
//

#include "Header.h"
#include "Random.hpp"
#include "Graph.hpp"
int main(int argc, const char * argv[]) {

    Random MyRand;
    MyRand.print_seed();
    Graph MyGraph(argc, argv);
    
        long int Nsite;
        Nsite=MyGraph.orderGraph();
        vector<vector<bool> > test;
        vector<long unsigned int> _v_test;
    for(int i=0; i<100; ++i){
    test=MyGraph.build_graph(MyRand);
    cout<<"E-R random graph with edge density equal to "<<MyGraph.edge_density()<<endl;
    cout<<MyGraph.orderGraph()<<endl;
    cout<<MyGraph.sizeGraph()<<endl;
    _v_test.push_back(MyGraph.sizeGraph());
    
    for (int i=0; i<MyGraph.orderGraph(); ++i) {
        for (int j=0; j<MyGraph._neighofi[i].size(); ++j) {
            cout<<i<<" "<<MyGraph._neighofi[i][j]<<endl;
        }
    }

    unsigned int HC=sqrt(Nsite);
    cout<<"I am planting a clique of size "<<HC<<endl;
    MyGraph.getHC(HC);
    
      cout<<"I am verifing that the clique has been planted"<<endl;
    for (int i=0; i<MyGraph.orderGraph(); ++i) {
        for (int j=0; j<MyGraph._neighofi[i].size(); ++j) {
            cout<<i<<" "<<MyGraph._neighofi[i][j]<<endl;
        }
    }
}
    
    const double mean=MyGraph.meanvalue<long unsigned int>(_v_test);
    cout<<"maen and std size of graphs"<<endl;
    cout<<mean<<" "<<MyGraph.sdvalue<long unsigned int>(_v_test,mean)<<endl;
    return 0;
}

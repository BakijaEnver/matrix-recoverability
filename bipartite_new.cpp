#include <iostream>
#include "graph.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <bits/stdc++.h> 
#include <fstream>

using namespace std;

Graph::rand rd;
Graph::gen Graph::generator = Graph::gen(rd());

double probability(int n, int m, int d, int p, int iterations, vector<int> *histog) {
    double numCompact = 0;
    double numNotCompact = 0;
    int histogram[100] = {0};
    for(int i = 0; i < iterations; i++) {
        Graph graph(n,m,d);
        graph.makeRandomEdges(false);
        graph.deletePNodes(p);
        graph.computeMaxFlow();
        int s = graph.getCompactor();
        histogram[s]++;
        if(graph.checkZeroFlow()) {
            numCompact++;
        } else {
            numNotCompact++;
        }
    }
    for(int i = 1; i < 100; i++) {
        //if(histogram[i] != 0) {
            histog->push_back(i);
            histog->push_back(histogram[i]);
        //}
    }
    return numCompact/(double)iterations;
  
}


void generateData(int n, int m, int d, int iterations) {

    ofstream myfile, histfile;
    string name = to_string(n) + to_string(m) + to_string(d);
    string s = "data" + name + ".txt";
    string s1 = "histograms" + name + ".txt";
    myfile.open(s.c_str());
    histfile.open(s1.c_str());
    myfile << n << " " << m << " " << d  << " " << iterations << endl;
    for(int i = 1; i <= m-n; i+=3) myfile << i << " ";
    myfile << endl;

    for(int i = 1; i <= m-n; i+=3) {
        vector<int> histogram;
        double val = probability(n,m,d,i,iterations,&histogram);
        myfile << val << " ";
        histfile << i << " ";
        for(int j = 0; j < 20; j++) {
            histfile << histogram[j] << " ";
        }
        histfile << endl;
    }
    myfile.close();

}

void getGraph(int n, int m, int d, int p, int comp) {

    //while(true){
        Graph graph(n,m,d);
        graph.makeRandomEdges(false);

        graph.printGraphTxt("original");
        graph.computeMaxFlow();
        cout << graph.getProbability(comp, p) << endl;
        graph.deletePNodes(p);
        graph.computeMaxFlow();
        int s = graph.getCompactor();

        /*if(s >= comp){
            graph.printGraphComplete("complete");
            break;
        }*/
    //}

}


void getMatrix(int n, int m, int d, int fieldSize, int corrected, int samples) {


        string s = "matrices/original.txt";
        string s1 = "matrices/info.txt";
        std::ofstream myfile;
        myfile.open(s1.c_str(), std::fstream::app);
        myfile << n << " " << m << " "  << d << " "  << fieldSize << " "  << corrected << " " << samples;
        myfile.close();
        myfile.open(s.c_str(), std::fstream::app);

        for (int i = 0; i < samples; i++) {
            Graph graph(n,m,d);
            graph.makeRandomEdges(corrected);
            graph.printMatrix(myfile, fieldSize);
        }


}

void getFullMatrix(int n, int m, int d, int fieldSize, int corrected, int samples) {


        string s = "matrices/original.txt";
        std::ofstream myfile;
        myfile.open(s.c_str(), std::fstream::app);
        
	Graph graph(n,m,d);
        for (int i = 0; i < samples; i++) {
            graph.printFullMatrix(myfile, n, m, fieldSize);
        }


}

int main (int argc, const char *argv[]) {

    // matrix size m, n, out degree, field size, corrected or not, number of samples
    getFullMatrix(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));



    //generateData(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
        
}

#include "graph.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <string>
#include <algorithm>
#include <bits/stdc++.h> 
#include <fstream>
#include <time.h>

Graph::Graph(int n, int m, int Out) {
    N=n;
    M=m;
    out = Out;
    for (int i = 0; i < N; i++) ListN.push_back(i);
    for (int i = 0; i < M; i++) ListM.push_back(i);
}

Graph::Graph(){

}

int Graph::getN(){
    return N;
}

int Graph::getM(){
    return M;
}

int Graph::getOut(){
    return out;
}

void Graph::setN(int n) {
    N = n;
}

void Graph::setM(int m) {
    M = m;
}

void Graph::setOut(int Out) {
    out = Out;
}

void Graph::calculateInDegree(){
    int inDeg = (N * out) / M;
    double inDegDouble = (N * out) / (double)M, fractpart, intpart;
    fractpart = modf (inDegDouble , &intpart);

    nodesDegMore = round(M * fractpart);
    nodesDegLess = M - nodesDegMore;
    DegLess = inDeg;
    DegMore = inDeg + 1;
    

    if(N * out != (DegLess * nodesDegLess + DegMore * nodesDegMore)) {
        std::cout << "Unable to create edges." << std::endl;
        exit(EXIT_FAILURE);
    }

    //std::cout << nodesDegMore << " " << DegMore << std::endl << nodesDegLess << " " << DegLess << std::endl;
}

void Graph::permutation(int n) {
        for (int i=n; i<buffer.size(); i++) {
                std::uniform_int_distribution<int> dis(i, buffer.size()-1);
                int v = dis(generator);
                int tmp = buffer[v];
                buffer[v] = buffer[i];
                buffer[i] = tmp;
        }

}

void Graph::generatePermutation() {

    for (int i = 0; i < N*out; i++) {
        buffer.push_back(i);
    }

    for (int i = 0; i < nodesDegLess; i++) {
        permutation(i * DegLess);
    }     
    for (int i = nodesDegLess; i < nodesDegLess + nodesDegMore - 1; i++) {
        permutation(i * DegMore);
    }

}

void Graph::reserveSpace(){

    adjListN.reserve(N);
    adjListM.reserve(M);
    adjListN.resize(N);
    adjListM.resize(M);

    for (int i = 0; i < N; i++) {
        adjListN[i].reserve(out);
    }

    for (int i = 0; i < M; i++) {
        adjListM[i].reserve(DegMore);
    }

}

bool Graph::checkGraphValidity() {

    for(int i = 0; i < adjListM.size(); i++) {
        for(int j = 0; j < adjListM[i].size(); j++) {
            if(count(adjListM[i].begin(), adjListM[i].end(), adjListM[i][j]) > 1) {
                return false;
            }
        }
    }

    return true;

}

void Graph::printAdjListN() {

     for(int i = 0; i < adjListN.size(); i++) {
        for(int j = 0; j < adjListN[i].size(); j++) {
            std::cout << adjListN[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

void Graph::printAdjListM() {

     for(int i = 0; i < adjListM.size(); i++) {
        for(int j = 0; j < adjListM[i].size(); j++) {
            std::cout << adjListM[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

void Graph::makeRandomEdges(bool check){

    calculateInDegree();
    generatePermutation();
    reserveSpace();


    int node = 0;
    for (int i = 0; i < nodesDegLess * DegLess; i+= DegLess) {
        for(int j = i; j < i + DegLess; j++){
            adjListM[node].push_back(buffer[j]/out);
            adjListN[buffer[j]/out].push_back(node);
        }
        node++;
    }

    for (int i = nodesDegLess * DegLess; i < buffer.size(); i+= DegMore) {
        for(int j = i; j < i + DegMore; j++){
            adjListM[node].push_back(buffer[j]/out);
            adjListN[buffer[j]/out].push_back(node);
        }
        node++;
    }

    if(check){
        if(!checkGraphValidity()){
            buffer.clear();
            adjListM.clear();
            adjListN.clear();
            makeRandomEdges(check);
        }
    }

}

bool Graph::bpm(int u, bool seen[], int matchR[]) {

    for (int v = 0; v < M; v++)
    {
        if (existsEdge(u,v) && !seen[v])
        {
            seen[v] = true;
 
            if (matchR[v] < 0 || bpm(matchR[v], seen, matchR))
            {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;

}

void Graph::computeMaxFlow() {
    
    maxflow.resize(N);
    std::fill(maxflow.begin(), maxflow.end(), -1);

    int matchR[M];
    memset(matchR, -1, sizeof(matchR));
 
    int result = 0;
    for (int u = 0; u < N; u++)
    {
        bool seen[M];
        memset(seen, 0, sizeof(seen));
 
        if (bpm(u, seen, matchR))
            result++;
    }
 
    for(int i = 0; i < M; i++) {
        if(matchR[i]!=-1) {
            maxflow[matchR[i]] = i;
        }
    }

}

bool Graph::existsEdge(int u, int v) {
    for(int i = 0; i < adjListN[u].size(); i++) {
        if (adjListN[u][i] == v) return true;
    }
    return false;
}

void Graph::printFlow() {
    for(int i = 0; i < maxflow.size(); i++) {
        std::cout << maxflow[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<std::vector<int>> Graph::getAdjListN(){

    return adjListN;
}

bool Graph::checkZeroFlow() {
    for(int i = 0; i < maxflow.size(); i++) {
        if( maxflow[i] == -1) return true;
    }
    return false;
}

void Graph::printGraphTxt(std::string s) {

    std::ofstream myfile;
    s += ".txt";
    myfile.open(s.c_str());

    for (int i = 0; i < ListN.size(); i++) {
        myfile << "x" << ListN[i] << " ";
    }
    myfile << std::endl;

    for (int i = 0; i < ListM.size(); i++) {
        myfile << "y" << ListM[i] << " ";
    }
    myfile << std::endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (existsEdge(i,j)) {
	    myfile << "x" << i << " y" << j << std::endl;
	   }
        }
    }
    myfile.close();
}

void Graph::printMatrix(std::ofstream &myfile, int fieldSize) {

    std::uniform_int_distribution<int> dis(1,fieldSize-1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (existsEdge(i,j)) {
                int v = dis(generator);
		int rr = v;
		myfile << rr;
            } else {
		myfile << 0;
	    }
		if (j < M-1) {
		myfile << " ";
		}
        }
	myfile << std::endl;
    }
}

void Graph::printFullMatrix(std::ofstream &myfile, int N, int M, int fieldSize) {

    std::uniform_int_distribution<int> dis(1,fieldSize-1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
		int v = dis(generator);
		int rr = v;
		myfile << rr;
		if (j < M-1) {
		myfile << " ";
		}
        }
	myfile << std::endl;
    }
}


void Graph::printFlowTxt(std::string s) {

    std::ofstream myfile;
    s += ".txt";
    myfile.open(s.c_str());

    for (int i = 0; i < ListN.size(); i++) {
        myfile << "x" << ListN[i] << " ";
    }
    myfile << std::endl;

    for (int i = 0; i < ListM.size(); i++) {
        myfile << "y" << ListM[i] << " ";
    }
    myfile << std::endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (maxflow[i]==j) {
                myfile << "x" << i << " y" << j << std::endl;
            }
        }
    }
    myfile.close();
}

void Graph::printGraphComplete(std::string s) {

    std::ofstream myfile;
    s += ".txt";
    myfile.open(s.c_str());

    for (int i = 0; i < compLeft.size(); i++) {
        myfile << "x" << compLeft[i] << " ";
    }
    myfile << std::endl;
    for (int i = 0; i < compRight.size(); i++) {
        myfile << "y" << compRight[i] << " ";
    }
    myfile << std::endl;

    for (int i = 0; i < ListN.size(); i++) {
        myfile << "x" << ListN[i] << " ";
    }
    myfile << std::endl;

    for (int i = 0; i < ListM.size(); i++) {
        myfile << "y" << ListM[i] << " ";
    }
    myfile << std::endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (existsEdge(i,j)) {
                myfile << "x" << i << " y" << j;
                if(maxflow[i] == j) {
                myfile << " 1" ;
                } else {
                    myfile << " 0";
                }
                myfile << std::endl;
            }
        }
    }
    myfile.close();
}

void Graph::deletePNodes(int p) {
    
    buffer.clear();
    for (int i = 0; i < M; i++) {
        buffer.push_back(i);
    }
    permutation(0);

    for (int i = 0; i < p; i++) {
        int randNode =  buffer[i];
        //std::cout << randNode << std::endl;

        std::vector<std::vector<int>>::iterator it = adjListM.begin();
        for(int l = 0; l < randNode; l++) it++;

        for(int j = 0; j < adjListM[randNode].size(); j++) {
            int Nnode = adjListM[randNode][j];

            std::vector<int>::iterator iter;
            for(iter = adjListN[Nnode].begin(); iter != adjListN[Nnode].end(); ++iter) {
                if(*iter == randNode) {
                    adjListN[Nnode].erase(iter);
                    break;
                }
            }

            adjListM[randNode][j]=-1;
        }

    
    }

}


void Graph::insertRightEdges(int x, std::vector<int> *neighbours){
    for(int k = 0; k < adjListN[x].size(); k++) {
        if(std::find(neighbours->begin(), neighbours->end(), adjListN[x][k]) == neighbours->end() ){
            neighbours->push_back(adjListN[x][k]);
        }
    }
}


void Graph::insertLeftEdges(std::vector<int> *left, std::vector<int> *right){

    for(int i = 0; i < right->size(); i++) {
        if(std::find(left->begin(), left->end(), getFlowNode(right->at(i))) == left->end() ) {
            left->push_back(getFlowNode(right->at(i)));
        }
    }

}

int Graph::getFlowNode(int x) {
    for(int i = 0; i < maxflow.size(); i++) {
        if(maxflow[i] == x) {
            return i;
        }
    }
}


int Graph::getCompactor() {
    std::vector<int> compactorRight;
    std::vector<int> compactorLeft;
    for(int i = 0; i < maxflow.size(); i++) {
        if(maxflow[i] == -1) {
            compactorLeft.push_back(i);
            insertRightEdges(i, &compactorRight);
        }
    }

    int leftSize = 0;
    while(compactorLeft.size() != leftSize) {
        leftSize = compactorLeft.size();

        insertLeftEdges(&compactorLeft, &compactorRight);
        for(int i = 0; i < compactorLeft.size(); i++) {
            insertRightEdges(compactorLeft[i], &compactorRight);
        }

    }

    compLeft = compactorLeft;
    compRight = compactorRight;

    return compactorLeft.size();
    /*for(int i = 0; i < compactorLeft.size(); i++) {
        std::cout << compactorLeft[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < compactorRight.size(); i++) {
        std::cout << compactorRight[i] << " ";
    }*/
}

double Graph::getInDegree() {
    double b = 0;
    for(int i = 0; i < adjListM.size();i++) {
            //std::cout << adjListM[i][j] << " ";
        b+= adjListM[i].size();
        //std::cout << std::endl;
    }
    return b / (double)adjListM.size();
}

double Graph::getProbability(int h, int d) {
    double inDeg = getInDegree();
    int out = getOut(), n = getN(), m = getM();
    double sPrim = (d + h - 1) * ceil(inDeg);
    int s = h * out;
    double nDegOut = n * out;
    std::cout << inDeg << " " << out << std::endl;
    double rez = 1.0;
    int k = sPrim - s + 1;
    for(int i = sPrim; i >= k; i--) {
        rez *= ( (double)i / (nDegOut - (sPrim - (double)i)) );
    }
    //std::cout << rez << std::endl;
    int nh = binomialCoeff(n,h);
    int mdh = binomialCoeff(m-d,h-1);
    return rez * nh * mdh;
}


int Graph::binomialCoeff(int n, int k)  
{  
    // Base Cases  
    if (k == 0 || k == n)  
        return 1;  
  
    // Recur  
    return binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);  
}  

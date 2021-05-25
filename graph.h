#include <vector>
#include <random>

class Graph{

    private:
        int N;
        int M;
        int out;
        std::vector<int> ListN;
        std::vector<int> ListM;
        std::vector<int> compLeft;
        std::vector<int> compRight;
        std::vector<std::vector<int>> adjListN;
        std::vector<std::vector<int>> adjListM;
        std::vector<int> maxflow;
        int nodesDegMore, nodesDegLess, DegMore, DegLess;
        std::vector<int> buffer;


    public:
        typedef std::mt19937_64 gen;
        typedef std::random_device rand;
        static gen generator;
        Graph();
        Graph (int N, int M, int out);
        void setN(int N);
        void setM(int M);
        void setOut(int out);
        int getN();
        int getM();
        int getOut();
        void makeRandomEdges(bool check);
        void calculateInDegree();
        void permutation(int n);
        void generatePermutation();
        void reserveSpace();
        bool checkGraphValidity();
        void printAdjListN();
        void printAdjListM();
        bool bpm(int u, bool seen[], int matchR[]);
        void computeMaxFlow();
        std::vector<std::vector<int>> getAdjListN();
        bool existsEdge(int u, int v);
        void printFlow();
        bool checkZeroFlow();
        void printGraphTxt(std::string s);
        void printFlowTxt(std::string s);
        void printMatrix(std::ofstream &myfile, int fieldSize);
        void printFullMatrix(std::ofstream &myfile, int N, int M, int fieldSize);
        void printGraphComplete(std::string s);
        void deletePNodes(int p);
        int getCompactor();
        void insertRightEdges(int x, std::vector<int> *neighbours);
        void insertLeftEdges(std::vector<int> *left, std::vector<int> *right);
        int getFlowNode(int x);
        double getProbability(int h, int d);
        double getInDegree();
        int binomialCoeff(int n, int k);

};

#include "Graph.hpp"
//  kkorenn1@gmail.com 209271535


namespace ariel {
void Graph::loadGraph(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty() || matrix.size() != matrix[0].size()) {
        throw std::invalid_argument("Invalid graph: The matrix is not square.");
    }

    std::unordered_set<size_t> uniqueVertices;

    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < i; j++) {  // Iterate only until `i`
            if (matrix[i][j] != matrix[j][i]) {
                throw std::invalid_argument("Invalid graph: The matrix is not symmetric.");
            }
            if (matrix[i][j] != 0)  {
                uniqueVertices.insert(i);
                uniqueVertices.insert(j);
            }
        }
        if (matrix[i][i] != 0) {
            throw std::invalid_argument("Invalid graph: Diagonal elements must be zero.");
        }
    }

    numVertices = uniqueVertices.size();
    adjMatrix = matrix;
}
void Graph::printGraph() const {
    int numEdges = 0;
    for (std::size_t i = 0; i < adjMatrix.size(); ++i) {
        for (std::size_t j = 0; j < adjMatrix.size(); ++j) {
            if (adjMatrix[i][j] != 0 && i != j) {
                numEdges++;
            }
        }
    }
    std::cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << std::endl;
}

size_t Graph::getNumVertices() const {
    return numVertices;
}

int Graph::getNumEdges() const {
    int numEdges = 0;
    for (std::size_t i = 0; i < adjMatrix.size(); ++i) {
        for (std::size_t j = 0; j < adjMatrix.size(); ++j) {
            if (adjMatrix[i][j] != 0 && i != j) {
                numEdges++;
            }
        }
    }
    return numEdges;
}

const std::vector<std::vector<int>>& Graph::getAdjMatrix() const {
    return adjMatrix;
}

void Graph::isSameSize(const Graph &g1) const {
    if (numVertices != g1.getNumVertices()) {
        throw std::invalid_argument("Graphs are not of the same size!");
    }
}

Graph operator+(const Graph &toAdd , const Graph &toAdd2) {
    toAdd2.isSameSize(toAdd);
    const auto& mat1 = toAdd.getAdjMatrix();
    const auto& mat2 = toAdd2.getAdjMatrix();
    std::vector<std::vector<int>> result(mat1.size(), std::vector<int>(mat1.size(), 0)); 
    for (int i = 0; i < mat1.size(); ++i) {
        for (int j = 0; j < mat1.size(); ++j) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
    Graph ret = Graph();
    ret.loadGraph2(result);
    return ret;
}

Graph Graph::operator+=(const Graph &toAdd){
    isSameSize(toAdd);

    for(size_t i = 0 ; i<numVertices ; i++){
        for(size_t j = 0 ; j < numVertices ; j++){
            adjMatrix[i][j] += toAdd.adjMatrix[i][j];
        }
    }
    return *this;
}

Graph Graph::operator+()const{

    return *this;
}

Graph Graph::operator-(const Graph &toAdd) const {
    isSameSize(toAdd);
    Graph result;
    std::vector<std::vector<int>> mat(this->numVertices, std::vector<int> (this->numVertices, 0));
    for (size_t i = 0; i < numVertices; ++i) {
        for (size_t j = 0; j < numVertices; ++j) {
            mat[i][j] = this->adjMatrix[i][j] - toAdd.adjMatrix[i][j];
        }
    }
    result.loadGraph(mat);
    return result;
}


Graph Graph::operator-=(const Graph &toAdd){
    isSameSize(toAdd);

    for(size_t i = 0 ; i<numVertices ; i++){
        for(size_t j = 0 ; j < numVertices ; j++){
            adjMatrix[i][j] -= toAdd.adjMatrix[i][j];
        }
    }
    // a refrence to current matrix
    return *this;
}

Graph Graph::operator-()const{
    Graph result;
    std::vector<std::vector<int>> mat(this->numVertices, std::vector<int> (this->numVertices, 0));
    for(size_t i = 0 ; i< numVertices ; i++){
        for (size_t j = 0; j < numVertices; j++)
        {
           mat[i][j] = -adjMatrix[i][j];
        }
        
    }
    result.loadGraph(mat);
    return result;
}


bool Graph::operator==(const Graph &toCompare)const{
    if(numVertices == toCompare.getNumVertices()){
        for(size_t i = 0 ; i < numVertices ; i++){
            for (size_t j = 0; j < numVertices; j++)
            {
                if(adjMatrix[i][j] != toCompare.adjMatrix[i][j]){
                  return false;
             }
         }
     }
    return true;
    }
    return false;
}

bool Graph::operator!=(const Graph &toCheck)const{
    if((*this==toCheck)){return false;}
    return true;

     }

bool Graph::operator<=(const Graph &toCheck)const{
    if(this->getNumEdges() > toCheck.getNumEdges()){
        return false;
    }
    for(size_t i = 0; i < numVertices ; i++){
        for (size_t j = 0; j < numVertices; j++)
        {
            if(adjMatrix[i][j] >= 0 && (toCheck.adjMatrix[i][j] < adjMatrix[i][j])){
                return false;
            }
        }
        
    }
    return true;
}

bool Graph::operator>=(const Graph &toCheck)const{
    if(this->getNumEdges() < toCheck.getNumEdges()){
        return false;
    }
    for(size_t i = 0; i < toCheck.getNumVertices() ; i++){
        for (size_t j = 0; j < toCheck.getNumVertices(); j++)
        {
            if(toCheck.adjMatrix[i][j] >= 0 && (toCheck.adjMatrix[i][j] > adjMatrix[i][j])){
                return false;
            }
        }
        
    }
    return true;
}

bool Graph::operator>(const Graph &toCheck) const {
    if (*this >= toCheck) {
        if (*this != toCheck) {
            return true;
        }
    }
    return false;
}

bool Graph::operator<(const Graph &toCheck) const {
    if (*this <= toCheck) {
        if (*this != toCheck) {
            return true;
        }
    }
    return false;
}


Graph Graph::operator++(){
    for(size_t i = 0 ; i<numVertices ; i ++){
        for(size_t j = 0 ; j < numVertices ; j++){
            if(adjMatrix[i][j] != 0){
                adjMatrix[i][j]++;
            }
        }
    }
    return *this;
}
Graph Graph::operator--(){
    for(size_t i = 0 ; i<numVertices ; i ++){
        for(size_t j = 0 ; j < numVertices ; j++){
            if(adjMatrix[i][j] != 0){
                adjMatrix[i][j] = adjMatrix[i][j]-1;
            }
        }
    }
    return *this;
}

Graph Graph::multByInt(int a){
    for(size_t i = 0 ; i<numVertices ; i ++){
        for(size_t j = 0 ; j < numVertices ; j++){
            if(i != j){
                adjMatrix[i][j]*=a;
            }
        }
    }
    return *this;
}

Graph operator*(const Graph &toAdd, const Graph &toAdd2){
    toAdd2.isSameSize(toAdd);  
    const auto& mat1 = toAdd.getAdjMatrix();
    const auto& mat2 = toAdd2.getAdjMatrix(); 
    std::vector<std::vector<int>> result(mat1.size(), std::vector<int>(mat1.size(), 0)); 
    for (int i = 0; i < mat1.size(); ++i) {
        for (int j = 0; j < mat1.size(); ++j) {
            for (int k = 0; k < mat1.size(); ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    Graph ret = Graph();
    ret.loadGraph2(result);
    return ret;
}

Graph Graph::operator*=(int mult){
    return this->multByInt(mult);
}

Graph Graph::operator/=(int div){
    if(div != 0){
        for(size_t i = 0 ; i<numVertices ; i ++){
            for(size_t j = 0 ; j < numVertices ; j++){
                if(i != j){
                    adjMatrix[i][j] = adjMatrix[i][j]/div;
                }
            }
        }
    }
    return *this;
}

//used the Web for this use of ostream&
std::ostream& operator<<(std::ostream& os, const Graph& graph) {
        const auto& adjMatrix = graph.getAdjMatrix();
        os << "[";
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            os << "[";
            for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
                os << adjMatrix[i][j];
                if (j != adjMatrix[i].size() - 1) {
                    os << ", ";
                }
            }
            os << "]";
            if (i != adjMatrix.size() - 1) {
                os << ", ";
            }
        }
        os << "]\n";
        return os;

}

// a function to load a graph that isnt adjoint matrix
void Graph::loadGraph2(const std::vector<std::vector<int>>& matrix) {
    
    numVertices = (matrix.size());
    adjMatrix = matrix;
}


        






} // namespace ariel
#include "cost.cpp"
#include <stdio.h>
#include <random>
#include <algorithm>
#include <set>

using namespace std;

const int dim = 12;

uniform_int_distribution<> rndInt(0,dim-1);
uniform_real_distribution<double> dis(0.0, 1.0);

int main(int argc, char* argv[]){
  mt19937 eng(stof(argv[1]));
  bool loadflag = stoi(argv[2]);
  vector<vector<int> > mat(dim);
  for (int i = 0; i < dim; i++){
    mat[i].resize(dim);
    for (int j = 0; j <= i; j++){
      if(i==j) mat[i][i] = 0;
      else{
        int bin;
        if(dis(eng) <1.0) bin =1;
        else bin =0;
        mat[i][j] = bin;
        mat[j][i] = bin;
      }
    }
  }
  auto mat_best = mat;
  double cost_best = 0.0;
  
 


  ///////////////////
  // Maximization  //
  ///////////////////

  for (int i = 0; i < dim; i++){
    mat[i].resize(dim);
    for (int j = 0; j <= i; j++){
      if(i==j) mat[i][i] = 0;
      else{
        int bin;
        if(dis(eng) <0.3) bin =1;
        else bin =0;
        mat[i][j] = bin;
        mat[j][i] = bin;
      }
    }
  }

  //////////////////
  // Load matrix  //
  //////////////////
  if(loadflag){
    ifstream loadFile;
    loadFile.open("matrix_"+to_string(dim)+".txt");

    for(int i = 0; i < dim; i++){
      for(int j = 0; j < dim; j++){
        loadFile>>mat[i][j];
      }
    }
  }

  cost_best = get_cost(mat);
  mat_best = mat;


  ////////////////////////////////////////////////////////////////////////////////
  // Take a single vertex and choose best optimization with nn random neighbors //
  ////////////////////////////////////////////////////////////////////////////////

  const int nn = 11;
  vector<int> neighbor_list(dim);
  iota(neighbor_list.begin(),neighbor_list.end(), 0);

  for(int cand_iter = 0;  cand_iter < 20*dim; cand_iter++){
    assert(dim > nn);
    shuffle(neighbor_list.begin(), neighbor_list.end(),eng);
    
    
    int cand = cand_iter%dim;
    int ptr = 0;
    vector<int> neighbors_nn;
    while(neighbors_nn.size()!=nn){
      if(neighbor_list[ptr] != cand){
        neighbors_nn.push_back(neighbor_list[ptr]);
      }
      ptr++;
    }
    

    for(int pattern = 0; pattern < (1<<nn); pattern++){
      auto mat_cp = mat;
      int curr_pattern = pattern;
      for(int i = 0; i < nn;i++){
        int neighbor  = neighbors_nn[i];
        mat_cp[cand][neighbor] = (curr_pattern%2);
        mat_cp[neighbor][cand] = (curr_pattern%2);
        curr_pattern/=2;
      }
      mat_cp[cand][cand]  = 0;
      double cost_curr = get_cost(mat_cp);
      
      if(cost_curr > cost_best){
        cost_best = cost_curr;
        mat_best = mat_cp;
        ofstream file;
        file.open("matrix_"+to_string(dim)+".txt");
        for(int i = 0; i < dim; i++){
          for(int j = 0; j < dim; j++){
            file<<mat_cp[i][j]<<" ";
          }
          file<<endl;
        }
        file.close();
        cout<<cost_curr<<endl;
      }
    }
    mat = mat_best;
  }

  return 0;
}
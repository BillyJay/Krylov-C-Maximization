#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <random>
#include <complex>
#include <math.h> 
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>
#include <gsl/gsl_sf_trig.h>
#include <gsl/gsl_sf_exp.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

using namespace std;



void dfs(vector<bool> &visited, vector<vector<int> > &mat, int node){
  visited[node] = true;
  for(int i = 0; i < mat.size(); i++){
    if(node == i) continue;
    if(mat[node][i]==1 && !visited[i]){
      dfs(visited, mat, i);
    }
  }
  return;
}

bool is_connected(vector<vector<int> >mat){
    int dim = mat.size();
    vector<bool> visited(dim,0);
    dfs(visited, mat,0);
    int tot = 0;
    
    for(int i = 0; i < dim; i++){
      if (visited[i]) tot++;
    }
  return (tot== dim);
}


double get_cost (vector<vector<int> > mat)
{
  int dim = mat.size();
  gsl_matrix * adj = gsl_matrix_alloc (dim, dim);

  for (int i = 0; i < dim; i++){
    for (int j = 0; j < dim; j++){
        gsl_matrix_set (adj, i, j, mat[i][j]);
      }
    }


  gsl_vector *tau = gsl_vector_alloc (dim);
  gsl_linalg_hessenberg_decomp(adj, tau);

  for (int i = 0; i < dim; i++){
      for (int j = 0; j < dim; j++){
        if(abs(gsl_matrix_get (adj, i, j))<0.0001)
          gsl_matrix_set(adj,i,j,0.0);
      }
  }
  gsl_linalg_hessenberg_set_zero(adj);

  
  gsl_vector *eval = gsl_vector_alloc (dim);
  gsl_matrix *evec = gsl_matrix_alloc (dim, dim);

  gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (dim);
  gsl_eigen_symmv (adj, eval, evec, w);
  complex<double> cost = ((complex<double>) 0.0);
  for(int m = 0 ; m < dim; m++){
    gsl_vector evec_m = gsl_matrix_column (evec, m).vector;
    complex<double> fact2 = abs(gsl_vector_get(&evec_m,0));
    for(int n = 0; n < dim; n++){
      complex<double> fact1 = abs(gsl_vector_get(&evec_m,n));
      cost += fact1 * fact1 * fact2 * fact2 * ((double)n);
    }
    
  }
  gsl_eigen_symmv_free (w);
  gsl_matrix_free (adj);

  return (real(cost));
}


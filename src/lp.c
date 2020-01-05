/*

Copyright (c) 2019-2020, Adrien BLASSIAU

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted, provided
that the above copyright notice and this permission notice appear
in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

#include "include.h"
#include "graph.h"
#include "lp.h"
#include "tools.h"

int run_lp(Pgraph g)
{
  int n               = get_vertices_number(g);
  int m               = get_edges_number(g);
  int** edges_list    = get_edges_list(g);
  int** edges_list_2  = get_edges_list_2(g);
  int** am            = g->adjacency_matrix;
  int   debug         = 0;

  int           i,j,k;
  int           edge_index_1;
  int           edge_index_2;
  int           x[m];
  int           y1[m][n];
  int           y2[m][n];
  int           z[n];
  int           count;
  int           a,b;
  int           ret;

  /* declare variables */
  glp_prob      *lp;
  glp_iocp      parm;

  int           ind[m+2*m*n+n+1];
  double        val[m+2*m*n+n+1];
  char          colName[256];
  char          rowName[256];



  /* create problem object */
  lp = glp_create_prob();

  /* set problem name */
  glp_set_prob_name(lp, "MBV");

  /* assign objective function name */
  glp_set_obj_name(lp, "obj");

  /* set optimization direction */
  glp_set_obj_dir(lp, GLP_MIN);

  /* add columns to problem object */
  glp_add_cols(lp, m+2*m*n+n);

  /*x[i][j]*/
  for(i = 1; i<=m; i++){
    a = edges_list[i-1][0];
    b = edges_list[i-1][1];
    sprintf(colName, "x_[%1d][%1d]",a,b);
    // set column name
    glp_set_col_name(lp, i, colName);
    // set column kind
    glp_set_col_kind(lp, i, GLP_BV);
  }

  /*y[i][j]*/
  for(i = 1; i<=m; i++){
    for(j = 1; j<=n; j++){
      a = edges_list[i-1][0];
      b = edges_list[i-1][1];
      sprintf(colName, "y_[%1d][%1d][%1d]",a,b,j-1);
      // set column name
      glp_set_col_name(lp, m+i+m*(j-1), colName);
      // set column kind
      glp_set_col_kind(lp, m+i+m*(j-1), GLP_BV);
      // set column name
      glp_set_col_name(lp, m+i+m*(j-1), colName);
    }
  }

  /*y[j][i]*/
  for(i = 1; i<=m; i++){
    for(j = 1; j<=n; j++){
      a = edges_list_2[i-1][0];
      b = edges_list_2[i-1][1];
      sprintf(colName, "y_[%1d][%1d][%1d]",a,b,j-1);
      // set column name
      glp_set_col_name(lp, m+m*n+i+m*(j-1), colName);
      // set column kind
      glp_set_col_kind(lp, m+m*n+i+m*(j-1), GLP_BV);
    }
  }

  /*z[i]*/
  for(i = 1; i<=n; i++){
    sprintf(colName, "z_[%1d]",i);
      // set column name
    glp_set_col_name(lp, m+2*m*n+i, colName);
      // set column kind
    glp_set_col_kind(lp, m+2*m*n+i, GLP_IV);
    glp_set_col_bnds(lp, m+2*m*n+i, GLP_DB, 0., 10.);
      // set objective coefficient
    glp_set_obj_coef(lp, m+2*m*n+i, 1.);
  }

  /* FIRST CONSTRAINT TYPE*/
  // add rows to problem object
  glp_add_rows(lp, 1);
  // set row name
  glp_set_row_name(lp, 1, "c1");
  // set row bounds
  glp_set_row_bnds(lp, 1, GLP_FX, n-1, n-1);
  //sum{i,j in V} x[i][j] == n-1;
  for(i = 1; i<=m; i++){
    ind[i] = i;
    val[i] = 1.;
  }
  glp_set_mat_row(lp, 1, m, ind, val);

  /* SECOND CONSTRAINT TYPE*/
  // add rows to problem object
  glp_add_rows(lp, n*m);
  for(i = 1; i<=m; i++){
    a = edges_list[i-1][0];
    b = edges_list[i-1][1];
    for(j = 1; j<=n; j++){
      sprintf(rowName, "c2_[%1d][%1d][%1d]",a,b,j-1);
      // set row name
      glp_set_row_name(lp, 1+i+m*(j-1),rowName);
      // set row bounds
      glp_set_row_bnds(lp, 1+i+m*(j-1), GLP_FX, 0, 0);
      // y[i][j][k] + y[j][i][k] - x[i][j] == 0;
      ind[1] = m+i+m*(j-1);
      val[1] = 1.;
      ind[2] = m+m*n+i+m*(j-1);
      val[2] = 1.;
      ind[3] = i;
      val[3] = -1.;
      glp_set_mat_row(lp, 1+i+m*(j-1), 3, ind, val);
    }
  }

  /* THIRD CONSTRAINT TYPE*/
  // add rows to problem object
  glp_add_rows(lp, m);

  for(i = 1; i<=m; i++){
    a = edges_list[i-1][0];
    b = edges_list[i-1][1];

    sprintf(rowName, "c3_[%1d][%1d]",a,b);
    glp_set_row_name(lp, 1+n*m+i,rowName);
    glp_set_row_bnds(lp, 1+n*m+i, GLP_FX, 1, 1);

    count = 1;
    for(k = 0; k<n; k++){
      edge_index_1 = get_edges_ind(edges_list,a,k,m);
      edge_index_2 = get_edges_ind(edges_list_2,a,k,m);
      if (k!=a && k!=b && edge_index_1 != -1){
        ind[count] = m+(edge_index_1+1)+m*(b);
        val[count] = 1.;
        count++;
      }
      else if(k!=a && k!=b && edge_index_2 != -1){
        ind[count] = m+m*n+(edge_index_2+1)+m*(b);
        val[count] = 1.;
        count++;
      }
    }
    ind[count] = i;
    val[count] = 1.;
    glp_set_mat_row(lp, 1+n*m+i, count, ind, val);
  }

  /* FOURTH CONSTRAINT TYPE*/
  // add rows to problem object
  glp_add_rows(lp, n);

  for(i = 1; i<=n; i++){
    sprintf(rowName, "c4_[%1d]",i-1);

    glp_set_row_name(lp,1+n*m+m+i,rowName);
    glp_set_row_bnds(lp,1+n*m+m+i, GLP_UP, 0., 2);

    count = 1;
    for(j = 1; j<=n; j++){
      if (am[i-1][j-1] != -1){

        edge_index_1 = get_edges_ind(edges_list,i-1,j-1,m);
        edge_index_2 = get_edges_ind(edges_list_2,i-1,j-1,m);

        if (edge_index_1 != -1){
          ind[count] = edge_index_1+1;
          val[count] = 1.;
          count++;

        }
        else if (edge_index_2 != -1){
          ind[count] = edge_index_2+1;
          val[count] = 1.;
          count++;
        }
      }
    }

    ind[count] = m+2*m*n+i;
    val[count] = -get_vertex_degree(g,i-1);
    glp_set_mat_row(lp, 1+n*m+m+i, count, ind, val);
  }

  glp_write_lp(lp, NULL, "BigTEST.lp");

  // initialize integer optimizer parameters
  glp_init_iocp(&parm);
  parm.presolve = GLP_ON;
  // solve MIP
  glp_intopt(lp, &parm);
  // determine status of MIP solution
  ret = glp_mip_status(lp);
  switch (ret) {
  case GLP_OPT:
    printf("Success\n");
    break;
    default:
    printf("Failed\n");
      // delete problem
    glp_delete_prob(lp);
    return 1;
  }

  for(i=1; i<=m; i++){
    x[i-1] = glp_mip_col_val(lp, i);
  }

  for(i=1; i<=n; i++){
    z[i-1] = glp_mip_col_val(lp, m+2*m*n+i);
  }

  for(i=1; i<=m; i++){
    for(j=1; j<=n; j++){
      y1[i-1][j-1] = glp_mip_col_val(lp, m+i+m*(j-1));
      y2[i-1][j-1] = glp_mip_col_val(lp, m+m*n+i+m*(j-1));
    }
  }

  // delete problem
  glp_delete_prob(lp);

  // // output the solution
  if (debug){
    printf("%7s %3s  %6s %9s %9s %6s\n","i","j","x[i]", "y[i][j]", "y[i][j]", "z[j]");
    for(i = 0; i < m; i++){
      a = edges_list[i][0];
      b = edges_list[i][1];
      for(j = 0; j < n; j++){
        printf("%3d %3d %3d: %6d %9d %9d %6d\n",a,b,j, x[i], y1[i][j], y2[i][j],z[j]);
      }
    }
  }

  // // output the solution
  // printf("%7s %4s\n","i","x[i]");
  // for(i = 0; i < m; i++){
  //   a = edges_list[i][0];
  //   b = edges_list[i][1];
  //   printf("%3d %3d:%4d\n",a,b,x[i]);
  // }

  // int res[n][n];

  // for(i=0; i<n; i++){
  //   for(j=0; j<n; j++){
  //     res[i][j] = 0;
  //   }
  // }
  // for (i = 0; i < m; ++i){
  //   if(x[i]!=0){
  //     a = edges_list[i][0];
  //     b = edges_list[i][1];
  //     res[a][b] = 1;
  //     res[b][a] = 1;
  //   }
  // }

  int result = 0;

  for (i = 0; i < n; i++){
    if (z[i] !=0){
      result+=z[i];
    }
  }

  // Pgraph gresult = new_graph(n);
  // fill_graph(gresult,res,0);
  // print_graph(gresult,0);
  // printf("RESULTAT : %d\n",result);

  // free_graph(gresult);
  // free_matrix(edges_list,m);
  // free_matrix(edges_list_2,m);
  return result;
}
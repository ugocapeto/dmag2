#include "header.h"
#include "proto.h"

void disparityAW(
 int width,
 int height,
 int *img1_arr,
 int *img2_arr,
 int *disp1_arr,
 int *disp2_arr,
 int min_d,
 int max_d,
 int radius,
 double gamma_p,
 double gamma_c,
 double max_cost_col,
 double max_cost_grad,
 double alpha
)

{

 double dist_dbl;
 int i;
 int j;
 int ind;
 int dist_c_siz;
 double *dist_c;
 int dist_c_ind;
 int dist_p_siz;
 double *dist_p;
 int dist_p_ind;
 double **cost_volume_arr;
 int d;
 int dim;
 int nd;
 double *E1_arr;
 double *E2_arr;
 double *W1;
 double *W2;
 double **weights2;
 int i_inp;
 int j_inp;
 int i_offset;
 int j_offset;
 int j1_inp;
 int j2_inp;
 double E;
 int task_increment;
 int task_counter;
 double val;
 double val2;

 /*
 Tabulate color similarity strengths dist_c
 (array of size 3*255+1)
 */

 dist_c_siz= 3*255+1;
 dist_c= (double *)calloc(dist_c_siz,sizeof(double));

 for ( dist_c_ind= 0 ;
       dist_c_ind< dist_c_siz ;
       dist_c_ind++ ) {
    dist_dbl= (double)dist_c_ind;
    dist_dbl/= 3;
    dist_c[dist_c_ind]= exp(-dist_dbl/gamma_c);
 }

 /*
 Tabulate proximity strengths dist_p
 (array of size (2*radius+1)^2)
 */

 dist_p_siz= (2*radius+1)*(2*radius+1);
 dist_p= (double *)calloc(dist_p_siz,sizeof(double));

 dist_p_ind= 0;
 for ( i= -radius ; i<= +radius ; i++ ) {
    for ( j= -radius ; j<= +radius ; j++ ) {
       dist_dbl= (double)(i*i+j*j);
       dist_dbl= sqrt(dist_dbl);
       dist_p[dist_p_ind]= exp(-2*dist_dbl/gamma_p);
       dist_p_ind++;
    }
 }

 /*
 Allocate memory for the cost volume
 */

 cost_volume_arr= (double **)calloc(max_d-min_d+1,sizeof(double *));
 for ( d= min_d ; d<= max_d ; d++ ) {
    cost_volume_arr[d-min_d]= (double *)calloc(width*height,sizeof(double));
 }

 /*
 Compute the raw cost volume
 */

 costVolume(
  width,
  height,
  img1_arr,
  img2_arr,
  min_d,
  max_d,
  radius,
  gamma_p,
  gamma_c,
  max_cost_col,
  max_cost_grad,
  alpha,
  cost_volume_arr
 );

 dim= 2*radius+1;
 nd= max_d-min_d+1;

 /*
 Allocate memory for E1_arr
 (dissimilarity 1->2)
 */

 E1_arr= (double *)calloc(width*height,sizeof(double));

 for ( ind= 0 ; ind< width*height ; ind++ ) {
    E1_arr[ind]= 1.0e32;
 }

 /*
 Allocate memory for E2_arr
 (dissimilarity 2->1)
 */

 E2_arr= (double *)calloc(width*height,sizeof(double));

 for ( ind= 0 ; ind< width*height ; ind++ ) {
    E2_arr[ind]= 1.0e32;
 }

 /*
 Initialize disp1_arr
 */

 for ( ind= 0 ; ind< width*height ; ind++ ) {
    disp1_arr[ind]= min_d;
 }

 /*
 Initialize disp2_arr
 */

 for ( ind= 0 ; ind< width*height ; ind++ ) {
    disp2_arr[ind]=-min_d;
 }

 task_increment= 10;
 task_counter= task_increment;

 for ( i= 0 ; i< height ; i++ ) {

    /*
    Create support weight window in image 1
    */

    W1= (double *)calloc(dim*dim,sizeof(double));

    /*
    Create array of support weight windows in image 2
    */

    weights2= (double **)calloc(nd,sizeof(double *));

    for ( d= max_d ; d>= min_d ; d-- ) {

       /*
       Create support weight window in image 2
       for disparity d
       */

       weights2[max_d-d]= (double *)calloc(dim*dim,sizeof(double));

       if ( d > min_d ) { /* we'll take care of min_d later */

          /*
          Compute support weight window for image 2
          */

          i_inp= i;
          j_inp= 0-d;
          support(
           width,
           height,
           img2_arr,
           i_inp,
           j_inp,
           radius,
           dist_c,
           weights2[max_d-d]
          );
       }
    }

    for ( j= 0 ; j< width ; j++ ) {

       /*
       Compute support weight window for image 1
       */

       i_inp= i;
       j_inp= j;
       support(
        width,
        height,
        img1_arr,
        i_inp,
        j_inp,
        radius,
        dist_c,
        W1
       );

       /*
       Compute support weight window for image 2
       at disparity min_d
       */

       i_inp= i;
       j_inp= j-min_d;
       support(
        width,
        height,
        img2_arr,
        i_inp,
        j_inp,
        radius,
        dist_c,
        weights2[(j+max_d-min_d)%nd]
       );

       for ( d= max_d ; d>= min_d ; d-- ) {
          if ( 0<=j-d && j-d<width ) {

             /*
             Create support weight window in image 2
             */

             W2= (double *)calloc(dim*dim,sizeof(double));

             /* 
             Get the support weight window in image 2
             */

             for ( i_offset= -radius ; i_offset<= +radius ; i_offset++ ) {
                for ( j_offset= -radius ; j_offset<= +radius ; j_offset++ ) {
                   ind= (i_offset+radius)*(2*radius+1)+j_offset+radius;
                   W2[ind]= weights2[(j-d+max_d)%nd][ind];
                }
             }

             /*
             Compute the weighted cost
             */

             i_inp= i;
             j1_inp= j;
             j2_inp= j-d;
             E= costCombined(
              width,
              height,
              radius,
              i_inp,
              j1_inp,
              j2_inp,
              W1,
              W2,
              dist_p,
              cost_volume_arr[d-min_d]
             );

             if ( E < E1_arr[i*width+j] ) {
                E1_arr[i*width+j]= E;
                disp1_arr[i*width+j]= d;
             }
             if ( E < E2_arr[i*width+j-d] ) {
                E2_arr[i*width+j-d]= E;
                disp2_arr[i*width+j-d]= -d;
             }

             /*
             Free W2
             */

             free(W2);
          }
       }
    }

    /*
    Free W1
    */

    free(W1);

    /*
    Free weights2
    */

    for ( d= min_d ; d<= max_d ; d++ ) {
       free(weights2[d-min_d]);
    }

    free(weights2);

    /*
    Progress report
    */

    val= (double)(i+1)/(double)height;
    val2= (double)task_counter/100;
    if ( val >= val2 ) {
       fprintf(stdout,"%d%% done\n",task_counter);
       task_counter+= task_increment;
    }
 }

 /*
 Free dist_c
 */

 free(dist_c);

 /*
 Free dist_p
 */

 free(dist_p);

 /*
 Free cost_volume_arr
 */

 for ( d= min_d ; d<= max_d ; d++ ) {
    free(cost_volume_arr[d-min_d]);
 }

 free(cost_volume_arr);

 /*
 Free E1_arr
 */

 free(E1_arr);

 /*
 Free E2_arr 
 */

 free(E2_arr);

}

#include <cblas.h>
#include <math.h>
/*
void matmult_nat(int m, int n, int k, double **A, double **B, double **C) {
    int i, j, h;
    double tmp;

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            tmp = 0;
            for(h = 0; h < k; h++){
                tmp += A[i][h] * B[h][j];
            }
            C[i][j] = tmp;
        }
    }
} */

void matmult_nat(int m, int n, int k, double **restrict A, double **restrict B, double **restrict C) {
    int i, j, h;

    for(j = 0; j < n; j++){
        for(i = 0; i < m; i++){
            C[i][j] = 0;
        }
    }

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            for(h = 0; h < k; h++){
                C[i][j] += A[i][h] * B[h][j];
            }
        }
    }
}

void matmult_lib(int m, int n, int k, double **A, double **B, double **C) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1, *A, k, *B, n, 0, *C, n);
}

void matmult_mnk(int m, int n, int k, double **restrict A, double **restrict B, double **restrict C) {
    int i, j, h;
    double tmp;

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            tmp = 0;
            for(h = 0; h < k; h++){
                tmp += A[i][h] * B[h][j];
            }
            C[i][j] = tmp;
        }
    }
}


void matmult_nmk(int m, int n, int k, double **restrict A, double **restrict B, double **restrict C) {
    int i, j, h;
    double tmp;

    for(j = 0; j < n; j++){
        for(i = 0; i < m; i++){
            tmp = 0;
            for(h = 0; h < k; h++){
                tmp += A[i][h] * B[h][j];
            }
            C[i][j] = tmp;
        }
    }
}

void matmult_knm(int m, int n, int k, double **restrict A, double **restrict B, double **restrict C) {
    int i, j, h;

    for(j = 0; j < n; j++){
        for(i = 0; i < m; i++){
            C[i][j] = 0;
        }
    }

    for(h = 0; h < k; h++){
        for(j = 0; j < n; j++){
            for(i = 0; i < m; i++){
                C[i][j] += A[i][h] * B[h][j];
            }
        }
    }
}

void matmult_kmn(int m, int n, int k, double **restrict A, double **restrict B, double **restrict C) {
    int i, j, h;

    for(j = 0; j < n; j++){
        for(i = 0; i < m; i++){
            C[i][j] = 0;
        }
    }
    
    for(h = 0; h < k; h++){
        for(i = 0; i < m; i++){
            for(j = 0; j < n; j++){
                C[i][j] += A[i][h] * B[h][j];
            }
        }
    }
}

void matmult_mkn(int m, int n, int k, double **restrict A, double **restrict B, double **restrict C) {
    int i, j, h;

    for(j = 0; j < n; j++){
        for(i = 0; i < m; i++){
            C[i][j] = 0;
        }
    }
    
    for(i = 0; i < m; i++){
        for(h = 0; h < k; h++){
            for(j = 0; j < n; j++){
                C[i][j] += A[i][h] * B[h][j];
            }
        }
    }
}

void matmult_nkm(int m, int n, int k, double **restrict A, double **restrict B, double **restrict C) {
    int i, j, h;

    for(j = 0; j < n; j++){
        for(i = 0; i < m; i++){
            C[i][j] = 0;
        }
    }
    
    for(j = 0; j < n; j++){
        for(h = 0; h < k; h++){
            for(i = 0; i < m; i++){
                C[i][j] += A[i][h] * B[h][j];
            }
        }
    }
}

void matmult_blk(int m, int n, int k, double **restrict A, double **restrict B, double **restrict C, int blk) {
    int i, j, h, x, y;

    for(j = 0; j < n; j++){
        for(i = 0; i < m; i++){
            C[i][j] = 0;
        }
    }
    
    int blkAm, blkk, blkBn;
    int itersm = 1 + (m / blk), itersn = 1 + (n / blk), itersk = 1 + (k / blk);
    int blki, blkj, blkh;
    int superi, superj, superh;

    // i er m og j er n - mos 2020
    int q1, q2, q3;
    // loop over blocks
    for(blki = 0; blki < m; blki+=blk){
        for(blkh = 0; blkh < k; blkh+=blk){
            for(blkj = 0; blkj < n; blkj+=blk){
                // blki = blkAm*blk;
                // blkj = blkBn*blk;
                // blkh = blkk*blk;

                // loop over block
                q1 = fmin(blk,m-blki);
                q2 = fmin(blk,k-blkh);
                q3 = fmin(blk,n-blkj);
                for(i = 0; i < q1; i++){
                    // superi = i + blki;
                    for(h = 0; h < q2; h++){
                        // superh = h + blkh;
                        for(j = 0; j < q3; j++){
                            // superj = j + blkj;
                            // C[superi][superj] += A[superi][h + blkh] * B[h+blkh][superj];
                            // C[i + blki][superj] += A[i + blki][superh] * B[superh][superj];
                            C[i + blki][j + blkj] += A[i + blki][h + blkh] * B[h + blkh][j + blkj];
                        }
                    }
                }
            }
        }
    }
    /*
    int cleanj = itersn * blk, cleani = itersm * blk, cleanh = itersk * blk;

    for(j = cleanj; j < n; j++){ // clean-up
        for(i = cleani; i < m; i++){
            for(h = cleanh; h < k; h++){
                C[i][j] += A[i][h] * B[h][j];
            }
        }
    }
    */
}
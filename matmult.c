#include <cblas.h>


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
}

void matmult_lib(int m, int n, int k, double **A, double **B, double **C) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1, *A, k, *B, n, 0, *C, n);
}

void matmult_mnk(int m, int n, int k, double **A, double **B, double **C) {
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


void matmult_nmk(int m, int n, int k, double **A, double **B, double **C) {
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

void matmult_knm(int m, int n, int k, double **A, double **B, double **C) {
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

void matmult_kmn(int m, int n, int k, double **A, double **B, double **C) {
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

void matmult_mkn(int m, int n, int k, double **A, double **B, double **C) {
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

void matmult_nkm(int m, int n, int k, double **A, double **B, double **C) {
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

void matmult_blk(int m, int n, int k, double **A, double **B, double **C, int blk) {
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

    for(blkk = 0; blkk < itersk; blkk++){ // loop over blocks
        for(blkAm = 0; blkAm < itersm; blkAm++){
            for(blkBn = 0; blkBn < itersn; blkBn++){
                blki = blkAm*blk;
                blkj = blkBn*blk;
                blkh = blkk*blk;

                for(h = 0; (h < blk && h + blkh < k); h++){
                    superh = h + blkh;
                    for(i = 0; (i < blk && i + blki < m); i++){
                        superi = i + blki;
                        for(j = 0; (j < blk && j + blkj < n); j++){ // loop over block
                            // superj = j + blkj;
                            // C[superi][superj] += A[superi][h + blkh] * B[h+blkh][superj];
                            // C[i + blki][superj] += A[i + blki][superh] * B[superh][superj];
                            C[superi][j + blkj] += A[superi][superh] * B[superh][j + blkj];
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
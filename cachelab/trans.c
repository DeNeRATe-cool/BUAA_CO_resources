/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Your transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * The transpose function is evaluated by counting the number of misses
 * on a 512B direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */

void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    /*
     * Please define your local variables here. 
     * You are allowed to define at most 12 local variables.
    */
    int i, j, x, y;
    int e0, e1, e2, e3, e4, e5, e6, e7;
    
    if(M == 16) { //16x16 matrix
       for(i = 0; i < 16; i += 8) {
            for(j = 0; j < 16; j += 8) {
                // diag：11 * 4
                for(x = i; x < i + 4; x++) {
                    e0 = A[x][j];
                    e1 = A[x][j + 1];
                    e2 = A[x][j + 2];
                    e3 = A[x][j + 3];
                    e4 = A[x][j + 4];
                    e5 = A[x][j + 5];
                    e6 = A[x][j + 6];
                    e7 = A[x][j + 7];

                    B[j][x] = e0;
                    B[j + 1][x] = e1;
                    B[j + 2][x] = e2;
                    B[j + 3][x] = e3;
                    B[j][x + 4] = e4;
                    B[j + 1][x + 4] = e5;
                    B[j + 2][x + 4] = e6;
                    B[j + 3][x + 4] = e7;
                }

                // diag: 15 * 4
                for(x = j; x < j + 4; x++) {
                    e0 = A[i + 4][x];
                    e1 = A[i + 5][x];
                    e2 = A[i + 6][x];
                    e3 = A[i + 7][x];
                    e4 = B[x][i + 4];
                    e5 = B[x][i + 5];
                    e6 = B[x][i + 6];
                    e7 = B[x][i + 7];

                    B[x][i + 4] = e0;
                    B[x][i + 5] = e1;
                    B[x][i + 6] = e2;
                    B[x][i + 7] = e3;
                    B[x + 4][i] = e4;
                    B[x + 4][i + 1] = e5;
                    B[x + 4][i + 2] = e6;
                    B[x + 4][i + 3] = e7;
                }

                // diag: 9 * 4
                for(x = i + 4; x < i + 8; x++) {
                    e0 = A[x][j + 4];
                    e1 = A[x][j + 5];
                    e2 = A[x][j + 6];
                    e3 = A[x][j + 7];
                    B[j + 4][x] = e0;
                    B[j + 5][x] = e1;
                    B[j + 6][x] = e2;
                    B[j + 7][x] = e3;
                }
            }
        }
        /**
         * for 16x16, 64(+3) misses
         */
        // for(i = 0; i < 16; i += 8) {
        //     for(j = 0; j < 16; j += 8) {
        //         if(i == j) {
        //             e0 = A[i][j];
        //             e1 = A[i][j + 1];
        //             e2 = A[i][j + 2];
        //             e3 = A[i][j + 3];
        //             e4 = A[i][j + 4];
        //             e5 = A[i][j + 5];
        //             e6 = A[i][j + 6];
        //             e7 = A[i][j + 7];

        //             for(x = i + 1; x < i + 8; x++) {
        //                 B[x - 1][j] = e0;
        //                 B[x - 1][j + 1] = e1;
        //                 B[x - 1][j + 2] = e2;
        //                 B[x - 1][j + 3] = e3;
        //                 B[x - 1][j + 4] = e4;
        //                 B[x - 1][j + 5] = e5;
        //                 B[x - 1][j + 6] = e6;
        //                 B[x - 1][j + 7] = e7;

        //                 e0 = A[x][j];
        //                 e1 = A[x][j + 1];
        //                 e2 = A[x][j + 2];
        //                 e3 = A[x][j + 3];
        //                 e4 = A[x][j + 4];
        //                 e5 = A[x][j + 5];
        //                 e6 = A[x][j + 6];
        //                 e7 = A[x][j + 7];
        //             }

        //             B[i + 7][j] = e0;
        //             B[i + 7][j + 1] = e1;
        //             B[i + 7][j + 2] = e2;
        //             B[i + 7][j + 3] = e3;
        //             B[i + 7][j + 4] = e4;
        //             B[i + 7][j + 5] = e5;
        //             B[i + 7][j + 6] = e6;
        //             B[i + 7][j + 7] = e7;

        //             x = B[i][j + 1]; B[i][j + 1] = B[j + 1][i]; B[j + 1][i] = x;
        //             x = B[i][j + 2]; B[i][j + 2] = B[j + 2][i]; B[j + 2][i] = x;
        //             x = B[i][j + 3]; B[i][j + 3] = B[j + 3][i]; B[j + 3][i] = x;
        //             x = B[i][j + 4]; B[i][j + 4] = B[j + 4][i]; B[j + 4][i] = x;
        //             x = B[i][j + 5]; B[i][j + 5] = B[j + 5][i]; B[j + 5][i] = x;
        //             x = B[i][j + 6]; B[i][j + 6] = B[j + 6][i]; B[j + 6][i] = x;
        //             x = B[i][j + 7]; B[i][j + 7] = B[j + 7][i]; B[j + 7][i] = x;

        //             x = B[i + 1][j + 2]; B[i + 1][j + 2] = B[j + 2][i + 1]; B[j + 2][i + 1] = x;
        //             x = B[i + 1][j + 3]; B[i + 1][j + 3] = B[j + 3][i + 1]; B[j + 3][i + 1] = x;
        //             x = B[i + 1][j + 4]; B[i + 1][j + 4] = B[j + 4][i + 1]; B[j + 4][i + 1] = x;
        //             x = B[i + 1][j + 5]; B[i + 1][j + 5] = B[j + 5][i + 1]; B[j + 5][i + 1] = x;
        //             x = B[i + 1][j + 6]; B[i + 1][j + 6] = B[j + 6][i + 1]; B[j + 6][i + 1] = x;
        //             x = B[i + 1][j + 7]; B[i + 1][j + 7] = B[j + 7][i + 1]; B[j + 7][i + 1] = x;

        //             x = B[i + 2][j + 3]; B[i + 2][j + 3] = B[j + 3][i + 2]; B[j + 3][i + 2] = x;
        //             x = B[i + 2][j + 4]; B[i + 2][j + 4] = B[j + 4][i + 2]; B[j + 4][i + 2] = x;
        //             x = B[i + 2][j + 5]; B[i + 2][j + 5] = B[j + 5][i + 2]; B[j + 5][i + 2] = x;
        //             x = B[i + 2][j + 6]; B[i + 2][j + 6] = B[j + 6][i + 2]; B[j + 6][i + 2] = x;
        //             x = B[i + 2][j + 7]; B[i + 2][j + 7] = B[j + 7][i + 2]; B[j + 7][i + 2] = x;

        //             x = B[i + 3][j + 4]; B[i + 3][j + 4] = B[j + 4][i + 3]; B[j + 4][i + 3] = x;
        //             x = B[i + 3][j + 5]; B[i + 3][j + 5] = B[j + 5][i + 3]; B[j + 5][i + 3] = x;
        //             x = B[i + 3][j + 6]; B[i + 3][j + 6] = B[j + 6][i + 3]; B[j + 6][i + 3] = x;
        //             x = B[i + 3][j + 7]; B[i + 3][j + 7] = B[j + 7][i + 3]; B[j + 7][i + 3] = x;

        //             x = B[i + 4][j + 5]; B[i + 4][j + 5] = B[j + 5][i + 4]; B[j + 5][i + 4] = x;
        //             x = B[i + 4][j + 6]; B[i + 4][j + 6] = B[j + 6][i + 4]; B[j + 6][i + 4] = x;
        //             x = B[i + 4][j + 7]; B[i + 4][j + 7] = B[j + 7][i + 4]; B[j + 7][i + 4] = x;

        //             x = B[i + 5][j + 6]; B[i + 5][j + 6] = B[j + 6][i + 5]; B[j + 6][i + 5] = x;
        //             x = B[i + 5][j + 7]; B[i + 5][j + 7] = B[j + 7][i + 5]; B[j + 7][i + 5] = x;

        //             x = B[i + 6][j + 7]; B[i + 6][j + 7] = B[j + 7][i + 6]; B[j + 7][i + 6] = x;

        //         } else {
        //             for(x = i; x < i + 8; x++)
        //                 for(y = j; y < j + 8; y++)
        //                     B[y][x] = A[x][y];
        //         }
        //     }
        // }
               
    }
    else if(M == 32) { //32x32 matrix
        /**
         * for any N and M both divided by 8
         */
        for(i = 0; i < 32; i += 8) {
            for(j = 0; j < 32; j += 8) {
                // diag：11 * 4
                for(x = i; x < i + 4; x++) {
                    e0 = A[x][j];
                    e1 = A[x][j + 1];
                    e2 = A[x][j + 2];
                    e3 = A[x][j + 3];
                    e4 = A[x][j + 4];
                    e5 = A[x][j + 5];
                    e6 = A[x][j + 6];
                    e7 = A[x][j + 7];

                    B[j][x] = e0;
                    B[j + 1][x] = e1;
                    B[j + 2][x] = e2;
                    B[j + 3][x] = e3;
                    B[j][x + 4] = e4;
                    B[j + 1][x + 4] = e5;
                    B[j + 2][x + 4] = e6;
                    B[j + 3][x + 4] = e7;
                }

                // diag: 15 * 4
                for(x = j; x < j + 4; x++) {
                    e0 = A[i + 4][x];
                    e1 = A[i + 5][x];
                    e2 = A[i + 6][x];
                    e3 = A[i + 7][x];
                    e4 = B[x][i + 4];
                    e5 = B[x][i + 5];
                    e6 = B[x][i + 6];
                    e7 = B[x][i + 7];

                    B[x][i + 4] = e0;
                    B[x][i + 5] = e1;
                    B[x][i + 6] = e2;
                    B[x][i + 7] = e3;
                    B[x + 4][i] = e4;
                    B[x + 4][i + 1] = e5;
                    B[x + 4][i + 2] = e6;
                    B[x + 4][i + 3] = e7;
                }

                // diag: 9 * 4
                for(x = i + 4; x < i + 8; x++) {
                    e0 = A[x][j + 4];
                    e1 = A[x][j + 5];
                    e2 = A[x][j + 6];
                    e3 = A[x][j + 7];
                    B[j + 4][x] = e0;
                    B[j + 5][x] = e1;
                    B[j + 6][x] = e2;
                    B[j + 7][x] = e3;
                }
            }
        }
    } else if(M == 48) { // 32x48 matrix
        // for(i = 0; i < 32; i += 8) {
        //     for(j = 0; j < 48; j += 8) {
        //         // diag：11 * 4
        //         for(x = i; x < i + 4; x++) {
        //             e0 = A[x][j];
        //             e1 = A[x][j + 1];
        //             e2 = A[x][j + 2];
        //             e3 = A[x][j + 3];
        //             e4 = A[x][j + 4];
        //             e5 = A[x][j + 5];
        //             e6 = A[x][j + 6];
        //             e7 = A[x][j + 7];

        //             B[j][x] = e0;
        //             B[j + 1][x] = e1;
        //             B[j + 2][x] = e2;
        //             B[j + 3][x] = e3;
        //             B[j][x + 4] = e4;
        //             B[j + 1][x + 4] = e5;
        //             B[j + 2][x + 4] = e6;
        //             B[j + 3][x + 4] = e7;
        //         }

        //         // diag: 15 * 4
        //         for(x = j; x < j + 4; x++) {
        //             e0 = A[i + 4][x];
        //             e1 = A[i + 5][x];
        //             e2 = A[i + 6][x];
        //             e3 = A[i + 7][x];
        //             e4 = B[x][i + 4];
        //             e5 = B[x][i + 5];
        //             e6 = B[x][i + 6];
        //             e7 = B[x][i + 7];

        //             B[x][i + 4] = e0;
        //             B[x][i + 5] = e1;
        //             B[x][i + 6] = e2;
        //             B[x][i + 7] = e3;
        //             B[x + 4][i] = e4;
        //             B[x + 4][i + 1] = e5;
        //             B[x + 4][i + 2] = e6;
        //             B[x + 4][i + 3] = e7;
        //         }

        //         // diag: 9 * 4
        //         for(x = i + 4; x < i + 8; x++) {
        //             e0 = A[x][j + 4];
        //             e1 = A[x][j + 5];
        //             e2 = A[x][j + 6];
        //             e3 = A[x][j + 7];
        //             B[j + 4][x] = e0;
        //             B[j + 5][x] = e1;
        //             B[j + 6][x] = e2;
        //             B[j + 7][x] = e3;
        //         }
        //     }
        // }

        /**
         * for violent blocking
         */
        // for(i = 0; i < N; i += 17) {
        //     for(j = 0; j < M; j += 17) {
        //         for(x = 0; x < i + 17 && x < N; x++) {
        //             for(y = 0; y < j + 17 && y < M; y++) {
        //                 B[y][x] = A[x][y];
        //             }
        //         }
        //     }
        // }

        /**
         * for violent but first copy blocking 8x8
         */
        for(i = 0; i < N / 8 * 8; i += 8)
            for(j = 0; j < M / 8 * 8; j += 8) {
                for(x = 0; x < 8; x++) {
				    e0 = A[i + x][j];
				    e1 = A[i + x][j + 1];
				    e2 = A[i + x][j + 2];
				    e3 = A[i + x][j + 3];
				    e4 = A[i + x][j + 4];
				    e5 = A[i + x][j + 5];
				    e6 = A[i + x][j + 6];
				    e7 = A[i + x][j + 7];
    
				    B[j + x][i] = e0;
				    B[j + x][i + 1] = e1;
				    B[j + x][i + 2] = e2;
				    B[j + x][i + 3] = e3;
				    B[j + x][i + 4] = e4;
				    B[j + x][i + 5] = e5;
				    B[j + x][i + 6] = e6;
				    B[j + x][i + 7] = e7;
			    }

                for(x = 0; x < 8; x++) {
                    for(y = 0; y < x; y++) {
                        e1 = B[j + x][i + y];
                        B[j + x][i + y] = B[j + y][i + x];
                        B[j + y][i + x] = e1;
                    }
                }
            }
		for (i = N / 8 * 8; i < N; ++i)
			for (j = M / 8 * 8; j < M; ++j)
			{
				e1 = A[i][j];
				B[j][i] = e1;
			}
		for (i = 0; i < N; ++i)
			for (j = M / 8 * 8; j < M; ++j)
			{
				e1 = A[i][j];
				B[j][i] = e1;
			}
		for (i = N / 8 * 8; i < N; ++i)
			for (j = 0; j < M; ++j)
			{
				e1 = A[i][j];
				B[j][i] = e1;
			}

    }
}

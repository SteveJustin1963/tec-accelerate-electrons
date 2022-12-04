#include <stdio.h>
#include <math.h>

#define N 100 // grid size
#define MAX_ITER 20000 // maximum number of iterations
#define MAX_CHARACTER 80

double phi[N+1][N+1]; // electric potential
double rho[N+1][N+1]; // charge density

int main()
{
    // Initialize the grid
    for (int i=0; i<=N; i++) {
        for (int j=0; j<=N; j++) {
            phi[i][j] = 0.0;
            rho[i][j] = 0.0;
        }
    }
 
    // Set the charge density around the electron beam ion source
    for (int i=N/4; i<=3*N/4; i++) {
        for (int j=N/4; j<=3*N/4; j++) {
            rho[i][j] = -1.0;
        }
    }
 
    // Solve the Poisson equation using the iterative method
    double error = 0.0;
    for (int iter=0; iter<MAX_ITER; iter++) {
        error = 0.0;
        for (int i=1; i<N; i++) {
            for (int j=1; j<N; j++) {
                double new_phi = (phi[i+1][j] + phi[i-1][j] + phi[i][j+1] + phi[i][j-1]) / 4.0 - (rho[i][j] / 4.0);
                error += fabs(new_phi - phi[i][j]);
                phi[i][j] = new_phi;
            }
        }
        if (error < 1.0e-6) break;
    }
 
    // Print the results
    for (int i=0; i<=N; i++) {
        for (int j=0; j<=N; j++) {
            int characterValue = (int) (phi[i][j] * MAX_CHARACTER);
            if (characterValue < 0) characterValue = 0;
            if (characterValue > MAX_CHARACTER) characterValue = MAX_CHARACTER;
            printf("%c", characterValue);
        }
        printf("\n");
    }
 
    return 0;
}

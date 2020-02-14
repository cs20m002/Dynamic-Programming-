/* Bottom Up(Tabulation) implementation of LCS */
#include <bits/stdc++.h>
using namespace std;

const char X[] = "qpqrr";
const char Y[] = "pqprqrp";
const int len1 = strlen(X);
const int len2 = strlen(Y);

int lcslength_matrix[len1+1][len2+1]; // as it is used by two functions

int max(int a, int b){
	return (a>b)?a:b;
}

/* Printing the lcs subsequence */
void lcs_print(int lcslength , int m, int n, char *lc){
	if(!lcslength){
		printf("%s\n",lc);
		return ;
	}

	else if (X[m-1] == Y[n-1] && m>=1 && n>=1){
		*(lc+lcslength-1) = X[m-1];
		lcs_print(lcslength-1, m-1, n-1, lc);
	}

	else if (lcslength_matrix[m][n-1] > lcslength_matrix[m-1][n])
		lcs_print(lcslength, m, n-1, lc);

	else if (lcslength_matrix[m][n-1] < lcslength_matrix[m-1][n])
		lcs_print(lcslength, m-1, n, lc);

	else
	{
		lcs_print(lcslength, m, n-1, lc);
		lcs_print(lcslength, m-1, n, lc);
	}
}

/* Returns length of LCS for A[0..m-1], B[0..n-1] */
int lcsdp(const char *A, const char *B, const int m, const int n){ 
	/*Fill order using RMO */

	int row = m , column=n;
	for(int i=0; i<m+1; i++){ 		// loop will run 8 times 
		for(int j=0; j<n+1; j++){   // loop will run 6 times
			if(i==0 || j==0)
				lcslength_matrix[i][j] = 0; 

			else if(A[i-1] == B[j-1])
				    lcslength_matrix[i][j] = lcslength_matrix[i-1][j-1] + 1;

			else
				lcslength_matrix[i][j] = max(lcslength_matrix[i-1][j],lcslength_matrix[i][j-1]);
		}
	}

	/* Testing Purpose */
	// for(int i=0; i<m+1; i++){ 		
	// 	for(int j=0; j<n+1; j++){
	// 			cout << lcslength_matrix[i][j] << "\t";
	// 	}
	// 	cout << "\n\n";
	// } 

	cout << "These are the following LCS :\n";
	char lc_sequence[lcslength_matrix[m][n]+1];
	lc_sequence[lcslength_matrix[m][n]] = '\0';
	lcs_print(lcslength_matrix[m][n], row, column, lc_sequence);
	return lcslength_matrix[m][n];
}


/* Driver function */
int main(){
	int len = lcsdp(X,Y,len1,len2);
	cout << "Length of LCS is " << len << "\n";
	return 0;
}
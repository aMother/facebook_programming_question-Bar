/**********************************************************
 *
 *
 *	Time Taken To Solve : 79.3 mins
 *
 *
 */

#include<stdio.h>
#include<stdlib.h>

struct elem
{
	int key;
	int i;
};

int comp_keys(const void *a, const void *b)
{
	int i1 = (*(struct elem*)a).key;
	int i2 = (*(struct elem*)b).key;
	return i1 - i2; 
}

int main(void)
{
	int T;
	scanf("%d",&T);
	if(!(T >= 1 && T <= 5))return -1; //INPUT OUT OF RANGE (IOR)
	
	while(T)
	{
		int N;
		scanf("%d",&N);
		if(!(N > 0 && N <= 1000))return -1; //IOR
		
		
		int K;
		scanf("%d",&K);
		if(!(K >= 1 && K <= N))return -1; //IOR
		

		struct elem  A[N*N]; //For List L_i, |L_i| <= N. |L_1| + |L_2| .... + |L_N| <= N^2  
		struct elem *a = A;
		int B[N];//B[i] will contain |L_i|
		int a_i;
		int j = 0;
		while(j < N)
		{
			scanf("%d",&a_i);
			if(!(a_i > 0 && a_i <= N))return -1; //ERROR: INPUT OUT OF RANGE
			B[j] = a_i;
			while(a_i)
			{
				a->i = j;
				scanf("%d",&(a->key));
				++a;
				--a_i;
			}
			++j;
		}
		
		int *b = B;
		int valid_size_A = 0;
		while(b < B + N)
		{
			valid_size_A = valid_size_A + (*b);
			++b;
		}
		
		qsort(A, valid_size_A, sizeof(struct elem), comp_keys);

		
		
		/********************************************************************************
		 *  A[0...valid_size_A - 1] contains all the members of all lists in sorted order. 
		 *	Each element of A contains a key which is equal to some element of list & 
		 *	i which stores the identifier for that list.
		 *
		 */
		
		/******************************************
		 *	The Rank K element must have :
		 *	K - 1 elements smaller than it &
		 *	N - K elements larger than it.
		 *	Also, ALL must be from different lists 
		 */
		
		int count = 0;
		int C[N];
		int *c = C;
		while( c < C + N)
		{
			*c = 0;
			++c;
		}
		int n_k = N - K;
		int k_1 = K - 1;
		int start = (valid_size_A - 1) - n_k;
		int l = 0;
		a = A + start + 1;
		while(a < A + valid_size_A)
		{
			if(!C[a->i]) ++l;
			C[a->i] = C[a->i] + 1;
			++a;
		}
		int p;
		if((p = C[A[start].i]))
		{
			C[A[start].i] = 0;
			--l;
		}
		
		a = A + start;
		while(a >= A + n_k)
		{
			if(l == n_k)
			{
				++count;
			}
			else if(l > n_k)
			{
				c = C;
				b = B;
				int delta = l - n_k;
				while((c < C + N) && (delta))
				{
					if((*c) && (((*b) - (*c)) > 0))
					{
						--delta;
					}
					++c;
					++b;
				}
				if(!delta) ++count;
				else break;
				
			}	
			C[a->i] = p + 1;
			++l;
			--a;
			if(p = C[a->i])
			{
				C[a->i] = 0;
				--l;
			}
			
		}
		printf("%d\n",count);				
		--T;
	}
	return 0;
}

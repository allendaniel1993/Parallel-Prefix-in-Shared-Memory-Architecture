/*  ALLEN_DANIEL
 *  YESA
 *  ALLENDAN
 */
#ifndef A0_HPP
#define A0_HPP

template <typename T, typename Op>
void omp_scan(int n, const T* in, T* out, Op op) {
int x;
#pragma omp parallel 
{
	x=omp_get_num_threads();
}

//Calculating parallel prefix in each processor
#pragma omp parallel for
for(int i=0;i<n;i=i+(n/x))
{
	out[i]=in[i];
	for (int j=i+1;j<i+(n/x)&&j<n;j++)
	{
		out[j]=op(in[j],out[j-1]);
	}	
}

//Calculating the last term sequentially
for(int i=2*(n/x)-1;i<n;i=i+(n/x))
{
	out[i]=op(out[i],out[i-(n/x)]);
}

//Calculating the remaining terms
#pragma omp parallel for
for (int i=(n/x)-1;i<n;i=i+n/x)
{
	for (int j=i+1;j<(i+n/x)&&j<n;j++)
	{
		out[j]=op(out[j],out[i]);
	}
}
} // omp_scan

#endif // A0_HPP

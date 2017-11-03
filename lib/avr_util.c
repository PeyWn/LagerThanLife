/*
*
*       UTILITY FUNCTIONS 
*
*/

/*
Generate array of size 8 with 1/0 for every bit in the binary representation of
the number n.

n - number to convert to binary
ar - array to save "bits" (integer of value 1/0) in
*/
void get_8bits(int n, int ar[]){
    for(int i = 0; i < 8; i++){
        ar[i] = (n >> i) & 1;
    }
}

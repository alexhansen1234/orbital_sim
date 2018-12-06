#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define max(x, y) ((x > y) ? x : y )

uint64_t generate_pub_key(uint64_t, uint64_t, uint64_t);
uint64_t generate_random_prime(uint64_t);
uint64_t generate_random_coprime(uint64_t);
uint64_t gcd(uint64_t, uint64_t);
void generate_keys(uint64_t *, uint64_t *, uint64_t *);
void encrypt(char * message, uint64_t * digest, uint64_t pub_key, uint64_t mod);
void decrypt(char * message, uint64_t * digest, uint64_t priv_key, uint64_t mod);
uint64_t mod_exp(uint64_t, uint64_t, uint64_t);

/*
  This should take input of a file, and read each character in to an array of type uint32_t.
  At the start of the array, the first entry should be the length of the message to assist with
  formatting the output from the decryption step.

  example:

  ./rsa -e filename1 -o my_encrypted_file -k my_key.pub
    * encrypts filename1 using the public key my_key.pub and saves the output in a file
    * named my_encrypted_file.

  ./rsa -e filename2 -n my_key2
    * encrypts filename2 using a newly generated public key and saves the key as filename2.pub
    * and saves the output to filename2_encrypted.
    * the public and private key will be saved as my_key2.pub and my_key2.priv respectively.

  ./rsa -d my_encrypted_file -o filename1 -k my_key.priv
    * decryptes my_encrypted_file using my_key.priv and saves output as filename1.

  As a command-line argument, the file will be encrypted and written to a file with
  a name specified by a -o flag. The name of the input file will be used otherwise.

  One may designate a specific encryption key to use by -k flag, or a new key-pair
  will be generated if not specified.
*/

int main(int argc, char ** argv)
{
  srand(time(0));
  uint64_t pub, priv, n;
  char * message = "Hello World, this is Alex and all your base are belong to us.\n";
  uint64_t digest[strlen(message)];
  generate_keys(&pub, &priv, &n);
  printf("PubKey = %llu\nPrivKey = %llu\nN = %llu\n", pub, priv, n);
  encrypt(message, digest, pub, n);
  for(int i=0; i < strlen(message); i++)
    printf("%llu ", digest[i]);
  printf("\n");
  decrypt(message, digest, priv, n);
  printf("\n%s\n", message);
  printf("\n");
  return 0;
}

void decrypt(char * message, uint64_t * digest, uint64_t priv, uint64_t n)
{
  for(int i=0; i < strlen(message); i++)
  {
    digest[i] = mod_exp(digest[i],priv,n);
    printf("%c ", ((uint8_t *)digest)[i]);
  }
}

void encrypt(char * message, uint64_t * digest, uint64_t pub, uint64_t n)
{
  for(int i=0; i < strlen(message); i++)
  {
    digest[i] = mod_exp((uint64_t)message[i],pub,n);
  }
}

uint64_t mod_exp(uint64_t m, uint64_t ex, uint64_t n)
{
  uint64_t c=1;

  for(int i=log2(ex); i >= 0; i--)
  {
    c = c*c % n;
    if((ex >> i) & 1)
      c = c*m % n;
  }
  return c;
}

void generate_keys(uint64_t * pub, uint64_t * priv, uint64_t * n)
{
  uint64_t p, q, d;
  while(1)
  {
    p = generate_random_prime(10000);
    q = generate_random_prime(10000);
    /* d needs to be coprime to the totient of n, but can essentially just be another prime
       in that case, replace generate_coprime(n) with generate_random_prime(upper_bound) */
    d = generate_random_coprime((p-1)*(q-1));
    if(d > max(p, q))
      break;
  }
  *pub = generate_pub_key(p, q, d);
  *priv  = d;
  *n = p*q;
  printf("p = %llu\nq = %llu\nd = %llu\n", p, q, d);
}

uint64_t generate_random_coprime(uint64_t val)
{
  uint64_t ret;
  while(1)
  {
    ret = rand() % val;
    if(ret == 0 || ret == 1)
      continue;
    if(gcd(ret, val) == 1)
      break;
  }
  return ret;
}

uint64_t gcd(uint64_t a, uint64_t b)
{
  uint64_t remaind;
  if(b > a)
  {
    remaind = b;
    b = a;
    a = remaind;
  }

  while(1)
  {
    remaind = a % b;
    if(remaind == 0)
      return b;
    if(a / b == 0)
      return a;
    a = b;
    b = remaind;
  }
}



uint64_t generate_random_prime(uint64_t upper_bound)
{
  uint64_t ret, flag=1;
  while(flag)
  {
    ret = rand() % upper_bound;
    flag = 0;

    if(ret < 2)
    {
      flag = 1;
      continue;
    }
    for(int i=2; i*i <= ret; i++)
    {
      if( ! (ret % i))
      {
        flag = 1;
        break;
      }
    }
  }
  return ret;
}

/* p, q are primes. d is a number that is coprime to (p-1)(q-1) */
uint64_t generate_pub_key(uint64_t p, uint64_t q, uint64_t d)
{
  int32_t x_n0 = (p - 1) * (q - 1);
  int32_t x_n1 = d;
  int32_t quotient, rem, temp1, temp2;
  int32_t a0 = 1, a1 = 0, b0 = 0, b1 = 1;

  while(x_n1 != 1)
  {
    quotient = x_n0 / x_n1;
    rem = x_n0 % x_n1;
    temp1 = a1;
    temp2 = b1;
    a1 = a0 - a1 * quotient;
    b1 = b0 - b1 * quotient;
    a0 = temp1;
    b0 = temp2;
    x_n0 = x_n1;
    x_n1 = rem;
  }
  while(b1 < 0)
    b1 += (p - 1)*(q - 1);

  return (uint64_t)b1;
}

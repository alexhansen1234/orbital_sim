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
  Stream cyphers are easy to figure out by character frequency analysis.
  This is just a demonstration of the underlying algorithm used to generate
  RSA asymmetric key pairs.
  Block cyphers are less prone to crack by frequency analysis,
  and professional crypto libraries are even less prone to crack :)
  Don't roll your own crypto for deployment, kids.
*/

int main(int argc, char ** argv)
{
  srand(time(0));
  uint64_t pub, priv, n;
  char message[] = "Message to encrypt.\n";
  uint64_t digest[strlen(message)];
  generate_keys(&pub, &priv, &n);
  printf("PubKey = %llu\nPrivKey = %llu\nN = %llu\n\n", pub, priv, n);
  printf("Original Message: %s\n", message);
  encrypt(message, digest, pub, n);
  printf("Encrypted Message: ");
  for(int i=0; i < strlen(message); i++)
    printf("0x%08llx ", digest[i]);
  printf("\n\n");
  decrypt(message, digest, priv, n);
  printf("Decrypted Message: %s\n", message);
  return 0;
}

void decrypt(char * message, uint64_t * digest, uint64_t priv, uint64_t n)
{
  for(int i=0; i < strlen(message); i++)
  {
    digest[i] = mod_exp(digest[i],priv,n);
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
    p = generate_random_prime(100000);
    q = generate_random_prime(100000);
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
    for(uint64_t i=2; i*i <= ret && i != 0; i++)
    {
      if( ! (ret % i) )
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
  int64_t x_n0 = (p - 1) * (q - 1);
  int64_t x_n1 = d;
  int64_t quotient, rem, temp1, temp2;
  int64_t a0 = 1, a1 = 0, b0 = 0, b1 = 1;

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

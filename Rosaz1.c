

#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then 

typedef enum { false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n) 
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

// itou avec un arg out => passage par adresse

void bisfact(int n, long * r) 
{ if (n==0) 
         *r=1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long fact2 (int n)
{ long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

     // Il est proposé de faire 3 versions pour observer des phénomènes de précision.
     // C'est le même code, seul le type change.

/*************************************************/
#include <math.h>
float Efloat ()
{ 
   float e_approx = 1.0; // Le premier terme de la série est toujours 1
   float factN=1.0;
   float old;
   float n = 1;
   float precision = 1e-6; // 10^-6
   do  {
        old = e_approx;
        factN = n * factN;
        n++;
        e_approx += 1.0 / factN;
    }while (fabs(old - e_approx)  > precision);
    return e_approx;
}

/*************************************************/

double Edouble () 
{

  double e_approx = 1.0; // Le premier terme de la série est toujours 1
   double factN=1.0;
   double old;
   double n = 1;
   double precision = 1e-6; // 10^-6
   do  {
        old = e_approx;
        factN = n * factN;
        n++;
        e_approx += 1.0 / factN;
    }while (fabs(old - e_approx)  > precision);
    return e_approx;
}
  
/*************************************************/

long double Elongdouble () {
  long double e_approx = 1.0; // Le premier terme de la série est toujours 1
  long double factN=1.0;
  long double old;
  long double n = 1;
  long double precision = 1e-6; // 10^-6
   do  {
        old = e_approx;
        factN = n * factN;
        n++;
        e_approx += 1.0 / factN;
    }while (fabs(old - e_approx)  > precision);
    return e_approx;
}

/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

void afficheYfloat (int n) 
{ 
  float y = Efloat() - 1.0;
  //printf("terme [%d]-> = %.15f\n", 0, y);
   for (int i = 1; i <= n; i++) {
        printf("terme [%d]-> = %.15f\n", i-1, y);
        y = i * y - 1.0;
    }
}

/*************************************************/

void afficheYdouble (int n) 
{
  double y = Edouble() - 1.0;
   for (int i = 1; i <= n; i++) {
        // printf("terme [%d]-> = %.15lf\n", i-1, y);
        y = i * y - 1.0;
    }
}

/*************************************************/

void afficheYlongdouble (int n) 
{
  long double y = Elongdouble() - 1.0;
  for (int i = 1; i <= n; i++) {
        // printf("terme [%d]-> = %.15Lf\n", i-1, y);
        y = i * y - 1.0;
    }
}


/*************************************************/
/*                                               */
/*            Puissance                          */
/*                                               */
/*************************************************/

double power1 (double x, long n) { 
  if(n==0)
    return 1.0;
  else if (n>0 )
    return power1(x,n-1)*x;
  else
    return 1.0/(power1(x,-n));
 }

/*************************************************/

double power2a (double x, long n) { 
  double r=1.0;
  int lim = n;

  if (n<0)
    lim = -n;
  for(int i=1;i<=lim;i++)
    r*=x;
  if (n<0)
    r=1.0/r;
  return r;
 }

/*************************************************/

double power2b (double x, long n) { 
  double r=1.0;
  while(n>0){
    r*=x;
    n--;
  }
  return r;
 }

/*************************************************/
double pow3(double x,long n,double *r){
  if(n!=0){
    *r=(*r)*x; // r doit etre passe en parametres en tant que pointeur 
    pow3(x,n-1,r);
  }
}

double power3 (double x, long n) { 
  double p = 1.0;
  double *r=&p;
  pow3(x,n,r);
  return *r;
 }

/*************************************************/
double pow4(double x,long n,double r){
  if(n==0){
    return r;
  }else{
    return pow4(x,n-1,r*x);
  }
}
double power4 (double x, long n) { 
  return pow4(x,n,1);
 }

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : rame : 8 en 1/2s, 9 en qqs s, 10 en 1m

double power5 (double x, long n)
{
    if (n == 0)
         return 1 ;
    else if (n % 2 == 0)
              return (power5(x,n/2)*power5(x,n/2)   ) ;
         else return (power5(x,n/2)*power5(x,n/2) *x) ;   
}

/*************************************************/

double power6 (double x, long n) { 
  if(n==0)
    return 1;
  else{
    double y = power6(x,n/2);
    if(n%2==0)
      return y*y;
    else
      return y*y*x;
  }
 }

/*************************************************/

double power7 (double x, long n) { 
if(n==0)
  return 1;
else{
  if(n%2==0)
    return power7(x*x,n/2);
  else 
    return (power7(x*x,n/2)*x);
}  
}

/*************************************************/
double pow8(double x,long n,double r){
  if(n==0)
    return r;
  else{
    if(n%2==0)
      return pow8(x*x,n/2,r); 
    else
      return pow8(x*x,n/2,r*x);
  }
}
double power8 (double x, long n) { 
  return pow8(x,n,1);
 }

/*************************************************/
double pow9(double x,long n,double *r ){ // r probablement en pointeur
  if(n!=0){
    if(n%2!=0)
      *r=(*r)*x;
    pow9(x*x,n/2,r);
  }
}
double power9 (double x, long n) { 
  double p=1.0; 
  double *r=&p;
  pow9(x,n,r);
  return *r;
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : calcul immédiat

double power10 (double x, long n)
{
    double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

double power (double x, long n, int i)
{ switch (i)  
   {
   case 1 : return power1(x,n) ; break ;
   case 2 : return power2a(x,n) ; break ;  // 2 pour 2a
   case 0 : return power2b(x,n) ; break ; // 0 pour 2b
   case 3 : return power3(x,n) ; break ;
   case 4 : return power4(x,n) ; break ;
   case 5 : return power5(x,n) ; break ;
   case 6 : return power6(x,n) ; break ;
   case 7 : return power7(x,n) ; break ;
   case 8 : return power8(x,n) ; break ;
   case 9 : return power9(x,n) ; break ;
  case 10 : return power10(x,n) ; break ;
     default : return 0 ; 
   }
}

   // remarque : les break sont ici inutiles car les returns font déjà des break

/*************************************************/

    // memes versions que la 10 mais avec des long double, puis des floats
    // but du jeu : observer des variations de precision

   // observation :
   //   imprécision à partir de k~5 (float), k~12 (double), k~14 (long double)
   //   rend 1 à partir de k=8 (float), k=16 (double)
   //   rend 1 non observé sur les long double, maxint atteint avant

long double power11 (long double x, long n)
{
    long double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

float power12 (float x, long n)
{
    float r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}


//**********************************************
/*************************************************/
/*                                               */
/*             Ackermann                         */
/*                                               */
/*************************************************/
// Version purement recursive
int A1(int m, int n) {
  if(m==0)
    return n+1;
  else if(n==0)
          return A1(m-1,1);
        else 
          return A1(m-1,A1(m,n-1));
    
}

//int Ackermann1 (int m) { return 0 ; }
int Ackermann1 (int m) { return A1(m,0); }

/*************************************************/
// recursive en m et iterative en n
int A2(int m, int n) { 
  if(m==0)
    return n+1;
  else{
    int r=1;
    for(int i=1;i<=n+1;i++)
      r=A2(m-1,r);
    return r;
  } 
}

//int Ackermann2 (int m) { return 0 ; }
int Ackermann2 (int m) { return A2(m,0); }

/*************************************************/
// iterative en m et recursive en n 
// pas sure pour celle la 
int A3(int m,int n){
  if(m==0){
    return n+1;
  }else if(n==0){
    int r=A3(m-1,1);
  }else{
    int r = n+1; 
    for(int i=1;i<=m;i++){
      r=A3(m,r);
    }
    return r;
  }
  
}
int Ackermann3 (int m) { return A3(m,0); }

/*************************************************/

int Ackermann4 (int m) { return 0 ; }

/*************************************************/

int Ackermann5 (int m) { return 0 ; }

/*************************************************/
  
int Ackermann (int m, int i)
{ switch (i)  
   {
   case 1 : return Ackermann1 (m) ; // break ;
   case 2 : return Ackermann2 (m) ; // break ;
   case 3 : return Ackermann3 (m) ; // break ;
   case 4 : return Ackermann4 (m) ; // break ;
   case 5 : return Ackermann5 (m) ; // break ;
   default : return 0 ; 
   }
}


/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{

       double x ;
       long double y ;
       float z ;
       
       int cptx ;
  
       long nx ;
       
       int i,j ; 
       
/******************************************************************************/
 
    // mettre "if true" vs "if false" selon que vous voulez les tests ou non
  
/****************  petit test sur le fonctionnement du switch  ************/

if (true) {

 switch (2)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }


 switch (4)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }

   printf("\n") ; 

}
      
      
/************************  taille des nombres  *************************/
      
if (true) {     
       
       printf("ce programme suppose que les long font 8 octets\n") ;
       printf("S'ils n'en font que 4, il faudra utiliser long long\n") ;

       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof(long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
 
       x = 1.0 ;
       cptx = 0 ;
       while ( (1.0 + x) - 1.0 != 0 )
          { x = x/10 ; cptx ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cptx) ; 
       printf("et 1+1/10^%d vaut en fait 1+%lf\n", cptx-1, (1.0 + 10*x) - 1.0) ;
        
       printf("ce programme suppose que les doubles font au moins 8 octets\n") ;
       printf("et que ((double) 1+1/10^-15) n'est pas 1 \n") ;       
       printf("Si ce n'est pas le cas, utiliser des long double \n") ;
       
       printf("\n") ;      
}

/************************  factorielle  *************************/

if (true) {

     printf("%ld \n",fact(5)) ;
     printf("%ld \n",fact2(5)) ;
     printf("\n") ;
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (true) {  
       

        printf(" e1 = %.20f \n", Efloat()) ;
        printf(" e2 = %.30lf \n", Edouble()) ; 
        printf(" e3 = %.40Lf \n", Elongdouble()) ; 
        
}

if (false) {  
            printf("for float\n");
            afficheYfloat(30) ;
            printf("for double\n");

            afficheYdouble(30) ;
            printf("for long double\n");

            afficheYlongdouble(30) ;
}
        
/******************    power     *******************************/

if (true) {  

        //   test simplet, vérifie le B.A. BA, test de 2^10 pour toutes les versions
        // printf("le res  = %lf\n", power2a(2,0) ) ;
        // printf("le res  = %lf\n", power(2,3,1) ) ;
        // printf("le res  = %lf\n", power3(2,3) ) ;
        // printf("le res  = %lf\n", power10(-2,3) ) ;

        
        for(i=0 ; i<=10 ; i++)
          printf("Power %d dit que power(2,-2) vaut %lf \n", i, power(2,-2,1) ) ;
        printf("\n") ;
      
}

        
if (false) {  

        i=5 ;  // numéro de la version que l'on teste

        // test de la résistance de power version i, calcul de (1+1/N)^N
        // pour des N puissances de 10 de plus en plus grosses
     
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=15 ; j++)
        {
        printf("power %d ((1+10^-%2d)^(10^%2d)) rend %.12lf\n", i, j, j, power(1+x,nx,i)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;
       
}
     
if (false) {

        // tests sur la précision que l'on obtient suivant que
        // l'on utilise float, double, long double

        printf("VERSION 12 avec float \n") ;
        z = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12f\n", j, j, power12(1+z,nx)) ;
        z = z/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 10 avec double \n") ;
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12lf\n", j, j, power10(1+x,nx)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 11 avec long double \n") ;
        y = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12LF\n", j, j, power11(1+y,nx)) ;
        y = y/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;



}

/******************    Ackermann    *******************************/
                
if (false) { 
 
        for(i=1 ; i<=5 ; i++)  // numéro de version
        
        for(j=0 ; j<=5 ; j++)  // test de A(j,0) pour j de 0 à 5
        
        printf("Ack%d(%d) = %d \n", i, j, Ackermann(j,i)) ;
}

/***********************************************************************/

    return 0;
}







// planos.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
/* En este código usted debe agregar las sentencias 
   necesarias ( funciones, operadores y script de pruebas )
   para: 
   // EJER 1) operador de entrada del clsVector3D
   // EJER 2) operador Producto Cruz de dos clsVector3D
   // EJER 3) Construir el plano a partir de los tres puntos v1, v2 y v3.
   // EJER 4) Impresión del plano A * x + B * y + C * z + D = 0.
   // EJER 5) Lectura del plano como A * x + B * y + c * z + D = 0. 
   // EJER 6) Obtener el punto que resulta de la intersección de tres planos 

  En los casos de los operadores de lectura agregue lectura de input streams
  definidos en base a cadenas de caracteres, de tal forma que pueda probar
  de manera rápida sus operadores.

*/

#include <iostream>
using namespace std;
// ============================================
class clsVector3D
{
private:
	double dbl_x, dbl_y, dbl_z ;
public:
	clsVector3D()
	{ 
      dbl_x = dbl_y = dbl_z = 0.0;
	}
	void x( double unX ) { dbl_x = unX; }
	double x() { return dbl_x; }

	void y( double unY ) { dbl_y = unY; }
	double y() { return dbl_y; }

	void z( double unZ ) { dbl_z = unZ; }
	double z() { return dbl_z; }

    friend ostream& operator <<( ostream& os, clsVector3D p )
	{
      os << "( " << p.x() << "," << p.y() << "," << p.z() << " )";
	  return os;
	}

	friend clsVector3D operator +( clsVector3D a, clsVector3D b )
	{
      clsVector3D s;
      s.x( a.x() + b.x() );
  	  s.y( a.y() + b.y() );
  	  s.z( a.z() + b.z() );

	   return s; 
	}

	friend clsVector3D operator * ( double esc, clsVector3D v )
	{
      clsVector3D w;

  	  w.x( esc * v.x() );
  	  w.y( esc * v.y() );
  	  w.z( esc * v.z() );

  	  return w;
	}

	friend clsVector3D operator * ( clsVector3D v, double esc )
	{
      return esc * v;
	}

   // EJER 1) operador de entrada del clsVector3D:
	friend istream& operator >>( istream& is, clsVector3D& v )
	{
      clsVector3D w;
      // double x, y, z;
      // is >> x;
      // is >> y;
      // is >> z;
      // w.x(x);
      // w.y(y);
      // w.z(z);

      // v = w;
      // return is;

      enum edo { S0, S1, S2, S3, S4, S5, SF, SError };
      enum edo s = S0;
      char c;
      int cont=0;
      double num=0;


      while((s != SF) && (s!=SError) &&(cont <3)){
        (is).get(c);

        if((is).eof()){ // cero es falso
          c = '\0';
        }
        switch (s){
          case S0:
            if(c == '(' && is >> num){
              s = S1;
              w.x(num);
              cont++;
            }else{
              s = SError;
              cout << "Error: No hay ( o no hay numero despues" << endl;
            }
            break;
          case S1:
            if(c==','){
              if(is >> num){ 
                switch(cont){
                  case 1:
                    w.y(num);
                    cont++;
                    break;
                  case 2:
                    w.z(num);
                    cont++;
                    break;
                }
              }else{
                s=SError;
                cout << "Error: Despues de , no hay numero" << endl;
              }
            }else{
              if(c==')'){
                s = SF;
              }else{
                s=SError;
                cout << "Error: Despues de numero no hay , ni )" << endl;
              }
            }    
            break;
          
          case SF:
            if(c!=0){
              s = SError;
              cout << "Error: La cadena deberia terminar" << endl;
            }else{
              cont ++;
            }
          case SError:
            cout << "Error en la cadena" << endl;
            break;
        }
      }
      v = w;
      return is;
	}
  // EJER 2) operador Producto Cruz de dos clsVector3D
	friend clsVector3D operator *( clsVector3D& a, clsVector3D& b )
	{
      clsVector3D w;
      double detX, detY, detZ;
      detX = (a.y()*b.z())-(a.z()*b.y());
      detY = (a.x()*b.z())-(a.z()*b.x());
      detZ = (a.x()*b.y())-(a.y()*b.x());
      w.x( detX );
  	  w.y( -detY );
  	  w.z( detZ );

  	  return w;
	}
};
// =============================================
class clsPlano3D
{
private:
   double dbl_A, dbl_B, dbl_C, dbl_D; // representa el plano Ax + By + Cz + D = 0.
public:
   clsPlano3D()
   {
      dbl_A = dbl_B = dbl_C = dbl_D = 0.0;
   }

   // EJER 3)  Construir el plano a partir de los tres puntos v1, v2 y v3.
   clsPlano3D( clsVector3D v1, clsVector3D v2, clsVector3D v3 )
   {  // por lo pronto un dummy que entrega el 5x + 5y + 5z + 5 = 0.

      dbl_A = (v2.y()*v3.z())-(v2.y()*v1.z())-(v1.y()*v3.z())-(v3.y()*v2.z())+(v1.y()*v2.z())+(v3.y()*v1.z());
      dbl_B = (v2.x()*v1.z())-(v2.x()*v3.z())+(v1.x()*v3.z())+(v3.x()*v2.z())+(v3.x()*v1.z())-(v1.x()*v2.z());
      dbl_C = (v2.x()*v3.y())-(v2.x()*v1.y())-(v1.x()*v3.y())-(v3.x()*v2.y())+(v3.x()*v1.y())+(v1.x()*v2.y());
      dbl_D = (v1.x()*v3.y()*v2.z())-(v1.x()*v2.y()*v3.z())+(v2.x()*v1.y()*v3.z())-(v3.x()*v1.y()*v2.z())-(v2.x()*v3.y()*v1.x())+(v3.x()*v2.y()*v1.z());
   }
	  
   void A( double unA ) { dbl_A = unA; }
   double A() { return dbl_A; }

   void B( double unB ) { dbl_B = unB; }
   double B() { return dbl_B; }

   void C( double unC ) { dbl_C = unC; }
   double C() { return dbl_C; }

    void D( double unD ) { dbl_D = unD; }
   double D() { return dbl_D; }

   // EJER 4) Impresión del plano A * x + B * y + c * z + D = 0.
   friend ostream& operator <<( ostream& os, clsPlano3D& p )
   {
     os << p.dbl_A << "x " ;
     if(p.dbl_B>=0){
        os << "+";
     }
     os << p.dbl_B << "y ";
     if(p.dbl_C >=0){
        os << "+";
     }
     os << p.dbl_C << "z ";
     if(p.dbl_D >=0){
        os << "+";
     }
     os << p.dbl_D << " = 0" << endl;
     return os;
   }
   
   // EJER 5) Lectura del plano como A * x + B * y + c * z + D = 0. 
   friend istream& operator >>( istream& is, clsPlano3D& p )
   { 
     clsPlano3D w;
     is >> w.dbl_A;
     is >> w.dbl_B;
     is >> w.dbl_C;
     is >> w.dbl_D;
  	 p = w;
  	 return is;
   }

   friend void sacaRecta( clsPlano3D P1, clsPlano3D P2){
    clsVector3D a,b,c;
    a.x(P1.dbl_A);
    a.y(P1.dbl_B);
    a.z(P1.dbl_C);

    b.x(P2.dbl_A);
    b.y(P2.dbl_B);
    b.z(P2.dbl_C);

    clsVector3D vect;
    vect.x((a*b).x());
    vect.y((a*b).y());
    vect.z((a*b).z());

    double detS, detX, detY;
    detS = (a.x()*b.y())-(a.y()*b.x());
    detX = (P1.dbl_D*b.y())-(a.y()*P2.dbl_D);
    detY = (a.x()*P2.dbl_D)-(P1.dbl_D*b.x());

    c.x(detX/detS);
    c.y(detY/detS);

    cout << "Recta de interseccion: (x,y,z) = " << c << " + t*" << vect << endl;

   }

   // EJER 6) Obtener el punto que resulta de la intersección de tres planos 
   friend clsVector3D interseccion( clsPlano3D P1, clsPlano3D P2, clsPlano3D P3 )
   {
     // va el dummy con el ( 100.0 ,200.0, 300.0)
    //Matriz extendida
    double r1[4] = {P1.dbl_A, P1.dbl_B, P1.dbl_C, P1.dbl_D};
    double r2[4] = {P2.dbl_A, P2.dbl_B, P2.dbl_C, P2.dbl_D};
    double r3[4] = {P3.dbl_A, P3.dbl_B, P3.dbl_C, P3.dbl_D};

    //Para obetener rango de matriz
    int rngM=0, rngME=0;
    double coc12A = r2[0]/r1[0];
    double coc12B = r2[1]/r1[1];
    double coc12C = r2[2]/r1[2];
    double coc12D = r2[3]/r1[3];

    double coc13A = r3[0]/r1[0];
    double coc13B = r3[1]/r1[1];
    double coc13C = r3[2]/r1[2];
    double coc13D = r3[3]/r1[3];

    double coc23A = r2[0]/r3[0];
    double coc23B = r2[1]/r3[1];
    double coc23C = r2[2]/r3[2];
    double coc23D = r2[3]/r3[3];

    int planoRep;

    //Simple:
    if(coc12A != coc12B  || coc12A != coc12C){ // r2 != alfa*r1
      rngM++;
    }else{
      planoRep = 2;
    }
    if(coc13A != coc13B || coc13A != coc13C){ // r3 != beta*r1
      rngM++;
    }{
      planoRep = 3;
    }
    if(coc23A != coc23B || coc23A != coc23C){ // r2 != gamma*r3
      rngM++;
    }{
      planoRep = 6;
    }
    if(rngM==0){
      rngM++;
    }

    //Extendida:
    if(coc12A != coc12B  || coc12A != coc12C || coc12A != coc12D){ // r2 != alfa*r1
      rngME++;
    }
    if(coc13A != coc13B || coc13A != coc13C  || coc13A != coc13D){ // r3 != beta*r1
      rngME++;
    }
    if(coc23A != coc23B || coc23A != coc23C  || coc23A != coc23D){ // r2 != gamma*r3
      rngME++;
    }
    if(rngME==0){
      rngME++;
    }

    clsVector3D a;
    switch(rngM){
      case 1:
        if(rngME == 1){
            cout << "Es el mismo plano. Interseccion: " << P1;            
        }else{
            cout << "Son tres planos paralelos o dos planos coincidentes y uno paralelo. No hay interseccion." << endl;
        }
        break;
      case 2:
        if(rngME == 2){
            cout << "Tres planos que intersectan en una recta.";
            switch(planoRep){
              case 2: //Planos iguales: 1 y 2
                sacaRecta(P1,P3);
                break;
              case 3: //Planos iguales: 1 y 3
                sacaRecta(P1, P2);
                break;
              case 6: //Planos iguales: 2 y 3
                sacaRecta(P1, P3);
                break;
            }
          }else{
            cout << "La interseccion de dos planos da dos rectas disntintas. No hay interseccion." << endl;
        }
        break;
      case 3:
        double detS, detX, detY, detZ;
        detS = ((P1.dbl_A*P2.dbl_B*P3.dbl_C)+(P2.dbl_A*P3.dbl_B*P1.dbl_C)+(P3.dbl_A*P1.dbl_B*P2.dbl_C))-((P3.dbl_A*P2.dbl_B*P1.dbl_C)+(P1.dbl_A*P3.dbl_B*P2.dbl_C)+(P2.dbl_A*P1.dbl_B*P3.dbl_C));
        detX = ((-P1.dbl_D*P2.dbl_B*P3.dbl_C)+(-P2.dbl_D*P3.dbl_B*P1.dbl_C)+(-P3.dbl_D*P1.dbl_B*P2.dbl_C))-((-P3.dbl_D*P2.dbl_B*P1.dbl_C)+(-P1.dbl_D*P3.dbl_B*P2.dbl_C)+(-P2.dbl_D*P1.dbl_B*P3.dbl_C));
        detY = ((P1.dbl_A*(-P2.dbl_D)*P3.dbl_C)+(P2.dbl_A*(-P3.dbl_D)*P1.dbl_C)+(P3.dbl_A*(-P1.dbl_D)*P2.dbl_C))-((P3.dbl_A*(-P2.dbl_D)*P1.dbl_C)+(P1.dbl_A*(-P3.dbl_D)*P2.dbl_C)+(P2.dbl_A*(-P1.dbl_D)*P3.dbl_C));
        detZ = ((P1.dbl_A*P2.dbl_B*(-P3.dbl_D))+(P2.dbl_A*P3.dbl_B*(-P1.dbl_D))+(P3.dbl_A*P1.dbl_B*(-P2.dbl_D)))-((P3.dbl_A*P2.dbl_B*(-P1.dbl_D))+(P1.dbl_A*P3.dbl_B*(-P2.dbl_D))+(P2.dbl_A*P1.dbl_B*(-P3.dbl_D)));

        a.x( detX / detS );
        a.y( detY / detS );
        a.z( detZ / detS );
        cout << "Los tres planos intersectan en: " << a;
        break;
    }
     return a;
   }
   
};
// =============================================
void main()
{
  clsVector3D a,b,c;
  string coord;

  a.x( 1.0 );
  a.y( 2.0 );
  a.z( 3.0 );

  b.x( -2.0 );
  b.y( -5.0 );
  b.z( -7.0 );

  cout << a << " + " << b << " = " << a + b << endl;

  cout << 5.0 << " * " << a << " = " << 5.0 * a << endl;

  cout << a << " * " << 5.0 << " = " << a * 5.0 << endl;

  cout << "Ingrese el vector: ";

  cin >> c;

  cout << "c = " << c << endl;

  cout << " a * b = " << a << " * " << b << " = " << a * b << endl;

  clsPlano3D q1,q2,q3;

  cout << "Ingrese A, B, C y D del plano separados por un espacio: ";

  //cin >> q1;

  cout << q1 << endl;

  // q1.A(1.0);
  // q1.B(-3.0);
  // q1.C(2.0);
  // q1.D(3.0);

  // q2.A(5.0);
  // q2.B(6.0);
  // q2.C(-1.0);
  // q2.D(-13.0);

  // q3.A(4.0);
  // q3.B(-1.0);
  // q3.C(3.0);
  // q3.D(-8.0);

  q1.A(2.0);
  q1.B(-1.0);
  q1.C(1.0);
  q1.D(-2.0);

  q2.A(3.0);
  q2.B(1.0);
  q2.C(-2.0);
  q2.D(-9.0);

  q3.A(-1.0);
  q3.B(2.0);
  q3.C(5.0);
  q3.D(5.0);

  cout << "Interseccion de " << q1 << " , " << q2 << " y " << q3 << endl;
  interseccion( q1,q2,q3 );

}
// ========================================================

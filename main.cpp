#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>

#include "funciones.cpp"

using namespace std;

typedef long int TDATO;


int main()
{
    TDATO p = 0;
    TDATO q = 0;
    TDATO s = 0;
    TDATO N = 0;
    TDATO x = 0;
    int e = 0;
    
    int num_iteraciones;
    int contador = 0;
    bool control = true;
    
    TDATO v =0;
    vector<TDATO> v_x;
    vector<TDATO> v_a;
    vector<int> v_e;
    vector<TDATO> v_y;

    
    cout << "----------------PRACTICA 9---------------" << endl;
    cout << "Datos de Entrada." << endl;
    do
    {
        cout <<  "Introduzca p:";
        cin >> p;
    }while(!primalidad(p));
    
    do
    {
        cout << "Introduzca q:"; 
        cin >> q;
    }while(!primalidad(q));
    
    N = p * q;
    do
    {
        cout << "Introduzca s:";
        cin >> s;
    }while(!comprobar_s(s, N));
    
    cout << "Introduzca el numero de iteraciones:";
    cin >> num_iteraciones;
    
    //Calculamos v
    v = exponenciacion_rapida(s, 2, N);
    
    
    for(int i=0;i < num_iteraciones; i++)
    {
        cout << i+1 << "º iteracion. " << endl;
        do
        {
            cout << "Introduzca numero secreto x:";
            cin >> x;
        }while(x >= N && x<=0);
        
        v_x.resize(v_x.size()+1);
        v_x[i] = x;
        TDATO a = exponenciacion_rapida(x,2,N);
        
        v_a.resize(v_a.size()+1);
        v_a[i] = a;
        
        do
        {
            cout << "Introduzca bit e: ";
            cin >> e;   
        }while(e < 0 && e > 1);
        
        v_e.resize(v_e.size()+1);
        v_e[i] = e;
    }
    
    cout << "--------------------------------------------------------" << endl;
    cout << "Salida: " << endl;
    cout << "Publicando N:" << N << endl;
    cout << "Publicando v:" << v << endl;
    
    while(contador < num_iteraciones && control == true)
    {
        v_y.resize(v_y.size()+1);

        if(v_e[contador] == 0)
        {
            v_y[contador] = v_x[contador] % N;

            //Verificación
            if((v_a[contador] % N) == exponenciacion_rapida(v_y[contador],2, N))
            {
                control = true;
                 cout << contador+1 << "º iteracion: a= " << v_a[contador] << ", y= " << v_y[contador] << " ,comprobar que " << v_y[contador] << "^2 = " << v_a[contador] << " (mod " << N << ") => Validez: True" << endl;
            }
            else
            {
                control = false;
                cout << contador+1 << "º iteracion: a= " << v_a[contador] << ", y= " << v_y[contador] << " ,comprobar que " << v_y[contador] << "^2 = " << v_a[contador] << " (mod " << N << ") => Validez: False" << endl;
                cout << "Parando ejecucion..." << endl;
            }
        }
        else if(v_e[contador] == 1)
        {
            v_y[contador] = (v_x[contador]*s) % N;
            
            //Verificación
            if(((v_a[contador]*v) % N) == exponenciacion_rapida(v_y[contador],2, N))
            {
                control = true;
                cout << contador+1 << "º iteracion: a= " << v_a[contador] << ", y= " << v_y[contador] << " ,comprobar que " << v_y[contador] << "^2 = " << v_a[contador] << "*" << v << " (mod " << N << ") => Validez: True" << endl;
            }
            else
            {
                control  = false;
                cout << contador+1 << "º iteracion: a= " << v_a[contador] << ", y= " << v_y[contador] << ", comprobar que " << v_y[contador] << "^2 = " << v_a[contador] << "*" << v << " (mod " << N << ") => Validez: False" << endl;
                cout << "Parando ejecucion..." << endl;
            }
        }
        
        contador++;
    }
    
    return 0;
}
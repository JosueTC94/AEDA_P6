using namespace std;

/*typedef struct euc
{
    int inverso;
    bool control;
};*/  

bool comprobacion_inicial_primo(vector<int> p,int x)
{
    bool res = false;
    for(int i=0;i<p.size();i++)
    {
        if(x == p[i])
        {
            res = true;
            break;
        }
    }
    return res;
}

bool divisible(vector<int> primos, int x)
{
    bool resultado = false;
    for(int i=0;i<primos.size();i++)
    {
        if(x % primos[i] == 0)
        {
            resultado = true;
            break;
        }
        else
        {
            resultado = false;
        }
    }
    return resultado;
}

bool comprobar_aleatorios(vector<int> aleatorios_, int aux)
{
    int i = 0;
    bool control_aux = false;
    while(i < aleatorios_.size() && control_aux == false)
    {
        if(aleatorios_[i] != aux)
        {
            i++;
            control_aux = false;
        }
        else
        {  
            control_aux = true;
        }
    }
    return control_aux;
}


long int exponenciacion_rapida(long int base, long int exponente, long int modulo)
{
    long int x = 1;
    long int y = fmod(base,modulo);
    while(exponente > 0 && y > 1)
    {
      if(fmod(exponente,2) != 0)
      {
        //Impar
        x = fmod((x*y),modulo);
        exponente = exponente-1;
      }
      else
      {
        //Par
        y = fmod((y*y),modulo);
        exponente = exponente / 2;
      }
    }
    return x;
}

bool primalidad(int x)
{
    bool control_primo = true;
    int tamanio = 0;
    //Compruebo que p no es divisible por ninguno primo pequeño
    vector<int> primos_peq;
    primos_peq.resize(5);
    primos_peq[0] = 2;
    primos_peq[1] = 3;
    primos_peq[2] = 5;
    primos_peq[3] = 7;
    primos_peq[4] = 11;
    
    vector<int> aleatorios;
    //aleatorios.resize(TAM);
    
    vector<int> resultados;
    //resultados.resize(TAM);
    
    if(comprobacion_inicial_primo(primos_peq,x)) //Compruebo si p es uno de los primos pequenios 
    {
        control_primo = true;
    }
    else
    {
        //Establezco tamanio del vector aleatorio
        if(x < 100)
            tamanio = 0.2 * x;
        else
            tamanio = 100;
            
        //cout << "Tamanio->" << tamanio << endl;
        
        if(divisible(primos_peq,x))
        {
              control_primo = false;
        }
        else
        {
            //cout << "Tamanio dentro del else:" << tamanio << endl;
            for(int i=0;i<tamanio;i++)
            {
                //cin.get();
                srand(clock());
                int numero = 1+rand()%(x-1);
                //cout << "Numero aleatorio->" << numero << endl;
                //cout << "Aleatorios:" << endl;
                //imprimir_vector(aleatorios);
                if(comprobar_aleatorios(aleatorios,numero) == true) //TRUE --> el aleatorio ya estaba dentro del vector. FALSE--> el aleatorio no estaba dentro del vector ----- && aleatorios.size() < tamanio-1
                {
                    //cout << "Aleatorio existente ya" << endl;
                    do
                    {
                        numero = 1+rand()%(x-1);   
                        //cout << "Nuevo aleatorio:" << numero << endl;
                    }while(comprobar_aleatorios(aleatorios,numero) == true);
                }
                //cout << "Tamanio del vector aleatorios:" << aleatorios.size() << endl;
                if(numero >= 1 && numero <= x-1)
                {
                    aleatorios.resize(aleatorios.size()+1);
                    aleatorios[i] = numero;   
                }
                else
                {
                    cerr << "Funcion aleatoria no se ha ejecutado correctamente..." << endl;
                    exit(-1);
                }
                //cout << "------------------------------------------" << endl; 
            }
            
            int i = 0;
            while(i < tamanio && control_primo == true)
            {
                long int resultado = exponenciacion_rapida(aleatorios[i],(x-1)/2,x);
                if(resultado == 1 || resultado == (x-1))   
                {
                    resultados.resize(resultados.size()+1);
                    resultados[i] = resultado;
                    control_primo = true;
                }
                else
                {
                    control_primo = false;
                }
                i++;
            }
        }        
    }

    //cout << "Tamanio de vector aleatorio->" << aleatorios.size() << endl;
    //cout << "Aleatorios:" << endl;
    //imprimir_vector(aleatorios);
    return control_primo;
}


bool algoritmo_euclides(int a, int b)
{
    int inverso = 0;
    bool inverso_control = false;
    vector<int> x;
    vector<int> z;
    int condicion = a; 
    int contador = 0;
    
    x.resize(x.size()+2);
    z.resize(z.size()+1);
    
    z[-1] = 0;
    z[0] = 1;
    
    x[0] = a;
    x[1] = b;
    
    while(condicion != 0)
    {
        //Divido x[contador] / x[contador+1]
            //Cociente
            if(x[contador] < x[contador+1])
            {
                int temp = x[contador];
                x[contador] = x[contador+1];
                x[contador+1] = temp;
            }
            int cociente = x[contador] / x[contador+1];
            //cout << "Divido " << x[contador] << "/" << x[contador+1] << "=" << cociente << endl;
            cociente = -cociente;
            //cout << "Cambio signo de cociente:" << cociente << endl;
            //Resto división
            condicion = x[contador] % x[contador+1];
            
        //Inserto en z[contador] el resultado anterior
        z.resize(z.size()+1);
        z[contador+1] = (cociente*z[contador]) + z[contador-1];

        //Inserto en x[contador+2] resto de la primera división
        x.resize(x.size()+1);
        x[contador+2] = condicion;

        //Actualizo contador
        contador++;
    }
    //cout << "Contador:" << contador << endl;
    //cout << "Imprimiendo x[contador]=>" << x[contador] << endl;
    
    if(condicion == 0 && x[contador] == 1)
    {
        //cout << "Inverso: " << z[contador-1] << endl;
        inverso_control = true;
        inverso = z[contador-1];
    }
    
    if(inverso < 0)
    {
        //cout << "Inverso negativo" << endl;
        while(inverso < 0)
        {
            inverso = inverso+b;
        }
        //cout << "Inverso actualizado:" << inverso << endl;
    }
    
    return inverso_control;
}

bool comprobar_s(int s_, int N_)
{
    bool resultado = false;
    if(s_ < N_ && s_ > 0 && algoritmo_euclides(s_,N_) == true)
    {
        resultado = true;
    }
    else
    {
        resultado = false;
        cout << "S no correcto." << endl;
    }
    return resultado;
}
/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simpletools header
#include "abdrive.h"                          // Include abdrive header
#include "ping.h"                             // Include ping header

int derecha; //variable para verificar si en el lado derecho hay pared
int desicion; //variable para indicar al robot que decision tomar

int main()                                    // main function
{
  //Pueros A0 y A1 en LOW
  low(26);
  low(27);

  while(1)                                    // Repeat indefinitely
  {
    drive_speed(45,45);  //velocidad de los motores
    
    //verifica si hay pared a la derecha
    derecha=evaluar_d();
    if (derecha == 1 && v_adelante() > 4){
      girarDerecha();  
    }
    //verifica si hay pared adelante
    if (v_adelante() < 5){
        girarIzquierda(); 
    }
    

  }
}

//funcion que retorna el valor del ultrasonico
int v_adelante(){
  return ping_cm(8);
}

// funcion para obtener los valores del sensor infrarojo
// Retorna 1 si no hay objeto
// Retorna 0 si hay objeto
int evaluar_d(){
    freqout(1, 1, 38000);
    if (input(2)==1){
      high(5);
    }
    else{
      low(5);
    }
    return input(2);
}


void girarDerecha(){
  drive_goto(6,6); 
  drive_speed(0,0);
  pause(500);
  drive_goto(26,-25); //giro a la derecha
  pause(500);
  // avanza hasta que se encuentra denuevo con una pared a la derecha
  while(evaluar_d()==1 && v_adelante()>5){
    drive_speed(10,10);
  }
  drive_goto(10,10);//avanza una pequeña distancia para evitar que detecte de nuevo un vacio en la derecha
  return;  
}

void girarIzquierda(){
  drive_speed(0,0);
  pause(500);
  drive_goto(-26,25); //gira a la izquierda 
  pause(500);
  drive_goto(5,5);
  return;
}

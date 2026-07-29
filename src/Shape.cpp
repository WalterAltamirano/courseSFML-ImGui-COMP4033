#include "Shape.h"
#include <iostream>

ManagementShape crearControlador() {
    ShapeHeader* mSh = new ShapeHeader;
    mSh->first = NULL;
    mSh->last  = NULL;
    mSh->cantidadDeFiguras = 0;
    return mSh;  
}

ShapeNode* figuraNodoConNombre(ManagementShape mSh ,std::string nombre) {
    if(mSh->cantidadDeFiguras != 0) {
        ShapeNode* actual = mSh->first;
        while(actual != NULL && actual->nombre != nombre) {
            actual = actual->next;
        }
        if(actual != NULL) {
            return actual;
        }
        std::cerr << "No existe una figura con el nombre dado" << std::endl;
        exit(1);
    } else {
        std::cerr << "No existen figuras que buscar. No se agrego ninguna aun" << std::endl;
        exit(1);
    }
}

//Dado un nombre, las velocidades en los ejes y un radio, construye un circulo.
//Obs: por default el color es Blanco
void agregarCirculo(ManagementShape mSh,float ancho,float altura,std::string nombreFigura, float velocidadX, float velocidadY, float radio,float posX, float posY){

}

//Dado un nombre, las velocidades en los ejes y un radio, construye un rectangulo.
//Obs: por default el color es Blanco
void agregarRectangulo(ManagementShape mSh,float ancho,float altura,std::string nombreFigura, float velocidadX, float velocidadY, float posX, float posY){

}

//Dado el encabezado de las figuras y el nombre de una especifica, devuelve la velocidad X de la figura con el nombre dado.
//Precond: Existe una figura con el nombre dado.
float obtenerVelocidadXDe(ManagementShape mSh, std::string nombre){

}

//Dado el encabezado de las figuras y el nombre de una especifica, devuelve la velocidad Y de la figura con el nombre dado.
//Precond: Existe una figura con el nombre dado.
float obtenerVelocidadYDe(ManagementShape mSh, std::string nombre){

}

//Dada una figura, la pinta de los colores dados
//Precond: Los colores se representan entre el rango 0 y 1 en formato RGB (en ese orden). 
//Obs: Recibe un array de 3 elementos en ese orden
void pintarFiguraDe(ManagementShape mSh ,float colores[]){

}

//Dada una figura, indica si esta visible en pantalla o no.
bool esVisible(ManagementShape mSh,std::string nombre){

}

//Dada una figura, indica si es de tipo circulo.
bool esCirculo(ManagementShape mSh,std::string nombre){

}

//Dado un controlador de figuras y un nombre, cambia el "sentido" de la direccion X de la figura con el nombre dado.
//Precond: Existe la figura con el nombre dado.
void invertirVelocidadXDe(ManagementShape mSh, std::string nombre){

}

//Dado un controlador de figuras y un nombre, cambia el "sentido" de la direccion Y de la figura con el nombre dado.
//Precond: Existe la figura con el nombre dado.
void invertirVelocidadYDe(ManagementShape mSh, std::string nombre){

}

//Dados dos numeros irracionales, actualiza ambas velocidades de la figura dada
void actualizarVelocidades(ManagementShape mSh,float velocidadX, float velocidadY){

}

//Dado un controlador y un nombre de figura, actualiza la visibildad de la figura con el nombre dado.
//Precond; existe la figura con el nombre dado.
void actualizarDibujadoDe(ManagementShape mSh, std::string nombre, bool estaVisible) {

}

//Dado un controlador de figuras y un nombre, retorna la figura de tipo circulo al nombre dado.
//Precond: existe una figura tipo circulo con el nombre dado.
sf::CircleShape obtenerCirculo(ManagementShape mSh, std::string nombre) {
    ShapeNode* figuraConNombre = figuraNodoConNombre(mSh,nombre);
    if(figuraConNombre->esCirculo) {
        return figuraConNombre->figuraCirculo;
    }
}

//Dado un controlador de figuras y un nombre, retorna la figura de tipo rectangulo al nombre dado.
//Precond: existe una figura tipo rectangulo con el nombre dado.
sf::RectangleShape obtenerRectangulo(ManagementShape mSh, std::string nombre) {
    ShapeNode* figuraConNombre = figuraNodoConNombre(mSh,nombre);
    if(!figuraConNombre->esCirculo) {
        return figuraConNombre->figuraRectangulo;
    }
}
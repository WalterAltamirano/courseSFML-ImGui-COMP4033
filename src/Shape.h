#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>
#define CANTIDADCOLORES 3

struct ShapeNode {
    sf::CircleShape figuraCirculo;
    sf::RectangleShape figuraRectangulo;
    std::string nombre;
    float colores[CANTIDADCOLORES];
    float velocidadX;
    float velocidadY;
    bool esVisible;
    bool esCirculo;
    ShapeNode* next;
};
typedef ShapeNode* NodeSh;

struct ShapeHeader {
    NodeSh first;
    NodeSh last;
    int cantidadDeFiguras;
    
};
typedef ShapeHeader* ManagementShape;
/*
    Inv.de.Rep:
        *Sea un encabezado de figuras "ShapeHeader" "sh", sii "sh->first == NULL" entonces "sh->last = NULL".
        
        *Sea un encabezado de figuras "ShapeHeader" "sh", si existe un nodo "NodeSh" en "sh->last" entonces
         "sh->last->next" debe ser igual a NULL.

        *Sea un nodo "ShapeNode" "nd", si existe un puntero en "nd->next", entonces apunta a un nodo "ShapeNode" y no otro tipo de estructura. 
        
        *Sea un encabezado de figuras "ShapeHeader" "sh", si "sh->cantidadDeFiguras" es numero entero "n", 
         entonces "n" es mayor o igual cero.

        *Sea un encabezado de figuras "ShapeHeader" "sh", si "sh->cantidadDeFiguras" es numero entero "n", 
         entonces "n" es la cantidad de nodos "ShapeNode" que se pueden recorrer desde "sh->first"
         por "sh->first->next" hasta alcanzar NULL.

        *Sea un ShapeNode "nd", "nd->colores" es un array de flotantes con capacidad de 3 elementos, donde
         cada "n", siendo "n" un elemento, "nd->colores[n] = m", "m" es un flotante mayor o igual a cero y menor
         o igual a 1.

        *Sea un ShapeNode "nd", si "nd->esCirculo" es false entonces "nd->figuraCirculo" es NULL y existe
         una instancia de sf::RectangleShape en "nd->figuraRectuangulo".

        * Sea un ShapeNode "nd", si "nd->esCirculo" es true entonces "nd->figuraRectangulo" es NULL y existe
         una instancia de sf::CircleShape en "nd->figuraCirculo".
        
*/

ManagementShape crearControlador();

//Dado un nombre, las velocidades en los ejes y un radio, construye un circulo.
//Obs: por default el color es Blanco
void agregarCirculo(ManagementShape manejadorDeFiguras,float ancho,float altura,std::string nombreFigura, float velocidadX, float velocidadY, float radio,float posX, float posY);

//Dado un nombre, las velocidades en los ejes y un radio, construye un rectangulo.
//Obs: por default el color es Blanco
void agregarRectangulo(ManagementShape manejadorDeFiguras,float ancho,float altura,std::string nombreFigura, float velocidadX, float velocidadY, float posX, float posY);

//Dado el encabezado de las figuras y el nombre de una especifica, devuelve la velocidad X de la figura con el nombre dado.
//Precond: Existe una figura con el nombre dado.
float obtenerVelocidadXDe(ManagementShape manejadorDeFiguras, std::string nombre);

//Dado el encabezado de las figuras y el nombre de una especifica, devuelve la velocidad Y de la figura con el nombre dado.
//Precond: Existe una figura con el nombre dado.
float obtenerVelocidadYDe(ManagementShape manejadorDeFiguras, std::string nombre);

//Dada una figura, la pinta de los colores dados
//Precond: Los colores se representan entre el rango 0 y 1 en formato RGB (en ese orden). 
//Obs: Recibe un array de 3 elementos en ese orden
void pintarFiguraDe(ManagementShape manejadorDeFiguras ,float colores[]);

//Dada una figura, indica si esta visible en pantalla o no.
bool esVisible(ManagementShape manejadorDeFiguras,std::string nombre);

//Dada una figura, indica si es de tipo circulo.
bool esCirculo(ManagementShape manejadorDeFiguras, std::string);

//Dados dos numeros irracionales, actualiza ambas velocidades de la figura dada
void actualizarVelocidades(ManagementShape manejadorDeFiguras,std::string nombre,float velocidadX, float velocidadY);

//Dado un controlador de figuras y un nombre, cambia el "sentido" de la direccion X de la figura con el nombre dado.
//Precond: Existe la figura con el nombre dado.
void invertirVelocidadXDe(ManagementShape manejadorDeFiguras, std::string nombre);

//Dado un controlador de figuras y un nombre, cambia el "sentido" de la direccion Y de la figura con el nombre dado.
//Precond: Existe la figura con el nombre dado.
void invertirVelocidadYDe(ManagementShape manejadorDeFiguras, std::string nombre);

//Dado un controlador y un nombre de figura, actualiza la visibildad de la figura con el nombre dado.
//Precond; existe la figura con el nombre dado.
void actualizarDibujadoDe(ManagementShape manejadorDeFiguras, std::string nombre, bool estaVisible);

//Dado un controlador de figuras y un nombre, retorna la figura de tipo circulo al nombre dado.
//Precond: existe una figura tipo circulo con el nombre dado.
sf::CircleShape obtenerCirculo(ManagementShape manejadorDeFiguras, std::string nombre);

//Dado un controlador de figuras y un nombre, retorna la figura de tipo rectangulo al nombre dado.
//Precond: existe una figura tipo rectangulo con el nombre dado.
sf::RectangleShape obtenerRectangulo(ManagementShape manejadorDeFiguras, std::string nombre);
    
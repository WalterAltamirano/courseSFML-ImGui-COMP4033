#include "Shape.h"


ManagementShape crearControlador() {
    ShapeHeader* mSh = new ShapeHeader;
    mSh->first = NULL;
    mSh->last  = NULL;
    mSh->cantidadDeFiguras = 0;
    return mSh;  
}

NodeSh figuraNodoConNombre(ManagementShape mSh ,std::string nombre) {
    if(mSh->cantidadDeFiguras != 0) {
        NodeSh actual = mSh->first;
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
void agregarCirculo(ManagementShape mSh,float radio,float segmentos,std::string nombreFigura,float velocidadX,float velocidadY,float posX, float posY){
    if(mSh != NULL) {
        NodeSh newNode = new ShapeNode;
        newNode->esVisible = true;
        newNode->esCirculo = true;
        newNode->tamañoOriginal = sf::Vector2f(radio,segmentos);
        sf::CircleShape nuevoCirculo = sf::CircleShape(radio,segmentos);
        nuevoCirculo.setPosition({posX, posY});
        nuevoCirculo.setPointCount(segmentos);
        nuevoCirculo.setRadius(radio);
        newNode->figuraCirculo = nuevoCirculo;
        newNode->escala = 0.0f;
        newNode->velocidadX = velocidadX;
        newNode->velocidadY = velocidadY;
        newNode->nombre = nombreFigura;
        if(mSh->first != NULL) {
            NodeSh prevFirst = mSh->first;
            newNode->next = prevFirst;
        } else {
            mSh->last = newNode;
            newNode->next = NULL;
        }
        mSh->first = newNode;
        mSh->cantidadDeFiguras++;
    }
}

//Dado un nombre, las velocidades en los ejes y un radio, construye un rectangulo.
//Obs: por default el color es Blanco
void agregarRectangulo(ManagementShape mSh,float ancho,float altura,std::string nombreFigura, float velocidadX, float velocidadY, float posX, float posY){
     if(mSh != NULL) {
        NodeSh newNode = new ShapeNode;
        newNode->esVisible = true;
        newNode->esCirculo = false;
        newNode->tamañoOriginal = sf::Vector2f(ancho,altura);
        sf::RectangleShape nuevoRectangulo = sf::RectangleShape({ancho,altura});
        nuevoRectangulo.setPosition({posX, posY});
        newNode->figuraRectangulo= nuevoRectangulo;
        newNode->escala = 0.0f;
        newNode->velocidadX = velocidadX;
        newNode->velocidadY = velocidadY;
        newNode->nombre = nombreFigura;
        if(mSh->first != NULL) {
            NodeSh prevFirst = mSh->first;
            newNode->next = prevFirst;
        } else {
            mSh->last = newNode;
            newNode->next = NULL;
        }
        mSh->first = newNode;
        mSh->cantidadDeFiguras++;
    }
}

//Dado el encabezado de las figuras y el nombre de una especifica, devuelve la velocidad X de la figura con el nombre dado.
//Precond: Existe una figura con el nombre dado.
float obtenerVelocidadXDe(ManagementShape mSh, std::string nombre){
    NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
    return figuraDada->velocidadX;
}

//Dado el encabezado de las figuras y el nombre de una especifica, devuelve la velocidad Y de la figura con el nombre dado.
//Precond: Existe una figura con el nombre dado.
float obtenerVelocidadYDe(ManagementShape mSh, std::string nombre){
    NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
    return figuraDada->velocidadY;
}

//Dada una figura, la pinta de los colores dados
//Precond: Los colores se representan entre el rango 0 y 1 en formato RGB (en ese orden). 
//Obs: Recibe un array de 3 elementos en ese orden
void pintarFiguraDe(ManagementShape mSh,std::string nombre,float* c){
    NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
    sf::CircleShape nuevoCirculo = figuraDada->figuraCirculo;
    nuevoCirculo.setFillColor(sf::Color(uint8_t(c[0] * 255), uint8_t(c[1] * 255), uint8_t(c[2] * 255)));
    figuraDada->figuraCirculo = nuevoCirculo;
    figuraDada->colores[0] = c[0];
    figuraDada->colores[1] = c[1];
    figuraDada->colores[2] = c[2];
}

//Dada una figura, indica si esta visible en pantalla o no.
bool esVisible(ManagementShape mSh,std::string nombre){
    ShapeNode* figuraDada = figuraNodoConNombre(mSh,nombre);
    return figuraDada->esVisible;
}

//Dada una figura, indica si es de tipo circulo.
bool esCirculo(ManagementShape mSh,std::string nombre){
    NodeSh figuraDada = figuraNodoConNombre(mSh,nombre);
    return figuraDada->esCirculo;
}

//Dado un controlador de figuras y un nombre, cambia el "sentido" de la direccion X de la figura con el nombre dado.
//Precond: Existe la figura con el nombre dado.
void invertirVelocidadXDe(ManagementShape mSh, std::string nombre){
    NodeSh figuraDada = figuraNodoConNombre(mSh,nombre);
    figuraDada->velocidadX = figuraDada->velocidadX * (-1.0f); 
}

//Dado un controlador de figuras y un nombre, cambia el "sentido" de la direccion Y de la figura con el nombre dado.
//Precond: Existe la figura con el nombre dado.
void invertirVelocidadYDe(ManagementShape mSh, std::string nombre){
    NodeSh figuraDada = figuraNodoConNombre(mSh,nombre);
    figuraDada->velocidadY = figuraDada->velocidadY * (-1.0f); 
}

//Dados dos numeros irracionales, actualiza ambas velocidades de la figura dada
void actualizarVelocidades(ManagementShape mSh,std::string nombre,float velocidadX, float velocidadY){
    NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
    figuraDada->velocidadX = velocidadX;
    figuraDada->velocidadY = velocidadY; 
}

//Dado un controlador y un nombre de figura, actualiza la visibildad de la figura con el nombre dado.
//Precond; existe la figura con el nombre dado.
void actualizarDibujadoDe(ManagementShape mSh, std::string nombre, bool estaVisible) {
     NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
     figuraDada->esVisible = estaVisible;
}

//Dado un controlador de figuras y un nombre, retorna la figura de tipo circulo al nombre dado.
//Precond: existe una figura tipo circulo con el nombre dado.
sf::CircleShape obtenerCirculo(ManagementShape mSh, std::string nombre) {
    NodeSh figuraConNombre = figuraNodoConNombre(mSh,nombre);
    if(figuraConNombre->esCirculo) {
        return figuraConNombre->figuraCirculo;
    }
    std::cerr << "La figura no es un circulo" << std::endl;
    exit(1);
}

//Dado un controlador de figuras y un nombre, retorna la figura de tipo rectangulo al nombre dado.
//Precond: existe una figura tipo rectangulo con el nombre dado.
sf::RectangleShape obtenerRectangulo(ManagementShape mSh, std::string nombre) {
    NodeSh figuraConNombre = figuraNodoConNombre(mSh,nombre);
    if(!figuraConNombre->esCirculo) {
        return figuraConNombre->figuraRectangulo;
    }
    std::cerr << "La figura no es un rectangulo" << std::endl;
    exit(1);
}

//Dado un controlador de figuras y un nombre, posiciona la figura de nombre "nombre" en la posicion que resulta 
// de sumar sus velocidades a su correspondientes coordenadas de su posicion actual. 
void actualizarPosicionConSuVelocidad(ManagementShape mSh, std::string nombre) {
    NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
    if(figuraDada->esCirculo) {
        sf::CircleShape circle = figuraDada->figuraCirculo;
        circle.setPosition(
            {circle.getPosition().x + figuraDada->velocidadX, circle.getPosition().y + figuraDada->velocidadY}
        );
        figuraDada->figuraCirculo = circle;
    } else {
        sf::RectangleShape rectangle = figuraDada->figuraRectangulo;
        rectangle.setPosition(
            {rectangle.getPosition().x + figuraDada->velocidadX, rectangle.getPosition().y + figuraDada->velocidadY}
        );
        figuraDada->figuraRectangulo = rectangle;
    }
}

//Dado un controlador de figuras y un nombre, posiciona la figura de nombre "nombre" en la posicion (0,0) (origen)
void actualizarPosicionAlOrigen(ManagementShape mSh, std::string nombre) {
    NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
    if(figuraDada->esCirculo) {
        sf::CircleShape circle = figuraDada->figuraCirculo;
        circle.setPosition({0.0f, 0.0f});
        figuraDada->figuraCirculo = circle;
    } else {
        sf::RectangleShape rectangle = figuraDada->figuraRectangulo;
        rectangle.setPosition({0.0f, 0.0f});
        figuraDada->figuraRectangulo = rectangle;
    }
}
//Dado un controlador de figuras, un nombre y una velocidadX, actualiza la velocidad Y de la figura dada.
void actualizarVelocidadX(ManagementShape mSh, std::string nombre, float velocidadX) {
    NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
    figuraDada->velocidadX = velocidadX;
}

//Dado un controlador de figuras, un nombre y una velocidadX, actualiza la velocidad X de la figura dada.
void actualizarVelocidadY(ManagementShape mSh, std::string nombre, float velocidadY) {
    NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
    figuraDada->velocidadY = velocidadY;
}

//Dado un controlador de figuras, un nombre y un valor de radio, aumenta el radio con "valorAAumentar" de la figura con nombre dado.
//Precond: Existe la figura con nombre dado y es un circulo

//Dado un controlador de figuras, un nombre y un valor a escalar, escala la figura con nombre dado "valorAEscalar" de veces.
void escalarFigura(ManagementShape mSh, std::string nombre, float valorAEscalar) {
    NodeSh figuraDada = figuraNodoConNombre(mSh,nombre);
    if(!figuraDada->esCirculo) {
        sf::RectangleShape nuevoRectangulo = figuraDada->figuraRectangulo;
        sf::Vector2f escalaRectangulo = nuevoRectangulo.getScale();
        nuevoRectangulo.setScale({nuevoRectangulo.getSize().x * valorAEscalar , nuevoRectangulo.getSize().y * valorAEscalar});
        figuraDada->figuraRectangulo = nuevoRectangulo;
    } else {
        sf::CircleShape nuevoCirculo = figuraDada->figuraCirculo;
        nuevoCirculo.setRadius(nuevoCirculo.getRadius() * valorAEscalar);
        figuraDada->figuraCirculo = nuevoCirculo;
    }
}

float escalaDe(ManagementShape mSh, std::string nombre) {
    NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
    return figuraDada->escala;
}

float* coloresDe(ManagementShape mSh, std::string nombre) {
    NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
    return figuraDada->colores;
}

void actualizarEscala(ManagementShape mSh, std::string nombre, float escalaNueva) {
    NodeSh figuraDada = figuraNodoConNombre(mSh, nombre);
    figuraDada->escala = escalaNueva;
}
//

//
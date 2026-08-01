#include <memory>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include "Shape.h"

int main(int argc, char *argv[])
{
    const int wWidth = 800;
    const int wHeight = 600;
    
    //{ elem1, elem2 } es un vector con dos elementos;como un conjunto.
    auto window = sf::RenderWindow(sf::VideoMode({wWidth, wHeight}), "Assignament 1");
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
    {
        std::printf("No se pudo inicializar la ventana");
        std::exit(1);
    }
    //Reloj
    sf::Clock clock;
    ImGui::GetStyle().ScaleAllSizes(1.0f);
    ImGui::GetIO().FontGlobalScale = 1.0f;

    //Inicializando figuras con sus caracteristicas.
    sf::Vector2f vec2 = {20.0, 10.0};
    ManagementShape controladorFiguras = crearControlador();
    
    //########Circulo AZul############
    float c[3] = {0.0f, 1.0f, 1.0f};
    //circleB->colores = {0.0f, 1.0f, 1.0f};
    agregarCirculo(controladorFiguras,20.0f,10.0f,"CBlue",1.0f,0.5f,1.0f,10.0f,10.0f);
    
    //########Circulo Purpura############
    agregarCirculo(controladorFiguras,50.0f,10.0f,"CPurple",0.1f,0.6f,1.0f,100.0f,200.0f);
    
    //########Circulo Verde############
    agregarCirculo(controladorFiguras,100.0f,10.0f,"CGreen",1.0f,0.5f,0.8f,60.0f,445.0f);

     //########Rectangulo Fuxia azul############
    agregarRectangulo(controladorFiguras,20.0f,10.0f,"RTail",1.0f,0.4f,300.0f,500.0f);
    
    //########Rectangulo Rojo############
    agregarRectangulo(controladorFiguras,20.0f,10.0f,"RRed",0.7f,0.7f,150.0f,450.0f);
    
    //########Rectangulo Verde############
    agregarRectangulo(controladorFiguras,20.0f,10.0f,"RGray",0.6f,0.6f,200.0f,335.5f);

    //Variables interactivas con interfaz ImGui de figura actual elegida.
    float radiusFigureSelected = 50;
    int circleSegments = 32;
    float shapeSpeedX = 0.0f;
    float shapeSpeedY = 0.0f;
    bool drawText = true;
    bool drawShape = true;

    //Manejo de Fuente de Texto
    sf::Font myFont;
    if (!myFont.openFromFile("./src/fonts/Dudu_Calligraphy.ttf"))
    {
        std::printf("No se pudo leer la fuente");
        std::exit(1);
    }
    sf::Text text(myFont, "Esto es genial", 24);

    text.setPosition({0, 500 - (float)text.getCharacterSize()});

    char displayString[255] = "Intentando...";

    //Loop Infito Ventana
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                std::cout << "CodigoTecla=" << int(keyPressed->scancode) << std::endl;

                if (keyPressed->scancode == sf::Keyboard::Scancode::X)
                {
                    shapeSpeedX *= -1.0f;
                }
            }
        }

        ImGui::SFML::Update(window, clock.restart());

        ImGui::Begin("Propiedades De Las Figuras");

        // Version de opciones con tamaño fijo.
        const char* shapesCombo[] = {"CGreen", "CBlue", "CPurple","RRed","RGray", "RTail"};
        static int indexShapeSelected = 0;
        //ShapeStr* shapes[] = {circleG,circleB, circleP,rectR, rectG,rectT};
        ImGui::Combo("Shapes", &indexShapeSelected, shapesCombo, IM_ARRAYSIZE(shapesCombo));
        
        //Actualizo la referencia de ImGui con las velocidades de la figura seleccionada actual.
        shapeSpeedX = obtenerVelocidadXDe(controladorFiguras,shapesCombo[indexShapeSelected]);
        shapeSpeedY = obtenerVelocidadYDe(controladorFiguras,shapesCombo[indexShapeSelected]);
        
        //Dibujar Figura
        if(ImGui::Checkbox("Dibujar Figura", &drawShape)) {
            actualizarDibujadoDe(controladorFiguras,shapesCombo[indexShapeSelected], drawShape);
        };
        ImGui::SameLine();
        
        //Dibujar Texto
        ImGui::Checkbox("Dibujar Texto", &drawText);
        
        //Velocidades Figura Actual
        ImGui::SliderFloat("VelocidadX",&shapeSpeedX, -10.0f, 10.0f);
        ImGui::SliderFloat("VelocidadY",&shapeSpeedY, -10.0f, 10.0f);

        //Escalar Figura Actual
        //ImGui::SliderFloat("Escala", &shapes[indexShapeSelected]->radio, 0.0f, 300.0f);
        
        //Cambiar Colores de Figura Actual
        ImGui::ColorEdit3("Color del circulo", c);
        
        //Cambiar Texto Ingresado
        ImGui::InputText("Texto", displayString, 255);
        if (ImGui::Button("Setear texto nuevo"))
        {
            text.setString(displayString);
        }
        ImGui::SameLine();
        
        //Posicionar Figura en el origen
        if (ImGui::Button("Resetear Posicion Inicial Figura"))
        {
            sf::Vector2f origin(0.0f,0.0f);
            if(esCirculo(controladorFiguras,shapesCombo[indexShapeSelected])) 
            {
                actualizarPosicionAlOrigen(controladorFiguras,shapesCombo[indexShapeSelected]);
            } else {
                actualizarPosicionAlOrigen(controladorFiguras, shapesCombo[indexShapeSelected]);
            }
        }
        ImGui::End();

        //Actualizar Inputs de ImGui para Figura Actual
        if(esCirculo(controladorFiguras,shapesCombo[indexShapeSelected])) {
            sf::CircleShape circleActual = obtenerCirculo(controladorFiguras,shapesCombo[indexShapeSelected]);
            circleActual.setRadius(radiusFigureSelected);
            circleActual.setFillColor(sf::Color(uint8_t(c[0] * 255), uint8_t(c[1] * 255), uint8_t(c[2] * 255)));
        } else {
            sf::RectangleShape rectangleActual = obtenerRectangulo(controladorFiguras,shapesCombo[indexShapeSelected]);
            rectangleActual.setFillColor(sf::Color(uint8_t(c[0] * 255), uint8_t(c[1] * 255), uint8_t(c[2] * 255)));
        }

        actualizarVelocidadX(controladorFiguras,shapesCombo[indexShapeSelected],shapeSpeedX);
        actualizarVelocidadY(controladorFiguras,shapesCombo[indexShapeSelected],shapeSpeedY);
        
        //Cambiar direccion si tocan el borde
        for (int i = 0; i < IM_ARRAYSIZE(shapesCombo); i++) 
        {
            std::string figuraActual = shapesCombo[i];
            if(esCirculo(controladorFiguras,figuraActual)) {
                sf::CircleShape circleActual = obtenerCirculo(controladorFiguras,figuraActual);
                if(circleActual.getGlobalBounds().position.x < 0.0f ||
                    circleActual.getGlobalBounds().position.x > wWidth) 
                {
                        invertirVelocidadXDe(controladorFiguras,figuraActual);
                }
                if(circleActual.getGlobalBounds().position.y < 0.0f ||
                    circleActual.getGlobalBounds().position.y > wHeight) 
                {
                        invertirVelocidadYDe(controladorFiguras,figuraActual);
                }

            } else {
                sf::RectangleShape rectangleActual = obtenerRectangulo(controladorFiguras,figuraActual);
                if(rectangleActual.getGlobalBounds().position.x < 0.0f ||
                    rectangleActual.getGlobalBounds().position.x > wWidth) 
                {
                        invertirVelocidadXDe(controladorFiguras,figuraActual);
                }
                if(rectangleActual.getGlobalBounds().position.y < 0.0f ||
                    rectangleActual.getGlobalBounds().position.y > wHeight) 
                {
                        invertirVelocidadYDe(controladorFiguras,figuraActual);
                }
            }
        }
        
        //Actualizar posiciones segun su velocidad.
        actualizarPosicionConSuVelocidad(controladorFiguras,"CBlue");
        actualizarPosicionConSuVelocidad(controladorFiguras, "CPurple");
        actualizarPosicionConSuVelocidad(controladorFiguras, "CGreen");
        actualizarPosicionConSuVelocidad(controladorFiguras, "RTail");
        actualizarPosicionConSuVelocidad(controladorFiguras, "RRed");
        actualizarPosicionConSuVelocidad(controladorFiguras, "RGray");

        //Renderizado
        window.clear();

        //Si en este frame se cambio que se dibuje la figura seleccionada, entonces lo cambio.
        for(int i = 0; i < IM_ARRAYSIZE(shapesCombo); i++) 
        {
            std::string figuraActual = shapesCombo[i];
            if(esVisible(controladorFiguras,figuraActual)) {
                if(esCirculo(controladorFiguras, figuraActual)) {
                    window.draw(obtenerCirculo(controladorFiguras,figuraActual));
                } else {
                    window.draw(obtenerRectangulo(controladorFiguras,figuraActual));
                }
            }
        }
        if (drawText)
        {
            window.draw(text);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

/* Anotaciones
    // el color de imgui requiere flotanes en rango 0-1   
    // sfml requiere uint8_t por lo que el rango es 0-255
    // esta conversion para representar los colores, es la cuestion mas "pesada" de el cross-over
    // entre ambas librerias
*/
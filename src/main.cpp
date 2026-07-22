#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#define CANTIDADCOLORES 3

struct ShapeStr {
    sf::CircleShape figuraCirculo;
    sf::RectangleShape figuraRectangulo;
    std::string nombre;
    float colores[CANTIDADCOLORES];
    float velocidadX;
    float velocidadY;
    float radio;
    bool estaActiva;
};

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
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

    //Inicializando figuras con sus caracteristicas.
    sf::Vector2f vec2 = {20.0, 10.0};
    ShapeStr* circleB = new ShapeStr;
    ShapeStr* circleP = new ShapeStr;
    ShapeStr* circleG = new ShapeStr;
    ShapeStr* rectR = new ShapeStr;
    ShapeStr* rectG = new ShapeStr;
    ShapeStr* rectT = new ShapeStr;
    
    //########Circulo AZul############
    float c[3] = {0.0f, 1.0f, 1.0f};
    circleB->nombre = "CBlue";
    //circleB->colores = {0.0f, 1.0f, 1.0f};
    circleB->figuraCirculo = sf::CircleShape(20.0f, 10.0f);
    circleB->figuraCirculo.setPosition({10.0f, 10.0f});
    circleB->velocidadX = 1.0f;
    circleB->velocidadY = 0.5f;
    circleB->estaActiva = true;

    //########Circulo Purpura############
    circleP->nombre = "CPurple";
    //float c[3] = {0.0f, 1.0f, 1.0f};
    //circleB->colores = {0.0f, 1.0f, 1.0f};
    circleP->figuraCirculo = sf::CircleShape(50.0f, 10.0f);;
    circleP->figuraCirculo.setPosition({100.0f, 200.0f});
    circleP->velocidadX = 0.1f;
    circleP->velocidadY = 0.6f;
    circleP->estaActiva = true;

    //########Circulo Verde############
    circleG->nombre = "CGreen";
    //float c[3] = {0.0f, 1.0f, 1.0f};
    //circleB->colores = {0.0f, 1.0f, 1.0f};
    circleG->figuraCirculo = sf::CircleShape(100.0f, 10.0f);
    circleG->figuraCirculo.setPosition({60.0f, 445.0f});
    circleG->velocidadX = 0.5f;
    circleG->velocidadY = 0.8f;
    circleG->estaActiva = true;

    //########Rectangulo Fuxia azul############
    rectT->nombre = "RTeal";
    rectT->figuraRectangulo = sf::RectangleShape(vec2);
    //float c[3] = {0.0f, 1.0f, 1.0f};
    //circleB->colores = {0.0f, 1.0f, 1.0f};
    rectT->figuraRectangulo.setPosition({300.0f, 500.0f});
    rectT->velocidadX = 1.0f;
    rectT->velocidadY = 0.4f;
    rectT->estaActiva = true;

    //########Rectangulo Rojo############
    rectR->nombre = "RRed";
    rectR->figuraRectangulo = sf::RectangleShape(vec2);
    //float c[3] = {0.0f, 1.0f, 1.0f};
    //circleB->colores = {0.0f, 1.0f, 1.0f};
    rectR->figuraRectangulo.setPosition({150.0f, 450.0f});
    rectR->velocidadX = 0.7f;
    rectR->velocidadY = 0.7f;
    rectR->estaActiva = true;

    //########Rectangulo Verde############
    rectG->nombre = "RGreen";
    rectG->figuraRectangulo = sf::RectangleShape(vec2);
    //float c[3] = {0.0f, 1.0f, 1.0f};
    //circleB->colores = {0.0f, 1.0f, 1.0f};
    rectG->figuraRectangulo.setPosition({200.0f, 335.5f});
    rectG->velocidadX = 0.6f;
    rectG->velocidadY = 0.6f;
    rectG->estaActiva = true;

    float radiusFigureSelected = 50;
    int circleSegments = 32;
    float shapeSpeedX = 1.0f;
    float shapeSpeedY = 0.5f;
    bool drawText = true;

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
        ShapeStr* shapes[] = {circleG,circleB, circleP,rectR, rectG,rectT};
        ImGui::Combo("Shapes", &indexShapeSelected, shapesCombo, IM_ARRAYSIZE(shapesCombo));
        
        //Dibujar Figura
        ImGui::Checkbox("Dibujar Figura", &shapes[indexShapeSelected]->estaActiva);
        ImGui::SameLine();
        
        //Dibujar Texto
        ImGui::Checkbox("Dibujar Texto", &drawText);
        
        //Escalar Figura Actual
        ImGui::SliderFloat("Escala", &shapes[indexShapeSelected]->radio, 0.0f, 300.0f);
        
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
            //const sf::Shape* shapeActual = shapes[indexShapeSelected];
        }
        ImGui::End();

        //Actualizar Inputs de ImGui para Figura Actual
        shapes[indexShapeSelected]->figuraCirculo.setRadius(shapes[indexShapeSelected]->radio);
        shapes[indexShapeSelected]->figuraCirculo.setFillColor(sf::Color(uint8_t(c[0] * 255), uint8_t(c[1] * 255), uint8_t(c[2] * 255)));

        //Cambiar direccion si tocan el borde
        for (int i = 0; i < IM_ARRAYSIZE(shapes); i++) 
        {
            if(i <= 2) {
                if (shapes[i]->figuraCirculo.getGlobalBounds().position.x < 0 ||
                    shapes[i]->figuraCirculo.getGlobalBounds().position.x > wWidth)
                {
                    shapes[i]->velocidadX *= -1;
                }
                if (shapes[i]->figuraCirculo.getGlobalBounds().position.y < 0 ||
                    shapes[i]->figuraCirculo.getGlobalBounds().position.y > wHeight)
                {
                    shapes[i]->velocidadY *= -1;
                }
            } else {
                if (shapes[i]->figuraRectangulo.getGlobalBounds().position.x < 0 ||
                    shapes[i]->figuraRectangulo.getGlobalBounds().position.x > wWidth)
                {
                    shapes[i]->velocidadX *= -1;
                }
                if (shapes[i]->figuraRectangulo.getGlobalBounds().position.y < 0 ||
                    shapes[i]->figuraRectangulo.getGlobalBounds().position.y > wHeight)
                {
                    shapes[i]->velocidadY *= -1;
                }
            }
        }

        //Actualizar posiciones segun su velocidad.
        circleB->figuraCirculo.setPosition({
            circleB->figuraCirculo.getPosition().x + circleB->velocidadX, 
            circleB->figuraCirculo.getPosition().y + circleB->velocidadY
        });
        circleP->figuraCirculo.setPosition({
            circleP->figuraCirculo.getPosition().x + circleG->velocidadX,
            circleP->figuraCirculo.getPosition().y + circleG->velocidadY
        });
        circleG->figuraCirculo.setPosition({
            circleG->figuraCirculo.getPosition().x + circleG->velocidadX,
            circleG->figuraCirculo.getPosition().y + circleG->velocidadY
        });
        rectR->figuraRectangulo.setPosition({
            rectR->figuraRectangulo.getPosition().x + rectR->velocidadX,
            rectR->figuraRectangulo.getPosition().y + rectR->velocidadY
        });
        rectT->figuraRectangulo.setPosition({
            rectT->figuraRectangulo.getPosition().x + rectT->velocidadX,
            rectT->figuraRectangulo.getPosition().y + rectT->velocidadY
        });
        rectG->figuraRectangulo.setPosition({
            rectG->figuraRectangulo.getPosition().x + rectG->velocidadX,
            rectG->figuraRectangulo.getPosition().y + rectG->velocidadY
        });
        
        //Renderizado
        window.clear();
        for(int i = 0; i < IM_ARRAYSIZE(shapes); i++) {
            if(i <= 2) {
                if(shapes[i]->estaActiva) {
                    window.draw(shapes[i]->figuraCirculo);
                }
            } else {
                if(shapes[i]->estaActiva) {
                    window.draw(shapes[i]->figuraRectangulo);
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
#include <print>
#include <memory>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

int main(int argc, char* argv[])
{

    const int wWidth = 800;
    const int wHeight = 600;

    //{ elem1, elem2 } es un vector con dos elementos;como un conjunto.
    auto window = sf::RenderWindow(sf::VideoMode({wWidth, wHeight}), "CMake SFML Project");
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window)) {
        std::printf("No se pudo inicializar la ventana");
        std::exit(1);
    }

    sf::Clock clock;
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;
    
    // el color de imgui requiere flotanes en rango 0-1
    // sfml requiere uint8_t por lo que el rango es 0-255
    // esta conversion para representar los colores, es la cuestion mas "pesada" de el cross-over
    // entre ambas librerias
    float c[3] = {0.0f, 1.0f, 1.0f}; 
    
    float circleRadius = 50;
    int circleSegments = 32;
    float circleSpeedX = 1.0f;
    float circleSpeedY = 0.5f;
    bool drawCircle = true;
    bool drawText = true;

    sf::CircleShape circle(circleRadius,circleSegments);
    circle.setPosition({10.0f, 10.0f});

    sf::Font myFont;

    if(!myFont.openFromFile("./src/fonts/Dudu_Calligraphy.ttf")) 
    {
        std::printf("No se pudo leer la fuente");
        std::exit(1);
    }

    sf::Text text(myFont,"Esto es genial",24);

    text.setPosition({0, 500 - (float)text.getCharacterSize()});

    char displayString[255] = "Esto es genial";

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                std::printf("Tecla presionada con codigo = ", int(keyPressed->scancode));

                if(keyPressed->scancode == sf::Keyboard::Scancode::X) 
                {
                    circleSpeedX *= -1.0f;
                }
            }

        }

        ImGui::SFML::Update(window, clock.restart());

        ImGui::Begin("Iniciando el mundo");
        ImGui::Checkbox("Dibujar Circulo", &drawCircle);
        ImGui::SameLine();
        ImGui::Checkbox("Dibujar Texto", &drawText);
        ImGui::SliderFloat("Radio", &circleRadius, 0.0f, 300.0f);
        ImGui::SliderInt("Tamaño",&circleSegments, 3, 64);
        ImGui::ColorEdit3("Color del circulo", c);
        ImGui::InputText("Texto", displayString,255);
        if(ImGui::Button("Setear texto nuevo")) 
        {
            text.setString(displayString);
        }
        ImGui::SameLine();
        if(ImGui::Button("Resetear circulo"))
        {
            circle.setPosition({0,0});
        }
        ImGui::End();

        circle.setPointCount(circleSegments);
        circle.setRadius(circleRadius);
        
        circle.setFillColor(sf::Color(uint8_t(c[0]*255),uint8_t(c[1]*255),uint8_t(c[2]*255)));

        circle.setPosition({circle.getPosition().x + circleSpeedX, circle.getPosition().y + circleSpeedY });

        window.clear();
        if(drawCircle) 
        {
            window.draw(circle);
        }
        if(drawText) 
        {
            window.draw(text);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

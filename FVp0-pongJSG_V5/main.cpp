#include <SFML/Graphics.hpp>
#include <iostream>

#define kVel 5

int main()
{
    int anchoJuego = 640;
    int altoJuego = 480;
    int radio = 14;
    int palaLargo = 119, palaAncho=26; 
   //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(anchoJuego, altoJuego), "P0. Fundamentos de los Videojuegos. DCCIA");
    // sincronizamos la frecuencia de la ventana con la del monitor
    window.setVerticalSyncEnabled(true);
    
    int x = 1, y = 1;
    int xincremento = 3, yincremento = 3;
    int pared_izq = 0, pared_der = anchoJuego;
    int techo = 70, piso = 410;

    //Cargo la imagen donde reside la textura del sprite
    sf::Texture texJ1;
    sf::Texture texJ2;
    sf::Texture texbola;
    sf::Texture texmarcador;
    sf::Texture fondo;
    
    if (!texJ1.loadFromFile("resources/J1.png") ||!fondo.loadFromFile("resources/fondo.png")
            || !texJ2.loadFromFile("resources/J2.png")||!texmarcador.loadFromFile("resources/marcador.png")
            ||!texbola.loadFromFile("resources/bola.png"))
               
    {
        std::cerr << "Error cargando los sprites !!!";
        exit(0);
    }
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite(texJ1);
    sf::Sprite sprite2(texJ2);
    sf::Sprite spriteFondo(fondo);
    sf::Sprite spriteMarcador(texmarcador);
    sf::Sprite spriteBola(texbola);
    
    /* PLAYER 1 */
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(26/2,119/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0*26, 0*119, 26, 119));
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(600, 240);

    /* PLAYER 2 */
    //Le pongo el centroide donde corresponde
    sprite2.setOrigin(26/2,119/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite2.setTextureRect(sf::IntRect(0*26, 0*119, 26, 119));
    sprite2.setColor(sf::Color(0,255,0));
    // Lo dispongo en el centro de la pantalla
    sprite2.setPosition(40, 240);
    
    /*FONDO*/
    //Le pongo el centroide donde corresponde
    spriteFondo.setOrigin(0,0);
    //Cojo el sprite que me interesa por defecto del sheet
    spriteFondo.setTextureRect(sf::IntRect(0, 0, 640, 480));
    // Lo dispongo en el centro de la pantalla
    spriteFondo.setPosition(0, 0);
    
    /*MARCADOR*/
    //Le pongo el centroide donde corresponde
    spriteMarcador.setOrigin(0,0);
    //Cojo el sprite que me interesa por defecto del sheet
    spriteMarcador.setTextureRect(sf::IntRect(0, 0, 544, 54));
    // Lo dispongo en el centro de la pantalla
    spriteMarcador.setPosition(50, 8);
    
    /* BOLA */
    //Le pongo el centroide donde corresponde
    spriteBola.setOrigin(28/2, 29/2);
    //Cojo el sprite que me interesa por defecto del sheet
    spriteBola.setTextureRect(sf::IntRect(0*28, 0*29, 28, 29));
    spriteBola.setColor(sf::Color(255,255,0));
    // Lo dispongo en el centro de la pantalla
    spriteBola.setPosition(anchoJuego/2, altoJuego/2);
    
    

    // ejecutar el programa mientras la ventana esté abierta
    while (window.isOpen())
    {
        
        // limpiamos la ventana con el color negro
        window.clear(sf::Color::Black);
        // verificamos los bordes de la ventana y cambiamos
        // el signo del incremento de x,y
        if (x <= pared_izq+radio) 
             xincremento = abs(xincremento);
        if (x >= pared_der-radio)
            xincremento =-xincremento;
        if (y <= techo+radio)
            yincremento = abs(yincremento);
        if (y >= piso-radio)
            yincremento =-yincremento;
        x = x + xincremento;
        y = y + yincremento;
        //pasamos las nuevas coordenadas al objeto circulo1
        spriteBola.setPosition(x,y);
        // JUGADOR BOSS
        if(y >= techo+palaLargo/2 && y <= piso-palaLargo/2){                  
            for(int i = 0; i<=y;i++){
                sprite2.setPosition(40,i);
            }
        }
        //verificamos todos los eventos de la ventana 
        sf::Event evento;
        while (window.pollEvent(evento))
        {
            switch(evento.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                // para cuando esta parado
                case sf::Event::KeyReleased:
                /*    sprite.setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
                    sprite.setScale(-1,1);
                    sprite2.setTextureRect(sf::IntRect(5.5*75, 3*75, 75, 75));
                    sprite2.setScale(-1,1);
                 */
                break;
                
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(evento.key.code) {
                        
                        //Mapeo del cursor
                        case sf::Keyboard::Up:
                            sprite.setTextureRect(sf::IntRect(0*26, 0*119, 26, 119));
                            if(sprite.getPosition().y >= techo+palaLargo/2+5){
                                sprite.move(0,-kVel);
                            }
                             
                        break;
                        
                        case sf::Keyboard::Down:
                            sprite.setTextureRect(sf::IntRect(0*26, 0*119, 26, 119));
                            
                            if(sprite.getPosition().y <= piso-palaLargo/2-5){
                                sprite.move(0,kVel);
                            }
                              
                        break;
                        
                                                
                        
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << evento.key.code << std::endl;
                        break;
                              
                    }
                

            }
        }

        
        
        window.clear();
        window.draw(spriteBola);
        window.draw(spriteFondo);
        window.draw(spriteMarcador);
        window.draw(sprite);
        window.draw(sprite2);
        
        // mostramos ventana en la pantalla
        window.display();

    }

    return 0;
}

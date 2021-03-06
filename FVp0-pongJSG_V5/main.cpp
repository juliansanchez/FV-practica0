#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// velocidades de las palas
#define kVel 10

int main()
{
    // dimensiones del juego
    int anchoJuego = 640;
    int altoJuego = 480;
    // dimensiones de objetos para colisiones
    int radio = 14;
    int palaLargo = 120, palaAncho=26; 
    
   //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(anchoJuego, altoJuego), "P0-PONG! JSG");
    // sincronizamos la frecuencia de la ventana con la del monitor
    window.setVerticalSyncEnabled(true);
    
    // incrementos de la bola
    int x = 1, y = 1;
    int xincremento = 4, yincremento = 4;
    // limites de la ventana para colisiones
    int pared_izq = 0, pared_der = anchoJuego;
    int techo = 70, piso = 410;
    
    // variables para contadores
    int vidasJ1 = 3;
    int vidasJ2 = 3;
    int toques = 0;
    
    // cargamo sla fuente para los textos
    sf::Font fuente;
    if (!fuente.loadFromFile("resources/fuente.ttf")){
        std::cerr << "Error cargando la fuente";
        exit(0);
    }    
    
    // Creamos los objetos texto
    // TEXTO PARA LA PAUSA
    sf::Text textoPausa("Pulsa espacio para comenzar!", fuente);
    textoPausa.setCharacterSize(30);
    textoPausa.setStyle(sf::Text::Regular);
    textoPausa.setPosition(anchoJuego/2,20);
    textoPausa.setColor(sf::Color::White);
  
    
    // puntuacion 
    sf::Text beats;
    beats.setFont(fuente);
    beats.setCharacterSize(30);
    beats.setPosition(anchoJuego/2,70);
    beats.setColor(sf::Color::White);
    
    // vidas usuario
    sf::Text vida1;
    vida1.setFont(fuente);
    vida1.setPosition(40,70);
    vida1.setColor(sf::Color(255,255,255));
    
    // vidas boss
    sf::Text vida2;
    vida2.setFont(fuente);
    vida2.setPosition(240,70);
    vida2.setColor(sf::Color(255,255,255));

    
    // cargamos las texturas para los objetos
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
    
    
    // creamos los sprites o elementos
    sf::Sprite sprite(texJ1);
    sf::Sprite sprite2(texJ2);
    sf::Sprite spriteFondo(fondo);
    sf::Sprite spriteMarcador(texmarcador);
    sf::Sprite spriteBola(texbola);
    
         /* PLAYER 1 */
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(palaAncho/2,palaLargo/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0*palaAncho, 0*palaLargo, palaAncho, palaLargo));
    // Lo dispongo en la pantalla
    sprite.setPosition(600, 240);
    

    /* PLAYER 2 */
    //Le pongo el centroide donde corresponde
    sprite2.setOrigin(palaAncho/2,palaLargo/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite2.setTextureRect(sf::IntRect(0*palaAncho, 0*palaLargo, palaAncho, palaLargo));
    // Lo dispongo en la pantalla
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
   
    
    // diferenciar pantalla juego y pausa
    bool isPlaying = false;
    
    /*******************************/
    // ejecutar el programa mientras la ventana esté abierta
    while (window.isOpen())
    {         
        // limpiamos la ventana con el color negro
        window.clear(sf::Color::Black);
        // verificamos los bordes de la ventana y cambiamos
        // el signo del incremento de x,y
        
        // Control de rebote en pantalla
        if (x <= pared_izq+radio)
            xincremento = abs(xincremento);
        if (x >= pared_der-radio)
            xincremento =-xincremento;
        if (y <= techo+radio)
            yincremento = abs(yincremento);
        if (y >= piso-radio)
            yincremento =-yincremento;
              
        
        // rebote BOSS
        if (x <= sprite2.getPosition().x+palaAncho) 
             xincremento = abs(xincremento);
               
        // si toca La pared DCHA, pierde punto
        if (x >= pared_der-radio){          
            vidasJ1--;
            toques = 0;
            x = anchoJuego/2;
            y = altoJuego/2;
            
            cout<<"Vidas: "<<vidasJ1<<endl;
            cout<<"Punto perdido"<<endl;
            
            if(vidasJ1 == 0){
                cout<<"Game Over"<<endl;
                isPlaying=false;          
            }
            
        }
        
       // REBOTE J1 
       if (x+radio >= sprite.getPosition().x-palaAncho/2
               && y<sprite.getPosition().y+palaLargo/2
               && y> sprite.getPosition().y-palaLargo/2){
           
            xincremento =-xincremento;
            toques++;
            cout<<toques<<endl;
        }
            
        
        // comienza el juego
        if(isPlaying){
            // actualizo valores
            x = x + xincremento;
            y = y + yincremento;
            spriteBola.setPosition(x,y);
            
            // JUGADOR BOSS
            if(y >= techo+palaLargo/2 && y <= piso-palaLargo/2){                  
                for(int i = 0; i<=y;i++){
                    sprite2.setPosition(40,i);
                }
            }
        }
       
        //verificamos todos los eventos de la ventana 
        sf::Event evento;
        while (window.pollEvent(evento))
        {
            if ((evento.type == sf::Event::KeyPressed) && (evento.key.code == sf::Keyboard::Escape)){
                            window.close();
                }
            // Space key pressed: play
                if ((evento.type == sf::Event::KeyPressed) && (evento.key.code == sf::Keyboard::Space))
                {
                    if (!isPlaying)
                    {
                        // reiniciamos posiciones de los objetos
                        spriteBola.setPosition(anchoJuego/2, altoJuego/2);
                        sprite.setPosition(600, 240);
                        sprite2.setPosition(40, 240);
                        spriteFondo.setPosition(0, 0);
                        spriteMarcador.setPosition(50, 8);
                        
                        // reiniciamos los contadores 
                        vidasJ1=3;
                        vidasJ2=3;
                        toques=0;
                        
                        // (re)start the game
                        isPlaying = true;
                    }
                } 
            if(isPlaying){
                
                switch(evento.type){
                
                    //Si se recibe el evento de cerrar la ventana la cierro
                    case sf::Event::Closed:
                        window.close();
                        break;
             
                    //Se pulsó una tecla, imprimo su codigo
                    case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(evento.key.code) {
                        
                        //Mapeo del cursor
                        case sf::Keyboard::Up:                           
                            if(sprite.getPosition().y >= techo+palaLargo/2+5){
                                sprite.move(0,-kVel);
                            }                            
                        break;
                        
                        case sf::Keyboard::Down:                                                
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
        }
        // refrescamos la pantalla
        window.clear();
        
        // si estamos jugando mostramos los objetos
        if(isPlaying){
                
            // std::string v1 = std::to_string(vidasJ1);
            // vida1.setString(v1);
            
            // std::string v2 = std::to_string(vidasJ2);
            // vida2.setString(v2);
            
            // std::string m = std::to_string(toques);
            // beats.setString(m);
           
            // beats.setString(to_string(toques));

            window.draw(beats); // no funciona mostrar
            window.draw(vida1); // no funciona mostrar
            window.draw(vida2); // no funciona mostrar
            
            window.draw(spriteBola);
            window.draw(spriteFondo);
            window.draw(spriteMarcador);
            window.draw(sprite);
            window.draw(sprite2);            
        }
        else{
            // Mensaje de PAUSA
            window.draw(textoPausa); 
        }
        // mostramos ventana en la pantalla
        window.display();
    }

    return 0;
}

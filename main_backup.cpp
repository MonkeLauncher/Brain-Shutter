#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Useful Functions.h"

using namespace sf;
using namespace std;


RenderWindow okno(VideoMode (1920, 1080), "wygaszacz mózgu", sf::Style::Fullscreen);
Event zdazenie;

Clock afk();


class prostokomt {
	public:
		RectangleShape duch;
		double speedX, speedY;
		
		prostokomt (double speetX, double speetY) 
		: speedX (speetX), speedY(speetY) 
		{
	    	duch.setSize (Vector2f (120, 120));
	    	duch.setOutlineThickness (5);
	    	duch.setFillColor (Color (0, 0, 0, 0));
	    	duch.setOutlineColor (Color (rand() % 256, rand() % 256, rand() % 256));
	    	
	    	duch.setPosition (rand() % (okno.getSize().x - 130), rand() % (okno.getSize().y - 130));
		}
		
};



int main () {
	
	
	srand(clock());
	okno.setFramerateLimit(60);
	okno.setPosition (Vector2i (-10, 0));
	okno.setVerticalSyncEnabled (true);
    
    
    
    // robienie prostokomtów
    vector <prostokomt> pros;
    
    int a = rand () % 10 - 5;
	int b = rand () % 10 - 5;
	pros.emplace_back (b, a);
    
    
    
    //pêtla programu
    while (okno.isOpen()) {

        // zamykanie okna
        while (okno.pollEvent(zdazenie)) {
            if (zdazenie.type == zdazenie.Closed || KPR (Keyboard::Escape)) okno.close(); 
            
            // nowy Duch
            if (zdazenie.key.code == Keyboard::Space && Keyboard::isKeyPressed (Keyboard::Space)) {
		    	int a = rand () % 10 - 5;
		    	int b = rand () % 10 - 5;
		    	pros.emplace_back (b, a);
			}
        }
        
        
        // r¹czkowanie duchów
        for (int i = 0; i < pros.size(); i++) {
        	pros[i].duch.move (pros[i].speedX, pros[i].speedY);
        }
        
        for (int i = 0; i < pros.size(); i++) {        	
        	
        	// kolizje ze œcian¹
        	if (pros[i].duch.getPosition().x <= pros[i].duch.getOutlineThickness()) pros[i].speedX = -(pros[i].speedX);
        	if (pros[i].duch.getPosition().y <= pros[i].duch.getOutlineThickness()) pros[i].speedY = -(pros[i].speedY);
        	
        	if (pros[i].duch.getPosition().x + pros[i].duch.getSize().x + pros[i].duch.getOutlineThickness() >= okno.getSize().x) pros[i].speedX = -(pros[i].speedX);
        	if (pros[i].duch.getPosition().y + pros[i].duch.getSize().y + pros[i].duch.getOutlineThickness() >= okno.getSize().y) pros[i].speedY = -(pros[i].speedY);
        	
        	int iCenter[2] = {pros[i].duch.getPosition().x + 60, pros[i].duch.getPosition().y + 60};
        	
        	
        	// kolizje ze sob¹
        	for (int j = i + 1; j < pros.size(); j++) {        		
				int jCenter[2] = {pros[j].duch.getPosition().x + 60, pros[j].duch.getPosition().y + 60};
				
				int xDis = abs(iCenter[0] - jCenter[0]);
				int yDis = abs(iCenter[1] - jCenter[1]);
				if (xDis > 130 || yDis > 130) continue;
				
				if (xDis > yDis) {
					int a = pros[i].speedX;
					pros[i].speedX = pros[j].speedX;
					pros[j].speedX = a;
				}
				else {
					int a = pros[i].speedY;
					pros[i].speedY = pros[j].speedY;
					pros[j].speedY = a;
				}
			}
		}
        
        
        okno.clear(Color (0, 0, 0, 0));
        
        // rysowanie wszystkiego
        for (int i = 0; i < pros.size(); i++) {
        	okno.draw (pros[i].duch);
		}

        okno.display();
    }
}

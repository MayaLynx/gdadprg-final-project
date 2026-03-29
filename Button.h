#pragma once

#include "GameObject.h"
#include "GameResource.h"

class Button: public GameObject{
	public:
		Button(std::string name,std::string textVal);
		~Button();
		void init();
        void update(sf::Time deltaTime);
        void draw(sf::RenderWindow *window);
		
		void setPosition(float x,float y);
		void setSize(float width,float height);
		void setText(std::string value);
		
		void setBlinkTime(float blinkTime);
		void toggleSelected();
		bool isSelected();
	private:
		sf::RectangleShape* rec;
		sf::Text* text;
		sf::Font font;
		bool selected;
		float blinkTime;
		sf::Time elapsedTime;
};

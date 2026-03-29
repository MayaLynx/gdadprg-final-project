#include "Button.h"

Button::Button(std::string name,std::string textVal):
    	GameObject(name){
    selected = false;
    elapsedTime = sf::Time::Zero;
    blinkTime = 1.f;
    
    rec = new sf::RectangleShape();
    rec->setFillColor(sf::Color::White);
    rec->setOutlineColor(sf::Color::Black);
    rec->setOutlineThickness(5);
    if(font.openFromFile("Assets\\Silver.ttf")){
        text = new sf::Text(font);
        text->setString(textVal);
        text->setFillColor(sf::Color::Black);
        text->setCharacterSize(40);
    }
}

Button::~Button(){
    delete rec;
    delete text;
}

void Button::init(){}
void Button::update(sf::Time deltaTime){
    if(!selected) return;
    elapsedTime += deltaTime;
    if(elapsedTime.asSeconds()>=blinkTime){
        elapsedTime = sf::Time::Zero;
        if(rec->getOutlineColor() == sf::Color::Yellow)
            rec->setOutlineColor(sf::Color::Black);
        else
            rec->setOutlineColor(sf::Color::Yellow);
    }
}

void Button::draw(sf::RenderWindow *window){
    window->draw(*rec);
    window->draw(*text);
}
		
void Button::setPosition(float x,float y){
    rec->setPosition({x,y});
    text->setPosition({x,y});
}
		
void Button::setSize(float width,float height){
    rec->setSize({width,height});
    sf::Vector2f pos = rec->getPosition();
    text->setPosition({pos.x+width*0.1f,pos.y});
}

void Button::setText(std::string value){
    text->setString(value);
}

void Button::setBlinkTime(float blinkTime){
    this->blinkTime=blinkTime;
}

void Button::toggleSelected(){ 
    selected = !selected;
	elapsedTime = sf::Time::Zero;
	if(selected) rec->setOutlineColor(sf::Color::Yellow);
	else rec->setOutlineColor(sf::Color::Black);
}

bool Button::isSelected(){
    return selected;
}


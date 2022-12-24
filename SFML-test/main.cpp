#include <iostream>
#include <unordered_map>
#include <sstream>
#include <functional>
#include <SFML/Graphics.hpp>

//#include "ParticleSystem.h"
//#include "RoundedRectangleShape.hpp"
//#include "Arm.h"

//void ParticleInit(sf::RenderTarget& window, sf::Time& elapsed, sf::Vector2i& mouse);
//void ParticleWork(sf::RenderTarget& window, sf::RectangleShape& target, ParticleSystem& particles);
//void ArmInit();
//void ArmWork(float& i, float& j, float& k, Arm& arm, Arm& arm2, Arm& arm3, sf::RenderTarget& window);

#define default_color sf::Color(45, 45, 45, 90)

enum FontStyle
{
	Regular,
	Bold
};

class Button : public sf::Drawable
{
private:
	sf::RectangleShape mBody;
	sf::Font mFont;
	sf::Text mText;

	bool mLeftClick;

	sf::Vector2f mTempPos;

	std::string mTheText;
	std::stringstream mSstream;
	
	std::function<void(void)> functional;

	void initializer(const std::string& _name, const sf::Vector2f _menuPos = sf::Vector2f(0,0))
	{
		this->mBody.setFillColor(default_color);
		this->mBody.setPosition(_menuPos);
		this->mBody.setSize(sf::Vector2f(100.f, 300.f));

		if (!this->mFont.loadFromFile("assets/fonts/Montserrat-Regular.ttf"))
			std::cout << "Error load font Montserrat-Regular.ttf";
		this->mTheText = "Button";
		this->mText.setFont(this->mFont);
		this->mText.setCharacterSize(20);
		this->mText.setFillColor(sf::Color::White);
		this->mText.setString(this->mTheText);
		this->mText.setOrigin(this->mText.getGlobalBounds().width / 2, 0);
		this->mText.setPosition(this->mBody.getPosition().x + this->mBody.getSize().x / 2, this->mBody.getPosition().y);

		this->mLeftClick = false;
	}

	void setLiteralPosition(const sf::Vector2f& _menuPos)
	{
		this->mBody.setPosition(this->mTempPos + _menuPos);
		this->updateOnce();
	}

	friend class Menu;
public:
	Button()
	{
		this->initializer("Button");
	}

	Button(const sf::Vector2f& _menuPos, const std::string& _name)
	{
		this->initializer(_name, _menuPos);
	}

	Button& operator=(const Button& other)
	{
		return *this;
	}

	virtual ~Button()
	{

	}

	//template<typename Funtional>
	void setFunction(const std::function<void(void)>& _functional)
	{
		functional =  _functional;
	}

	void function()
	{
		functional();
	}

	void setSize(const sf::Vector2f _size)
	{
		this->mBody.setSize(_size);
	}

	void setPosition(const sf::Vector2f _pos)
	{
		this->mTempPos = _pos;
		this->updateOnce();
	}

	void setColor(const sf::Color& _color)
	{
		this->mBody.setFillColor(_color);
	}

	void setOutline(const sf::Color& _color, const float& _thick = 0)
	{
		this->mBody.setOutlineColor(_color);
		if (_thick)
			this->mBody.setOutlineThickness(_thick);
	}

	void setString(const char* _string)
	{
		this->mTheText = _string;
		this->updateOnce();
	}

	void update(sf::Vector2f _mouse, const sf::Event& _event)
	{
		if (this->mBody.getGlobalBounds().contains(_mouse) &&
			_event.type == sf::Event::MouseButtonReleased &&
			_event.mouseButton.button == sf::Mouse::Left)
		{
			if (this->mLeftClick == false)
			{
				this->mLeftClick = true;
				this->function();
			}
			this->mLeftClick = true;
		}
		else
			this->mLeftClick = false; 
	}

	void updateOnce()
	{
		this->mText.setString(this->mTheText); 
		this->mText.setOrigin(this->mText.getGlobalBounds().width / 2, 0);
		this->mText.setPosition(this->mBody.getPosition().x + this->mBody.getSize().x / 2, this->mBody.getPosition().y);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(this->mBody);
		target.draw(this->mText);
	}
};

class Menu : public sf::Drawable
{
private:
	sf::RectangleShape mBackground;
	sf::Font mFontReg;
	sf::Font mFontBold;
	sf::Text mTitle;
	sf::Texture mTexture;

	std::string mText;
	std::stringstream mSstream;

	std::unordered_map<std::string, Button> mMap;

	void initializer()
	{
		this->mBackground.setSize(sf::Vector2f(300.f, 300.f));
		this->mBackground.setPosition(200.f, 10.f);
		this->mBackground.setFillColor(default_color);

		if (!this->mFontReg.loadFromFile("assets/fonts/Montserrat-Regular.ttf"))
			std::cout << "Error load font Montserrat-Regular.ttf";
		if (!this->mFontBold.loadFromFile("assets/fonts/Montserrat-Bold.ttf"))
			std::cout << "Error load font Montserrat-Bold.ttf";
		this->mText = "MENU";
		//this->mSstream << this->mText;
		this->mTitle.setFont(this->mFontReg);
		this->mTitle.setCharacterSize(50);
		this->mTitle.setFillColor(sf::Color::White);
		this->mTitle.setString(this->mText);
		this->mTitle.setOrigin(this->mTitle.getGlobalBounds().width / 2, 0.f);
		this->mTitle.setPosition(this->mBackground.getPosition().x + (this->mBackground.getSize().x / 2), this->mBackground.getPosition().y + 5.f);

		
	}
public:
	Menu()
	{
		this->initializer();
	}
	virtual ~Menu()
	{

	}

	void setSize(const float& _width, const float& _height)
	{
		this->mBackground.setSize(sf::Vector2f(_width, _height));
		this->updateOnce();
	}

	void setPosition(const sf::Vector2f& _pos)
	{
		this->mBackground.setPosition(_pos);
		this->updateOnce();
	}

	void setBackgroundColor(const sf::Color& _color)
	{
		this->mBackground.setFillColor(_color);
		this->updateOnce();
	}

	void setBackgroundTexture(const sf::Texture& _texture)
	{
		this->mBackground.setFillColor(sf::Color(0, 0, 0, 0));
		this->mBackground.setTexture(&_texture);
		this->updateOnce();
	}

	void setBackgroundTexture(const std::string& _texturePath)
	{
		this->mBackground.setFillColor(sf::Color(255, 255, 255, 255));
		if (!this->mTexture.loadFromFile(_texturePath))
			std::cout << "Error load background";
		this->mBackground.setTexture(&this->mTexture);
		this->updateOnce();
	}

	void setBackgroundTextureRect(const sf::IntRect& _rect)
	{
		this->mBackground.setTextureRect(_rect);
	}

	void setTitle(const std::string& _string)
	{
		this->mText = _string;
		this->updateOnce();
	}

	void setTitlePosition(const sf::Vector2f& _pos)
	{
		this->mTitle.setPosition(this->mBackground.getPosition().x + _pos.x, this->mBackground.getPosition().y + _pos.y);
	}

	void setTitleSize(const int& _size)
	{
		this->mTitle.setCharacterSize(_size);
	}

	void setTitleStyle(const FontStyle& _style)
	{
		switch (_style)
		{
		case Regular:
			this->mTitle.setFont(this->mFontReg);
			break;
		case Bold:
			this->mTitle.setFont(this->mFontBold);
			break;
		default:
			break;
		}
	}

	void setTitleFillColor(const sf::Color& _color)
	{
		this->mTitle.setFillColor(_color);
	}

	void setTitleOutline(const sf::Color& _color, const float& _thick = 0)
	{
		this->mTitle.setOutlineColor(_color);
		if (_thick)
			this->mTitle.setOutlineThickness(_thick);
	}

	void addButton(const char* _name)
	{
		this->mMap[_name] = Button(this->mBackground.getPosition(), _name);
		this->updateOnce();
	}

	void addButton(const std::string& _name, const float& _width, const float& _height)
	{
		this->mMap[_name] = Button(this->mBackground.getPosition(), _name);
		this->mMap[_name].setSize(sf::Vector2f(_width, _height));
		this->updateOnce();
	}

	void update(const sf::Vector2f& _mouse, const sf::Event& _event)
	{
		for (auto& it : this->mMap)
		{
			it.second.update(_mouse, _event);
		}
	}

	void updateOnce()
	{
		//this->mTitle.setPosition(this->mBackground.getPosition().x + (this->mBackground.getSize().x / 2), this->mBackground.getPosition().y + 5.f);
		this->mTitle.setString(this->mText);
		this->mTitle.setOrigin(this->mTitle.getGlobalBounds().width / 2, 0.f);

		for (auto& it : this->mMap)
		{
			it.second.setLiteralPosition(this->mBackground.getPosition());
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(this->mBackground);
		target.draw(this->mTitle);

		for (auto& it : this->mMap)
			target.draw(it.second);
	}

	Button& operator[](const char* _name)
	{
		return this->mMap[_name];
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 360), "SFML-test", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Vector2f mouse;
	sf::Clock clock;
	sf::Time elapsed = clock.restart();

	/*
	sf::RectangleShape target;
	ParticleSystem particles(1000, target.getGlobalBounds(), 4.f);

	ParticleInit(window, elapsed, mouse, target, particles);

	Arm* arm = new Arm(sf::Vector2f(1280 / 2, 720 / 2), 100.f, 0.f);
	Arm* arm2 = new Arm(arm->GetEndPos(), 100.f, 1.1f);
	Arm* arm3 = new Arm(arm2->GetEndPos(), 100.f, 1.6f);

	float i = 0.f, j = 0.f, k = 0.f;
	*/
	
	Menu menu;
	menu.setSize(640.f, 360.f);
	menu.setPosition(sf::Vector2f(0.f, 0.f));
	menu.setTitle("SIBILANT");
	menu.setTitleSize(40);
	menu.setTitlePosition(sf::Vector2f(320.f, 80.f));
	menu.setTitleStyle(FontStyle::Bold);
	menu.setTitleFillColor(sf::Color(200, 200, 255));
	menu.setTitleOutline(sf::Color::Black, 2.f);
	menu.addButton("Exit", 100.f, 30.f);
	menu.setBackgroundTexture("assets/backgrounds/Background.png");
	menu.setBackgroundTextureRect(sf::IntRect(0, 150, 900, 643));
	menu["Exit"].setPosition(sf::Vector2f(270.f, 270.f));
	menu["Exit"].setColor(sf::Color(45, 45, 60, 185));
	menu["Exit"].setOutline(sf::Color(255, 255, 255, 155), 0.75f);
	menu["Exit"].setString("Exit");
	menu.addButton("Start", 100.f, 30.f);
	menu["Start"].setPosition(sf::Vector2f(270.f, 220.f));
	menu["Start"].setColor(sf::Color(45, 45, 60, 185));
	menu["Start"].setOutline(sf::Color(255, 255, 255, 155), 0.75f);
	menu["Start"].setString("Start");
	menu.updateOnce();

	menu["Exit"].setFunction([&]() 
		{
			std::cout << "Ikan";
			window.close();
		}
	);
	

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();
				break;
			}
		}
		mouse = (sf::Vector2f)sf::Mouse::getPosition(window);

		menu.update(mouse, event);

		window.clear(sf::Color::White);
		window.draw(menu);

		//ArmWork(i, j, k, *arm, *arm2, *arm3, window);
		//ParticleWork(window, target, particles);
		window.display();
	}
	return 0;
}

//void ParticleInit(sf::RenderTarget& window, sf::Time& elapsed, sf::Vector2i& mouse, sf::RectangleShape& target, ParticleSystem& particles)
//{
//
//	target.setSize(sf::Vector2f(4.f, 4.f));
//	target.setPosition(640.f, 360.f);
//	target.setOrigin(2.f, 2.f);
//	target.setFillColor(sf::Color::Cyan);
//	
//	particles.setEmitter(window.mapPixelToCoords(mouse));
//	particles.update(elapsed);
//
//}
//void ParticleWork(sf::RenderTarget& window, sf::RectangleShape& target, ParticleSystem& particles)
//{
//
//	window.draw(target);
//	window.draw(particles);
//}
//void ArmInit()
//{
//
//}
//void ArmWork(float& i,float& j, float& k, Arm& arm, Arm& arm2, Arm& arm3, sf::RenderTarget& window)
//{
//	i += 0.02f; j += 0.01f; k += 0.01f;
//	if (i > 1000.f)
//		i = 0.f;
//	if (j > 2000.f)
//		j = 0.f;
//	if (k > 3000.f)
//		k = 0.f;
//
//	float angle1 = std::sin(i) * 3.f;
//	float angle2 = std::cos(j) * 2.f * 1.2f;
//	float angle3 = std::atan(k) * 1.2f * 0.5f;
//
//
//	arm.update(arm.pos, angle1);
//	arm2.update(arm.GetEndPos(), angle2, arm.getAngle());
//	arm3.update(arm2.GetEndPos(), angle3, arm2.getAngle());
//
//	window.draw(arm);
//	window.draw(arm2);
//	window.draw(arm3);
//}